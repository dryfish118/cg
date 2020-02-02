
// ddaDoc.h: CddaDoc 类的接口
//


#pragma once

#include "ddaView.h"

class CddaDoc
	: public CDocument
	, public CGetPointCallback
{
protected: // 仅从序列化创建
	CddaDoc() noexcept;
	DECLARE_DYNCREATE(CddaDoc)

// 特性
public:
	Objects m_objects;

// 操作
public:
	virtual void onGetPoint(const CGePoint& pnt);
	
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CddaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	enum State
	{
		kNone,
		kGetFirstPoint,
		kGetSecondPoint,
	};
	State m_state;
	CGePoint m_point;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnLineDda();
};
