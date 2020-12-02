//
// Created by marti on 22.05.2019.
//

#include "cdate.h"
#include "mylib.h"

CDate::CDate(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

bool operator == (const CDate & date1, const CDate & date2) {
    if (date1.GetDay() == date2.GetDay() && date1.GetMonth() == date2.GetMonth() && date1.GetYear() == date2.GetYear()){
        return true;
    } else {
        return false;
    }
}

std::ostream &operator<<(std::ostream &os, const CDate &date) {
    os << date.GetDay() << "." << date.GetMonth() << "." << date.GetYear();
    return os;
}

bool operator<(const CDate &date1, const CDate &date2) {
    if (date1 == date2){
        return false;
    }

    if(date1.GetYear() < date2.GetYear()){
        return true;
    } else if (date1.GetYear() > date2.GetYear()){
        return false;
    } else {
        if (date1.GetMonth() < date2.GetMonth()){
            return true;
        } else if (date1.GetMonth() > date2.GetMonth()){
            return false;
        } else {
            if (date1.GetDay() < date2.GetDay()){
                return true;
            } else if (date1.GetDay() > date2.GetDay()){
                return false;
            }
        }
    }
    return true;
}

bool operator>(const CDate &date2, const CDate &date1) {
    if (date1 == date2){
        return false;
    }

    if(date1.GetYear() < date2.GetYear()){
        return true;
    } else if (date1.GetYear() > date2.GetYear()){
        return false;
    } else {
        if (date1.GetMonth() < date2.GetMonth()){
            return true;
        } else if (date1.GetMonth() > date2.GetMonth()){
            return false;
        } else {
            if (date1.GetDay() < date2.GetDay()){
                return true;
            } else if (date1.GetDay() > date2.GetDay()){
                return false;
            }
        }
    }
    return true;
}


int CDate::GetDay() const {
    return day;
}

int CDate::GetMonth() const {
    return month;
}

int CDate::GetYear() const {
    return year;
}

CDate::CDate() {}

CDate &CDate::operator++(int) {

    int days_in_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (IsLeap(year)){
        days_in_month[1]++;
    }

    if (day == days_in_month[month-1]){
        day = 1;
        if (month == 12) {
            month = 1;
            year++;
        } else {
            month++;
        }
    } else {
        day++;
    }

    return *this;

}


