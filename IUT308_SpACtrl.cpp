#include "Stdafx.h"
#include "Global.h"
#include "Thread.h"
u8 g_IUT308_SpAOneLinePixel_temp[44][8];

void IUT308_getSpAOneLineData(char Type)
{
	int i, j, k1, k2;
	if (0 == Type)
	{
		for (i = 0; i<44; i++)
		{
			for (j = 0; j<8; j++)
			{
				g_IUT308_SpAOneLinePixel[i][j] = 0;
			}
		}
	}
	else if (1 == Type)
	{
		for (i = 0; i < 14; i++) //奇数列
		{
			if (i < 7)
			{
				k1 = i;
				k2 = 0;
			}
			else
			{
				k1 = i - 7;
				k2 = 22;
			}

			g_IUT308_SpAOneLinePixel_temp[k2 + 14][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 0)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 7][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 1)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 0][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 2)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 15][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 3)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 8][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 4)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 1][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 5)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 16][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 6)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 9][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 7)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 2][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 8)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 17][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 9)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 10][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 10)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 3][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 11)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 18][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 12)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 11][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 13)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 4][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 14)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 19][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 15)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 12][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 16)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 5][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 17)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 20][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 18)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 13][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 19)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 6][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 20)];
			g_IUT308_SpAOneLinePixel_temp[k2 + 21][k1] = g_IUT308_001To308Pixel[307 - (22 * i + 21)];
		}


		for (j = 0; j < 22; j++) //奇数列
		{
			g_IUT308_SpAOneLinePixel[j][0] = g_IUT308_SpAOneLinePixel_temp[j + 22][3]; //P11
			g_IUT308_SpAOneLinePixel[j][1] = g_IUT308_SpAOneLinePixel_temp[j + 22][4]; //P12
			g_IUT308_SpAOneLinePixel[j][2] = g_IUT308_SpAOneLinePixel_temp[j + 22][5]; //P13
			g_IUT308_SpAOneLinePixel[j][3] = g_IUT308_SpAOneLinePixel_temp[j + 22][6]; //P14
			g_IUT308_SpAOneLinePixel[j][4] = g_IUT308_SpAOneLinePixel_temp[j + 22][0]; //P8
			g_IUT308_SpAOneLinePixel[j][5] = g_IUT308_SpAOneLinePixel_temp[j + 22][1]; //P9
			g_IUT308_SpAOneLinePixel[j][6] = g_IUT308_SpAOneLinePixel_temp[j + 22][2]; //P10
			g_IUT308_SpAOneLinePixel[j][7] = 0;
		}

		for (j = 22; j < 44; j++) //偶数列
		{
			g_IUT308_SpAOneLinePixel[j][0] = g_IUT308_SpAOneLinePixel_temp[j - 22][2];
			g_IUT308_SpAOneLinePixel[j][1] = g_IUT308_SpAOneLinePixel_temp[j - 22][1];
			g_IUT308_SpAOneLinePixel[j][2] = g_IUT308_SpAOneLinePixel_temp[j - 22][0];
			g_IUT308_SpAOneLinePixel[j][3] = g_IUT308_SpAOneLinePixel_temp[j - 22][6];
			g_IUT308_SpAOneLinePixel[j][4] = g_IUT308_SpAOneLinePixel_temp[j - 22][5];
			g_IUT308_SpAOneLinePixel[j][5] = g_IUT308_SpAOneLinePixel_temp[j - 22][4];
			g_IUT308_SpAOneLinePixel[j][6] = g_IUT308_SpAOneLinePixel_temp[j - 22][3];
			g_IUT308_SpAOneLinePixel[j][7] = 0;
		}

	}
}

//g_SpAOneLinePixelZipped
//g_SpBOneLinePixelZipped
void IUT308_ZipSpData() //压缩SpA,SpB数据
{
	int i, j;
	for (i = 0; i<44; i++)
	{
		g_SpAOneLinePixelZipped[i] = 0;
		g_SpBOneLinePixelZipped[i] = 0;
		for (j = 0; j<8; j++)
		{
			if (1 == g_IUT308_SpAOneLinePixel[i][j])
			{
				g_SpAOneLinePixelZipped[i] |= (1 << j);
			}
			if (1 == g_IUT308_SpBOneLinePixel[i][j])
			{
				g_SpBOneLinePixelZipped[i] |= (1 << j);
			}
		}
	}
}
