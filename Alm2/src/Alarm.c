/*
 * Alarm.c
 *
 *  Created on: 5 oct. 2025
 *      Author: olivierbessettemac
 * 
 */
 
// Simu.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>

#include "vbm.h" // pour uint16, boolean, TRUE/FALSE

extern void RCtApAlmDtc_SendDtc(uint16 Src, uint16 Dtc, boolean State);

#define MAX_LINE_LENGTH 256

typedef struct {
    long chrono_ms;
    uint16 src;
    uint16 dtc;
    boolean state;
} AlarmEntry;

#define MAX_ENTRIES 100

static AlarmEntry entries[MAX_ENTRIES];
static int entry_count = 0;
static int current_index = 0;
static struct timeval start_time;

// Chrono en millisecondes depuis le lancement
static long getCurrentTimeInMs(void) {
    struct timeval now;
    gettimeofday(&now, NULL);
    long seconds = now.tv_sec - start_time.tv_sec;
    long usec = now.tv_usec - start_time.tv_usec;
    return (seconds * 1000L) + (usec / 1000L);
}

void Alarm_Init(void) {
    FILE* file = fopen("src/Alarms.txt", "r");
    if (!file) {
        perror("Erreur ouverture fichier");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) && entry_count < MAX_ENTRIES) {
        long chrono;
        unsigned int src, dtc, state;
        if (sscanf(line, "%ld %u %u %u", &chrono, &src, &dtc, &state) == 4) {
            entries[entry_count].chrono_ms = chrono;
            entries[entry_count].src = (uint16)src;
            entries[entry_count].dtc = (uint16)dtc;
            entries[entry_count].state = (boolean)(state ? TRUE : FALSE);
            entry_count++;
        }
    }

    fclose(file);
    gettimeofday(&start_time, NULL);
}

void Alarm_Step(void) {
    if (current_index >= entry_count) {
        return; // Plus rien à envoyer
    }

    long current_time = getCurrentTimeInMs();

    // Envoyer tous les DTC prêts
    while (current_index < entry_count && entries[current_index].chrono_ms <= current_time) {
        RCtApAlmDtc_SendDtc(
            entries[current_index].src,
            entries[current_index].dtc,
            entries[current_index].state
        );
        printf("Alarm_Step %d\n", current_index);
        current_index++;
    }
}
