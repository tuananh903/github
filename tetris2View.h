
// tetris2View.h : interface of the Ctetris2View class
//

#pragma once
#include "Banco.h"


class Ctetris2View : public CView
{
protected: // create from serialization only
	Ctetris2View() noexcept;
	DECLARE_DYNCREATE(Ctetris2View)

// Attributes
public:
	Ctetris2Doc* GetDocument() const;

// Operations
public:
	Banco banco;

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
	virtual ~Ctetris2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	int batdaugame();
};

#ifndef _DEBUG  // debug version in tetris2View.cpp
inline Ctetris2Doc* Ctetris2View::GetDocument() const
   { return reinterpret_cast<Ctetris2Doc*>(m_pDocument); }
#endif

