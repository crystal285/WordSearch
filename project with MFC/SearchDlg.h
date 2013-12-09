
// SearchDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSearchDlg 对话框
class CSearchDlg : public CDialogEx
{
// 构造
public:
	CSearchDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SEARCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strIn;
	CString m_strOut;
	afx_msg void OnEnChangeIn();
	afx_msg void OnCbnSelchangeChoice();
	CComboBox m_combBox;
	CListCtrl m_listCtrl;
	CEdit m_editIn;
};

