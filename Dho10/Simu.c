
#include "Simu.h"

#include "DhoCommun.h"
#include "xml_utils.h"
#include <time.h>
#include <windows.h>

const char* filename_Vbm = "data.xml";
const char* filename_Fum = "data_Fum.xml";
const char* filename_Lim = "data_Lim.xml";

uint32_T compteurSimu = 0;

int main() {
    start_xml(filename_Vbm);
    start_xml(filename_Fum);
    start_xml(filename_Lim);

    VbmInit();
    FumInit();
    LimInit();

	DWORD start1, start2 = GetTickCount();

    while (1) {
    	DWORD now = GetTickCount();
    	if (now - start1 >= 100){
            Vbm_step100ms();
            Lim_step100ms();
            Fum_step100ms();
            start1=now;
    	}
    }
}
