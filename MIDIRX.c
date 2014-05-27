/*
 *
 *  MIDI Reciever   Version 0.1
 *  (C) 2014 Kazusa Okuda (a.k.a. klaNath)
 *
 *  This software is freely distributable under the terms of an MIT-style license.
 *  For details, see the https://github.com/klaNath/midiRX.git/LICENSE
 *
 */


#include "MIDIRX.h"
#include <xc.h>
#include "UART.h"

enum DECODE_STATE
{
    NONE,
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

    if(DecodeState == NONE)
    {
        Decoded = 0;
        Parse_Done = 0;
        switch(rxd & 0xF0)
        {
            case    0x90    : DecodeState = NOTE_ON_1;
                                      Decoded.MidiState = NOTE_ON;
                                      Decoded.MidiCh = (rxd & 0xF0) >> 4;
                                      break;
            case    0x80    : DecodeState = NOTE_OFF_1;
                                      Decoded.MidiState = NOTE_OFF;
                                      Decoded.MidiCh = (rxd & 0xF0) >> 4;
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
            default            : DecodeState = NONE;
        }
        if(DecodeState == SYSTEM_F)
        {
            switch(rxd & 0x0F)
            {
                case    0x00    : DecodeState = SYSEX_ON;
                                          Decoded.MidiState = SYSEX;
                                          break;
                case    0x07    : DecodeState = NONE;
                                          break;                            //End of SysEx. goto initial state
                case    0x08    : DecodeState = NONE;
                                          break;                            //timing Clock. this implement has not difine.
                case    0x0E    : DecodeState = NONE;
                                          break;                            //Active Sense. this implement has not difine.
                default            : DecodeState = NONE;
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
                                             DecodeState = NONE;
                                             if(Decoded.MidiVel = 0) Decoded.MidiState = NOTE_OFF;
                                             Parse_Done = 1;
                                             break;
        case    NOTE_OFF_1  : Decoded.MidiNote = rxd;
                                             DecodeState = NOTE_OFF_2;
                                             break;
        case    NOTE_OFF_2  : Decoded.MidiVel = rxd;
                                             DecodeState = NONE;
                                             Parse_Done = 1;
                                             break;
        case    SYSEX_ON      : if(rxd == 0xF7) DecodeState = NONE;
                                             break;
        case    OTHER2_1       : DecodeState = NONE; break;
        case    OTHER3_1       : DecodeState = OTHER3_2; break;
        case    OTHER3_2       : DecodeState = NONE; break;
        default                        : DecodeState = NONE;
    }
    return;
}