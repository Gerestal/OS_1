#pragma once
#include <iostream>
#include <thread>
#include <chrono>

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

MinMaxResult result1;
AverageResult result2;

void min_max(void* args);
void average(void* args);
