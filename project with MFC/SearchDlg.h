
// SearchDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSearchDlg �Ի���
class CSearchDlg : public CDialogEx
{
// ����
public:
	CSearchDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SEARCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

