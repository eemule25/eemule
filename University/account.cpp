#include "account.hh"
#include "utils.hh"
#include "instance.hh"
#include "course.hh"

Account::Account(std::string full_name, std::string email, int account_number):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    email_(email),
    account_number_(account_number)
{
    std::vector<std::string> name = utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();
}


void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email()
{
    return email_;
}

void Account::complete(Course* course)
{
    for(long unsigned int i=0; i<current_courses_.size(); i++) {
        if(current_courses_.at(i) == course) {
            completed_.push_back(course);
            std::cout << "Course completed." << std::endl;
            current_courses_.erase(current_courses_.begin() + i);
            total_credits_ += 5;
            return;
        }
    }
    std::cout << NO_SIGNUPS << std::endl;
}

void Account::add_instance_to_current(Instance* instance)
{
    current_instances_.push_back(instance);
}

void Account::add_course_to_current_courses(Course *course)
{
    current_courses_.push_back(course);
}

bool Account::check_student_instances(Instance* instance)
{
    if(find(current_instances_.begin(), current_instances_.end(), instance)
            == current_instances_.end()) {
        std::cout << NO_SIGNUPS << std::endl;
        return false;
    } else {
        return true;
    }
}

void Account::print_all_courses()
{
    int i=0;
    std::cout << "Current:" << std::endl;
    for(auto course : current_courses_) {
        course->print_info(false);
        std::cout << " ";
        current_instances_.at(i)->print_name();
        i++;
    }
    std::cout << "Completed:" << std::endl;
    print_completed_courses();
}

void Account::print_completed_courses()
{
    for(auto course : completed_) {
        course->print_info(true);
    }
    std::cout << "Total credits:" << " " << total_credits_ << std::endl;

}




