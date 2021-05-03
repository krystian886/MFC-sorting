#pragma once

#define MAX_SORT_SIZE 1000000

// SortDlg dialog

class SortDlg : public CDialog
{
	DECLARE_DYNAMIC(SortDlg)

public:
	SortDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SortDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SORT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bSelection;
	BOOL m_bInsertion;
	BOOL m_bHInsertion;
	BOOL m_bBubble;
	BOOL m_bMBubble;
	BOOL m_bHeap;
	BOOL m_bQuick;
	int m_nArraySize;
public:
	afx_msg void OnClickedButtonAll();

	BOOL getInfoSelection();
	BOOL getInfoInsertion();
	BOOL getInfoHInsertion();
	BOOL getInfoBubble();
	BOOL getInfoMBubble();
	BOOL getInfoHeap();
	BOOL getInfoQuick();

	int getArraySize();
};
