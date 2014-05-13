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

void initSys(void);

void interrupt IRQ()
{
    if(PIE1bits.RCIE == 1) getMIDI();
}


void main(void)
{

    unsigned char state, note, och;

    initSys();
    initFM();

    while(1)
    {
        if(validMIDI() == 1)   state = getStatus();

        if(state == NOTE_ON)
        {
            note = getNote();
            och = getSendCh(0);

            sendFM(note, och, 1);
        }
        else if(state == NOTE_OFF)
        {
            note = getNote();
            och = getSendCh(note);

            sendFM(note, och, 0);
        }
    }
}

void initSys()
{


}