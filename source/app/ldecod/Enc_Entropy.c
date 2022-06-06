#include "My_Entropy.h"

int ReadExpGlomb(char *Bit_stream, int *Offset, int *Bit_offset_to_go)
{
	int M = 0, i = *Offset;
	int Output = 0;
	while (!ReadFlag(Bit_stream, &i, Bit_offset_to_go))
	{
		M++;
	}
	for (int j = 0; j < M; j++)
	{
		Output |= ReadFlag(Bit_stream, &i, Bit_offset_to_go) << (M - 1 - j);
	}
	*Offset = i;
	return Output + (int)pow(2, M) - 1;
}
boolean ReadFlag(char *Bit_stream, int *Offset, int *Bit_offset_to_go)
{
	boolean Output;
	int i = *Offset;
	if (*Bit_offset_to_go == 0)
	{
		*Bit_offset_to_go = 8;
		i++;
	}
	Output = ((Bit_stream[i] & (1 << ((*Bit_offset_to_go) - 1))) != 0);
	(*Bit_offset_to_go)--;
	*Offset = i;
	return Output;
}
SliceType Find_Slice_type(FILE *Input_File, unsigned char *fileN)
{
	SliceType slice_type = 5;
	int startcode = 0, IFrame = 0, PFrame = 0;
	while (slice_type == 5)
	{
		if (!fread(fileN, 1, 256, Input_File))
			return (PFrame ? P_SLICE : I_SLICE);
		for (int i = 0; i < 256; i++)
		{
			if (startcode == 5)
			{
				if (((fileN[i] & 0x7c) == 0x18) || ((fileN[i] & 0x40) == 0x40))					//Pframe
				{
					PFrame = 1;
				}
				else if (((fileN[i] & 0x7c) == 0x1c) || ((fileN[i] & 0x70) == 0x20))			//Bframe
				{
					slice_type = B_SLICE;
					break;
				}
				else if (((fileN[i] & 0x7F) == 0x8) || ((fileN[i] & 0x70) == 0x30))			//Iframe
				{
					if (!IFrame)
						IFrame = 1;
					else
					{
						slice_type = PFrame ? P_SLICE : I_SLICE;
						break;
					}
				}
				startcode = 0;
			}
			if ((startcode == 4) && (((fileN[i] & 0x0F) == 0x5) || ((fileN[i] & 0x0F) == 0x1)))		//IDR or non-IDR
				startcode++;
			if ((fileN[i] == 0) && (startcode < 3))
				startcode++;
			else if ((fileN[i] != 0) && (fileN[i] != 1) && (startcode != 5))
				startcode = 0;
			else if ((fileN[i] == 1) && ((startcode == 3) || (startcode == 2)))
				startcode = 4;
		}
	}
	return slice_type;
}
