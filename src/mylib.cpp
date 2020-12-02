//
// Created by marti on 26.05.2019.
//

#include <ctime>
#include <iostream>
#include <string>

#include "mylib.h"

CTime CurrentTime() {

    time_t t = time(0);
    tm* current_date = localtime(&t);
    int minute;
    int hour;

    minute = current_date->tm_min;
    hour = current_date->tm_hour;

    CTime c_time(hour,minute);

    return c_time;
}

CDate CurrentDate() {

    time_t t = time(0);
    tm* current_date = localtime(&t);
    int day;
    int month;
    int year;

    day = current_date->tm_mday;
    month = current_date->tm_mon + 1;
    year = current_date->tm_year + 1900;

    CDate c_date (day,month,year);

    return c_date;
}

string GetDay(const CDate &date) {

    int year = date.GetYear();
    int day = date.GetDay();
    int month = date.GetMonth();

    /* Take the last 2 digits of the year. */
    int centuries = year / 100;
    int milenium = centuries / 10;
    int last_two = year - 100 * centuries;
    int result = last_two;

    /* Divide by 4, and drop any remainder. */
    result = (result - (result % 4)) / 4;

    /* Add the day of the month */
    result += day;

    /* Add the month's key value, from the following table. */
    /* months key values */
    int month_key[12] = {1,4,4,0,2,5,0,3,6,1,4,6};
    result += month_key[month-1];

    /* If your date is in January or February of a leap year, subtract 1 */
    if ( IsLeap(year) && ( month == 1 || month == 2 ) ){
        result--;
    }

    /* Add the century code from the following table. */
    /* century keys, going by 1700s, 1800s, 1900s, 2000s */
    int century_key[4] = {4, 2, 0, 6 };

    while (centuries > 20 || centuries < 17) {
        if (centuries < 17) {
            centuries += 4;
        } else {
            centuries -= 4;
        }
    }

    result += century_key[centuries-17];

    /* Add the last two digits of the year. 48 + 82 = 130. */
    result += last_two;

    /*Divide by 7 and take the remainder. */
    result = result % 7;

    /* This time, 0 means Saturday, 1 means Sunday, 2 means Monday */
    string day_names[7] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

    return day_names[result];

}

bool IsLeap(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)){
        return true;
    } else {
        return false;
    }
}

int NumberOfDays(const CDate &begin, const CDate &end) {

    int year_begin = begin.GetYear();
    int day_begin = begin.GetDay();
    int month_begin = begin.GetMonth();

    int year_end = end.GetYear();
    int day_end = end.GetDay();
    int month_end = end.GetMonth();

    int days_amount = 0;

    int days_in_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    /* first check if the dates are in the same year */
    int year_delta = year_end - year_begin;

    /* if dates are in different years it will calculate number of days */
    if (year_delta > 0){

        /* add full years if needed */
        int year_begin_tmp = year_begin;
        year_begin_tmp++;
        while (year_begin_tmp != year_end){
            if (IsLeap(year_begin_tmp)){
                days_amount += 366;
            } else {
                days_amount += 365;
            }
            year_begin_tmp++;
        }

        /* adds days from begin date until dec 31st that year */
        days_amount += days_in_month[month_begin-1] - day_begin;
        month_begin++;
        while (month_begin < 13){
            days_amount += days_in_month[month_begin-1];
            if (IsLeap(year_begin) && month_begin == 2){
                days_amount++;
            }
            month_begin++;
        }

        /* adds days from jan 1st the end year until the end date */
        days_amount += day_end;
        int tmp_month = 1;
        while (tmp_month < month_end){
            days_amount += days_in_month[tmp_month-1];
            if (IsLeap(year_end) && tmp_month == 2){
                days_amount++;
            }
            tmp_month++;
        }
    } else {
        /* if dates are in the same month */
        if (month_begin == month_end){
            days_amount = day_end - day_begin;
        } else {
            /* if dates are in the same year but the same month */
            days_amount += days_in_month[month_begin-1] - day_begin;
            month_begin++;
            while (month_begin < month_end){
                days_amount += days_in_month[month_begin-1];
                if (IsLeap(year_end) && month_begin == 2){
                    days_amount++;
                }
                month_begin++;
            }
            days_amount += day_end;
        }
    }
    return days_amount;
}

bool CheckDate(const CDate &date) {

    int year = date.GetYear();
    int day = date.GetDay();
    int month = date.GetMonth();

    int days_in_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (year <= 0 || month < 1 || month > 12) {
        return false;
    }

    if ( day < 1 ){
        return false;
    }

    if (IsLeap(year) && month == 2){
        if ( day > days_in_month[month-1]+1) {
            return false;
        }
    } else {
        if ( day > days_in_month[month-1]) {
            return false;
        }
    }

    return true;
}

bool CheckTime(const CTime &time) {
    int minute = time.GetMinute();
    int hour = time.GetHour();

    if (hour < 0 || hour > 23) {
        return false;
    }

    if (minute < 0 || minute > 59){
        return false;
    }

    return true;
}


void Separate() {
    cout << endl;
    cout << "====================================================================================================================" << endl;
}

void IsInvalid(const string & text){
    Separate();
    cout << "Entered " << text <<" is invalid, please try again." << endl;
    cout << "====================================================================================================================" << endl;
}

void StrBack(){
    cout << "If you want to cancel this operation write \"Back\"" << endl;
}

bool Menu(){

    string input;

    cout<<"Write \"Menu\" to return to the main menu"<<endl;

    while (1){

        cin >> input;

        if (cin.eof()) {
            return false;
        }

        if (input == "Menu"){
            break;
        }
        Separate();
        cout << "Wrong input, please try again."<<endl;
        cout << "====================================================================================================================" << endl;

    }

    Separate();
    return true;


}

void Message(const string & text){
    cout<<endl;
    cout << "====================================================================================================================" << endl;
    cout << text << endl;
    cout << "====================================================================================================================" << endl;
}


