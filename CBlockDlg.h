#pragma once


#include<vector>
#include<string>
// CBlockDlg 窗体视图

class CBlockDlg : public CFormView
{
	DECLARE_DYNCREATE(CBlockDlg)

protected:
	CBlockDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CBlockDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLOCK };
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
	CString m_blocktxt1;
	CString m_blocktxt2;
	CString m_blockkey;
	CComboBox m_block1;
	CString m_blockfilepath;

	CString funcSelect;
	char* filename;
	bool  fileflag = false;

	std::vector<std::string> block = { "DES","AES" };
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnCbnSelchangeCombo1();
	virtual void OnInitialUpdate();
private:
	CButton m_blockfile;
};


