//
// Created by marti on 22.05.2019.
//

#ifndef CALENDAR_CTIME_H
#define CALENDAR_CTIME_H

#include <iostream>

//! Class implementing time
/*!
 * Class also implements some useful functions and operations to work efficiently with times.
 * */
class CTime {
public:
    //! A constructor without parameters.
    CTime();
    //! A constructor with paramaters.
    /*!
     * \param hour an int parameter.
     * \param minute an int parameter.
     * */
    CTime(int hour, int minute);
    //! A getter method, returns hour variable.
    int GetHour() const;
    //! A getter method, returns minute variable.
    int GetMinute() const;
private:
    //! int variable representing hour in time.
    int hour;
    //! int variable representing minute in time.
    int minute;
};

//! Operator << for class
/*!
 * Prints out time into ostream.
 * \param os an ostream reference.
 * \param time a constant CDate reference.
 * \return ostream reference.
 * */
std::ostream & operator << (std::ostream & os, const CTime & time);

//! Operator < for the class
/*!
 * \param time1 constant CTime reference.
 * \param time2 constant CTime reference.
 * \return True if time1 is farther in time than time2
 * */
bool operator < (CTime &time1, CTime &time2);

#endif //CALENDAR_CTIME_H
