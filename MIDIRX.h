/*
 *
 *  MIDI Reciever   Version 0.2
 *  (C) 2014 Kazusa Okuda (a.k.a. klaNath)
 *
 *  This software is freely distributable under the terms of an MIT-style license.
 *  For details, see the https://github.com/klaNath/midiRX.git/LICENSE
 *
 */
#include "UART.h"
#include <xc.h>


#ifndef _MIDIRX_H
#define _MIDIRX_H

enum MIDI_RX_STATUS
{
    NONE,
    NOTE_ON,
    NOTE_OFF,
    ACTSENSE,
    SYSEX,
    OTHER
};

enum MIDI_BUF_STATUS
{
    EMPTY,
    VALID,
    FULL
};


void getMIDI();
unsigned char validMIDI();
unsigned char getStatus();
unsigned char getNote();
unsigned char getVel();
void clearMIDI();

unsigned char statusMIDI();


#endif