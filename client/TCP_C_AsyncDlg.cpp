
// TCP_C_AsyncDlg.cpp: 實作檔案
//

#include "stdafx.h"
#include "TCP_C_Async.h"
#include "TCP_C_AsyncDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
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


// CTCPCAsyncDlg 對話方塊



CTCPCAsyncDlg::CTCPCAsyncDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TCP_C_ASYNC_DIALOG, pParent)
	, m_Edit1(_T(""))
	, m_Edit2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCPCAsyncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	DDX_Text(pDX, IDC_EDIT2, m_Edit2);
}

BEGIN_MESSAGE_MAP(CTCPCAsyncDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTCPCAsyncDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTCPCAsyncDlg 訊息處理常式

BOOL CTCPCAsyncDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CTCPCAsyncDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CTCPCAsyncDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CTCPCAsyncDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ########################################################
// ########################################################
#include "TCPIP_Async.cpp"
#include <iostream>
#include <string>

#define   CEVENT  (WM_USER+100)
SOCKET    CSock;
//sockaddr_in CAddr;
BOOL      F = 0;
char IP[100] = { "127.0.0.1" };
void CTCPCAsyncDlg::OnBnClickedButton1()
{
	int      Len;
	char     S1[2000];
	wchar_t  *S11;

	// 1.啟動 TCP Client(第一次才會啟動)
	if (F == 0) 
	{  
		F = 1; 
		Start_TCP_Client(&CSock, 6000, "127.0.0.1", CEVENT, m_hWnd);
	}
	
	// 2.擷取輸入框資訊
	UpdateData(1); 
	S11 = (wchar_t *)m_Edit2.GetString(); 
	Len = m_Edit2.GetLength(); 
	UpdateData(0);
	
	// 3.轉換
	UniCodeToBig5(S11, S1, Len);
	// 4.送出
	send(CSock, S1, strlen(S1), 0);
	
}


LRESULT CAboutDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CDialogEx::WindowProc(message, wParam, lParam);
}


LRESULT CTCPCAsyncDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	int      i, Len = sizeof(sockaddr);
	char     S1[2000];
	wchar_t  SS1[2000];

	if (message == CEVENT)
	{
		switch (LOWORD(lParam))
		{
			case FD_CONNECT: // 連線伺服器成功事件
				UpdateData(1); 
				m_Edit1 += L"連線伺服器成功\r\n"; 
				UpdateData(0);
				break;

			case FD_READ:   // 遠端送來資料事件
				i = recv(wParam, S1, sizeof(S1) - 1, 0);
				if (i > 0)
				{	
					S1[i] = 0; 
					Big5ToUniCode(S1, SS1, strlen(S1)+1);
					UpdateData(1); 
					m_Edit1 += SS1;
					m_Edit1 += "\r\n";  
					UpdateData(0);
				}
				break;

			case FD_CLOSE:  // 遠端斷線事件
				closesocket(wParam);
				UpdateData(1); 
				m_Edit1 += L"遠端斷線\r\n"; 
				UpdateData(0);
				break;
		}

	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}
