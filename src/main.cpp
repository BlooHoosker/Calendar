#include <iostream>
#include <string>

#include "cdate.h"
#include "ctime.h"
#include "cevent.h"
#include "mylib.h"
#include "ccalendar.h"

using namespace std;

int main() {

    CCalendar calendar;
    bool exit = false;
    string menu_choice;

    // Loads calendar DB.
    calendar.Load();

    cout << endl << "Welcome to your calendar!" << endl;

    // Manages user input and main menu.
    while(!exit) {
        cout << endl << "You are at main menu. Choose one of the actions bellow(write them into the console):" << endl << endl;
        cout << "\"AddEvent\" to add an event to your calendar." << endl;
        cout << "\"DeleteEvent\" to delete an event." << endl;
        cout << "\"SearchEvent\" to search an event." << endl;
        cout << "\"EditEvent\" to edit an event." << endl;
        cout << "\"ShowMonth\" to show a specified month from your calendar." << endl;
        cout << "\"ShowWeek\" to show a specified week from your calendar." << endl;
        cout << "\"ShowDay\" to show a specified day from your calendar." << endl;
        cout << "\"ImportEvent\" to import event from a file." << endl;
        cout << "\"ExportEvent\" to export event to a file." << endl;
        cout << "\"Exit\" to exit the program." << endl << endl;

        cout << "Choice: ";
        cin >> menu_choice;
        if (cin.eof()){
            calendar.Save();
            return 0;
        }

        if (menu_choice == "AddEvent"){
            if (!calendar.AddEvent()){
                calendar.Save();
                return 0;
            }
        } else if (menu_choice == "DeleteEvent") {
            if (!calendar.DeleteEvent()){
                calendar.Save();
                return 0;
            }
        } else if (menu_choice == "SearchEvent") {
            if (!calendar.SearchEvent()){
                calendar.Save();
                return 0;
            }
        } else if (menu_choice == "EditEvent") {
            if(!calendar.EditEvent()){
                calendar.Save();
                return 0;
            }
        } else if (menu_choice == "ShowMonth") {
            if(!calendar.ShowMonth()){
                calendar.Save();
                return 0;
            }
        } else if (menu_choice == "ShowWeek"){
            if(!calendar.ShowWeek()){
                calendar.Save();
                return 0;
            }
        } else if (menu_choice == "ShowDay"){
            if(!calendar.ShowDay()){
                calendar.Save();
                return 0;
            }
        } else if (menu_choice == "ImportEvent"){
            if(!calendar.ImportEvent()){
                calendar.Save();
                return 0;
            }
        } else if (menu_choice == "ExportEvent"){
            if(!calendar.ExportEvent()){
                calendar.Save();
                return 0;
            }
        } else if (menu_choice == "Exit"){
            calendar.Save();
            exit = true;
        } else {
            Separate();
            cout << "Wrong input. Please try again." << endl;
            cout << "====================================================================================================================" << endl;
        }

    }
    return 0;
}