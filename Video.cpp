#include "Video.h"
#ifdef Video_H

Video::Video() {}

Video::Video(const string& filePath) {
    setFilePath(filePath);
}

void Video::setFilePath(const string& filePath) {
    ifstream supportedExtensionsFile("supported_extensions.txt");
    if (!supportedExtensionsFile.is_open()) {
        cout << "Error opening supported_extensions.txt" << endl;
        return;
    }

    string ext = getFileExtension(filePath);
    string supportedExtension;
    bool isValidExtension = false;

    while (getline(supportedExtensionsFile, supportedExtension)) {
        if (ext == supportedExtension) {
            isValidExtension = true;
            break;
        }
    }

    supportedExtensionsFile.close();

    if (isValidExtension) {
        this->filePath = filePath;
        isValid = true;
        wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
        this->filePathMap = converter.from_bytes(filePath);
        mapFile();
    }
    else {
        cout << "This file extension is not supported" << endl;
    }
}

string Video::getFileName() {
    size_t pos = filePath.find_last_of("/\\");
    string fileNameWithExtension = filePath.substr(pos + 1);
    size_t extensionPos = fileNameWithExtension.find_last_of(".");

    if (extensionPos != string::npos) {
        return fileNameWithExtension.substr(0, extensionPos);
    }
    else {
        return fileNameWithExtension;
    }
}

string Video::getFilePath() {
    return filePath;
}

double Video::getFileSize() {
    ifstream file(filePath, ios::binary | ios::ate);
    if (file.is_open()) {
        double size = file.tellg();
        file.close();
        return ((size / 1024) / 1024);
    }
    else {
        return -1;
    }
}

string Video::getFileExtension(const string& filePath) {
    size_t pos = filePath.find_last_of(".");
    return filePath.substr(pos);
}

void Video::mapFile() {
    fileHandle = CreateFile(filePathMap.c_str(),   // For C-style String
        GENERIC_READ,   // Read Mode
        FILE_SHARE_READ,   // Share the file between the process
        nullptr,
        OPEN_EXISTING,   // Open only if the file exist
        FILE_ATTRIBUTE_NORMAL,     // Normal ATTRIBUTE
        nullptr);

    if (fileHandle == INVALID_HANDLE_VALUE) {
        cout << "Error opening file." << endl;
        return;
    }

    fileMapping = CreateFileMapping(fileHandle,
        nullptr,
        PAGE_READONLY,   // Read Mode
        0, // for 32-bit files
        0, // for all the file
        nullptr);

    if (fileMapping == nullptr) {
        cout << "Error creating file mapping." << endl;
        CloseHandle(fileHandle);
        return;
    }

    fileAddress = MapViewOfFile(fileMapping,
        FILE_MAP_READ,   // Read Mode
        0,   // offset: 0 means from the begining of the file
        0,   // offset: 0 means from the begining of the file
        0);  // all the file should be mapped

    if (fileAddress == nullptr) {
        cout << "Error mapping view of file." << endl;
        closeFileMapping();
    }
}

LPVOID Video::getFileAddress() {
    return fileAddress;
}

void Video::closeFileMapping() {
    if (fileAddress != nullptr) {
        UnmapViewOfFile(fileAddress);
        fileAddress = nullptr;
    }

    if (fileMapping != nullptr) {
        CloseHandle(fileMapping);
        fileMapping = nullptr;
    }

    if (fileHandle != nullptr && fileHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(fileHandle);
        fileHandle = nullptr;
    }
}

bool Video::getIsValid() {
    return isValid;
}

#endif