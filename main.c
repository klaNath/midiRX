/*
 *
 *  MIDI Reciever and FM Audio Generator Controller Firmware  Version 0.1
 *  (C) 2014 Kazusa Okuda (a.k.a. klaNath)
 *
 *  This software is freely distributable under the terms of an MIT-style license.
 *  For details, see the https://github.com/klaNath/midiRX.git/LICENSE
 *
 */

#include <xc.h>
#include "MIDIRX.h"
#include "fm1001.h"



void interrupt IRQ()
{
    if(PIE1bits.RCIE == 1) getMIDI();
}