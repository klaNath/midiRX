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

__CONFIG(CLKOUTEN_OFF & FOSC_INTOSC & FCMEN_OFF & IESO_OFF & BOREN_ON & PWRTE_ON
& WDTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF) ;
__CONFIG(PLLEN_ON & STVREN_ON & WRT_OFF & BORV_HI & LVP_OFF);


void initSys(void);

void interrupt IRQ()
{
    if(PIR1bits.RCIF == 1) getMIDI();
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
    OSCCON = 0x0F2;
    OPTION_REG = 0xD0;
    TRISA = 0x38;
    ANSELA = 0;
    INTCON = 0xC0;
    //PIE1 = 0x20;                                                  //move to initUART()
    
    initUART(UART_RX_ONLY);
    initFM();
}