#include "StdAfx.h"
#include "Global.h"
#include "Thread.h"

CPtrArray g_ptrCncList;
UNION_CNC_DATA_SEND unionCncData[50000];
int gnCncXMax,gnCncYMax;

unsigned short g_iCncDataTemp[50000*16];
unsigned short g_ZippedCncData[50000*16];
int g_iCncDataSizeZipped;
void ZipCncData();
int SendCncData()
{
	int nIndex,nSize;
	ST_CNC_DATA_ALL *pCncData;
	nSize = g_ptrCncList.GetSize();
	for (nIndex=0; nIndex<nSize; nIndex++)
	{
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(nIndex);
		unionCncData[nIndex].stBuff.m_iX = pCncData->m_iX;
		unionCncData[nIndex].stBuff.m_iY = pCncData->m_iY;
		unionCncData[nIndex].stBuff.m_nMaxSpeed = pCncData->m_nMaxSpeed;
		unionCncData[nIndex].stBuff.m_nEndSpeed = pCncData->m_nEndSpeed;
		unionCncData[nIndex].stBuff.m_nCmdType = pCncData->m_nCmdType;
		unionCncData[nIndex].stBuff.m_nDccPerCent = (u16)( pCncData->m_dDccPerCent * 4096.0 );
	}
	ZipCncData();
	if (gUSB.WriteBulk((char*)(&g_ZippedCncData),g_iCncDataSizeZipped) != g_iCncDataSizeZipped)
	{
		return -1;
	}
	return 0;
}

void ZipCncData()
{
	int i,j;
	int nSizeOrg,nZeroNum;
	int nSize = g_ptrCncList.GetSize();
	
	g_iCncDataSizeZipped = 0;
	nSizeOrg = CNC_DATA_SIZE*nSize; //unsigned short数据大小
	
	memcpy( (char*)(&g_iCncDataTemp[0]),(char*)(&unionCncData[0].u8Buff[0]), CNC_DATA_SIZE*nSize);
	memset( (char*)(&g_ZippedCncData[0]),0,CNC_DATA_SIZE*nSize);
	
	i=0;
	j=0;
	nZeroNum=0;
	
	for (i=0;i<nSizeOrg;i++)
	{
		if (g_iCncDataTemp[i] == 0)
		{
			nZeroNum++;
			if (nZeroNum >= 65000) //防止超过65536
			{
				g_ZippedCncData[j]=0;
				j++;
				g_ZippedCncData[j]=nZeroNum;
				j++;
				nZeroNum=0;
			}
		}
		else
		{
			if (nZeroNum != 0)
			{
				g_ZippedCncData[j]=0;
				j++;
				g_ZippedCncData[j]=nZeroNum;
				j++;
				nZeroNum=0;
			}
			g_ZippedCncData[j]=g_iCncDataTemp[i];
			j++;
		}
	}
	
	if (nZeroNum != 0)
	{
		g_ZippedCncData[j]=0;
		j++;
		g_ZippedCncData[j]=nZeroNum;
		j++;
		nZeroNum=0;
	}
	g_iCncDataSizeZipped = j*2;
}


void CalculateAngles()
{
	int i;
	ST_CNC_DATA_ALL *pCncData;
	int iLastX,iLastY;
	double dLastAngle;
	int nSize;
	nSize =g_ptrCncList.GetSize();
	if (nSize == 0)
	{
		return;
	}
	
	pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(0);
	pCncData->m_iDeltaX = 0;
	pCncData->m_iDeltaY = 0;
	pCncData->m_dAngle = 0;
	pCncData->m_dDeltaAngle = 0;
	
	iLastX = pCncData->m_iX;
	iLastY = pCncData->m_iY;
	dLastAngle = pCncData->m_dAngle;
	
	for (i=1;i<nSize;i++)
	{
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		pCncData->m_iDeltaX = pCncData->m_iX - iLastX;
		pCncData->m_iDeltaY = pCncData->m_iY - iLastY;
		pCncData->m_dAngle = atan2((double)pCncData->m_iDeltaY, (double)pCncData->m_iDeltaX);
		pCncData->m_dDeltaAngle = pCncData->m_dAngle - dLastAngle;
		
		if (pCncData->m_dDeltaAngle>PI)
		{
			pCncData->m_dDeltaAngle = pCncData->m_dDeltaAngle - 2.0*PI;
		}
		else if (pCncData->m_dDeltaAngle <= -PI)
		{
			pCncData->m_dDeltaAngle = pCncData->m_dDeltaAngle + 2.0*PI;
		}
		
		iLastX = pCncData->m_iX;
		iLastY = pCncData->m_iY;
		dLastAngle = pCncData->m_dAngle;
	}
}

void GetLongAxialSteps()
{
	int i;
	ST_CNC_DATA_ALL *pCncData;
	int nSize;
	nSize =g_ptrCncList.GetSize();
	if (nSize == 0)
	{
		return;
	}
	for (i=0;i<nSize;i++)
	{
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
//获得长轴脉冲数
		pCncData->m_nLongAxialStep = 
			(abs(pCncData->m_iDeltaX) > abs(pCncData->m_iDeltaY))?
			abs(pCncData->m_iDeltaX):abs(pCncData->m_iDeltaY); 
	}
}

void CalcCurvature()
{
	int i;
	ST_CNC_DATA_ALL *pCncData;
	double dX,dY,dR;

	int nSize;
	nSize =g_ptrCncList.GetSize();
	if (nSize == 0)
	{
		return;
	}
	pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(0);
	pCncData->m_dCurvature = 0;

	for (i=1;i<nSize;i++)
	{
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		dX = pCncData->m_iDeltaX;
		dY = pCncData->m_iDeltaY;
		dR = sqrt(dX*dX+dY*dY);
		if (dR == 0)
		{
			pCncData->m_dCurvature = 0;
		}
		else
		{
			pCncData->m_dCurvature = fabs(pCncData->m_dDeltaAngle)/( dR / gMacSet.getPPMMY() );
			pCncData->m_dCurvature = pCncData->m_dCurvature*180.0;
		}
	}
}

void CalcSdPercent(void)
{
	int i,nSize;
	ST_CNC_DATA_ALL *pCncData;
	double dDeltaX,dDeltaY;
	double dR;
	nSize = g_ptrCncList.GetSize();
	if (nSize == 0)
	{
		return;
	}
	for (i=0;i<nSize;i++)
	{
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		dDeltaX = fabs((double)pCncData->m_iDeltaX);
		dDeltaY = fabs((double)pCncData->m_iDeltaY);
		dR = sqrt((double)(dDeltaX*dDeltaX+dDeltaY*dDeltaY));
		if ( dDeltaX > dDeltaY )
		{
			if (dDeltaX == 0.0)
			{
				pCncData->m_dDccPerCent = 1.0;
			}
			else
			{
				pCncData->m_dDccPerCent = dR/dDeltaX;
			}
		}
		else
		{
			if (dDeltaY == 0.0)
			{
				pCncData->m_dDccPerCent = 1.0;
			}
			else
			{
				pCncData->m_dDccPerCent = dR/dDeltaY;
			}
		}
	}
}

void CalcCncSpeed(void)
{
	int i,nSize;
	ST_CNC_DATA_ALL *pCncData;
	ST_CNC_DATA_ALL *pCncDataNext;
	nSize = g_ptrCncList.GetSize();
	if (nSize == 0)
	{
		return;
	}

	pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(nSize-1);
	pCncData->m_nEndSpeed = 0;
	pCncData->m_nMaxSpeed = pCncData->m_nLongAxialStep;
	if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdMax)
	{
		pCncData->m_nMaxSpeed = gSpdLimit.m_spdMax;
	}

	for (i=nSize-2;i>=0;i--) 
	{
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		pCncDataNext = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i+1);
		if (pCncDataNext->m_nCmdType == TYPE_MOVE) //下一条指令是移动
		{
			pCncData->m_nEndSpeed = 0;
			pCncData->m_nMaxSpeed = pCncData->m_nLongAxialStep;
			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdMax)
			{
				pCncData->m_nMaxSpeed = gSpdLimit.m_spdMax;
			}
			continue;
		}


		if (fabs(pCncDataNext->m_dDeltaAngle*180.0/PI) > SD_LV0_ANGLE)
		{
			pCncData->m_nEndSpeed = 0;
			pCncData->m_nMaxSpeed = pCncData->m_nLongAxialStep;
			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdMax)
			{
				pCncData->m_nMaxSpeed = gSpdLimit.m_spdMax;
			}
			continue;
		}
		else if (fabs(pCncDataNext->m_dDeltaAngle*180.0/PI) > SD_LV1_ANGLE)
		{
			pCncData->m_nEndSpeed = pCncDataNext->m_nMaxSpeed;
			if (pCncData->m_nEndSpeed > gSpdLimit.m_spdLV1)
			{
				pCncData->m_nEndSpeed = gSpdLimit.m_spdLV1;
			}
			pCncData->m_nMaxSpeed = (pCncData->m_nEndSpeed+pCncData->m_nLongAxialStep);
			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdMax)
			{
				pCncData->m_nMaxSpeed = gSpdLimit.m_spdMax;
			}
			continue;
		}
		else if( pCncData->m_nLongAxialStep > (gMacSet.getCurveLen()*90) )
		{
			pCncData->m_nEndSpeed = pCncDataNext->m_nMaxSpeed;
			pCncData->m_nMaxSpeed = (pCncData->m_nEndSpeed+pCncData->m_nLongAxialStep);
			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdMax)
			{
				pCncData->m_nMaxSpeed = gSpdLimit.m_spdMax;
			}
			continue;
		}

//		if (pCncDataNext->m_dCurvature > CURVATURE_R002 )
		if (pCncDataNext->m_dCurvature > CURVATURE_R010 )
		{
			pCncData->m_nEndSpeed = pCncDataNext->m_nMaxSpeed;
			if (pCncData->m_nEndSpeed > gSpdLimit.m_spdLV2_R002)
			{
				pCncData->m_nEndSpeed = gSpdLimit.m_spdLV2_R002;
			}
			pCncData->m_nMaxSpeed = (pCncData->m_nEndSpeed+pCncData->m_nLongAxialStep);
			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdLV2_R002)
			{
				pCncData->m_nMaxSpeed = gSpdLimit.m_spdLV2_R002;
			}	
		}
// 		else if (pCncDataNext->m_dCurvature > CURVATURE_R004 )
// 		{
// 			pCncData->m_nEndSpeed = pCncDataNext->m_nMaxSpeed;
// 			if (pCncData->m_nEndSpeed > gSpdLimit.m_spdLV3_R004)
// 			{
// 				pCncData->m_nEndSpeed = gSpdLimit.m_spdLV3_R004;
// 			}
// 			pCncData->m_nMaxSpeed = (pCncData->m_nEndSpeed+pCncData->m_nLongAxialStep);
// 			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdLV3_R004)
// 			{
// 				pCncData->m_nMaxSpeed = gSpdLimit.m_spdLV3_R004;
// 			}
// 		}
// 		else if (pCncDataNext->m_dCurvature > CURVATURE_R005 )
// 		{
// 			pCncData->m_nEndSpeed = pCncDataNext->m_nMaxSpeed;
// 			if (pCncData->m_nEndSpeed > gSpdLimit.m_spdLV4_R005)
// 			{
// 				pCncData->m_nEndSpeed = gSpdLimit.m_spdLV4_R005;
// 			}
// 			pCncData->m_nMaxSpeed = (pCncData->m_nEndSpeed+pCncData->m_nLongAxialStep);
// 			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdLV4_R005)
// 			{
// 				pCncData->m_nMaxSpeed = gSpdLimit.m_spdLV4_R005;
// 			}
// 		}
// 		else if(pCncDataNext->m_dCurvature > CURVATURE_R010 )
// 		{
// 			pCncData->m_nEndSpeed = pCncDataNext->m_nMaxSpeed;
// 			if (pCncData->m_nEndSpeed > gSpdLimit.m_spdLV5_R010)
// 			{
// 				pCncData->m_nEndSpeed = gSpdLimit.m_spdLV5_R010;
// 			}
// 			pCncData->m_nMaxSpeed = (pCncData->m_nEndSpeed+pCncData->m_nLongAxialStep);
// 			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdLV5_R010)
// 			{
// 				pCncData->m_nMaxSpeed = gSpdLimit.m_spdLV5_R010;
// 			}
// 		}
// 		else if(pCncDataNext->m_dCurvature > CURVATURE_R020 )
// 		{
// 			pCncData->m_nEndSpeed = pCncDataNext->m_nMaxSpeed;
// 			if (pCncData->m_nEndSpeed > gSpdLimit.m_spdLV6_R020)
// 			{
// 				pCncData->m_nEndSpeed = gSpdLimit.m_spdLV6_R020;
// 			}
// 			pCncData->m_nMaxSpeed = (pCncData->m_nEndSpeed+pCncData->m_nLongAxialStep);
// 			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdLV6_R020)
// 			{
// 				pCncData->m_nMaxSpeed = gSpdLimit.m_spdLV6_R020;
// 			}
// 		}
// 		else if(pCncDataNext->m_dCurvature > CURVATURE_R050 )
// 		{
// 			pCncData->m_nEndSpeed = pCncDataNext->m_nMaxSpeed;
// 			if (pCncData->m_nEndSpeed > gSpdLimit.m_spdLV7_R050)
// 			{
// 				pCncData->m_nEndSpeed = gSpdLimit.m_spdLV7_R050;
// 			}
// 			pCncData->m_nMaxSpeed = (pCncData->m_nEndSpeed+pCncData->m_nLongAxialStep);
// 			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdLV7_R050)
// 			{
// 				pCncData->m_nMaxSpeed = gSpdLimit.m_spdLV7_R050;
// 			}
// 		}
		else if(pCncDataNext->m_dCurvature > CURVATURE_R100 )
		{
			pCncData->m_nEndSpeed = pCncDataNext->m_nMaxSpeed;
			if (pCncData->m_nEndSpeed > gSpdLimit.m_spdLV8_R100)
			{
				pCncData->m_nEndSpeed = gSpdLimit.m_spdLV8_R100;
			}
			pCncData->m_nMaxSpeed = (pCncData->m_nEndSpeed+pCncData->m_nLongAxialStep);
			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdLV8_R100)
			{
				pCncData->m_nMaxSpeed = gSpdLimit.m_spdLV8_R100;
			}
		}
		else if(pCncDataNext->m_dCurvature > CURVATURE_R150 )
		{
			pCncData->m_nEndSpeed = pCncDataNext->m_nMaxSpeed;
			if (pCncData->m_nEndSpeed > gSpdLimit.m_spdLV9_R150)
			{
				pCncData->m_nEndSpeed = gSpdLimit.m_spdLV9_R150;
			}
			pCncData->m_nMaxSpeed = (pCncData->m_nEndSpeed+pCncData->m_nLongAxialStep);
			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdLV9_R150)
			{
				pCncData->m_nMaxSpeed = gSpdLimit.m_spdLV9_R150;
			}
		}
		else if(pCncDataNext->m_dCurvature > CURVATURE_R200 )
		{
			pCncData->m_nEndSpeed = pCncDataNext->m_nMaxSpeed;
			if (pCncData->m_nEndSpeed > gSpdLimit.m_spdLV10_R200)
			{
				pCncData->m_nEndSpeed = gSpdLimit.m_spdLV10_R200;
			}
			pCncData->m_nMaxSpeed = (pCncData->m_nEndSpeed+pCncData->m_nLongAxialStep);
			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdLV10_R200)
			{
				pCncData->m_nMaxSpeed = gSpdLimit.m_spdLV10_R200;
			}
		}
		else if(pCncDataNext->m_dCurvature > CURVATURE_R300 )
		{
			pCncData->m_nEndSpeed = pCncDataNext->m_nMaxSpeed;
			if (pCncData->m_nEndSpeed > gSpdLimit.m_spdLV11_R300)
			{
				pCncData->m_nEndSpeed = gSpdLimit.m_spdLV11_R300;
			}
			pCncData->m_nMaxSpeed = (pCncData->m_nEndSpeed+pCncData->m_nLongAxialStep);
			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdLV11_R300)
			{
				pCncData->m_nMaxSpeed = gSpdLimit.m_spdLV11_R300;
			}
		}
		else
		{
			pCncData->m_nEndSpeed = pCncDataNext->m_nMaxSpeed;
			if (pCncData->m_nEndSpeed > gSpdLimit.m_spdMax)
			{
				pCncData->m_nEndSpeed = gSpdLimit.m_spdMax;
			}
			pCncData->m_nMaxSpeed = (pCncData->m_nEndSpeed+pCncData->m_nLongAxialStep);
			if (pCncData->m_nMaxSpeed > gSpdLimit.m_spdMax)
			{
				pCncData->m_nMaxSpeed = gSpdLimit.m_spdMax;
			}
		}
	}
}

void AddOverCutData()
{
	int i;
	int nDataSize = g_ptrCncList.GetSize();
	ST_CNC_DATA_ALL* pCutData;
	ST_CNC_DATA_ALL* pCutData1;
	ST_CNC_DATA_ALL* pCutDataAdd;
	
	int iDeltaX,iDeltaY,iDeltaX1,iDeltaY1;
	if (0 == gMacSet.getOverCutLen())
	{
		return;
	}
	for (i=1;i<nDataSize;i++)
	{
		pCutData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		pCutData1 = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i-1);
		
		if( (TYPE_MOVE == pCutData1->m_nCmdType) && (TYPE_CUT == pCutData->m_nCmdType) ) 
			//是一段闭合曲线的起始 在此段数据之前后退 gMacSet.getOverCutLen()
		{
			//改变抬笔目标 (沿着反向移动)
			iDeltaX = (int)( gMacSet.getOverCutLen() * cos(pCutData->m_dAngle) );
			iDeltaY = (int)( gMacSet.getOverCutLen() * sin(pCutData->m_dAngle) );
			pCutData1->m_iX = pCutData1->m_iX-iDeltaX;
			pCutData1->m_iY = pCutData1->m_iY-iDeltaY;
		}
		else if ((TYPE_CUT == pCutData1->m_nCmdType) && (TYPE_MOVE == pCutData->m_nCmdType)) 
			//是一段闭合曲线的结束 在此段数据之后前进 gMacSet.getOverCutLen()
		{
			iDeltaX = (int)(gMacSet.getOverCutLen() * cos(pCutData1->m_dAngle) );
			iDeltaY = (int)(gMacSet.getOverCutLen() * sin(pCutData1->m_dAngle) );
			pCutData1->m_iX = pCutData1->m_iX+iDeltaX;
			pCutData1->m_iY = pCutData1->m_iY+iDeltaY;
		}
		else if((TYPE_CUT == pCutData1->m_nCmdType) && (TYPE_CUT == pCutData->m_nCmdType))
		{ //当前点的角度变化量
			if( ( fabs(pCutData->m_dDeltaAngle*180/PI) > OVERCUT_ANGLE )	//是锐角
				&& ( fabs(pCutData->m_dDeltaAngle*180/PI) < 120.0 )	) 

			{
				iDeltaX = (int)( gMacSet.getOverCutLen() * cos(pCutData1->m_dAngle) );
				iDeltaY = (int)( gMacSet.getOverCutLen() * sin(pCutData1->m_dAngle) );
				pCutData1->m_iX = pCutData1->m_iX+iDeltaX;
				pCutData1->m_iY = pCutData1->m_iY+iDeltaY;
				
				pCutDataAdd = new ST_CNC_DATA_ALL;
				iDeltaX1 = (int)( gMacSet.getOverCutLen() * cos(pCutData->m_dAngle) );
				iDeltaY1 = (int)( gMacSet.getOverCutLen() * sin(pCutData->m_dAngle) );	
				pCutDataAdd->m_nCmdType = TYPE_CUT;
				pCutDataAdd->m_iX = pCutData1->m_iX-iDeltaX-iDeltaX1;
				pCutDataAdd->m_iY = pCutData1->m_iY-iDeltaY-iDeltaY1;

				g_ptrCncList.InsertAt(i,pCutDataAdd);
				nDataSize++;
				i++;
			}
		}
	}
	
	pCutData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(nDataSize - 1);
	if (pCutData->m_nCmdType == TYPE_CUT) //最后一个数据是落笔
	{
		iDeltaX = (int)(gMacSet.getOverCutLen() * cos(pCutData->m_dAngle) );
		iDeltaY = (int)(gMacSet.getOverCutLen() * sin(pCutData->m_dAngle) );
		pCutData->m_iX = pCutData->m_iX+iDeltaX;
		pCutData->m_iY = pCutData->m_iY+iDeltaY;
	}
	
	for (i=0;i<nDataSize;i++)//计算 m_iDeltaX m_iDeltaY m_dAngle m_dDeltaAngle
	{
		pCutData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		if (0 == i)
		{
			pCutData->m_iDeltaX = 0;
			pCutData->m_iDeltaY = 0;
			pCutData->m_dAngle = 0.0;
			pCutData->m_dDeltaAngle = 0.0;
		}
		else
		{
			pCutData1 = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i-1);
			pCutData->m_iDeltaX = pCutData->m_iX - pCutData1->m_iX;
			pCutData->m_iDeltaY = pCutData->m_iY - pCutData1->m_iY;
			pCutData->m_dAngle = atan2((double)pCutData->m_iDeltaY,(double)pCutData->m_iDeltaX);
			pCutData->m_dDeltaAngle = pCutData->m_dAngle - pCutData1->m_dAngle;
		}
	}
}

void dumpCutDataToFile()
{
	int i;
	ST_CNC_DATA_ALL *pCncData;
	CFile fileData;
	CString strTemp;
	CString strFileName;
	int nSize;
	strFileName.Format("d:\\CutData.csv");
	fileData.Open(strFileName,CFile::modeCreate|CFile::modeReadWrite|CFile::typeBinary);
	nSize = g_ptrCncList.GetSize();
	strTemp.Format("目标X,目标Y,DeltaX,DeltaY,加速次数,角度,角度变化,曲率,降速比,MaxSpd,EndSpd,类型\n");

	fileData.Write(strTemp.GetBuffer(0),strTemp.GetLength());
	for (i=0;i<nSize;i++)
	{
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
	
//		strTemp.Format("%d,%d, %d,%d,%d, %f,%f,%f,%f, %d,%d,%d\n",
		strTemp.Format("%d,%d, %d,%d,%d, %f,%f,%f,%d, %d,%d,%d\n",
			pCncData->m_iX,
			pCncData->m_iY,

			pCncData->m_iDeltaX,
			pCncData->m_iDeltaY,
			pCncData->m_nLongAxialStep,

			pCncData->m_dAngle*180.0/PI,
			pCncData->m_dDeltaAngle*180.0/PI,
			pCncData->m_dCurvature,
//			pCncData->m_dDccPerCent,
			(u16)( pCncData->m_dDccPerCent * 4096.0 ),
			pCncData->m_nMaxSpeed,
			pCncData->m_nEndSpeed,
			pCncData->m_nCmdType);
		fileData.Write(strTemp.GetBuffer(0),strTemp.GetLength());
	}
	fileData.Close();
	AfxMessageBox(strFileName+" Saved");
}

void ReleaseCncDataBuffer()
{
	int i;
	ST_CNC_DATA_ALL* pCutData;
	for (i=0;i<g_ptrCncList.GetSize();i++)
	{
		pCutData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		delete pCutData;
	}
	g_ptrCncList.RemoveAll();
}


void GetCncMaxPulse()
{
	int nSize;
	ST_CNC_DATA_ALL *pCncData;
	int nIndex;
	nSize = g_ptrCncList.GetSize();
	
	pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(0);
	gnCncXMax = pCncData->m_iX;
	gnCncYMax = pCncData->m_iY;
	
	for (nIndex=1; nIndex<nSize; nIndex++)
	{
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(nIndex);
		gnCncXMax = (gnCncXMax > pCncData->m_iX)? gnCncXMax : pCncData->m_iX;
		gnCncYMax = (gnCncYMax > pCncData->m_iY)? gnCncYMax : pCncData->m_iY;
	}
	return;
}
