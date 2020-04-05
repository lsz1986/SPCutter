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
		unionCncData[nIndex].stBuff.m_nEndSpeed = pCncData->m_nMaxEndSpeed;
		unionCncData[nIndex].stBuff.m_cCmdType = pCncData->m_cCmdType;
		unionCncData[nIndex].stBuff.m_cNull = 0;
		
	}
	ZipCncData();
	if (gCommu.WriteBulk((char*)(&g_ZippedCncData),g_iCncDataSizeZipped) != g_iCncDataSizeZipped)
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

void RemoveDupPoints()
{
	int i;
	ST_CNC_DATA_ALL *pCncData1;
	ST_CNC_DATA_ALL *pCncData2;
	ST_CNC_DATA_ALL *pCncData3;
	ST_CNC_DATA_ALL *pCncData4;
	int nSize;
	nSize = g_ptrCncList.GetSize();
	for (i = 1; i < nSize-4; i++)
	{
		pCncData1 = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		pCncData2 = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i + 1);
		pCncData3 = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i + 2);
		pCncData4 = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i + 3);
		if ((pCncData1->m_cCmdType == TYPE_CUT)
			&& (pCncData2->m_cCmdType == TYPE_CUT)
			&& (pCncData3->m_cCmdType == TYPE_CUT)
			&& (pCncData4->m_cCmdType == TYPE_CUT)
			)
		{
			if (   (pCncData2->m_nLongAxialStep < 50)
				&& (pCncData3->m_nLongAxialStep < 50)
				&& (pCncData4->m_nLongAxialStep < 50)
				)
			{
				pCncData4->m_iDeltaX = pCncData4->m_iX - pCncData2->m_iX;
				pCncData4->m_iDeltaY = pCncData4->m_iY - pCncData2->m_iY;

				pCncData4->m_nLongAxialStep =
				(abs(pCncData4->m_iDeltaX) > abs(pCncData4->m_iDeltaY)) ?
					abs(pCncData4->m_iDeltaX) : abs(pCncData4->m_iDeltaY);
				g_ptrCncList.RemoveAt(i+2);

				nSize--;
			}

		}

	}
}

void CalculateAngles()
{
	int i;
	ST_CNC_DATA_ALL *pCncData;
	int iLastX,iLastY;
	double dLastAngle;
	int nSize;
	nSize = g_ptrCncList.GetSize();
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

void AddOverCutData()
{
	int i;
	int nDataSize = g_ptrCncList.GetSize();

	ST_CNC_DATA_ALL* pCutData;
	ST_CNC_DATA_ALL* pCutData1;
	ST_CNC_DATA_ALL* pCutDataAdd;
	
	int iDeltaX,iDeltaY,iDeltaX1,iDeltaY1;
	if (0 == gSet.getOverCutLen())
	{
		return;
	}

	for (i=1;i<nDataSize;i++)
	{
		pCutData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		pCutData1 = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i-1);
		
		if( (TYPE_MOVE == pCutData1->m_cCmdType) && (TYPE_CUT == pCutData->m_cCmdType) ) 
			//是一段闭合曲线的起始 在此段数据之前后退 gSet.getOverCutLen()
		{
			//改变抬笔目标 (沿着反向移动)
			iDeltaX = (int)( gSet.getOverCutLen() * cos(pCutData->m_dAngle) );
			iDeltaY = (int)( gSet.getOverCutLen() * sin(pCutData->m_dAngle) );
			pCutData1->m_iX = pCutData1->m_iX-iDeltaX;
			pCutData1->m_iY = pCutData1->m_iY-iDeltaY;
		}
		else if ((TYPE_CUT == pCutData1->m_cCmdType) && (TYPE_MOVE == pCutData->m_cCmdType)) 
			//是一段闭合曲线的结束 在此段数据之后前进 gSet.getOverCutLen()
		{
			iDeltaX = (int)(gSet.getOverCutLen() * cos(pCutData1->m_dAngle) );
			iDeltaY = (int)(gSet.getOverCutLen() * sin(pCutData1->m_dAngle) );
			pCutData1->m_iX = pCutData1->m_iX+iDeltaX;
			pCutData1->m_iY = pCutData1->m_iY+iDeltaY;
		}
		else if((TYPE_CUT == pCutData1->m_cCmdType) && (TYPE_CUT == pCutData->m_cCmdType))
		{ //当前点的角度变化量
			if( ( fabs(pCutData->m_dDeltaAngle*180/PI) > OVERCUT_ANGLE )	//是锐角
				&& ( fabs(pCutData->m_dDeltaAngle*180/PI) < 120.0 )	) 

			{
				iDeltaX = (int)( gSet.getOverCutLen() * cos(pCutData1->m_dAngle) );
				iDeltaY = (int)( gSet.getOverCutLen() * sin(pCutData1->m_dAngle) );
				pCutData1->m_iX = pCutData1->m_iX+iDeltaX;
				pCutData1->m_iY = pCutData1->m_iY+iDeltaY;
				
				pCutDataAdd = new ST_CNC_DATA_ALL;
				iDeltaX1 = (int)( gSet.getOverCutLen() * cos(pCutData->m_dAngle) );
				iDeltaY1 = (int)( gSet.getOverCutLen() * sin(pCutData->m_dAngle) );	
				pCutDataAdd->m_cCmdType = TYPE_CUT;
				pCutDataAdd->m_iX = pCutData1->m_iX-iDeltaX-iDeltaX1;
				pCutDataAdd->m_iY = pCutData1->m_iY-iDeltaY-iDeltaY1;

				g_ptrCncList.InsertAt(i,pCutDataAdd);
				nDataSize++;
				i++;
			}
		}
	}
	
	pCutData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(nDataSize - 1);
	if (pCutData->m_cCmdType == TYPE_CUT) //最后一个数据是落笔
	{
		iDeltaX = (int)(gSet.getOverCutLen() * cos(pCutData->m_dAngle) );
		iDeltaY = (int)(gSet.getOverCutLen() * sin(pCutData->m_dAngle) );
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
	strFileName.Format("d:\\Spcutter7.csv");
	fileData.Open(strFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary);
	nSize = g_ptrCncList.GetSize();
	strTemp.Format("目标X,目标Y,DeltaX,DeltaY,加速次数,角度,角度变化,是否弧线,MaxSpd,EndSpd,类型\n");
	fileData.Write(strTemp.GetBuffer(0), strTemp.GetLength());

	double d;
	for (i = 0; i < nSize; i++)
	{
		pCncData = (ST_CNC_DATA_ALL*)g_ptrCncList.GetAt(i);
		d = fabs(pCncData->m_dDeltaAngle)*100.0 / pCncData->m_nLongAxialStep;

		strTemp.Format("%d,%d, %d,%d, %d, %f,%f, %d,%d,%d,%c,%f\n",
			pCncData->m_iX, pCncData->m_iY,
			pCncData->m_iDeltaX, pCncData->m_iDeltaY,
			pCncData->m_nSecNum,
			pCncData->m_dAngle*180.0 / PI, pCncData->m_dDeltaAngle*180.0 / PI,
			pCncData->m_cIsCurve,
			pCncData->m_nMaxSpeed,
			pCncData->m_nMaxEndSpeed,
			pCncData->m_cCmdType,
			d);
		fileData.Write(strTemp.GetBuffer(0), strTemp.GetLength());
	}
	fileData.Close();
	AfxMessageBox("file saved");
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

