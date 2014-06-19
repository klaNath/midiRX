/*
 *
 *  FM Audio Generator Controller  Version 0.1
 *  (C) 2014 Kazusa Okuda (a.k.a. klaNath)
 *
 *  This software is freely distributable under the terms of an MIT-style license.
 *  For details, see the https://github.com/klaNath/midiRXb.git/LICENSE
 *
 */

/*
 *this library, fm1001 controller manager, needs Low Lavel SPI function.
 *
 * enum SPI_INIT_STATE
 *{
 *	SPI_NONE,
 *	SPI_MASTER,
 *	SPI_SLAVE
 *};
 *
 *void initSPI(enum SPI_INIT_STATE);
 *unsigned char getSPI();
 *void sendSingleSPI(unsigned char);
 *void sendMultiSPI(unsigned char*, unsigned char);
 *
 * Their has required to use their function. SPI mode is (0,0) master mode.
 */

#include "SPI.h"

#ifndef _FM1001_H
#define _FM1001_H

void initFM(char);
/**
 *
 * @param 0 => normal mode. 1=> fixed velocity mode
 * @return None
 */

unsigned char getSendCh(unsigned char);
/*
 * Return is FM synthesizer channel to send.
 * 1st argument is 0,
 * then this function will return empty or most oldest channnel.
 * Argument is not 0, first, serching channel has same note number and
 * returning this channel.
 * However no correct channel, function return empty or most oldest channel.
 *
 */

unsigned char sendFM(unsigned char, unsigned char, unsigned char);
/*unsigned char sendFM(unsigned char, unsigned char, unsigned char)
 *
 * Return is OK or FAIL indicater. OK return 0, FAIL return 0xFF
 *
 * 1st argument is FM sinthesizer channel, 0-15
 * 2nd argument is Note number, 0-127.
 * 3rd argument is Velocity, OFF is 0, other 1-127 is ON.
 *
 */


#endif