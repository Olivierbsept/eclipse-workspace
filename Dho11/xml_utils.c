/*
 * xml_utils.c
 *
 *  Created on: 29 mai 2025
 *      Author: olivierbessettemac
 */


#include "xml_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void start_xml(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file) {
        fprintf(file, "<data>\n");
        fclose(file);
    }
}

void append_to_xml(const char* filename, uint32_T mn, uint16_T mt, uint32_T mh) {
    FILE* file = fopen(filename, "a");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    time_t now = time(NULL);
    fprintf(file,
        "  <entry>\n"
        "    <timestamp>%ld</timestamp>\n"
        "    <mn>%u</mn>\n"
        "    <mt>%u</mt>\n"
        "    <mh>%u</mh>\n"
        "  </entry>\n",
        now, mn, mt, mh);

    fclose(file);
}

void Store(const char* filename, uint32_T mn, uint16_t mt, uint32_T mh) {
    append_to_xml(filename, mn, mt, mh);
}
