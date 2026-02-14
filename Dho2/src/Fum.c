#include "Common.h"
#include "Dho2.h"

void VbmToFumMsg(uint32_t mn, uint32_t mh);
void RamToFumMsg(uint32_t mn, uint32_t mh);
extern FumToVbmMsg(uint32_t mn, uint32_t mh);
extern FumToRamMsg(uint32_t mn, uint32_t mh);
Mnh getMnh_Fum(void);

static uint32_t mn0=101;
static uint32_t mh0=50;
static uint32_t mn1= 0xFFFFFFFF;
static uint32_t mh1= 0xFFFFFFFF;
static uint32_t mn2= 0xFFFFFFFF;
static uint32_t mh2= 0xFFFFFFFF;

void VbmToFumMsg(uint32_t mn, uint32_t mh){
	check1=true;
	mn1=mn;
	mh1=mh;
}
void RamToFumMsg(uint32_t mn, uint32_t mh){
	check2Vbm=true;
	mn2=mn;
	mh2=mh;
}
void Fum_step10ms(){
	compteurStep++;
	if (	(TxSlow1 == true && 0 == (compteurStep % 150))
		||	(TxSlow1 == false && TxFastForSync == false && 0 == (compteurStep % 100))
		||	(TxFastForSync == true && 0 == (compteurStep % 10)) ){
		FumToVbmMsg(mn0,mh0);
	}
	if (	(TxSlow2 == true && 0 == (compteurStep % 150))
			||	(TxSlow2 == false && TxFastForSync == false && 0 == (compteurStep % 100))
			||	(TxFastForSync == true && 0 == (compteurStep % 10)) ){
		FumToRamMsg(mn0,mh0);
	}
	if (0 == (compteurStep % 100)){
		mh0++;
	}
	/*if (0 == (compteurStep % 100)){
		mh0++;
		if (TxHigh == false){
			FumToVbmMsg(mn0,mh0);
			FumToRamMsg(mn0,mh0);
		}
		compteurStep=0;
	}
	if ((TxHigh == true) && (0 == compteurStep % 10) ){
		FumToVbmMsg(mn0,mh0);
		FumToRamMsg(mn0,mh0);
	}*/
	if (check1){
		check1=false;
		if (cc_step1 >= 99){
			RxFast1ForSync = false;
		}
		else if (cc_step1 >= 9){
			RxFast1ForSync = true;
		}
		cc_step1=0;
	}
	else{
		if (cc_step1 > 500){
			RxTooSlow1 = true;
		}
		else{
			if (cc_step1 < 200){
				RxTooSlow1 = false;
			}
			cc_step1++;
		}
	}
	if (check2Vbm){
		check2Vbm=false;
		if (cc_step2 >= 99){
			RxFast2ForSync = false;
		}
		else if (cc_step2 >= 9){
			RxFast2ForSync = true;
		}
		cc_step2=0;
	}
	else{
		if (cc_step2 > 500){
			RxTooSlow2 = true;
		}
		else{
			if (cc_step2 < 200){
				RxTooSlow2 = false;
			}
			cc_step2++;
		}
	}
	if (TxFastForSync == true){
		// pas de modification du mh0 et mn0
		// modification des mh1 et mh2
		TxSlow1 = false;
		TxSlow2 = false;
	}
	else if (RxFast1ForSync==true && RxTooSlow1==false){
		mh0=mh1;
		mn0=mn1;
		// pas modification du mh1
		TxSlow1 = true;
		TxSlow2 = false;
	}
	else if (RxFast2ForSync==true & RxTooSlow2==false){
		mh0=mh2;
		mn0=mn2;
		// pas modification du mh2
		TxSlow1 = false;
		TxSlow2 = true;
	}
	else if (mn0==mn1 && mn0==mn2 && RxTooSlow1==false && RxTooSlow2==false){
		mh0= max3(mh0, mh1, mh2);
		// modification des mh1 et mh2
		TxSlow1 = false;
		TxSlow2 = false;
	}
	else if (mn0==mn1 && RxTooSlow1==false){
		mh0= max2(mh0, mh1);
		// modification de mh1 et pas du mh2
		TxSlow1 = false;
		TxSlow2 = true;
	}
	else if (mn0==mn2 && RxTooSlow2==false){
		mh0= max2(mh0, mh2);
		// modification de mh2 et pas du mh1
		TxSlow2 = false;
		TxSlow1 = true;
	}
	else  if (mn1==mn2 && mn1!=0xFFFFFFFF && RxTooSlow1==false && RxTooSlow2==false){
		mn0=mn1;
		mh0= max2(mh1, mh2);
		// pas de modification des mh1 et mh2
		TxSlow1 = true;
		TxSlow2 = true;
	}
	else{
		TxSlow1 = true;//mh0 is not synchronised
		TxSlow2 = true;
	}
}
Mnh getMnh_Fum(){
	Mnh mnh;
	mnh.mh=mh0;
	mnh.mn=mn0;
	mnh.RxFast1ForSync=RxFast1ForSync;
	mnh.RxTooSlow1=RxTooSlow1;
	mnh.RxFast2=RxFast2ForSync;
	mnh.RxTooSlow2=RxTooSlow2;
	mnh.TxSlow1=TxSlow1;
	mnh.TxSlow2=TxSlow2;
	mnh.TxFastForSync=TxFastForSync;
	return mnh;
}

