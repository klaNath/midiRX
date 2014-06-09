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
 * This library implemented only recieve function.
 *
 */


#include <xc.h>
#include "UART.h"


void initUART(enum UART_INIT_STATE argv)
{
    if(argv == UART_RX_ONLY)
    {
        BAUDCON = 0;
        SPBRGL = 15;
        INTCONbits.PEIE = 1;
        PIE1bits.RCIE = 1;
        TXSTAbits.SYNC = 0;
        RCSTAbits.SPEN = 1;
        RCSTAbits.CREN = 1;
    }
    else
    {
        return;
    }

    return;
}

unsigned char readUART()
{
    unsigned char RXData;
    
    RXData = RCREG;
    if(RCSTAbits.OERR == 1)
    {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
        return(0);
    }
    return(RXData);
}
