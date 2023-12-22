#pragma once
#ifndef Video_H
#define Video_H
#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>
#include <locale>
#include <codecvt>
#include <windows.h>

using namespace std;

class Video {
private:
    string filePath, fileName, fileExtension;
    wstring filePathMap;
    double fileSize;
    HANDLE fileHandle, fileMapping;
    LPVOID fileAddress;
    bool isValid;

public:

    Video();

    Video(const string& filePath);

    bool getIsValid();

    void setFilePath(const string& filePath);

    string getFileName();

    string getFilePath();

    string getFileExtension(const string& filePath);

    double getFileSize();

    void mapFile();

    LPVOID getFileAddress();

    void closeFileMapping();
};

#endif