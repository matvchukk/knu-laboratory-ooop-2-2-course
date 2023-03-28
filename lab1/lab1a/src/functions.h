#ifndef LABOR1_FUNCTIONS_H
#define LABOR1_FUNCTIONS_H
#include "message.h"

using namespace std;

struct benchData {
    double timeGeneratingAndSaving;
    double timeReading;
    double timeSearching;
    double memoryOfData;

};

class Functions {
public:
    vector<MessageLog> log;
    string arrOfErrors[5] = {
            "debug",
            "info",
            "fatal",
            "warning",
            "error"
    };

    static void defineId();

    //��������� ��������
    void createNewElemAndAddToVector(string);
    //��������� ����� (����� ����� � ����)
    void saveToFile();
    //³��������� ����� (���������� ����� � �����);
    void readingFromTxt();
    void readingFromBin();
    //���� ��� ���������� �����;
    static void coutFromTxt();
    static void coutFromBin();
    void coutFromVector();
    //����� �� �������� ��������� (���. ��������� a-c );
    static void searchingBetweenTime(FullTime, FullTime);
    static void searchingTypeAndLoading(string, double);
    static void searchingSubString(string);
    void benchSearchingWithSubstr(string);
    //��������� �������� (�������� ����)
    void deleteOneMessage(int);
    //����������� �������� (�������� ����)
    void updateOneMessage(int, string);
    //�������
    int countWords(string);
    void generateMessages(int);
    static bool subString(string, string);
    void clearFiles();
    benchData forBenchmark(int);//generate N message, save to files,
                        //reading from files and searching random element
};

#endif //LABOR1_FUNCTIONS_H