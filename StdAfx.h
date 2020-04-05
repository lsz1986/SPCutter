// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__DEB52B8D_7F50_4FA1_AE67_3F3702ED9A58__INCLUDED_)
#define AFX_STDAFX_H__DEB52B8D_7F50_4FA1_AE67_3F3702ED9A58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions
#include <afxtempl.h> //CArray用到

#pragma comment(lib,"libusb\\libusb.lib")

#include <math.h>
#define PI 3.14159265359

#define TYPE_END		'E'
#define TYPE_MOVE		'M'
#define TYPE_CUT		'C'

#define OVERCUT_ANGLE  45.0 //角度补偿用
//-------------20150411------------
//#define SD0_ANGLE  15.0		//降速到0
#define SD0_ANGLE  15.0		//降速到0 20161205
#define SD5_ANGLE  7.5		//降速到5
#define CURVE_ANGLE	 4.0	//判断是否为弧线
#define MAX_SPD 160
//#define CURVE_SPD 8
#define SD5_SPD 5

#define CNC_DATA_SIZE 12
#define SOFT_BIRTH_TIME 1405932800

#define SPLR_DOT_MAX 30 //喷头左右两列之间的点数
#define SP12_DOT_MAX 160

//#define SPRAY_LEN_X2 25.0
#define MM_P_DOTX  (25.4/300) //X方向1mm单位对应的像素点数

#include <afxcview.h>
#define  DISP_START_X  20
#define  DISP_START_Y  30

#define KP_XXX	(-2207) //IUT308
#define KP_YYY	(-3440)

#define C_GM (1)
#define C_ALL (0)
#define CUSTOMER_TYPE C_GM

#define YHZ_DEBUG 0
#pragma warning(disable:4996)
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__DEB52B8D_7F50_4FA1_AE67_3F3702ED9A58__INCLUDED_)
