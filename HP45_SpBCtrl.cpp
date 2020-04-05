#include "Stdafx.h"
#include "Global.h"
#include "Thread.h"

void HP45_getSpBOneLineData(char Type)
{
	if (0==Type) //µ•≈Á—°‘Ò1#≈ÁÕ∑
	{
		int i,j;
		for (i=0;i<22;i++)
		{
			for (j=0;j<8;j++)
			{
				g_HP45_SpBOneLinePixel[i][j] = 0;
			}
		}
	}
	else if (1==Type) //
	{
		g_HP45_SpBOneLinePixel[0][0] = g_Hp45_000To150Pixel[0];
		g_HP45_SpBOneLinePixel[0][1] = g_Hp45_000To150Pixel[22];
		g_HP45_SpBOneLinePixel[0][2] = g_Hp45_000To150Pixel[44];
		g_HP45_SpBOneLinePixel[0][3] = g_Hp45_000To150Pixel[66];
		g_HP45_SpBOneLinePixel[0][4] = g_Hp45_000To150Pixel[88];
		g_HP45_SpBOneLinePixel[0][5] = g_Hp45_000To150Pixel[110];
		g_HP45_SpBOneLinePixel[0][6] = g_Hp45_000To150Pixel[132];
		g_HP45_SpBOneLinePixel[0][7] = 0;

		g_HP45_SpBOneLinePixel[1][0] = g_Hp45_000To150Pixel[3];
		g_HP45_SpBOneLinePixel[1][1] = g_Hp45_000To150Pixel[25];
		g_HP45_SpBOneLinePixel[1][2] = g_Hp45_000To150Pixel[47];
		g_HP45_SpBOneLinePixel[1][3] = g_Hp45_000To150Pixel[69];
		g_HP45_SpBOneLinePixel[1][4] = g_Hp45_000To150Pixel[91];
		g_HP45_SpBOneLinePixel[1][5] = g_Hp45_000To150Pixel[113];
		g_HP45_SpBOneLinePixel[1][6] = g_Hp45_000To150Pixel[135];
		g_HP45_SpBOneLinePixel[1][7] = 0;

		g_HP45_SpBOneLinePixel[2][0] = g_Hp45_000To150Pixel[6];
		g_HP45_SpBOneLinePixel[2][1] = g_Hp45_000To150Pixel[28];
		g_HP45_SpBOneLinePixel[2][2] = g_Hp45_000To150Pixel[50];
		g_HP45_SpBOneLinePixel[2][3] = g_Hp45_000To150Pixel[72];
		g_HP45_SpBOneLinePixel[2][4] = g_Hp45_000To150Pixel[94];
		g_HP45_SpBOneLinePixel[2][5] = g_Hp45_000To150Pixel[116];
		g_HP45_SpBOneLinePixel[2][6] = g_Hp45_000To150Pixel[138];
		g_HP45_SpBOneLinePixel[2][7] = 0;

		g_HP45_SpBOneLinePixel[3][0] = g_Hp45_000To150Pixel[9];
		g_HP45_SpBOneLinePixel[3][1] = g_Hp45_000To150Pixel[31];
		g_HP45_SpBOneLinePixel[3][2] = g_Hp45_000To150Pixel[53];
		g_HP45_SpBOneLinePixel[3][3] = g_Hp45_000To150Pixel[75];
		g_HP45_SpBOneLinePixel[3][4] = g_Hp45_000To150Pixel[97];
		g_HP45_SpBOneLinePixel[3][5] = g_Hp45_000To150Pixel[119];
		g_HP45_SpBOneLinePixel[3][6] = g_Hp45_000To150Pixel[141];
		g_HP45_SpBOneLinePixel[3][7] = 0;

		g_HP45_SpBOneLinePixel[4][0] = g_Hp45_000To150Pixel[12];
		g_HP45_SpBOneLinePixel[4][1] = g_Hp45_000To150Pixel[34];
		g_HP45_SpBOneLinePixel[4][2] = g_Hp45_000To150Pixel[56];
		g_HP45_SpBOneLinePixel[4][3] = g_Hp45_000To150Pixel[78];
		g_HP45_SpBOneLinePixel[4][4] = g_Hp45_000To150Pixel[100];
		g_HP45_SpBOneLinePixel[4][5] = g_Hp45_000To150Pixel[122];
		g_HP45_SpBOneLinePixel[4][6] = g_Hp45_000To150Pixel[144];
		g_HP45_SpBOneLinePixel[4][7] = 0;

		g_HP45_SpBOneLinePixel[5][0] = g_Hp45_000To150Pixel[15];
		g_HP45_SpBOneLinePixel[5][1] = g_Hp45_000To150Pixel[37];
		g_HP45_SpBOneLinePixel[5][2] = g_Hp45_000To150Pixel[59];
		g_HP45_SpBOneLinePixel[5][3] = g_Hp45_000To150Pixel[81];
		g_HP45_SpBOneLinePixel[5][4] = g_Hp45_000To150Pixel[103];
		g_HP45_SpBOneLinePixel[5][5] = g_Hp45_000To150Pixel[125];
		g_HP45_SpBOneLinePixel[5][6] = g_Hp45_000To150Pixel[147];
		g_HP45_SpBOneLinePixel[5][7] = 0;

		g_HP45_SpBOneLinePixel[6][0] = g_Hp45_000To150Pixel[18];
		g_HP45_SpBOneLinePixel[6][1] = g_Hp45_000To150Pixel[40];
		g_HP45_SpBOneLinePixel[6][2] = g_Hp45_000To150Pixel[62];
		g_HP45_SpBOneLinePixel[6][3] = g_Hp45_000To150Pixel[84];
		g_HP45_SpBOneLinePixel[6][4] = g_Hp45_000To150Pixel[106];
		g_HP45_SpBOneLinePixel[6][5] = g_Hp45_000To150Pixel[128];
		g_HP45_SpBOneLinePixel[6][6] = 0;
		g_HP45_SpBOneLinePixel[6][7] = 0;
		
		g_HP45_SpBOneLinePixel[7][0] = 0;
		g_HP45_SpBOneLinePixel[7][1] = g_Hp45_000To150Pixel[21];
		g_HP45_SpBOneLinePixel[7][2] = g_Hp45_000To150Pixel[43];
		g_HP45_SpBOneLinePixel[7][3] = g_Hp45_000To150Pixel[65];
		g_HP45_SpBOneLinePixel[7][4] = g_Hp45_000To150Pixel[87];
		g_HP45_SpBOneLinePixel[7][5] = g_Hp45_000To150Pixel[109];
		g_HP45_SpBOneLinePixel[7][6] = g_Hp45_000To150Pixel[131];
		g_HP45_SpBOneLinePixel[7][7] = 0;
		
		g_HP45_SpBOneLinePixel[8][0] = g_Hp45_000To150Pixel[2];
		g_HP45_SpBOneLinePixel[8][1] = g_Hp45_000To150Pixel[24];
		g_HP45_SpBOneLinePixel[8][2] = g_Hp45_000To150Pixel[46];
		g_HP45_SpBOneLinePixel[8][3] = g_Hp45_000To150Pixel[68];
		g_HP45_SpBOneLinePixel[8][4] = g_Hp45_000To150Pixel[90];
		g_HP45_SpBOneLinePixel[8][5] = g_Hp45_000To150Pixel[112];
		g_HP45_SpBOneLinePixel[8][6] = g_Hp45_000To150Pixel[134];
		g_HP45_SpBOneLinePixel[8][7] = 0;
		
		g_HP45_SpBOneLinePixel[9][0] = g_Hp45_000To150Pixel[5];
		g_HP45_SpBOneLinePixel[9][1] = g_Hp45_000To150Pixel[27];
		g_HP45_SpBOneLinePixel[9][2] = g_Hp45_000To150Pixel[49];
		g_HP45_SpBOneLinePixel[9][3] = g_Hp45_000To150Pixel[71];
		g_HP45_SpBOneLinePixel[9][4] = g_Hp45_000To150Pixel[93];
		g_HP45_SpBOneLinePixel[9][5] = g_Hp45_000To150Pixel[115];
		g_HP45_SpBOneLinePixel[9][6] = g_Hp45_000To150Pixel[137];
		g_HP45_SpBOneLinePixel[9][7] = 0;
		
		g_HP45_SpBOneLinePixel[10][0] = g_Hp45_000To150Pixel[8];
		g_HP45_SpBOneLinePixel[10][1] = g_Hp45_000To150Pixel[30];
		g_HP45_SpBOneLinePixel[10][2] = g_Hp45_000To150Pixel[52];
		g_HP45_SpBOneLinePixel[10][3] = g_Hp45_000To150Pixel[74];
		g_HP45_SpBOneLinePixel[10][4] = g_Hp45_000To150Pixel[96];
		g_HP45_SpBOneLinePixel[10][5] = g_Hp45_000To150Pixel[118];
		g_HP45_SpBOneLinePixel[10][6] = g_Hp45_000To150Pixel[140];
		g_HP45_SpBOneLinePixel[10][7] = 0;
		
		g_HP45_SpBOneLinePixel[11][0] = g_Hp45_000To150Pixel[11];
		g_HP45_SpBOneLinePixel[11][1] = g_Hp45_000To150Pixel[33];
		g_HP45_SpBOneLinePixel[11][2] = g_Hp45_000To150Pixel[55];
		g_HP45_SpBOneLinePixel[11][3] = g_Hp45_000To150Pixel[77];
		g_HP45_SpBOneLinePixel[11][4] = g_Hp45_000To150Pixel[99];
		g_HP45_SpBOneLinePixel[11][5] = g_Hp45_000To150Pixel[121];
		g_HP45_SpBOneLinePixel[11][6] = g_Hp45_000To150Pixel[143];
		g_HP45_SpBOneLinePixel[11][7] = 0;
		
		g_HP45_SpBOneLinePixel[12][0] = g_Hp45_000To150Pixel[14];
		g_HP45_SpBOneLinePixel[12][1] = g_Hp45_000To150Pixel[36];
		g_HP45_SpBOneLinePixel[12][2] = g_Hp45_000To150Pixel[58];
		g_HP45_SpBOneLinePixel[12][3] = g_Hp45_000To150Pixel[80];
		g_HP45_SpBOneLinePixel[12][4] = g_Hp45_000To150Pixel[102];
		g_HP45_SpBOneLinePixel[12][5] = g_Hp45_000To150Pixel[124];
		g_HP45_SpBOneLinePixel[12][6] = g_Hp45_000To150Pixel[146];
		g_HP45_SpBOneLinePixel[12][7] = 0;
		
		g_HP45_SpBOneLinePixel[13][0] = g_Hp45_000To150Pixel[17];
		g_HP45_SpBOneLinePixel[13][1] = g_Hp45_000To150Pixel[39];
		g_HP45_SpBOneLinePixel[13][2] = g_Hp45_000To150Pixel[61];
		g_HP45_SpBOneLinePixel[13][3] = g_Hp45_000To150Pixel[83];
		g_HP45_SpBOneLinePixel[13][4] = g_Hp45_000To150Pixel[105];
		g_HP45_SpBOneLinePixel[13][5] = g_Hp45_000To150Pixel[127];
		g_HP45_SpBOneLinePixel[13][6] = g_Hp45_000To150Pixel[149];
		g_HP45_SpBOneLinePixel[13][7] = 0;
		
		g_HP45_SpBOneLinePixel[14][0] = 0;
		g_HP45_SpBOneLinePixel[14][1] = g_Hp45_000To150Pixel[20];
		g_HP45_SpBOneLinePixel[14][2] = g_Hp45_000To150Pixel[42];
		g_HP45_SpBOneLinePixel[14][3] = g_Hp45_000To150Pixel[64];
		g_HP45_SpBOneLinePixel[14][4] = g_Hp45_000To150Pixel[86];
		g_HP45_SpBOneLinePixel[14][5] = g_Hp45_000To150Pixel[108];
		g_HP45_SpBOneLinePixel[14][6] = g_Hp45_000To150Pixel[130];
		g_HP45_SpBOneLinePixel[14][7] = 0;
		
		g_HP45_SpBOneLinePixel[15][0] = g_Hp45_000To150Pixel[1];
		g_HP45_SpBOneLinePixel[15][1] = g_Hp45_000To150Pixel[23];
		g_HP45_SpBOneLinePixel[15][2] = g_Hp45_000To150Pixel[45];
		g_HP45_SpBOneLinePixel[15][3] = g_Hp45_000To150Pixel[67];
		g_HP45_SpBOneLinePixel[15][4] = g_Hp45_000To150Pixel[89];
		g_HP45_SpBOneLinePixel[15][5] = g_Hp45_000To150Pixel[111];
		g_HP45_SpBOneLinePixel[15][6] = g_Hp45_000To150Pixel[133];
		g_HP45_SpBOneLinePixel[15][7] = 0;
		
		g_HP45_SpBOneLinePixel[16][0] = g_Hp45_000To150Pixel[4];
		g_HP45_SpBOneLinePixel[16][1] = g_Hp45_000To150Pixel[26];
		g_HP45_SpBOneLinePixel[16][2] = g_Hp45_000To150Pixel[48];
		g_HP45_SpBOneLinePixel[16][3] = g_Hp45_000To150Pixel[70];
		g_HP45_SpBOneLinePixel[16][4] = g_Hp45_000To150Pixel[92];
		g_HP45_SpBOneLinePixel[16][5] = g_Hp45_000To150Pixel[114];
		g_HP45_SpBOneLinePixel[16][6] = g_Hp45_000To150Pixel[136];
		g_HP45_SpBOneLinePixel[16][7] = 0;
		
		g_HP45_SpBOneLinePixel[17][0] = g_Hp45_000To150Pixel[7];
		g_HP45_SpBOneLinePixel[17][1] = g_Hp45_000To150Pixel[29];
		g_HP45_SpBOneLinePixel[17][2] = g_Hp45_000To150Pixel[51];
		g_HP45_SpBOneLinePixel[17][3] = g_Hp45_000To150Pixel[73];
		g_HP45_SpBOneLinePixel[17][4] = g_Hp45_000To150Pixel[95];
		g_HP45_SpBOneLinePixel[17][5] = g_Hp45_000To150Pixel[117];
		g_HP45_SpBOneLinePixel[17][6] = g_Hp45_000To150Pixel[139];
		g_HP45_SpBOneLinePixel[17][7] = 0;
		
		g_HP45_SpBOneLinePixel[18][0] = g_Hp45_000To150Pixel[10];
		g_HP45_SpBOneLinePixel[18][1] = g_Hp45_000To150Pixel[32];
		g_HP45_SpBOneLinePixel[18][2] = g_Hp45_000To150Pixel[54];
		g_HP45_SpBOneLinePixel[18][3] = g_Hp45_000To150Pixel[76];
		g_HP45_SpBOneLinePixel[18][4] = g_Hp45_000To150Pixel[98];
		g_HP45_SpBOneLinePixel[18][5] = g_Hp45_000To150Pixel[120];
		g_HP45_SpBOneLinePixel[18][6] = g_Hp45_000To150Pixel[142];
		g_HP45_SpBOneLinePixel[18][7] = 0;
		
		g_HP45_SpBOneLinePixel[19][0] = g_Hp45_000To150Pixel[13];
		g_HP45_SpBOneLinePixel[19][1] = g_Hp45_000To150Pixel[35];
		g_HP45_SpBOneLinePixel[19][2] = g_Hp45_000To150Pixel[57];
		g_HP45_SpBOneLinePixel[19][3] = g_Hp45_000To150Pixel[79];
		g_HP45_SpBOneLinePixel[19][4] = g_Hp45_000To150Pixel[101];
		g_HP45_SpBOneLinePixel[19][5] = g_Hp45_000To150Pixel[123];
		g_HP45_SpBOneLinePixel[19][6] = g_Hp45_000To150Pixel[145];
		g_HP45_SpBOneLinePixel[19][7] = 0;

		g_HP45_SpBOneLinePixel[20][0] = g_Hp45_000To150Pixel[16];
		g_HP45_SpBOneLinePixel[20][1] = g_Hp45_000To150Pixel[38];
		g_HP45_SpBOneLinePixel[20][2] = g_Hp45_000To150Pixel[60];
		g_HP45_SpBOneLinePixel[20][3] = g_Hp45_000To150Pixel[82];
		g_HP45_SpBOneLinePixel[20][4] = g_Hp45_000To150Pixel[104];
		g_HP45_SpBOneLinePixel[20][5] = g_Hp45_000To150Pixel[126];
		g_HP45_SpBOneLinePixel[20][6] = g_Hp45_000To150Pixel[148];
		g_HP45_SpBOneLinePixel[20][7] = 0;
		
		g_HP45_SpBOneLinePixel[21][0] = g_Hp45_000To150Pixel[19];
		g_HP45_SpBOneLinePixel[21][1] = g_Hp45_000To150Pixel[41];
		g_HP45_SpBOneLinePixel[21][2] = g_Hp45_000To150Pixel[63];
		g_HP45_SpBOneLinePixel[21][3] = g_Hp45_000To150Pixel[85];
		g_HP45_SpBOneLinePixel[21][4] = g_Hp45_000To150Pixel[107];
		g_HP45_SpBOneLinePixel[21][5] = g_Hp45_000To150Pixel[129];
		g_HP45_SpBOneLinePixel[21][6] = 0;
		g_HP45_SpBOneLinePixel[21][7] = 0;
	}
	else if (2==Type)
	{
		g_HP45_SpBOneLinePixel[0][0] = g_Hp45_150To300Pixel[0];
		g_HP45_SpBOneLinePixel[0][1] = g_Hp45_150To300Pixel[22];
		g_HP45_SpBOneLinePixel[0][2] = g_Hp45_150To300Pixel[44];
		g_HP45_SpBOneLinePixel[0][3] = g_Hp45_150To300Pixel[66];
		g_HP45_SpBOneLinePixel[0][4] = g_Hp45_150To300Pixel[88];
		g_HP45_SpBOneLinePixel[0][5] = g_Hp45_150To300Pixel[110];
		g_HP45_SpBOneLinePixel[0][6] = g_Hp45_150To300Pixel[132];
		g_HP45_SpBOneLinePixel[0][7] = 0;

		g_HP45_SpBOneLinePixel[1][0] = g_Hp45_150To300Pixel[3];
		g_HP45_SpBOneLinePixel[1][1] = g_Hp45_150To300Pixel[25];
		g_HP45_SpBOneLinePixel[1][2] = g_Hp45_150To300Pixel[47];
		g_HP45_SpBOneLinePixel[1][3] = g_Hp45_150To300Pixel[69];
		g_HP45_SpBOneLinePixel[1][4] = g_Hp45_150To300Pixel[91];
		g_HP45_SpBOneLinePixel[1][5] = g_Hp45_150To300Pixel[113];
		g_HP45_SpBOneLinePixel[1][6] = g_Hp45_150To300Pixel[135];
		g_HP45_SpBOneLinePixel[1][7] = 0;

		g_HP45_SpBOneLinePixel[2][0] = g_Hp45_150To300Pixel[6];
		g_HP45_SpBOneLinePixel[2][1] = g_Hp45_150To300Pixel[28];
		g_HP45_SpBOneLinePixel[2][2] = g_Hp45_150To300Pixel[50];
		g_HP45_SpBOneLinePixel[2][3] = g_Hp45_150To300Pixel[72];
		g_HP45_SpBOneLinePixel[2][4] = g_Hp45_150To300Pixel[94];
		g_HP45_SpBOneLinePixel[2][5] = g_Hp45_150To300Pixel[116];
		g_HP45_SpBOneLinePixel[2][6] = g_Hp45_150To300Pixel[138];
		g_HP45_SpBOneLinePixel[2][7] = 0;

		g_HP45_SpBOneLinePixel[3][0] = g_Hp45_150To300Pixel[9];
		g_HP45_SpBOneLinePixel[3][1] = g_Hp45_150To300Pixel[31];
		g_HP45_SpBOneLinePixel[3][2] = g_Hp45_150To300Pixel[53];
		g_HP45_SpBOneLinePixel[3][3] = g_Hp45_150To300Pixel[75];
		g_HP45_SpBOneLinePixel[3][4] = g_Hp45_150To300Pixel[97];
		g_HP45_SpBOneLinePixel[3][5] = g_Hp45_150To300Pixel[119];
		g_HP45_SpBOneLinePixel[3][6] = g_Hp45_150To300Pixel[141];
		g_HP45_SpBOneLinePixel[3][7] = 0;

		g_HP45_SpBOneLinePixel[4][0] = g_Hp45_150To300Pixel[12];
		g_HP45_SpBOneLinePixel[4][1] = g_Hp45_150To300Pixel[34];
		g_HP45_SpBOneLinePixel[4][2] = g_Hp45_150To300Pixel[56];
		g_HP45_SpBOneLinePixel[4][3] = g_Hp45_150To300Pixel[78];
		g_HP45_SpBOneLinePixel[4][4] = g_Hp45_150To300Pixel[100];
		g_HP45_SpBOneLinePixel[4][5] = g_Hp45_150To300Pixel[122];
		g_HP45_SpBOneLinePixel[4][6] = g_Hp45_150To300Pixel[144];
		g_HP45_SpBOneLinePixel[4][7] = 0;

		g_HP45_SpBOneLinePixel[5][0] = g_Hp45_150To300Pixel[15];
		g_HP45_SpBOneLinePixel[5][1] = g_Hp45_150To300Pixel[37];
		g_HP45_SpBOneLinePixel[5][2] = g_Hp45_150To300Pixel[59];
		g_HP45_SpBOneLinePixel[5][3] = g_Hp45_150To300Pixel[81];
		g_HP45_SpBOneLinePixel[5][4] = g_Hp45_150To300Pixel[103];
		g_HP45_SpBOneLinePixel[5][5] = g_Hp45_150To300Pixel[125];
		g_HP45_SpBOneLinePixel[5][6] = g_Hp45_150To300Pixel[147];
		g_HP45_SpBOneLinePixel[5][7] = 0;

		g_HP45_SpBOneLinePixel[6][0] = g_Hp45_150To300Pixel[18];
		g_HP45_SpBOneLinePixel[6][1] = g_Hp45_150To300Pixel[40];
		g_HP45_SpBOneLinePixel[6][2] = g_Hp45_150To300Pixel[62];
		g_HP45_SpBOneLinePixel[6][3] = g_Hp45_150To300Pixel[84];
		g_HP45_SpBOneLinePixel[6][4] = g_Hp45_150To300Pixel[106];
		g_HP45_SpBOneLinePixel[6][5] = g_Hp45_150To300Pixel[128];
		g_HP45_SpBOneLinePixel[6][6] = 0;
		g_HP45_SpBOneLinePixel[6][7] = 0;
		
		g_HP45_SpBOneLinePixel[7][0] = 0;
		g_HP45_SpBOneLinePixel[7][1] = g_Hp45_150To300Pixel[21];
		g_HP45_SpBOneLinePixel[7][2] = g_Hp45_150To300Pixel[43];
		g_HP45_SpBOneLinePixel[7][3] = g_Hp45_150To300Pixel[65];
		g_HP45_SpBOneLinePixel[7][4] = g_Hp45_150To300Pixel[87];
		g_HP45_SpBOneLinePixel[7][5] = g_Hp45_150To300Pixel[109];
		g_HP45_SpBOneLinePixel[7][6] = g_Hp45_150To300Pixel[131];
		g_HP45_SpBOneLinePixel[7][7] = 0;
		
		g_HP45_SpBOneLinePixel[8][0] = g_Hp45_150To300Pixel[2];
		g_HP45_SpBOneLinePixel[8][1] = g_Hp45_150To300Pixel[24];
		g_HP45_SpBOneLinePixel[8][2] = g_Hp45_150To300Pixel[46];
		g_HP45_SpBOneLinePixel[8][3] = g_Hp45_150To300Pixel[68];
		g_HP45_SpBOneLinePixel[8][4] = g_Hp45_150To300Pixel[90];
		g_HP45_SpBOneLinePixel[8][5] = g_Hp45_150To300Pixel[112];
		g_HP45_SpBOneLinePixel[8][6] = g_Hp45_150To300Pixel[134];
		g_HP45_SpBOneLinePixel[8][7] = 0;
		
		g_HP45_SpBOneLinePixel[9][0] = g_Hp45_150To300Pixel[5];
		g_HP45_SpBOneLinePixel[9][1] = g_Hp45_150To300Pixel[27];
		g_HP45_SpBOneLinePixel[9][2] = g_Hp45_150To300Pixel[49];
		g_HP45_SpBOneLinePixel[9][3] = g_Hp45_150To300Pixel[71];
		g_HP45_SpBOneLinePixel[9][4] = g_Hp45_150To300Pixel[93];
		g_HP45_SpBOneLinePixel[9][5] = g_Hp45_150To300Pixel[115];
		g_HP45_SpBOneLinePixel[9][6] = g_Hp45_150To300Pixel[137];
		g_HP45_SpBOneLinePixel[9][7] = 0;
		
		g_HP45_SpBOneLinePixel[10][0] = g_Hp45_150To300Pixel[8];
		g_HP45_SpBOneLinePixel[10][1] = g_Hp45_150To300Pixel[30];
		g_HP45_SpBOneLinePixel[10][2] = g_Hp45_150To300Pixel[52];
		g_HP45_SpBOneLinePixel[10][3] = g_Hp45_150To300Pixel[74];
		g_HP45_SpBOneLinePixel[10][4] = g_Hp45_150To300Pixel[96];
		g_HP45_SpBOneLinePixel[10][5] = g_Hp45_150To300Pixel[118];
		g_HP45_SpBOneLinePixel[10][6] = g_Hp45_150To300Pixel[140];
		g_HP45_SpBOneLinePixel[10][7] = 0;
		
		g_HP45_SpBOneLinePixel[11][0] = g_Hp45_150To300Pixel[11];
		g_HP45_SpBOneLinePixel[11][1] = g_Hp45_150To300Pixel[33];
		g_HP45_SpBOneLinePixel[11][2] = g_Hp45_150To300Pixel[55];
		g_HP45_SpBOneLinePixel[11][3] = g_Hp45_150To300Pixel[77];
		g_HP45_SpBOneLinePixel[11][4] = g_Hp45_150To300Pixel[99];
		g_HP45_SpBOneLinePixel[11][5] = g_Hp45_150To300Pixel[121];
		g_HP45_SpBOneLinePixel[11][6] = g_Hp45_150To300Pixel[143];
		g_HP45_SpBOneLinePixel[11][7] = 0;
		
		g_HP45_SpBOneLinePixel[12][0] = g_Hp45_150To300Pixel[14];
		g_HP45_SpBOneLinePixel[12][1] = g_Hp45_150To300Pixel[36];
		g_HP45_SpBOneLinePixel[12][2] = g_Hp45_150To300Pixel[58];
		g_HP45_SpBOneLinePixel[12][3] = g_Hp45_150To300Pixel[80];
		g_HP45_SpBOneLinePixel[12][4] = g_Hp45_150To300Pixel[102];
		g_HP45_SpBOneLinePixel[12][5] = g_Hp45_150To300Pixel[124];
		g_HP45_SpBOneLinePixel[12][6] = g_Hp45_150To300Pixel[146];
		g_HP45_SpBOneLinePixel[12][7] = 0;
		
		g_HP45_SpBOneLinePixel[13][0] = g_Hp45_150To300Pixel[17];
		g_HP45_SpBOneLinePixel[13][1] = g_Hp45_150To300Pixel[39];
		g_HP45_SpBOneLinePixel[13][2] = g_Hp45_150To300Pixel[61];
		g_HP45_SpBOneLinePixel[13][3] = g_Hp45_150To300Pixel[83];
		g_HP45_SpBOneLinePixel[13][4] = g_Hp45_150To300Pixel[105];
		g_HP45_SpBOneLinePixel[13][5] = g_Hp45_150To300Pixel[127];
		g_HP45_SpBOneLinePixel[13][6] = g_Hp45_150To300Pixel[149];
		g_HP45_SpBOneLinePixel[13][7] = 0;
		
		g_HP45_SpBOneLinePixel[14][0] = 0;
		g_HP45_SpBOneLinePixel[14][1] = g_Hp45_150To300Pixel[20];
		g_HP45_SpBOneLinePixel[14][2] = g_Hp45_150To300Pixel[42];
		g_HP45_SpBOneLinePixel[14][3] = g_Hp45_150To300Pixel[64];
		g_HP45_SpBOneLinePixel[14][4] = g_Hp45_150To300Pixel[86];
		g_HP45_SpBOneLinePixel[14][5] = g_Hp45_150To300Pixel[108];
		g_HP45_SpBOneLinePixel[14][6] = g_Hp45_150To300Pixel[130];
		g_HP45_SpBOneLinePixel[14][7] = 0;
		
		g_HP45_SpBOneLinePixel[15][0] = g_Hp45_150To300Pixel[1];
		g_HP45_SpBOneLinePixel[15][1] = g_Hp45_150To300Pixel[23];
		g_HP45_SpBOneLinePixel[15][2] = g_Hp45_150To300Pixel[45];
		g_HP45_SpBOneLinePixel[15][3] = g_Hp45_150To300Pixel[67];
		g_HP45_SpBOneLinePixel[15][4] = g_Hp45_150To300Pixel[89];
		g_HP45_SpBOneLinePixel[15][5] = g_Hp45_150To300Pixel[111];
		g_HP45_SpBOneLinePixel[15][6] = g_Hp45_150To300Pixel[133];
		g_HP45_SpBOneLinePixel[15][7] = 0;
		
		g_HP45_SpBOneLinePixel[16][0] = g_Hp45_150To300Pixel[4];
		g_HP45_SpBOneLinePixel[16][1] = g_Hp45_150To300Pixel[26];
		g_HP45_SpBOneLinePixel[16][2] = g_Hp45_150To300Pixel[48];
		g_HP45_SpBOneLinePixel[16][3] = g_Hp45_150To300Pixel[70];
		g_HP45_SpBOneLinePixel[16][4] = g_Hp45_150To300Pixel[92];
		g_HP45_SpBOneLinePixel[16][5] = g_Hp45_150To300Pixel[114];
		g_HP45_SpBOneLinePixel[16][6] = g_Hp45_150To300Pixel[136];
		g_HP45_SpBOneLinePixel[16][7] = 0;
		
		g_HP45_SpBOneLinePixel[17][0] = g_Hp45_150To300Pixel[7];
		g_HP45_SpBOneLinePixel[17][1] = g_Hp45_150To300Pixel[29];
		g_HP45_SpBOneLinePixel[17][2] = g_Hp45_150To300Pixel[51];
		g_HP45_SpBOneLinePixel[17][3] = g_Hp45_150To300Pixel[73];
		g_HP45_SpBOneLinePixel[17][4] = g_Hp45_150To300Pixel[95];
		g_HP45_SpBOneLinePixel[17][5] = g_Hp45_150To300Pixel[117];
		g_HP45_SpBOneLinePixel[17][6] = g_Hp45_150To300Pixel[139];
		g_HP45_SpBOneLinePixel[17][7] = 0;
		
		g_HP45_SpBOneLinePixel[18][0] = g_Hp45_150To300Pixel[10];
		g_HP45_SpBOneLinePixel[18][1] = g_Hp45_150To300Pixel[32];
		g_HP45_SpBOneLinePixel[18][2] = g_Hp45_150To300Pixel[54];
		g_HP45_SpBOneLinePixel[18][3] = g_Hp45_150To300Pixel[76];
		g_HP45_SpBOneLinePixel[18][4] = g_Hp45_150To300Pixel[98];
		g_HP45_SpBOneLinePixel[18][5] = g_Hp45_150To300Pixel[120];
		g_HP45_SpBOneLinePixel[18][6] = g_Hp45_150To300Pixel[142];
		g_HP45_SpBOneLinePixel[18][7] = 0;
		
		g_HP45_SpBOneLinePixel[19][0] = g_Hp45_150To300Pixel[13];
		g_HP45_SpBOneLinePixel[19][1] = g_Hp45_150To300Pixel[35];
		g_HP45_SpBOneLinePixel[19][2] = g_Hp45_150To300Pixel[57];
		g_HP45_SpBOneLinePixel[19][3] = g_Hp45_150To300Pixel[79];
		g_HP45_SpBOneLinePixel[19][4] = g_Hp45_150To300Pixel[101];
		g_HP45_SpBOneLinePixel[19][5] = g_Hp45_150To300Pixel[123];
		g_HP45_SpBOneLinePixel[19][6] = g_Hp45_150To300Pixel[145];
		g_HP45_SpBOneLinePixel[19][7] = 0;

		g_HP45_SpBOneLinePixel[20][0] = g_Hp45_150To300Pixel[16];
		g_HP45_SpBOneLinePixel[20][1] = g_Hp45_150To300Pixel[38];
		g_HP45_SpBOneLinePixel[20][2] = g_Hp45_150To300Pixel[60];
		g_HP45_SpBOneLinePixel[20][3] = g_Hp45_150To300Pixel[82];
		g_HP45_SpBOneLinePixel[20][4] = g_Hp45_150To300Pixel[104];
		g_HP45_SpBOneLinePixel[20][5] = g_Hp45_150To300Pixel[126];
		g_HP45_SpBOneLinePixel[20][6] = g_Hp45_150To300Pixel[148];
		g_HP45_SpBOneLinePixel[20][7] = 0;
		
		g_HP45_SpBOneLinePixel[21][0] = g_Hp45_150To300Pixel[19];
		g_HP45_SpBOneLinePixel[21][1] = g_Hp45_150To300Pixel[41];
		g_HP45_SpBOneLinePixel[21][2] = g_Hp45_150To300Pixel[63];
		g_HP45_SpBOneLinePixel[21][3] = g_Hp45_150To300Pixel[85];
		g_HP45_SpBOneLinePixel[21][4] = g_Hp45_150To300Pixel[107];
		g_HP45_SpBOneLinePixel[21][5] = g_Hp45_150To300Pixel[129];
		g_HP45_SpBOneLinePixel[21][6] = 0;
		g_HP45_SpBOneLinePixel[21][7] = 0;
	}
}
