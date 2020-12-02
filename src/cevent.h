//
// Created by marti on 22.05.2019.
//

#ifndef CALENDAR_CEVENT_H
#define CALENDAR_CEVENT_H

#include "cdate.h"
#include "ctime.h"
#include "mylib.h"


using namespace std;

//! Class implementing an event.
/*!
 * Polymorph class that implements event and its functionalities.
 * Classes CRepeatingEvent and CLongEvent are derived from this class
 * */
class CEvent {
public:
    //! A constructor with paramaters.
    /*!
     * \param name a constant string reference.
     * \param date a constant date reference.
     * \param from_time a constant time reference.
     * \param to_time a constant time reference.
     * */
    CEvent(const string & name, const CDate & date, const CTime & from_time, const CTime & to_time);
    //! Virtual destructor.
    virtual ~CEvent();
    //! Method that prints all event details into the console based on type of event.
    virtual void Print() const;
    //! Virtual method for editing events.
    /*!
     *  This method manages user interface, user input, and editing details of events in calendar.
     *  Differs based on type of event.
     *  \return True - if method ends normally or with an error message for the user
     *  \return False - if method ends with user declaring no further input by Ctrl+D
     * */
    virtual bool Edit();
    //! Virtual method that checks if event happens in a particular date.
    /*!
     *  Differs based on type of event.
     * \return True if event falls under that day.
     */
    virtual bool IsInDay(const CDate & date) const;
    //! A virtual getter method, returns year variable.
    /*!
     * Virtual method used for exporting all event information into a single string.
     * Used for exporting and saving events.
     * Implementation differs based on type of event.
     * \return string
     */
    virtual string ExportString() const;
    //! A getter method, returns name as a string.
    string GetName() const;
protected:
    //! A string variable representing type of the event.
    string type;
    //! A string variable representing name of the event.
    string name;
    //! A date variable representing date of the event.
    CDate date;
    //! A time variable representing starting time of the event.
    CTime from_time;
    //! A time variable representing ending time of the event.
    CTime to_time;
};




#endif //CALENDAR_CEVENT_H
