/*
 *
 *  MIDI Reciever   Version 0.3
 *  (C) 2014 Kazusa Okuda (a.k.a. klaNath)
 *
 *  This software is freely distributable under the terms of an MIT-style license.
 *  For details, see the https://github.com/klaNath/midiRX.git/LICENSE
 *
 */

#include "MIDIRX.h"
//#ifdef __DEBUG
//#include "test.h"
//#endif
#ifndef __DEBUG
#include <xc.h>
#include "UART.h"
#endif

enum DECODE_STATE
{
    INITIAL_STATE,
    NOTE_ON_1,
    NOTE_ON_2,
    NOTE_OFF_1,
    NOTE_OFF_2,
    SYSEX_ON,
    SYSTEM_F,
    OTHER3_1,                                                           //AnH, BnH, EnH first Byte
    OTHER3_2,
    OTHER2_1                                                            //CnH, DnH first Byte
} DecodeState;


struct DECODED_DATA Decoded;

void getMIDI()
{

    unsigned char rxd;

    rxd = readUART();

    if(DecodeState == INITIAL_STATE)
    {
        Parse_Done = 0;
        switch(rxd & 0xF0)
        {
            case    0x90    : DecodeState = NOTE_ON_1;
                                      Decoded.MidiState = NOTE_ON;
                                      Decoded.MidiCh = rxd & 0x0F;
                                      break;
            case    0x80    : DecodeState = NOTE_OFF_1;
                                      Decoded.MidiState = NOTE_OFF;
                                      Decoded.MidiCh = rxd & 0x0F;
                                      break;
            case    0xA0    : DecodeState = OTHER3_1;
                                      break;
            case    0xB0    : DecodeState = OTHER3_1;
                                      break;
            case    0xE0    : DecodeState = OTHER3_1;
                                      break;
            case    0xC0    : DecodeState = OTHER2_1;
                                      break;
            case    0xD0    : DecodeState = OTHER2_1;
                                      break;
            case    0xF0    : DecodeState = SYSTEM_F;
                                      break;
            default            : DecodeState = INITIAL_STATE;
        }
        if(DecodeState == SYSTEM_F)
        {
            switch(rxd & 0x0F)
            {
                case    0x00    : DecodeState = SYSEX_ON;
                                          Decoded.MidiState = SYSEX;
                                          break;
                case    0x07    : DecodeState = INITIAL_STATE;
                                          break;                            //End of SysEx. goto initial state
                case    0x08    : DecodeState = INITIAL_STATE;
                                          break;                            //timing Clock. this implement has not difine.
                case    0x0E    : DecodeState = INITIAL_STATE;
                                          break;                            //Active Sense. this implement has not difine.
                default            : DecodeState = INITIAL_STATE;
            }
        }
        return;
    }
    switch(DecodeState)
    {
        case    NOTE_ON_1   : Decoded.MidiNote = rxd;
                                             DecodeState = NOTE_ON_2;
                                             break;
        case    NOTE_ON_2   : Decoded.MidiVel = rxd;
                                             DecodeState = INITIAL_STATE;
                                             if(Decoded.MidiVel == 0) Decoded.MidiState = NOTE_OFF;
                                             Parse_Done = 1;
                                             break;
        case    NOTE_OFF_1  : Decoded.MidiNote = rxd;
                                             DecodeState = NOTE_OFF_2;
                                             break;
        case    NOTE_OFF_2  : Decoded.MidiVel = rxd;
                                             DecodeState = INITIAL_STATE;
                                             Parse_Done = 1;
                                             break;
        case    SYSEX_ON      : if(rxd == 0xF7) DecodeState = INITIAL_STATE;
                                             break;
        case    OTHER2_1       : DecodeState = INITIAL_STATE; break;
        case    OTHER3_1       : DecodeState = OTHER3_2; break;
        case    OTHER3_2       : DecodeState = INITIAL_STATE; break;
        default                        : DecodeState = INITIAL_STATE;
    }
    return;
}

enum MIDI_RX_STATUS getMIDIStatus()
{
    return(Decoded.MidiState);
}

unsigned char getChannel()
{
    return(Decoded.MidiCh);
}

unsigned char getNote()
{
    return(Decoded.MidiNote);
}

unsigned char getVel()
{
    return(Decoded.MidiVel);
}

void clearMIDI()
{
    Decoded.MidiState = NONE;
    Decoded.MidiNote = 0;
    Decoded.MidiCh = 0;
    Decoded.MidiVel = 0;
    DecodeState = INITIAL_STATE;
    Parse_Done = 0;
}
