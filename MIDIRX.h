/*
 *
 *  MIDI Reciever   Version 0.1
 *  (C) 2014 Kazusa Okuda (a.k.a. klaNath)
 *
 *  This software is freely distributable under the terms of an MIT-style license.
 *  For details, see the https://github.com/klaNath/midiRX.git/LICENSE
 *
 */

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


void inputMIDI(unsigned char*);
int readMIDI();
void clearMIDI();






#endif