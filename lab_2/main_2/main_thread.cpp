#include <iostream>
#include <thread>
#include <chrono>
#include "Header.h"

using namespace std;

void min_max(void* args)
{
    cout << "MinMax thread is started." << endl;
    ThreadArgs* args1 = static_cast<ThreadArgs*>(args);
    int* arr = args1->arr;
    int size = args1->size;

    int min = arr[0], max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < min) {
            min = arr[i];
            this_thread::sleep_for(chrono::milliseconds(7));
        }
        if (arr[i] > max) {
            max = arr[i];
            this_thread::sleep_for(chrono::milliseconds(7));
        }
    }

    cout << "Min: " << min << endl;
    cout << "Max: " << max << endl;

    result1.min = min;
    result1.max = max;

    cout << "MinMax thread is finished." << endl;
}

void average(void* args)
{
    cout << "Average thread is started." << endl;
    ThreadArgs* args1 = static_cast<ThreadArgs*>(args);
    int* arr = args1->arr;
    int size = args1->size;

    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
        this_thread::sleep_for(chrono::milliseconds(12));
    }
    int result = sum / size;

    cout << "Average: " << result << endl;

    result2.average = result;

    cout << "Average thread is finished." << endl;
}

int main()
{
    int n;
    cout << "Enter array size: ";
    cin >> n;
    while (n <= 0) {
        cout << "Size should be positive. Enter again: ";
        cin >> n;
    }

    int* arr = new int[n];
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    ThreadArgs* args = new ThreadArgs{ arr, n };


    result1.min = 0;
    result1.max = 0;
    result2.average = 0;


    thread t1(min_max, args);
    t1.join();

    thread t2(average, args);
    t2.join();

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

    return 0;
}