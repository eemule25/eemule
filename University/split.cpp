#include "split.hh"

std::vector<std::string> split( std::string& str, char delim){
    std::vector<std::string> result = {""};
    bool cont = false;
    for ( auto cha : str ){
        if ( cha == '"' ){
            cont = !cont;
        } else if ( cha == delim && !cont){
            result.push_back("");
        } else {
            result.back().push_back(cha);
        }
    }
    if ( result.back() == "" ){
        result.erase(--result.end());
    }
    return result;
}
