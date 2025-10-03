/**
 * @file plib_hcms2902_comm.c
 * @brief Bibliothèque de communication pour l'afficheur HCMS-2902
 * @author Ramiro Najera
 * @version 1.0.1
 * @date 2025-04-23
 * @copyright Copyright (c) 2025
 */

#include "plib_hcms2902_comm.h"

void HCMS2902_GenerateClock(HCMS2902Comm_t *comm)
{
    // Generate clock by setting low, high then low
    comm->pinCLK.Clear();
    Wait100ns(comm->delay);
    comm->pinCLK.Set();
    Wait100ns(comm->delay);
    comm->pinCLK.Clear();
}

void HCMS2902_GenerateInit(HCMS2902Comm_t *comm)
{
    // Init sequence of signals
    comm->pinCE.Set();
    comm->pinCLK.Clear();
    comm->pinDIN.Clear();
}

void HCMS2902_Write(HCMS2902Comm_t *comm, char reg)
{
    // Send each dot of column
    for (unsigned char i = 0; i < HCMS2902_NUM_DOTS_IN_COLUMN; i++)
    {
        // Send MSB bit
        if (reg & HCMS2901_MSB_MASK)
            comm->pinDIN.Set();
        else
            comm->pinDIN.Clear();
        // Generate clock and shift register
        HCMS2902_GenerateClock(comm);
        reg <<= 1;
    }
    comm->pinDIN.Clear();
}

void HCMS2902_WriteArray(HCMS2902Comm_t *comm, char a, char b, char c, char d, char e)
{
    char tempArray[HCMS2902_NUM_COLUMNS] = {a, b, c, d, e};
    // Send each colomn of digit
    for (unsigned char i = 0 ; i < HCMS2902_NUM_COLUMNS; i++)
        HCMS2902_Write(comm, tempArray[i]);
}

void HCMS2902_WriteREG0(HCMS2902Comm_t *comm, char reg)
{
    // Register selection : Reg0
    comm->pinRS.Set();
    Wait100ns(comm->delay);
    // Send register
    comm->pinCE.Clear();
    Wait100ns(comm->delay);
    HCMS2902_Write(comm, reg);
    comm->pinCE.Set(); 
    Wait100ns(comm->delay);
    // Clears clock
    comm->pinCLK.Clear();
    Wait100ns(comm->delay);
    // Register selection : Normal 
    comm->pinRS.Clear();
}

void HCMS2902_WriteBrightness(HCMS2902Comm_t *comm, unsigned char val)
{
    HCMS2902_WriteREG0(comm, (HCMS2901_BRIGHTNESS_MASK + val));
}

void HCMS2902_WriteChar(HCMS2902Comm_t *comm, char c)
{
    switch (c)
    {
        case ' ': HCMS2902_WriteArray(comm, 0x00, 0x00, 0x00, 0x00, 0x00); break;
        case 'A': HCMS2902_WriteArray(comm, 0x7E, 0x09, 0x09, 0x09, 0x7E); break;
        case 'B': HCMS2902_WriteArray(comm, 0x7F, 0x49, 0x49, 0x49, 0x76); break;
        case 'C': HCMS2902_WriteArray(comm, 0x3E, 0x41, 0x41, 0x41, 0x22); break;
        case 'D': HCMS2902_WriteArray(comm, 0x7F, 0x41, 0x41, 0x41, 0x7E); break;
        case 'E': HCMS2902_WriteArray(comm, 0x7F, 0x49, 0x49, 0x49, 0x41); break;
        case 'F': HCMS2902_WriteArray(comm, 0x7F, 0x09, 0x09, 0x09, 0x01); break;
        case 'G': HCMS2902_WriteArray(comm, 0x7E, 0x41, 0x49, 0x49, 0x39); break;
        case 'H': HCMS2902_WriteArray(comm, 0x7F, 0x08, 0x08, 0x08, 0x7F); break;
        case 'I': HCMS2902_WriteArray(comm, 0x00, 0x41, 0x7F, 0x41, 0x00); break;
        case 'J': HCMS2902_WriteArray(comm, 0x00, 0x20, 0x40, 0x40, 0x7F); break;
        case 'K': HCMS2902_WriteArray(comm, 0x7F, 0x08, 0x14, 0x22, 0x41); break;
        case 'L': HCMS2902_WriteArray(comm, 0x7F, 0x40, 0x40, 0x40, 0x40); break;
        case 'M': HCMS2902_WriteArray(comm, 0x7F, 0x02, 0x04, 0x02, 0x7F); break;
        case 'N': HCMS2902_WriteArray(comm, 0x7F, 0x04, 0x08, 0x10, 0x7F); break;
        case 'O': HCMS2902_WriteArray(comm, 0x3E, 0x41, 0x41, 0x41, 0x3E); break;
        case 'P': HCMS2902_WriteArray(comm, 0x7F, 0x09, 0x09, 0x09, 0x07); break;
        case 'Q': HCMS2902_WriteArray(comm, 0x3E, 0x41, 0x51, 0x61, 0x7E); break;
        case 'R': HCMS2902_WriteArray(comm, 0x7F, 0x09, 0x19, 0x29, 0x46); break;
        case 'S': HCMS2902_WriteArray(comm, 0x4F, 0x49, 0x49, 0x49, 0x79); break;
        case 'T': HCMS2902_WriteArray(comm, 0x01, 0x01, 0x7F, 0x01, 0x01); break;
        case 'U': HCMS2902_WriteArray(comm, 0x3F, 0x40, 0x40, 0x40, 0x3F); break;
        case 'V': HCMS2902_WriteArray(comm, 0x1F, 0x20, 0x40, 0x20, 0x1F); break;
        case 'W': HCMS2902_WriteArray(comm, 0x3F, 0x40, 0x30, 0x40, 0x3F); break;
        case 'X': HCMS2902_WriteArray(comm, 0x63, 0x14, 0x08, 0x14, 0x63); break;
        case 'Y': HCMS2902_WriteArray(comm, 0x07, 0x08, 0x78, 0x08, 0x07); break;
        case 'Z': HCMS2902_WriteArray(comm, 0x61, 0x51, 0x49, 0x45, 0x43); break;

        case '0': HCMS2902_WriteArray(comm, 0x3E, 0x41, 0x41, 0x41, 0x3E); break;
        case '1': HCMS2902_WriteArray(comm, 0x00, 0x00, 0x04, 0x02, 0x7F); break;
        case '2': HCMS2902_WriteArray(comm, 0x46, 0x61, 0x51, 0x49, 0x46); break;
        case '3': HCMS2902_WriteArray(comm, 0x22, 0x41, 0x49, 0x49, 0x36); break;
        case '4': HCMS2902_WriteArray(comm, 0x18, 0x14, 0x12, 0x7F, 0x10); break;
        case '5': HCMS2902_WriteArray(comm, 0x27, 0x45, 0x45, 0x45, 0x39); break;
        case '6': HCMS2902_WriteArray(comm, 0x3E, 0x49, 0x49, 0x49, 0x32); break;
        case '7': HCMS2902_WriteArray(comm, 0x01, 0x01, 0x79, 0x05, 0x03); break;
        case '8': HCMS2902_WriteArray(comm, 0x36, 0x49, 0x49, 0x49, 0x36); break;
        case '9': HCMS2902_WriteArray(comm, 0x06, 0x49, 0x49, 0x49, 0x3E); break;

        case '=': HCMS2902_WriteArray(comm, 0x24, 0x24, 0x24, 0x24, 0x24); break;
        case '.': HCMS2902_WriteArray(comm, 0x00, 0x60, 0x60, 0x00, 0x00); break;
        case ':': HCMS2902_WriteArray(comm, 0x00, 0x66, 0x66, 0x00, 0x00); break;
        case '>': HCMS2902_WriteArray(comm, 0x00, 0x41, 0x22, 0x14, 0x08); break;
        case '<': HCMS2902_WriteArray(comm, 0x08, 0x14, 0x22, 0x41, 0x00); break;
        case '/': HCMS2902_WriteArray(comm, 0x20, 0x10, 0x08, 0x04, 0x02); break;
        case '!': HCMS2902_WriteArray(comm, 0x00, 0x00, 0x5F, 0x00, 0x00); break;
        case '|': HCMS2902_WriteArray(comm, 0x00, 0x00, 0x7F, 0x00, 0x00); break;
        case '-': HCMS2902_WriteArray(comm, 0x08, 0x08, 0x08, 0x08, 0x08); break;
        case '+': HCMS2902_WriteArray(comm, 0x08, 0x08, 0x3E, 0x08, 0x08); break;
        case '#': HCMS2902_WriteArray(comm, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF); break;
        default:  HCMS2902_WriteArray(comm, 0x63, 0x14, 0x08, 0x14, 0x63); break;
    }
}

void HCMS2902_WriteText(HCMS2902Comm_t *comm, char* text)
{
    // Register selection : Normal
    comm->pinRS.Clear();
    Wait100ns(comm->delay);
    // Send text (char by char)
    comm->pinCE.Clear();
    Wait100ns(comm->delay);
    for (unsigned char i = 0 ; i < HCMS2902_NUM_DIGITS; i++)
        HCMS2902_WriteChar(comm, text[i]);
    comm->pinCE.Set();
    Wait100ns(comm->delay);
    // Clear clock
    comm->pinCLK.Clear();
    Wait100ns(comm->delay);
    // Clear data in
    comm->pinDIN.Clear();
}