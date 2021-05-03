// SortDlg.cpp : implementation file
//

#include "pch.h"
#include "SortingComparison.h"
#include "SortDlg.h"
#include "afxdialogex.h"


// SortDlg dialog

IMPLEMENT_DYNAMIC(SortDlg, CDialog)

SortDlg::SortDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SORT_DLG, pParent)
{
	m_bSelection = FALSE;
	m_bInsertion = FALSE;
	m_bHInsertion = FALSE;
	m_bBubble = FALSE;
	m_bMBubble = FALSE;
	m_bHeap = FALSE;
	m_bQuick = FALSE;

	m_nArraySize = 10;
}

SortDlg::~SortDlg()
{
}

void SortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_SELECTION, m_bSelection);
	DDX_Check(pDX, IDC_INSERTION, m_bInsertion);
	DDX_Check(pDX, IDC_H_INSERTION, m_bHInsertion);
	DDX_Check(pDX, IDC_BUBBLE, m_bBubble);
	DDX_Check(pDX, IDC_M_BUBBLE, m_bMBubble);
	DDX_Check(pDX, IDC_HEAP, m_bHeap);
	DDX_Check(pDX, IDC_QUICK, m_bQuick);
	DDX_Text(pDX, IDC_ARRAY_SIZE, m_nArraySize);
	DDV_MinMaxInt(pDX, m_nArraySize, 0, MAX_SORT_SIZE);
}


BEGIN_MESSAGE_MAP(SortDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ALL, &SortDlg::OnClickedButtonAll)
END_MESSAGE_MAP()


// SortDlg message handlers


void SortDlg::OnClickedButtonAll()
{
	CButton* pBtn;
	pBtn = (CButton*)GetDlgItem(IDC_SELECTION);
	ASSERT(pBtn);
	pBtn->SetCheck(1);

	pBtn = (CButton*)GetDlgItem(IDC_INSERTION);
	ASSERT(pBtn);
	pBtn->SetCheck(1);

	pBtn = (CButton*)GetDlgItem(IDC_H_INSERTION);
	ASSERT(pBtn);
	pBtn->SetCheck(1);

	pBtn = (CButton*)GetDlgItem(IDC_BUBBLE);
	ASSERT(pBtn);
	pBtn->SetCheck(1);

	pBtn = (CButton*)GetDlgItem(IDC_M_BUBBLE);
	ASSERT(pBtn);
	pBtn->SetCheck(1);

	pBtn = (CButton*)GetDlgItem(IDC_HEAP);
	ASSERT(pBtn);
	pBtn->SetCheck(1);

	pBtn = (CButton*)GetDlgItem(IDC_QUICK);
	ASSERT(pBtn);
	pBtn->SetCheck(1);

	UpdateData(TRUE);
}

BOOL SortDlg::getInfoSelection()
{
	return m_bSelection;
}

BOOL SortDlg::getInfoInsertion()
{
	return m_bInsertion;
}

BOOL SortDlg::getInfoHInsertion()
{
	return m_bHInsertion;
}

BOOL SortDlg::getInfoBubble()
{
	return m_bBubble;
}

BOOL SortDlg::getInfoMBubble()
{
	return m_bMBubble;
}

BOOL SortDlg::getInfoHeap()
{
	return m_bHeap;
}

BOOL SortDlg::getInfoQuick()
{
	return m_bQuick;
}

int SortDlg::getArraySize()
{
	return m_nArraySize;
}