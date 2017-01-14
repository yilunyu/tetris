// tetrisView.cpp : implementation of the CtetrisView class
//

#include "stdafx.h"
#include "tetris.h"
#include "Tile.h"
#include "tetrisDoc.h"
#include "tetrisView.h"
#include <afxsock.h>		
#include <afxwin.h>		
#include <vector>		
using namespace std;		
//extern CtetrisView* g_pCtetrisView;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtetrisView

IMPLEMENT_DYNCREATE(CtetrisView, CView)

BEGIN_MESSAGE_MAP(CtetrisView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_WM_KEYDOWN()
    ON_WM_TIMER()
END_MESSAGE_MAP()

// CtetrisView construction/destruction

CtetrisView::CtetrisView()
{
	// TODO: add construction code here
    
}

CtetrisView::~CtetrisView()
{
}

BOOL CtetrisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CtetrisView drawing

void CtetrisView::OnDraw(CDC* /*pDC*/)
{
	CtetrisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
    if(pDoc->firstTime)
    {
        gameBoard = new KGameBoard;
        gameBoard->addTile();
        CClientDC dc(this);
        gameBoard->drawBoard(::GetDC(m_hWnd));
        gameBoard->m_nWindowTimer = SetTimer(MOVEDOWN,800,NULL);
        pDoc->firstTime = FALSE;
        gameBoard->pThread = new CWinThread(StartServer, (LPVOID)this);		
        gameBoard->pThread->CreateThread(CREATE_SUSPENDED);		
        gameBoard->pThread->ResumeThread();
    }
	// TODO: add draw code for native data here
}


// CtetrisView printing
	BOOL m_exit = FALSE;

void StopServer()		
{		
    m_exit = true;		
}		
unsigned int CtetrisView::StartServer(LPVOID lParam)		
{		
    CtetrisView* pView = (CtetrisView*)lParam;		
    //初始化Winscok		
    if (!AfxSocketInit())		
    {		
       // AfxMessageBox("123",0,0);		
        return 1;		
    }		
    m_exit = false;		
    //CServerDlg *aDlg = (CServerDlg *)lParam;		
    //获取端口		
    CString charPort = _T("8080");		
    //aDlg->GetDlgItemText(IDC_EDIT_PORT, strPort);		
    		
    CStringA strPort(charPort);		
    UINT nPort = atoi((const char*)strPort);		
    //socket----创建2个socket--------------------------------------------		
    CSocket aSocket,serverSocket;		
    //最好不要使用pView->gameBoard->aSocket.Create创建，因为容易会出现10048错误		
    if (!aSocket.Socket())		
    {		
        char szError[256] = {0};		
        sprintf(szError, "Create Faild: %d", GetLastError());		
        AfxMessageBox(CString(szError), MB_OK, 0);		
        return 1; 		
    }		
    BOOL bOptVal = TRUE;		
    int bOptLen = sizeof(BOOL);		
    //设置Socket的选项, 解决10048错误必须的步骤		
    aSocket.SetSockOpt(SO_REUSEADDR, (void *)&bOptVal, bOptLen, SOL_SOCKET);		
    //绑定		
    if (!aSocket.Bind(nPort))		
    {		
        char szError[256] = {0};		
        sprintf(szError, "Bind Faild: %d", GetLastError());		
        AfxMessageBox((CString)szError);			
        return 1; 		
    }		
    //监听		
    if(!aSocket.Listen(10))		
    {			
        char szError[256] = {0};		
        sprintf(szError, "Listen Faild: %d", GetLastError());		
        AfxMessageBox((CString)szError);		
        return 1;		
    }		
    CString strText;		
    /*aDlg->GetDlgItemText(IDC_EDIT_LOG, strText);		
    strText += "服务已经开启! \r\n";		
    aDlg->SetDlgItemText(IDC_EDIT_LOG, strText);*/		
    //BOOL socketCreated = FALSE;		
    //CSocket serverSocket2;		
    while(!m_exit)		
    {		
        //接收外部连接		
        if(!aSocket.Accept(serverSocket))  		
        {  		
            continue;  		
        }  		
        char szRecvMsg[256] = {0};		
        char szOutMsg[256] = {0};			
        serverSocket.Receive(szRecvMsg, 256); //接收客户端内容:阻塞		
        sprintf(szOutMsg, "接受到的参数是: %s \r\n", szRecvMsg);		
        vector<string> result;		
        char* p = szRecvMsg;		
        do 		
        {		
            const char *begin = p;		
            while(*p != ',' && *p)		
                p++;		
            result.push_back(string(begin,p));		
        } while (0!= *p++);		
        for(int i=0;i<8;i=i+2)		
        {		
            string x = result[i];		
            string y = result[i+1];		
            int xint = atoi(x.c_str());		
            int yint = atoi(y.c_str());		
            pView->gameBoard->m_colorMatrix2[xint][yint] = L_GREY;		
        }		
        unsigned int tColor = strtoul(result[16].c_str(),NULL,10);		
        for(int i=8;i<16; i=i+2)		
        {		
            string x = result[i];		
            string y = result[i+1];		
            int xint = atoi(x.c_str());		
            int yint = atoi(y.c_str());		
            pView->gameBoard->m_colorMatrix2[xint][yint] = (COLORREF)tColor;		
        }		
        CClientDC dc(pView);		
        pView->gameBoard->drawBoard((HDC)dc);		

        CStringA strData;
        /*for(int i = 0; i < 10; ++i)
        {
            for(int j = 0; j < 23; ++j)
            {
                strData.AppendFormat("%lu", m_colorMatrix[i][j]);
                strData.Append(",");
            }
        }*/
        for(int i=0;i<4;i++)
        {
            strData.AppendFormat("%d",pView->gameBoard->m_changedCol[i]->x);
            strData.Append(",");
            strData.AppendFormat("%d",pView->gameBoard->m_changedCol[i]->y);
            strData.Append(",");
        }
       // strData.Append(".");
        for(int i=4;i<8;i++)
        {
            strData.AppendFormat("%d",pView->gameBoard->m_changedCol[i]->x);
            strData.Append(",");
            strData.AppendFormat("%d",pView->gameBoard->m_changedCol[i]->y);
            strData.Append(",");
        }
        strData.AppendFormat("%lu",pView->gameBoard->m_curTile->getColor());

       // char szRecValue[1024] = {0};
        serverSocket.Send(strData, strData.GetLength());
        serverSocket.Close();		
        
        		
    }		
    aSocket.Close();		
    serverSocket.Close();		
    //aDlg->GetDlgItemText(IDC_EDIT_LOG, strText);		
    //strText += "Have Close!";		
    //aDlg->SetDlgItemText(IDC_EDIT_LOG, strText);		
    return 0;		
}
BOOL CtetrisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CtetrisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CtetrisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}
void CtetrisView::OnTimer(UINT_PTR nIDEvent)
{
    int next = gameBoard->updatePos(DOWN);
    gameBoard->m_originPos;
    for(int i=0;i<gameBoard->m_curTile->getNumOfPos();i++)
    {
        gameBoard->m_curTile->m_position[i]->x;
        gameBoard->m_curTile->m_position[i]->y;
    }
    if(next ==KEEPGOING)
    {
        CClientDC dc(this);
        gameBoard->drawBoard(HDC(dc));
    }
    if(next == REACHEDBOTTOM)
    {


        CClientDC dc(this);
        gameBoard->eliminateLine(HDC(dc));
        delete gameBoard->m_curTile;
        gameBoard->addTile();
    }
    else if(next == GAMEOVER)
    {
        CClientDC dc(this);
        gameBoard->gameOver(HDC(dc),m_hWnd);
    }
    //CMDIFrameWnd::OnTimer(nIDEvent);
}
void CtetrisView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if(nChar==VK_LEFT)
    {
        int next = gameBoard->updatePos(LEFT);
        if(next ==KEEPGOING)
        {
            CClientDC dc(this);
            gameBoard->drawBoard(HDC(dc));
        }
    }
    else if(nChar==VK_RIGHT)
    {
        int next = gameBoard->updatePos(RIGHT);
        if(next ==KEEPGOING)
        {
            CClientDC dc(this);
            gameBoard->drawBoard(HDC(dc));
        }
    }
    else if(nChar==VK_DOWN)
    {
        int next = gameBoard->updatePos(DOWN);
        gameBoard->m_originPos;
        for(int i=0;i<gameBoard->m_curTile->getNumOfPos();i++)
        {
            gameBoard->m_curTile->m_position[i]->x;
            gameBoard->m_curTile->m_position[i]->y;
        }
        if(next ==KEEPGOING)
        {
            CClientDC dc(this);
            gameBoard->drawBoard(HDC(dc));
        }
         if(next == REACHEDBOTTOM)
        {
            
            
            CClientDC dc(this);
            gameBoard->eliminateLine(HDC(dc));
            delete gameBoard->m_curTile;
            gameBoard->addTile();
        }
        else if(next == GAMEOVER)
        {
            CClientDC dc(this);
            gameBoard->gameOver(HDC(dc),m_hWnd);
        }
    }
    else if(nChar==VK_UP)
    {
        coord **oldpts = gameBoard->getPositions();
        gameBoard->m_curTile->rotateRight();
        coord **newpts = gameBoard->getPositions();
        BOOL flag = TRUE;
        for(int i=0;i<4;i++)
        {
            if(0>newpts[i]->x||newpts[i]->x>9||newpts[i]->y>=23)
            {
                flag= FALSE;
                break;
            }
            BOOL flag2 = TRUE;
            for(int j=0;j<4;j++)
            {
                if(newpts[i]->x==oldpts[j]->x && newpts[i]->y==oldpts[j]->y)
                {
                    flag2 = FALSE;
                }
            }
            if(flag2 && gameBoard->m_colorMatrix[newpts[i]->x][newpts[i]->y]!=L_GREY)
            {
                flag = FALSE;
                break;
            }
        }
        if(flag)
        {
            for(int i=0;i<4;i++)
            {
                gameBoard->m_colorMatrix[oldpts[i]->x][oldpts[i]->y]=L_GREY;
                gameBoard->m_changedCol[i]->x = oldpts[i]->x;		                
                gameBoard->m_changedCol[i]->y = oldpts[i]->y;
            }
            for(int i=0;i<4;i++){
                gameBoard->m_colorMatrix[newpts[i]->x][newpts[i]->y]= gameBoard->m_curTile->getColor();
                gameBoard->m_changedCol[i+4]->x = newpts[i]->x;		
                gameBoard->m_changedCol[i+4]->y = newpts[i]->y;
            }
            
            CClientDC dc(this);
            gameBoard->drawBoard(HDC(dc));
        }
        if(!flag)
        {
            gameBoard->m_curTile->rotateLeft();
        }
        for(int i=0;i<4;i++)
        {
            delete oldpts[i];
            delete newpts[i];
        }
        delete[] oldpts;
        delete[] newpts;
        /*gameBoard->m_colorMatrix[gameBoard->m_originPos->x][gameBoard->m_originPos->y] = L_GREY;
        
        gameBoard->m_colorMatrix[gameBoard->m_originPos->x + gameBoard->m_curTile->m_position[0]->x]
        [gameBoard->m_originPos->y + gameBoard->m_curTile->m_position[0]->y] = L_GREY;

        gameBoard->m_colorMatrix[gameBoard->m_originPos->x + gameBoard->m_curTile->m_position[1]->x]
        [gameBoard->m_originPos->y + gameBoard->m_curTile->m_position[1]->y] = L_GREY;

        gameBoard->m_colorMatrix[gameBoard->m_originPos->x + gameBoard->m_curTile->m_position[2]->x]
        [gameBoard->m_originPos->y + gameBoard->m_curTile->m_position[2]->y] = L_GREY;

        gameBoard->m_curTile->rotateRight();*/
        /*BOOL flag = TRUE;
        if(gameBoard->m_colorMatrix[gameBoard->m_originPos->x][gameBoard->m_originPos->y]!=L_GREY) {
            flag = FALSE;
        }
        if(gameBoard->m_colorMatrix[gameBoard->m_originPos->x + gameBoard->m_curTile->m_position[0]->x]
        [gameBoard->m_originPos->y + gameBoard->m_curTile->m_position[0]->y]!=L_GREY)
        {
            flag = FALSE;
        }
        if (gameBoard->m_colorMatrix[gameBoard->m_originPos->x + gameBoard->m_curTile->m_position[1]->x]
        [gameBoard->m_originPos->y + gameBoard->m_curTile->m_position[1]->y]!=L_GREY)
        {
            flag = FALSE;
        }
        if (gameBoard->m_colorMatrix[gameBoard->m_originPos->x + gameBoard->m_curTile->m_position[2]->x]
        [gameBoard->m_originPos->y + gameBoard->m_curTile->m_position[2]->y]!=L_GREY)
        {
            flag = FALSE;
        }*/
        /*if(flag = FALSE)
        {
            gameBoard->m_curTile->rotateLeft();
        }*/
        //gameBoard->m_colorMatrix[gameBoard->m_originPos->x][gameBoard->m_originPos->y] = gameBoard->m_curTile->getColor();
        //gameBoard->m_colorMatrix[gameBoard->m_originPos->x+gameBoard->m_curTile->m_position[0]->x][gameBoard->m_originPos->y+gameBoard->m_curTile->m_position[0]->y] = gameBoard->m_curTile->getColor();
        //gameBoard->m_colorMatrix[gameBoard->m_originPos->x+gameBoard->m_curTile->m_position[1]->x][gameBoard->m_originPos->y+gameBoard->m_curTile->m_position[1]->y] = gameBoard->m_curTile->getColor();
        //gameBoard->m_colorMatrix[gameBoard->m_originPos->x+gameBoard->m_curTile->m_position[2]->x][gameBoard->m_originPos->y+gameBoard->m_curTile->m_position[2]->y] = gameBoard->m_curTile->getColor();
    }
}

// CtetrisView diagnostics

#ifdef _DEBUG
void CtetrisView::AssertValid() const
{
	CView::AssertValid();
}

void CtetrisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtetrisDoc* CtetrisView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtetrisDoc)));
	return (CtetrisDoc*)m_pDocument;
}
#endif //_DEBUG


// CtetrisView message handlers
