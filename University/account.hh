/* Class: Account
  * ----------
  * Defines a student or a staff account in the university system.
  *
  * In the project, this class should be expanded to
  * include study history of the account.
  * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include "date.hh"
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Instance;
class Course;

const std::string NO_SIGNUPS = "No signups found on this instance.";
const std::string SIGNED_UP = "Signed up on the course instance.";
const std::string COMPLETED = "Course completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "frontname lastname"
     * @param email
     * @param account_number
     */
    Account(std::string full_name, std::string email, int account_number);

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email();

    /**
     * @brief marks student's course to be completed if possible
     * @param course
     */
    void complete(Course* course);

    /**
     * @brief adds the given instance to student's current instances
     * @param instance
     */
    void add_instance_to_current(Instance* instance);

    /**
     * @brief adds the given course to student's current courses
     * @param course
     */
    void add_course_to_current_courses(Course* course);

    /**
     * @brief check if student has given instance
     * @param instance
     * @return true if student has instance named given name, false otherwise
     */
    bool check_student_instances(Instance* instance);

    /**
     * @brief prints student's all current and completed courses
     */
    void print_all_courses();

    /**
     * @brief prints student's all completed courses
     */
    void print_completed_courses();

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;
    std::vector<Instance*> current_instances_;
    std::vector<Course*> current_courses_;
    std::vector<Course*> completed_;
    int total_credits_ = 0;
};

#endif // ACCOUNT_HH
