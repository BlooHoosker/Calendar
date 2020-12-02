//
// Created by marti on 22.05.2019.
//

#include "crepeatingevent.h"
#include "mylib.h"

CRepeatingEvent::CRepeatingEvent(const string &name, const CDate &date, const CTime &from_time, const CTime &to_time, int period): CEvent(name,date,from_time,to_time) {
    type = "Repeating";
    this->period = period;
}

bool CRepeatingEvent::IsInDay(const CDate &date) const {

    int number_of_days = NumberOfDays(this->date,date);

    if (number_of_days % period == 0){
        return true;
    }
    return false;
}

void CRepeatingEvent::Print() const {
    cout<<"Event"<<endl;
    cout<<"Type:          " << type<< endl;
    cout<<"Name:          " << name<<endl;
    cout<<"Start date:    " << date << endl;
    cout<<"Time begining: " << from_time << endl;
    cout<<"Time ending:   " << to_time << endl;
    cout<<"Period:        " << "Every " << period << " days"<<endl;
}

bool CRepeatingEvent::Edit() {
    cout<<endl;
    cout<<"Your event found is type " << type << " that means you can edit following details: " << endl;
    cout<<"Date, Time begining, Time ending, Repeating period" << endl <<endl;
    cout<<"Write \"Date\" to edit date of your event"<<endl;
    cout<<"Write \"Start\" to edit starting time of your event"<<endl;
    cout<<"Write \"End\" to edit ending time of your event"<<endl;
    cout<<"Write \"Period\" to edit repeating period of your event"<<endl;
    cout << "If you want to cancel this operation write \"Back\"" << endl << endl;

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

        // Edits a parameter based on user input.
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
                    return false;
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

        } else if (input == "Period") {

            int new_period = 0;

            while (1){

                StrBack();
                cout << "Your new repeating period: ";
                cin >> new_period;

                if (cin.eof()) {
                    return false;
                }

                if (!cin.good() || period < 1){
                    IsInvalid("period");
                    continue;
                }
                break;
            }

            period = new_period;
            Separate();
            cout<<"Ending time successfully edited!"<<endl;
            cout << "====================================================================================================================" << endl;
            return true;

        }else if (input == "Back") {
                return true;
        } else {
            IsInvalid("choice");
            continue;
        }

    }
}

string CRepeatingEvent::ExportString() const {
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
    a += " ";
    a += to_string(period);

    return a;
}


