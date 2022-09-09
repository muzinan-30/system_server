// CMd5Dlg.cpp: 实现文件
//

#include "pch.h"
#include "system_server.h"
#include "CMd5Dlg.h"


#include "md5.cpp"
// CMd5Dlg

IMPLEMENT_DYNCREATE(CMd5Dlg, CFormView)

CMd5Dlg::CMd5Dlg()
	: CFormView(IDD_MD5)
	, m_md5string(_T(""))
	, m_md5value(_T(""))
	, m_md5filepath(_T(""))
{

}

CMd5Dlg::~CMd5Dlg()
{
}

void CMd5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_md5string);
	//  DDX_Control(pDX, IDC_EDIT2, m_md5filepath);
	DDX_Text(pDX, IDC_EDIT3, m_md5value);
	DDX_Text(pDX, IDC_EDIT2, m_md5filepath);
	DDX_Control(pDX, IDC_BUTTON1, m_md5file);
}

BEGIN_MESSAGE_MAP(CMd5Dlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMd5Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMd5Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMd5Dlg 诊断

#ifdef _DEBUG
void CMd5Dlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMd5Dlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMd5Dlg 消息处理程序



//打开文件
void CMd5Dlg::OnBnClickedButton1()
{
	CString filter;
	CString str;
	filter = "文本文件(*.txt)|*.txt|C++文件(*.h,*.cpp)|*.h;*.cpp||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter);
	if (dlg.DoModal() == IDOK)
	{

		str = dlg.GetPathName();
		//AfxMessageBox(str);
	}

	UpdateData(TRUE);

	//Cstring 转 char*
	int len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), NULL, 0, NULL, NULL);
	char* filename = new char[len + 1];
	memset(filename, 0, sizeof((char*)(len + 1)));
	WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), filename, len, NULL, NULL);
	filename[len] = '\0';

	std::string res = md5::MDFile(filename);

	m_md5string.ReleaseBuffer();
	//MessageBox(CString(res.c_str()));
	m_md5value = res.c_str();
	m_md5filepath = str;

	UpdateData(FALSE);
}

//生成MD5值
void CMd5Dlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	//CString2char*
	//散列函数
	//MessageBox(m_md5string);

	//Cstring 转 char*
	int len = WideCharToMultiByte(CP_ACP, 0, m_md5string, m_md5string.GetLength(), NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, sizeof((char*)(len + 1)));
	WideCharToMultiByte(CP_ACP, 0, m_md5string, m_md5string.GetLength(), str, len, NULL, NULL);
	str[len] = '\0';


	std::string res = md5::MDString(str);

	m_md5string.ReleaseBuffer();
	//MessageBox(CString(res.c_str()));
	m_md5value = res.c_str();

	UpdateData(FALSE);
}


void CMd5Dlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON1);

	m_md5file.SetIcon(icon);
}
