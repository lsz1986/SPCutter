#include "Stdafx.h"
#include "Global.h"
#include "Thread.h"

void IUT308_getSpBOneLineData(char Type)
{
	if (0==Type)
	{
		int i,j;
		for (i=0;i<44;i++)
		{
			for (j=0;j<8;j++)
			{
				g_IUT308_SpBOneLinePixel[i][j] = 0;
			}
		}
	}
	else if (1==Type)
	{
		g_IUT308_SpBOneLinePixel[0][0] = g_IUT308_001To308Pixel[308-223];
		g_IUT308_SpBOneLinePixel[0][1] = g_IUT308_001To308Pixel[308-245];
		g_IUT308_SpBOneLinePixel[0][2] = g_IUT308_001To308Pixel[308-267];
		g_IUT308_SpBOneLinePixel[0][3] = g_IUT308_001To308Pixel[308-289];
		g_IUT308_SpBOneLinePixel[0][4] = g_IUT308_001To308Pixel[308-157];
		g_IUT308_SpBOneLinePixel[0][5] = g_IUT308_001To308Pixel[308-179];
		g_IUT308_SpBOneLinePixel[0][6] = g_IUT308_001To308Pixel[308-201];
		g_IUT308_SpBOneLinePixel[0][7] = 0;
		
		g_IUT308_SpBOneLinePixel[1][0] = g_IUT308_001To308Pixel[308-226];
		g_IUT308_SpBOneLinePixel[1][1] = g_IUT308_001To308Pixel[308-248];
		g_IUT308_SpBOneLinePixel[1][2] = g_IUT308_001To308Pixel[308-270];
		g_IUT308_SpBOneLinePixel[1][3] = g_IUT308_001To308Pixel[308-292];
		g_IUT308_SpBOneLinePixel[1][4] = g_IUT308_001To308Pixel[308-160];
		g_IUT308_SpBOneLinePixel[1][5] = g_IUT308_001To308Pixel[308-182];
		g_IUT308_SpBOneLinePixel[1][6] = g_IUT308_001To308Pixel[308-204];
		g_IUT308_SpBOneLinePixel[1][7] = 0;

		g_IUT308_SpBOneLinePixel[2][0] = g_IUT308_001To308Pixel[308-229];
		g_IUT308_SpBOneLinePixel[2][1] = g_IUT308_001To308Pixel[308-251];
		g_IUT308_SpBOneLinePixel[2][2] = g_IUT308_001To308Pixel[308-273];
		g_IUT308_SpBOneLinePixel[2][3] = g_IUT308_001To308Pixel[308-295];
		g_IUT308_SpBOneLinePixel[2][4] = g_IUT308_001To308Pixel[308-163];
		g_IUT308_SpBOneLinePixel[2][5] = g_IUT308_001To308Pixel[308-185];
		g_IUT308_SpBOneLinePixel[2][6] = g_IUT308_001To308Pixel[308-207];
		g_IUT308_SpBOneLinePixel[2][7] = 0;
		
		g_IUT308_SpBOneLinePixel[3][0] = g_IUT308_001To308Pixel[308-232];
		g_IUT308_SpBOneLinePixel[3][1] = g_IUT308_001To308Pixel[308-254];
		g_IUT308_SpBOneLinePixel[3][2] = g_IUT308_001To308Pixel[308-276];
		g_IUT308_SpBOneLinePixel[3][3] = g_IUT308_001To308Pixel[308-298];
		g_IUT308_SpBOneLinePixel[3][4] = g_IUT308_001To308Pixel[308-166];
		g_IUT308_SpBOneLinePixel[3][5] = g_IUT308_001To308Pixel[308-188];
		g_IUT308_SpBOneLinePixel[3][6] = g_IUT308_001To308Pixel[308-210];
		g_IUT308_SpBOneLinePixel[3][7] = 0;
		
		g_IUT308_SpBOneLinePixel[4][0] = g_IUT308_001To308Pixel[308-235];
		g_IUT308_SpBOneLinePixel[4][1] = g_IUT308_001To308Pixel[308-257];
		g_IUT308_SpBOneLinePixel[4][2] = g_IUT308_001To308Pixel[308-279];
		g_IUT308_SpBOneLinePixel[4][3] = g_IUT308_001To308Pixel[308-301];
		g_IUT308_SpBOneLinePixel[4][4] = g_IUT308_001To308Pixel[308-169];
		g_IUT308_SpBOneLinePixel[4][5] = g_IUT308_001To308Pixel[308-191];
		g_IUT308_SpBOneLinePixel[4][6] = g_IUT308_001To308Pixel[308-213];
		g_IUT308_SpBOneLinePixel[4][7] = 0;

		g_IUT308_SpBOneLinePixel[5][0] = g_IUT308_001To308Pixel[308-238];
		g_IUT308_SpBOneLinePixel[5][1] = g_IUT308_001To308Pixel[308-260];
		g_IUT308_SpBOneLinePixel[5][2] = g_IUT308_001To308Pixel[308-282];
		g_IUT308_SpBOneLinePixel[5][3] = g_IUT308_001To308Pixel[308-304];
		g_IUT308_SpBOneLinePixel[5][4] = g_IUT308_001To308Pixel[308-172];
		g_IUT308_SpBOneLinePixel[5][5] = g_IUT308_001To308Pixel[308-194];
		g_IUT308_SpBOneLinePixel[5][6] = g_IUT308_001To308Pixel[308-216];
		g_IUT308_SpBOneLinePixel[5][7] = 0;
				
		g_IUT308_SpBOneLinePixel[6][0] = g_IUT308_001To308Pixel[308-241];
		g_IUT308_SpBOneLinePixel[6][1] = g_IUT308_001To308Pixel[308-263];
		g_IUT308_SpBOneLinePixel[6][2] = g_IUT308_001To308Pixel[308-285];
		g_IUT308_SpBOneLinePixel[6][3] = g_IUT308_001To308Pixel[308-307];
		g_IUT308_SpBOneLinePixel[6][4] = g_IUT308_001To308Pixel[308-175];
		g_IUT308_SpBOneLinePixel[6][5] = g_IUT308_001To308Pixel[308-197];
		g_IUT308_SpBOneLinePixel[6][6] = g_IUT308_001To308Pixel[308-219];
		g_IUT308_SpBOneLinePixel[6][7] = 0;
		
		g_IUT308_SpBOneLinePixel[7][0] = g_IUT308_001To308Pixel[308-222];
		g_IUT308_SpBOneLinePixel[7][1] = g_IUT308_001To308Pixel[308-244];
		g_IUT308_SpBOneLinePixel[7][2] = g_IUT308_001To308Pixel[308-266];
		g_IUT308_SpBOneLinePixel[7][3] = g_IUT308_001To308Pixel[308-288];
		g_IUT308_SpBOneLinePixel[7][4] = g_IUT308_001To308Pixel[308-156];
		g_IUT308_SpBOneLinePixel[7][5] = g_IUT308_001To308Pixel[308-178];
		g_IUT308_SpBOneLinePixel[7][6] = g_IUT308_001To308Pixel[308-200];
		g_IUT308_SpBOneLinePixel[7][7] = 0;
		
		g_IUT308_SpBOneLinePixel[8][0] = g_IUT308_001To308Pixel[308-225];
		g_IUT308_SpBOneLinePixel[8][1] = g_IUT308_001To308Pixel[308-247];
		g_IUT308_SpBOneLinePixel[8][2] = g_IUT308_001To308Pixel[308-269];
		g_IUT308_SpBOneLinePixel[8][3] = g_IUT308_001To308Pixel[308-291];
		g_IUT308_SpBOneLinePixel[8][4] = g_IUT308_001To308Pixel[308-159];
		g_IUT308_SpBOneLinePixel[8][5] = g_IUT308_001To308Pixel[308-181];
		g_IUT308_SpBOneLinePixel[8][6] = g_IUT308_001To308Pixel[308-203];
		g_IUT308_SpBOneLinePixel[8][7] = 0;	

		g_IUT308_SpBOneLinePixel[9][0] = g_IUT308_001To308Pixel[308-228];
		g_IUT308_SpBOneLinePixel[9][1] = g_IUT308_001To308Pixel[308-250];
		g_IUT308_SpBOneLinePixel[9][2] = g_IUT308_001To308Pixel[308-272];
		g_IUT308_SpBOneLinePixel[9][3] = g_IUT308_001To308Pixel[308-294];
		g_IUT308_SpBOneLinePixel[9][4] = g_IUT308_001To308Pixel[308-162];
		g_IUT308_SpBOneLinePixel[9][5] = g_IUT308_001To308Pixel[308-184];
		g_IUT308_SpBOneLinePixel[9][6] = g_IUT308_001To308Pixel[308-206];
		g_IUT308_SpBOneLinePixel[9][7] = 0;
		
		g_IUT308_SpBOneLinePixel[10][0] = g_IUT308_001To308Pixel[308-231];
		g_IUT308_SpBOneLinePixel[10][1] = g_IUT308_001To308Pixel[308-253];
		g_IUT308_SpBOneLinePixel[10][2] = g_IUT308_001To308Pixel[308-275];
		g_IUT308_SpBOneLinePixel[10][3] = g_IUT308_001To308Pixel[308-297];
		g_IUT308_SpBOneLinePixel[10][4] = g_IUT308_001To308Pixel[308-165];
		g_IUT308_SpBOneLinePixel[10][5] = g_IUT308_001To308Pixel[308-187];
		g_IUT308_SpBOneLinePixel[10][6] = g_IUT308_001To308Pixel[308-209];
		g_IUT308_SpBOneLinePixel[10][7] = 0;
		
		g_IUT308_SpBOneLinePixel[11][0] = g_IUT308_001To308Pixel[308-234];	
		g_IUT308_SpBOneLinePixel[11][1] = g_IUT308_001To308Pixel[308-256];	
		g_IUT308_SpBOneLinePixel[11][2] = g_IUT308_001To308Pixel[308-278];	
		g_IUT308_SpBOneLinePixel[11][3] = g_IUT308_001To308Pixel[308-300];
		g_IUT308_SpBOneLinePixel[11][4] = g_IUT308_001To308Pixel[308-168];	
		g_IUT308_SpBOneLinePixel[11][5] = g_IUT308_001To308Pixel[308-190];	
		g_IUT308_SpBOneLinePixel[11][6] = g_IUT308_001To308Pixel[308-212];		
		g_IUT308_SpBOneLinePixel[11][7] = 0;

		g_IUT308_SpBOneLinePixel[12][0] = g_IUT308_001To308Pixel[308-237];
		g_IUT308_SpBOneLinePixel[12][1] = g_IUT308_001To308Pixel[308-259];
		g_IUT308_SpBOneLinePixel[12][2] = g_IUT308_001To308Pixel[308-281];
		g_IUT308_SpBOneLinePixel[12][3] = g_IUT308_001To308Pixel[308-303];
		g_IUT308_SpBOneLinePixel[12][4] = g_IUT308_001To308Pixel[308-171];
		g_IUT308_SpBOneLinePixel[12][5] = g_IUT308_001To308Pixel[308-193];
		g_IUT308_SpBOneLinePixel[12][6] = g_IUT308_001To308Pixel[308-215];
		g_IUT308_SpBOneLinePixel[12][7] = 0;

		g_IUT308_SpBOneLinePixel[13][0] = g_IUT308_001To308Pixel[308-240];
		g_IUT308_SpBOneLinePixel[13][1] = g_IUT308_001To308Pixel[308-262];
		g_IUT308_SpBOneLinePixel[13][2] = g_IUT308_001To308Pixel[308-284];
		g_IUT308_SpBOneLinePixel[13][3] = g_IUT308_001To308Pixel[308-306];
		g_IUT308_SpBOneLinePixel[13][4] = g_IUT308_001To308Pixel[308-174];
		g_IUT308_SpBOneLinePixel[13][5] = g_IUT308_001To308Pixel[308-196];
		g_IUT308_SpBOneLinePixel[13][6] = g_IUT308_001To308Pixel[308-218];
		g_IUT308_SpBOneLinePixel[13][7] = 0;

		g_IUT308_SpBOneLinePixel[14][0] = g_IUT308_001To308Pixel[308-221];	
		g_IUT308_SpBOneLinePixel[14][1] = g_IUT308_001To308Pixel[308-243];	
		g_IUT308_SpBOneLinePixel[14][2] = g_IUT308_001To308Pixel[308-265];	
		g_IUT308_SpBOneLinePixel[14][3] = g_IUT308_001To308Pixel[308-287];	
		g_IUT308_SpBOneLinePixel[14][4] = g_IUT308_001To308Pixel[308-155];	
		g_IUT308_SpBOneLinePixel[14][5] = g_IUT308_001To308Pixel[308-177];	
		g_IUT308_SpBOneLinePixel[14][6] = g_IUT308_001To308Pixel[308-199];		
		g_IUT308_SpBOneLinePixel[14][7] = 0;		

		g_IUT308_SpBOneLinePixel[15][0] = g_IUT308_001To308Pixel[308-224];	
		g_IUT308_SpBOneLinePixel[15][1] = g_IUT308_001To308Pixel[308-246];	
		g_IUT308_SpBOneLinePixel[15][2] = g_IUT308_001To308Pixel[308-268];	
		g_IUT308_SpBOneLinePixel[15][3] = g_IUT308_001To308Pixel[308-290];	
		g_IUT308_SpBOneLinePixel[15][4] = g_IUT308_001To308Pixel[308-158];	
		g_IUT308_SpBOneLinePixel[15][5] = g_IUT308_001To308Pixel[308-180];	
		g_IUT308_SpBOneLinePixel[15][6] = g_IUT308_001To308Pixel[308-202];	
		g_IUT308_SpBOneLinePixel[15][7] = 0;		
		
		g_IUT308_SpBOneLinePixel[16][0] = g_IUT308_001To308Pixel[308-227];	
		g_IUT308_SpBOneLinePixel[16][1] = g_IUT308_001To308Pixel[308-249];	
		g_IUT308_SpBOneLinePixel[16][2] = g_IUT308_001To308Pixel[308-271];	
		g_IUT308_SpBOneLinePixel[16][3] = g_IUT308_001To308Pixel[308-293];	
		g_IUT308_SpBOneLinePixel[16][4] = g_IUT308_001To308Pixel[308-161];	
		g_IUT308_SpBOneLinePixel[16][5] = g_IUT308_001To308Pixel[308-183];	
		g_IUT308_SpBOneLinePixel[16][6] = g_IUT308_001To308Pixel[308-205];		
		g_IUT308_SpBOneLinePixel[16][7] = 0;		

		g_IUT308_SpBOneLinePixel[17][0] = g_IUT308_001To308Pixel[308-230];	
		g_IUT308_SpBOneLinePixel[17][1] = g_IUT308_001To308Pixel[308-252];	
		g_IUT308_SpBOneLinePixel[17][2] = g_IUT308_001To308Pixel[308-274];	
		g_IUT308_SpBOneLinePixel[17][3] = g_IUT308_001To308Pixel[308-296];	
		g_IUT308_SpBOneLinePixel[17][4] = g_IUT308_001To308Pixel[308-164];	
		g_IUT308_SpBOneLinePixel[17][5] = g_IUT308_001To308Pixel[308-186];	
		g_IUT308_SpBOneLinePixel[17][6] = g_IUT308_001To308Pixel[308-208];	
		g_IUT308_SpBOneLinePixel[17][6] = 0;

		g_IUT308_SpBOneLinePixel[18][0] = g_IUT308_001To308Pixel[308-233];	
		g_IUT308_SpBOneLinePixel[18][1] = g_IUT308_001To308Pixel[308-255];	
		g_IUT308_SpBOneLinePixel[18][2] = g_IUT308_001To308Pixel[308-277];	
		g_IUT308_SpBOneLinePixel[18][3] = g_IUT308_001To308Pixel[308-299];	
		g_IUT308_SpBOneLinePixel[18][4] = g_IUT308_001To308Pixel[308-167];	
		g_IUT308_SpBOneLinePixel[18][5] = g_IUT308_001To308Pixel[308-189];	
		g_IUT308_SpBOneLinePixel[18][6] = g_IUT308_001To308Pixel[308-211];	
		g_IUT308_SpBOneLinePixel[18][7] = 0;	

		g_IUT308_SpBOneLinePixel[19][0] = g_IUT308_001To308Pixel[308-236];	
		g_IUT308_SpBOneLinePixel[19][1] = g_IUT308_001To308Pixel[308-258];	
		g_IUT308_SpBOneLinePixel[19][2] = g_IUT308_001To308Pixel[308-280];	
		g_IUT308_SpBOneLinePixel[19][3] = g_IUT308_001To308Pixel[308-302];	
		g_IUT308_SpBOneLinePixel[19][4] = g_IUT308_001To308Pixel[308-170];	
		g_IUT308_SpBOneLinePixel[19][5] = g_IUT308_001To308Pixel[308-192];	
		g_IUT308_SpBOneLinePixel[19][6] = g_IUT308_001To308Pixel[308-214];
		g_IUT308_SpBOneLinePixel[19][7] = 0;
		
		g_IUT308_SpBOneLinePixel[20][0] = g_IUT308_001To308Pixel[308-239];	
		g_IUT308_SpBOneLinePixel[20][1] = g_IUT308_001To308Pixel[308-261];	
		g_IUT308_SpBOneLinePixel[20][2] = g_IUT308_001To308Pixel[308-283];	
		g_IUT308_SpBOneLinePixel[20][3] = g_IUT308_001To308Pixel[308-305];	
		g_IUT308_SpBOneLinePixel[20][4] = g_IUT308_001To308Pixel[308-173];	
		g_IUT308_SpBOneLinePixel[20][5] = g_IUT308_001To308Pixel[308-195];	
		g_IUT308_SpBOneLinePixel[20][6] = g_IUT308_001To308Pixel[308-217];
		g_IUT308_SpBOneLinePixel[20][6] = 0;

		g_IUT308_SpBOneLinePixel[21][0] = g_IUT308_001To308Pixel[308-242];	
		g_IUT308_SpBOneLinePixel[21][1] = g_IUT308_001To308Pixel[308-264];	
		g_IUT308_SpBOneLinePixel[21][2] = g_IUT308_001To308Pixel[308-286];	
		g_IUT308_SpBOneLinePixel[21][3] = g_IUT308_001To308Pixel[308-308];	
		g_IUT308_SpBOneLinePixel[21][4] = g_IUT308_001To308Pixel[308-176];	
		g_IUT308_SpBOneLinePixel[21][5] = g_IUT308_001To308Pixel[308-198];	
		g_IUT308_SpBOneLinePixel[21][6] = g_IUT308_001To308Pixel[308-220];	
		g_IUT308_SpBOneLinePixel[21][7] = 0;
//---------------------------------------------------------------------------------
		g_IUT308_SpBOneLinePixel[22][0] = g_IUT308_001To308Pixel[308-47];
		g_IUT308_SpBOneLinePixel[22][1] = g_IUT308_001To308Pixel[308-25];
		g_IUT308_SpBOneLinePixel[22][2] = g_IUT308_001To308Pixel[308-3];
		g_IUT308_SpBOneLinePixel[22][3] = g_IUT308_001To308Pixel[308-135];
		g_IUT308_SpBOneLinePixel[22][4] = g_IUT308_001To308Pixel[308-113];
		g_IUT308_SpBOneLinePixel[22][5] = g_IUT308_001To308Pixel[308-91];
		g_IUT308_SpBOneLinePixel[22][6] = g_IUT308_001To308Pixel[308-69];
		g_IUT308_SpBOneLinePixel[22][7] = 0;

		g_IUT308_SpBOneLinePixel[23][0] = g_IUT308_001To308Pixel[308-50];
		g_IUT308_SpBOneLinePixel[23][1] = g_IUT308_001To308Pixel[308-28];
		g_IUT308_SpBOneLinePixel[23][2] = g_IUT308_001To308Pixel[308-6];
		g_IUT308_SpBOneLinePixel[23][3] = g_IUT308_001To308Pixel[308-138];
		g_IUT308_SpBOneLinePixel[23][4] = g_IUT308_001To308Pixel[308-116];
		g_IUT308_SpBOneLinePixel[23][5] = g_IUT308_001To308Pixel[308-94];
		g_IUT308_SpBOneLinePixel[23][6] = g_IUT308_001To308Pixel[308-72];
		g_IUT308_SpBOneLinePixel[23][7] = 0;

		g_IUT308_SpBOneLinePixel[24][0] = g_IUT308_001To308Pixel[308-53];
		g_IUT308_SpBOneLinePixel[24][1] = g_IUT308_001To308Pixel[308-31];
		g_IUT308_SpBOneLinePixel[24][2] = g_IUT308_001To308Pixel[308-9];
		g_IUT308_SpBOneLinePixel[24][3] = g_IUT308_001To308Pixel[308-141];
		g_IUT308_SpBOneLinePixel[24][4] = g_IUT308_001To308Pixel[308-119];
		g_IUT308_SpBOneLinePixel[24][5] = g_IUT308_001To308Pixel[308-97];
		g_IUT308_SpBOneLinePixel[24][6] = g_IUT308_001To308Pixel[308-75];
		g_IUT308_SpBOneLinePixel[24][7] = 0;

		g_IUT308_SpBOneLinePixel[25][0] = g_IUT308_001To308Pixel[308-56];
		g_IUT308_SpBOneLinePixel[25][1] = g_IUT308_001To308Pixel[308-34];
		g_IUT308_SpBOneLinePixel[25][2] = g_IUT308_001To308Pixel[308-12];
		g_IUT308_SpBOneLinePixel[25][3] = g_IUT308_001To308Pixel[308-144];
		g_IUT308_SpBOneLinePixel[25][4] = g_IUT308_001To308Pixel[308-122];
		g_IUT308_SpBOneLinePixel[25][5] = g_IUT308_001To308Pixel[308-100];
		g_IUT308_SpBOneLinePixel[25][6] = g_IUT308_001To308Pixel[308-78];
		g_IUT308_SpBOneLinePixel[25][7] = 0;

		g_IUT308_SpBOneLinePixel[26][0] = g_IUT308_001To308Pixel[308-59];
		g_IUT308_SpBOneLinePixel[26][1] = g_IUT308_001To308Pixel[308-37];
		g_IUT308_SpBOneLinePixel[26][2] = g_IUT308_001To308Pixel[308-15];
		g_IUT308_SpBOneLinePixel[26][3] = g_IUT308_001To308Pixel[308-147];
		g_IUT308_SpBOneLinePixel[26][4] = g_IUT308_001To308Pixel[308-125];
		g_IUT308_SpBOneLinePixel[26][5] = g_IUT308_001To308Pixel[308-103];
		g_IUT308_SpBOneLinePixel[26][6] = g_IUT308_001To308Pixel[308-81];//ok
		g_IUT308_SpBOneLinePixel[26][7] = 0;
		
		g_IUT308_SpBOneLinePixel[27][0] = g_IUT308_001To308Pixel[308-62];
		g_IUT308_SpBOneLinePixel[27][1] = g_IUT308_001To308Pixel[308-40];
		g_IUT308_SpBOneLinePixel[27][2] = g_IUT308_001To308Pixel[308-18];
		g_IUT308_SpBOneLinePixel[27][3] = g_IUT308_001To308Pixel[308-150];
		g_IUT308_SpBOneLinePixel[27][4] = g_IUT308_001To308Pixel[308-128];
		g_IUT308_SpBOneLinePixel[27][5] = g_IUT308_001To308Pixel[308-106];
		g_IUT308_SpBOneLinePixel[27][6] = g_IUT308_001To308Pixel[308-84]; //ok
		g_IUT308_SpBOneLinePixel[27][7] = 0;	

		g_IUT308_SpBOneLinePixel[28][0] = g_IUT308_001To308Pixel[308-65];
		g_IUT308_SpBOneLinePixel[28][1] = g_IUT308_001To308Pixel[308-43];
		g_IUT308_SpBOneLinePixel[28][2] = g_IUT308_001To308Pixel[308-21];
		g_IUT308_SpBOneLinePixel[28][3] = g_IUT308_001To308Pixel[308-153];
		g_IUT308_SpBOneLinePixel[28][4] = g_IUT308_001To308Pixel[308-131];
		g_IUT308_SpBOneLinePixel[28][5] = g_IUT308_001To308Pixel[308-109];
		g_IUT308_SpBOneLinePixel[28][6] = g_IUT308_001To308Pixel[308-87]; //ok
		g_IUT308_SpBOneLinePixel[28][7] = 0;
		
		g_IUT308_SpBOneLinePixel[29][0] = g_IUT308_001To308Pixel[308-46];
		g_IUT308_SpBOneLinePixel[29][1] = g_IUT308_001To308Pixel[308-24];
		g_IUT308_SpBOneLinePixel[29][2] = g_IUT308_001To308Pixel[308-2];
		g_IUT308_SpBOneLinePixel[29][3] = g_IUT308_001To308Pixel[308-134];
		g_IUT308_SpBOneLinePixel[29][4] = g_IUT308_001To308Pixel[308-112];
		g_IUT308_SpBOneLinePixel[29][5] = g_IUT308_001To308Pixel[308-90];
		g_IUT308_SpBOneLinePixel[29][6] = g_IUT308_001To308Pixel[308-68]; //ok
		g_IUT308_SpBOneLinePixel[29][7] = 0;
		
		g_IUT308_SpBOneLinePixel[30][0] = g_IUT308_001To308Pixel[308-49];
		g_IUT308_SpBOneLinePixel[30][1] = g_IUT308_001To308Pixel[308-27];
		g_IUT308_SpBOneLinePixel[30][2] = g_IUT308_001To308Pixel[308-5];
		g_IUT308_SpBOneLinePixel[30][3] = g_IUT308_001To308Pixel[308-137];
		g_IUT308_SpBOneLinePixel[30][4] = g_IUT308_001To308Pixel[308-115];
		g_IUT308_SpBOneLinePixel[30][5] = g_IUT308_001To308Pixel[308-93];
		g_IUT308_SpBOneLinePixel[30][6] = g_IUT308_001To308Pixel[308-71]; //ok
		g_IUT308_SpBOneLinePixel[30][7] = 0;

		g_IUT308_SpBOneLinePixel[31][0] = g_IUT308_001To308Pixel[308-52];
		g_IUT308_SpBOneLinePixel[31][1] = g_IUT308_001To308Pixel[308-30];
		g_IUT308_SpBOneLinePixel[31][2] = g_IUT308_001To308Pixel[308-8];
		g_IUT308_SpBOneLinePixel[31][3] = g_IUT308_001To308Pixel[308-140];
		g_IUT308_SpBOneLinePixel[31][4] = g_IUT308_001To308Pixel[308-118];
		g_IUT308_SpBOneLinePixel[31][5] = g_IUT308_001To308Pixel[308-96];
		g_IUT308_SpBOneLinePixel[31][6] = g_IUT308_001To308Pixel[308-74];//ok
		g_IUT308_SpBOneLinePixel[31][7] = 0;
		
		g_IUT308_SpBOneLinePixel[32][0] = g_IUT308_001To308Pixel[308-55];
		g_IUT308_SpBOneLinePixel[32][1] = g_IUT308_001To308Pixel[308-33];
		g_IUT308_SpBOneLinePixel[32][2] = g_IUT308_001To308Pixel[308-11];
		g_IUT308_SpBOneLinePixel[32][3] = g_IUT308_001To308Pixel[308-143];
		g_IUT308_SpBOneLinePixel[32][4] = g_IUT308_001To308Pixel[308-121];
		g_IUT308_SpBOneLinePixel[32][5] = g_IUT308_001To308Pixel[308-99];
		g_IUT308_SpBOneLinePixel[32][6] = g_IUT308_001To308Pixel[308-77]; //ok
		g_IUT308_SpBOneLinePixel[32][7] = 0;
//---------------------------------------------------------------------
		g_IUT308_SpBOneLinePixel[33][0] = g_IUT308_001To308Pixel[308-58];	
		g_IUT308_SpBOneLinePixel[33][1] = g_IUT308_001To308Pixel[308-36];	
		g_IUT308_SpBOneLinePixel[33][2] = g_IUT308_001To308Pixel[308-14];	
		g_IUT308_SpBOneLinePixel[33][3] = g_IUT308_001To308Pixel[308-146];	
		g_IUT308_SpBOneLinePixel[33][4] = g_IUT308_001To308Pixel[308-124];	
		g_IUT308_SpBOneLinePixel[33][5] = g_IUT308_001To308Pixel[308-102];	
		g_IUT308_SpBOneLinePixel[33][6] = g_IUT308_001To308Pixel[308-80];
		g_IUT308_SpBOneLinePixel[33][7] = 0;

		g_IUT308_SpBOneLinePixel[34][0] = g_IUT308_001To308Pixel[308-61];
		g_IUT308_SpBOneLinePixel[34][1] = g_IUT308_001To308Pixel[308-39];
		g_IUT308_SpBOneLinePixel[34][2] = g_IUT308_001To308Pixel[308-17];
		g_IUT308_SpBOneLinePixel[34][3] = g_IUT308_001To308Pixel[308-149];
		g_IUT308_SpBOneLinePixel[34][4] = g_IUT308_001To308Pixel[308-127];
		g_IUT308_SpBOneLinePixel[34][5] = g_IUT308_001To308Pixel[308-105];
		g_IUT308_SpBOneLinePixel[34][6] = g_IUT308_001To308Pixel[308-83];
		g_IUT308_SpBOneLinePixel[34][7] = 0;

		g_IUT308_SpBOneLinePixel[35][0] = g_IUT308_001To308Pixel[308-64];
		g_IUT308_SpBOneLinePixel[35][1] = g_IUT308_001To308Pixel[308-42];	
		g_IUT308_SpBOneLinePixel[35][2] = g_IUT308_001To308Pixel[308-20];	
		g_IUT308_SpBOneLinePixel[35][3] = g_IUT308_001To308Pixel[308-152];	
		g_IUT308_SpBOneLinePixel[35][4] = g_IUT308_001To308Pixel[308-130];	
		g_IUT308_SpBOneLinePixel[35][5] = g_IUT308_001To308Pixel[308-108];	
		g_IUT308_SpBOneLinePixel[35][6] = g_IUT308_001To308Pixel[308-86];
		g_IUT308_SpBOneLinePixel[35][7] = 0;

		g_IUT308_SpBOneLinePixel[36][0] = g_IUT308_001To308Pixel[308-45];
		g_IUT308_SpBOneLinePixel[36][1] = g_IUT308_001To308Pixel[308-23];	
		g_IUT308_SpBOneLinePixel[36][2] = g_IUT308_001To308Pixel[308-1];	
		g_IUT308_SpBOneLinePixel[36][3] = g_IUT308_001To308Pixel[308-133];	
		g_IUT308_SpBOneLinePixel[36][4] = g_IUT308_001To308Pixel[308-111];	
		g_IUT308_SpBOneLinePixel[36][5] = g_IUT308_001To308Pixel[308-89];	
		g_IUT308_SpBOneLinePixel[36][6] = g_IUT308_001To308Pixel[308-67];
		g_IUT308_SpBOneLinePixel[36][7] = 0;

		g_IUT308_SpBOneLinePixel[37][0] = g_IUT308_001To308Pixel[308-48];
		g_IUT308_SpBOneLinePixel[37][1] = g_IUT308_001To308Pixel[308-26];	
		g_IUT308_SpBOneLinePixel[37][2] = g_IUT308_001To308Pixel[308-4];	
		g_IUT308_SpBOneLinePixel[37][3] = g_IUT308_001To308Pixel[308-136];	
		g_IUT308_SpBOneLinePixel[37][4] = g_IUT308_001To308Pixel[308-114];	
		g_IUT308_SpBOneLinePixel[37][5] = g_IUT308_001To308Pixel[308-92];	
		g_IUT308_SpBOneLinePixel[37][6] = g_IUT308_001To308Pixel[308-70];
		g_IUT308_SpBOneLinePixel[37][7] = 0;

		g_IUT308_SpBOneLinePixel[38][0] = g_IUT308_001To308Pixel[308-51];	
		g_IUT308_SpBOneLinePixel[38][1] = g_IUT308_001To308Pixel[308-29];	
		g_IUT308_SpBOneLinePixel[38][2] = g_IUT308_001To308Pixel[308-7];	
		g_IUT308_SpBOneLinePixel[38][3] = g_IUT308_001To308Pixel[308-139];	
		g_IUT308_SpBOneLinePixel[38][4] = g_IUT308_001To308Pixel[308-117];	
		g_IUT308_SpBOneLinePixel[38][5] = g_IUT308_001To308Pixel[308-95];	
		g_IUT308_SpBOneLinePixel[38][6] = g_IUT308_001To308Pixel[308-73];
		g_IUT308_SpBOneLinePixel[38][7] = 0;
		
		g_IUT308_SpBOneLinePixel[39][0] = g_IUT308_001To308Pixel[308-54];
		g_IUT308_SpBOneLinePixel[39][1] = g_IUT308_001To308Pixel[308-32];	
		g_IUT308_SpBOneLinePixel[39][2] = g_IUT308_001To308Pixel[308-10];	
		g_IUT308_SpBOneLinePixel[39][3] = g_IUT308_001To308Pixel[308-142];	
		g_IUT308_SpBOneLinePixel[39][4] = g_IUT308_001To308Pixel[308-120];	
		g_IUT308_SpBOneLinePixel[39][5] = g_IUT308_001To308Pixel[308-98];	
		g_IUT308_SpBOneLinePixel[39][6] = g_IUT308_001To308Pixel[308-76];
		g_IUT308_SpBOneLinePixel[39][7] = 0;
		
		g_IUT308_SpBOneLinePixel[40][0] = g_IUT308_001To308Pixel[308-57];
		g_IUT308_SpBOneLinePixel[40][1] = g_IUT308_001To308Pixel[308-35];	
		g_IUT308_SpBOneLinePixel[40][2] = g_IUT308_001To308Pixel[308-13];	
		g_IUT308_SpBOneLinePixel[40][3] = g_IUT308_001To308Pixel[308-145];	
		g_IUT308_SpBOneLinePixel[40][4] = g_IUT308_001To308Pixel[308-123];	
		g_IUT308_SpBOneLinePixel[40][5] = g_IUT308_001To308Pixel[308-101];	
		g_IUT308_SpBOneLinePixel[40][6] = g_IUT308_001To308Pixel[308-79];
		g_IUT308_SpBOneLinePixel[40][7] = 0;

		g_IUT308_SpBOneLinePixel[41][0] = g_IUT308_001To308Pixel[308-60];
		g_IUT308_SpBOneLinePixel[41][1] = g_IUT308_001To308Pixel[308-38];	
		g_IUT308_SpBOneLinePixel[41][2] = g_IUT308_001To308Pixel[308-16];	
		g_IUT308_SpBOneLinePixel[41][3] = g_IUT308_001To308Pixel[308-148];	
		g_IUT308_SpBOneLinePixel[41][4] = g_IUT308_001To308Pixel[308-126];	
		g_IUT308_SpBOneLinePixel[41][5] = g_IUT308_001To308Pixel[308-104];	
		g_IUT308_SpBOneLinePixel[41][6] = g_IUT308_001To308Pixel[308-82];
		g_IUT308_SpBOneLinePixel[41][7] = 0;
	
		g_IUT308_SpBOneLinePixel[42][0] = g_IUT308_001To308Pixel[308-63];	
		g_IUT308_SpBOneLinePixel[42][1] = g_IUT308_001To308Pixel[308-41];	
		g_IUT308_SpBOneLinePixel[42][2] = g_IUT308_001To308Pixel[308-19];	
		g_IUT308_SpBOneLinePixel[42][3] = g_IUT308_001To308Pixel[308-151];	
		g_IUT308_SpBOneLinePixel[42][4] = g_IUT308_001To308Pixel[308-129];	
		g_IUT308_SpBOneLinePixel[42][5] = g_IUT308_001To308Pixel[308-107];	
		g_IUT308_SpBOneLinePixel[42][6] = g_IUT308_001To308Pixel[308-85];
		g_IUT308_SpBOneLinePixel[42][7] = 0;

		g_IUT308_SpBOneLinePixel[43][0] = g_IUT308_001To308Pixel[308-66];	
		g_IUT308_SpBOneLinePixel[43][1] = g_IUT308_001To308Pixel[308-44];	
		g_IUT308_SpBOneLinePixel[43][2] = g_IUT308_001To308Pixel[308-22];	
		g_IUT308_SpBOneLinePixel[43][3] = g_IUT308_001To308Pixel[308-154];	
		g_IUT308_SpBOneLinePixel[43][4] = g_IUT308_001To308Pixel[308-132];	
		g_IUT308_SpBOneLinePixel[43][5] = g_IUT308_001To308Pixel[308-110];	
		g_IUT308_SpBOneLinePixel[43][6] = g_IUT308_001To308Pixel[308-88];
		g_IUT308_SpBOneLinePixel[43][7] = 0;
	}
	else if (2==Type)
	{
		g_IUT308_SpBOneLinePixel[0][0] = g_IUT308_309To616Pixel[308-223];
		g_IUT308_SpBOneLinePixel[0][1] = g_IUT308_309To616Pixel[308-245];
		g_IUT308_SpBOneLinePixel[0][2] = g_IUT308_309To616Pixel[308-267];
		g_IUT308_SpBOneLinePixel[0][3] = g_IUT308_309To616Pixel[308-289];
		g_IUT308_SpBOneLinePixel[0][4] = g_IUT308_309To616Pixel[308-157];
		g_IUT308_SpBOneLinePixel[0][5] = g_IUT308_309To616Pixel[308-179];
		g_IUT308_SpBOneLinePixel[0][6] = g_IUT308_309To616Pixel[308-201];
		g_IUT308_SpBOneLinePixel[0][7] = 0;
		
		g_IUT308_SpBOneLinePixel[1][0] = g_IUT308_309To616Pixel[308-226];
		g_IUT308_SpBOneLinePixel[1][1] = g_IUT308_309To616Pixel[308-248];
		g_IUT308_SpBOneLinePixel[1][2] = g_IUT308_309To616Pixel[308-270];
		g_IUT308_SpBOneLinePixel[1][3] = g_IUT308_309To616Pixel[308-292];
		g_IUT308_SpBOneLinePixel[1][4] = g_IUT308_309To616Pixel[308-160];
		g_IUT308_SpBOneLinePixel[1][5] = g_IUT308_309To616Pixel[308-182];
		g_IUT308_SpBOneLinePixel[1][6] = g_IUT308_309To616Pixel[308-204];
		g_IUT308_SpBOneLinePixel[1][7] = 0;

		g_IUT308_SpBOneLinePixel[2][0] = g_IUT308_309To616Pixel[308-229];
		g_IUT308_SpBOneLinePixel[2][1] = g_IUT308_309To616Pixel[308-251];
		g_IUT308_SpBOneLinePixel[2][2] = g_IUT308_309To616Pixel[308-273];
		g_IUT308_SpBOneLinePixel[2][3] = g_IUT308_309To616Pixel[308-295];
		g_IUT308_SpBOneLinePixel[2][4] = g_IUT308_309To616Pixel[308-163];
		g_IUT308_SpBOneLinePixel[2][5] = g_IUT308_309To616Pixel[308-185];
		g_IUT308_SpBOneLinePixel[2][6] = g_IUT308_309To616Pixel[308-207];
		g_IUT308_SpBOneLinePixel[2][7] = 0;
		
		g_IUT308_SpBOneLinePixel[3][0] = g_IUT308_309To616Pixel[308-232];
		g_IUT308_SpBOneLinePixel[3][1] = g_IUT308_309To616Pixel[308-254];
		g_IUT308_SpBOneLinePixel[3][2] = g_IUT308_309To616Pixel[308-276];
		g_IUT308_SpBOneLinePixel[3][3] = g_IUT308_309To616Pixel[308-298];
		g_IUT308_SpBOneLinePixel[3][4] = g_IUT308_309To616Pixel[308-166];
		g_IUT308_SpBOneLinePixel[3][5] = g_IUT308_309To616Pixel[308-188];
		g_IUT308_SpBOneLinePixel[3][6] = g_IUT308_309To616Pixel[308-210];
		g_IUT308_SpBOneLinePixel[3][7] = 0;
		
		g_IUT308_SpBOneLinePixel[4][0] = g_IUT308_309To616Pixel[308-235];
		g_IUT308_SpBOneLinePixel[4][1] = g_IUT308_309To616Pixel[308-257];
		g_IUT308_SpBOneLinePixel[4][2] = g_IUT308_309To616Pixel[308-279];
		g_IUT308_SpBOneLinePixel[4][3] = g_IUT308_309To616Pixel[308-301];
		g_IUT308_SpBOneLinePixel[4][4] = g_IUT308_309To616Pixel[308-169];
		g_IUT308_SpBOneLinePixel[4][5] = g_IUT308_309To616Pixel[308-191];
		g_IUT308_SpBOneLinePixel[4][6] = g_IUT308_309To616Pixel[308-213];
		g_IUT308_SpBOneLinePixel[4][7] = 0;

		g_IUT308_SpBOneLinePixel[5][0] = g_IUT308_309To616Pixel[308-238];
		g_IUT308_SpBOneLinePixel[5][1] = g_IUT308_309To616Pixel[308-260];
		g_IUT308_SpBOneLinePixel[5][2] = g_IUT308_309To616Pixel[308-282];
		g_IUT308_SpBOneLinePixel[5][3] = g_IUT308_309To616Pixel[308-304];
		g_IUT308_SpBOneLinePixel[5][4] = g_IUT308_309To616Pixel[308-172];
		g_IUT308_SpBOneLinePixel[5][5] = g_IUT308_309To616Pixel[308-194];
		g_IUT308_SpBOneLinePixel[5][6] = g_IUT308_309To616Pixel[308-216];
		g_IUT308_SpBOneLinePixel[5][7] = 0;
				
		g_IUT308_SpBOneLinePixel[6][0] = g_IUT308_309To616Pixel[308-241];
		g_IUT308_SpBOneLinePixel[6][1] = g_IUT308_309To616Pixel[308-263];
		g_IUT308_SpBOneLinePixel[6][2] = g_IUT308_309To616Pixel[308-285];
		g_IUT308_SpBOneLinePixel[6][3] = g_IUT308_309To616Pixel[308-307];
		g_IUT308_SpBOneLinePixel[6][4] = g_IUT308_309To616Pixel[308-175];
		g_IUT308_SpBOneLinePixel[6][5] = g_IUT308_309To616Pixel[308-197];
		g_IUT308_SpBOneLinePixel[6][6] = g_IUT308_309To616Pixel[308-219];
		g_IUT308_SpBOneLinePixel[6][7] = 0;
		
		g_IUT308_SpBOneLinePixel[7][0] = g_IUT308_309To616Pixel[308-222];
		g_IUT308_SpBOneLinePixel[7][1] = g_IUT308_309To616Pixel[308-244];
		g_IUT308_SpBOneLinePixel[7][2] = g_IUT308_309To616Pixel[308-266];
		g_IUT308_SpBOneLinePixel[7][3] = g_IUT308_309To616Pixel[308-288];
		g_IUT308_SpBOneLinePixel[7][4] = g_IUT308_309To616Pixel[308-156];
		g_IUT308_SpBOneLinePixel[7][5] = g_IUT308_309To616Pixel[308-178];
		g_IUT308_SpBOneLinePixel[7][6] = g_IUT308_309To616Pixel[308-200];
		g_IUT308_SpBOneLinePixel[7][7] = 0;
		
		g_IUT308_SpBOneLinePixel[8][0] = g_IUT308_309To616Pixel[308-225];
		g_IUT308_SpBOneLinePixel[8][1] = g_IUT308_309To616Pixel[308-247];
		g_IUT308_SpBOneLinePixel[8][2] = g_IUT308_309To616Pixel[308-269];
		g_IUT308_SpBOneLinePixel[8][3] = g_IUT308_309To616Pixel[308-291];
		g_IUT308_SpBOneLinePixel[8][4] = g_IUT308_309To616Pixel[308-159];
		g_IUT308_SpBOneLinePixel[8][5] = g_IUT308_309To616Pixel[308-181];
		g_IUT308_SpBOneLinePixel[8][6] = g_IUT308_309To616Pixel[308-203];
		g_IUT308_SpBOneLinePixel[8][7] = 0;	

		g_IUT308_SpBOneLinePixel[9][0] = g_IUT308_309To616Pixel[308-228];
		g_IUT308_SpBOneLinePixel[9][1] = g_IUT308_309To616Pixel[308-250];
		g_IUT308_SpBOneLinePixel[9][2] = g_IUT308_309To616Pixel[308-272];
		g_IUT308_SpBOneLinePixel[9][3] = g_IUT308_309To616Pixel[308-294];
		g_IUT308_SpBOneLinePixel[9][4] = g_IUT308_309To616Pixel[308-162];
		g_IUT308_SpBOneLinePixel[9][5] = g_IUT308_309To616Pixel[308-184];
		g_IUT308_SpBOneLinePixel[9][6] = g_IUT308_309To616Pixel[308-206];
		g_IUT308_SpBOneLinePixel[9][7] = 0;
		
		g_IUT308_SpBOneLinePixel[10][0] = g_IUT308_309To616Pixel[308-231];
		g_IUT308_SpBOneLinePixel[10][1] = g_IUT308_309To616Pixel[308-253];
		g_IUT308_SpBOneLinePixel[10][2] = g_IUT308_309To616Pixel[308-275];
		g_IUT308_SpBOneLinePixel[10][3] = g_IUT308_309To616Pixel[308-297];
		g_IUT308_SpBOneLinePixel[10][4] = g_IUT308_309To616Pixel[308-165];
		g_IUT308_SpBOneLinePixel[10][5] = g_IUT308_309To616Pixel[308-187];
		g_IUT308_SpBOneLinePixel[10][6] = g_IUT308_309To616Pixel[308-209];
		g_IUT308_SpBOneLinePixel[10][7] = 0;
		
		g_IUT308_SpBOneLinePixel[11][0] = g_IUT308_309To616Pixel[308-234];	
		g_IUT308_SpBOneLinePixel[11][1] = g_IUT308_309To616Pixel[308-256];	
		g_IUT308_SpBOneLinePixel[11][2] = g_IUT308_309To616Pixel[308-278];	
		g_IUT308_SpBOneLinePixel[11][3] = g_IUT308_309To616Pixel[308-300];
		g_IUT308_SpBOneLinePixel[11][4] = g_IUT308_309To616Pixel[308-168];	
		g_IUT308_SpBOneLinePixel[11][5] = g_IUT308_309To616Pixel[308-190];	
		g_IUT308_SpBOneLinePixel[11][6] = g_IUT308_309To616Pixel[308-212];		
		g_IUT308_SpBOneLinePixel[11][7] = 0;

		g_IUT308_SpBOneLinePixel[12][0] = g_IUT308_309To616Pixel[308-237];
		g_IUT308_SpBOneLinePixel[12][1] = g_IUT308_309To616Pixel[308-259];
		g_IUT308_SpBOneLinePixel[12][2] = g_IUT308_309To616Pixel[308-281];
		g_IUT308_SpBOneLinePixel[12][3] = g_IUT308_309To616Pixel[308-303];
		g_IUT308_SpBOneLinePixel[12][4] = g_IUT308_309To616Pixel[308-171];
		g_IUT308_SpBOneLinePixel[12][5] = g_IUT308_309To616Pixel[308-193];
		g_IUT308_SpBOneLinePixel[12][6] = g_IUT308_309To616Pixel[308-215];
		g_IUT308_SpBOneLinePixel[12][7] = 0;

		g_IUT308_SpBOneLinePixel[13][0] = g_IUT308_309To616Pixel[308-240];
		g_IUT308_SpBOneLinePixel[13][1] = g_IUT308_309To616Pixel[308-262];
		g_IUT308_SpBOneLinePixel[13][2] = g_IUT308_309To616Pixel[308-284];
		g_IUT308_SpBOneLinePixel[13][3] = g_IUT308_309To616Pixel[308-306];
		g_IUT308_SpBOneLinePixel[13][4] = g_IUT308_309To616Pixel[308-174];
		g_IUT308_SpBOneLinePixel[13][5] = g_IUT308_309To616Pixel[308-196];
		g_IUT308_SpBOneLinePixel[13][6] = g_IUT308_309To616Pixel[308-218];
		g_IUT308_SpBOneLinePixel[13][7] = 0;

		g_IUT308_SpBOneLinePixel[14][0] = g_IUT308_309To616Pixel[308-221];	
		g_IUT308_SpBOneLinePixel[14][1] = g_IUT308_309To616Pixel[308-243];	
		g_IUT308_SpBOneLinePixel[14][2] = g_IUT308_309To616Pixel[308-265];	
		g_IUT308_SpBOneLinePixel[14][3] = g_IUT308_309To616Pixel[308-287];	
		g_IUT308_SpBOneLinePixel[14][4] = g_IUT308_309To616Pixel[308-155];	
		g_IUT308_SpBOneLinePixel[14][5] = g_IUT308_309To616Pixel[308-177];	
		g_IUT308_SpBOneLinePixel[14][6] = g_IUT308_309To616Pixel[308-199];		
		g_IUT308_SpBOneLinePixel[14][7] = 0;		

		g_IUT308_SpBOneLinePixel[15][0] = g_IUT308_309To616Pixel[308-224];	
		g_IUT308_SpBOneLinePixel[15][1] = g_IUT308_309To616Pixel[308-246];	
		g_IUT308_SpBOneLinePixel[15][2] = g_IUT308_309To616Pixel[308-268];	
		g_IUT308_SpBOneLinePixel[15][3] = g_IUT308_309To616Pixel[308-290];	
		g_IUT308_SpBOneLinePixel[15][4] = g_IUT308_309To616Pixel[308-158];	
		g_IUT308_SpBOneLinePixel[15][5] = g_IUT308_309To616Pixel[308-180];	
		g_IUT308_SpBOneLinePixel[15][6] = g_IUT308_309To616Pixel[308-202];	
		g_IUT308_SpBOneLinePixel[15][7] = 0;		
		
		g_IUT308_SpBOneLinePixel[16][0] = g_IUT308_309To616Pixel[308-227];	
		g_IUT308_SpBOneLinePixel[16][1] = g_IUT308_309To616Pixel[308-249];	
		g_IUT308_SpBOneLinePixel[16][2] = g_IUT308_309To616Pixel[308-271];	
		g_IUT308_SpBOneLinePixel[16][3] = g_IUT308_309To616Pixel[308-293];	
		g_IUT308_SpBOneLinePixel[16][4] = g_IUT308_309To616Pixel[308-161];	
		g_IUT308_SpBOneLinePixel[16][5] = g_IUT308_309To616Pixel[308-183];	
		g_IUT308_SpBOneLinePixel[16][6] = g_IUT308_309To616Pixel[308-205];		
		g_IUT308_SpBOneLinePixel[16][7] = 0;		

		g_IUT308_SpBOneLinePixel[17][0] = g_IUT308_309To616Pixel[308-230];	
		g_IUT308_SpBOneLinePixel[17][1] = g_IUT308_309To616Pixel[308-252];	
		g_IUT308_SpBOneLinePixel[17][2] = g_IUT308_309To616Pixel[308-274];	
		g_IUT308_SpBOneLinePixel[17][3] = g_IUT308_309To616Pixel[308-296];	
		g_IUT308_SpBOneLinePixel[17][4] = g_IUT308_309To616Pixel[308-164];	
		g_IUT308_SpBOneLinePixel[17][5] = g_IUT308_309To616Pixel[308-186];	
		g_IUT308_SpBOneLinePixel[17][6] = g_IUT308_309To616Pixel[308-208];	
		g_IUT308_SpBOneLinePixel[17][6] = 0;

		g_IUT308_SpBOneLinePixel[18][0] = g_IUT308_309To616Pixel[308-233];	
		g_IUT308_SpBOneLinePixel[18][1] = g_IUT308_309To616Pixel[308-255];	
		g_IUT308_SpBOneLinePixel[18][2] = g_IUT308_309To616Pixel[308-277];	
		g_IUT308_SpBOneLinePixel[18][3] = g_IUT308_309To616Pixel[308-299];	
		g_IUT308_SpBOneLinePixel[18][4] = g_IUT308_309To616Pixel[308-167];	
		g_IUT308_SpBOneLinePixel[18][5] = g_IUT308_309To616Pixel[308-189];	
		g_IUT308_SpBOneLinePixel[18][6] = g_IUT308_309To616Pixel[308-211];	
		g_IUT308_SpBOneLinePixel[18][7] = 0;	

		g_IUT308_SpBOneLinePixel[19][0] = g_IUT308_309To616Pixel[308-236];	
		g_IUT308_SpBOneLinePixel[19][1] = g_IUT308_309To616Pixel[308-258];	
		g_IUT308_SpBOneLinePixel[19][2] = g_IUT308_309To616Pixel[308-280];	
		g_IUT308_SpBOneLinePixel[19][3] = g_IUT308_309To616Pixel[308-302];	
		g_IUT308_SpBOneLinePixel[19][4] = g_IUT308_309To616Pixel[308-170];	
		g_IUT308_SpBOneLinePixel[19][5] = g_IUT308_309To616Pixel[308-192];	
		g_IUT308_SpBOneLinePixel[19][6] = g_IUT308_309To616Pixel[308-214];
		g_IUT308_SpBOneLinePixel[19][7] = 0;
		
		g_IUT308_SpBOneLinePixel[20][0] = g_IUT308_309To616Pixel[308-239];	
		g_IUT308_SpBOneLinePixel[20][1] = g_IUT308_309To616Pixel[308-261];	
		g_IUT308_SpBOneLinePixel[20][2] = g_IUT308_309To616Pixel[308-283];	
		g_IUT308_SpBOneLinePixel[20][3] = g_IUT308_309To616Pixel[308-305];	
		g_IUT308_SpBOneLinePixel[20][4] = g_IUT308_309To616Pixel[308-173];	
		g_IUT308_SpBOneLinePixel[20][5] = g_IUT308_309To616Pixel[308-195];	
		g_IUT308_SpBOneLinePixel[20][6] = g_IUT308_309To616Pixel[308-217];
		g_IUT308_SpBOneLinePixel[20][6] = 0;

		g_IUT308_SpBOneLinePixel[21][0] = g_IUT308_309To616Pixel[308-242];	
		g_IUT308_SpBOneLinePixel[21][1] = g_IUT308_309To616Pixel[308-264];	
		g_IUT308_SpBOneLinePixel[21][2] = g_IUT308_309To616Pixel[308-286];	
		g_IUT308_SpBOneLinePixel[21][3] = g_IUT308_309To616Pixel[308-308];	
		g_IUT308_SpBOneLinePixel[21][4] = g_IUT308_309To616Pixel[308-176];	
		g_IUT308_SpBOneLinePixel[21][5] = g_IUT308_309To616Pixel[308-198];	
		g_IUT308_SpBOneLinePixel[21][6] = g_IUT308_309To616Pixel[308-220];	
		g_IUT308_SpBOneLinePixel[21][7] = 0;
//---------------------------------------------------------------------------------
		g_IUT308_SpBOneLinePixel[22][0] = g_IUT308_309To616Pixel[308-47];
		g_IUT308_SpBOneLinePixel[22][1] = g_IUT308_309To616Pixel[308-25];
		g_IUT308_SpBOneLinePixel[22][2] = g_IUT308_309To616Pixel[308-3];
		g_IUT308_SpBOneLinePixel[22][3] = g_IUT308_309To616Pixel[308-135];
		g_IUT308_SpBOneLinePixel[22][4] = g_IUT308_309To616Pixel[308-113];
		g_IUT308_SpBOneLinePixel[22][5] = g_IUT308_309To616Pixel[308-91];
		g_IUT308_SpBOneLinePixel[22][6] = g_IUT308_309To616Pixel[308-69];
		g_IUT308_SpBOneLinePixel[22][7] = 0;

		g_IUT308_SpBOneLinePixel[23][0] = g_IUT308_309To616Pixel[308-50];
		g_IUT308_SpBOneLinePixel[23][1] = g_IUT308_309To616Pixel[308-28];
		g_IUT308_SpBOneLinePixel[23][2] = g_IUT308_309To616Pixel[308-6];
		g_IUT308_SpBOneLinePixel[23][3] = g_IUT308_309To616Pixel[308-138];
		g_IUT308_SpBOneLinePixel[23][4] = g_IUT308_309To616Pixel[308-116];
		g_IUT308_SpBOneLinePixel[23][5] = g_IUT308_309To616Pixel[308-94];
		g_IUT308_SpBOneLinePixel[23][6] = g_IUT308_309To616Pixel[308-72];
		g_IUT308_SpBOneLinePixel[23][7] = 0;

		g_IUT308_SpBOneLinePixel[24][0] = g_IUT308_309To616Pixel[308-53];
		g_IUT308_SpBOneLinePixel[24][1] = g_IUT308_309To616Pixel[308-31];
		g_IUT308_SpBOneLinePixel[24][2] = g_IUT308_309To616Pixel[308-9];
		g_IUT308_SpBOneLinePixel[24][3] = g_IUT308_309To616Pixel[308-141];
		g_IUT308_SpBOneLinePixel[24][4] = g_IUT308_309To616Pixel[308-119];
		g_IUT308_SpBOneLinePixel[24][5] = g_IUT308_309To616Pixel[308-97];
		g_IUT308_SpBOneLinePixel[24][6] = g_IUT308_309To616Pixel[308-75];
		g_IUT308_SpBOneLinePixel[24][7] = 0;

		g_IUT308_SpBOneLinePixel[25][0] = g_IUT308_309To616Pixel[308-56];
		g_IUT308_SpBOneLinePixel[25][1] = g_IUT308_309To616Pixel[308-34];
		g_IUT308_SpBOneLinePixel[25][2] = g_IUT308_309To616Pixel[308-12];
		g_IUT308_SpBOneLinePixel[25][3] = g_IUT308_309To616Pixel[308-144];
		g_IUT308_SpBOneLinePixel[25][4] = g_IUT308_309To616Pixel[308-122];
		g_IUT308_SpBOneLinePixel[25][5] = g_IUT308_309To616Pixel[308-100];
		g_IUT308_SpBOneLinePixel[25][6] = g_IUT308_309To616Pixel[308-78];
		g_IUT308_SpBOneLinePixel[25][7] = 0;

		g_IUT308_SpBOneLinePixel[26][0] = g_IUT308_309To616Pixel[308-59];
		g_IUT308_SpBOneLinePixel[26][1] = g_IUT308_309To616Pixel[308-37];
		g_IUT308_SpBOneLinePixel[26][2] = g_IUT308_309To616Pixel[308-15];
		g_IUT308_SpBOneLinePixel[26][3] = g_IUT308_309To616Pixel[308-147];
		g_IUT308_SpBOneLinePixel[26][4] = g_IUT308_309To616Pixel[308-125];
		g_IUT308_SpBOneLinePixel[26][5] = g_IUT308_309To616Pixel[308-103];
		g_IUT308_SpBOneLinePixel[26][6] = g_IUT308_309To616Pixel[308-81];//ok
		g_IUT308_SpBOneLinePixel[26][7] = 0;
		
		g_IUT308_SpBOneLinePixel[27][0] = g_IUT308_309To616Pixel[308-62];
		g_IUT308_SpBOneLinePixel[27][1] = g_IUT308_309To616Pixel[308-40];
		g_IUT308_SpBOneLinePixel[27][2] = g_IUT308_309To616Pixel[308-18];
		g_IUT308_SpBOneLinePixel[27][3] = g_IUT308_309To616Pixel[308-150];
		g_IUT308_SpBOneLinePixel[27][4] = g_IUT308_309To616Pixel[308-128];
		g_IUT308_SpBOneLinePixel[27][5] = g_IUT308_309To616Pixel[308-106];
		g_IUT308_SpBOneLinePixel[27][6] = g_IUT308_309To616Pixel[308-84]; //ok
		g_IUT308_SpBOneLinePixel[27][7] = 0;	

		g_IUT308_SpBOneLinePixel[28][0] = g_IUT308_309To616Pixel[308-65];
		g_IUT308_SpBOneLinePixel[28][1] = g_IUT308_309To616Pixel[308-43];
		g_IUT308_SpBOneLinePixel[28][2] = g_IUT308_309To616Pixel[308-21];
		g_IUT308_SpBOneLinePixel[28][3] = g_IUT308_309To616Pixel[308-153];
		g_IUT308_SpBOneLinePixel[28][4] = g_IUT308_309To616Pixel[308-131];
		g_IUT308_SpBOneLinePixel[28][5] = g_IUT308_309To616Pixel[308-109];
		g_IUT308_SpBOneLinePixel[28][6] = g_IUT308_309To616Pixel[308-87]; //ok
		g_IUT308_SpBOneLinePixel[28][7] = 0;
		
		g_IUT308_SpBOneLinePixel[29][0] = g_IUT308_309To616Pixel[308-46];
		g_IUT308_SpBOneLinePixel[29][1] = g_IUT308_309To616Pixel[308-24];
		g_IUT308_SpBOneLinePixel[29][2] = g_IUT308_309To616Pixel[308-2];
		g_IUT308_SpBOneLinePixel[29][3] = g_IUT308_309To616Pixel[308-134];
		g_IUT308_SpBOneLinePixel[29][4] = g_IUT308_309To616Pixel[308-112];
		g_IUT308_SpBOneLinePixel[29][5] = g_IUT308_309To616Pixel[308-90];
		g_IUT308_SpBOneLinePixel[29][6] = g_IUT308_309To616Pixel[308-68]; //ok
		g_IUT308_SpBOneLinePixel[29][7] = 0;
		
		g_IUT308_SpBOneLinePixel[30][0] = g_IUT308_309To616Pixel[308-49];
		g_IUT308_SpBOneLinePixel[30][1] = g_IUT308_309To616Pixel[308-27];
		g_IUT308_SpBOneLinePixel[30][2] = g_IUT308_309To616Pixel[308-5];
		g_IUT308_SpBOneLinePixel[30][3] = g_IUT308_309To616Pixel[308-137];
		g_IUT308_SpBOneLinePixel[30][4] = g_IUT308_309To616Pixel[308-115];
		g_IUT308_SpBOneLinePixel[30][5] = g_IUT308_309To616Pixel[308-93];
		g_IUT308_SpBOneLinePixel[30][6] = g_IUT308_309To616Pixel[308-71]; //ok
		g_IUT308_SpBOneLinePixel[30][7] = 0;

		g_IUT308_SpBOneLinePixel[31][0] = g_IUT308_309To616Pixel[308-52];
		g_IUT308_SpBOneLinePixel[31][1] = g_IUT308_309To616Pixel[308-30];
		g_IUT308_SpBOneLinePixel[31][2] = g_IUT308_309To616Pixel[308-8];
		g_IUT308_SpBOneLinePixel[31][3] = g_IUT308_309To616Pixel[308-140];
		g_IUT308_SpBOneLinePixel[31][4] = g_IUT308_309To616Pixel[308-118];
		g_IUT308_SpBOneLinePixel[31][5] = g_IUT308_309To616Pixel[308-96];
		g_IUT308_SpBOneLinePixel[31][6] = g_IUT308_309To616Pixel[308-74];//ok
		g_IUT308_SpBOneLinePixel[31][7] = 0;
		
		g_IUT308_SpBOneLinePixel[32][0] = g_IUT308_309To616Pixel[308-55];
		g_IUT308_SpBOneLinePixel[32][1] = g_IUT308_309To616Pixel[308-33];
		g_IUT308_SpBOneLinePixel[32][2] = g_IUT308_309To616Pixel[308-11];
		g_IUT308_SpBOneLinePixel[32][3] = g_IUT308_309To616Pixel[308-143];
		g_IUT308_SpBOneLinePixel[32][4] = g_IUT308_309To616Pixel[308-121];
		g_IUT308_SpBOneLinePixel[32][5] = g_IUT308_309To616Pixel[308-99];
		g_IUT308_SpBOneLinePixel[32][6] = g_IUT308_309To616Pixel[308-77]; //ok
		g_IUT308_SpBOneLinePixel[32][7] = 0;
//---------------------------------------------------------------------
		g_IUT308_SpBOneLinePixel[33][0] = g_IUT308_309To616Pixel[308-58];	
		g_IUT308_SpBOneLinePixel[33][1] = g_IUT308_309To616Pixel[308-36];	
		g_IUT308_SpBOneLinePixel[33][2] = g_IUT308_309To616Pixel[308-14];	
		g_IUT308_SpBOneLinePixel[33][3] = g_IUT308_309To616Pixel[308-146];	
		g_IUT308_SpBOneLinePixel[33][4] = g_IUT308_309To616Pixel[308-124];	
		g_IUT308_SpBOneLinePixel[33][5] = g_IUT308_309To616Pixel[308-102];	
		g_IUT308_SpBOneLinePixel[33][6] = g_IUT308_309To616Pixel[308-80];
		g_IUT308_SpBOneLinePixel[33][7] = 0;

		g_IUT308_SpBOneLinePixel[34][0] = g_IUT308_309To616Pixel[308-61];
		g_IUT308_SpBOneLinePixel[34][1] = g_IUT308_309To616Pixel[308-39];
		g_IUT308_SpBOneLinePixel[34][2] = g_IUT308_309To616Pixel[308-17];
		g_IUT308_SpBOneLinePixel[34][3] = g_IUT308_309To616Pixel[308-149];
		g_IUT308_SpBOneLinePixel[34][4] = g_IUT308_309To616Pixel[308-127];
		g_IUT308_SpBOneLinePixel[34][5] = g_IUT308_309To616Pixel[308-105];
		g_IUT308_SpBOneLinePixel[34][6] = g_IUT308_309To616Pixel[308-83];
		g_IUT308_SpBOneLinePixel[34][7] = 0;

		g_IUT308_SpBOneLinePixel[35][0] = g_IUT308_309To616Pixel[308-64];
		g_IUT308_SpBOneLinePixel[35][1] = g_IUT308_309To616Pixel[308-42];	
		g_IUT308_SpBOneLinePixel[35][2] = g_IUT308_309To616Pixel[308-20];	
		g_IUT308_SpBOneLinePixel[35][3] = g_IUT308_309To616Pixel[308-152];	
		g_IUT308_SpBOneLinePixel[35][4] = g_IUT308_309To616Pixel[308-130];	
		g_IUT308_SpBOneLinePixel[35][5] = g_IUT308_309To616Pixel[308-108];	
		g_IUT308_SpBOneLinePixel[35][6] = g_IUT308_309To616Pixel[308-86];
		g_IUT308_SpBOneLinePixel[35][7] = 0;

		g_IUT308_SpBOneLinePixel[36][0] = g_IUT308_309To616Pixel[308-45];
		g_IUT308_SpBOneLinePixel[36][1] = g_IUT308_309To616Pixel[308-23];	
		g_IUT308_SpBOneLinePixel[36][2] = g_IUT308_309To616Pixel[308-1];	
		g_IUT308_SpBOneLinePixel[36][3] = g_IUT308_309To616Pixel[308-133];	
		g_IUT308_SpBOneLinePixel[36][4] = g_IUT308_309To616Pixel[308-111];	
		g_IUT308_SpBOneLinePixel[36][5] = g_IUT308_309To616Pixel[308-89];	
		g_IUT308_SpBOneLinePixel[36][6] = g_IUT308_309To616Pixel[308-67];
		g_IUT308_SpBOneLinePixel[36][7] = 0;

		g_IUT308_SpBOneLinePixel[37][0] = g_IUT308_309To616Pixel[308-48];
		g_IUT308_SpBOneLinePixel[37][1] = g_IUT308_309To616Pixel[308-26];	
		g_IUT308_SpBOneLinePixel[37][2] = g_IUT308_309To616Pixel[308-4];	
		g_IUT308_SpBOneLinePixel[37][3] = g_IUT308_309To616Pixel[308-136];	
		g_IUT308_SpBOneLinePixel[37][4] = g_IUT308_309To616Pixel[308-114];	
		g_IUT308_SpBOneLinePixel[37][5] = g_IUT308_309To616Pixel[308-92];	
		g_IUT308_SpBOneLinePixel[37][6] = g_IUT308_309To616Pixel[308-70];
		g_IUT308_SpBOneLinePixel[37][7] = 0;

		g_IUT308_SpBOneLinePixel[38][0] = g_IUT308_309To616Pixel[308-51];	
		g_IUT308_SpBOneLinePixel[38][1] = g_IUT308_309To616Pixel[308-29];	
		g_IUT308_SpBOneLinePixel[38][2] = g_IUT308_309To616Pixel[308-7];	
		g_IUT308_SpBOneLinePixel[38][3] = g_IUT308_309To616Pixel[308-139];	
		g_IUT308_SpBOneLinePixel[38][4] = g_IUT308_309To616Pixel[308-117];	
		g_IUT308_SpBOneLinePixel[38][5] = g_IUT308_309To616Pixel[308-95];	
		g_IUT308_SpBOneLinePixel[38][6] = g_IUT308_309To616Pixel[308-73];
		g_IUT308_SpBOneLinePixel[38][7] = 0;
		
		g_IUT308_SpBOneLinePixel[39][0] = g_IUT308_309To616Pixel[308-54];
		g_IUT308_SpBOneLinePixel[39][1] = g_IUT308_309To616Pixel[308-32];	
		g_IUT308_SpBOneLinePixel[39][2] = g_IUT308_309To616Pixel[308-10];	
		g_IUT308_SpBOneLinePixel[39][3] = g_IUT308_309To616Pixel[308-142];	
		g_IUT308_SpBOneLinePixel[39][4] = g_IUT308_309To616Pixel[308-120];	
		g_IUT308_SpBOneLinePixel[39][5] = g_IUT308_309To616Pixel[308-98];	
		g_IUT308_SpBOneLinePixel[39][6] = g_IUT308_309To616Pixel[308-76];
		g_IUT308_SpBOneLinePixel[39][7] = 0;
		
		g_IUT308_SpBOneLinePixel[40][0] = g_IUT308_309To616Pixel[308-57];
		g_IUT308_SpBOneLinePixel[40][1] = g_IUT308_309To616Pixel[308-35];	
		g_IUT308_SpBOneLinePixel[40][2] = g_IUT308_309To616Pixel[308-13];	
		g_IUT308_SpBOneLinePixel[40][3] = g_IUT308_309To616Pixel[308-145];	
		g_IUT308_SpBOneLinePixel[40][4] = g_IUT308_309To616Pixel[308-123];	
		g_IUT308_SpBOneLinePixel[40][5] = g_IUT308_309To616Pixel[308-101];	
		g_IUT308_SpBOneLinePixel[40][6] = g_IUT308_309To616Pixel[308-79];
		g_IUT308_SpBOneLinePixel[40][7] = 0;

		g_IUT308_SpBOneLinePixel[41][0] = g_IUT308_309To616Pixel[308-60];
		g_IUT308_SpBOneLinePixel[41][1] = g_IUT308_309To616Pixel[308-38];	
		g_IUT308_SpBOneLinePixel[41][2] = g_IUT308_309To616Pixel[308-16];	
		g_IUT308_SpBOneLinePixel[41][3] = g_IUT308_309To616Pixel[308-148];	
		g_IUT308_SpBOneLinePixel[41][4] = g_IUT308_309To616Pixel[308-126];	
		g_IUT308_SpBOneLinePixel[41][5] = g_IUT308_309To616Pixel[308-104];	
		g_IUT308_SpBOneLinePixel[41][6] = g_IUT308_309To616Pixel[308-82];
		g_IUT308_SpBOneLinePixel[41][7] = 0;
	
		g_IUT308_SpBOneLinePixel[42][0] = g_IUT308_309To616Pixel[308-63];	
		g_IUT308_SpBOneLinePixel[42][1] = g_IUT308_309To616Pixel[308-41];	
		g_IUT308_SpBOneLinePixel[42][2] = g_IUT308_309To616Pixel[308-19];	
		g_IUT308_SpBOneLinePixel[42][3] = g_IUT308_309To616Pixel[308-151];	
		g_IUT308_SpBOneLinePixel[42][4] = g_IUT308_309To616Pixel[308-129];	
		g_IUT308_SpBOneLinePixel[42][5] = g_IUT308_309To616Pixel[308-107];	
		g_IUT308_SpBOneLinePixel[42][6] = g_IUT308_309To616Pixel[308-85];
		g_IUT308_SpBOneLinePixel[42][7] = 0;

		g_IUT308_SpBOneLinePixel[43][0] = g_IUT308_309To616Pixel[308-66];	
		g_IUT308_SpBOneLinePixel[43][1] = g_IUT308_309To616Pixel[308-44];	
		g_IUT308_SpBOneLinePixel[43][2] = g_IUT308_309To616Pixel[308-22];	
		g_IUT308_SpBOneLinePixel[43][3] = g_IUT308_309To616Pixel[308-154];	
		g_IUT308_SpBOneLinePixel[43][4] = g_IUT308_309To616Pixel[308-132];	
		g_IUT308_SpBOneLinePixel[43][5] = g_IUT308_309To616Pixel[308-110];	
		g_IUT308_SpBOneLinePixel[43][6] = g_IUT308_309To616Pixel[308-88];
		g_IUT308_SpBOneLinePixel[43][7] = 0;
	}
}
