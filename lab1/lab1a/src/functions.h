#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

class MessageLog;
class Message;
/// Struct for returnable value for function for benchmarkmode
///
/// @see MessageLog::forBenchmark(int)
struct benchData {
    double timeGeneratingAndSaving;
    double timeReading;
    double timeSearching;
    double memoryOfData;
};
/// Class for time
///
/// Class is describing time and has function to work with time. Used in class Message
class FullTime {
public:
    short year;
    short month;
    short day;
    short hour;
    short minutes;
    short sec;

    /// Function compares two times
    ///
    /// @param secondTime A second param for comparing. First is this*
    /// @return If this* is more than secondTime or equale to it, return true, otherwise return false
    bool moreThen(FullTime secondTime) const;
    /// Function set current time to the object
    ///
    /// \param delta a count of second that will be added to current time
    void setCurrentTime(int delta = 0);
};


/// Class describes message
///
/// Used in MessageLog
class Message {
    int id;
    int countWords;
    string text;
    FullTime timeCreated;
    string typeOfError;
    int priority;
    double loading;
    bool savedInFiles;

public:
    /// return id of message
    int getId() {
        return id;
    }
    /// return countWords of message
    int getCountWords() {
        return countWords;
    }
    /// return text of message
    string getText() {
        return text;
    }

    /// set type of error of message
    void setTypeOfError(string type) {
        typeOfError = type;
    }
    /// set loading of message
    void setLoading(double _loading) {
        loading = _loading;
    }

    /// Function counts words in message
    ///
    /// Counts a count of words between which there are spaces. Function could be called from any object
    /// \note could be static may be
    /// \param s string in which should count words
    /// \return count of words
    int toCountWords(const string& s);
    /// Out all attributes
    void outElem();

    friend MessageLog;
};


/// Main class, which contains message
///
/// Each message have unique id
/// ### Example
/// ~~~~~~~~~~~~~~~~~~~~~~~.cpp
/// MessageLog log("data");
/// ~~~~~~~~~~~~~~~~~~~~~~~
/// \note There are two vectors: log and temp. Log is the main vector which contains messages which is created by user.
/// \note Temp is used only in some functions.
class MessageLog {

    int currentFreeId;
    vector<Message> log;
    vector<Message> temp;
    string fileName;
    string arrOfErrors[5] = {
            "debug",
            "info",
            "fatal",
            "warning",
            "error"
    };

public:
    /// Constructor
    ///
    /// Defines id if these files already were used and contains some messages.
    /// \param fileName is the path to files (filename.txt and filename.bin) in which will be saved all messages
    explicit MessageLog(const string& fileName);

    /// Get message by reference
    /// \param id of needed message
    /// \return Return message by reference
    Message& get(int id) {
        return log[id];
    }
    /// Get current free Id
    /// \return current max free id
    int get() {
        return currentFreeId;
    }
    /// Defines id parsed files
    ///
    /// Read file till the end and set currentFreeId by max id
    void defineId();
    /// Check empty log
    ///
    /// \return If log is empty returns true, otherwise, return false
    bool emptyVector();
    /// Clear log
    void clearVector();
    /// Return size of log
    ///
    /// \return log.size()
    int countMessagesInTheVector();
    //Додавання елементів
    /// Create message and push it to log
    ///
    /// Message will be saved to RAM, but must be called saveToFile() if you want to save it after program will be shut down
    /// \param message string which will be set to message
    void createNewElemAndAddToVector(const string& message);
    //Зберігання даних (запис даних у файл)
    /// Saves all log or temp to files
    ///
    /// \param fromTemp default param. If it set true, then saving will be from vector temp. Used in searchBetweenTime() etc.
    /// \warning Log will not be clear. But you can't save messages with same id to file
    void saveToFile(bool fromTemp = false);
    //Відновлення даних (зчитування даних з файлу);
    /// Reads messages from fileName.txt
    ///
    /// \param inTemp if set true, messages will be saved to temp, otherwise, to log.
    /// \warning Messages saved in vector could have same id. Be care
    void readFromTxt(bool inTemp = false);
    /// Reads messages from fileName.bin
    ///
    /// \param inTemp if set true, messages will be saved to temp, otherwise, to log.
    /// \warning see readFromTxt()
    void readFromBin(bool inTemp = false);
    //Вивід всіх збережених даних;
    /// Out all messages from fileName.txt
    void outFromTxt() const;
    /// Out all messages from fileName.bin
    void outFromBin() const;
    /// Out all messages from log
    void outFromVector() const;
    //Пошук за заданими критеріями (див. підваріанти a-c );
    /// Search messages **in file** which times is between two given
    ///
    /// Used temp vector. Temp vector will be cleared after searching.
    /// \param timeBefore bottom border of searching
    /// \param timeAfter top border of searching
    /// \return vector<Message> which satisfy the condition
    vector<Message> searchBetweenTime(FullTime timeBefore, FullTime timeAfter);
    /// Search messages **in file** which with needed type and loading which is more then given
    ///
    /// See searchBetweenTime()
    /// \param neededType type of error
    /// \param neededLoading double value between 0 and 1
    /// \return vector<Message> which satisfy the condition
    vector<Message> searchTypeAndLoading(string neededType, double neededLoading);
    /// Search messages **in file** which which text contains given substring
    ///
    /// If inVector set to false, see searchBetweenTime(), otherwise, searching will be in log. Use temp
    /// \param subStr given substring
    /// \param inVector if set true, searching will be in log
    /// \return vector<Message> which satisfy the condition
    vector<Message> searchSubString(const string& subStr, bool inVector = false);
    //Видалення елементів (додаткові бали)
    /// Delete a message with given id
    ///
    /// Delete in **log and in files**
    /// \param id of deleted message
    void deleteOneMessage(int id);
    //Модифікація елементів (додаткові бали)
    /// Update a message with given id
    ///
    /// Update message **in files and in log**. Also change the time of message to current time. Use temp
    /// \param id of updated message
    /// \param newMessage will be set instead old text message
    void updateOneMessage(int id, const string& newMessage);
    //Допоміжні
    /// Generate some message to **files**
    ///
    /// Use temp vector.
    /// \param count of generated messages
    void generateMessagesToFile(int count);
    /// Check if the subString is the sub string of main
    ///
    /// \param main text
    /// \param subString searched sub string
    /// \return true, if subString is the sub string of main,otherwise, false
    bool subString(string main, string subString);
    /// Clear all files (fileName.txt and fileName.bin)
    ///
    /// \note log willnot be cleared
    void clearFiles();
    /// Function for benchmark mode
    ///
    /// Generates N messages, saves them to files, reads from files and searching some element
    /// \param N count of messages
    /// \return time (sec) for each operation and memory (MB) spent for messages
    benchData forBenchmark(int N);//generate N message, save to files,
                                //reading from files and searching random element
};
