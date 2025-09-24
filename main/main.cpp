#include "Header.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <exception>



using namespace std;



bool DoProcess(const wstring& appPath, const wstring& params)
{
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    
    wstring cmdLine = L"\"" + appPath + L"\" " + params;
   

    if (!CreateProcessW(
       // appPath.c_str(),    
        nullptr,
        &cmdLine[0],             
        NULL, NULL, FALSE,
        CREATE_NEW_CONSOLE,
        NULL, NULL,
        &si, &pi))
    {
        throw runtime_error("Cannot start process: " +
            string(appPath.begin(), appPath.end()));
    }

    
    DWORD waitResult = WaitForSingleObject(pi.hProcess, INFINITE);
    if (waitResult == WAIT_FAILED)
    {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        throw runtime_error("Error waiting for process. Code: " +
            to_string(GetLastError()));
       
    }

    
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return true;
}


void PrintFile(const string& fileName)
{
    employee emp;
    ifstream file(fileName, ios::binary);
    if (!file)
    {
        cerr << "Couldn't open the file: " << fileName << endl;
        return;
    }
    
    int index = 1;
    while (file.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        cout << "\nEmployee " << index++ << endl;
        cout << "Number: " << emp.num << endl;
        cout << "Name: " << emp.name << endl;
        cout << "Hours: " << emp.hours << endl;
    }
    file.close();

    cout << endl;
}

void PrintFile2(const string& fileName)
{
    employee2 emp;
    ifstream file(fileName);
    if (!file)
    {
        cerr << "Couldn't open the file: " << fileName << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
    cout << endl;
}

string ReadBinaryFileName(istream& in, ostream& out) {
    const string forbidden = "\\/:*?\"<>|";
    string name;
    while (true) {
        out << "Enter the name of the binary file: ";
        in >> name;
        if (name.empty()) {
            out << "Error: File name can't be empty.\n";
            continue;
        }
        if (name.find_first_of(forbidden) != string::npos) {
            out << "Error: File name contains invalid characters.\n";
            continue;
        }
        return name;
    }
}

int ReadRecordCount(istream& in, ostream& out) {
    int cnt;
    while (true) {
        out << "Enter the number of employees: ";
        in >> cnt;
        if (!in) throw runtime_error("EOF or bad input");
        if (cnt < 0) {
            out << "Error: Number of employees can't be negative.\n";
            continue;
        }
        return cnt;
    }
}



int main()
{
    try {
        

        string binFileName = ReadBinaryFileName(cin, cout);
        int recordCount = ReadRecordCount(cin, cout);


      wstring creatorPath = L"Creator.exe";

        
        wstring creatorParams = wstring(binFileName.begin(), binFileName.end()) + L" " + to_wstring(recordCount);
       

       DoProcess(creatorPath, creatorParams);


        cout << "\nThe contents of the binary file:\n";
        PrintFile(binFileName);


        string reportFileName;
        double hourlyRate;

        while (true) {
            cout << "Enter the name of the report file: ";
            cin >> reportFileName;


            if (reportFileName.empty()) {
                cout << "Error: File name cannot be empty.\n";
                continue;
            }


            const string forbidden = "\\/:*?\"<>|";
            if (reportFileName.find_first_of(forbidden) != string::npos) {
                cout << "Error: File name contains invalid characters.\n";
                continue;
            }
            break;
        }
       

        while (true) {
            cout << "Enter the payment for the hour of work: ";
            if (!(cin >> hourlyRate)) {
                cout << "Error: please enter a valid paymant.\n";
                continue;
            }

            if (hourlyRate < 0) {
                cout << "Error: payment can't be negative.\n";
                continue;
            }

            break;
        }


        wstring reporterPath = L"Repoter.exe";
        wstring reporterParams = wstring(binFileName.begin(), binFileName.end()) + L" " +
            wstring(reportFileName.begin(), reportFileName.end()) + L" " +
            to_wstring(hourlyRate);

        DoProcess(reporterPath, reporterParams);


        cout << "\nReport Content:\n";
        PrintFile2(reportFileName);

        _cputs("\nThe work is completed.\n");
        _getch();
       
    }
    catch (const ios_base::failure& io_err) {
        cerr << "I/O error: " << io_err.what() << endl;
        return 1;
    }
    catch (const invalid_argument& arg_err) {
        cerr << "Invalid argument: " << arg_err.what() << endl;
        return 2;
    }
    catch (const out_of_range& range_err) {
        cerr << "Value out of range: " << range_err.what() << endl;
        return 3;
    }
    catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 4;
    }
    return 0;
}
