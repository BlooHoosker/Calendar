//
// Created by marti on 22.05.2019.
//

#ifndef CALENDAR_CREPEATINGEVENT_H
#define CALENDAR_CREPEATINGEVENT_H

#include "cdate.h"
#include "ctime.h"
#include "cevent.h"

using namespace std;

//! Class implementing a repeating event.
/*!
 * Polymorph class that implements a repeating event and its functionalities and properties.
 * Class is derived from CEvent class.
 * */
class CRepeatingEvent : public CEvent {
public:
    //! A constructor with paramaters.
    /*!
     * \param name a constant string reference.
     * \param date a constant date reference.
     * \param from_time a constant time reference.
     * \param to_time a constant time reference.
     * \param period an int variable.
     * */
    CRepeatingEvent(const string & name, const CDate & date, const CTime & from_time, const CTime & to_time, int period);
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
private:
    //! An int variable representing period in which the event repeats.
    int period;
};


#endif //CALENDAR_CREPEATINGEVENT_H
