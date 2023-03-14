#define _CRT_SECURE_NO_WARNINGS
#include "Methods.h"
#include <fstream>
#include <iostream>

using namespace std;

void Functions::defineId() {
    ifstream file("data.txt");
    MessageLog mess;
    bool flag = true;
    if (file.peek() == EOF) {
        MessageLog::count = 0;
        return;
    }
    while (file >> mess.id >> mess.countWords && true) {
        mess.text = "";
        string s;
        MessageLog::count = max(MessageLog::count, mess.id + 1);
        for (int i = 0; i < mess.countWords; i++)
            file >> s;
        file >> mess.timeCreated.year >> mess.timeCreated.month
            >> mess.timeCreated.day >> mess.timeCreated.hour >> mess.timeCreated.minutes >> mess.timeCreated.sec
            >> mess.typeOfError >> mess.priority >> mess.loading;
    }
    file.close();
}
//Вывод
void Functions::coutFromVector() {
    for (auto i : log)
        i.coutElem();
}
void Functions::coutFromTxt() {
    ifstream file("data.txt");
    string s;
    while (getline(file, s))
        cout << s << endl;
    file.close();
}
void Functions::coutFromBin() {
    ifstream file("binary.txt", ios_base::binary);
    MessageLog mess;
    file.seekg(0, ios::end);
    int end_file = file.tellg();
    file.seekg(0, ios::beg);
    while (file.tellg() != end_file) {
        file.read((char*)&mess.id, sizeof(mess.id));
        file.read((char*)&mess.countWords, sizeof(mess.countWords));

        int lengthOfText;
        string temp = "1";
        file.read((char*)&lengthOfText, sizeof(lengthOfText));
        for (int i = 0; i < lengthOfText; i++) {
            file.get(temp[0]);
            mess.text += temp;
        }

        file.read((char*)&mess.timeCreated.year, sizeof(mess.timeCreated.year));
        file.read((char*)&mess.timeCreated.month, sizeof(mess.timeCreated.month));
        file.read((char*)&mess.timeCreated.day, sizeof(mess.timeCreated.day));
        file.read((char*)&mess.timeCreated.hour, sizeof(mess.timeCreated.hour));
        file.read((char*)&mess.timeCreated.minutes, sizeof(mess.timeCreated.minutes));
        file.read((char*)&mess.timeCreated.sec, sizeof(mess.timeCreated.sec)); //time

        int lengthTypeOfError;
        file.read((char*)&lengthTypeOfError, sizeof(lengthTypeOfError));
        for (int i = 0; i < lengthTypeOfError; i++) {
            file.get(temp[0]);
            mess.typeOfError += temp;
        }

        file.read((char*)&mess.priority, sizeof(mess.priority)); //priority

        file.read((char*)&mess.loading, sizeof(mess.loading)); //loading
        mess.coutElem();
        mess.text.clear();
        mess.typeOfError.clear();
    }
    file.close();
}
//Чтение
void Functions::readingFromTxt() {
    ifstream file("data.txt");
    MessageLog mess;
    while (file >> mess.id >> mess.countWords) {
        mess.text = "";
        string s;
        for (int i = 0; i < mess.countWords; i++) {
            file >> s;
            if (i == mess.countWords - 1)
                mess.text += s;
            else
                mess.text += s + " ";
        }
        file >> mess.timeCreated.year >> mess.timeCreated.month
            >> mess.timeCreated.day >> mess.timeCreated.hour >> mess.timeCreated.minutes >> mess.timeCreated.sec
            >> mess.typeOfError >> mess.priority >> mess.loading;
        mess.savedInFiles = true;

        log.push_back(mess);
    }
    file.close();
}
void Functions::readingFromBin() {
    ifstream file("binary.txt", ios_base::binary);
    MessageLog mess;
    file.seekg(0, ios::end);
    int end_file = file.tellg();
    file.seekg(0, ios::beg);
    while (file.tellg() != end_file) {
        file.read((char*)&mess.id, sizeof(mess.id));
        file.read((char*)&mess.countWords, sizeof(mess.countWords));

        int lengthOfText;
        string temp = "1";
        file.read((char*)&lengthOfText, sizeof(lengthOfText));
        for (int i = 0; i < lengthOfText; i++) {
            file.get(temp[0]);
            mess.text += temp;
        }

        file.read((char*)&mess.timeCreated.year, sizeof(mess.timeCreated.year));
        file.read((char*)&mess.timeCreated.month, sizeof(mess.timeCreated.month));
        file.read((char*)&mess.timeCreated.day, sizeof(mess.timeCreated.day));
        file.read((char*)&mess.timeCreated.hour, sizeof(mess.timeCreated.hour));
        file.read((char*)&mess.timeCreated.minutes, sizeof(mess.timeCreated.minutes));
        file.read((char*)&mess.timeCreated.sec, sizeof(mess.timeCreated.sec)); //time

        int lengthTypeOfError;
        file.read((char*)&lengthTypeOfError, sizeof(lengthTypeOfError));
        for (int i = 0; i < lengthTypeOfError; i++) {
            file.get(temp[0]);
            mess.typeOfError += temp;
        }

        file.read((char*)&mess.priority, sizeof(mess.priority)); //priority

        file.read((char*)&mess.loading, sizeof(mess.loading)); //loading
        mess.savedInFiles = true;
        log.push_back(mess);

        mess.text.clear();
        mess.typeOfError.clear();
    }
    file.close();
};
//Создание
void Functions::createNewElemAndAddToVector(string message) {
    MessageLog mess;
    Functions function;

    mess.id = MessageLog::count;
    MessageLog::count++;

    mess.text = message;
    mess.countWords = function.countWords(mess.text);

    time_t seconds = time(nullptr);

    tm* timeinfo = localtime(&seconds);
    char* t_tim = asctime(timeinfo);
    string m_month = "123";
    m_month[0] = t_tim[4];
    m_month[1] = t_tim[5];
    m_month[2] = t_tim[6];
    string month[12] = {
            "Jan", "Feb", "Mar", "Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
    };
    bool flag = true;
    for (mess.timeCreated.month = 0; mess.timeCreated.month < 12 && flag; mess.timeCreated.month++)
        if (month[mess.timeCreated.month] == m_month)
            flag = false;
    mess.timeCreated.day = (t_tim[8] - '0') * 10 + t_tim[9] - '0';
    mess.timeCreated.hour = (t_tim[11] - '0') * 10 + t_tim[12] - '0';
    mess.timeCreated.minutes = (t_tim[14] - '0') * 10 + t_tim[15] - '0';
    mess.timeCreated.sec = (t_tim[17] - '0') * 10 + t_tim[18] - '0';
    mess.timeCreated.year = (t_tim[20] - '0') * 1000 + (t_tim[21] - '0') * 100 + (t_tim[22] - '0') * 10 + t_tim[23] - '0';


    mess.typeOfError = arrOfErrors[rand() % 5];

    mess.priority = rand() % 200;

    mess.loading = rand();
    mess.loading = mess.loading / (mess.loading + rand());

    mess.savedInFiles = false;

    Functions::log.push_back(mess);
}
//Сохранение
void Functions::saveToFile() {
    ofstream file("data.txt", ios_base::app);
    ofstream bin("binary.txt", ios_base::binary | ios_base::app);
    if (!file) {
        cout << "txt is closed \n";
        return;
    }
    if (!bin) {
        cout << "bin is closed \n";
        return;
    }
    for (auto& i : log) {
        if (i.savedInFiles) {
            cout << "Element with id " << i.id << " is already saved. Skipped.\n";
            continue;
        }
        i.savedInFiles = true;

        file << i.id << ' ' << i.countWords << ' ' << i.text << ' ' << i.timeCreated.year << ' ' << i.timeCreated.month
            << ' ' << i.timeCreated.day << ' ' << i.timeCreated.hour << ' ' << i.timeCreated.minutes << ' ' << i.timeCreated.sec
            << ' ' << i.typeOfError << ' ' << i.priority << ' ' << i.loading << '\n';

        bin.write((char*)&i.id, sizeof(i.id)); //id

        int lengthText = i.text.size();
        bin.write((char*)&i.countWords, sizeof(i.countWords));
        bin.write((char*)&lengthText, sizeof(lengthText));
        bin << i.text; //text

        bin.write((char*)&i.timeCreated.year, sizeof(i.timeCreated.year));
        bin.write((char*)&i.timeCreated.month, sizeof(i.timeCreated.month));
        bin.write((char*)&i.timeCreated.day, sizeof(i.timeCreated.day));
        bin.write((char*)&i.timeCreated.hour, sizeof(i.timeCreated.hour));
        bin.write((char*)&i.timeCreated.minutes, sizeof(i.timeCreated.minutes));
        bin.write((char*)&i.timeCreated.sec, sizeof(i.timeCreated.sec)); //time

        int lengthTypeOfError = i.typeOfError.size();
        bin.write((char*)&lengthTypeOfError, sizeof(lengthTypeOfError));
        bin << i.typeOfError; //typeOfError

        bin.write((char*)&i.priority, sizeof(i.priority)); //priority

        bin.write((char*)&i.loading, sizeof(i.loading)); //loading
    }
    file.close();
    bin.close();
}
//Поиск по критериям
void Functions::searchingBetweenTime(FullTime timeBefore, FullTime timeAfter) {
    Functions funct;
    funct.readingFromTxt();
    for (auto i : funct.log) {
        if (i.timeCreated.moreThen(timeBefore) && timeAfter.moreThen(i.timeCreated)) {
            /*cout << "Time before: ";
            timeBefore.coutTime();
            cout << "Item time:";
            i.timeCreated.coutTime();
            cout << "Time after: ";
            timeAfter.coutTime();*/
            i.coutElem();
        }
    }
}
void Functions::searchingTypeAndLoading(string neededType, double neededLoading) {
    Functions funct;
    funct.readingFromTxt();
    for (auto i : funct.log) {
        if (i.typeOfError == neededType && i.loading >= neededLoading)
            i.coutElem();
    }
}
void Functions::searchingSubString(string subStr) {
    Functions funct;
    funct.readingFromTxt();
    for (auto i : funct.log) {
        if (subString(i.text, subStr))
            i.coutElem();
    }
}
void Functions::benchSearchingWithSubstr(string subStr) {
    for (auto i : log) {
        if (subString(i.text, subStr))
            cout << "Element has found: " << endl, i.coutElem();
    }
}
//Удаление
void Functions::deleteOneMessage(int id) {
    Functions func;
    func.readingFromTxt();
    for (int i = 0; i < func.log.size(); i++)
        if (func.log[i].id == id) {
            func.log.erase(func.log.begin() + i);
        }
    for (int i = 0; i < log.size(); i++)
        if (log[i].id == id) {
            log.erase(log.begin() + i);
        }
    func.clearFiles();
    func.saveToFile();
    defineId();
}
//Обновление
void Functions::updateOneMessage(int id, string newMessage) {
    Functions func;
    func.readingFromTxt();
    for (auto& i : func.log)
        if (i.id == id) {

            i.text = newMessage;
            i.countWords = countWords(i.text);

            time_t seconds = time(nullptr);
            tm* timeinfo = localtime(&seconds);
            char* t_tim = asctime(timeinfo);
            string m_month = "123";
            m_month[0] = t_tim[4];
            m_month[1] = t_tim[5];
            m_month[2] = t_tim[6];
            string month[12] = {
                    "Jan", "Feb", "Mar", "Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
            };
            bool flag = true;
            for (i.timeCreated.month = 0; i.timeCreated.month < 12 && flag; i.timeCreated.month++)
                if (month[i.timeCreated.month] == m_month)
                    flag = false;
            i.timeCreated.day = (t_tim[8] - '0') * 10 + t_tim[9] - '0';
            i.timeCreated.hour = (t_tim[11] - '0') * 10 + t_tim[12] - '0';
            i.timeCreated.minutes = (t_tim[14] - '0') * 10 + t_tim[15] - '0';
            i.timeCreated.sec = (t_tim[17] - '0') * 10 + t_tim[18] - '0';
            i.timeCreated.year = (t_tim[20] - '0') * 1000 + (t_tim[21] - '0') * 100 + (t_tim[22] - '0') * 10 + t_tim[23] - '0';
        }
    for (auto& i : log)
        if (i.id == id) {

            i.text = newMessage;
            i.countWords = countWords(i.text);

            time_t seconds = time(nullptr);
            tm* timeinfo = localtime(&seconds);
            char* t_tim = asctime(timeinfo);
            string m_month = "123";
            m_month[0] = t_tim[4];
            m_month[1] = t_tim[5];
            m_month[2] = t_tim[6];
            string month[12] = {
                    "Jan", "Feb", "Mar", "Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
            };
            bool flag = true;
            for (i.timeCreated.month = 0; i.timeCreated.month < 12 && flag; i.timeCreated.month++)
                if (month[i.timeCreated.month] == m_month)
                    flag = false;
            i.timeCreated.day = (t_tim[8] - '0') * 10 + t_tim[9] - '0';
            i.timeCreated.hour = (t_tim[11] - '0') * 10 + t_tim[12] - '0';
            i.timeCreated.minutes = (t_tim[14] - '0') * 10 + t_tim[15] - '0';
            i.timeCreated.sec = (t_tim[17] - '0') * 10 + t_tim[18] - '0';
            i.timeCreated.year = (t_tim[20] - '0') * 1000 + (t_tim[21] - '0') * 100 + (t_tim[22] - '0') * 10 + t_tim[23] - '0';
        }
    func.clearFiles();
    func.saveToFile();
    defineId();
}
//Вспомогательные
int Functions::countWords(string s) {
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
void Functions::generateMessages(int n) {
    Functions function;
    for (int i = 0; i < n; i++) {
        MessageLog mess;

        mess.id = MessageLog::count;
        MessageLog::count++;

        int randCountSymblos = rand() % 16 + 3;
        string temp = "1";
        for (int j = 0; j < randCountSymblos; j++) {
            temp[0] = rand() % 30 + 92;
            mess.text += temp;
        }

        mess.countWords = function.countWords(mess.text);

        time_t seconds = time(nullptr);
        tm* timeinfo = localtime(&seconds);
        char* t_tim = asctime(timeinfo);
        string m_month = "123";
        m_month[0] = t_tim[4];
        m_month[1] = t_tim[5];
        m_month[2] = t_tim[6];
        string month[12] = {
                "Jan", "Feb", "Mar", "Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
        };
        bool flag = true;
        for (mess.timeCreated.month = 0; mess.timeCreated.month < 12 && flag; mess.timeCreated.month++)
            if (month[mess.timeCreated.month] == m_month)
                flag = false;
        mess.timeCreated.day = (t_tim[8] - '0') * 10 + t_tim[9] - '0';
        mess.timeCreated.hour = (t_tim[11] - '0') * 10 + t_tim[12] - '0';
        mess.timeCreated.minutes = (t_tim[14] - '0') * 10 + t_tim[15] - '0';
        mess.timeCreated.sec = (t_tim[17] - '0') * 10 + t_tim[18] - '0';
        mess.timeCreated.year = (t_tim[20] - '0') * 1000 + (t_tim[21] - '0') * 100 + (t_tim[22] - '0') * 10 + t_tim[23] - '0';


        mess.typeOfError = arrOfErrors[rand() % 5];

        mess.priority = (MessageLog::count * rand()) % 200;

        mess.loading = rand();
        mess.loading = mess.loading / (mess.loading + MessageLog::count * rand());
        mess.savedInFiles = false;

        function.log.push_back(mess);
    }
    function.saveToFile();
}

bool Functions::subString(string main, string substring) {
    for (int i = 0; i < substring.size(); i++)
        if (main[i] != substring[i])
            return false;
    return true;
}
void Functions::clearFiles() {
    ofstream fileTxt("data.txt", ios::out);
    fileTxt.close();
    ofstream fileBin("binary.txt", ios::out);
    fileBin.close();
    for (auto& i : log) {
        i.savedInFiles = false;
        MessageLog::count = max(MessageLog::count, i.id);
    }
}
benchData Functions::forBenchmark(int N) {
    MessageLog::count = 0;

    double timeGeneratingAndSavingStart = clock();
    generateMessages(N);
    double timeGeneratingAndSavingEnd = clock();
    double timeGeneratingAndSaving = (timeGeneratingAndSavingEnd - timeGeneratingAndSavingStart) / CLOCKS_PER_SEC;

    double timeReadingMessStart = clock();
    readingFromTxt();
    double timeReadingMessEnd = clock();
    double timeReading = (timeReadingMessEnd - timeReadingMessStart) / CLOCKS_PER_SEC;
    cout << "log " << log.size() << endl;
    double timeSearchingMessStart = clock();
    benchSearchingWithSubstr("abcd");
    double timeSearchingMessEnd = clock();
    double timeSearching = (timeSearchingMessEnd - timeSearchingMessStart) / CLOCKS_PER_SEC;

    benchData data{};
    data.timeGeneratingAndSaving = timeGeneratingAndSaving;
    data.timeReading = timeReading;
    data.timeSearching = timeSearching;
    fstream file("data.txt");
    double size = 0;
    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.close();
    data.memoryOfData = size / 1024 / 1024;

    return data;

}