//
// Created by marti on 22.05.2019.
//

#include "cevent.h"
#include <fstream>
#include <string>

CEvent::CEvent(const string &name, const CDate &date, const CTime &from_time, const CTime &to_time) {
    type = "Simple";
    this->name = name;
    this->date = date;
    this->from_time = from_time;
    this->to_time = to_time;
}

CEvent::~CEvent() {
}

bool CEvent::IsInDay(const CDate &date) const {
    if (this->date == date){
        return true;
    }
    return false;
}

void CEvent::Print() const {

    cout<<"Event"<<endl;
    cout<<"Type:          " << type<< endl;
    cout<<"Name:          " << name<<endl;
    cout<<"Date:          " << date << endl;
    cout<<"Time begining: " << from_time << endl;
    cout<<"Time ending:   " << to_time << endl;

}

bool CEvent::Edit() {

    cout<<endl;
    cout<<"Your event found is type " << type << " that means you can edit following details: " << endl;
    cout<<"Date, Time begining, Time ending." << endl<<endl;
    cout<<"Write \"Date\" to edit date of your event"<<endl;
    cout<<"Write \"Start\" to edit starting time of your event"<<endl;
    cout<<"Write \"End\" to edit ending time of your event"<<endl;
    cout << "If you want to cancel this operation write \"Back\"" << endl<<endl;

    string input;

    CDate today = CurrentDate();
    CTime time_now = CurrentTime();

    // Manages user input.
    while(1) {

        cout << "Your choice: ";

        cin >> input;

        if (cin.eof()) {
            return false;
        }

        // Edits parameter of event based on user input.
        if (input == "Date") {

            CDate new_date;

            while(1) {

                int day = 0;
                int month = 0;
                int year = 0;

                StrBack();
                cout << "Your new event date(in format: 1.1.2019):";

                cin >> input;

                if (cin.eof()) {
                    return false;
                }

                if (input == "Back") {
                    return true;
                }

                if (sscanf(input.c_str(), "%d.%d.%d", &day, &month, &year) != 3){
                    IsInvalid("date");
                    continue;
                }

                new_date = CDate(day,month,year);

                if (!CheckDate(new_date)){
                    IsInvalid("date");
                    continue;
                }
                break;
            }

            date = new_date;
            Separate();
            cout<<"Date successfully edited!"<<endl;
            cout << "====================================================================================================================" << endl;

            return true;

        } else if (input == "Start") {

            CTime new_time;

            while(1) {

                int hour = 0;
                int minute = 0;

                StrBack();
                cout << "Your new event starting time(in format HH:MM):";

                cin >> input;

                if (cin.eof()) {
                    return false;
                }

                if (input == "Back") {
                    return true;
                }

                if (sscanf(input.c_str(), "%d:%d", &hour, &minute) != 2){
                    IsInvalid("time");
                    continue;
                }

                new_time = CTime(hour,minute);

                if (!CheckTime(new_time) || (today == date && new_time < time_now)){
                    IsInvalid("time");
                    continue;
                }
                break;
            }

            from_time = new_time;
            Separate();
            cout<<"Starting time successfully edited!"<<endl;
            cout << "====================================================================================================================" << endl;

            return true;

        } else if (input == "End") {

            CTime new_time;

            while(1) {

                int hour = 0;
                int minute = 0;

                StrBack();
                cout << "Your new event ending time(in format HH:MM):";

                cin >> input;

                if (cin.eof()) {
                    return false;
                }

                if (input == "Back") {
                    return true;
                }

                if (sscanf(input.c_str(), "%d:%d", &hour, &minute) != 2){
                    IsInvalid("time");
                    continue;
                }

                new_time = CTime(hour,minute);

                if (!CheckTime(new_time) || (today == date && new_time < time_now) || (today == date && new_time < from_time)){
                    IsInvalid("time");
                    continue;
                }
                break;
            }

            to_time = new_time;
            Separate();
            cout<<"Ending time successfully edited!"<<endl;
            cout << "====================================================================================================================" << endl;

            return true;

        } else if (input == "Back") {
            return true;
        } else {
            IsInvalid("choice");
            continue;
        }

    }

}

string CEvent::ExportString() const {

    string a;

    a += type + " " + name + " ";
    a += to_string(date.GetDay());
    a += ".";
    a +=  to_string(date.GetMonth());
    a += ".";
    a +=  to_string(date.GetYear());
    a += " ";
    a += to_string(from_time.GetHour());
    a += ":";
    a += to_string(from_time.GetMinute());
    a += " ";
    a += to_string(to_time.GetHour());
    a += ":";
    a += to_string(to_time.GetMinute());

    return a;

}

string CEvent::GetName() const {
    return name;
}




