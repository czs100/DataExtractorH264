#pragma once
#include "global.h"

SliceType Find_Slice_type(FILE *Input_File, unsigned char *fileN);
int ReadExpGlomb(char *Bit_stream, int *Offset, int *Bit_offset_to_go);
boolean ReadFlag(char *Bit_stream, int *Offset, int *Bit_offset_to_go);
