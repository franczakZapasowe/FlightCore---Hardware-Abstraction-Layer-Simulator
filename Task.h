#pragma once
#include <chrono>
#include <functional>

struct Task {
    std::function<void()> funckja;
    std::chrono::microseconds period; // czas pomiedzy kolejnymi wywolaniami
    std::chrono::steady_clock::time_point next_execution_time; //punktw kotrym zadanie ma sie wykonac po raz kolejny
};
