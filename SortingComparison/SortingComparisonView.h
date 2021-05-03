
// SortingComparisonView.h : interface of the CSortingComparisonView class
//

#pragma once

#include <array>
#include <algorithm>


#define NO_SORTS 7
#define MARGIN 65

#define RED RGB(255,0,0)
#define ORANGE RGB(255,140,0)
#define YELLOW RGB(255,255,0)
#define GREEN RGB(0,255,0)
#define BLUE RGB(0,0,255)
#define PURPLE RGB(255,0,255)
#define BLACK RGB(0,0,0)




class CSortingComparisonView : public CView
{
protected: // create from serialization only
	CSortingComparisonView() noexcept;
	DECLARE_DYNCREATE(CSortingComparisonView)

	// Attributes
public:
	CSortingComparisonDoc* GetDocument() const;

	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
protected:

	// Implementation
public:
	virtual ~CSortingComparisonView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSortProperties();

private:
	void DrawBackground(CDC* pDC);
	void DrawDiagram(CDC* pDC);
	void ResetTimes();

private:
	int currentArraySize;
	int noLines;
	int namesPosition;
	double linesPosition;

	CRect* m_pClientRect;
	CPen* m_pPencil;
	CPen* m_pPenBlack;

	std::array<CPen*, NO_SORTS> m_pPens;
	std::array<CBrush*, NO_SORTS> m_bBrushes;

	std::array<double, NO_SORTS> m_dSortTimes;
	std::array<CString, NO_SORTS> m_sSortNames;
};

#ifndef _DEBUG  // debug version in SortingComparisonView.cpp
inline CSortingComparisonDoc* CSortingComparisonView::GetDocument() const
{
	return reinterpret_cast<CSortingComparisonDoc*>(m_pDocument);
}
#endif

