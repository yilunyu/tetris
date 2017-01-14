#include "stdafx.h"

#include "Tile.h"

KTile::~KTile()
{
    for(int i=0;i<m_numOfPos;i++)
    {
        for(int j=0;j<3;j++)
        {
            delete m_pArrayPositions[i][j];
        }
        delete[] m_pArrayPositions[i];
    }
    delete[] m_pArrayPositions;
}
KTile::KTile (int numofp) {
    m_numOfPos = numofp;
    m_pArrayPositions = new coord** [m_numOfPos];
    for(int i=0;i<m_numOfPos;i++)   
    {
        m_pArrayPositions[i] = new coord* [3]; //occupy four- 1 squares 
        for(int j=0;j<3;j++)
        {
            m_pArrayPositions[i][j] = new coord; // each square has x,y coordinates
        }
    }
    m_curPos = 0;
    m_position = m_pArrayPositions[0];
}
KITile::KITile(int numofp): KTile(numofp) {
    //m_pArrayPositions = new coord* [m_numOfPos];
    //for(int i=0;i<m_numOfPos;i++)   
    //{
    //    m_pArrayPositions[i] = new coord[4]; //occupy four squares 
    //    for(int j=0;j<4;j++)
    //    {
    //        m_pArrayPositions[i][j] = new coord; // each square has x,y coordinates
    //    }
    //}
    //m_pArrayPositions[0][0]->x = 0;
    //m_pArrayPositions[0][0]->y = 0;

    
    m_pArrayPositions[0][0]->x = 0;
    m_pArrayPositions[0][0]->y = -1;
    m_pArrayPositions[0][1]->x = 0;
    m_pArrayPositions[0][1]->y = 1;
    m_pArrayPositions[0][2]->x = 0;
    m_pArrayPositions[0][2]->y = 2;
    //m_pArrayPositions[1][0]->x = 0;
    //m_pArrayPositions[1][0]->y = 0;
    m_pArrayPositions[1][0]->x = -1;
    m_pArrayPositions[1][0]->y = 0;
    m_pArrayPositions[1][1]->x = 1;
    m_pArrayPositions[1][1]->y = 0;
    m_pArrayPositions[1][2]->x = 2;
    m_pArrayPositions[1][2]->y = 0;
    m_color = RGB(0,0,255);
}
KJTile::KJTile(int numofp): KTile(numofp)
{
    //m_pArrayPositions = new coord* [m_numOfPos];
    //for(int i=0;i<m_numOfPos;i++)   
    //{
    //    m_pArrayPositions[i] = new coord[4]; //occupy four squares 
    //    for(int j=0;j<4;j++)
    //    {
    //        m_pArrayPositions[i][j] = new coord; // each square has x,y coordinates
    //    }
    //}
    //m_pArrayPositions[0][0]->x = 0;
    //m_pArrayPositions[0][0]->y = 0;
    //m_numOfPos = 4;
 /*   KTile::KTile();*/
    
    m_pArrayPositions[0][0]->x = 0;
    m_pArrayPositions[0][0]->y = -1;
    m_pArrayPositions[0][1]->x = 0;
    m_pArrayPositions[0][1]->y = 1;
    m_pArrayPositions[0][2]->x = -1;
    m_pArrayPositions[0][2]->y = 1;
    //m_pArrayPositions[1][1]->x = 0;
    //m_pArrayPositions[1][1]->y = 0;
    m_pArrayPositions[1][0]->x = 1;
    m_pArrayPositions[1][0]->y = 0;
    m_pArrayPositions[1][1]->x = -1;
    m_pArrayPositions[1][1]->y = 0;
    m_pArrayPositions[1][2]->x = -1;
    m_pArrayPositions[1][2]->y = -1;
    //m_pArrayPositions[2][0]->x = 0;
    //m_pArrayPositions[2][0]->y = 0;
    m_pArrayPositions[2][0]->x = 0;
    m_pArrayPositions[2][0]->y = 1;
    m_pArrayPositions[2][1]->x = 0;
    m_pArrayPositions[2][1]->y = -1;
    m_pArrayPositions[2][2]->x = 1;
    m_pArrayPositions[2][2]->y = -1;
    //m_pArrayPositions[3][0]->x = 0;
    //m_pArrayPositions[3][0]->y = 0;
    m_pArrayPositions[3][0]->x = -1;
    m_pArrayPositions[3][0]->y = 0;
    m_pArrayPositions[3][1]->x = 1;
    m_pArrayPositions[3][1]->y = 0;
    m_pArrayPositions[3][2]->x = 1;
    m_pArrayPositions[3][2]->y = 1;
    //m_position = m_pArrayPosition[0];
    m_color = RGB(255,130,0);
}
KLTile::KLTile(int numofp): KTile(numofp) 
{
   // m_numOfPos = 4;
/*    KTile::KTile();*/
    
    m_pArrayPositions[0][0]->x = 0;
    m_pArrayPositions[0][0]->y = -1;
    m_pArrayPositions[0][1]->x = 0;
    m_pArrayPositions[0][1]->y = 1;
    m_pArrayPositions[0][2]->x = 1;
    m_pArrayPositions[0][2]->y = 1;
    //m_pArrayPositions[1][1]->x = 0;
    //m_pArrayPositions[1][1]->y = 0;
    m_pArrayPositions[1][0]->x = 1;
    m_pArrayPositions[1][0]->y = 0;
    m_pArrayPositions[1][1]->x = -1;
    m_pArrayPositions[1][1]->y = 0;
    m_pArrayPositions[1][2]->x = -1;
    m_pArrayPositions[1][2]->y = 1;
    //m_pArrayPositions[2][0]->x = 0;
    //m_pArrayPositions[2][0]->y = 0;
    m_pArrayPositions[2][0]->x = 0;
    m_pArrayPositions[2][0]->y = 1;
    m_pArrayPositions[2][1]->x = 0;
    m_pArrayPositions[2][1]->y = -1;
    m_pArrayPositions[2][2]->x = -1;
    m_pArrayPositions[2][2]->y = -1;
    //m_pArrayPositions[3][0]->x = 0;
    //m_pArrayPositions[3][0]->y = 0;
    m_pArrayPositions[3][0]->x = -1;
    m_pArrayPositions[3][0]->y = 0;
    m_pArrayPositions[3][1]->x = 1;
    m_pArrayPositions[3][1]->y = 0;
    m_pArrayPositions[3][2]->x = 1;
    m_pArrayPositions[3][2]->y = -1;
    m_color = RGB(28,192,227);
}
KOTile::KOTile(int numofp): KTile(numofp)
{
    /*KTile::KTile();*/
    //m_numOfPos = 1;
    m_pArrayPositions[0][0]->x = 1;
    m_pArrayPositions[0][0]->y = 0;
    m_pArrayPositions[0][1]->x = 0;
    m_pArrayPositions[0][1]->y = 1;
    m_pArrayPositions[0][2]->x = 1;
    m_pArrayPositions[0][2]->y = 1;
    //m_pArrayPositions[1][1]->x = 0;
    //m_pArrayPositions[1][1]->y = 0;
    m_color = RGB(255,255,0);
}
KZTile::KZTile(int numofp): KTile(numofp)
{ 
    //m_numOfPos = 2;
   /* KTile::KTile();*/
   
    m_pArrayPositions[0][0]->x = -1;
    m_pArrayPositions[0][0]->y = 0;
    m_pArrayPositions[0][1]->x = 0;
    m_pArrayPositions[0][1]->y = 1;
    m_pArrayPositions[0][2]->x = 1;
    m_pArrayPositions[0][2]->y = 1;
    //m_pArrayPositions[1][1]->x = 0;
    //m_pArrayPositions[1][1]->y = 0;
    m_pArrayPositions[1][0]->x = 0;
    m_pArrayPositions[1][0]->y = 1;
    m_pArrayPositions[1][1]->x = 1;
    m_pArrayPositions[1][1]->y = 0;
    m_pArrayPositions[1][2]->x = 1;
    m_pArrayPositions[1][2]->y = -1;
    m_color = RGB(237,35,96);
}
KTTile::KTTile(int numofp): KTile(numofp)
{
    //m_numOfPos = 4; 
/*    KTile::KTile();*/
    
    m_pArrayPositions[0][0]->x = -1;
    m_pArrayPositions[0][0]->y = 0;
    m_pArrayPositions[0][1]->x = 1;
    m_pArrayPositions[0][1]->y = 0;
    m_pArrayPositions[0][2]->x = 0;
    m_pArrayPositions[0][2]->y = -1;
    //m_pArrayPositions[1][1]->x = 0;
    //m_pArrayPositions[1][1]->y = 0;
    m_pArrayPositions[1][0]->x = 0;
    m_pArrayPositions[1][0]->y = -1;
    m_pArrayPositions[1][1]->x = 1;
    m_pArrayPositions[1][1]->y = 0;
    m_pArrayPositions[1][2]->x = 0;
    m_pArrayPositions[1][2]->y = 1;
    //m_pArrayPositions[2][0]->x = 0;
    //m_pArrayPositions[2][0]->y = 0;
    m_pArrayPositions[2][0]->x = -1;
    m_pArrayPositions[2][0]->y = 0;
    m_pArrayPositions[2][1]->x = 1;
    m_pArrayPositions[2][1]->y = 0;
    m_pArrayPositions[2][2]->x = 0;
    m_pArrayPositions[2][2]->y = 1;
    //m_pArrayPositions[3][0]->x = 0;
    //m_pArrayPositions[3][0]->y = 0;
    m_pArrayPositions[3][0]->x = 0;
    m_pArrayPositions[3][0]->y = -1;
    m_pArrayPositions[3][1]->x = -1;
    m_pArrayPositions[3][1]->y = 0;
    m_pArrayPositions[3][2]->x = 0;
    m_pArrayPositions[3][2]->y = 1;
    m_color = RGB(128,0,255);
}
KSTile::KSTile(int numofp): KTile(numofp)
{
    //m_numOfPos = 2;
   /* KTile::KTile();*/
    
    m_pArrayPositions[0][0]->x = -1;
    m_pArrayPositions[0][0]->y = 1;
    m_pArrayPositions[0][1]->x = 0;
    m_pArrayPositions[0][1]->y = 1;
    m_pArrayPositions[0][2]->x = 1;
    m_pArrayPositions[0][2]->y = 0;
    //m_pArrayPositions[1][1]->x = 0;
    //m_pArrayPositions[1][1]->y = 0;
    m_pArrayPositions[1][0]->x = 0;
    m_pArrayPositions[1][0]->y = 1;
    m_pArrayPositions[1][1]->x = -1;
    m_pArrayPositions[1][1]->y = 0;
    m_pArrayPositions[1][2]->x = -1;
    m_pArrayPositions[1][2]->y = -1;
    m_color = RGB(140,220,64);

}