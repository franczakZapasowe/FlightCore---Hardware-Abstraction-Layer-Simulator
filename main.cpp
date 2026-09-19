#include "ImuWrapper.h"
#include "ImuDataPacket.h"
#include "SpscRingBuffer.h"
#include <thread>
#include <chrono>
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

void producent(ImuWrapper& imu, SpscRingBuffer<ImuDataPacket,256>& buffer) {
    for (int i = 0; i < 1000000; i++) {
        imu.zapisz(i);
        imu.isr_handler(buffer);
    }
}

void konsument(SpscRingBuffer<ImuDataPacket,256>& buffer) {
    int licznik = 0;
    while (licznik<1000000) {
        ImuDataPacket packet;
        if (buffer.pop(packet))
        licznik++;
    }
}

int main(){

    ImuWrapper testowanyRejestr{};
    SpscRingBuffer<ImuDataPacket,256> buffer;
    std::thread t1(producent,std::ref(testowanyRejestr),std::ref(buffer));
    std::thread t2(konsument,std::ref(buffer));

    t1.join();
    t2.join();
    return 0;
}
