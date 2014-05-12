/*
 *
 *  UART Controller for PIC12F1/16F1   Version 0.1
 *  (C) 2014 Kazusa Okuda (a.k.a. klaNath)
 *
 *  This software is freely distributable under the terms of an MIT-style license.
 *  For details, see the https://github.com/klaNath/midiRX.git/LICENSE
 *
 */


/*
 *
 *  CAUTION!!!!
 * This library implemented only reciev function.
 *
 */


#include <xc.h>


void initUARTRX()
{
    TXSTA = 0;
    RCSTA = 0x90;
    BAUDCON = 0;
    SPBRGL = 3;
}

unsigned char readUART()
{
    unsigned char rslt;

    rslt = RCREG;
}