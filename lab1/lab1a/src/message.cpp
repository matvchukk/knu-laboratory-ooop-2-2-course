#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"

using namespace std;


int Message::toCountWords(const string& s) {
    if (s.size() == 0)
        return 0;
    int count = 0;
    for (int i = 0; i < s.size() - 1; i++)
        if (s[i] == ' ' && s[i + 1] != ' ')
            count++;
    if (s[s.size()] != ' ')
        count++;
    if (s[0] == ' ')
        count--;

    return count;
}

void Message::outElem() {
    cout << this->id << ' ' << this->countWords << ' ' << this->text << "\t\t" << this->timeCreated.year << ' ' << this->timeCreated.month
        << ' ' << this->timeCreated.day << ' ' << this->timeCreated.hour << ' ' << this->timeCreated.minutes << ' ' << this->timeCreated.sec
        << ' ' << this->typeOfError << ' ' << this->priority << ' ' << this->loading << ' ' << '\n';
}
void FullTime::setCurrentTime(int delta) {
    time_t seconds = time(nullptr) + delta;
    tm* timeInfo = localtime(&seconds);
    char* t_tim = asctime(timeInfo);
    string m_month = "123";
    m_month[0] = t_tim[4];
    m_month[1] = t_tim[5];
    m_month[2] = t_tim[6];
    string _month[12] = {
            "Jan", "Feb", "Mar", "Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
    };
    bool flag = true;
    for (month = 0; month < 12 && flag; month++)
        if (_month[month] == m_month)
            flag = false;
    day = (t_tim[8] - '0') * 10 + t_tim[9] - '0';
    hour = (t_tim[11] - '0') * 10 + t_tim[12] - '0';
    minutes = (t_tim[14] - '0') * 10 + t_tim[15] - '0';
    sec = (t_tim[17] - '0') * 10 + t_tim[18] - '0';
    year = (t_tim[20] - '0') * 1000 + (t_tim[21] - '0') * 100 + (t_tim[22] - '0') * 10 + t_tim[23] - '0';
}

bool FullTime::moreThen(FullTime secondTime) const {
    if (year == secondTime.year)
        ;
    else
        return year > secondTime.year;
    if (month == secondTime.month)
        ;
    else
        return month > secondTime.month;
    if (day == secondTime.day)
        ;
    else
        return day > secondTime.day;
    if (hour == secondTime.hour)
        ;
    else
        return hour > secondTime.hour;
    if (minutes == secondTime.minutes)
        ;
    else
        return minutes > secondTime.minutes;
    if (sec == secondTime.sec)
        ;
    else
        return sec > secondTime.sec;
    return true;
}