/*
 *
 *  SPI Controller for PIC12F1/16F1   Version 0.1
 *  (C) 2014 Kazusa Okuda (a.k.a. klaNath)
 *
 *  This software is freely distributable under the terms of an MIT-style license.
 *  For details, see the https://github.com/klaNath/midiRX.git/LICENSE
 *
 */



#ifndef _SPI_H
#define _SPI_H

enum SPI_INIT_STATE
{
	SPI_NONE,
	SPI_BOTH,
	SPI_RX_ONLY,
	SPI_TX_ONLY
};

void initSPI(enum SPI_INIT_STATE);

unsigned char getSPI();
unsigned char sendSingleSPI(unsigned char);
unsigned char sendMultiSPI(unsigned char*, unsigned char);


#endif