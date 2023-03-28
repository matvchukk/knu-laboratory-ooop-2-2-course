#ifndef LABOR1_MESSAGE_H
#define LABOR1_MESSAGE_H
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <map>

class FullTime {
public:
    short year;
    short month;
    short day;
    short hour;
    short minutes;
    short sec;

    bool moreThen(FullTime);
    void coutTime();
};

class MessageLog
{
public:
    static int count;

    int id;
    int countWords;
    std::string text;
    FullTime timeCreated;
    std::string typeOfError;
    int priority;
    double loading;
    bool savedInFiles;

    void coutElem();
    void saveToDisk();
};

#endif //LABOR1_MESSAGE_H