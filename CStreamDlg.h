#pragma once



// CStreamDlg 窗体视图

class CStreamDlg : public CFormView
{
	DECLARE_DYNCREATE(CStreamDlg)

protected:
	CStreamDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CStreamDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STREAM };
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
	CString m_rc4txt1;
	CString m_rc4txt2;
	CString m_streamkey;
	CString m_rc4filepath;
	CButton m_rc4file;
	CString m_catxt1;
	CString m_catxt2;
	CString m_cacell;
	int m_cacellnum;
	int m_carule;
	CString m_cafilepath;
	CButton m_csfile;

	char* filename;
	bool  fileflag = false;
	int len = 0;
	int calen = 0;
	char output[BUFSIZ] = " ";

	char caoutput[BUFSIZ] = " ";
	char* rc4cipehr;
	CBrush m_brush;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();


	virtual void OnInitialUpdate();
};


