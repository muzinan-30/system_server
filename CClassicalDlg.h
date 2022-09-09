#pragma once



// CClassicalDlg 窗体视图

class CClassicalDlg : public CFormView
{
	DECLARE_DYNCREATE(CClassicalDlg)

protected:
	CClassicalDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CClassicalDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLASSICAL };
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
private:
	CString m_classtxt1;
	CString m_classtxt2;
	CString m_classkey;
	CString m_classfilepath;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
private:
	CButton m_classfile;
	char* filename;
	bool  fileflag = false;
	CComboBox m_classical1;
	CString funcSelect;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnCbnSelchangeCombo1();
	virtual void OnInitialUpdate();
};


