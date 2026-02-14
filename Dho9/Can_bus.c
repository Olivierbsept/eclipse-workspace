// can_bus.c
#include "Can_bus.h"
#include <stdio.h>
#include <time.h>

static FILE *log_file = NULL;
static struct timespec start_time;

void can_bus_init(CAN_Bus *bus) {
    bus->node_count = 0;

    // Ouvrir le fichier de log
    log_file = fopen("can_log.txt", "w");
    if (!log_file) {
        perror("Erreur lors de l'ouverture du fichier log");
    }

    // Démarrer le chrono
    clock_gettime(CLOCK_MONOTONIC, &start_time);
}

void can_bus_register(CAN_Bus *bus, void (*callback)(CAN_Message)) {
    if (bus->node_count < MAX_NODES) {
        bus->receive_callbacks[bus->node_count++] = callback;
    }
}

void can_bus_send_Vbm(CAN_Bus *pbus, CAN_Message msg) {
	can_bus_send(pbus,msg);
}
void can_bus_send_Lim(CAN_Bus *pbus, CAN_Message msg) {
	can_bus_send(pbus,msg);
}

void can_bus_send_Fum(CAN_Bus *pbus, CAN_Message msg) {
	can_bus_send(pbus,msg);
}

void can_bus_send(CAN_Bus *bus, CAN_Message msg) {
    // Affichage console
    printf("[Bus] Transmitting message ID: %03X, DLC: %d\n", msg.id, msg.dlc);

    // Calcul du temps écoulé
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    double elapsed = (current_time.tv_sec - start_time.tv_sec) +
                     (current_time.tv_nsec - start_time.tv_nsec) / 1e9;

    // Écriture dans le fichier log
    if (log_file) {
        fprintf(log_file, "[+%.3f s] ID: %03X, DLC: %d, Data:", elapsed, msg.id, msg.dlc);
        for (int i = 0; i < msg.dlc; i++) {
            fprintf(log_file, " %02X", msg.data[i]);
        }
        fprintf(log_file, "\n");
        fflush(log_file); // Pour forcer l'écriture immédiate
    }

    // Appel des récepteurs
    for (int i = 0; i < bus->node_count; i++) {
        bus->receive_callbacks[i](msg);
    }
}
