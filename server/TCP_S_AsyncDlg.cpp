
// TCP_S_AsyncDlg.cpp: 實作檔案
//

#include "stdafx.h"
#include "TCP_S_Async.h"
#include "TCP_S_AsyncDlg.h"
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


// CTCPSAsyncDlg 對話方塊



CTCPSAsyncDlg::CTCPSAsyncDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TCP_S_ASYNC_DIALOG, pParent)
	, m_Edit1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCPSAsyncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_LIST1, m_List1);
}

BEGIN_MESSAGE_MAP(CTCPSAsyncDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTCPSAsyncDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CTCPSAsyncDlg::OnEnChangeEdit1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTCPSAsyncDlg::OnLvnItemchangedList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CTCPSAsyncDlg::OnClickList1)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CTCPSAsyncDlg::OnColumnclickList1)
END_MESSAGE_MAP()


// CTCPSAsyncDlg 訊息處理常式

BOOL CTCPSAsyncDlg::OnInitDialog()
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

void CTCPSAsyncDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTCPSAsyncDlg::OnPaint()
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
HCURSOR CTCPSAsyncDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// #####################################################
// #####################################################
#include "TCPIP_Async.cpp"
#define  SEVENT  (WM_USER+100)
SOCKET   SSock;
void CTCPSAsyncDlg::OnBnClickedButton1()
{
	// 啟動 TCP 伺服器
	Start_TCP_Server(&SSock, 6000, SEVENT, m_hWnd);
	UpdateData(1);
	m_Edit1 += L"開放連入囉~~~\r\n";
	UpdateData(0);//顯示訊息

	//設定list
	m_List1.InsertColumn(0, L"狀態");		m_List1.SetColumnWidth(0, 130);
	m_List1.InsertColumn(1, L"port");		m_List1.SetColumnWidth(1, 110);
	m_List1.InsertColumn(2, L"wParam");		m_List1.SetColumnWidth(2, 110);

}
#include <string> 

using namespace std;
#define MAX 100

SOCKET  Sock[MAX];
int CIP[2000];
int CPort[2000];
int     No = 0;
CString n;

LRESULT CTCPSAsyncDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	int      i,Len = sizeof(sockaddr);
	char     S1[2000], S2[200], Client_IP[33], IP[18], Port[20], arm[10];
	wchar_t  SS1[2000], SS2[200], SS3[200], SS4[200];

	sockaddr_in Addr;
	
	if (message == SEVENT)
	{  
		switch(LOWORD(lParam))
	    {  
			case FD_ACCEPT: // 遠端要求連線事件
				Sock[No] = accept(wParam, (sockaddr *)&Addr, &Len); // 接受連線
				CIP[No] = Addr.sin_addr.s_addr;
				CPort[No] = Addr.sin_port;

				//UpdateData();
				//List 欄位0加上 client IP
				sprintf_s(IP, sizeof(IP) - 1, "IP = %d.%d.%d.%d",
					(CIP[No] >> 0) & 0xFF,
					(CIP[No] >> 8) & 0xFF,
					(CIP[No] >> 16) & 0xFF,
					(CIP[No] >> 24) & 0xFF);
				Big5ToUniCode(IP, SS2, strlen(IP) + 1);
				m_List1.InsertItem(No, SS2);

				//List 欄位1加上 Port
				sprintf_s(Port, sizeof(Port) - 1, "%d", ((CPort[No] & 0xFF) << 8) + ((CPort[No] >> 8) & 0xFF) );
				Big5ToUniCode(Port, SS3, strlen(Port) + 1);
				m_List1.SetItemText(No, 1, SS3);

				//List 欄位2加上 wParam
				sprintf_s(arm, sizeof(arm) - 1, "%d", Sock[No]);
				Big5ToUniCode(arm, SS4, strlen(arm) + 1);
				m_List1.SetItemText(No, 2, SS4);

				No = No + 1; 

				UpdateData(1); 
				n.Format(L"哇賽~~這是第 '%d' 個Client上線了!!\r\n", No);
				m_Edit1 += n;
				UpdateData(0);//顯示訊息
				break;

			case FD_READ:   // 遠端送來資料事件
			   // 1.接收資料
				i = recv(wParam, S1, sizeof(S1) - 1, 0);
				if (i > 0)
				{   // 2.資料轉換並顯示
			   		S1[i] = 0; 

					int U = 0;
					for (int i = 0; i < 500; i++) {
						if (Sock[i] == wParam)
							U = i;
					}
					//紀錄client IP
					sprintf_s(Client_IP, sizeof(Client_IP) - 1, "IP: %d.%d.%d.%d / wParam: %d >> ",
						(CIP[U] >> 0) & 0xFF,
						(CIP[U] >> 8) & 0xFF,
						(CIP[U] >> 16) & 0xFF,
						(CIP[U] >> 24) & 0xFF, wParam);
					
					Big5ToUniCode(S1, SS1, strlen(S1) + 1);
					UpdateData(1); 
					m_Edit1 += Client_IP;
					m_Edit1 += SS1; 
					m_Edit1 += "\r\n";  
					UpdateData(0);

				   // 3.資料轉傳給所有人
					for (i = 0; i < No; i++)
					{
						if (Sock[i] != wParam)
						{   
							send(Sock[i], Client_IP, strlen(Client_IP), 0);
							send(Sock[i], S1, strlen(S1), 0);
						}		
					}
				}
				break;

			case FD_CLOSE:  // 遠端斷線事件
				closesocket(wParam);



				int U = 0;
				for (int i = 0; i < 500; i++) {
					if (Sock[i] == wParam)
						U = i;
				}
				
				for (int j = U; j < No; j++) {

					Sock[j] = Sock[j + 1];
					CIP[j] = CIP[j + 1];
					CPort[j] = CPort[j + 1];

					if (j != No - 1) {
						m_List1.SetItemText(j, 0, m_List1.GetItemText(j + 1, 0));
						m_List1.SetItemText(j, 1, m_List1.GetItemText(j + 1, 1));
						m_List1.SetItemText(j, 2, m_List1.GetItemText(j + 1, 2));
					}
					else {
						sprintf_s(S1, sizeof(S1) - 1, " ");
						Big5ToUniCode(S1, SS1, strlen(S1) + 1);
						m_List1.SetItemText(j, 0, SS1);
						m_List1.SetItemText(j, 1, SS1);
						m_List1.SetItemText(j, 2, SS1);
					}
				}
				No--;

				UpdateData(1); 
				n.Format(L"IP: 127.0.0.1 / wParam %d 遠端斷線\r\n", wParam);
				m_Edit1 += n;
				m_Edit1 += L"ByeBye!! (被發洗澡卡QQ)\r\n";
				UpdateData(0);
				break;
		}
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CTCPSAsyncDlg::OnEnChangeEdit1()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
}


void CTCPSAsyncDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;
}



void CTCPSAsyncDlg::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;
}


void CTCPSAsyncDlg::OnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;
}
