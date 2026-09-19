#pragma once
#include "Task.h"
#include <array>
#include <functional>

constexpr size_t MAX_TASKS = 10;
class Scheduler {
    std::array<Task,MAX_TASKS>tasks;
public:
    Task addTask(std::function<void()>, unsigned int czestotliwosc_w_HZ) {

    }
};