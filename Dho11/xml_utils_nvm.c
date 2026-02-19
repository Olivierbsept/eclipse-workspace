/*
 * xml_utils.c
 *
 *  Created on: 29 mai 2025
 *      Author: olivierbessettemac
 */


#include "xml_utils_nvm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>

void append_to_xml_nvm(const char* filename, uint32 mnbu, uint16 mtbu, uint32 mhbu, uint8 ecuname, uint16 mtf, uint32 mnf, uint16 mtl, uint32 mnl) {
    FILE* file = fopen(filename, "a");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    fprintf(file,
        "  <entry>\n"
        "    <mhbu>%u</mhbu>\n"
        "    <mtbu>%u</mtbu>\n"
        "    <mnbu>%u</mnbu>\n"
        "    <ecuname>%u</ecuname>\n"
        "    <mtf>%u</mtf>\n"
        "    <mnf>%u</mnf>\n"
        "    <mtl>%u</mtl>\n"
        "    <mnl>%u</mnl>\n"
        "  </entry>\n",
        mhbu, mtbu, mnbu, ecuname,mtf,mnf,mtl,mnl);
    fclose(file);
}

void Store_nvm(const char* filename, uint32 mnbu, uint16 mtbu, uint32 mhbu, uint8 ecuname, uint16 mtf, uint32 mnf, uint16 mtl, uint32 mnl)
{
    append_to_xml_nvm(filename, mhbu, mtbu, mnbu, ecuname,mtf, mnf, mtl, mnl);
}

uint8 Read_ecuname(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 0;
    }

    char line[256];
    uint8 value = 0;

    while (fgets(line, sizeof(line), file)) {
        if ( strstr(line, "<ecuname>") ) {
            sscanf(line, " <ecuname>%hhu</ecuname>", &value);
        }
    }

    fclose(file);
    return value; // retourne la dernière valeur mtf trouvée
}

uint16 Read_mtf(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 0;
    }

    char line[256];
    uint16 value = 0;

    while ( fgets(line, sizeof(line), file) ) {
        if (strstr(line, "<mtf>")) {
            sscanf(line, " <mtf>%hu</mtf>", &value);
        }
    }

    fclose(file);
    return value; // retourne la dernière valeur mtf trouvée
}
uint16 Read_mtl(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 0;
    }

    char line[256];
    uint16 value = 0;

    while ( fgets(line, sizeof(line), file) ) {
        if (strstr(line, "<mtl>")) {
            sscanf(line, " <mtl>%hu</mtl>", &value);
        }
    }

    fclose(file);
    return value; // retourne la dernière valeur mtf trouvée
}
uint32 Read_mnf(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 0;
    }

    char line[256];
    uint32 value = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "<mnf>")) {
        	sscanf(line, " <mnf>%" SCNu32 "</mnf>", &value);
        }
    }

    fclose(file);
    return value; // retourne la dernière valeur mtf trouvée
}
uint32 Read_mnl(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 0;
    }

    char line[256];
    uint32 value = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "<mnl>")) {
        	sscanf(line, " <mnl>%" SCNu32 "</mnl>", &value);
        }
    }

    fclose(file);
    return value; // retourne la dernière valeur mtf trouvée
}

uint32 Read_mhbu(const char* filename){
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 0;
    }

    char line[256];
    uint32 value = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "<mhbu>")) {
            sscanf(line, " <mhbu>%u</mhbu>", &value);
        }
    }

    fclose(file);
    return value; // retourne la dernière valeur mtf trouvée
}

uint16 Read_mtbu(const char* filename){
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 0;
    }

    char line[256];
    uint16 value = 0;

    while ( fgets(line, sizeof(line), file) ) {
        if (strstr(line, "<mtbu>")) {
            sscanf(line, " <mtbu>%hu</mtbu>", &value);
        }
    }

    fclose(file);
    return value; // retourne la dernière valeur mtf trouvée
}

uint32 Read_mnbu(const char* filename){
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 0;
    }

    char line[256];
    uint32 value = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "<mnbu>")) {
            sscanf(line, " <mnbu>%u</mnbu>", &value);
        }
    }

    fclose(file);
    return value; // retourne la dernière valeur mtf trouvée
}
