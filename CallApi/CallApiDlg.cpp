// CallApiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CallApi.h"
#include "CallApiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCallApiDlg dialog

CCallApiDlg::CCallApiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCallApiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCallApiDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCallApiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCallApiDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCallApiDlg, CDialog)
	//{{AFX_MSG_MAP(CCallApiDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCallApiDlg message handlers

BOOL CCallApiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCallApiDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCallApiDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


PROCESS_INFORMATION  ProcessCreate(wchar_t * cProcessPath,wchar_t * cRunCommendLink)
{
	STARTUPINFOW StatInfo;
	ZeroMemory(&StatInfo,sizeof(STARTUPINFOW));
	StatInfo.cb = sizeof(StatInfo); //��ʼ��STARTUPINFO �ṹ�Ĵ�С
	PROCESS_INFORMATION mProcInfo;//�ñ��������½����̵ı�־��Ϣ
	CreateProcessW(cProcessPath, //���ڴ�ָ����ִ�е��ļ���
		cRunCommendLink, //�����в���
		NULL, //Ĭ�Ͻ��̰�ȫ����
		NULL, //Ĭ���̰߳�ȫ����
		FALSE, //ָ����ǰ�����ڵľ�������Ա��½��̼̳�
		NULL,   //ʹ��Ĭ�ϵĴ�����ʽ
		NULL,   //ʹ�ñ����̵Ļ�������
		NULL,   //ʹ�ñ����̵�Ŀ¼
		&StatInfo,    //ʹ��Ĭ�ϵ���ʾ��ʽ
		&mProcInfo); //�����½����̵ı�־��Ϣ
	return mProcInfo;
}

void CCallApiDlg::OnOK() 
{
	// TODO: Add extra validation here
	wchar_t szCommandLine[] = L"\"C:\\Windows\\System32\\wscript.exe\"";
	ProcessCreate(NULL,szCommandLine);	
	//CDialog::OnOK();
}
