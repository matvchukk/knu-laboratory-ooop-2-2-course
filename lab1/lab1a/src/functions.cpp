#include "functions.h"

MessageLog::MessageLog(const std::string& newFileName) :
    fileName(newFileName), currentFreeId(0) {
    log.clear();
    defineId();
}
void MessageLog::defineId()
{
    ifstream file(fileName + ".txt");
    Message mess;
    while (file >> mess.id >> mess.countWords) {
        mess.text = "";
        currentFreeId = max(currentFreeId, mess.id + 1);
        getline(file >> ws, mess.text);
        file >> mess.timeCreated.year >> mess.timeCreated.month >> mess.timeCreated.day
            >> mess.timeCreated.hour >> mess.timeCreated.minutes >> mess.timeCreated.sec
            >> mess.typeOfError >> mess.priority >> mess.loading;
    }
    file.close();
}
bool MessageLog::emptyVector() {
    return log.empty();
}
void MessageLog::clearVector() {
    log.clear();
}
int MessageLog::countMessagesInTheVector() {
    return log.size();
}
void MessageLog::outFromVector() const {
    for (auto i : log)
        i.outElem();
}
void MessageLog::outFromTxt() const
{
    ifstream file(fileName + ".txt");
    string s;
    while (!file.eof()) {
        getline(file, s);
        cout << s << endl;
    }
    file.close();
}
void MessageLog::outFromBin() const {
    MessageLog tempLog(fileName);
    tempLog.readFromBin();
    tempLog.outFromVector();
}
void MessageLog::readFromTxt(bool inTemp)
{
    ifstream file(fileName + ".txt");
    Message mess;
    while (file >> mess.id >> mess.countWords) {
        mess.text = "";
        getline(file >> ws, mess.text);
        file >> mess.timeCreated.year >> mess.timeCreated.month >> mess.timeCreated.day
            >> mess.timeCreated.hour >> mess.timeCreated.minutes >> mess.timeCreated.sec
            >> mess.typeOfError >> mess.priority >> mess.loading;
        mess.savedInFiles = true;

        if (inTemp)
            temp.emplace_back(mess);
        else
            log.emplace_back(mess);
    }
    file.close();
}
void MessageLog::readFromBin(bool inTemp) {
    ifstream file(fileName + ".bin", ios_base::binary);
    Message mess;
    file.seekg(0, ios::end);
    int end_file = file.tellg();
    file.seekg(0, ios::beg);
    while (file.tellg() != end_file) {
        file.read((char*)&mess.id, sizeof(mess.id));
        file.read((char*)&mess.countWords, sizeof(mess.countWords));

        int lengthOfText;
        string tempString = "1";
        file.read((char*)&lengthOfText, sizeof(lengthOfText));
        for (int i = 0; i < lengthOfText; i++) {
            file.get(tempString[0]);
            mess.text += tempString;
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
            file.get(tempString[0]);
            mess.typeOfError += tempString;
        }

        file.read((char*)&mess.priority, sizeof(mess.priority)); //priority

        file.read((char*)&mess.loading, sizeof(mess.loading)); //loading
        mess.savedInFiles = true;


        if (inTemp)
            temp.push_back(mess);
        else
            log.push_back(mess);

        mess.text.clear();
        mess.typeOfError.clear();
    }
    file.close();
}
void MessageLog::createNewElemAndAddToVector(const string& message) {
    Message mess;
    mess.id = currentFreeId;
    currentFreeId++;
    mess.text = message;
    mess.countWords = mess.toCountWords(mess.text);
    mess.timeCreated.setCurrentTime();
    mess.typeOfError = arrOfErrors[rand() % 5];
    mess.priority = rand() % 200;
    mess.loading = (double)rand() / RAND_MAX;
    mess.savedInFiles = false;
    log.push_back(mess);
}
void MessageLog::saveToFile(bool fromTemp) {
    ofstream txt(fileName + ".txt", ios_base::app);
    ofstream bin(fileName + ".bin", ios_base::binary | ios_base::app);
    if (!txt) {
        cout << "txt is closed \n";
        return;
    }
    if (!bin) {
        cout << "bin is closed \n";
        return;
    }
    vector<Message> vec;
    if (fromTemp)
        vec = temp;
    else
        vec = log;
    for (auto& i : vec) {
        if (i.savedInFiles) {
            cout << "Element with id " << i.id << " is already saved. Skipped.\n";
            continue;
        }
        i.savedInFiles = true;

        txt << i.id << ' ' << i.countWords << ' ' << i.text << ' ' << i.timeCreated.year << ' ' << i.timeCreated.month
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
    txt.close();
    bin.close();
}
vector<Message> MessageLog::searchBetweenTime(FullTime timeBefore, FullTime timeAfter) {
    readFromTxt(true);
    vector<Message> result;
    for (auto i : temp) {
        if (i.timeCreated.moreThen(timeBefore) && timeAfter.moreThen(i.timeCreated)) {
            result.push_back(i);
        }
    }
    temp.clear();
    return result;
}
vector<Message> MessageLog::searchTypeAndLoading(string neededType, double neededLoading) {
    readFromTxt(true);
    vector<Message> result;
    for (auto i : temp) {
        if (i.typeOfError == neededType && i.loading >= neededLoading) {
            result.push_back(i);
        }
    }
    temp.clear();
    return result;
}
vector<Message> MessageLog::searchSubString(const string& subStr, bool inVector) {
    vector<Message> result;
    if (!inVector) {
        readFromTxt(true);

        for (const auto& i : temp) {
            if (subString(i.text, subStr)) {
                result.push_back(i);
            }
        }
        temp.clear();
    }
    else {
        for (const auto& i : log) {
            if (subString(i.text, subStr)) {
                result.push_back(i);
            }
        }
    }
    return result;
}
void MessageLog::deleteOneMessage(int id) {
    readFromTxt(true);
    for (int i = 0; i < temp.size(); i++)
        if (temp[i].id == id) {
            temp.erase(temp.begin() + i);
        }
    for (int i = 0; i < log.size(); i++)
        if (log[i].id == id) {
            log.erase(log.begin() + i);
        }
    clearFiles();
    saveToFile(true);
    temp.clear();
}
void MessageLog::updateOneMessage(int id, const string& newMessage) {
    readFromTxt(true);
    for (auto& i : temp)
        if (i.id == id) {

            i.text = newMessage;
            i.countWords = i.toCountWords(i.text);
            i.timeCreated.setCurrentTime();
        }

    for (auto& i : log)
        if (i.id == id) {

            i.text = newMessage;
            i.countWords = i.toCountWords(i.text);
            i.timeCreated.setCurrentTime();
        }
    clearFiles();
    saveToFile(true);
    temp.clear();
}
void MessageLog::generateMessagesToFile(int n) {
    for (int i = 0; i < n; i++) {
        Message mess;

        mess.id = currentFreeId;
        currentFreeId++;

        int randCountSymbols = rand() % 16 + 3;
        string newString = "1";
        for (int j = 0; j < randCountSymbols; j++) {
            newString[0] = rand() % 30 + 92;
            mess.text += newString;
        }
        mess.countWords = mess.toCountWords(mess.text);
        mess.timeCreated.setCurrentTime();
        mess.typeOfError = arrOfErrors[rand() % 5];
        mess.priority = (MessageLog::currentFreeId * rand()) % 200;
        mess.loading = (double)rand() / RAND_MAX;
        mess.savedInFiles = false;
        temp.push_back(mess);
    }
    saveToFile(true);
    temp.clear();
}
bool MessageLog::subString(string main, string subString) {
    for (int i = 0; i < subString.size(); i++)
        if (main[i] != subString[i])
            return false;
    return true;
}
void MessageLog::clearFiles() {
    ofstream fileTxt(fileName + ".txt", ios::out);
    fileTxt.close();
    ofstream fileBin(fileName + ".bin", ios::out);
    fileBin.close();
    for (auto& i : log) {
        i.savedInFiles = false;
        currentFreeId = max(currentFreeId, i.id);
    }
    for (auto& i : temp) {
        i.savedInFiles = false;
        currentFreeId = max(currentFreeId, i.id);
    }
}
benchData MessageLog::forBenchmark(int N) {
    currentFreeId = 0;
    double timeGeneratingAndSavingStart = clock();
    generateMessagesToFile(N);
    double timeGeneratingAndSavingEnd = clock();
    double timeGeneratingAndSaving = (timeGeneratingAndSavingEnd - timeGeneratingAndSavingStart) / CLOCKS_PER_SEC;
    double timeReadingMessStart = clock();
    readFromTxt();
    double timeReadingMessEnd = clock();
    double timeReading = (timeReadingMessEnd - timeReadingMessStart) / CLOCKS_PER_SEC;

    double timeSearchingMessStart = clock();
    for (auto i : searchSubString("abcd", true))
        i.outElem();
    double timeSearchingMessEnd = clock();
    double timeSearching = (timeSearchingMessEnd - timeSearchingMessStart) / CLOCKS_PER_SEC;

    benchData data{};
    data.timeGeneratingAndSaving = timeGeneratingAndSaving;
    data.timeReading = timeReading;
    data.timeSearching = timeSearching;
    fstream file(fileName + ".txt");
    double size;
    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.close();
    data.memoryOfData = size / 1024 / 1024;

    return data;

}