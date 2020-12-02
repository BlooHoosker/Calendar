//
// Created by marti on 22.05.2019.
//

#ifndef CALENDAR_CDATE_H
#define CALENDAR_CDATE_H

#include <iostream>

//! Class implementing date
/*!
 * Class also implements some useful functions and operations to work efficiently with dates.
 * */
class CDate {
public:
    //! A constructor without parameters.
    CDate();
    //! A constructor with paramaters.
    /*!
     * \param day an int parameter.
     * \param month an int parameter.
     * \param year an int parameter.
     * */
    CDate(int day, int month, int year);
    //! A getter method, returns day variable.
    int GetDay() const;
    //! A getter method, returns month variable.
    int GetMonth() const;
    //! A getter method, returns year variable.
    int GetYear() const;
    //! ++ operator for the class.
    /*!
     * Increases date by one day.
     * */
    CDate &operator++(int);
private:
    //! An int variable representing a day in month.
    int day;
    //! An int variable representing a month in year.
    int month;
    //! An int variable representing a year.
    int year;
};

//! Operator == for the class
/*!
 * \param date1 constant CDate reference.
 * \param date2 constant CDate reference.
 * \return True if two dates match.
 * */
bool operator == (const CDate & date1, const CDate & date2);

//! Operator < for the class
/*!
 * \param date1 constant CDate reference.
 * \param date2 constant CDate reference.
 * \return True if date2 is farther in time than date1
 * */
bool operator < (const CDate & date1, const CDate & date2);

//! Operator > for the class
/*!
 * \param date1 constant CDate reference.
 * \param date2 constant CDate reference.
 * \return True if date1 is farther in time than date2
 * */
bool operator > (const CDate & date1, const CDate & date2);

//! Operator << for class
/*!
 * Prints out date into ostream.
 * \param os an ostream reference.
 * \param date a constant CDate reference.
 * \return ostream reference.
 * */
std::ostream & operator << (std::ostream & os, const CDate &date);

#endif //CALENDAR_CDATE_H
