#include "Tile.h"
#include "Resource.h"
#define GAMEOVER 0
#define REACHEDBOTTOM 1
#define KEEPGOING 2
#define SQUAREWIDTH  30
#define RIGHT 1
#define LEFT 2
#define DOWN 3
#define MOVEDOWN 1
#define L_GREY RGB(151,151,151)
#ifndef KGAMEBOARD_H
#define KGAMEBOARD_H

class KGameBoard 
{
public:
      COLORREF m_colorMatrix [10][23];
      COLORREF m_colorMatrix2 [10][23];		

      coord *m_changedCol [8];
      coord * m_originPos;
      KTile *m_curTile;
      UINT_PTR  m_nWindowTimer;
      // int m_offset;      //by how much tiles have moved since keydown
      // int m_hov;         //horizontal or vertical direction
      // bool m_moved;
      // int m_red[7];
      // int m_green[7];
      // int m_blue[7];
      // int m_oldboard[4][4];
      ///* std::vector<int> oldx;
      // std::vector<int> oldy;
      // std::vector<int> newx;
      // std::vector<int> newy;*/
      // int m_oldpos[4][4];
      // int m_newpos[4][4];
      // int m_count;
      // bool m_lastcall;    //if true, then we are drawing the last frame of the tile moving animation
      // KTile m_board[4][4];   
      // 
      // int m_xstart [4]; 
      // int m_xend[4];
      // int m_ystart[4];
      // int m_yend[4];
      //  //these four arrays define the x and y coordinates of the top-left and bottom right corners of
      // //all 16 tiles on the gameboard

      // int m_okay;
      // int m_score;
      // int m_oldrand;

public:
    KGameBoard();
     void moveLeft(int x,int y);
     void moveRight(int x,int y);
     void clearLine();
     void canMove();
       /*void gameOver(HDC hdc,HWND hWnd);*/
       /*bool canMove();*/
       void drawBoard(HDC hdc);
/*       void drawRect(HDC hdc, RECT *temp,int x,int y,bool sw);*/
//        void moveHori( int x, int y, int d );
//        void moveVert( int x, int y, int d );
//        void makeMove(int dir);
        void addTile();
        void gameOver(HDC hdc,HWND hWnd);
     int updatePos(int dir);
     coord** getXPos(int dir,coord** pts);
     coord** getYPos(coord** pts);
    // BOOL checkXSpace(coord **pts);
     BOOL checkSpace(coord **pts,int dir);
     void eliminateLine(HDC hdc);
     coord** getPositions();
     CWinThread *pThread;
     static unsigned int StartServer(LPVOID lParam);
     //        KGameBoard();
private:
       /*bool _testAdd(int x,int y,int v);*/
    
};

#endif
