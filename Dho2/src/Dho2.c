/*
 ============================================================================
 Name        : Dho2.c
 Author      : OB
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include <termios.h>
#include <fcntl.h>
#include "Dho2.h"
#include <inttypes.h>

#include <termios.h>

void Vbm_step10ms();
void Fum_step10ms();
void Ram_step10ms();
extern Mnh getMnh_Fum(void);
extern Mnh getMnh_Ram(void);
extern Mnh getMnh_Vbm(void);
extern void TxHighCmd(bool enable);
uint32_t cc = 0;
Mnh mnh0,mnh1,mnh2;

// Met le terminal en mode non canonique
void enableNonCanonicalMode() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO); // désactive mode canonique et echo
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

// Restaure les réglages du terminal
void disableNonCanonicalMode() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

// Rend stdin non bloquant
void setNonBlockingInput() {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

int main(void) {
    enableNonCanonicalMode();
    setNonBlockingInput();
    bool flaga=false;
    bool flagb=false;
    bool flagc=false;

	TxHighCmd(false);
	while(true){
		cc++;
		usleep(10000);//10ms
		if (getchar() == 'a') {
			flaga=true;
			flagb=false;
			flagc=false;
		}
		if(flaga){
			Vbm_step10ms();
			Fum_step10ms();
			Ram_step10ms();
		}
		if (getchar() == 'b') {
			flagb=true;
			flaga=false;
			flagc=false;
		}
		if (flagb){
			Fum_step10ms();
			Ram_step10ms();
		}
		if (getchar() == 'c') {
			flagc=true;
			flagb=false;
			flaga=false;
		}
		if (flagc){
			Ram_step10ms();
		}
		mnh0 = getMnh_Vbm();
		mnh1 = getMnh_Fum();
		mnh2 = getMnh_Ram();
		if (cc >= 100){
			cc=0;
			printf("Mnh_Vbm -> mn: %" PRIu32 ", mh: %" PRIu32 "\n", mnh0.mn, mnh0.mh);
			printf("Mnh_Fum -> mn: %" PRIu32 ", mh: %" PRIu32 "\n", mnh1.mn, mnh1.mh);
			printf("Mnh_Ram -> mn: %" PRIu32 ", mh: %" PRIu32 "\n", mnh2.mn, mnh2.mh);
			printf("flaga : %d\n", flaga);
			printf("flagb : %d\n", flagb);
			printf("flagc : %d\n", flagc);
printf("Vbm.RxFast1: %d, RxTooSlow1: %d,RxFast2: %d, RxTooSlow2: %d,TxSlow1 %d, TxSlow2 %d\n", mnh0.RxFast1ForSync, mnh0.RxTooSlow1, mnh0.RxFast2, mnh0.RxTooSlow2, mnh0.TxSlow1, mnh0.TxSlow2);
printf("Fum.RxFast1: %d, RxTooSlow1: %d,RxFast2: %d, RxTooSlow2: %d,TxSlow1 %d, TxSlow2 %d\n", mnh1.RxFast1ForSync, mnh1.RxTooSlow1, mnh1.RxFast2, mnh1.RxTooSlow2, mnh1.TxSlow1, mnh1.TxSlow2);
printf("Ram.RxFast1: %d, RxTooSlow1: %d,RxFast2: %d, RxTooSlow2: %d,TxSlow1 %d, TxSlow2 %d\n", mnh2.RxFast1ForSync, mnh2.RxTooSlow1, mnh2.RxFast2, mnh2.RxTooSlow2, mnh2.TxSlow1, mnh2.TxSlow2);
		}
	}
	return EXIT_SUCCESS;
}
