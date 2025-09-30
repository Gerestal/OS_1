#include <windows.h>
#include <iostream>
#include "Header.h"
using namespace std;

MinMaxResult result1;
AverageResult result2;

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
            Sleep(7);
        }
        if (arr[i] > max) {
            max = arr[i];
            Sleep(7);
        }
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

    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
        Sleep(12);
    }
    int result = sum / size;

    cout << "Average: " << result << endl;

    result2.average = result;

    cout << "Average thread is finished." << endl;
    return 0;
}