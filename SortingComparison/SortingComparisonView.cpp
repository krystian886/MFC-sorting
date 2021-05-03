
// SortingComparisonView.cpp : implementation of the CSortingComparisonView class
//

#include "pch.h"
#include "framework.h"
#include "SortDlg.h"
#include "SortAlgs.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SortingComparison.h"
#endif

#include "SortingComparisonDoc.h"
#include "SortingComparisonView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSortingComparisonView

IMPLEMENT_DYNCREATE(CSortingComparisonView, CView)

BEGIN_MESSAGE_MAP(CSortingComparisonView, CView)
	ON_COMMAND(ID_SORT_PROPERTIES, &CSortingComparisonView::OnSortProperties)
END_MESSAGE_MAP()

// CSortingComparisonView construction/destruction

CSortingComparisonView::CSortingComparisonView() noexcept
{
	currentArraySize = 0;
	noLines = 0;
	namesPosition = 0;
	linesPosition = 0;

	m_pClientRect = new CRect(0, 0, 0, 0);
	m_pPencil = new CPen(PS_DASH, 1, RGB(200, 200, 200));
	m_pPenBlack = new CPen(PS_SOLID, 2, RGB(0, 0, 0));

	m_pPens = { new CPen(PS_SOLID, 1, RED), new CPen(PS_SOLID, 1, ORANGE),
				new CPen(PS_SOLID, 1, YELLOW), new CPen(PS_SOLID, 1, GREEN),
				new CPen(PS_SOLID, 1, BLUE), new CPen(PS_SOLID, 1, PURPLE),
				m_pPens[6] = new CPen(PS_SOLID, 1, BLACK) };

	m_bBrushes = { new CBrush(RED), new CBrush(ORANGE),
				   new CBrush(YELLOW), new CBrush(GREEN),
				   new CBrush(BLUE), new CBrush(PURPLE),
				   new CBrush(BLACK) };


	m_dSortTimes = { .0 };
	m_sSortNames = { L"Selection",L"Insertion",L"Half insertion",
					 L"Bubble",L"Mixed bubble",L"Heap",L"Quick" };

}

CSortingComparisonView::~CSortingComparisonView()
{
	delete m_pClientRect;
	delete m_pPencil;
	delete m_pPenBlack;
	for (int i = 0; i < NO_SORTS; ++i)
	{
		delete m_pPens[i];
		delete m_bBrushes[i];
	}
}

BOOL CSortingComparisonView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSortingComparisonView drawing

void CSortingComparisonView::OnDraw(CDC* pDC)
{
	CSortingComparisonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	DrawBackground(pDC);
	DrawDiagram(pDC);
}

// CSortingComparisonView diagnostics

#ifdef _DEBUG
void CSortingComparisonView::AssertValid() const
{
	CView::AssertValid();
}

void CSortingComparisonView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSortingComparisonDoc* CSortingComparisonView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSortingComparisonDoc)));
	return (CSortingComparisonDoc*)m_pDocument;
}
#endif //_DEBUG

//===========================================
// message handlers
//===========================================

void CSortingComparisonView::OnSortProperties()
{
	SortDlg sDlg;
	if (sDlg.DoModal() != IDOK) return;

	ResetTimes();
	currentArraySize = sDlg.getArraySize();

	SortAlgs sortAlgs(currentArraySize);

	if (sDlg.getInfoSelection())
	{
		size_t start = clock();
		sortAlgs.SelectionSort();
		size_t stop = clock();
		m_dSortTimes[0] = (float)(stop - start) / CLOCKS_PER_SEC;
		sortAlgs.ResetArrData();
	}

	if (sDlg.getInfoInsertion())
	{
		size_t start = clock();
		sortAlgs.InsertionSort();
		size_t stop = clock();
		m_dSortTimes[1] = (float)(stop - start) / CLOCKS_PER_SEC;
		sortAlgs.ResetArrData();
	}

	if (sDlg.getInfoHInsertion())
	{
		size_t start = clock();
		sortAlgs.HalfInsertionSort();
		size_t stop = clock();
		m_dSortTimes[2] = (float)(stop - start) / CLOCKS_PER_SEC;
		sortAlgs.ResetArrData();
	}

	if (sDlg.getInfoBubble())
	{
		size_t start = clock();
		sortAlgs.BubbleSort();
		size_t stop = clock();
		m_dSortTimes[3] = (float)(stop - start) / CLOCKS_PER_SEC;
		sortAlgs.ResetArrData();
	}

	if (sDlg.getInfoMBubble())
	{
		size_t start = clock();
		sortAlgs.MixedBubbleSort();
		size_t stop = clock();
		m_dSortTimes[4] = (float)(stop - start) / CLOCKS_PER_SEC;
		sortAlgs.ResetArrData();
	}

	if (sDlg.getInfoHeap())
	{
		size_t start = clock();
		sortAlgs.HeapSort();
		size_t stop = clock();
		m_dSortTimes[5] = (float)(stop - start) / CLOCKS_PER_SEC;
		sortAlgs.ResetArrData();
	}

	if (sDlg.getInfoQuick())
	{
		size_t start = clock();
		sortAlgs.QuickSort(0, sDlg.getArraySize() - 1);
		size_t stop = clock();
		m_dSortTimes[6] = (float)(stop - start) / CLOCKS_PER_SEC;
		sortAlgs.ResetArrData();
	}

	Invalidate();
}

void CSortingComparisonView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	GetClientRect(m_pClientRect);

	CView::OnPrepareDC(pDC, pInfo);
}

//===========================================
// custom functions
//===========================================


void CSortingComparisonView::ResetTimes()
{
	for (int i = 0; i < NO_SORTS; ++i)
		m_dSortTimes[i] = .0;
}


void CSortingComparisonView::DrawBackground(CDC* pDC)
{
	// drawing axes - horizontal + vertical
	CPen* pOldPen = pDC->SelectObject(m_pPenBlack);
	pDC->MoveTo(MARGIN, MARGIN);
	pDC->LineTo(MARGIN, m_pClientRect->bottom - MARGIN);
	pDC->LineTo(m_pClientRect->right - MARGIN, m_pClientRect->bottom - MARGIN);

	// drawing sort names
	namesPosition = (m_pClientRect->right - 2 * MARGIN) / NO_SORTS;

	for (int i = 0; i < NO_SORTS; i++)
		pDC->TextOutW(MARGIN + namesPosition * i + 5, m_pClientRect->bottom - MARGIN + 5, m_sSortNames[i]);


	// drawing measure lines
	noLines = (m_pClientRect->bottom - 2 * MARGIN) / MARGIN;
	linesPosition = (double)(m_pClientRect->bottom - 2 * MARGIN) / (double)(m_pClientRect->bottom / MARGIN);
	pDC->SelectObject(m_pPencil);

	for (int i = 0; i <= noLines + 1; i++)
	{
		pDC->MoveTo(MARGIN, MARGIN + i * linesPosition);
		pDC->LineTo(m_pClientRect->right - MARGIN, MARGIN + i * linesPosition);
	}

	// afterwork
	pDC->SelectObject(pOldPen);
}


void CSortingComparisonView::DrawDiagram(CDC* pDC)
{
	// drawing timestamps
	double maxTimeValue = *std::max_element(m_dSortTimes.begin(), m_dSortTimes.end());
	if (maxTimeValue == 0.0) return;

	double timeStep = maxTimeValue / ((double)noLines + 2);
	CString timeStr, infoStr;

	for (int i = 0; i <= noLines + 1; i++)
	{
		timeStr.Format(L"%.4f", maxTimeValue - timeStep * i);
		pDC->TextOutW(5, MARGIN + i * linesPosition - 10, timeStr);
	}
	timeStr.Format(L"%.4f", 0.0);
	pDC->TextOutW(5, m_pClientRect->bottom - MARGIN - 12, timeStr);

	// drawing array size
	CString arrSizeText;
	arrSizeText.Format(L"Array size: %d", currentArraySize);
	pDC->TextOutW(MARGIN, MARGIN / 3, arrSizeText);


	// drawing value rectangles
	for (int i = 0; i < NO_SORTS; ++i)
	{
		if (m_dSortTimes[i] <= .0001) continue;

		CPen* pOldPen = pDC->SelectObject(m_pPens[i]);
		CBrush* pOldBrush = pDC->SelectObject(m_bBrushes[i]);

		double height = m_dSortTimes[i] / maxTimeValue;
		height *= (double)(m_pClientRect->bottom - 2 * MARGIN);

		pDC->Rectangle(
			MARGIN + namesPosition * i + 5,
			m_pClientRect->bottom - MARGIN - (int)height,
			MARGIN + namesPosition * (i + 1) - 5,
			m_pClientRect->bottom - MARGIN - 1
		);

		infoStr.Format(L"%.4f sec", m_dSortTimes[i]);
		pDC->TextOutW(MARGIN + namesPosition * i + 5, m_pClientRect->bottom - MARGIN - (int)height - 25, infoStr);

		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
	}
}