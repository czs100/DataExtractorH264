#pragma once
#include "My_Entropy.h"

int ReadPLNZ(int block_y, int block_x, int *cof, int Y, int X);
void ExtractBit(int PLNZ, Macroblock currMB);
int ReadPLNZV(int numcoeff, int *Run);
void ExtractBitV(int PLNZ, Macroblock currMB);
void ExtractBit16(int *lev, Macroblock currMB);