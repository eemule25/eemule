#include "utils.hh"

std::vector<std::string> utils::split( std::string& str, char delim){
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

bool utils::is_numeric(std::string s, bool zero_allowed)
{
    if( not zero_allowed and s.length() == 1 and s.at(0) == '0' ) {
        return false;
    }
    for( unsigned int i = 0; i < s.length(); ++i ) {
        if( not isdigit(s.at(i)) ) {
            return false;
        }
    }
    return true;
}
