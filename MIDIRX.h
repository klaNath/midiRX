/*
 *
 *  MIDI Reciever   Version 0.3
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


struct DECODED_DATA
{
    enum MIDI_RX_STATUS MidiState;
    unsigned char MidiCh,
                            MidiNote,
                            MidiVel;
};

unsigned char Parse_Done;


void getMIDI(unsigned char);
enum MIDI_RX_STATUS getMIDIStatus();
unsigned char getChannel();
unsigned char getNote();
unsigned char getVel();
void clearMIDI();


#endif