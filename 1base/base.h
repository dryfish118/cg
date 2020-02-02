
// base.h: base 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // 主符号


// CbaseApp:
// 有关此类的实现，请参阅 base.cpp
//

class CbaseApp : public CWinApp
{
public:
	CbaseApp() noexcept;


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CbaseApp theApp;
