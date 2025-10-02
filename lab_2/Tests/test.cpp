
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <windows.h>
#include "Header.h"

extern MinMaxResult result1;
extern AverageResult result2;

TEST_CASE("MinMax function calculations") {
    SUBCASE("Basic array") {
        int arr[] = { 3, 1, 4, 1, 5, 9, 2, 6 };
        int size = sizeof(arr) / sizeof(arr[0]);
        ThreadArgs args{ arr, size };

        HANDLE hThread = CreateThread(NULL, 0, min_max, &args, 0, NULL);
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);

        CHECK(result1.min == 1);
        CHECK(result1.max == 9);
    }

    SUBCASE("Single element") {
        int arr[] = { 42 };
        int size = sizeof(arr) / sizeof(arr[0]);
        ThreadArgs args{ arr, size };

        HANDLE hThread = CreateThread(NULL, 0, min_max, &args, 0, NULL);
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);

        CHECK(result1.min == 42);
        CHECK(result1.max == 42);
    }

    SUBCASE("Negative numbers") {
        int arr[] = { -5, -2, -10, -1 };
        int size = sizeof(arr) / sizeof(arr[0]);
        ThreadArgs args{ arr, size };

        HANDLE hThread = CreateThread(NULL, 0, min_max, &args, 0, NULL);
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);

        CHECK(result1.min == -10);
        CHECK(result1.max == -1);
    }
}

TEST_CASE("Average function calculations") {
    SUBCASE("Basic array") {
        int arr[] = { 1, 2, 3, 4, 5 };
        int size = sizeof(arr) / sizeof(arr[0]);
        ThreadArgs args{ arr, size };

        HANDLE hThread = CreateThread(NULL, 0, average, &args, 0, NULL);
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);

        CHECK(result2.average == 3);
    }

    SUBCASE("Rounding down") {
        int arr[] = { 1, 2, 3, 4 }; // 10/4 = 2.5 -> 2
        int size = sizeof(arr) / sizeof(arr[0]);
        ThreadArgs args{ arr, size };

        HANDLE hThread = CreateThread(NULL, 0, average, &args, 0, NULL);
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);

        CHECK(result2.average == 2);
    }
}