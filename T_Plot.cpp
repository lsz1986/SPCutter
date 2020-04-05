#include "Stdafx.h"
#include "Global.h"
#include "Thread.h"

int g_iPlotPixelX; //图形X向的像素值

int g_iBmpPixelY; //图形Y向的像素值
int g_iMacPixelY; //包含对喷头间距和左右两列间距填0后的图形像素值
int g_iSpdataSizeZipped;

// char g_SpDataOrg[MAX_PIXEL][40]; 
// char g_SpDataSend[MAX_PIXEL][44];
char g_SpDataOrg[MAX_PIXEL][80]; 
char g_IUT308_SpDataSend[MAX_PIXEL][88];
char g_HP45_SpDataSend[MAX_PIXEL][44];


// unsigned short g_TempSpDataSend[MAX_PIXEL*44];
// unsigned short g_ZippedSpDataSend[MAX_PIXEL*44];
unsigned short g_TempSpDataSend[MAX_PIXEL*88];
unsigned short g_ZippedSpDataSend[MAX_PIXEL*88];


u8 g_Hp45_000To150Pixel[150];
u8 g_Hp45_150To300Pixel[150];

u8 g_IUT308_001To308Pixel[308];
u8 g_IUT308_309To616Pixel[308];

u8 g_HP45_SpAOneLinePixel[22][8];
u8 g_HP45_SpBOneLinePixel[22][8];


u8 g_IUT308_SpAOneLinePixel[44][8];
u8 g_IUT308_SpBOneLinePixel[44][8];

u8 g_SpAOneLinePixelZipped[44];
u8 g_SpBOneLinePixelZipped[44];

void HP45_SetSpDataZero(void) //用0填充 g_SpDataOrg
{
	int i,j;
	for (i=0; i<MAX_PIXEL; i++)
	{
		for (j=0;j<80;j++)
		{
			g_SpDataOrg[i][j] = 0;
		}
		for (j=0;j<44;j++)
		{
			g_HP45_SpDataSend[i][j] = 0;
		}
	}
}

void IUT308_SetSpDataZero(void) //用0填充 g_SpDataOrg
{
	int i,j;
	for (i=0; i<MAX_PIXEL; i++)
	{
		for (j=0;j<80;j++)
		{
			g_SpDataOrg[i][j] = 0;
		}
		for (j=0;j<88;j++)
		{
			g_IUT308_SpDataSend[i][j] = 0;
		}
	}
}

void CalcPlotPackSum(void) //计算喷墨数据的包数
{
	if( (gWorkingPage.m_nPlotXMax == 0)&&(gWorkingPage.m_nPlotYMax == 0) )
	{
		gPackSumPlotOnly = 0;
		return;
	}
	int nDotsOfOneSp;
	if (gSet.getSpType() == 1)
	{
		nDotsOfOneSp = 308;
	}
	else
	{
		nDotsOfOneSp = 150;
	}

	g_iPlotPixelX = ftoi(gWorkingPage.m_nPlotXMax/40.0/MM_P_DOTX*gSet.getPltScale()*10.0/gSet.get10000X()+2*gSet.getLineWidth());
	g_iBmpPixelY = ftoi(gWorkingPage.m_nPlotYMax/40.0*gSet.getPPMMY()/gSet.getPPDOTY() *gSet.getPltScale()*10.0/gSet.get10000Y()+2*gSet.getLineWidth());
	g_iMacPixelY = g_iBmpPixelY+SPLR_DOT_MAX+gSet.getSp12EY();

	if (0 == gSet.getSpStat()) //是双喷
	{
		gPackSumPlotOnly = g_iPlotPixelX / (nDotsOfOneSp*2-gSet.getSpEX());
		if( 0 != (g_iPlotPixelX % (nDotsOfOneSp*2-gSet.getSpEX())) )
			gPackSumPlotOnly++;
	}
	else
	{
		gPackSumPlotOnly = g_iPlotPixelX / nDotsOfOneSp;
		if( 0 != (g_iPlotPixelX % nDotsOfOneSp ) )
			gPackSumPlotOnly++;
	}
	return;
}

void GetOnePackOrgData(int nPackNo) //获取一包喷墨数据，存入g_SpDataOrg中
{
	HDC hdc, hdcMem;
	HBITMAP hBitMap = NULL;
	CBitmap bitMap;
	CBitmap *pOldBitmap1;
	CDC *pMemDC = NULL;
	int nXPixelStart;
	int nDotsOfOneSp;
	if (gSet.getSpType() == 1)
	{
		nDotsOfOneSp = 308;
	}
	else
	{
		nDotsOfOneSp = 150;
	}

	hdc = CreateIC(TEXT("DISPLAY"), NULL, NULL, NULL);
    hdcMem = CreateCompatibleDC(hdc);
    pMemDC = new CDC;
    pMemDC->Attach(hdcMem);

	bitMap.CreateBitmap(640, g_iBmpPixelY, 1, 1, g_SpDataOrg); 
	if (0 == gSet.getSpStat()) //是双喷
	{
		nXPixelStart = nPackNo*(nDotsOfOneSp*2-gSet.getSpEX());
	}
	else
	{
		nXPixelStart = nPackNo*nDotsOfOneSp;
	}
	pOldBitmap1 = pMemDC->SelectObject(&bitMap); //添加自绘图形

	DrawBmp(pMemDC,nXPixelStart);
#if 0
	CString strBmpName;
	strBmpName.Format(_T("D:\\plot-%d.bmp"),nPackNo);
	SaveBmp((HBITMAP)(bitMap.GetSafeHandle()),strBmpName);
#endif
	bitMap.GetBitmapBits(MAX_PIXEL*80, g_SpDataOrg); //获取点阵

	pMemDC->SelectObject(pOldBitmap1);
	bitMap.DeleteObject();
	
	pMemDC->DeleteDC();
	delete pMemDC;
    pMemDC = NULL;
	return;
}

void HP45_Get001To150Pixel(int nYPixel) //从 g_SpDataOrg 获取一个点行的数据
{
	int i,j;
	for (i=0;i<150;i++)
	{
		g_Hp45_000To150Pixel[i] = 0;
	}
	for (i=0;i<19;i++)
	{
		for (j=0;j<8;j++)
		{
			if( (i*8+j) < 150 )
			{
				if( ( ((g_SpDataOrg[nYPixel][i])>>(7-j)) & 0x01 ) == 0x01)
				{
					g_Hp45_000To150Pixel[i*8+j] = 1;
				}
			}
		}
	}
}

void HP45_Get150To300Pixel(int nYPixel) //从 g_SpDataOrg 获取一个点行的数据
{
	int i,j;
	int nStartBit,nEndBit;
	nStartBit = 150-gSet.getSpEX();
	nEndBit = 300-gSet.getSpEX();
	for (i=0;i<150;i++)
	{
		g_Hp45_150To300Pixel[i] = 0;
	}
	for (i=18;i<38;i++)
	{
		for (j=0;j<8;j++)
		{
			if( ( (i*8+j) >= 150 ) && ( (i*8+j) < nEndBit ) )
			{
				if( ( ((g_SpDataOrg[nYPixel][i])>>(7-j)) & 0x01 ) == 0x01)
				{
					g_Hp45_150To300Pixel[i*8+j-nStartBit] = 1;
				}
			}
		}
	}
}

void IUT308_Get001To308Pixel(int nYPixel) //从 g_SpDataOrg 获取一个点行的数据
{
	int i,j;
	for (i=0;i<308;i++)
	{
		g_IUT308_001To308Pixel[i] = 0;
	}
//	for (i=0;i<44;i++)
	for (i=0;i<39;i++) //20161223  38->39
	{
		for (j=0;j<8;j++)
		{
			if( (i*8+j) < 308 )
			{
				if( ( ((g_SpDataOrg[nYPixel][i])>>(7-j)) & 0x01 ) == 0x01)
				{
					g_IUT308_001To308Pixel[i*8+j] = 1;
				}
			}
		}
	}
}

void IUT308_Get309To616Pixel(int nYPixel) //从 g_SpDataOrg 获取一个点行的数据
{
	int i,j;
	int nStartBit,nEndBit;
	nStartBit = 308-gSet.getSpEX();
	nEndBit = 616-gSet.getSpEX();
	for (i=0;i<308;i++)
	{
		g_IUT308_309To616Pixel[i] = 0;
	}
	for (i=38;i<77;i++) //20161223 76->77
	{
		for (j=0;j<8;j++)
		{
			if( ( (i*8+j) >= 308 ) && ( (i*8+j) < nEndBit ) )
			{
				if( ( ((g_SpDataOrg[nYPixel][i])>>(7-j)) & 0x01 ) == 0x01)
				{
					g_IUT308_309To616Pixel[i*8+j-nStartBit] = 1;
				}
			}
		}
	}
}

void HP45_ConvertOrgDataToSendData(int packNo)
{
	int i,j;
	int SP12SPACE;

	SP12SPACE = gSet.getSp12EY();

	switch (gSet.getSpStat())
	{
		case 0:
		for (i=0;i<g_iMacPixelY;i++)
		{
			HP45_Get001To150Pixel(i); //
			HP45_Get150To300Pixel(i); //
			HP45_getSpAOneLineData(1); //数据保存在数组 g_SpAOneLinePixel[][]中
			HP45_getSpBOneLineData(2); //数据保存在数组 g_SpBOneLinePixel[][]中
			HP45_ZipSpData();
			for (j=0;j<22;j++)
			{
				g_HP45_SpDataSend[i+SPLR_DOT_MAX][j] = g_SpAOneLinePixelZipped[j];
			}
			for (j=0;j<22;j++)
			{
				g_HP45_SpDataSend[i+SPLR_DOT_MAX+SP12SPACE][j+22] = g_SpBOneLinePixelZipped[j];
			}
		}
		break;
		
		case 1:
		for (i=0;i<g_iMacPixelY;i++)
		{
			HP45_Get001To150Pixel(i);
			HP45_getSpAOneLineData(1);
			HP45_getSpBOneLineData(0);
			HP45_ZipSpData();
			for (j=0;j<22;j++)
			{
				g_HP45_SpDataSend[i+SPLR_DOT_MAX][j] = g_SpAOneLinePixelZipped[j];
			}
			for (j=0;j<22;j++)
			{
				g_HP45_SpDataSend[i+SPLR_DOT_MAX+SP12SPACE][j+22] = g_SpBOneLinePixelZipped[j];
			}
		}
		break;

		case 2:
		for (i=0;i<g_iMacPixelY;i++)
		{
			HP45_Get001To150Pixel(i);
			HP45_getSpAOneLineData(0);
			HP45_getSpBOneLineData(1);
			HP45_ZipSpData();
			for (j=0;j<22;j++)
			{
				g_HP45_SpDataSend[i+SPLR_DOT_MAX][j] = g_SpAOneLinePixelZipped[j];
			}
			for (j=0;j<22;j++)
			{
				g_HP45_SpDataSend[i+SPLR_DOT_MAX+SP12SPACE][j+22] = g_SpBOneLinePixelZipped[j];
			}
		}
		break;
	}
}

void IUT308_ConvertOrgDataToSendData(int packNo)
{
	int i,j;
	int SP12SPACE;
	
	SP12SPACE = gSet.getSp12EY();
	
	switch (gSet.getSpStat())
	{
		case 0:
		for (i=0;i<g_iMacPixelY;i++)
		{
			IUT308_Get001To308Pixel(i); //
			IUT308_Get309To616Pixel(i); //
			IUT308_getSpAOneLineData(1); //数据保存在数组 g_SpAOneLinePixel[][]中
			IUT308_getSpBOneLineData(2); //数据保存在数组 g_SpBOneLinePixel[][]中
			IUT308_ZipSpData();
			for (j=0;j<44;j++)
			{
				g_IUT308_SpDataSend[i+SPLR_DOT_MAX][j] = g_SpAOneLinePixelZipped[j];
			}
			for (j=0;j<44;j++)
			{
				g_IUT308_SpDataSend[i+SPLR_DOT_MAX+SP12SPACE][j+44] = g_SpBOneLinePixelZipped[j];
			}
		}
		break;
		
		case 1:
		for (i=0;i<g_iMacPixelY;i++)
		{
			IUT308_Get001To308Pixel(i);
			IUT308_getSpAOneLineData(1);
			IUT308_getSpBOneLineData(0);
			IUT308_ZipSpData();
			for (j=0;j<44;j++)
			{
				g_IUT308_SpDataSend[i+SPLR_DOT_MAX][j] = g_SpAOneLinePixelZipped[j];
			}
			for (j=0;j<44;j++)
			{
				g_IUT308_SpDataSend[i+SPLR_DOT_MAX+SP12SPACE][j+44] = g_SpBOneLinePixelZipped[j];
			}
		}
		break;
		
		case 2:
		for (i=0;i<g_iMacPixelY;i++)
		{
			IUT308_Get001To308Pixel(i);
			IUT308_getSpAOneLineData(0);
			IUT308_getSpBOneLineData(1);
			IUT308_ZipSpData();
			for (j=0;j<44;j++)
			{
				g_IUT308_SpDataSend[i+SPLR_DOT_MAX][j] = g_SpAOneLinePixelZipped[j];
			}
			for (j=0;j<44;j++)
			{
				g_IUT308_SpDataSend[i+SPLR_DOT_MAX+SP12SPACE][j+44] = g_SpBOneLinePixelZipped[j];
			}
		}
		break;
	}
}

BOOL SaveBmp(HBITMAP hBitmap, CString FileName) //FileName包括路径和文件的全名
{
	HDC hDC; 	//设备描述表
	int iBits; 	//当前分辨率下每象素所占字节数
	WORD wBitCount; 	//位图中每象素所占字节数
	
	DWORD dwPaletteSize=0, dwBmBitsSize=0, dwDIBSize=0, dwWritten=0;	//定义调色板大小， 位图中像素字节大小 ，位图文件大小 ， 写入文件字节数
	BITMAP Bitmap;	//位图属性结构
	BITMAPFILEHEADER bmfHdr;	//位图文件头结构
	BITMAPINFOHEADER bi;	//位图信息头结构
	LPBITMAPINFOHEADER lpbi;	//指向位图信息头结构
	HANDLE fh, hDib, hPal,hOldPal=NULL;	//定义文件，分配内存句柄，调色板句柄
	hDC = CreateDC("DISPLAY", NULL, NULL, NULL); 	//计算位图文件每个像素所占字节数 
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES); 
	DeleteDC(hDC);

	wBitCount = 1;
	
	GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap); 
	bi.biSize = sizeof(BITMAPINFOHEADER); 
	bi.biWidth = Bitmap.bmWidth; 
	bi.biHeight = Bitmap.bmHeight; 
	bi.biPlanes = 1; 
	bi.biBitCount = wBitCount; 
	bi.biCompression = BI_RGB; 
	bi.biSizeImage = 0; 
	bi.biXPelsPerMeter = 0; 
	bi.biYPelsPerMeter = 0; 
	bi.biClrImportant = 0; 
	bi.biClrUsed = 0; 
	
	dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight; 
	
	//为位图内容分配内存 
	hDib = GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER)); 
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib); 
	*lpbi = bi; 
	
	// 处理调色板   
	hPal = GetStockObject(DEFAULT_PALETTE); 
	if (hPal) 
	{ 
		hDC = ::GetDC(NULL); 
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE); 
		RealizePalette(hDC); 
	} 
	
	// 获取该调色板下新的像素值 
	GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) 
		+dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS); 
	
	//恢复调色板   
	if (hOldPal) 
	{ 
		::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE); 
		RealizePalette(hDC); 
		::ReleaseDC(NULL, hDC); 
	} 
	
	//创建位图文件   
	fh = CreateFile(FileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL); 
	
	if (fh == INVALID_HANDLE_VALUE)   return FALSE; 
	// 设置位图文件头 
	bmfHdr.bfType = 0x4D42; // "BM" 
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;   
	bmfHdr.bfSize = dwDIBSize; 
	bmfHdr.bfReserved1 = 0; 
	bmfHdr.bfReserved2 = 0; 
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize; 
	// 写入位图文件头 
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	// 写入位图文件其余内容
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
	//清除   
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return TRUE;
}

void DrawBmp(CDC *pDC,int StartPixelX)
{
	int i,j;
	int nCurveSize,nPlSize;
	CPoint pt;
	int iTempX,iTempY;

	int nPenNum = 1; //当前的笔号
	int nLineType = LT_SOLID;

	CPen pen;
	CPen *pOldPen;
	CCurve* pCurve;
	nCurveSize = gWorkingPage.m_CurveList.GetSize();

	pDC->SetBkColor(RGB(0, 0, 0));
	pen.CreatePen(LT_SOLID,gSet.getLineWidth(),RGB(255,255,255));

	pOldPen = pDC->SelectObject(&pen);

	for (i=0; i<nCurveSize; i++)
	{
		pCurve = (CCurve*) gWorkingPage.m_CurveList.GetAt(i);
		nPlSize = pCurve->m_pointList->GetSize();
		if (pCurve->m_nPenNum <= 1)
		{
			pt= pCurve->m_pointList->GetAt(0);
			iTempX = ftoi( pt.x/40.0/MM_P_DOTX*gSet.getPltScale()*10.0/gSet.get10000X() )-StartPixelX;
			iTempY = ftoi( pt.y/40.0*gSet.getPPMMY()/gSet.getPPDOTY()*gSet.getPltScale()*10.0/gSet.get10000Y()); //改为在下位机将图形翻转
			pDC->MoveTo(iTempX+gSet.getLineWidth()-1,iTempY+gSet.getLineWidth()-1);
			for (j=1;j<pCurve->m_pointList->GetSize();j++)
			{
				pt= pCurve->m_pointList->GetAt(j);
				iTempX = ftoi( pt.x/40.0/MM_P_DOTX*gSet.getPltScale()*10.0/gSet.get10000X() )-StartPixelX;
				iTempY = ftoi( pt.y/40.0*gSet.getPPMMY()/gSet.getPPDOTY()*gSet.getPltScale()*10.0/gSet.get10000Y() );
				pDC->LineTo(iTempX+gSet.getLineWidth()-1,iTempY+gSet.getLineWidth()-1);
			}
		}
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}

void HP45_ZipSpSendData() //将要发送的数据压缩存入 g_ZippedSpDataSend 中
{
	int i,j;
	int nSizeOrg,nZeroNum;
	g_iSpdataSizeZipped = 0;
	nSizeOrg = (g_iMacPixelY+SPLR_DOT_MAX)*22; //unsigned short数据大小
	
	memcpy( (char*)(&g_TempSpDataSend[0]),(char*)&(g_HP45_SpDataSend[0][0]), (g_iMacPixelY+SPLR_DOT_MAX)*44);
	memset( (char*)(&g_ZippedSpDataSend[0]),0,MAX_PIXEL*88);
	
	i=0;
	j=0;
	nZeroNum=0;
	
	for (i=0;i<nSizeOrg;i++)
	{
		if (g_TempSpDataSend[i] == 0)
		{
			nZeroNum++;
			if (nZeroNum >= 65000) //防止超过65536
			{
				g_ZippedSpDataSend[j]=0;
				j++;
				g_ZippedSpDataSend[j]=nZeroNum;
				j++;
				nZeroNum=0;
			}
		}
		else
		{
			if (nZeroNum != 0)
			{
				g_ZippedSpDataSend[j]=0;
				j++;
				g_ZippedSpDataSend[j]=nZeroNum;
				j++;
				nZeroNum=0;
			}
			g_ZippedSpDataSend[j]=g_TempSpDataSend[i];
			j++;
		}
	}
	
	if (nZeroNum != 0)
	{
		g_ZippedSpDataSend[j]=0;
		j++;
		g_ZippedSpDataSend[j]=nZeroNum;
		j++;
		nZeroNum=0;
	}
	
	g_iSpdataSizeZipped = j*2;
}

void IUT308_ZipSpSendData() //将要发送的数据压缩存入 g_ZippedSpDataSend 中
{
	int i,j;
	int nSizeOrg,nZeroNum;
	g_iSpdataSizeZipped = 0;
	nSizeOrg = (g_iMacPixelY + SPLR_DOT_MAX) * 44; //20161222

	memcpy( (char*)(&g_TempSpDataSend[0]),(char*)&(g_IUT308_SpDataSend[0][0]), (g_iMacPixelY+SPLR_DOT_MAX)*88);
	memset( (char*)(&g_ZippedSpDataSend[0]),0,MAX_PIXEL*88);
	
	i=0;
	j=0;
	nZeroNum=0;
	
	for (i=0;i<nSizeOrg;i++)
	{
		if (g_TempSpDataSend[i] == 0)
		{
			nZeroNum++;
			if (nZeroNum >= 65000) //防止超过65536
			{
				g_ZippedSpDataSend[j]=0;
				j++;
				g_ZippedSpDataSend[j]=nZeroNum;
				j++;
				nZeroNum=0;
			}
		}
		else
		{
			if (nZeroNum != 0)
			{
				g_ZippedSpDataSend[j]=0;
				j++;
				g_ZippedSpDataSend[j]=nZeroNum;
				j++;
				nZeroNum=0;
			}
			g_ZippedSpDataSend[j]=g_TempSpDataSend[i];
			j++;
		}
	}
	
	if (nZeroNum != 0)
	{
		g_ZippedSpDataSend[j]=0;
		j++;
		g_ZippedSpDataSend[j]=nZeroNum;
		j++;
		nZeroNum=0;
	}
	
	g_iSpdataSizeZipped = j*2;
}

