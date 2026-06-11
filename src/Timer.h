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
       std::cout << "\033[36m [성능 측정] '" << function_name << "' 실행 완료 -> " << duration.count() << " 마이크로초(us) 소요\033[0m\n";
    }
};