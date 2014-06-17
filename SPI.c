/*
 *
 *  SPI Controller for PIC12F1/16F1   Version 0.1
 *  (C) 2014 Kazusa Okuda (a.k.a. klaNath)
 *
 *  This software is freely distributable under the terms of an MIT-style license.
 *  For details, see the https://github.com/klaNath/midiRX.git/LICENSE
 *
 */

#include <xc.h>


void initSPI(enum SPI_INIT_STATE initstate)
{
    switch(initstate)
    {
    case SPI_MASTER:    SSP1STAT = 0;
                        SSP1CON1bits.SSPM0 = 1;
                        SSP1CON1bits.SSPEN = 1;
                        break;
    case SPI_NONE:      SSP1CON1 = 0;
                        break;
    default:            break;
    }
}

unsigned char getSPI()
{
    return SSP1BUF;
}

void sendSingleSPI(unsigned char txd)
{
    SSP1BUF = txd;
    while(SSP1STATbits.BF != 1) NOP();
}

void sendMultiSPI(unsigned char* txd, unsigned char num)
{
    char i = 0;

    while(num != 0)
    {
        sendSingleSPI(txd[i]);
        i++;
        num--;
    }
}