
// ConverterDlg.h : header file
//

#pragma once


// CConverterDlg dialog
class CConverterDlg : public CDialogEx
{
// Construction
public:
	CConverterDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONVERTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedbtnconvert();
	afx_msg void OnBnClickedbtnchooser();
	afx_msg void OnCbnSelchangecbxtype();
	afx_msg void OnBnClickedbtndestination();
	afx_msg void OnBnClickedckbopen();
	afx_msg void OnBnClickedckbshowinfolder();

	CButton m_convert;
	CButton m_open;
	CButton m_show;
	CComboBox m_cbxType;
	
	CString m_fullpath;
	CString m_outputType;
	CString m_destinationFolder;
	bool m_openAfter;
	BOOL m_showInFolder;
};
