/*
 * Dho2.h
 *
 *  Created on: 16 mai 2025
 *      Author: olivierbessettemac
 */

#ifndef DHO2_H_
#define DHO2_H_

typedef struct{
	uint32_t mn;
	uint32_t mh;
	bool RxTooSlow1;
	bool RxFast1ForSync;
	bool RxTooSlow2;
	bool RxFast2;
	bool TxSlow1;
	bool TxSlow2;
	bool TxFastForSync;
} Mnh;

#endif /* DHO2_H_ */
