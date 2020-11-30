/* Class: Instance
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a single instance.
 *
 * Note: Students should make changes to this class, and add their info and
 * specifics of the class to this comment.
 * */
#ifndef INSTANCE_HH
#define INSTANCE_HH

#include "account.hh"
#include "date.hh"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "utils.hh"

// Forward-declaration of Course, so that instance can point
// to the course it belongs to.
class Course;

const std::string ALREADY_REGISTERED = "Error: Student has already registered "
                                       "on this course.";
const std::string LATE = "Error: Can't sign up on instance after the starting "
                         "date.";
const std::string INDENT = "    ";

class Instance
{
public:
    /**
     * @brief Instance constructor
     * @param name
     */
    Instance(std::string name);

    /**
     * @brief prints instance information
     */
    void print();

    /**
     * @brief prints the information of students in the instance
     */
    void print_students();

    /**
     * @brief returns boolean on whether the course has that instance
     * @param name
     * @return true if course has instance named given name, false otherwise
     */
    bool is_named(std::string name);
    
    /**
     * @brief if possible, adds student to instance
     * @param student
     * @return true if was possible to add student to instance, false otherwise
     */
    bool add_student(Account* student);

    /**
     * @brief saves the start date of the instance
     * @param date
     */
    void set_date(Date* date);

    /**
     * @brief print the name of the instance
     */
    void print_name();

    /**
     * @brief checks if the new date is larger than starting day of the instance
     * @param date
     */
    void check_starting_date(Date* date);


private:
    std::string name_;
    Date* date_;
    std::vector<Account*> students_;
    unsigned int starting_date_;
    unsigned int starting_month_;
    unsigned int starting_year_;
    bool check_ = true;
};

#endif // INSTANCE_HH
