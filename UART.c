/*
 *
 *  UART Controller for PIC12F1/16F1   Version 0.2
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
#include "UART.h"


void initUART(enum UART_INIT_STATE argv)
{
    if(argv == UART_RX_ONLY)
    {
        TXSTA = 0;
        RCSTA = 0x90;
        BAUDCON = 0;
        SPBRGL = 15;
    }
    else
    {
        return;
    }
}

unsigned char readUART()
{
    return(RCREG);
}