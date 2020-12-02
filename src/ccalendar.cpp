//
// Created by marti on 22.05.2019.
//

#include <fstream>
#include "ccalendar.h"

//! Function that converts string to time and checks if time is valid.
/*!
 * @param str_time a constant string reference.
 * @param out_date out CDate reference.
 * @return False if date isn't valid or string didn't have valid format
 */
bool StrDate(const string & str_date, CDate & out_date){

    int day;
    int month;
    int year;
    CDate date_from;

    if (sscanf(str_date.c_str(), "%d.%d.%d", &day, &month, &year) != 3){
        return false;
    }

    date_from = CDate(day,month,year);

    if (!CheckDate(date_from)){
        return false;
    }

    out_date = date_from;

    return true;
}

//! Function that converts string to time and checks if time is valid.
/*!
 * @param str_time a constant string reference.
 * @param out_time out CTime reference.
 * @return False if time isn't valid or string didn't have valid format
 */
bool StrTime(const string & str_time, CTime & out_time){

    int minute;
    int hour;
    CTime time_to;


    if (sscanf(str_time.c_str(), "%d:%d", &hour, &minute) != 2){
        return false;
    }

    time_to = CTime(hour,minute);

    if (!CheckTime(time_to)){
        return false;
    }

    out_time = time_to;

    return true;
}

bool CCalendar::AddEvent() {

    string name;
    string str_time;
    string str_date;
    string event_type;
    CDate date_from;
    CDate date_to;
    CTime time_from;
    CTime time_to;
    int minute;
    int hour;
    int day;
    int month;
    int year;
    int period = 0;

    CTime time_now = CurrentTime();
    CDate date_now = CurrentDate();

    Separate();

    // Here user inputs name of the event they want to add.
    cout << "Write name of your event." << endl;
    // manages user input
    while(1) {
        StrBack();
        cout << "Your event name:";

        cin >> name;

        if (cin.eof()) {
            return false;
        }

        if (name == "Back") {
            return true;
        }

        if (events.find(name) == events.end()) {
            break;
        } else {
            Message("An event with identical name already exists, please choose different one.");
            continue;
        }
    }
// ================================================================================================================================================= //
    // Here user inputs date of the event they want to add.

    Separate();
    cout << "Now enter a date from which your event starts." << endl;

    // Manages user input.
    while(1) {
        StrBack();
        cout << "Your event date(in format: 1.1.2019):";

        cin >> str_date;

        if (cin.eof()) {
            return false;
        }

        if (str_date == "Back") {
            return true;
        }

        if ( !StrDate(str_date,date_from) ){
            Message("Your date is invalid. Please try again.");
            continue;
        }

        if (date_from < CurrentDate()){
            Message("Your date is invalid. Please try again.");
            cout<<"Earliest date you can use: " << CurrentDate();
        }

        break;
    }

// ================================================================================================================================================= //
    // Here user inputs starting time of the event they want to add.

    Separate();
    cout << "Now enter a time from which your event starts." << endl;

    // Manages user input.
    while(1) {
        StrBack();
        cout << "Your event time(in format HH:MM): ";

        cin >> str_time;

        if (cin.eof()) {
            return false;
        }

        if (str_time == "Back") {
            return true;
        }

        if( !StrTime(str_time, time_from)){
            Message("Your time is invalid. Please try again.");
            continue;
        }

        break;
    }


// ================================================================================================================================================= //
    // Here user decides which type of event they want to add.

    Separate();
    cout << "Now choose the desired type of your event. You can choose \"Simple\", \"Long\", \"Repeating\"" << endl;

    // Manages user input.
    while (1){
        StrBack();
        cout << "Your choice: ";

        cin >> event_type;

        if (cin.eof()) {
            return false;
        }

        if (event_type == "Back"){
            return false;
        } else if (event_type == "Simple"){
        } else if (event_type == "Long"){

            Separate();
            cout << "You chose long event type. Now you need to write a date to which your event will last." << endl;

            while(1) {
                StrBack();
                cout << "Your event date(in format: 1.1.2019):";

                cin >> str_date;

                if (cin.eof()) {
                    return false;
                }

                if (str_date == "Back") {
                    Separate();
                    return true;
                }

                if ( !StrDate(str_date,date_to) ){
                    Message("Your date is invalid. Please try again.");
                    continue;
                }

                if (date_to < date_from){
                    Message("Your ending date can't be sooner than your starting date. Please try again.");
                    continue;
                }
                break;
            }

        } else if (event_type == "Repeating"){

            Separate();
            cout << "You chose repeating event type. Now you need to write whole decimal number greater than 1 which will represent period of repeating of your event" << endl;
            while (1){

                StrBack();
                cout << "Your period: ";
                cin >> period;

                if (cin.eof()) {
                    return false;
                }

                if (!cin.good() || period < 1){
                    Message("Your period is invalid. Please try again.");
                    continue;
                }
                break;
            }

        } else {
            Message("Your input is invalid. Please try again.");
            continue;
        }
        break;
    }

// ================================================================================================================================================= //
    // Here user inputs ending time of the event they want to add.

    Separate();
    cout << "Now enter a time at which your event ends." << endl;

    // Manages user input.
    while(1) {
        StrBack();
        cout << "Your event time(in format HH:MM): ";

        cin >> str_time;

        if (cin.eof()) {
            return false;
        }

        if (str_time == "Back") {
            Separate();
            return true;
        }

        if( !StrTime(str_time, time_to) ){
            Message("Your time is invalid. Please try again.");
            continue;
        }

        if (event_type != "Long"){
            if ( time_from < time_to ){
                Message("Your ending time can't be sooner than your starting time. Please try again.");
                continue;
            }
        }

        break;
    }

// ================================================================================================================================================= //
    // Here user decides if they want to save the event or abort.

    Separate();
    cout << "If you want to save the event, write \"Save\"" << endl;
    cout << "If you want to abort event creation, write \"Abort\"" << endl;

    // Manages user input.
    while(1) {
        cout << "Your choice: ";

        string input;

        cin >> input;

        if (cin.eof()) {
            return false;
        }

        if (input == "Save") {
            if (event_type == "Simple"){
                CEvent * event = new CEvent (name, date_from, time_from, time_to);
                event->ExportString();
                events.insert(make_pair(name,event));
            } else if (event_type == "Long"){
                CEvent * event = new CLongEvent(name, date_from, time_from, time_to, date_to);
                events.insert(make_pair(name,event));
            } else if (event_type == "Repeating"){
                CEvent * event = new CRepeatingEvent (name, date_from, time_from, time_to, period);
                events.insert(make_pair(name,event));
            }
            Message("Event added successfully!");
            return true;
        } else if (input == "Abort") {
            Message("Action aborted successfully!");
            return true;
        } else {
            Message("Your choice is invalid. Please try again.");
            continue;
        }
    }

}

bool CCalendar::DeleteEvent() {

    string input_event;

    Separate();
    cout << "Write name of the event you want to delete." << endl;
    StrBack();

    cout<<endl<<"Your event name: "<<endl;

    cin >> input_event;

    if (cin.eof()) {
        return false;
    }

    if (input_event == "Back"){
        Separate();
        return true;
    }

    // Searches for the event.
    auto it = events.find(input_event);
    if (it == events.end()){
        Message("Event not found.");
        return true;
    }

    // Manages user input.
    while(1) {
        Separate();
        cout << "Matching event " << "\"" << input_event << "\" found." << endl;
        cout << "If you want to delete the event, write \"Delete\"" << endl;
        cout << "If you want to abort deletion, write \"Abort\"" << endl << endl;
        cout << "Your choice: ";

        string input;

        cin >> input;

        if (cin.eof()) {
            return false;
        }

        if (input == "Delete") {
            events.erase(input_event);
            cout<<endl;
            Message("Event was deleted successfully!");
            return true;
        } else if (input == "Abort") {
            Message("Action aborted successfully!");
            return true;
        } else {
            Message("Your choice is invalid. Please try again.");
        }
    }

}

bool CCalendar::SearchEvent() const {

    string input;

    Separate();
    cout << "Write name of the event you want to search." << endl;
    StrBack();

    cout<<endl<<"Your event name: "<<endl;

    cin >> input;

    if (cin.eof()) {
        return false;
    }

    if (input == "Back"){
        Separate();
        return true;
    }

    // Searches for the event.
    auto it = events.find(input);
    if (it == events.end()){
        Separate();
        cout << "Event not found." << endl;
        cout << "====================================================================================================================" << endl;
        return true;
    }

    Separate();
    cout<<"Event with a matching name found. Here are the event details: "<< endl << endl;
    it->second->Print();
    cout << "====================================================================================================================" << endl;
    if (Menu()){
        return true;
    }
    return false;
}

bool CCalendar::EditEvent() {

    string input_event;

    Separate();
    cout << "Write name of the event you want to edit." << endl;
    StrBack();

    cout<<endl<<"Your event name: "<<endl;

    cin >> input_event;

    if (cin.eof()) {
        return false;
    }

    if (input_event == "Back"){
        Separate();
        return true;
    }

    // Searches for the event.
    auto it = events.find(input_event);
    if (it == events.end()){
        Separate();
        cout << "Event not found." << endl;
        Separate();
        return true;
    }

    Separate();
    cout<<"Event with a matching name found. Here are the event details: "<< endl << endl;
    it->second->Print();
    cout << "====================================================================================================================" << endl;

    if( it->second->Edit() ) {
        return true;
    } else {
        return false;
    }

}

bool CCalendar::ExportEvent() {

    Separate();

    StrBack();
    cout<<"Write name of the event you wish to export: ";

    string input_event;

    cin >> input_event;

    if (cin.eof()) {
        return false;
    }

    if (input_event == "Back"){
        Separate();
        return true;
    }

    // Searches for the event.
    auto it = events.find(input_event);
    if (it == events.end()){
        Separate();
        cout << "Event not found." << endl;
        cout << "====================================================================================================================" << endl;
        return true;
    }

    string str_export = it->second->ExportString();

    // Manages user input.
    while(1) {
        Separate();
        cout << "Matching event " << "\"" << input_event << "\" found." << endl;
        cout << "If you want to export the event, write \"Export\"" << endl;
        cout << "If you want to abort deletion, write \"Abort\"" << endl << endl;
        cout << "Your choice: ";

        string input;

        cin >> input;

        if (cin.eof()) {
            return false;
        }

        if (input == "Export") {

            while(1) {
                Separate();
                cout << "Write name of the file you wish to export your event into." << endl;

                cin >> input;

                ifstream check_file(input);
                if (check_file.good()) {
                    Separate();
                    cout << "A file with the same name already exists, please choose another one." << endl;
                    continue;
                }
                break;
            }

            ofstream out_file(input);
            // Checks if file can be created and written into.
            if(!out_file.good()){
                cout<<"Export failed and was aborted. Check folder write rights and try again." << endl;
                return true;
            }

            out_file<< str_export;
            out_file.close();

            Separate();
            cout << "Event was exported successfully!" << endl;
            cout << "====================================================================================================================" << endl;
            return true;
        } else if (input == "Abort") {
            Message("Action aborted successfully.");
            return true;
        } else {
            IsInvalid("input");
        }
    }
}

bool CCalendar::ImportEvent() {

    Separate();
    cout << "Write name of the file to export your event from." <<endl;
    StrBack();
    cout<<endl;

    string input;
    string type;
    string name;
    string str_date;
    string str_date_to;
    string str_time_to;
    string str_time_from;
    string str_period;
    CDate date_from;
    CDate date_to;
    CTime time_from;
    CTime time_to;
    int period;


    ifstream in_file;

    // Manages user input.
    while(1) {
        cout << "Your file: ";

        cin >> input;

        if (cin.eof()) {
            return false;
        }

        if (input == "Back") {
            Separate();
            return true;
        }

        in_file.open(input);

        if (!in_file.good()) {
            Separate();
            cout << "File couldn't be open. Please try again" << endl;
            cout<< "===================================================================================================================="<< endl;
            continue;
        }
        break;
    }

        in_file>>type;
        in_file>>name;
        in_file>>str_date;
        in_file>>str_time_from;
        in_file>>str_time_to;

        if ( !StrDate(str_date, date_from) ){
            Message("Invalid data format. Import aborted.");
            return true;
        }

        if (!StrTime(str_time_from, time_from)){
            Message("Invalid data format. Import aborted.");
            return true;
        }

        if (!StrTime(str_time_to, time_to)){
            Message("Invalid data format. Import aborted.");
            return true;
        }

        // Check if event with same name already exists in calendar.
        if (events.find(name) != events.end()) {
            Message("Event couldn't be imported because event with identical name already exists.");
            return true;
        }

        if (type == "Simple") {

            CEvent* event = new CEvent(name,date_from,time_from,time_to);
            events.insert(make_pair(name,event));
        } else if ( type == "Long" ){

            in_file >> str_date_to;

            if ( !StrDate(str_date_to, date_to) ){
                Message("Invalid data format. Import aborted.");
                return true;
            }

            if(date_from > date_to){
                Message("Invalid data format. Import aborted.");
                return true;
            }

            if(date_from == date_to && time_to < time_from){
                Message("Invalid data format. Import aborted.");
                return true;
            }

            CEvent* event = new CLongEvent(name,date_from,time_from,time_to,date_to);
            events.insert(make_pair(name,event));
        } else if (type == "Repeating"){

            in_file >> period;

            if(!in_file.good()){
                Message("Invalid data format. Import aborted.");
                return true;
            }

            CEvent* event = new CRepeatingEvent(name,date_from,time_from,time_to,period);
            events.insert(make_pair(name,event));
        } else {
            Message("Invalid data format. Import aborted.");
            return true;
        }

        Message("Event imported successfully!");
        return true;
}

bool CCalendar::ShowMonth() const {

    Separate();
    cout<<"Write month and year you wish to show.(In format \"06.2019\")"<<endl;
    StrBack();

    string input;

    int month;
    int year;

    // Controls user input.
    while(1){
        cout<<"Your month: ";

        cin >> input;

        if (cin.eof()) {
            return false;
        }

        if (input == "Back") {
            Separate();
            return true;
        }

        if ( sscanf(input.c_str(), "%d.%d", &month, &year) != 2){
            Separate();
            cout<<"Input is invalid. Please try again."<<endl;
            continue;
        }

        if( year < 1 || month > 12 || month <1 ){
            Separate();
            cout<<"Month or year is invalid. Please try again."<<endl;
            continue;
        }
        break;
    }

    // Necessary data for writing out calendar
    int days_in_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    string month_names[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    map<string, int> day_index = {{"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3}, {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}, {"Sunday", 7}};

    if (!IsLeap(year)){
        days_in_month[1] += 1;
    }


    CDate month_start(1,month,year);
    CDate month_end(days_in_month[month-1], month, year);

    string first_day_tmp = GetDay(month_start);

    auto it = day_index.find(first_day_tmp);

    int first_day_index = it->second;

    // Gets first day of the visual calendar.
    if (first_day_index != 1){
        if ( month == 1 ){
            month = 12;
        } else {
            month--;
        }
        first_day_index = days_in_month[month-1] - (first_day_index - 2);
    }

    // Starting date of the visual representation of the calendar.
    CDate cal_start(first_day_index, month, year);

    // Writes out name of month and year.
    Separate();
    cout<< endl <<  "  " << month_names[month-1]<<" "<<year<<endl;
    cout<< "  ================================="<<endl;
    cout<< "  Mon  Tue  Wed  Thu  Fri  Sat  Sun"<<endl;

    int n = 0;

    // Writes out days.
   while (1){
        if (cal_start < month_start || cal_start > month_end){
            cout << "     ";
        } else {
            if (cal_start.GetDay() < 10){
                cout << "    " << cal_start.GetDay();
            } else {
                cout << "   " << cal_start.GetDay();
            }
        }

        n++;
        if(n == 7){
            n=0;
            cout<<endl;
            if (cal_start > month_end){
                break;
            }
        }
        cal_start++;
    }

    cout << endl << endl;
    // Writes out events for each day of this month.
    for (int i = 1; i < days_in_month[month -1]+1; i++) {

        auto it = events.begin();

        string day_events = "  " + to_string(i) + ". - ";
        bool out = false;

        while (it != events.end()) {
            if (it->second->IsInDay(month_start)) {
                day_events += it->first + " ";
                out = true;
            }
            it++;
        }

        if (out) {
            cout << day_events << endl;
        }
        month_start++;
    }

    Separate();
    if ( Menu()){
        return true;
    }
    return false;

}

bool CCalendar::ShowWeek() const {

    CDate today = CurrentDate();

    int year = today.GetYear();
    int month = today.GetMonth();

    int days_in_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    map<string, int> day_index = {{"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3}, {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}, {"Sunday", 7}};

    if (!IsLeap(year)){
        days_in_month[1] += 1;
    }


    string first_day_tmp = GetDay(today);

    auto it = day_index.find(first_day_tmp);

    int first_day_index = it->second;

    // Gets first day and date of the current week
    if (first_day_index != 1){
        if ( today.GetDay() < 7 ){
            if ( month == 1 ){
                month = 12;
            } else {
                month--;
            }
        }
        first_day_index = days_in_month[month-1] - (first_day_index - 2);
    }


    // Starting date of the visual representation of the calendar.
    CDate week_start(first_day_index, month, year);

    // Writes out name of month and year.
    cout << "  Today is: " << CurrentDate() << " - " << GetDay(CurrentDate()) << endl;
    cout << "  ==========================="<<endl;
    cout << "  Mon Tue Wed Thu Fri Sat Sun"<<endl;

    CDate week_start_tmp = week_start;

    // Writes out day numbers.
    for (int i = 0; i < 6; i++){

        if (week_start_tmp.GetDay() < 10){
            cout << "   " << week_start_tmp.GetDay() << ".";
        } else {
            cout << "  " << week_start_tmp.GetDay() << ".";
        }

        week_start_tmp++;
    }

    cout<<endl;
    week_start_tmp = week_start;

    // Writes out number of month.
    for (int i = 0; i < 6; i++){

        if (week_start_tmp.GetMonth() < 10){
            cout << "   " << week_start_tmp.GetMonth() << ".";
        } else {
            cout << "  " << week_start_tmp.GetMonth() << ".";
        }

        week_start_tmp++;
    }

    cout << endl << endl;

    // Writes events for each day of this month.
    for (int i = 1; i < 7; i++) {

        auto it = events.begin();

        string day_events = "  " + to_string(i) + ". - ";
        bool out = false;

        while (it != events.end()) {

            if (it->second->IsInDay(week_start)) {
                day_events += it->first + " ";
                out = true;
            }
            it++;
        }

        if (out) {
            cout << day_events << endl;
        }
        week_start++;
    }

    Separate();
    if ( Menu()){
        return true;
    }
    return false;
}

bool CCalendar::ShowDay() const {

    Separate();
    cout<<"Enter date of the day you would like to see." << endl;
    StrBack();

    string input;
    CDate date;

    // Controls user input.
    while (1){

        cout<<"Your date: ";

        cin>>input;

        if (cin.eof()) {
            return false;
        }

        if (input == "Back"){
            Separate();
            return true;
        }

        if (!StrDate(input,date)){
            IsInvalid("date");
            continue;
        }

        break;
    }

    Separate();

    cout<<"Date:   " << date<<endl;
    cout<<"Day:    " << GetDay(date)<<endl;
    cout<<"Events: ";

    auto it = events.begin();

    bool first = false;

    // Writes all events that happen on that day
    while(it != events.end() && !first){
        if (it->second->IsInDay(date)){
            cout<<it->second->GetName();
            !first;
        }
        it++;
    }

    while(it != events.end()){
        if (it->second->IsInDay(date)){
            cout<<", "<<it->second->GetName();
        }
        it++;
    }

    Separate();
    if (Menu()){
        return true;
    }
    return false;

}

void CCalendar::Save() {

    if (events.empty()){
        return;
    }

    auto it = events.begin();

    ofstream save_file("calendar_db");

    // Checks if file can be created and written into
    if(!save_file.good()){
        cout<<"Failed to access calendar DB. Calendar couldn't be saved."<<endl;
        return;
    }

    while (it != events.end()){
        save_file<<it->second->ExportString();
        save_file<<" ";
        it++;
    }

    save_file.close();

}

void CCalendar::Load() {

    string input;
    string type;
    string name;
    string str_date;
    string str_date_to;
    string str_time_to;
    string str_time_from;
    string str_period;
    CDate date_from;
    CDate date_to;
    CTime time_from;
    CTime time_to;
    int period;


    ifstream save_file("calendar_db");

    // Checks if file exists or if it could be opened.
    if(!save_file.good()){
        Message("Failed to access calendar DB. Calenedar couldn't be loaded.");
        return;
    }

    // Loads events until reaches end of file.
    while(save_file.peek() != EOF) {
        save_file >> type;
        save_file >> name;
        save_file >> str_date;
        save_file >> str_time_from;
        save_file >> str_time_to;

        if (!StrDate(str_date, date_from)) {
            Message("DB appears to be corrupted and couldn't be loaded. Calendar will be empty.");
            DeleteList();
            return;
        }

        if (!StrTime(str_time_from, time_from)) {
            Message("DB appears to be corrupted and couldn't be loaded. Calendar will be empty.");
            DeleteList();
            return;
        }

        if (!StrTime(str_time_to, time_to)) {
            Message("DB appears to be corrupted and couldn't be loaded. Calendar will be empty.");
            DeleteList();
            return;
        }

        if (type == "Simple") {

            CEvent *event = new CEvent(name, date_from, time_from, time_to);
            events.insert(make_pair(name, event));
        } else if (type == "Long") {

            save_file >> str_date_to;

            if (!StrDate(str_date_to, date_to)) {
                Message("DB appears to be corrupted and couldn't be loaded. Calendar will be empty.");
                DeleteList();
                return;
            }

            if (date_from > date_to) {
                Message("DB appears to be corrupted and couldn't be loaded. Calendar will be empty.");
                DeleteList();
                return;
            }

            if (date_from == date_to && time_to < time_from) {
                Message("DB appears to be corrupted and couldn't be loaded. Calendar will be empty.");
                DeleteList();
                return;
            }

            CEvent *event = new CLongEvent(name, date_from, time_from, time_to, date_to);
            events.insert(make_pair(name, event));
        } else if (type == "Repeating") {

            save_file >> period;

            if (save_file.bad()) {
                Message("DB appears to be corrupted and couldn't be loaded. Calendar will be empty.");
                DeleteList();
                return;
            }

            if (save_file.fail()) {
                Message("DB appears to be corrupted and couldn't be loaded. Calendar will be empty.");
                DeleteList();
                return;
            }


            CEvent *event = new CRepeatingEvent(name, date_from, time_from, time_to, period);
            events.insert(make_pair(name, event));
        } else {
            Message("DB appears to be corrupted and couldn't be loaded. Calendar will be empty.");
            DeleteList();
            return;
        }
    }
    Message("Calendar DB loaded successfully.");
}

void CCalendar::DeleteList() {

    auto it = events.begin();

    // Frees out memory first
    while (it != events.end()){
        delete it->second;
        it++;
    }

    events.clear();

}

CCalendar::~CCalendar() {
    DeleteList();
}

