#pragma once



#include<string>
// CCdhDlg 窗体视图

class CCdhDlg : public CFormView
{
	DECLARE_DYNCREATE(CCdhDlg)

protected:
	CCdhDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CCdhDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDH };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit5();
private:
//	CString m_dhA;
//	CString m_dhkey;
public:
//	CEdit m_dhdeskey;
private:
	CString m_dhdeskey;
	CString m_recvfilepath;
	CString m_plaintext;
	std::string filename;
public:
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
private:
	long long m_dhA;
	long long m_dhkey;
};


