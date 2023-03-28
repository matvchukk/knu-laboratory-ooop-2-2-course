#include "modes.h"
#include "functions.h"
#include <cstring>

bool interactive(Functions functions) {
    bool flag = true;
    string subStr;
    string neededType;
    string updatedMessage;
    string newMessage;

    while (flag) {
        cout << "Choose your action\n"
            << "1 - create new message and add to vector\n"
            << "2 - save all vector to txt and bin files\n"
            << "3 - reading from txt to vector\n"
            << "4 - reading from bin to vector\n"
            << "5 - show vector\n"
            << "6 - show txt\n"
            << "7 - show bin\n"
            << "8 - generate N messages to files\n"
            << "9 - searching message between 2 dates\n"
            << "10 - searching message with type and loading\n"
            << "11 - searching some message with substring which is the start of the message\n"
            << "12 - clear txt and bin files\n"
            << "13 - clear the vector\n"
            << "14 - delete a message\n"
            << "15 - update a message\n"
            << "100 - exit\n";
        short action;
        cin >> action;
        switch (action) {
        case 1:
            cout << "Enter text of message\n";
            cin.ignore();
            getline(cin, newMessage, '\n');
            functions.createNewElemAndAddToVector(newMessage);
            break;
        case 2:
            functions.saveToFile();
            break;
        case 3:
            if (!functions.log.empty()) {
                cout << "Vector has " << functions.log.size() << " element\n"
                    << "Do you want to save them to files(1) or clear the vector(2)? Enter 1 or 2\n";
                int action2;
                cin >> action2;
                switch (action2) {
                case 1:
                    functions.saveToFile();
                    functions.readingFromTxt();
                    break;
                case 2:
                    functions.log.clear();
                    functions.readingFromTxt();
                }
            }
            else
                functions.readingFromTxt();
            break;
        case 4:
            if (!functions.log.empty()) {
                cout << "Vector has " << functions.log.size() << " element\n"
                    << "Do you want to save them to files(1) or clear the vector(2)? Enter 1 or 2\n";
                int action2;
                cin >> action2;
                switch (action2) {
                case 1:
                    functions.saveToFile();
                    functions.readingFromBin();
                    break;
                case 2:
                    functions.log.clear();
                    functions.readingFromBin();
                }
            }
            else
                functions.readingFromBin();
            break;
        case 5:
            functions.coutFromVector();
            break;
        case 6:
            Functions::coutFromTxt();
            break;
        case 7:
            Functions::coutFromBin();
            break;
        case 8:
            cout << "Enter count of messages\n";
            int countOfMessages;
            cin >> countOfMessages;
            functions.generateMessages(countOfMessages);
            break;
        case 9:
            cout << "Enter data before\n"
                << "Year Month Day Hour Minutes Sec\n";
            FullTime timeBefore;
            cin >> timeBefore.year >> timeBefore.month >> timeBefore.day
                >> timeBefore.hour >> timeBefore.minutes >> timeBefore.sec;
            cout << "Enter data after\n"
                << "Year Month Day Hour Minutes Sec\n";
            FullTime timeAfter;
            cin >> timeAfter.year >> timeAfter.month >> timeAfter.day
                >> timeAfter.hour >> timeAfter.minutes >> timeAfter.sec;
            Functions::searchingBetweenTime(timeBefore, timeAfter);
            break;
        case 10:
            cout << "Choose a type of message\n"
                << "debug, info, fatal, warning, error\n";
            cin >> neededType;
            cout << "Choose a loading of message\n";
            double neededLoading;
            cin >> neededLoading;
            Functions::searchingTypeAndLoading(neededType, neededLoading);
            break;
        case 11:
            cout << "Enter substring which is start of the message\n";
            cin >> subStr;
            Functions::searchingSubString(subStr);
            break;
        case 12:
            functions.clearFiles();
            cout << "Files were successfully cleared :)\n";
            break;
        case 13:
            functions.log.clear();
            break;
        case 14:
            functions.coutFromTxt();
            cout << "Enter id of the message which you want to delete\n";
            int idOfDeletedElement;
            cin >> idOfDeletedElement;
            functions.deleteOneMessage(idOfDeletedElement);
            break;
        case 15:
            functions.coutFromTxt();
            cout << "Enter id of the message which you want to update\n";
            int idOfUpdatedElement;
            cin >> idOfUpdatedElement;
            cout << "Enter new message\n";
            cin.ignore();
            getline(cin, newMessage, '\n');
            functions.updateOneMessage(idOfUpdatedElement, newMessage);
            break;
        case 100:
            flag = false;
            break;
        default: cout << "Choose correct number\n";
        }
        cout << "Do you want to continue working? y/n\n";
        char next;
        cin >> next;
        flag = next == 'y';
    }
    cout << "Do you want to choose a mode? y/n\n";
    char next;
    cin >> next;
    flag = next == 'y';
    return flag;
};

bool demonstration() {
    Functions func;
    func.clearFiles();
    Functions::defineId();

    cout << "DEMONSTRATION MODE HAS BEEN STARTED\n";
    cout << "Let's create new message\n";
    func.createNewElemAndAddToVector("We have created new mess");
    cout << "Let's see what we have done\n\n";
    func.coutFromVector();
    cout << "\nOkay, save to txt and bin files\n\n";
    func.saveToFile();
    cout << "Now, we have in txt:\n\n";
    Functions::coutFromTxt();
    cout << "\n...and in bin:\n\n";
    Functions::coutFromBin();
    cout << "\nIts too long, let's generate 10 messages quickly and add them to files\n";
    func.generateMessages(10);
    cout << "Now, we have in txt:\n\n";
    Functions::coutFromTxt();
    cout << "Let's delete a message. For example, 5th\n";
    func.deleteOneMessage(5);
    cout << "Now, we have in txt:\n\n";
    Functions::coutFromTxt();
    cout << "\nLet's update a message. For example, 7th and enter new message 'Smells like teen spirits'\n\n";
    func.updateOneMessage(7, "Smells like teen spirits");
    cout << "Now, we have in txt:\n\n";
    Functions::coutFromTxt();
    cout << "Last part of demo: searching\n";
    cout << "\n1) searchingSubString(Smells)\n\n";
    Functions::searchingSubString("Smells");
    cout << "\n2) searchingTypeAndLoading(warning, 0.1);\n\n";
    Functions::searchingTypeAndLoading("warning", 0.1);
    FullTime timeBefore, timeAfter;
    timeBefore.year = func.log[0].timeCreated.year;
    timeBefore.month = func.log[0].timeCreated.month;
    timeBefore.day = func.log[0].timeCreated.day;
    timeBefore.hour = func.log[0].timeCreated.hour;
    timeBefore.minutes = func.log[0].timeCreated.minutes;
    timeBefore.sec = max(func.log[0].timeCreated.sec - 5, 0);
    timeAfter.year = func.log[0].timeCreated.year;
    timeAfter.month = func.log[0].timeCreated.month;
    timeAfter.day = func.log[0].timeCreated.day;
    timeAfter.hour = func.log[0].timeCreated.hour;
    timeAfter.minutes = func.log[0].timeCreated.minutes;
    timeAfter.sec = min(func.log[0].timeCreated.sec + 5, 59);
    cout << "\n3) searchingBetweenTime(" << timeBefore.year << "." << timeBefore.month << "." << timeBefore.day << " "
        << timeBefore.hour << ":" << timeBefore.minutes << ":" << timeBefore.sec << ", ";
    cout << timeAfter.year << "." << timeAfter.month << "." << timeAfter.day << " "
        << timeAfter.hour << ":" << timeAfter.minutes << ":" << timeAfter.sec << ")\n\n";
    Functions::searchingBetweenTime(timeBefore, timeAfter);

    cout << "\nTHE END OF DEMO MOD\n";
    cout << "Do you want to choose a mode? y/n\n";
    bool flag = true;
    char next;
    cin >> next;
    flag = next == 'y';
    return flag;
}

bool benchmark() {
    bool flag = true;
    Functions func;
    int countMessages = 10;
    double allTime = 0;

    benchData data{ 0,0,0,0 };
    while (allTime < 10) {
        func.clearFiles();
        MessageLog::count = 0;
        cout << endl << "Count of messages " << countMessages << endl;
        data = func.forBenchmark(countMessages);
        allTime = data.timeGeneratingAndSaving + data.timeReading + data.timeSearching;
        cout << "timeGeneratingAndSaving = " << data.timeGeneratingAndSaving << endl;
        cout << "timeReading = " << data.timeReading << endl;
        cout << "timeSearching = " << data.timeSearching << endl;
        cout << "All time = " << allTime << endl;
        cout << "Memory = " << data.memoryOfData << "MB " << endl << endl;
        if (allTime > 1)
            countMessages += countMessages;
        else
            countMessages *= 10;
    }
    cout << "Do you want to choose a mode? y/n\n";
    char next;
    cin >> next;
    flag = next == 'y';
    return flag;
}