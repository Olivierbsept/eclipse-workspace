/*
 * Common.c
 *
 *  Created on: 16 mai 2025
 *      Author: olivierbessettemac
 */
/*
#include "Common.h"
#include "Dho2.h"

void MsgRx1(uint32_t mn, uint32_t mh);
void MsgRx2(uint32_t mn, uint32_t mh);
extern MsgTx1(uint32_t mn, uint32_t mh);
extern MsgTx2(uint32_t mn, uint32_t mh);
Mnh getMnh(void);

static uint32_t mn0=100;
static uint32_t mh0=5;
static uint32_t mn1= 0xFFFFFFFF;
static uint32_t mh1= 0xFFFFFFFF;
static uint32_t mn2= 0xFFFFFFFF;
static uint32_t mh2= 0xFFFFFFFF;

static bool freqHighOn=false;

void MsgRx1(uint32_t mn, uint32_t mh){
	check1=true;
	mn1=mn;
	mh1=mh;
}
void MsgRx2(uint32_t mn, uint32_t mh){
	check2=true;
	mn2=mn;
	mh2=mh;
}

void Step(){
	compteur1sec++;
	compteur100msec++;
	if (compteur1sec == 100){
		mh0++;
		compteur1sec=0;
		if (freqHighOn == false){
			MsgTx1(mn0,mh0);
			MsgTx2(mn0,mh0);
		}
	}
	if (compteur100msec == 10){
		compteur100msec=0;
		if (freqHighOn == true){
			MsgTx1(mn0,mh0);
			MsgTx2(mn0,mh0);
		}
	}
	if (check1){
		check1=false;
		if (cc_step1 >= 100){
			HighFreq1 = false;
		}
		else if (cc_step1 >= 10){
			HighFreq1 = true;
		}
		cc_step1=0;
	}
	else{
		if (cc_step1 > 300){
			LowFreq1 = true;
		}
		else{
			LowFreq1 = false;
		}
		cc_step1++;
	}
	if (check2){
		check2=false;
		if (cc_step2 >= 100){
			HighFreq2 = false;
		}
		else if (cc_step2 >= 10){
			HighFreq2 = true;
		}
		cc_step2=0;
	}
	else{
		if (cc_step2 > 300){
			LowFreq2 = true;
		}
		else{
			LowFreq2 = false;
		}
		cc_step2++;
	}
	if (HighFreq1==true && LowFreq1==false){
		mh0=mh1;
		mn0=mn1;
	}
	else if (HighFreq2==true & LowFreq2==false){
		mh0=mh2;
		mn0=mn2;
	}
	else if (mn0==mn1 && mn0==mn2 && LowFreq1==false && LowFreq2==false){
		mh0= max3(mh0, mh1, mh2);
	}
	else if (mn0==mn1 && LowFreq1==false){
		mh0= max2(mh0, mh1);
	}
	else if (mn0==mn2 && LowFreq2==false){
		mh0= max2(mh0, mh2);
	}
	else  if (mn1==mn2 && mn1!=0xFFFFFFFF && LowFreq1==false && LowFreq2==false){
		mh0= max2(mh1, mh2);
	}

}
Mnh getMnh(){
	Mnh mnh;
	mnh.mh=mh0;
	mnh.mn=mn0;
	return mnh;
}

void FreqHighOn(bool enable){
	freqHighOn=enable;
	printf("FreqHighOn : %d\n", freqHighOn);
}
*/
