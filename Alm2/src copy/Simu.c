
#include "vbm.h"
#include "Simu.h"
#include "Alarm.h"
#include "EemStates.h"

int main() {
	EemStates_Init();
	Alarm_Init();
	RCtApAlm_Init();
    while (1) {
        usleep(50000); // 50 ms
        EemStates_Step();
        Alarm_Step();
        RCtApAlm_Step();
    }
}
