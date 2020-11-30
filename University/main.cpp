/* University:
 *
 * Desc:
 * This program describes the operation of the university system.
 * It reads user-given commands. Depending on the command,
 * the program either stores data into a suitable data structure,
 * or makes searches in the data structure in question.
 * */

#include "utils.hh"
#include "cli.hh"
#include "university.hh"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

const std::string PROMPT = "Uni> ";


int main()
{
    University* university = new University();
    Cli cli(university, PROMPT);
    while ( cli.exec() ){}

    delete university;
    return EXIT_SUCCESS;
}
