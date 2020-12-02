//
// Created by marti on 22.05.2019.
//

#ifndef CALENDAR_CCALENDAR_H
#define CALENDAR_CCALENDAR_H

#include <map>

#include "cdate.h"
#include "ctime.h"
#include "mylib.h"
#include "cevent.h"
#include "crepeatingevent.h"
#include "clongevent.h"

using namespace std;

//!  A calendar class.
/*!
 * This is the main class of the program, it contains main methods for managing the calendar features.
*/
class CCalendar {
public:
    //! A destructor, takes care of freeing allocated memory for events.
    ~CCalendar();
    //! Method that adds an event to calendar.
    /*!
     *  This method manages user interface, user input, and adding events to calendar.
     *  \return True - if method ends normally or with an error message for the user.
     *  \return False - if method ends with user declaring no further input by Ctrl+D.
     * */
    bool AddEvent();
    //! Method that deletes an event from calendar.
    /*!
     *  This method manages user interface, user input, and deleting events from calendar.
     *  \return True - if method ends normally or with an error message for the user.
     *  \return False - if method ends with user declaring no further input by Ctrl+D.
     * */
    bool DeleteEvent();
    //! Method that searches an event in calendar.
    /*!
     *  This method manages searches an event in calendar and displays information about it.
     *  \return True - if method ends normally or with an error message for the user.
     *  \return False - if method ends with user declaring no further input by Ctrl+D.
     * */
    bool SearchEvent() const;
    //! Method that edits an existing event in calendar.
    /*!
     *  This method manages user interface, user input, and editing details of events in calendar.
     *  \return True - if method ends normally or with an error message for the user.
     *  \return False - if method ends with user declaring no further input by Ctrl+D.
     * */
    bool EditEvent();
    //! Method that displays calendar in a month format.
    /*!
     *  This method manages displaying calendar in a specified month, as well as all events happening in that month.
     *  \return True - if method ends normally or with an error message for the user.
     *  \return False - if method ends with user declaring no further input by Ctrl+D.
     * */
    bool ShowMonth()const;
    //! Method that displays calendar in a week format.
    /*!
     *  This method manages displaying calendar in current week, as well as all events happening in that week.
     *  \return True - if method ends normally or with an error message for the user.
     *  \return False - if method ends with user declaring no further input by Ctrl+D.
     * */
    bool ShowWeek()const;
    //! Method that displays one day of the calendar and its details.
    /*!
     *  \return True - if method ends normally or with an error message for the user.
     *  \return False - if method ends with user declaring no further input by Ctrl+D.
     * */
    bool ShowDay()const;
    //! Method that imports an event from a file.
    /*!
     *  \return True - if method ends normally or with an error message for the user.
     *  \return False - if method ends with user declaring no further input by Ctrl+D.
     * */
    bool ImportEvent();
    //! Method that exports an event to a file.
    /*!
     *  \return True - if method ends normally or with an error message for the user.
     *  \return False - if method ends with user declaring no further input by Ctrl+D.
     * */
    bool ExportEvent();
    //! Method that saves all events.
    /*!
     *  Method that menages saving of all events into calendar's own database.
     * */
    void Save();
    //! Method that loads all events.
    /*!
     *  Method that menages loading of all events from calendar's own database. If DB file can't be opened or is corrupted, events won't be loaded.
     * */
    void Load();
private:
    //! Private method that frees all allocated events in calendar from memory.
    void DeleteList();

    //! Private STL container to store events and search them.
    map<string,CEvent*> events;
};


#endif //CALENDAR_CCALENDAR_H
