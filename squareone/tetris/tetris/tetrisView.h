// tetrisView.h : interface of the CtetrisView class
//
#include "GameBoard.h"

#pragma once


class CtetrisView : public CView
{
protected: // create from serialization only
	CtetrisView();
	DECLARE_DYNCREATE(CtetrisView)

// Attributes
public:
	CtetrisDoc* GetDocument() const;
    KGameBoard *gameBoard;
    
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    
// Implementation
public:
	virtual ~CtetrisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    static unsigned int StartServer(LPVOID lParam);
};

#ifndef _DEBUG  // debug version in tetrisView.cpp
inline CtetrisDoc* CtetrisView::GetDocument() const
   { return reinterpret_cast<CtetrisDoc*>(m_pDocument); }
#endif

