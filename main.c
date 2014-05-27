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

#define SYS_FREQ 32000000

#define __DEBUG

__CONFIG(CLKOUTEN_OFF & FOSC_INTOSC & FCMEN_OFF & IESO_OFF & BOREN_ON & PWRTE_ON
& WDTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF) ;
__CONFIG(PLLEN_ON & STVREN_ON & WRT_OFF & BORV_HI & LVP_OFF);

char rx_Done = 0;

void initSys(void);

void interrupt IRQ()
{
    if(PIR1bits.RCIF == 1)
    {
        rx_Done = 1;
        PIR1bits.RCIF = 0;
    }
}


void main(void)
{

    unsigned char note, och;
    MIDI_RX_STATUS state;

    initSys();

    while(1)
    {
        if(rx_Done == 1) getMIDI();  
        if(Parse_Done == 1)   state = getStatus();


        if(state == NOTE_ON)
        {
            note = getNote();
            och = getSendCh(0);
#ifndef __DEBUG
            sendFM(note, och, 1);
#endif
            PORTA = 0x04;

        }
        else if(state == NOTE_OFF)
        {
            note = getNote();
            och = getSendCh(note);
#ifndef
            sendFM(note, och, 0);
#endif
            PORTA = 0;
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
    PORTA = 0;
    //PIE1 = 0x20;                                                  //move to initUART()

    clearMIDI();
    initUART(UART_RX_ONLY);
#ifndef __DEBUG
    initFM();
#endif
}

