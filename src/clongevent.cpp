//
// Created by marti on 22.05.2019.
//

#include "clongevent.h"

void CLongEvent::Print() const {
    cout<<"Event"<<endl;
    cout<<"Type:          " << type<< endl;
    cout<<"Name:          " << name<<endl;
    cout<<"Start date:    " << date << endl;
    cout<<"Time begining: " << from_time << endl;
    cout<<"End date:      " << to_date<< endl;
    cout<<"Time ending:   " << to_time << endl;
}

bool CLongEvent::Edit() {
    cout<<endl;
    cout<<"Your event found is type " << type << " that means you can edit following details: " << endl;
    cout<<"Date begining, Date ending, Time begining, Time ending." << endl<<endl;
    cout<<"Write \"StartDate\" to edit starting date of your event"<<endl;
    cout<<"Write \"EndDate\" to edit ending date of your event"<<endl;
    cout<<"Write \"StartTime\" to edit starting time of your event"<<endl;
    cout<<"Write \"EndTime\" to edit ending time of your event"<<endl;
    cout << "If you want to cancel this operation write \"Back\"" << endl<<endl;

    string input;

    CDate today = CurrentDate();
    CTime time_now = CurrentTime();

    // Manages user input
    while(1) {

        cout << "Your choice: ";

        cin >> input;

        if (cin.eof()) {
            return false;
        }

        // Edits a parameter based on user input.
        if (input == "StartDate") {

            CDate new_date;

            while(1) {

                int day = 0;
                int month = 0;
                int year = 0;

                StrBack();
                cout << "Your new event starting date(in format: 1.1.2019):";

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

        } else if (input == "StartTime") {

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

        } else if (input == "EndTime") {

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

        } else if (input == "EndDate") {

            CDate new_date;

            while(1) {

                int day = 0;
                int month = 0;
                int year = 0;

                StrBack();
                cout << "Your new event ending date(in format: 1.1.2019):";

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

                if (!CheckDate(new_date) || new_date > date){
                    IsInvalid("date");
                    continue;
                }
                break;
            }

            to_date = new_date;
            Separate();
            cout<<"Ending date successfully edited!"<<endl;
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

bool CLongEvent::IsInDay(const CDate &date) const {

    if (this->date < date && this->to_date > date  ){
        return true;
    } else if( this->date == date || this->to_date == date){
        return true;
    }

    return false;

}

CLongEvent::CLongEvent(const string &name, const CDate &date, const CTime &from_time, const CTime &to_time,
                       const CDate &to_date) : CEvent(name,date,from_time,to_time){
    type = "Long";
    this->to_date = to_date;
}

string CLongEvent::ExportString() const {
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
    a += to_string(to_date.GetDay());
    a += ".";
    a +=  to_string(to_date.GetMonth());
    a += ".";
    a +=  to_string(to_date.GetYear());

    return a;

}
