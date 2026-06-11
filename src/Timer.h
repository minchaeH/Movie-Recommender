#pragma once
#include <chrono>
#include <string>
#include <iostream>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::string function_name;

public:
    Timer(const std::string& name) : function_name(name) {
        start_time = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << "[Profile] " << function_name << " took " << duration.count() << " us.\n";
    }
};