#include "message.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void MessageLog::coutElem() {
    cout << this->id << ' ' << this->countWords << ' ' << this->text << ' ' << this->timeCreated.year << ' ' << this->timeCreated.month
        << ' ' << this->timeCreated.day << ' ' << this->timeCreated.hour << ' ' << this->timeCreated.minutes << ' ' << this->timeCreated.sec
        << ' ' << this->typeOfError << ' ' << this->priority << ' ' << this->loading << ' ' << '\n';
}

void MessageLog::saveToDisk() {


    ofstream file("data.txt", ios_base::app);
    if (!file) {
        cout << "txt is closed \n";
        return;
    }

    file << this->id << ' ' << this->countWords << ' ' << this->text << ' ' << this->timeCreated.year << ' ' << this->timeCreated.month
        << ' ' << this->timeCreated.day << ' ' << this->timeCreated.hour << ' ' << this->timeCreated.minutes << ' ' << this->timeCreated.sec
        << ' ' << this->typeOfError << ' ' << this->priority << ' ' << this->loading << '\n';

    file.close();

    ofstream bin("binary.txt", ios_base::binary | ios_base::app);
    if (!bin) {
        cout << "bin is closed \n";
        return;
    }
    bin.write((char*)&this->id, sizeof(this->id)); //id

    int lengthText = this->text.size();
    bin.write((char*)&this->countWords, sizeof(this->countWords));
    bin.write((char*)&lengthText, sizeof(lengthText));
    bin << this->text; //text

    bin.write((char*)&this->timeCreated.year, sizeof(this->timeCreated.year));
    bin.write((char*)&this->timeCreated.month, sizeof(this->timeCreated.month));
    bin.write((char*)&this->timeCreated.day, sizeof(this->timeCreated.day));
    bin.write((char*)&this->timeCreated.hour, sizeof(this->timeCreated.hour));
    bin.write((char*)&this->timeCreated.minutes, sizeof(this->timeCreated.minutes));
    bin.write((char*)&this->timeCreated.sec, sizeof(this->timeCreated.sec)); //time

    int lengthTypeOfError = this->typeOfError.size();
    bin.write((char*)&lengthTypeOfError, sizeof(lengthTypeOfError));
    bin << this->typeOfError; //typeOfError

    bin.write((char*)&this->priority, sizeof(this->priority)); //priority

    bin.write((char*)&this->loading, sizeof(this->loading)); //loading

    bin.close();
}

bool FullTime::moreThen(FullTime secondTime) {
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

void FullTime::coutTime() {
    cout << year << ' ' << month << ' ' << day << ' ' << hour << ' ' << minutes << ' ' << sec << endl;
}