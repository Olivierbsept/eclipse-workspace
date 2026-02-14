
#include "Dho.h"

#include "VbmDhoCommun.h"
#include "xml_utils.h"

const char* filename_Vbm = "data.xml";
const char* filename_Fum = "data_Fum.xml";
const char* filename_Lim = "data_Lim.xml";


EemStates currentEemState = ST_ReadytoStart;
bool flagDiag = true;

int main() {
    start_xml(filename_Vbm);
    start_xml(filename_Fum);
    start_xml(filename_Lim);

    VbmInit();
    FumInit();
    LimInit();

    while (true) {
        usleep(100000); // 100 ms
        Vbm_step100ms();
        Fum_step100ms();
        Lim_step100ms();
    }
}
