#include "header.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <exception>

#include <sstream> 

std::string ReadBinaryFileName(std::istream& in, std::ostream& out) {
    const std::string forbidden = "\\/:*?\"<>|";
    std::string name;
    while (true) {
        out << "Enter the name of the binary file: ";
        in >> name;
        if (name.empty()) {
            out << "Error: File name can't be empty.\n";
            continue;
        }
        if (name.find_first_of(forbidden) != std::string::npos) {
            out << "Error: File name contains invalid characters.\n";
            continue;
        }
        return name;
    }
}

int ReadRecordCount(std::istream& in, std::ostream& out) {
    int cnt;
    while (true) {
        out << "Enter the number of employees: ";
        in >> cnt;
        if (!in) throw std::runtime_error("EOF or bad input");
        if (cnt < 0) {
            out << "Error: Number of employees can't be negative.\n";
            continue;
        }
        return cnt;
    }
}


