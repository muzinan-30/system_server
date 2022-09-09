// CCdhDlg.cpp: 实现文件
//

#include "pch.h"
#include "system_server.h"
#include "CCdhDlg.h"

#include  "dh.cpp"
// CCdhDlg

IMPLEMENT_DYNCREATE(CCdhDlg, CFormView)

CCdhDlg::CCdhDlg()
	: CFormView(IDD_CDH)
	, m_dhdeskey(_T(""))
	, m_recvfilepath(_T(""))
	, m_plaintext(_T(""))
	, m_dhA(0)
	, m_dhkey(0)
{

}

CCdhDlg::~CCdhDlg()
{
}

void CCdhDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_dhA);
	//  DDX_Text(pDX, IDC_EDIT2, m_dhkey);
	//  DDX_Control(pDX, IDC_EDIT5, m_dhdeskey);
	DDX_Text(pDX, IDC_EDIT5, m_dhdeskey);
	DDX_Text(pDX, IDC_EDIT3, m_recvfilepath);
	DDX_Text(pDX, IDC_EDIT4, m_plaintext);
	DDX_Text(pDX, IDC_EDIT1, m_dhA);
	DDX_Text(pDX, IDC_EDIT2, m_dhkey);
}

BEGIN_MESSAGE_MAP(CCdhDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CCdhDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT5, &CCdhDlg::OnEnChangeEdit5)
	ON_BN_CLICKED(IDC_BUTTON4, &CCdhDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CCdhDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CCdhDlg 诊断

#ifdef _DEBUG
void CCdhDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCdhDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCdhDlg 消息处理程序

//密钥协商
void CCdhDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建客户端的socket
	int listenfd, connfd;
	int len;

	ll a;
	ll p;
	//读取文件取出共享的数据
	ifstream inFile;
	inFile.open("prime.txt");
	if (!inFile.is_open()) { cout << " open failed" << endl; }
	inFile >> p;
	inFile >> a;
	inFile.close();

	srand((unsigned)time(NULL));
	ll A = rand() % p;
	ll Ya = dh::q_pow(a, A, p);
	cout << "server selection:" << A << "send " << Ya << endl;

	m_dhA = A;

	//stringstream ss;
	//ss<< p;
	//MessageBox(CString(ss.str().c_str()));

	//连接客户端
	struct sockaddr_in servaddr, cliaddr;
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout << "socket created failed.\n" << endl;
	};

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	servaddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
		cout << "bind failed\n" << endl;

	}

	cout << "listening\n" << endl;

	listen(listenfd, 5);

	len = sizeof(cliaddr);
	connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);


	//转为字符串
	//发送Ya
	char ch[100] = {};
	itoa(Ya, ch, 10);
	char* str = ch;
	send(connfd, str, strlen(str) + sizeof(char), 0);

	char szBuffer[BUFSIZ] = {};
	recv(connfd, szBuffer, BUFSIZ, 0);
	cout << "The data received from the client is:" << szBuffer << endl;


	int Yb = 0;
	for (int i = 0; szBuffer[i] != '\0'; i++)
	{
		Yb *= 10;
		Yb += szBuffer[i] - '0';
	}

	ll K = dh::q_pow(Yb, A, p);
	cout << "The negotiated key is:" << K << endl;

	m_dhkey = K;

	//关闭套接字
	closesocket(connfd);

	//终止使用 DLL
	WSACleanup();

	closesocket(listenfd);
	closesocket(connfd);

	UpdateData(FALSE);
}


void CCdhDlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



//解密文件
void CCdhDlg::OnBnClickedButton4()
{
	UpdateData(TRUE);
	ifstream input;
	input.open((char*)filename.c_str());
	string plain;
	input >> plain;
	m_plaintext = CString(plain.c_str());
	input.close();
	UpdateData(FALSE);
}


//接收文件
void CCdhDlg::OnBnClickedButton3()
{
	//初始化DLL
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0)
	{
		cout << "打开成功网络库成功" << endl;
	}
	else
	{
		exit(1);
	}


	//创建客户端的socket
	int listenfd, connfd;
	int len;

	//连接客户端
	struct sockaddr_in servaddr, cliaddr;
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout << "socket created failed.\n" << endl;

	};

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	servaddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
		cout << "bind failed\n" << endl;

	}

	cout << "listening\n" << endl;

	listen(listenfd, 5);


	len = sizeof(cliaddr);
	connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);


	//接受文件名
	char namebuffer[50] = "";
	memset(namebuffer, '\0', sizeof(namebuffer));
	if (recv(connfd, namebuffer, sizeof(namebuffer), 0) < 0)
	{
		cout << "name接受异常" << endl;
	}

	//同步控件内容
	m_recvfilepath = CString(namebuffer);

	string filepath(namebuffer);
	cout << filepath;
	ofstream outFile;
	outFile.open(filepath + "bak.txt", ios::out);
	char szBuffer[BUFSIZ] = "";
	//新建文件夹内容
	do
	{
		memset(szBuffer, '\0', sizeof(szBuffer));
		cout << sizeof(szBuffer);
		if (recv(connfd, szBuffer, sizeof(szBuffer), 0) < 0)
		{
			cout << "接受失败" << endl;
		}
		else
		{
			cout << "接受成功" << endl;
		}
		outFile << szBuffer;
		outFile << endl;
		cout << *szBuffer << endl;
	} while (*szBuffer != 94);
	outFile.close();
	//解密文件并得到解密密钥
	filename = filepath + "bak.txt";
	string deskey = dh_defile((char*)filename.c_str(), m_dhkey);
	m_dhdeskey = CString(deskey.c_str());

	cout << "接受完毕" << endl;
	strcpy(namebuffer, "recv over!");
	send(connfd, namebuffer, strlen(namebuffer), 0);

	//关闭套接字
	closesocket(connfd);

	//终止使用 DLL
	WSACleanup();


	closesocket(listenfd);
	closesocket(connfd);


	UpdateData(FALSE);
	return;
}
