/* Class: University
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represents a simple university with students, staff and courses
 * with instances.
 *
 * Note: Students shouldn't need to make changes to the existing functions
 * or their implementations.
 * */
#ifndef UNIVERSITY_HH
#define UNIVERSITY_HH

#include "account.hh"
#include "course.hh"
#include "date.hh"
#include "utils.hh"
#include <vector>
#include <map>
#include <string>

const std::string WRONG_PARAMS = "Error: Wrong amount or type of parameters.";
const std::string ALREADY_EXISTS = "Error: Already exists.";
const std::string INSTANCE_EXISTS = "Error: Instance already exists on this "
                                    "course.";
const std::string CANT_FIND = "Error: Can't find anything that matches the "
                              "given string: ";
const std::string NEW_ACCOUNT = "A new account has been created.";
const std::string NEW_COURSE = "A new course has been created.";

using Params = const std::vector<std::string>&;

class University
{
public:
    // Constructor and deconstructor.
    University();
    ~University();

    /**
     * @brief add_course
     * @param params: course code, name
     * Adds a neew course to the system.
     * If course with given code is found from the system, gives an error.
     */
    void add_course(Params params);
    /**
     * @brief print_courses
     * Prints short info of all courses in the system.
     */
    void print_courses(Params);
    /**
     * @brief print_course
     * @param params: course code
     * Prints longer info of given course.
     * If no course with given code is found, error is given.
     */
    void print_course(Params params);

    /**
     * @brief add_account
     * @param params: full name, email
     * Adds a new account to the system.
     * If there's an account in the system associated with the given email,
     * this gives an error.
     */
    void add_account(Params params);
    /**
     * @brief print_accounts
     * Print all accounts found in the system.
     */
    void print_accounts(Params);
    /**
     * @brief print_account_info
     * @param params: account number
     * Print single accounts info
     * If account is not found from the system, gives an error.
     */
    void print_account_info(Params params);
    /**
     * @brief add_staff_to_course
     * @param params: course code, account number
     * Add staff to the course.
     * If course or account is not found, gives an error.
     */
    void add_staff_to_course(Params params);

    /**
     * @brief add_instance
     * @param params: course code, instance name
     * Adds an instance to given course.
     * If course is not found, gives an error.
     */
    void add_instance(Params params);

    /**
     * @brief sign_up_on_course
     * @param params: course code, instance name, account number
     * Signs up the account on instance found on course.
     * If any of the paramteres are not found, gives and error.
     * @note instance should be associated with the course, not just any
     * instance named correctly.
     */
    void sign_up_on_course(Params params);
    /**
     * @brief complete_course
     * @param params: course code, instance name, account number
     * Complete the course instance student has previously signed up on.
     * Gives an error if any of the params is not found or if no matching
     * signup is found.
     */
    void complete_course(Params params);
    /**
     * @brief print_signups
     * @param params: course code
     * Print current signups on a course.
     * If course is not found, gives an error.
     */
    void print_signups(Params params);

    /**
     * @brief print_study_state
     * @param params: account number
     * Print all signups, completed courses and total credits of a given student.
     * If no account is found, gives an error.
     */
    void print_study_state(Params params);
    /**
     * @brief print_completed
     * @param params: account number
     * Prints completed courses and total credits of the student.
     * If no account is found, gives an error.
     */
    void print_completed(Params params);

    /**
     * @brief set_date
     * @param params: day, month, year
     * Tries to set the date to the given date.
     * @note Date-object will always be a valid date, so if one of the
     * parameters is unfit, it will just be replaced with default.
     */
    void set_date(Params);
    /**
     * @brief advance_date
     * @param params: days
     * Advances the date by given amount of days.
     */
    void advance_date(Params params);
    /**
     * @brief advance_by_period
     * Advances the date by 1 period length.
     */
    void advance_by_period(Params);
private:
    // <Account number, Account*>
    std::map<int, Account*> accounts_;
    // <Course code, Course*>
    std::map<std::string, Course*> courses_;
    // <Course code, Course*>
    std::map<std::string, Instance*> instances_;

    // Keeps track of the next account id to be given
    int running_number_;

};

#endif // UNIVERSITY_HH
