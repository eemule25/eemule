#include "course.hh"

Course::Course(std::string code, std::string name, int credits):
    course_code_(code), name_(name), credits_(credits)
{

}

Course::~Course()
{
    for ( Instance* inst : instances_ ){
        delete inst;
    }
}

void Course::print_info(bool print_new_line)
{
    std::cout << course_code_ << " : " << name_;
    if(print_new_line) {
        std::cout << std::endl;
    }
}

void Course::print_staff()
{

    std::cout << "* Staff: " << std::endl;
    for (auto acc : course_staff_ ){
        acc->print();
    }
}

void Course::print_long_info()
{
    std::cout << "* Course name: " << name_ << std::endl
              << "* Code: " << course_code_ << std::endl;
    print_staff();
    std::cout << "* Instances: " << std::endl;

    for ( auto instance : instances_ ){
        instance->print();
    }
}

void Course::print_signups()
{
    for ( auto inst : instances_ ){
        inst->print();
        inst->print_students();
    }
}

void Course::add_staff(Account *new_staff)
{
    for(unsigned int i = 0; i < course_staff_.size(); ++i)
    {
        if(course_staff_.at(i) == new_staff)
        {
            std::cout << STAFF_EXISTS << std::endl;
            return;
        }
    }

    course_staff_.push_back(new_staff);
    std::cout << STAFF_ADDED << std::endl;
}

void Course::new_instance(Instance *n_instance)
{
    instances_.push_back(n_instance);
    std::cout << INSTANCE_ADDED << std::endl;
}

bool Course::has_instance(const std::string &name)
{
    for ( auto inst : instances_ ){
        if ( inst->is_named(name)){
            return true;
        }
    }
    return false;
}

Instance *Course::get_instance(std::string name)
{
    for ( Instance* inst : instances_ ){
        if ( inst->is_named(name) ){
            return inst;
        }
    }
    return nullptr;
}

const std::string Course::get_code() const
{
    return course_code_;
}

int Course::get_credits() const
{
    return credits_;
}


