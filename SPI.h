/*
 *
 *  SPI Controller for PIC12F1/16F1   Version 0.1
 *  (C) 2014 Kazusa Okuda (a.k.a. klaNath)
 *
 *  This software is freely distributable under the terms of an MIT-style license.
 *  For details, see the https://github.com/klaNath/midiRX.git/LICENSE
 *
 */

/*
 *
 *
 *	Caution! This Library implement only MASTER MODE
 *	Another function is not prepared.
 *
 *
 */

#ifndef _SPI_H
#define _SPI_H

enum SPI_INIT_STATE
{
	SPI_NONE,
	SPI_MASTER,
	SPI_SLAVE
};

void initSPI(enum SPI_INIT_STATE);

unsigned char getSPI();
void sendSingleSPI(unsigned char);
void sendMultiSPI(unsigned char*, unsigned char);


#endif