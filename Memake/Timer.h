#pragma once

#include <iostream>
#include <chrono>

/*
 * RAII = Resource Acquisition Is Initialization
 * is a C++ programming technique which binds the life cycle of a resource that-
 * must be acquired before use
 */
class Timer
{
public:
    Timer()
    {
        startTimePoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        stop();
    }

    void stop()
    {
        // in microseconds
        auto endTimePoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

        auto duration = end - start;

        // microseconds to millisecond
        double ms = duration * 0.001;

        std::cout << duration << "us (" << ms << "ms)\n";
    }

private:
    // in microseconds
    std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
};

