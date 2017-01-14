// tetrisView.cpp : implementation of the CtetrisView class
//

#include "stdafx.h"
#include "tetris.h"
#include "Tile.h"
#include "tetrisDoc.h"
#include "tetrisView.h"
#include <winsock2.h> 		
#pragma comment(lib, "WS2_32.lib")		
#ifdef _DEBUG 		
#define new DEBUG_NEW 		
#endif		
UINT server_thd(LPVOID p); //声明线程函数 		
SOCKET listen_sock;//定义一个全局的监听soket 		
SOCKET sock;//定义一个soket 		
CString showeditmsg; //定义全局的显示消息的字符串
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
    }
	// TODO: add draw code for native data here
}


// CtetrisView printing

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
        gameBoard->client((HDC)dc,this);
    }
    if(next == REACHEDBOTTOM)
    {


        CClientDC dc(this);
        gameBoard->eliminateLine(HDC(dc));
        delete gameBoard->m_curTile;
        gameBoard->addTile();
        gameBoard->client((HDC)dc,this);
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
            gameBoard->client((HDC)dc,this);
        }
    }
    else if(nChar==VK_RIGHT)
    {
        int next = gameBoard->updatePos(RIGHT);
        if(next ==KEEPGOING)
        {
            CClientDC dc(this);
            gameBoard->drawBoard(HDC(dc));
            gameBoard->client((HDC)dc,this);
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
            gameBoard->client((HDC)dc,this);
        }
         if(next == REACHEDBOTTOM)
        {
            
            
            CClientDC dc(this);
            gameBoard->eliminateLine(HDC(dc));
            delete gameBoard->m_curTile;
            gameBoard->addTile();
            gameBoard->client((HDC)dc,this);
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
                gameBoard->m_changedCol[i+4]->x = newpts[i]->x;		
                gameBoard->m_changedCol[i+4]->y = newpts[i]->y;
            }
            for(int i=0;i<4;i++){
                gameBoard->m_colorMatrix[newpts[i]->x][newpts[i]->y]= gameBoard->m_curTile->getColor();
                gameBoard->m_changedCol[i+4]->x = newpts[i]->x;		
                gameBoard->m_changedCol[i+4]->y = newpts[i]->y;
            }
            
            CClientDC dc(this);
            gameBoard->drawBoard(HDC(dc));
            gameBoard->client((HDC)dc,this);
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
