#include <windows.h>
#include <iostream>
#include "Header.h"
using namespace std;

const int time_for_Sleep_min_max = 7;
const int time_for_Sleep_average = 12;

DWORD WINAPI min_max(LPVOID args)
{
    cout << "MinMax thread is started." << endl;
    ThreadArgs* args1 = static_cast<ThreadArgs*>(args);
    int* arr = args1->arr;
    int size = args1->size;

    int min = arr[0], max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
        Sleep(time_for_Sleep_min_max);
        if (arr[i] > max) {
            max = arr[i];
        }
        Sleep(time_for_Sleep_min_max);
    }

    cout << "Min: " << min << endl;
    cout << "Max: " << max << endl;

    result1.min = min;
    result1.max = max;

    cout << "MinMax thread is finished." << endl;
    return 0;
}

DWORD WINAPI average(LPVOID args)
{
    cout << "Average thread is started." << endl;
    ThreadArgs* args1 = static_cast<ThreadArgs*>(args);
    int* arr = args1->arr;
    int size = args1->size;

    long long sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
        Sleep(time_for_Sleep_average);
    }
    int result = sum / size;

    cout << "Average: " << result << endl;

    result2.average = result;

    cout << "Average thread is finished." << endl;
    return 0;
}

int main()
{
    try {
        int n;
        cout << "Enter array size: ";
        cin >> n;
        if (cin.fail()) {
            throw runtime_error("Invalid input type");
        }

        while (n <= 0) {
            cout << "Size should be positive. Enter again: ";
            cin >> n;
            if (cin.fail()) {
                throw runtime_error("Invalid input type");
            }
        }

        int* arr = new int[n];
        cout << "Enter " << n << " elements: ";
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
            if (cin.fail()) {
                throw runtime_error("Invalid input type");
            }
        }

        ThreadArgs* args = new ThreadArgs{ arr, n };


        result1.min = 0;
        result1.max = 0;
        result2.average = 0;


        HANDLE hThread;
        DWORD IDThread;
        hThread = CreateThread(NULL, 0, min_max, args, 0, &IDThread);
        if (hThread == NULL)
            return GetLastError();
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);

        HANDLE hThread2;
        DWORD IDThread2;
        hThread2 = CreateThread(NULL, 0, average, args, 0, &IDThread2);
        if (hThread2 == NULL)
            return GetLastError();
        WaitForSingleObject(hThread2, INFINITE);
        CloseHandle(hThread2);


        for (int i = 0; i < n; ++i) {
            if (arr[i] == result1.min || arr[i] == result1.max) {
                arr[i] = result2.average;
            }
        }

        cout << "Final array: ";
        for (int i = 0; i < n; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;


        delete[] arr;
        delete args;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}