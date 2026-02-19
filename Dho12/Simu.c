
#include "Simu.h"

#include "xml_utils.h"
#include "xml_utils_dtc.h"
#include "xml_utils_nvm.h"
#include <time.h>
#include <windows.h>

#include "Dho.h"
#include "ExternalCalls.h"

const char* filename_Vbm = "data.xml";
const char* filename_Fum = "data_Fum.xml";
const char* filename_Lim = "data_Lim.xml";
const char* filename_dtc = "dtc.xml";
const char* filename_nvm = "nvm.xml";

uint32_T compteurSimu = 0;

int main() {
    start_xml(filename_Vbm);
    start_xml(filename_Fum);
    start_xml(filename_Lim);
    start_xml(filename_dtc);

    VbmInit();
    FumInit();
    LimInit();
    ExternalCalls_Init();

	DWORD start1 = GetTickCount();

    while (1) {
    	DWORD now = GetTickCount();
    	if (now - start1 >= 100){
    		ExternalCalls_step();
            Vbm_step100ms();
            Lim_step100ms();
            Fum_step100ms();
            start1=now;
    	}
    }
}
