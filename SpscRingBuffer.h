#pragma once
#include <iomanip>
#include <array>
#include <atomic>

template <typename T, size_t Size>
class SpscRingBuffer {
    std::array<T, Size> tablica;
    std::atomic<size_t> head = 0;
    std::atomic<size_t> tail = 0;
public:
    bool push(const T&item);
    bool pop(T&item);
};

template<typename T, size_t Size>
bool SpscRingBuffer<T, Size>::push(const T &item) {
    size_t aktualnyHead = head.load(std::memory_order_relaxed); // dla optymalizacji żebym nie musial ciagle odpytywac zmiennej atomowej
    size_t nastepnyHead = (aktualnyHead + 1) % Size;
    if (tail.load(std::memory_order_acquire) == nastepnyHead) return false;
    tablica[aktualnyHead] = item;
    head.store(nastepnyHead, std::memory_order_release);
    return true;
}

template<typename T, size_t Size>
bool SpscRingBuffer<T, Size>::pop(T &item) {
    size_t aktualnyTail = tail.load(std::memory_order_relaxed);
    if (head.load(std::memory_order_acquire) == aktualnyTail) return false;
    item = tablica[aktualnyTail];
    tail.store(((aktualnyTail+1) %Size), std::memory_order_release);
    return true;
}
