
// SearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Search.h"
#include "SearchDlg.h"
#include "afxdialogex.h"
//#include <climits>
//#include <iostream>
//#include <algorithm>
//#include <iterator>
//#include <iomanip>
//#include "node.h"
//#include "concretesearch.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSearchDlg 对话框

ConcreteSearch cs(new letter_Search(10));
string ss;

CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSearchDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OUT, m_strOut);
	DDX_Control(pDX, IDC_CHOICE, m_combBox);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	DDX_Control(pDX, IDC_IN, m_editIn);
}

BEGIN_MESSAGE_MAP(CSearchDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_IN, &CSearchDlg::OnEnChangeIn)
	ON_CBN_SELCHANGE(IDC_CHOICE, &CSearchDlg::OnCbnSelchangeChoice)
END_MESSAGE_MAP()


// CSearchDlg 消息处理程序

BOOL CSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_listCtrl.InsertColumn(0,"PossibleResult",LVCFMT_CENTER,120,-1);
	m_listCtrl.InsertColumn(1,"Distance",LVCFMT_CENTER,100,-1);
	m_listCtrl.InsertColumn(2," ",0,-1,-1);
	// TODO: 在此添加额外的初始化代码
	m_combBox.AddString("BER_Search");
	m_combBox.AddString("Exact_Search");
	m_combBox.AddString("BER_PR_Search");
	m_combBox.AddString("Letter_Search");

	m_editIn.SetWindowTextA("");
	m_strOut = _T("Please enter a word for search: ['qqq' to exit]\r\n");

	cs.setSearchWordAlgorithm(new BER_Search(3));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSearchDlg::OnPaint()
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
HCURSOR CSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSearchDlg::OnEnChangeIn()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//m_strOut="Please enter a word for search: ['qqq' to exit]\r\n";
	//cs=ConcreteSearch(new letter_Search(10));
	
	

	CString temp;
	CString orig;
	int i;
	m_editIn.GetWindowTextA(m_strIn);

	ss = CT2CA(m_strIn);
	m_strOut=cs.searchWord(ss).c_str();
	orig=m_strOut.Left(m_strOut.Find(":\r\n"));
	m_strOut = m_strOut.Right(m_strOut.GetLength() - m_strOut.Find(_T(":\r\n"))-2);

	if(m_combBox.GetCurSel()%2)	//Choose Exact OR Letter Search
	{

		m_listCtrl.DeleteAllItems();
	
		while(m_strOut.Find(_T("\r\n"))!=-1)
		{
			temp=m_strOut.Left(m_strOut.Find("\r\n"));
			m_strOut = m_strOut.Right(m_strOut.GetLength() - m_strOut.Find(_T("\r\n"))-2);
			
			m_listCtrl.InsertItem(0, temp);
			
		}
	}
	else
	{
		m_listCtrl.DeleteAllItems();
		i=0;

		while(m_strOut.Find(_T("\r\n"))!=-1)
		{
			temp=m_strOut.Left(m_strOut.Find("\r\n with"));
			m_strOut = m_strOut.Right(m_strOut.GetLength() - m_strOut.Find(_T("\r\n with"))-7);
			
			m_listCtrl.InsertItem(0, temp);
			 
		
			temp=m_strOut.Left(m_strOut.Find(" letter different from the input and"));
			m_strOut = m_strOut.Right(m_strOut.GetLength() - m_strOut.Find(_T(" letter different from the input and"))-36 );
			
			m_listCtrl.SetItemText(i, 1, temp);
			

			temp=m_strOut.Left(m_strOut.Find("\r\n"));
			m_strOut = m_strOut.Right(m_strOut.GetLength() - m_strOut.Find(_T("\r\n"))-2);
			
			m_listCtrl.SetItemText(i, 2, temp);
		
		
		}
	}
	m_strOut=orig;
	UpdateData(FALSE);

}



void CSearchDlg::OnCbnSelchangeChoice()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (m_combBox.GetCurSel()+1){
		case 1:
            cs.setSearchWordAlgorithm(new BER_Search(3));
            break;
	    case 2:
            cs.setSearchWordAlgorithm(new Exact_Search());
            break;
		case 3:
            cs.setSearchWordAlgorithm(new BER_PR_Search(3));
            break;
		case 4:
            cs.setSearchWordAlgorithm(new letter_Search(10));
			break;
	}
}
