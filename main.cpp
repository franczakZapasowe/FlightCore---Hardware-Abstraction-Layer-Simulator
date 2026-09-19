#include "ImuWrapper.h"
#include <thread>
#include <chrono>
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

void producent(ImuWrapper& imu) {
    for (int i = 0; i < 10; i++) {
        imu.zapisz(i);
        sleep_for(milliseconds(100));
    }
}

void konsument(ImuWrapper& imu) {
    for (int i = 0; i < 10; i++) {
        imu.isDataRdy();
        sleep_for(milliseconds(100));
    }
}

int main(){

    ImuWrapper testowanyRejestr{};
    std::thread t1(producent,std::ref(testowanyRejestr));
    std::thread t2(konsument,std::ref(testowanyRejestr));

    t1.join();
    t2.join();
    return 0;
}
