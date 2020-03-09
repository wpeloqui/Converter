
// ConverterDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Converter.h"
#include "ConverterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CConverterDlg dialog



CConverterDlg::CConverterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONVERTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConverterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, cbxType, m_CbxType);
	DDX_Control(pDX, ckbOpen, m_open);
}

BEGIN_MESSAGE_MAP(CConverterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(btnConvert, &CConverterDlg::OnBnClickedbtnconvert)
	ON_BN_CLICKED(btnChooser, &CConverterDlg::OnBnClickedbtnchooser)
	ON_CBN_SELCHANGE(cbxType, &CConverterDlg::OnCbnSelchangecbxtype)
	ON_BN_CLICKED(btnDestination, &CConverterDlg::OnBnClickedbtndestination)
	ON_BN_CLICKED(ckbOpen, &CConverterDlg::OnBnClickedckbopen)
END_MESSAGE_MAP()


// CConverterDlg message handlers

BOOL CConverterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_fullpath = _T("");
	m_outputType = _T("");
	m_destinationFolder = _T("");
	m_openAfter = (m_open.GetCheck() == BST_CHECKED ? true : false);

	// Load the type combo box
	//
	//

	m_CbxType.SetCurSel(0);
	short index = m_CbxType.GetCurSel();
	m_CbxType.GetLBText(index, m_outputType);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CConverterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CConverterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CConverterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CConverterDlg::OnBnClickedbtnconvert()
{
	CT2A path(m_fullpath);
	CT2A folder(m_destinationFolder);
	CT2A extension(m_outputType);

	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char directory[_MAX_DIR];
	char fname[_MAX_FNAME];
	errno_t err;

	err = _splitpath_s(path, NULL, 0, NULL, 0, fname, _MAX_FNAME, NULL, 0);

	if (err != 0)
	{
		AfxMessageBox(_T("Unknown Error Opening Converted File."), MB_OK | MB_ICONSTOP);
		return;
	}

	err = _splitpath_s(folder, drive, _MAX_DRIVE, directory, _MAX_DIR, NULL, 0, NULL, 0);

	if (err != 0)
	{
		AfxMessageBox(_T("Unknown Error Opening Converted File."), MB_OK | MB_ICONSTOP);
		return;
	}

	err = _makepath_s(path_buffer, _MAX_PATH, drive, directory, fname, extension);

	if (err != 0)
	{
		AfxMessageBox(_T("Unknown Error Opening Converted File."), MB_OK | MB_ICONSTOP);
		return;
	}

	CString src(path);
	CString dst(path_buffer);

	if (CopyFile(src, dst, FALSE) == 0)
	{
		AfxMessageBox(_T("Copy Operation Failed"), MB_OK | MB_ICONSTOP);
		return;
	}

	if (m_openAfter == true)
	{
		int results = (int) ShellExecute(0, 0, dst, 0, 0, SW_SHOW);

		if (results > 32)
		{

			AfxMessageBox(_T("Conversion is Complete!"), MB_OK | MB_ICONEXCLAMATION);
			return;
		}
		else if (results == SE_ERR_NOASSOC)
		{
			AfxMessageBox(_T("Sorry, No Program is associated with this type."), MB_OK | MB_ICONSTOP);
		}
		else
		{
			AfxMessageBox(_T("Unknown Error Opening Converted File."), MB_OK | MB_ICONSTOP);
		}
	}

}


void CConverterDlg::OnBnClickedbtnchooser()
{

	CString extensions("InDesign File (*.indd)|*.indd||");
	CString defExt("");
	CString defName("");

	CFileDialog dlg(TRUE, defName, defExt, OFN_FILEMUSTEXIST, extensions, this);

	auto result = dlg.DoModal();

	if (result != IDOK)
	{
		return;
	}

	m_fullpath = dlg.GetPathName();

	CT2A path(m_fullpath);

	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char directory[_MAX_DIR];

	errno_t err;

	_splitpath_s(path, NULL, 0, NULL, 0, fname, _MAX_FNAME, ext, _MAX_EXT);

	strcat_s(fname, ext);

	CString filename(fname);
	SetDlgItemText(txtFile, filename);

	// Fill in the destination default
	//
	//

	CT2A folder(m_destinationFolder);
	CT2A extension(m_outputType);

	err = _splitpath_s(path, drive, _MAX_DRIVE, directory, _MAX_DIR, NULL, 0, NULL, 0);

	if (err != 0)
	{
		AfxMessageBox(_T("Unknown Error Splitting Path."), MB_OK | MB_ICONSTOP);
	}

	err = _makepath_s(path_buffer, _MAX_PATH, drive, directory, NULL, NULL);

	if (err != 0)
	{
		AfxMessageBox(_T("Unknown Error Making Default Destination."), MB_OK | MB_ICONSTOP);
	}

	m_destinationFolder = CA2T(path_buffer);
	SetDlgItemText(txtDestination, m_destinationFolder);
}


void CConverterDlg::OnCbnSelchangecbxtype()
{
	short index = m_CbxType.GetCurSel();
	m_CbxType.GetLBText(index, m_outputType);

}


void CConverterDlg::OnBnClickedbtndestination()
{

	CFolderPickerDialog dlg;

	dlg.m_ofn.lpstrTitle = _T("Put Title Here");
	dlg.m_ofn.lpstrInitialDir = _T("C:\\");

	if (dlg.DoModal() == IDOK)
	{
		m_destinationFolder = dlg.GetPathName();
		m_destinationFolder += _T("\\");
		SetDlgItemText(txtDestination, m_destinationFolder);
	}

}


void CConverterDlg::OnBnClickedckbopen()
{
	m_openAfter = (m_open.GetCheck() == BST_CHECKED ? true : false);
}
