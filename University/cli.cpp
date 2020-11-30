#include "cli.hh"
#include "utils.hh"
#include <fstream>
#include <sstream>

Cli::Cli(University* university, std::string prompt):
    university_(university),
    prompt_(prompt),
    can_start(university != nullptr)
{

}

bool Cli::exec()
{
    if ( !can_start ){
        std::cout << UNINITIALIZED << std::endl;
        return false;
    }
    std::vector<std::string> input;
    std::string cmd;
    std::cout << prompt_ ;
    std::getline(std::cin, cmd);
    input = utils::split(cmd, ' ');
    if ( input.empty() ){
        return true;
    }
    cmd = input.front();
    pop_front(input);
    Cmd* func = find_command(cmd);
    if ( func == nullptr ){
        std::cout << UNKNOWN_CMD << std::endl;
        return true;
    }
    if ( func->name == "Quit" ){
        return false;
    }

    if  ( func->name == "Help" ){
        print_help(input);
        return true;
    }

    if ( func->name == "Set date" )
    {
        if ( not utils::is_numeric(input.at(0), false) or
             not utils::is_numeric(input.at(1), false) or
             not utils::is_numeric(input.at(2), false) ){
            std::cout << NOT_NUMERIC << std::endl;
            return true;
        }
    }

    if ( func->params.size() != input.size() ){
        std::cout << WRONG_PARAMETERS << std::endl;
        return true;
    }

    if( func->numeric_param_index >= 0 and not utils::is_numeric
            (input.at(func->numeric_param_index), true) ) {
        std::cout << NOT_NUMERIC << std::endl;
        return true;
    }

    if ( func->name == "Read"){
        if ( !read_from_file(input.at(0)) ){
            std::cout << FILE_READING_ERROR << std::endl;
            return false;
        } else {
            std::cout << FILE_READING_OK << input.at(0) << std::endl;
        }
        return true;
    }

    // Call to member func ptr: (OBJ ->* FUNC_PTR)(PARAMS)
    (university_->*(func->func_ptr))(input);
    return true;
}

void Cli::pop_front(std::vector<std::string> &vec)
{
    vec.erase(vec.begin(), ++vec.begin());
}

Cmd *Cli::find_command(std::string cmd)
{
    for (unsigned int i = 0; i < cmd.size(); i++){
        cmd.at(i) = std::toupper(cmd.at(i));
    }
    for ( auto command = cmds_.begin(); command != cmds_.end(); command++ ){
        for ( auto alias : command->aliases ){
            if ( alias == cmd ){
                return &(*command);
            }
        }
    }
    return nullptr;
}

void Cli::print_help(std::vector<std::string> params)
{
    if ( params.size() != 0 ){
        print_cmd_info(find_command(params.at(0)), true);
        return;
    }
    for ( Cmd cmd : cmds_ ){
        print_cmd_info(&cmd);
    }
}

void Cli::print_cmd_info(Cmd* cmd, bool longer)
{
    std::cout << cmd->name << " : " ;
    for ( auto alias : cmd->aliases ){
        std::cout << alias << " ";
    }
    std::cout << std::endl;
    if ( longer ) {
        std::cout << cmd->brief_expl
                  << std::endl
                  << "Params: " << std::endl;
        if ( cmd->params.size() == 0 ){
            std::cout << "None." << std::endl;
        } else {
            for ( auto param : cmd->params){
                std::cout << param << std::endl;
            }
        }
    }
}

bool Cli::read_from_file(const std::string &filename)
{
    std::ifstream inputfile(filename);
    if ( !inputfile ){
        return false;
    }
    // Redirect the file to cin and save the old cin
    auto cinbuf = std::cin.rdbuf(inputfile.rdbuf());
    std::ostringstream unwanted_output;
    auto coutbuf = std::cout.rdbuf(unwanted_output.rdbuf());

    while( exec() ){}

    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    inputfile.close();

    return true;
}
