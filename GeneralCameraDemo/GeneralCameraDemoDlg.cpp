
// GeneralCameraDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GeneralCameraDemo.h"
#include "GeneralCameraDemoDlg.h"
#include "afxdialogex.h"

#include "GenaralCamera.h"

#pragma comment(lib,"GeneralCamera.lib") 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


bool m_bCaptureBuffer = false;
int iBufferCount = 0;

// CGeneralCameraDemoDlg 对话框



CGeneralCameraDemoDlg::CGeneralCameraDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGeneralCameraDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGeneralCameraDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGeneralCameraDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGeneralCameraDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGeneralCameraDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CGeneralCameraDemoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CGeneralCameraDemoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CGeneralCameraDemoDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CGeneralCameraDemoDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CGeneralCameraDemoDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CGeneralCameraDemoDlg::OnBnClickedButton8)
END_MESSAGE_MAP()

int CALLBACK pThread1(BYTE* pData, LONG BufferLength)
{
	//TRACE("pThread1 %d\n", BufferLength);
	CString FileName;
	FileName.Format(L"%d.jpg", iBufferCount++);
	if (m_bCaptureBuffer)
	{
		m_bCaptureBuffer = false;
		CFile SaveFile;
		SaveFile.Open(FileName, CFile::modeWrite | CFile::modeCreate, NULL);
		SaveFile.Write(pData, BufferLength);
		SaveFile.Close();
	}
	return 0;
}


// CGeneralCameraDemoDlg 消息处理程序

BOOL CGeneralCameraDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	long iCount;
	int i = GetCameraCount(&iCount);
	char *pVID = NULL, *pPID = NULL, *pDeviceName = NULL;
	i = GetCameraInfo(0, &pVID, &pPID, &pDeviceName);

	i = CameraInit(0,
		pThread1,
		GetDlgItem(IDC_SHOW)->m_hWnd
		);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGeneralCameraDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGeneralCameraDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGeneralCameraDemoDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	int i = CameraPlay(0);
	if (i != 1)
	{
		i = CameraInit(0,
			pThread1,
			GetDlgItem(IDC_SHOW)->m_hWnd);
		i = CameraPlay(0);
	}
	if (i != 1)
	{
		MessageBox(L"Failed", NULL, NULL);
	}
}


void CGeneralCameraDemoDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	int i = CameraStop(0);
	i = CameraUnInit(0);
}


void CGeneralCameraDemoDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	WCHAR FileName[] = { _T("1234.avi") };
	int i = CameraStartCapture(0, VIDEOFORMAT_avi, FileName);
	if (i != 1)
	{
		MessageBox(L"Failed", NULL, NULL);
	}
}


void CGeneralCameraDemoDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	int i = CameraStopCapture(0);
	if (i != 1)
	{
		MessageBox(L"Failed", NULL, NULL);
	}
}




void CGeneralCameraDemoDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	long iCount = 0;
	COLORSPACE iColor;
	long lWidth, lHeight = 0;

	int i = GetPreviewResolutionCount(0, &iCount);
	for (int i = 0; i < iCount; i++)
	{
		GetPreviewResolutionInfo(0, i, &iColor, &lWidth, &lHeight);
	}
	UpdateData(FALSE);
}


void CGeneralCameraDemoDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	int i = CameraSetVideoFormat(0, 0);
	if (i != 1)
	{
		MessageBox(L"Failed", NULL, NULL);
	}
}


void CGeneralCameraDemoDlg::OnBnClickedButton7()
{
	// TODO:  在此添加控件通知处理程序代码
	m_bCaptureBuffer = true;
}


void CGeneralCameraDemoDlg::OnBnClickedButton8()
{
	// TODO:  在此添加控件通知处理程序代码
	WCHAR FileName[] = { _T("1234.jpg") };
	int i = CameraSnapShot(0, PICTUREFORMAT_JPG, FileName);
	if (i != 1)
	{
		MessageBox(L"Failed", NULL, NULL);
	}
}
