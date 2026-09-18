#include <cstdint>

#pragma pack(1)
struct ImuRegisters{
    union {
        uint32_t raw;
        struct {
            uint32_t POWER_EN: 1;        // 0 = Sleep Mode, 1 = Power On
            uint32_t ACCEL_RANGE: 2;     // 00 = ±2g, 01 = ±4g, 10 = ±8g, 11 = ±16g
            uint32_t GYRO_RANGE: 2;      // 00 = ±250 dps, 01 = ±500 dps, 10 = ±1000 dps, 11 = ±2000 dps
            uint32_t SAMPLE_RATE: 2;     // 000 = 100Hz, 001 = 200Hz, 010 = 400Hz, 011 = 800Hz, 100 = 1000Hz, reszta kombinacji nieużywana/zabroniona
            uint32_t INT_EN: 1;          // Interrupt Enable: 0 = Wyłączone przerwania sprzętowe, 1 = Sprzęt generuje przerwanie (sygnał wyzwalający ISR) przy nowych danych.
            uint32_t RESERVED: 24;       // Bity zarezerwowane
        }bits;
    } CTRL_REG; //Rejestr konfiguracyjny do zapisu przez software

    union {
        uint32_t raw;
        struct {
            uint32_t DATA_READY : 1;    // 1 probki w rejstrzedanych - Oprogramowanie ma obowiązek zapisać w tym bicie 0 natychmiast po odczytaniu danych
            uint32_t BUFFER_OVERRUN: 1; // 1 = Zgubiono ramkę danych - Sprzęt ustawia na 1, jeśli nadeszła nowa próbka, a DATA_READY wciąż wynosiło 1 (zgubiona ramka)
            uint32_t HW_ERROR: 1;       // 1 = Błąd sprzętowy
            uint32_t RESERVED: 29;      // Bity zarezerwowane, ignorować przy odczycie
        }bits;
    } STATUS_REG;    //Rejestr statusu do zapisu przez hardware

    //Dane z akcelerometru
    uint32_t ACCEL_X;
    uint32_t ACCEL_Y;
    uint32_t ACCEL_Z;

    //Dane z żyroskopu
    uint32_t GYRO_X;
    uint32_t GYRO_Y;
    uint32_t GYRO_Z;

};
#pragma pack()

static_assert(sizeof(ImuRegisters)==32, "Struktura ma mniej lub wiecej niz 32 bajty");
static_assert(std::is_standard_layout_v<ImuRegisters>, "Struktura nie ma standardowego ukladu");
