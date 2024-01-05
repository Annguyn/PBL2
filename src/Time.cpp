#include "Time.h"
#include <iomanip>
#include <sstream>
#include <cstring>
#include <stdexcept>

Time::Time() : day(0), month(0), year(0), hour(0), minute(0) {
    // updateRealTime();
}

Time::Time(int day, int month, int year, int hour, int minute) {
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59 || month < 1 || month > 12 || day < 1 || day > 31) {
        throw std::invalid_argument("Invalid date, hour, or minute value");
    }
    updateRealTime();
    this -> day = day ;
    this -> month = month ;
    this -> year = year ;
    this -> hour = hour ;
    this -> minute = minute ; 
}

Time::Time(int day, int month, int year) : day(day), month(month), year(year), hour(0), minute(0) {
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        throw std::invalid_argument("Invalid date value");
    }
    updateRealTime();
    this -> day = day ;
    this -> month = month ;
    this -> year = year ;
}

Time::Time(int hour, int minute) : day(0), month(0), year(0), hour(hour), minute(minute) {
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        throw std::invalid_argument("Invalid hour or minute value");
    }
    updateRealTime();
    this -> hour = hour ;
    this -> minute = minute ; 
}

int Time::getDay() const {
    return day;
}

void Time::setDay(int newDay) {
    if (newDay < 1 || newDay > 31) {
        throw std::invalid_argument("Invalid day value");
    }
    day = newDay;
}

int Time::getMonth() const {
    return month;
}

void Time::setMonth(int newMonth) {
    if (newMonth < 1 || newMonth > 12) {
        throw std::invalid_argument("Invalid month value");
    }
    month = newMonth;
}

int Time::getYear() const {
    return year;
}

void Time::setYear(int newYear) {
    if (newYear < 0) {
        throw std::invalid_argument("Invalid year value");
    }
    year = newYear;
}

int Time::getHour() const {
    return hour;
}

void Time::setHour(int newHour) {
    if (newHour < 0 || newHour > 23) {
        throw std::invalid_argument("Invalid hour value");
    }
    hour = newHour;
}

int Time::getMinute() const {
    return minute;
}

void Time::setMinute(int newMinute) {
    if (newMinute < 0 || newMinute > 59) {
        throw std::invalid_argument("Invalid minute value");
    }
    minute = newMinute;
}

char* Time::getFormattedTime() const {
    char* formattedTime = new char[6];
    std::snprintf(formattedTime, 6, "%02d:%02d", hour, minute);
    return formattedTime;
}
  int Time::operator-(const Time& other) const {
        // Giả sử ngày, tháng, năm là các trường kiểu int
        int days = day + month * 30 + year * 365;
        int otherDays = other.day + other.month * 30 + other.year * 365;

        return days - otherDays;
    }

void Time::updateRealTime() {
    realTime = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(realTime);
    auto timeStruct = std::localtime(&timeT);
    year = timeStruct->tm_year + 1900;
    month = timeStruct->tm_mon + 1;
    day = timeStruct->tm_mday;
    hour = timeStruct->tm_hour;
    minute = timeStruct->tm_min;
}

char* Time::getRealTime() const {
    auto currentTime = std::chrono::system_clock::to_time_t(realTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&currentTime), "%Y-%m-%d %H:%M:%S");
    std::string timeStr = ss.str();
    char* realTimeStr = new char[timeStr.length() + 1];
    std::strcpy(realTimeStr, timeStr.c_str());
    return realTimeStr;
}

std::ostream& operator<<(std::ostream& os, const Time& timeObj) {
    os << std::setw(2) << std::setfill('0') << timeObj.day << "/"
       << std::setw(2) << std::setfill('0') << timeObj.month << "/"
       << std::setw(4) << std::setfill('0') << timeObj.year << " "
       << std::setw(2) << std::setfill('0') << timeObj.hour << ":"
       << std::setw(2) << std::setfill('0') << timeObj.minute
       << std::setfill(' ');
    return os;
}

std::istream& operator>>(std::istream& is, Time& timeObj) {
    char dash, colon;
    // timeObj.updateRealTime();
    is >> timeObj.day >> dash 
        >> timeObj.month >> dash 
        >> timeObj.year
       >> timeObj.hour >> colon >>
        timeObj.minute;


    // if (!is || dash != '-' || colon != ':') {
    //     is.setstate(std::ios::failbit);
    // }
    
    
    return is;
}

bool Time::operator==(const Time& other) const {
    return (year == other.year) && (month == other.month) && (day == other.day) &&
           (hour == other.hour) && (minute == other.minute);
}

bool Time::operator>=(const Time& other) const {
    if (year > other.year) {
        return true;
    } else if (year == other.year) {
        if (month > other.month) {
            return true;
        } else if (month == other.month) {
            if (day > other.day) {
                return true;
            } else if (day == other.day) {
                return (hour > other.hour) || ((hour == other.hour) && (minute >= other.minute));
            }
        }
    }
    return false;
}

bool Time::operator<=(const Time& other) const {
    if (year < other.year) {
        return true;
    } else if (year == other.year) {
        if (month < other.month) {
            return true;
        } else if (month == other.month) {
            if (day < other.day) {
                return true;
            } else if (day == other.day) {
                return (hour < other.hour) || ((hour == other.hour) && (minute <= other.minute));
            }
        }
    }
    return false;
}
bool Time::operator>(const Time& other) const {
    if (year > other.year) {
        return true;
    } else if (year == other.year) {
        if (month > other.month) {
            return true;
        } else if (month == other.month) {
            if (day > other.day) {
                return true;
            } else if (day == other.day) {
                return (hour > other.hour) || ((hour == other.hour) && (minute >= other.minute));
            }
        }
    }
    return false;
}

bool Time::operator<(const Time& other) const {
    if (year < other.year) {
        return true;
    } else if (year == other.year) {
        if (month < other.month) {
            return true;
        } else if (month == other.month) {
            if (day < other.day) {
                return true;
            } else if (day == other.day) {
                return (hour < other.hour) || ((hour == other.hour) && (minute <= other.minute));
            }
        }
    }
    return false;
}
