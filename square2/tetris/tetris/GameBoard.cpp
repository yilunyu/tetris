#include "stdafx.h"
#include "GameBoard.h"
#include <afx.h>
#include <afxsock.h>  		
#include <afxwin.h>		
#include <vector>		
using namespace std;		



 KGameBoard::KGameBoard() 
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<23;j++)
        {
            m_colorMatrix[i][j] = L_GREY;
            m_colorMatrix2[i][j] = L_GREY;
        }
    }
    for(int i=0;i<8;i++)		
    {		
        m_changedCol[i] = new coord;		
    }		

    m_originPos = new coord;
}
void KGameBoard::addTile(){
    srand(time(NULL));
    int r = rand();
    int iSecret = r % 7;
    switch(iSecret){
        case 0:
        m_curTile = new KITile(2);
        
        //ITile
        break;
        case 1:
        m_curTile = new KJTile(4);
        //JTile
        break;
        case 2:
        m_curTile = new KLTile(4);

        //LTile
        break;
        case 3:
        m_curTile = new KOTile(1);
        //OTile
        break;
        case 4:
        m_curTile = new KZTile(2);
        //ZTile
        break;
        case 5:
        m_curTile = new KTTile(4);
        //TTile
        break;
        case 6:
        m_curTile = new KSTile(2);
        //STile
        break;
    }
    //m_curTile = new KLTile(4);
    m_originPos->x = 3;
    m_originPos->y = 1;
    updatePos(DOWN);
}
coord** KGameBoard::getYPos(coord** pts)
{
    coord * temp;
    for(int i=0;i<4;i++)
    {   
        for(int j=i+1;j<4;j++)
        {
            if(pts[j]->x>pts[i]->x)
            {
                temp = pts[i];
                pts[i] = pts[j];
                pts[j] = temp;
            }
        }
    }
    //int m = pts[0]->x;
    coord ** ypos;
    ypos = new coord* [4];
    for(int i=0;i<4;i++)
    {
        ypos[i]=NULL;
    }
    int index = 0;
    ypos[0] = pts[0];
    for(int i=1;i<4;i++)
    {
        if(pts[i]->x==ypos[index]->x)
        {
            if(pts[i]->y>ypos[index]->y) ypos[index] = pts[i];
            
        }
        else
        {
            index++;
            ypos[index] = pts[i];
        }
    }
    return ypos;
}
coord** KGameBoard::getXPos(int dir,coord** pts)
{
   
    coord * temp;
    for(int i=0;i<4;i++)
    {    for(int j=i+1;j<4;j++)
         {
            if(pts[j]->y>pts[i]->y)
            {
                temp = pts[i];
                pts[i] = pts[j];
                pts[j] = temp;
            }
        }
    }
    //int m = pts[0]->x;
    coord ** xpos;
    xpos = new coord* [4];
    for(int i=0;i<4;i++)
    {
        xpos[i] = NULL;
    }
    int index = 0;
    xpos[0]= pts[0];
    if(dir==RIGHT)
    {
        for(int i=1;i<4;i++)
        {
            if(pts[i]->y==pts[i-1]->y)
            {
                if(pts[i]->x>xpos[index]->x)
                {
                    xpos[index] = pts[i];
                }
                
            }
            else
            {
                index++;
                xpos[index] = pts[i];
            }
        }
    }
    
    else
    {
        for(int i=1;i<4;i++)
        {
            if(pts[i]->y==pts[i-1]->y)
            {
                if(pts[i]->x<xpos[index]->x)
                {
                    xpos[index] = pts[i];
                }

            }
            else
            {
                index++;
                xpos[index] = pts[i];
            }
        }
    }
    return xpos;
}
BOOL KGameBoard::checkSpace(coord **pts,int dir)
{
    BOOL res = TRUE;
    for(int i=0;i<4;i++)
    {
        BOOL flg = TRUE;
        for(int j=0;j<4;j++)
        {
            if(dir == DOWN)
            {
                if(pts[i]->x==pts[j]->x&&pts[i]->y==pts[j]->y-1)
                {
                    flg = FALSE;
                }
            }
            else if(dir == LEFT)
            {
                if(pts[i]->x==pts[j]->x+1&&pts[i]->y==pts[j]->y)
                {
                    flg = FALSE;
                }
            }
            else if(dir == RIGHT)
            {
                if(pts[i]->x==pts[j]->x-1&&pts[i]->y==pts[j]->y)
                {
                    flg = FALSE;
                }
            }
        }
        if(flg && m_colorMatrix[pts[i]->x][pts[i]->y]!=L_GREY)
        {
            res = FALSE;
            return res;
        }
    }
    return res;
}
int KGameBoard::updatePos(int dir)
{
    if(dir == RIGHT)
    {
        
        coord ** pts;
        pts = new coord* [4];
        for(int i=0;i<4 ;i++)
        {   
            pts[i] = new coord;
        }
        pts[0]->x = m_originPos->x+1;
        pts[1]->x = m_originPos->x+1+m_curTile->m_position[0]->x;
        pts[2]->x = m_originPos->x+1+m_curTile->m_position[1]->x;
        pts[3]->x = m_originPos->x+1+m_curTile->m_position[2]->x;
        pts[0]->y = m_originPos->y;
        pts[1]->y = m_originPos->y+m_curTile->m_position[0]->y;
        pts[2]->y = m_originPos->y+m_curTile->m_position[1]->y;
        pts[3]->y = m_originPos->y+m_curTile->m_position[2]->y;
        
        
        if(pts[0]->x<=9 && pts[1]->x<=9 &&pts[2]->x<=9 && pts[3]->x<=9)
        {
            BOOL space= checkSpace(pts,RIGHT);
            /*for(int i=0;i<4;i++)
            {
                if(xpos[i]!=NULL)
                {
                    if(m_colorMatrix[xpos[i]->x][xpos[i]->y]!=L_GREY)
                    {
                        space = false;
                    }
                }
            }*/
            if(space)
            {
                m_colorMatrix[pts[0]->x-1][pts[0]->y] = L_GREY;
                m_colorMatrix[pts[1]->x-1][pts[1]->y] = L_GREY;
                m_colorMatrix[pts[2]->x-1][pts[2]->y] = L_GREY;
                m_colorMatrix[pts[3]->x-1][pts[3]->y] = L_GREY;
                m_colorMatrix[pts[0]->x][pts[0]->y] = m_curTile->getColor();
                m_colorMatrix[pts[1]->x][pts[1]->y] = m_curTile->getColor();
                m_colorMatrix[pts[2]->x][pts[2]->y] = m_curTile->getColor();
                m_colorMatrix[pts[3]->x][pts[3]->y] = m_curTile->getColor();
                m_originPos->x++;
                for(int i=0;i<4;i++)		
                {		
                    m_changedCol[i]->x = pts[i]->x-1;		
                    m_changedCol[i]->y = pts[i]->y;		
                }		
                for(int i=4;i<8;i++)		
                {		
                    m_changedCol[i]->x = pts[i-4]->x;		
                    m_changedCol[i]->y = pts[i-4]->y;		
                }
                for(int x=0;x<4;x++)
                {
                    delete pts[x];
                }
                delete[] pts;
                return KEEPGOING;
            }
            /*if(m_colorMatrix[pts[0]->x][newy0]==L_GREY && m_colorMatrix[pts[1]->x][newy1]==L_GREY
                &&m_colorMatrix[newx2][newy2]==L_GREY && m_colorMatrix[newx3][newy3] == L_GREY)
            {
                m_colorMatrix[pts[0]->x-1][newy0] = L_GREY;
                m_colorMatrix[pts[1]->x-1][newy1] = L_GREY;
                m_colorMatrix[newx2-1][newy2] = L_GREY;
                m_colorMatrix[newx3-1][newy3] = L_GREY;
                m_colorMatrix[pts[0]->x][newy0] = m_curTile->m_color;
                m_colorMatrix[pts[1]->x][newy1] = m_curTile->m_color;
                m_colorMatrix[newx2][newy2] = m_curTile->m_color;
                m_colorMatrix[newx3][newy3] = m_curTile->m_color;
            }*/
            
        }
        for(int i=0;i<4;i++)
        {
            delete pts[i];
        }
        delete[] pts;
        //m_originPos->x++;
        return REACHEDBOTTOM;
    }
    else if(dir == LEFT)
    {
        coord ** pts;
        pts = new coord* [4];
        for(int i=0;i<4 ;i++)
        {   
            pts[i] = new coord;
        }
        pts[0]->x = m_originPos->x-1;
        pts[1]->x = m_originPos->x-1+m_curTile->m_position[0]->x;
        pts[2]->x = m_originPos->x-1+m_curTile->m_position[1]->x;
        pts[3]->x = m_originPos->x-1+m_curTile->m_position[2]->x;
        pts[0]->y = m_originPos->y;
        pts[1]->y = m_originPos->y+m_curTile->m_position[0]->y;
        pts[2]->y = m_originPos->y+m_curTile->m_position[1]->y;
        pts[3]->y = m_originPos->y+m_curTile->m_position[2]->y;
        
        
        if(pts[0]->x>=0 && pts[1]->x>=0 &&pts[2]->x>=0 && pts[3]->x>=0)
        {
            BOOL space = checkSpace(pts,LEFT);
            /*for(int i=0;i<4;i++)
            {
                if(xpos[i]!=NULL)
                {
                    if(m_colorMatrix[xpos[i]->x][xpos[i]->y]!=L_GREY)
                    {
                        space = false;
                    }
                }
            }*/
            if(space)
            {
                m_colorMatrix[pts[0]->x+1][pts[0]->y] = L_GREY;
                m_colorMatrix[pts[1]->x+1][pts[1]->y] = L_GREY;
                m_colorMatrix[pts[2]->x+1][pts[2]->y] = L_GREY;
                m_colorMatrix[pts[3]->x+1][pts[3]->y] = L_GREY;
                m_colorMatrix[pts[0]->x][pts[0]->y] = m_curTile->getColor();
                m_colorMatrix[pts[1]->x][pts[1]->y] = m_curTile->getColor();
                m_colorMatrix[pts[2]->x][pts[2]->y] = m_curTile->getColor();
                m_colorMatrix[pts[3]->x][pts[3]->y] = m_curTile->getColor();
                m_originPos->x--;
                for(int i=0;i<4;i++)		
                {		
                    m_changedCol[i]->x = pts[i]->x+1;		
                    m_changedCol[i]->y = pts[i]->y;		
                }		
                for(int i=4;i<8;i++)		
                {		
                    m_changedCol[i]->x = pts[i-4]->x;		
                    m_changedCol[i]->y = pts[i-4]->y;		
                }
                for(int x=0;x<4;x++)
                {
                    delete pts[x];
                }
                delete[] pts;
                return KEEPGOING;
            }
        }
        for(int i=0;i<4;i++)
        {
            delete pts[i];
        }
        delete[] pts;
        //m_originPos->x--;
        return REACHEDBOTTOM;
    }
    else if(dir == DOWN)
    {
        coord ** pts;
        pts = new coord* [4];
        for(int i=0;i<4 ;i++)
        {   
            pts[i] = new coord;
        }
        pts[0]->x = m_originPos->x;
        pts[1]->x = m_originPos->x+m_curTile->m_position[0]->x;
        pts[2]->x = m_originPos->x+m_curTile->m_position[1]->x;
        pts[3]->x = m_originPos->x+m_curTile->m_position[2]->x;
        pts[0]->y = m_originPos->y+1;
        pts[1]->y = m_originPos->y+1+m_curTile->m_position[0]->y;
        pts[2]->y = m_originPos->y+1+m_curTile->m_position[1]->y;
        pts[3]->y = m_originPos->y+1+m_curTile->m_position[2]->y;
        //coord ** ypos = getYPos(pts);
        
        if(pts[0]->y<23 && pts[1]->y<23 &&pts[2]->y<23 && pts[3]->y<23)
        {
            BOOL space = checkSpace(pts,DOWN);
            if(space)
            {
                m_colorMatrix[pts[0]->x][pts[0]->y-1] = L_GREY;
                m_colorMatrix[pts[1]->x][pts[1]->y-1] = L_GREY;
                m_colorMatrix[pts[2]->x][pts[2]->y-1] = L_GREY;
                m_colorMatrix[pts[3]->x][pts[3]->y-1] = L_GREY;
                m_colorMatrix[pts[0]->x][pts[0]->y] = m_curTile->getColor();
                m_colorMatrix[pts[1]->x][pts[1]->y] = m_curTile->getColor();
                m_colorMatrix[pts[2]->x][pts[2]->y] = m_curTile->getColor();
                m_colorMatrix[pts[3]->x][pts[3]->y] = m_curTile->getColor();
                m_originPos->y++;
                for(int i=0;i<4;i++)		
                {		
                    m_changedCol[i]->x = pts[i]->x;		
                    m_changedCol[i]->y = pts[i]->y-1;		
                }		
                for(int i=4;i<8;i++)		
                {		
                    m_changedCol[i]->x = pts[i-4]->x;		
                    m_changedCol[i]->y = pts[i-4]->y;		
                }
                for(int x=0;x<4;x++)
                {
                    delete pts[x];
                }
                delete[] pts;
            /*    int countx=0;
                int county=0;
                for(int i=0;i<10;i++)
                {
                    for(int j=0;j<23;j++)
                    {

                        if(m_colorMatrix[i][j]!=L_GREY)
                        {
                            countx++;
                            county++;
                        }
                    }
                }*/
                return KEEPGOING;
            }
            else if(pts[0]->y-1<3||pts[1]->y-1<3||pts[2]->y-1<3||pts[3]->y-1<3)
            {
                for(int x=0;x<4;x++)
                {
                    delete pts[x];
                }
                delete[] pts;
                return GAMEOVER;
            }
        }
        for(int x=0;x<4;x++)
        {
            delete pts[x];
        }
        delete[] pts;
        //m_originPos->y++;
        return REACHEDBOTTOM;
    /////*    BOOL flag;
    ////    flag = TRUE;
    ////    if(0<=newy0 && newy0<20)
    ////    {
    ////        if(m_colorMatrix[newx0][newy0]==L_GREY)
    ////        {
    ////            if(newy0-1<20)
    ////            {
    ////                m_colorMatrix[newx0][newy0-1] = L_GREY;
    ////                
    ////            }
    ////            m_colorMatrix[newx0][newy0] = m_curTile->m_color;
    ////            flag = TRUE;
    ////        }
    ////    }
    ////    if(0<=newy0&&newy0<=9 && 0<=newy1 && newy1<=9 && 0<=newy2 &&newy2<=9 &&
    ////        0<=newy3 &&newy3<=9)
    ////    {
    ////        if(m_colorMatrix[newx0][newy0]==L_GREY && m_colorMatrix[newx1][newy1]==L_GREY
    ////            &&m_colorMatrix[newx2][newy2]==L_GREY && m_colorMatrix[newx3][newy3] == L_GREY)
    ////        {
    ////           if(newy0-1>=0) m_colorMatrix[newx0][newy0-1] = L_GREY;
    ////           if(newy1-1>=0) m_colorMatrix[newx1][newy1-1] = L_GREY;
    ////           if(newy2-1>=0) m_colorMatrix[newx2][newy2-1] = L_GREY;
    ////           if(newy3-1>=0) m_colorMatrix[newx3][newy3-1] = L_GREY;
    ////            m_colorMatrix[newx0][newy0] = m_curTile->m_color;
    ////            m_colorMatrix[newx1][newy1] = m_curTile->m_color;
    ////            m_colorMatrix[newx2][newy2] = m_curTile->m_color;
    ////            m_colorMatrix[newx3][newy3] = m_curTile->m_color;
    ////            return KEEPGOING;
    ////        }
    ////        return REACHEDBOTTOM;
    ////    }*/
    }
    return REACHEDBOTTOM;
}
coord** KGameBoard::getPositions()
{
    coord ** pts;
    pts = new coord* [4];
    for(int i=0;i<4 ;i++)
    {   
        pts[i] = new coord;
    }
    pts[0]->x = m_originPos->x;
    pts[1]->x = m_originPos->x+m_curTile->m_position[0]->x;
    pts[2]->x = m_originPos->x+m_curTile->m_position[1]->x;
    pts[3]->x = m_originPos->x+m_curTile->m_position[2]->x;
    pts[0]->y = m_originPos->y;
    pts[1]->y = m_originPos->y+m_curTile->m_position[0]->y;
    pts[2]->y = m_originPos->y+m_curTile->m_position[1]->y;
    pts[3]->y = m_originPos->y+m_curTile->m_position[2]->y;
    return pts;
}
void KGameBoard::client(HDC hdc,CtetrisView* v)		
{		
    AfxSocketInit();		
    		
    CString strIP = _T("localhost");		
    CString port = _T("8080");		
    //CString strText = _T("Hallo Abdo");		
    CStringA strPort(port);		
    CSocket aSocket;
    //this->GetDlgItem(IDC_EDIT_IP)->GetWindowText(strIP);		
    //this->GetDlgItem(IDC_EDIT_PORT)->GetWindowText(strPort);		
    //this->GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(strText);		
    //初始化 CSocket 对象, 因为客户端不需要绑定任何端口和地址, 所以用默认参数即可		
    		
    if(!aSocket.Create())		
    {		
        char szMsg[1024] = {0};		
        sprintf(szMsg, "create faild: %d", aSocket.GetLastError());		
        AfxMessageBox((CString)szMsg);		
        return;		
    }		
    //转换需要连接的端口内容类型		
    int nPort = atoi((const char*)strPort);		
    //连接指定的地址和端口		
    if(aSocket.Connect(strIP, nPort))		
    {		
        //CWinThread* pThread = new CWinThread(fromServer, (LPVOID)v);		
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
            strData.AppendFormat("%d",m_changedCol[i]->x);		
            strData.Append(",");		
            strData.AppendFormat("%d",m_changedCol[i]->y);		
            strData.Append(",");		
        }		
       // strData.Append(".");		
        for(int i=4;i<8;i++)		
        {		
            strData.AppendFormat("%d",m_changedCol[i]->x);		
            strData.Append(",");		
            strData.AppendFormat("%d",m_changedCol[i]->y);		
            strData.Append(",");		
        }		
        strData.AppendFormat("%lu",m_curTile->getColor());		
        char szRecValue[1024] = {0};		
        aSocket.Send(strData, strData.GetLength()); //发送内容给服务器		
        aSocket.Receive((void *)szRecValue, 1024); //接收服务器发送回来的内容(该方法会阻塞, 在此等待有内容接收到才继续向下执行)		
        //AfxMessageBox((CString)szRecValue);		
        		
        vector<string> result;		
        char* p = szRecValue;		
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
            m_colorMatrix2[xint][yint] = L_GREY;		
        }		
        unsigned int tColor = strtoul(result[16].c_str(),NULL,10);		
        for(int i=8;i<16; i=i+2)		
        {		
            string x = result[i];		
            string y = result[i+1];		
            int xint = atoi(x.c_str());		
            int yint = atoi(y.c_str());		
            m_colorMatrix2[xint][yint] = (COLORREF)tColor;		
        }		
        		
        
        drawBoard(hdc);		
        firstClient = FALSE;		
        //delete[] m_colorMatrix2;		
       // m_colorMatrix2;		
    }		
    else		
    {		
        char szMsg[1024] = {0};		
        sprintf(szMsg, "create faild: %d", aSocket.GetLastError());		
        AfxMessageBox((CString)szMsg);		
    }		
   
    
   // aSocket.Close();		
}
void KGameBoard::eliminateLine(HDC hdc)
{
    coord ** pts=getPositions();
    /*coord * temp;
    for(int i=0;i<4;i++)
    {    for(int j=i+1;j<4;j++)
        {
            if(pts[j]->y>pts[i]->y)
            {
                temp = pts[i];
                pts[i] = pts[j];
                pts[j] = temp;
            }
        }
    }
    coord ** xpos;
    xpos = new coord* [4];
    for(int i=0;i<4;i++)
    {
        xpos[i] = NULL;
    }
    int index = 0;
    xpos[0]= pts[0];
    for(int i=1;i<4;i++)
    {
        if(pts[i]->y==pts[i-1]->y)
        {
            if(pts[i]->x>xpos[index]->x)
            {
                xpos[index] = pts[i];
            }

        }
        else
        {
            index++;
            xpos[index] = pts[i];
        }
    }*/
    int t=0;
    int maxline=-1;
    int index = 0;
    int* clearedlines = new int [4];
    for(int i=0;i<4;i++)
    {
        clearedlines[i] = -1;
    }
    while(t<4)
    {
        BOOL flg = TRUE;
        for(int x=0;x<10;x++)
        {
            if(m_colorMatrix[x][pts[t]->y]==L_GREY)
            {
                flg = FALSE;
                break;
            }
        }
        if(flg)
        {
            for(int x=0;x<10;x++)
            {
                m_colorMatrix[x][pts[t]->y]=L_GREY;
                //might have to clear everything there is a bug!!!!!
            }
            clearedlines[index] = pts[t]->y;
            index++;
            maxline = max(maxline,pts[t]->y);
        }
        t++;
    }
    if(maxline!=-1){
        int curline = maxline-1;
        int destline = maxline;
        while(curline>=3)
        {
            BOOL flag = TRUE;
            for(int j = 0;j<4;j++)
            {
                if(curline==clearedlines[j])    flag = FALSE;
            }
            if(flag)
            {
                for(int x=0;x<10;x++)
                {
                    m_colorMatrix[x][destline] = m_colorMatrix[x][curline];
                }
                curline--;
                destline--;
            }
            else
            {
                curline--;
            }
        }
    }
    //draw here

    for(int x=0;x<4;x++)
    {
        delete pts[x];
    }
    delete[] pts;
}
void KGameBoard::drawBoard(HDC hdc){
    //after every move and after init
    //addTile();
    // 
     HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP bitmap = CreateCompatibleBitmap(hdc,730,640);
    SelectObject(memDC,bitmap);
/*    Rectangle(memDC,0,0,330,640);*/

//     HBRUSH hBrush2 = CreateSolidBrush(RGB(255, 0,0));  
//     HBRUSH b = (HBRUSH)SelectObject(memDC,hBrush2);

//     Ellipse(memDC,5,5,45,45);//用笔刷画实心圆 ;

//     BitBlt(hdc,0,0,330,640,memDC,0,0,SRCCOPY);
//     return ;
    // Rectangle(hdc,30,0,400,600);
//     HDC memDC = CreateCompatibleDC(hdc);
//     HBITMAP bitmap = CreateCompatibleBitmap(memDC,330,640);
//     SelectObject(memDC,bitmap);
    Rectangle(memDC,0,0,730,640);		
    Rectangle(memDC,0,0,330,640);		    
    Rectangle(memDC,400,0,730,640);
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<20;j++)
        {
            if(m_colorMatrix[i][j+3]==L_GREY)
            { 
                HBRUSH b = (HBRUSH)SelectObject(memDC,GetStockObject(GRAY_BRUSH));
                 Rectangle(memDC,10+i+SQUAREWIDTH*i,10+j+SQUAREWIDTH*(j),10+i+SQUAREWIDTH*(i+1),10+j+SQUAREWIDTH*(j+1));
                SelectObject(memDC,b);
            }
            else{
                //HBRUSH tBrush = CreateSolidBrush(RGB(255,255,255));
                /*HBRUSH b = (HBRUSH)SelectObject(memDC,GetStockObject(WHITE_BRUSH));
                COLORREF c = RGB(0,255,255);
                COLORREF  d = SetDCBrushColor(memDC, c);*/

                HBRUSH hBrush2 = CreateSolidBrush(m_colorMatrix[i][j+3]);  
                HBRUSH b = (HBRUSH)SelectObject(memDC,hBrush2);

               // Ellipse(memDC,5,5,45,45);//用笔刷画实心圆 ;
                 Rectangle(memDC,10+i+SQUAREWIDTH*i,10+j+SQUAREWIDTH*(j),10+i+SQUAREWIDTH*(i+1),10+j+SQUAREWIDTH*(j+1));
                 SelectObject(memDC,b);
                 DeleteObject(hBrush2);
                //DeleteObject(tBrush);
            }
            
            HBRUSH hbrush = CreateSolidBrush(m_colorMatrix2[i][j+3]);		            
            HBRUSH bru = (HBRUSH)SelectObject(memDC,hbrush);		
            Rectangle(memDC,410+i+SQUAREWIDTH*i,10+j+SQUAREWIDTH*(j),410+i+SQUAREWIDTH*(i+1),10+j+SQUAREWIDTH*(j+1));		
            SelectObject(memDC,bru);		
            DeleteObject(hbrush);
            
            //Rectangle(memDC,10+i+SQUAREWIDTH*i,10+j+SQUAREWIDTH*(j),10+i+SQUAREWIDTH*(i+1),10+j+SQUAREWIDTH*(j+1));
            ////SelectObject(memDC,oldBrush);
            //DeleteObject(tBrush);
        }
    }
    BitBlt(hdc,0,0,730,640,memDC,0,0,SRCCOPY);
    DeleteDC(memDC);
    DeleteObject(bitmap);
    ////for(int x=0;x<4;x++)
    ////{    for(int y=0;y<4;y++)
    ////{  RECT temp;
    ////temp.left = m_xstart[x]+1;
    ////temp.right = m_xend[x]-1;
    ////temp.top = m_ystart[y]+1;
    ////temp.bottom = m_yend[y]-1;
    ////if(m_newpos[x][y]==0||m_newpos[x][y]==m_oldpos[x][y])
    ////{


    ////    //if((m_oldpos[x][y]==0||m_oldpos[x][y]==m_newpos[x][y]))

    ////    drawRect(hdc,&temp,x,y,false);
    ////    if(m_board[x][y].val!=0){
    ////        CString pointsInStr;
    ////        pointsInStr.Format(TEXT("%d"),m_board[x][y].val);
    ////        TextOut(hdc,m_xstart[x]+37,m_ystart[y]+60,pointsInStr, pointsInStr.GetLength());
    ////    }
    ////}
    ////else if(m_oldpos[x][y]==0)  FillRect(hdc, &temp, (HBRUSH)GetStockObject(GRAY_BRUSH));
    ////}
    ////}
    //////::SetTimer(hWnd, 1, 100, TimerProc);
    ////for(int i=0;i<4;i++)
    ////{
    ////    for(int j=0;j<4;j++)
    ////    {
    ////        if(!(m_newpos[i][j]==0||m_oldpos[i][j]==m_newpos[i][j]))
    ////        {
    ////            RECT temp;
    ////            int disp=0;

    ////            switch (m_hov)
    ////            {   case 1:
    ////            if(i<=2&&m_oldpos[i+1][j]==m_newpos[i][j])    disp=1;
    ////            if(i<=1&&m_oldpos[i+2][j]==m_newpos[i][j])    disp=2;
    ////            if(i<=0&&m_oldpos[i+3][j]==m_newpos[i][j])    disp=3;
    ////            temp.left = m_xstart[i+disp]+1-m_offset*SPEED*(disp);
    ////            temp.right = m_xend[i+disp]-1-m_offset*SPEED*(disp);
    ////            temp.top=m_ystart[j]+1;
    ////            temp.bottom=m_yend[j]-1;
    ////            if(m_oldboard[i+disp][j]==m_board[i][j].val)  drawRect(hdc,&temp,i,j,false);
    ////            else if(!m_lastcall) drawRect(hdc,&temp,i+disp,j,true);
    ////            else drawRect(hdc,&temp,i,j,false);
    ////            break;
    ////            case 2:
    ////                if(j<=2&&m_oldpos[i][j+1]==m_newpos[i][j])    disp=1;
    ////                if(j<=1&&m_oldpos[i][j+2]==m_newpos[i][j])    disp=2;
    ////                if(j<=0&&m_oldpos[i][j+3]==m_newpos[i][j])    disp=3;
    ////                temp.left = m_xstart[i]+1;
    ////                temp.right = m_xend[i]-1;
    ////                temp.top = m_ystart[j+disp]+1-m_offset*SPEED*(disp);
    ////                temp.bottom = m_yend[j+disp]-1-m_offset*SPEED*(disp);
    ////                if(m_oldboard[i][j+disp]==m_board[i][j].val)  drawRect(hdc,&temp,i,j,false);
    ////                else if(!m_lastcall) drawRect(hdc,&temp,i,j+disp,true);
    ////                else drawRect(hdc,&temp,i,j,false);
    ////                break;
    ////            case 3:
    ////                if(i>=1&&m_oldpos[i-1][j]==m_newpos[i][j])    disp=1;
    ////                if(i>=2&&m_oldpos[i-2][j]==m_newpos[i][j])    disp=2;
    ////                if(i>=3&&m_oldpos[i-3][j]==m_newpos[i][j])    disp=3;
    ////                temp.left = m_xstart[i-disp]+1+m_offset*SPEED*(disp);
    ////                temp.right = m_xend[i-disp]-1+m_offset*SPEED*(disp);
    ////                temp.top=m_ystart[j]+1;
    ////                temp.bottom=m_yend[j]-1;
    ////                if(m_oldboard[i-disp][j]==m_board[i][j].val)  drawRect(hdc,&temp,i,j,false);
    ////                else if(!m_lastcall) drawRect(hdc,&temp,i-disp,j,true);
    ////                else drawRect(hdc,&temp,i,j,false);
    ////                break;
    ////            case 4:
    ////                if(j>=1&&m_oldpos[i][j-1]==m_newpos[i][j])    disp=1;
    ////                if(j>=2&&m_oldpos[i][j-2]==m_newpos[i][j])    disp=2;
    ////                if(j>=3&&m_oldpos[i][j-3]==m_newpos[i][j])    disp=3;
    ////                temp.left = m_xstart[i]+1;
    ////                temp.right = m_xend[i]-1;
    ////                temp.top = m_ystart[j-disp]+1+m_offset*SPEED*(disp);
    ////                temp.bottom = m_yend[j-disp]-1+m_offset*SPEED*(disp);
    ////                if(m_oldboard[i][j-disp]==m_board[i][j].val)  drawRect(hdc,&temp,i,j,false);
    ////                else if(!m_lastcall) drawRect(hdc,&temp,i,j-disp,true);
    ////                else drawRect(hdc,&temp,i,j,false);
    ////                break;
    ////            }    
    ////        }
    ////    }
    ////}
    // KillTimer(hWnd, 1);*/
}


void KGameBoard::gameOver(HDC hdc,HWND hWnd){
    SetBkMode(hdc,OPAQUE);
    RECT clientRect;
    GetClientRect(hWnd,&clientRect);
    FillRect(hdc,&clientRect,(HBRUSH)GetStockObject(LTGRAY_BRUSH));
    TextOut(hdc,clientRect.right/2,clientRect.bottom/2,TEXT("Game Over"),9);
    KillTimer(hWnd,m_nWindowTimer);
}





