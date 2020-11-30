/* Class: Date
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Represents a single date, that can be compared and advanced
 * by a some number of days.
 *
 * Note: Students shouldn't need to make changes to this file.
 * */
#ifndef DATE_HH
#define DATE_HH

#include <string>
#include <vector>

// Month lengths. Leap year february is handled in the code.
unsigned int const month_sizes[12] = { 31, 28, 31, 30, 31, 30,
                                       31, 31, 30, 31, 30, 31 };
// Default period lenght
const int PERIOD_LENGTH = 49; // seven weeks

class Date
{
public:
    // Constructor. If any of the params is out of sensible limits,
    // default value of 1 is used instead.
    Date(unsigned int day, unsigned int month, unsigned int year);
    ~Date();

    // Calls the advance_by with default PERIOD_LENGTH
    void advance_by_period_length();

    // Advances the date with given amount of days.
    // Can't be anvanced by negative amounts.
    void advance_by(unsigned int days);

    // Prints the date.
    void print() const;

    // Self-descriptive getters
    unsigned int get_day() const;
    unsigned int get_month() const;
    unsigned int get_year() const;

    // Comparison operators
    bool operator==(const Date& rhs) const;
    bool operator<(const Date& rhs) const;

private:
    unsigned int day_;
    unsigned int month_;
    unsigned int year_;

    bool is_leap_year() const;
};

#endif // DATE_HH
