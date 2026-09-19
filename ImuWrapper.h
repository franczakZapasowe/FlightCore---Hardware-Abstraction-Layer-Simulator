#pragma once
#include "pamiecIMU.h"
#include "ImuDataPacket.h"
#include "SpscRingBuffer.h"
#include <atomic>
#include <iostream>
#include <cstdint>
constexpr uint32_t MASK_CTRL_REG_DATA_READY= 0x01; //maska do zmiany

class ImuWrapper {
    ImuRegisters imuRegisters{};

    bool dataRdy() {
        std::atomic_ref<uint32_t> atomic_raw(imuRegisters.STATUS_REG.raw);
        uint32_t maska = 1;
        if((atomic_raw.load(std::memory_order_acquire)&maska) == 1 )
            return true;
        return false;
    }

    void zerujDataRdy() {
        std::atomic_ref<uint32_t> atomic_raw(imuRegisters.STATUS_REG.raw);
        uint32_t maska = 1;
        if (dataRdy()) atomic_raw.fetch_and(~maska,std::memory_order_relaxed);
    }
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
    }

    void isr_handler(SpscRingBuffer<ImuDataPacket,256>&buffer) {
        if (dataRdy()) {
            ImuDataPacket packet;
            packet.ACCEL_X = imuRegisters.ACCEL_X;
            packet.ACCEL_Y = imuRegisters.ACCEL_Y;
            packet.ACCEL_Z = imuRegisters.ACCEL_Z;
            packet.GYRO_X = imuRegisters.GYRO_X;
            packet.GYRO_Y = imuRegisters.GYRO_Y;
            packet.GYRO_Z = imuRegisters.GYRO_Z;

            buffer.push(packet);
            zerujDataRdy();
        }
    }
};
