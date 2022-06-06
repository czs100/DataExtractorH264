#include "Data_Extractor.h"

int ReadPLNZ(int block_y, int block_x, int *cof, int Y, int X)
{
	int coeffcount = 0;
	int i;
	int tempC;
	int PLNZ = 0;
	for (i = 0; i < 16; i++)
	{
		tempC = cof[block_y * 32 + block_x * 16 + i];
		if (tempC)
		{
			PLNZ = i + 1;
		}
	}
	return PLNZ;
}

void ExtractBit(int PLNZ, Macroblock currMB)
{
	if (I_finish == 0)
	{
		if ((PLNZ % 2) == 0)
			BitBuffer++;
		else
		{
			MD_Buffer |= 1 << (7 - BitBuffer);
			BitBuffer++;
		}
		if (BitBuffer == 8)
		{
			switch (MD_State)
			{
			case 0:
				if (MD_Buffer != '$')
					Err = 1;
				else
					MD_State++;
				break;
			case 1:
				EMD_NUM = MD_Buffer << 8;
				MD_State++;
				break;
			case 2:
				EMD_NUM |= MD_Buffer;
				if (EMD_NUM == MD_NUM)
				{
					if (EMD_NUM == MD_Ext)
						processingMode = 1;
					MD_State++;
				}
				else
					Err = 2;
				break;
			case 3:
				if (MD_Buffer != '$')
					Err = 1;
				else
					MD_State++;
				break;
			case 4:
				MDSIZE |= MD_Buffer << 24;
				MD_State++;
				break;
			case 5:
				MDSIZE |= MD_Buffer << 16;
				MD_State++;
				break;
			case 6:
				MDSIZE |= MD_Buffer << 8;
				MD_State++;
				break;
			case 7:
				MDSIZE |= MD_Buffer;
				MD_State++;
				case4 = 1;
				break;
			case 8:
				case4 = 0;
				MDSIZE--;
				if (MDSIZE == 0)
				{
					if (processingMode)
					{
						I_finish = 1;
						processingMode = 0;
						fwrite(&MD_Buffer, 1, 1, Output_MD);
					}
					MD_NUM++;
					MD_State = 0;
					Allow_MB = currMB.mbAddrX + 1;
					if (EMD_NUM == endInfo.MetaDataNum - 1)
						I_finish = 1;
				}
				break;
			default:
				break;
			}
			if ((processingMode) && (case4 == 0) && (MD_State == 8))
			{
				fwrite(&MD_Buffer, 1, 1, Output_MD);
			}
			BitBuffer = 0;
			MD_Buffer = 0;
		}
	}
}

int ReadPLNZV(int numcoeff, int *Run)
{
	int i;
	int PLNZ = numcoeff;
	int *Rn = Run;
	for (i = 0; i <= numcoeff; i++)
	{
		PLNZ += *Rn++;
	}
	return PLNZ;
}

void ExtractBitV(int PLNZ, Macroblock currMB)
{
	if (I_finish == 0)
	{
		if ((PLNZ % 2) == 0)
			BitBuffer++;
		else
		{
			MD_Buffer |= 1 << (7 - BitBuffer);
			BitBuffer++;
		}
		if (BitBuffer == 8)
		{
			switch (MD_State)
			{
			case 0:
				if (MD_Buffer != '$')
					Err = 1;
				else
					MD_State++;
				break;
			case 1:
				EMD_NUM = MD_Buffer << 8;
				MD_State++;
				break;
			case 2:
				EMD_NUM |= MD_Buffer;
				if (EMD_NUM == MD_NUM)
				{
					if (EMD_NUM == MD_Ext)
						processingMode = 1;
					MD_State++;
				}
				else
					Err = 2;
				break;
			case 3:
				if (MD_Buffer != '$')
					Err = 1;
				else
					MD_State++;
				break;
			case 4:
				MDSIZE |= MD_Buffer << 24;
				MD_State++;
				break;
			case 5:
				MDSIZE |= MD_Buffer << 16;
				MD_State++;
				break;
			case 6:
				MDSIZE |= MD_Buffer << 8;
				MD_State++;
				break;
			case 7:
				MDSIZE |= MD_Buffer;
				MD_State++;
				case4 = 1;
				break;
			case 8:
				case4 = 0;
				MDSIZE--;
				if (MDSIZE == 0)
				{
					if (processingMode)
					{
						I_finish = 1;
						processingMode = 0;
					}
					MD_NUM++;
					MD_State = 0;
					Allow_MB = currMB.mbAddrX + 1;
					if (EMD_NUM == endInfo.MetaDataNum - 1)
						I_finish = 1;
				}
				break;
			default:
				break;
			}
			if ((processingMode) && (case4 == 0) && (MD_State == 8))
			{
				fwrite(&MD_Buffer, 1, 1, Output_MD);
			}
			BitBuffer = 0;
			MD_Buffer = 0;
		}
	}
}
void ExtractBit16(int *lev, Macroblock currMB)
{
	if (I_finish == 0)
	{
		if (lev[15] < 0)
			BitBuffer++;
		else
		{
			MD_Buffer |= 1 << (7 - BitBuffer);
			BitBuffer++;
		}
		if (BitBuffer == 8)
		{
			switch (MD_State)
			{
			case 0:
				if (MD_Buffer != '$')
					Err = 1;
				else
					MD_State++;
				break;
			case 1:
				EMD_NUM = MD_Buffer << 8;
				MD_State++;
				break;
			case 2:
				EMD_NUM |= MD_Buffer;
				if (EMD_NUM == MD_NUM)
				{
					if (EMD_NUM == MD_Ext)
						processingMode = 1;
					MD_State++;
				}
				else
					Err = 2;
				break;
			case 3:
				if (MD_Buffer != '$')
					Err = 1;
				else
					MD_State++;
				break;
			case 4:
				MDSIZE |= MD_Buffer << 24;
				MD_State++;
				break;
			case 5:
				MDSIZE |= MD_Buffer << 16;
				MD_State++;
				break;
			case 6:
				MDSIZE |= MD_Buffer << 8;
				MD_State++;
				break;
			case 7:
				MDSIZE |= MD_Buffer;
				MD_State++;
				case4 = 1;
				break;
			case 8:
				case4 = 0;
				MDSIZE--;
				if (MDSIZE == 0)
				{
					if (processingMode)
					{
						I_finish = 1;
						processingMode = 0;
					}
					MD_NUM++;
					MD_State = 0;
					Allow_MB = currMB.mbAddrX + 1;
					if (EMD_NUM == endInfo.MetaDataNum - 1)
						I_finish = 1;
				}
				break;
			default:
				break;
			}
			if ((processingMode) && (case4 == 0) && (MD_State == 8))
			{
				fwrite(&MD_Buffer, 1, 1, Output_MD);
			}
			BitBuffer = 0;
			MD_Buffer = 0;
		}
	}
}