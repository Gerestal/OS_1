#pragma once
#include <windows.h>
#include <iostream>
using namespace std;

struct ThreadArgs {
    int* arr;
    int size;
};

struct MinMaxResult {
    int min;
    int max;
};

struct AverageResult {
    int average;
};

extern MinMaxResult result1;
extern AverageResult result2;

DWORD WINAPI min_max(LPVOID args);
DWORD WINAPI average(LPVOID args);
