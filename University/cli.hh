/* Class: Cli
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Command line interface example with function pointers.
 *
 *
 * Note: Students shouldn't need to make changes to this file.
 * */
#ifndef CLI_HH
#define CLI_HH

#include "university.hh"
#include <string>
#include <iostream>
#include <vector>

// Declare a type of function called.
using MemberFunc = void (University::*)(const std::vector<std::string>& params);


// Struct that 'defines' a function.
struct Cmd{
    std::vector<std::string> aliases;
    std::string name;
    std::vector<std::string> params;
    int numeric_param_index;
    std::string brief_expl;
    MemberFunc func_ptr;
};

// Error strings.
const std::string UNINITIALIZED = "Error: Given object hasn't been initialized. Stopping.";
const std::string WRONG_PARAMETERS = "Error: Wrong amount of parameters.";
const std::string NOT_NUMERIC = "Error: Wrong type of parameters.";
const std::string UNKNOWN_CMD = "Error: Unknown commands given.";
const std::string FILE_READING_ERROR = "Error: Can't read given file.";
const std::string FILE_READING_OK = "Input read from file: ";

class Cli
{
public:
    /**
     * @brief Cli
     * @param university pointer to the university obj the functions are called to
     * @param prompt that is printed before taking in user input
     */
    Cli(University* university, std::string prompt);

    /**
     * @brief exec the cli
     * @return false if execution should end, true if it should continue.
     */
    bool exec();

private:
    /**
     * @brief pop_front
     * @param vec
     * vector utility func that erases the first element of given vector.
     *
     * @note All iterators to the container are invalitaded
     */
    void pop_front(std::vector<std::string>& vec);

    /**
     * @brief find_command
     * @param cmd
     * @return Cmd pointer if one with given alias is found.
     */
    Cmd* find_command(std::string cmd);

    /**
     * @brief print_help
     * @param params
     * Generate and print a help, either generic ( no params ) or
     * specific ( func name as param )
     */
    void print_help(std::vector<std::string> params);

    /**
     * @brief print_cmd_info
     * @param cmd
     * @param longer
     * Print info of a single cmd.
     * if longer == true, print brief and params.
     */
    void print_cmd_info(Cmd *cmd, bool longer = false);

    /**
     * @brief read_from_file
     * @param filename
     * @return false if file could not be read, true otherwise.
     *
     * @note will remove informative output, so even cmds are read, they may
     * not have worked.
     */
    bool read_from_file(const std::string& filename);

    University* university_;
    std::string prompt_;
    bool can_start;

    // Vector that stores all cmd info.
    std::vector<Cmd> cmds_ = {
        {{"PRINT_COURSES", "PAC"},"Print all courses",{},-1,"Prints all available courses.", &University::print_courses},
        {{"PRINT_ACCOUNTS", "PAA"},"Print all accounts",{},-1,"Prints all available accounts.", &University::print_accounts},
        {{"NEW_COURSE", "NC"},"New course", {"course code", "name"},-1,"Adds a new course, if none with param code are found in the system.", &University::add_course},
        {{"PRINT_COURSE", "PC"},"Print course",{"course code"},-1,"Print long info of course with given code.", &University::print_course},
        {{"ADD_ACCOUNT", "AA"},"Add account",{"full name", "email" },-1,"Add a new generic account", &University::add_account},
        {{"PRINT_ACCOUNT", "PA"},"Print account",{"account number"},0,"Prints account's long info", &University::print_account_info},
        {{"ADD_STAFF", "AS"},"Add staff",{"course code", "account number"},1,"Adds account with given number to course staff.", &University::add_staff_to_course},
        {{"ADD_INSTANCE", "AI"},"Add instance",{"course code", "instance name"},-1,"Add instance with given name to given course.", &University::add_instance},
        {{"SIGN_UP", "S"},"Sign up on a course",{"course code", "instance name", "account number"},2,"Sign account up on a course instance.", &University::sign_up_on_course},
        {{"COMPLETE", "C"},"Complete a course",{"course code", "instance name", "account number"},2,"Mark a course as completed.", &University::complete_course},
        {{"PRINT_SIGNUPS", "PS"},"Print current signups on a course",{"course code"},-1,"Print all currently active signups on given course, separated by instances", &University::print_signups},
        {{"PRINT_STUDY_STATE", "PSS"},"Print study state",{"account number"},0,"Print all signups and courses of a given student.", &University::print_study_state},
        {{"PRINT_COMPLETED", "PCC"},"Print completed courses of a student",{"account number"},0,"Prints short info of al courses the student has completed.", &University::print_completed},
        {{"DATE", "D"},"Set date",{"day", "month", "year"},1,"Sets the date to given date", &University::set_date},
        {{"ADVANCE", "A"},"Advance",{},-1,"Advance date by 1 period.", &University::advance_by_period},
        {{"ADVANCE_BY", "AB"},"Advance by",{"days"},0,"Advance the date by given number of days.", &University::advance_date},
        {{"READ_FROM", "RF"}, "Read", {"filename"},-1,"Read the database from given file. Does not clear the database.", nullptr},
        {{"HELP", "H"},"Help",{"function"},-1,"Prints generic or func specific help.",nullptr},
        {{"QUIT", "Q"}, "Quit", {},-1, "Quits the program.", nullptr}
    };

};

#endif // CLI_HH
