#pragma once
#include "pamiecIMU.h"
#include <atomic>
#include <iostream>
#include <cstdint>
constexpr uint32_t MASK_CTRL_REG_DATA_READY= 0x01; //maska do zmiany

class ImuWrapper {
    ImuRegisters imuRegisters{};
    public:
    void zapisz(unsigned int x) {
            imuRegisters.ACCEL_X = x;
            imuRegisters.ACCEL_Y = x;
            imuRegisters.ACCEL_Z = x;
            imuRegisters.GYRO_X = x;
            imuRegisters.GYRO_Y = x;
            imuRegisters.GYRO_Z = x;
            std::atomic_ref<uint32_t> atomic_raw(imuRegisters.STATUS_REG.raw);
            atomic_raw.fetch_or(MASK_CTRL_REG_DATA_READY, std::memory_order_release); // zmiana bitu 0 na 1
            //std::cerr<<"Zpisalem i zmienilem bit na 1\n";
    }

    void isDataRdy() {
        std::atomic_ref<uint32_t> atomic_raw(imuRegisters.STATUS_REG.raw);
        uint32_t maska = 1;

        while ((atomic_raw.load(std::memory_order_acquire)&maska) == 0 ) {} //pusta petla czekajaca dopki status bedzie rowny 1
        //std::cerr<<"Bit sie zmienil\n";

        std::cout<<"Accel x: "<<imuRegisters.ACCEL_X << std::endl;
        std::cout<<"Accel y: "<<imuRegisters.ACCEL_Y << std::endl;
        std::cout<<"Accel z: "<<imuRegisters.ACCEL_Z << std::endl;
        std::cout<<"Gyro x: "<<imuRegisters.GYRO_X << std::endl;
        std::cout<<"Gyro y: "<<imuRegisters.GYRO_Y << std::endl;
        std::cout<<"Gyro z: "<<imuRegisters.GYRO_Z << std::endl;

        atomic_raw.fetch_and(~MASK_CTRL_REG_DATA_READY,std::memory_order_relaxed);
        //std::cerr<<"Zmienilem bit na 0\n";
    }
};
