/*
 * xml_utils.c
 *
 *  Created on: 29 mai 2025
 *      Author: olivierbessettemac
 */


#include "xml_utils_dtc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void append_to_xml_dtc(const char* filename, uint32_T dtc, uint8_T state) {
    FILE* file = fopen(filename, "a");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    time_t now = time(NULL);
    fprintf(file,
        "  <entry>\n"
        "    <timestamp>%ld</timestamp>\n"
        "    <dtc>%u</dtc>\n"
        "    <state>%u</state>\n"
        "  </entry>\n",
        now, dtc, state);

    fclose(file);
}

void Store_dtc(const char* filename, uint32_T dtc, uint8_t state) {
    append_to_xml_dtc(filename, dtc, state);
}
