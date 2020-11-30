#include "instance.hh"
#include "course.hh"

Instance::Instance(std::string name):
    name_(name), date_(nullptr)
{
}


void Instance::print()
{
    std::cout << name_ << std::endl;
    std::cout << INDENT << "Starting date: " << starting_date_ << "." <<
                 starting_month_ << "." << starting_year_;
    std::cout << std::endl;
    std::cout << INDENT << "Amount of students: " << students_.size() <<
                 std::endl;
}

void Instance::print_students()
{
    for ( auto student : students_ ){
        std::cout << INDENT;
        student->print();
    }
}

bool Instance::is_named(std::string name)
{
    if(name == name_) {
        return true;
    } else {
        return false;
    }
}

bool Instance::add_student(Account* student)
{
    if(find(students_.begin(), students_.end(), student) != students_.end()) {
        std::cout << ALREADY_REGISTERED << std::endl;
        return false;
    } else if(check_ == false) {
        std::cout << LATE << std::endl;
        return false;
    } else {
        students_.push_back(student);
        std::cout << "Signed up on the course instance." << std::endl;
        return true;
    }
}

void Instance::set_date(Date *date)
{
    starting_date_ = date->get_day();
    starting_month_ = date->get_month();
    starting_year_ = date->get_year();
}

void Instance::print_name()
{
    std::cout << name_ << std::endl;
}

void Instance::check_starting_date(Date *date)
{
    if(date->get_year() > starting_year_) {
        check_ = false;
    } else if(date->get_month() > starting_month_) {
        check_ = false;
    } else if(date->get_day() > starting_date_) {
        check_ = false;
    } else {
        check_ = true;
    }
}







