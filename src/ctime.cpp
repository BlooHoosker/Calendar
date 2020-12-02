//
// Created by marti on 22.05.2019.
//

#include "ctime.h"

CTime::CTime(int hour, int minute) {
    this->hour = hour;
    this->minute = minute;
}

CTime::CTime() {}

int CTime::GetHour() const {
    return hour;
}

int CTime::GetMinute() const {
    return minute;
}

std::ostream &operator<<(std::ostream &os, const CTime &time) {
    if(time.GetMinute() < 10){
        os << time.GetHour() << ":" << time.GetMinute() << "0";
    } else {
        os << time.GetHour() << ":" << time.GetMinute();
    }

    return os;
}

bool operator<(CTime &time1, CTime &time2) {

    if (time1.GetHour() < time2.GetHour()){
        return true;
    } else if (time1.GetHour() == time2.GetMinute()){
        if (time1.GetMinute() < time2.GetMinute()){
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }

}
