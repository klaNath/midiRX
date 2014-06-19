/*
 *
 *  MIDI Reciever and FM Audio Generator Controller Firmware  Version 0.3
 *  (C) 2014 Kazusa Okuda (a.k.a. klaNath)
 *
 *  This software is freely distributable under the terms of an MIT-style license.
 *  For details, see the https://github.com/klaNath/midiRX.git/LICENSE
 *
 */

#include <xc.h>
#include "MIDIRX.h"
#include "fm1001.h"

#define _XTAL_FREQ 32000000


__CONFIG(CLKOUTEN_OFF & FOSC_INTOSC & FCMEN_OFF  & IESO_OFF & BOREN_ON & PWRTE_ON
& WDTE_OFF & MCLRE_ON & CP_OFF & CPD_OFF) ;
__CONFIG(PLLEN_ON & STVREN_OFF & WRT_OFF & BORV_LO & LVP_OFF);

unsigned char rxd;

void initSys(void);

void interrupt IRQ()
{
    if(PIR1bits.RCIF == 1)
    {
        rxd = readUART();
        PORTAbits.RA2 = 0;
    }

    return;
}


void main(void)
{

    unsigned char note, och;
    enum MIDI_RX_STATUS state;

    initSys();

    while(1)
    {
        state = 0;
        if(rxd != 0) getMIDI(rxd);
        if(Parse_Done == 1)   state = getMIDIStatus();

        if(state == NOTE_ON)
        {
            note = getNote();
            och = getSendCh(0);
            sendFM(och, note, 1);
            PORTAbits.RA2 = 1;

        }
        else if(state == NOTE_OFF)
        {
            note = getNote();
            och = getSendCh(note);
            sendFM(och, note, 0);
            PORTAbits.RA2 = 1;
        }
    }
}

void initSys()
{
    rxd = 0;
    OSCCON = 0xF0;
    OPTION_REG = 0x07;
    TRISA = 0x28;
    ANSELA = 0;
    INTCONbits.GIE = 1;
    PORTA = 0;
    APFCON=0x80;

    clearMIDI();
    initUART(UART_RX_ONLY);
    initFM(1);

}

