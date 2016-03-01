
// GeneralCameraDemoDlg.cpp : ʵ���ļ�
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

// CGeneralCameraDemoDlg �Ի���



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


// CGeneralCameraDemoDlg ��Ϣ�������

BOOL CGeneralCameraDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	long iCount;
	int i = GetCameraCount(&iCount);
	char *pVID = NULL, *pPID = NULL, *pDeviceName = NULL;
	i = GetCameraInfo(0, &pVID, &pPID, &pDeviceName);

	i = CameraInit(0,
		pThread1,
		GetDlgItem(IDC_SHOW)->m_hWnd
		);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGeneralCameraDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGeneralCameraDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGeneralCameraDemoDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i = CameraStop(0);
	i = CameraUnInit(0);
}


void CGeneralCameraDemoDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	WCHAR FileName[] = { _T("1234.avi") };
	int i = CameraStartCapture(0, VIDEOFORMAT_avi, FileName);
	if (i != 1)
	{
		MessageBox(L"Failed", NULL, NULL);
	}
}


void CGeneralCameraDemoDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i = CameraStopCapture(0);
	if (i != 1)
	{
		MessageBox(L"Failed", NULL, NULL);
	}
}




void CGeneralCameraDemoDlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i = CameraSetVideoFormat(0, 0);
	if (i != 1)
	{
		MessageBox(L"Failed", NULL, NULL);
	}
}


void CGeneralCameraDemoDlg::OnBnClickedButton7()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_bCaptureBuffer = true;
}


void CGeneralCameraDemoDlg::OnBnClickedButton8()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	WCHAR FileName[] = { _T("1234.jpg") };
	int i = CameraSnapShot(0, PICTUREFORMAT_JPG, FileName);
	if (i != 1)
	{
		MessageBox(L"Failed", NULL, NULL);
	}
}
