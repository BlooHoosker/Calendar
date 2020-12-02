//
// Created by marti on 26.05.2019.
//

#ifndef CALENDAR_MYLIB_H
#define CALENDAR_MYLIB_H


#include "cdate.h"
#include "ctime.h"

using namespace std;

//! Function that gets a day
/*!
 * This function returns what day of a week it is on a given date.
 * \param date const CDate reference.
 * \return day of a week as a string
 * */
string GetDay(const CDate & date);

//! Function that checks if given year is leap
/*!
 * \param date const CDate reference.
 * \return True if year is leap
 * */
bool IsLeap(int year);

//! Function that calculates number of days between two days
/*!
 * \param begin const CDate reference.
 * \param end const CDate reference.
 * \return number of days as an int.
 * */
int NumberOfDays(const CDate & begin, const CDate & end);

//! Function that checks if date is valid
/*!
 * \param date const CDate reference.
 * \return True if date is valid.
 * */
bool CheckDate(const CDate & date);

//! Function that checks if time is valid
/*!
 * \param time const CDate reference.
 * \return True if time is valid.
 * */
bool CheckTime(const CTime & time);

//! Function that returns current time.
/*!
 * \return Current time as CTime.
 * */
CTime CurrentTime();

//! Function that returns current date.
/*!
 * \return Current date as CDate.
 * */
CDate CurrentDate();

//! Function that writes message with a parameter
/*!
 * Function writes out message with a parameter which says what is the message about.
 * \param text const string reference.
 * */
void IsInvalid(const string & text);

//! Function that writes message into console
/*!
 * Message tells user that if they wish to return to menu they should write "Back".
 */
void StrBack();

//! Function that writes message into console
/*!
 * Message tells user that if they wish to return to menu they should write "Menu".
 * Also manages user input of "Menu"
 *  \return True - if method ends normally or with an error message for the user.
 *  \return False - if method ends with user declaring no further input by Ctrl+D.
 */
bool Menu();

//! Function that writes out a separating line in console.
void Separate();

//! Function that writes message into console in a specific format
void Message(const string & text);

#endif //CALENDAR_MYLIB_H
