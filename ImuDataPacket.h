#pragma once
#include <cstdint>
struct ImuDataPacket {
    uint32_t ACCEL_X;
    uint32_t ACCEL_Y;
    uint32_t ACCEL_Z;
    uint32_t GYRO_X;
    uint32_t GYRO_Y;
    uint32_t GYRO_Z;
};