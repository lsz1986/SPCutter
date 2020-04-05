// CSettings.h: interface for the CSettings class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTINGS_H__7C86702C_BD84_45CD_BE7C_10999ABBB7A2__INCLUDED_)
#define AFX_SETTINGS_H__7C86702C_BD84_45CD_BE7C_10999ABBB7A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TBS_SEL  0
#define TBS_MOVE 1

#define THREAD_MESSAGE_NONE    0
#define THREAD_MESSAGE_RESUME  1
#define THREAD_MESSAGE_PAUSE   2
#define THREAD_MESSAGE_CANCEL  3

class CSettings  
{
public:
	CSettings();
	virtual ~CSettings();

public: 
//double--16Byte--------------------------------------
	inline void setPPMMX(double d){m_dPPMMX = d;};
	inline double getPPMMX(){return m_dPPMMX;};

	inline void setPPMMY(double d){m_dPPMMY = d;};
	inline double getPPMMY(){return m_dPPMMY;};

//short--10Byte--------------------------------------
	inline void set10000X(int n){ m_n1000X = n;}; //比例调整
	inline int get10000X(){ return m_n1000X;};

	inline void set10000Y(int n){ m_n1000Y = n;};
	inline int get10000Y(){ return m_n1000Y;};
	
	inline void setMacSizeX(int n){m_nMacSizeX = n;};
	inline int getMacSizeX(){return m_nMacSizeX;};

	inline void setMacSizeY(int n){m_nMacSizeY = n;};
	inline int getMacSizeY(){return m_nMacSizeY;};

	inline void setJobEndPosXmm(int n) {m_nJobEndHeadPosXmm = n;};
	inline int getJobEndPosXmm() {return m_nJobEndHeadPosXmm;};

//short--6Byte--------------------------------------
	inline void setJobEndPosYmm(int n) {m_nJobEndHeadPosYmm = n;};
	inline int getJobEndPosYmm() {return m_nJobEndHeadPosYmm;};

	inline void setCutPaperStartYmm(int n){m_nCutPaperStartYmm = n;}; //切割完成后自动裁断起点
	inline int getCutPaperStartYmm() {return m_nCutPaperStartYmm;};

	inline void setCutPaperEndYmm(int n) { m_nCutPaperEndYmm = n; }; //切割完成后自动裁断终点
	inline int getCutPaperEndYmm() { return m_nCutPaperEndYmm; };

	inline void setSpAccDistmm(int n){m_nSpAccDistmm = n;}; //
	inline int getSpAccDistmm() {return m_nSpAccDistmm;};
//u8--5Byte--------------------------------------
	inline void setKPDistX(int n){ m_nKPDistX = n;}; //刀笔补偿(脉冲数)
	inline int getKPDistX(){ return m_nKPDistX;}; //刀笔补偿

	inline void setKPDistY(int n){ m_nKPDistY = n;};
	inline int getKPDistY(){ return m_nKPDistY;};
	
	inline void setPwmKStart(int n) {m_nPwmKStart = n;};
	inline int getPwmKStart() {return m_nPwmKStart;};

	inline void setPwmKWork(int n) {m_nPwmKWork = n;};
	inline int getPwmKWork() {return m_nPwmKWork;};

	inline void setSp12EY(int n){ m_nSp12EY = n;}; //正向行走喷头间距
	inline int getSp12EY(){ return m_nSp12EY;}; //正向行走时的喷头间距
//u8--5Byte--------------------------------------
	inline void setBiDir(BOOL b){m_bBiDir = b;};
	inline BOOL getBiDir(){return m_bBiDir;};

	inline void setJamDetect(BOOL b){m_bJamDetectOn = b;};
	inline BOOL getJamDetect(){return m_bJamDetectOn;};

	inline void setSP1DOTLR(int n){ m_nSp1DotLr = n;}; //比例调整
	inline int getSP1DOTLR(){ return m_nSp1DotLr;}; 

	inline void setSP2DOTLR(int n){ m_nSp2DotLr = n;};
	inline int getSP2DOTLR(){ return m_nSp2DotLr;};

	inline void setSpdMove(int n){m_nSpdMove = n;};
	inline int getSpdMove() {return m_nSpdMove;};
	
	inline void setSpdCut(int n) {m_nSpdCut = n;};
	inline int getSpdCut() {return m_nSpdCut;};
//u8--5byte----------------------------------------------
	inline void setSpDDY(int n){ m_nSpDDY = n;}; //双向误差
	inline int getSpDDY(){ return m_nSpDDY;}; //双向误差

	inline void setSpStat(unsigned char c){m_cSpStat = c;};
	inline unsigned char getSpStat(){return m_cSpStat;};
	
	inline void setSpEX(int n){ m_nSpEX = n;}; //喷头重叠
	inline int getSpEX(){ return m_nSpEX;}; //喷头重叠

	inline void setAngleAdjust(int n){m_nAngleAdjust = n;};
	inline int getAngleAdjust(){return m_nAngleAdjust;};

	inline void setJobEndHeadPos(int n) {m_nJobEndHeadPos = n;};
	inline int getJobEndHeadPos() {return m_nJobEndHeadPos;};

	inline void setSpType(int n) {m_nSpType = (n>=0 && n<=1)?n:0;}; //墨盒类型
	inline int getSpType() {return (m_nSpType>=0 && m_nSpType<=1)?m_nSpType:0;};

	inline void setConnetViaEth(BOOL b) { m_bConnectViaEth = b; };
	inline BOOL getConnetViaEth() { return m_bConnectViaEth; };
//u8--2byte----------------------------------------------
	inline void setPPDOTY(int n){ m_nPPDOT_Y = n;};
	inline int getPPDOTY(){ return m_nPPDOT_Y;}; //喷墨间隔脉冲

	inline void setLedLan(int n){ m_nLedLan = n;};
	inline int getLedLan(){ return m_nLedLan;}; //液晶面板语言

public: //保存在配置文件中的机器参数
	inline void setLineWidth(int n){ m_nLineWidth = n;};
	inline int getLineWidth(){ return m_nLineWidth;};
	inline void setOverCutLen(int n) {m_nOverCutLen = n;};
	inline int getOverCutLen() {return m_nOverCutLen;};

	inline void setPltPageLen(int n) {m_nPltPageLen = n;};
	inline int getPltPageLen() {return m_nPltPageLen;};
public: //显示参数
	inline void setDisplayStartAndDir(BOOL b) {m_bStartAndDirOn = b;};
	inline BOOL getDisplayStartAndDir() {return m_bStartAndDirOn;};
	
	inline void setDisplaySequence(BOOL b) {m_bDisplaySequence = b;};
	inline BOOL getDisplaySequence() {return m_bDisplaySequence;};

public://---其他参数-------------------------
	inline void setToolBarState(int n){m_nToolBarState = n;};
	inline int getToolBarState(){return m_nToolBarState;};

	inline void setYBlankMm(int n){m_nYBlankMm = n;};
	inline int getYBlankMm(){return m_nYBlankMm;};

	inline void setAutoMoveToLeft(BOOL b){m_bAutoMoveToLeft = b;};
	inline BOOL getAutoMoveToLeft(){return m_bAutoMoveToLeft;};

	inline void setAutoMoveToBottom(BOOL b){m_bAutoMoveToBottom = b;};
	inline BOOL getAutoMoveToBottom(){return m_bAutoMoveToBottom;};

	inline void setAutoDelPlt(BOOL b){m_bAutoDelPlt = b;};
	inline BOOL getAutoDelPlt(){return m_bAutoDelPlt;};

	inline void setSpAutoClean(BOOL b){m_bSpAutoClean = b;};
	inline BOOL getSpAutoClean(){return m_bSpAutoClean;};

	inline void setJobAutoStart(BOOL b){m_bJobAutoStart = b;};
	inline BOOL getJobAutoStart(){return m_bJobAutoStart;};

	inline void setOnlyPlot(BOOL b){m_bOnlyPlot = b;};
	inline BOOL getOnlyPlot(){return m_bOnlyPlot;};
	
	inline void setFirstPageConfirm(BOOL b){m_bFirstPageConfirm = b;};
	inline BOOL getFirstPageConfirm(){return m_bFirstPageConfirm;};

	inline void setMachineLocked(BOOL b){m_bMachineLocked = b;};
	inline BOOL getMachineLocked(){return m_bMachineLocked;};

	inline void setWorkStartPause(BOOL b){m_bWorkStartPause = b;};
	inline BOOL getWorkStartPause(){return m_bWorkStartPause;};

	BOOL getAppExitFlag() { return m_bAppExitFlag; }
	void setAppExitFlag(BOOL b) { m_bAppExitFlag = b; };

	inline void setThreadMessage(int n){m_nUserThreadMessage = n;};
	inline BOOL getThreadMessage(){return m_nUserThreadMessage;};
	
public:
	inline void setDataDir(CString str){m_strDataDir = str;}
	inline void setKeyFile(CString str){m_strKeyFile = str;}

	inline void setMcuCode(int n){m_nMcuCode = n;};
	inline int getMcuCode(){return m_nMcuCode;};
	
	inline void setPltScale(int n){ m_nPltScale = n; };
	inline int getPltScale() { return m_nPltScale; };

	BOOL getQueryEnable(){return m_bQueryEnable;};
	void setQueryEnable(bool b){m_bQueryEnable = b;Sleep(10);};

	inline void setCurveSpd(int n) {
		if ((n >= 5) && (n <= 50)) 
			m_nCurveSpd = n;
		else
			m_nCurveSpd = 8;
	};
	inline int getCurveSpd() { return m_nCurveSpd; };

	inline void setPltSaveScaleX(int n){ m_nPltSaveScaleX = n; };
	inline int getPltSaveScaleX() { return m_nPltSaveScaleX; };

	inline void setPltSaveScaleY(int n){ m_nPltSaveScaleY = n; };
	inline int getPltSaveScaleY() { return m_nPltSaveScaleY; };

	inline void setFindOutLine(BOOL b) {m_bFindOutLine = b;};
	inline BOOL getFindOutLine() {return m_bFindOutLine;};

	inline void setSecLen(int n) { m_nCutSecLen = n; };
	inline int getSecLen() { return m_nCutSecLen; };

	inline void setParaUpdateFlag(BOOL b) { m_bParaUpdateFlag = b; }; //打印线程中更新参数
	inline BOOL getParaUpdateFlag() { return m_bParaUpdateFlag; };

	inline void setMachineIpAddr(unsigned int n) { m_nMachineIpAddr = n; };
	inline unsigned int getMachineIpAddr() { return m_nMachineIpAddr; };
public:
	inline CString getMcuSn(){return m_strMcuSn;};
	inline void setMcuSn(CString str){m_strMcuSn = str;};

	inline CString getAuthCode(){return m_strAuthCode;};
	inline void setAuthCode(CString str){m_strAuthCode = str;};

	void getAppDir();
	void checkDataDir();

public:
	CString m_strDataDir;
	CString m_strAppDir;
	CString m_strKeyFile;
	CString m_strFonHz;
	CString m_strFonEn;

private:
	BOOL m_bConnectViaEth;

	BOOL m_bJobAutoStart;
	BOOL m_bOnlyPlot;
	BOOL m_bFirstPageConfirm;
	BOOL m_bAutoDelPlt;
	BOOL m_bSpAutoClean;
	BOOL m_bParaUpdateFlag;

	BOOL m_bStartAndDirOn;
	BOOL m_bAutoMoveToLeft;
	BOOL m_bAutoMoveToBottom;
	BOOL m_bDisplaySequence; //显示铣刀(切刀)加工顺序
	BOOL m_bBiDir;
	BOOL m_bJamDetectOn;
	BOOL m_bLowSpdMode;

	BOOL m_bFindOutLine;
	BOOL m_bAppExitFlag;

	int m_nMachineIpAddr;
	int m_nSpType;
	int m_nLineWidth;
	int m_nMaxCutSpd;
	int m_nMachineType;
	int m_nPltPageLen;
	int m_nCurveSpd;

	int m_nJobEndHeadPos;
	int m_nJobEndHeadPosXmm;
	int m_nJobEndHeadPosYmm;

	int m_nKPDistX; //刀笔补偿
	int m_nKPDistY;
	int m_n1000X; //比例调整 100mm 实际输出多少
	int m_n1000Y;

	int m_nSp1DotLr;
	int m_nSp2DotLr;

	int m_nSpEX; //喷头重叠
	int m_nSp12EY; //正向行走时喷头间距
	int m_nSpDDY; //双向误差

	unsigned char m_cSpStat; //喷头状态 0-喷头全选，1-仅选择喷头1 2-仅选择喷头2
	BOOL m_bWorkStartPause;

	int m_nSpdMove;
	int m_nCutPaperStartYmm;
	int m_nCutPaperEndYmm;

	int m_nAngleAdjust;
	int m_nOverCutLen;

	int m_nPwmKStart; //启动刀压
	int m_nPwmKWork; //工作刀压

	double m_dPPMMX;
	double m_dPPMMY;
	int m_nZpPosX;
	int m_nZpPosY;
	int m_nMacSizeX;
	int m_nMacSizeY;

	int m_nSpAccDistmm;
	int m_nSpdCut;
	int m_nPPDOT_Y;
	int m_nLedLan;

	int m_nYBlankMm;
	int m_nPltScale;
	int m_nPltSaveScaleX;
	int m_nPltSaveScaleY;

	int m_nCutSecLen;

	int m_nToolBarState;
	bool m_bQueryEnable;
	BOOL m_bMachineLocked;
	int m_nUserThreadMessage;
	int m_nMcuCode;
	CString m_strMcuSn;
	CString m_strAuthCode;
};
#endif // !defined(AFX_SETTINGS_H__7C86702C_BD84_45CD_BE7C_10999ABBB7A2__INCLUDED_)
