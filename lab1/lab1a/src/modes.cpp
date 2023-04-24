#include "modes.h"

FullTime getFullTime() {
    FullTime fullTime;
    cin >> fullTime.year >> fullTime.month >> fullTime.day
        >> fullTime.hour >> fullTime.minutes >> fullTime.sec;
    return fullTime;
}

void chooseAction(MessageLog& log) {
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
    case 1: {
        cout << "Enter text of message\n";
        cin.ignore();
        string newMessage;
        getline(cin, newMessage, '\n');
        log.createNewElemAndAddToVector(newMessage);
        break;
    }
    case 2:
        log.saveToFile();
        break;
    case 3:
        if (!log.emptyVector()) {
            cout << "Vector has " << log.countMessagesInTheVector() << " element\n"
                << "Do you want to save them to files(1) or clear the vector(2)? Enter 1 or 2\n";
            int action2;
            cin >> action2;
            switch (action2) {
            case 1:
                log.saveToFile();
                log.readFromTxt();
                break;
            case 2:
                log.clearVector();
                log.readFromTxt();
                break;
            }
        }
        else {
            log.readFromTxt();
        }
        break;
    case 4:
        if (!log.emptyVector()) {
            cout << "Vector has " << log.countMessagesInTheVector() << " element\n"
                << "Do you want to save them to files(1) or clear the vector(2)? Enter 1 or 2\n";
            int action2;
            cin >> action2;
            switch (action2) {
            case 1:
                log.saveToFile();
                log.readFromBin();
                break;
            case 2:
                log.clearVector();
                log.readFromBin();
                break;
            }
        }
        else {
            log.readFromBin();
        }
        break;
    case 5:
        log.outFromVector();
        break;
    case 6:
        log.outFromTxt();
        break;
    case 7:
        log.outFromBin();
        break;
    case 8: {
        cout << "Enter count of messages\n";
        int countOfMessages;
        cin >> countOfMessages;
        log.generateMessagesToFile(countOfMessages);
        break;
    }
    case 9: {
        cout << "Enter data before\n"
            << "Year Month Day Hour Minutes Sec\n";
        FullTime timeBefore = getFullTime();
        cout << "Enter data after\n"
            << "Year Month Day Hour Minutes Sec\n";
        FullTime timeAfter = getFullTime();
        for (auto i : log.searchBetweenTime(timeBefore, timeAfter)) {
            i.outElem();
        }
        break;
    }
    case 10: {
        cout << "Enter type and loading of message\n";
        string type, loading;
        cin >> type >> loading;
        for (auto i : log.searchTypeAndLoading(type, atof(loading.c_str()))) {
            i.outElem();
        }
        break;
    }
    case 11: {
        cout << "Enter substring\n";
        string substr;
        cin >> substr;
        for (auto i : log.searchSubString(substr)) {
            i.outElem();
        }
        break;
    }
    case 12:
        log.clearFiles();
        break;
    case 13:
        log.clearVector();
        break;
    case 14: {
        cout << "Enter index of message to delete\n";
        int index;
        cin >> index;
        if (index >= 0 && index < log.countMessagesInTheVector()) {
            log.deleteOneMessage(index);
        }
        else {
            cout << "Index is out of range\n";
        }
        break;
    }
    case 15: {
        cout << "Enter index of message to update\n";
        int index;
        cin >> index;
        if (index >= 0 && index < log.countMessagesInTheVector()) {
            cout << "Enter new text of message\n";
            cin.ignore();
            string newText;
            getline(cin, newText, '\n');
            log.updateOneMessage(index, newText);
        }
        else {
            cout << "Index is out of range\n";
        }
        break;
    }
    case 100:
        exit(0);
        break;
    default:
        cout << "Wrong input, try again\n";
        break;
    }
}

bool interactive() {
    MessageLog log("data");
    bool flag = true;
    string subStr;
    string neededType;
    string updatedMessage;
    string newMessage;

    while (flag) {
        chooseAction(log);
        if (flag) {
            cout << "Do you want to continue working? y/n\n";
            char next;
            cin >> next;
            flag = next == 'y';
        }
    }
    cout << "Do you want to choose a mode? y/n\n";
    char next;
    cin >> next;
    flag = next == 'y';
    return flag;
};

bool demonstration() {
    MessageLog log("demo");
    log.clearFiles();
    log.defineId();

    cout << "DEMONSTRATION MODE HAS BEEN STARTED\n";
    cout << "Let's create new message\n";
    log.createNewElemAndAddToVector("We have created new mess");
    cout << "Let's see what we have done\n\n";
    log.outFromVector();
    cout << "\nOkay, save to txt and bin files\n\n";
    log.saveToFile();
    cout << "Now, we have in txt:\n\n";
    log.outFromTxt();
    cout << "\n...and in bin:\n\n";
    log.outFromBin();
    cout << "\nIts too long, let's generate 10 messages quickly and add them to files\n";
    log.generateMessagesToFile(10);
    cout << "Now, we have in txt:\n\n";
    log.outFromTxt();
    cout << "Let's delete a message. For example, 5th\n";
    log.deleteOneMessage(5);
    cout << "Now, we have in txt:\n\n";
    log.outFromTxt();
    cout << "\nLet's update a message. For example, 7th and enter new message 'Smells like teen spirits'\n\n";
    log.updateOneMessage(7, "Smells like teen spirits");
    cout << "Now, we have in txt:\n\n";
    log.outFromTxt();
    cout << "Last part of demo: searching\n";
    cout << "\n1) searchingSubString(Smells)\n\n";
    for (auto i : log.searchSubString("Smells"))
        i.outElem();
    cout << "\n2) searchingTypeAndLoading(warning, 0.1);\n\n";
    for (auto i : log.searchTypeAndLoading("warning", 0.1))
        i.outElem();

    FullTime timeBefore, timeAfter;
    timeBefore.setCurrentTime(-5);
    timeAfter.setCurrentTime(5);
    cout << "\n3) searchingBetweenTime(" << timeBefore.year << "." << timeBefore.month << "." << timeBefore.day << " "
        << timeBefore.hour << ":" << timeBefore.minutes << ":" << timeBefore.sec << ", ";
    cout << timeAfter.year << "." << timeAfter.month << "." << timeAfter.day << " "
        << timeAfter.hour << ":" << timeAfter.minutes << ":" << timeAfter.sec << ")\n\n";
    for (auto i : log.searchBetweenTime(timeBefore, timeAfter))
        i.outElem();

    log.clearFiles();
    cout << "\nTHE END OF DEMO MOD\n";
    cout << "Do you want to choose a mode? y/n\n";
    bool flag;
    char next;
    cin >> next;
    flag = next == 'y';
    return flag;
}

bool benchmark() {
    bool flag;
    MessageLog log("bench");
    int countMessages = 10;
    double allTime = 0;

    benchData data{ 0,0,0,0 };
    while (allTime < 10) {
        log.clearFiles();
        log.clearVector();
        log.defineId();

        cout << endl << "Count of messages " << countMessages << endl;
        data = log.forBenchmark(countMessages);
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
