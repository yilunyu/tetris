
#pragma once

typedef struct {
    int x;
    int y;
} coord;
class KTile 
{
protected:
    COLORREF m_color;
     
     int m_curPos;
    int m_numOfPos;
     coord ***m_pArrayPositions;
    
public:
    int getNumOfPos() {return m_numOfPos;};
    COLORREF getColor() {return m_color; };
     void rotateRight() {
        m_position = m_pArrayPositions[(m_curPos+1)%m_numOfPos];
        m_curPos = (m_curPos+1)%m_numOfPos;
    };
    coord** m_position;
     void rotateLeft() {
        m_position = m_pArrayPositions[(m_curPos-1+m_numOfPos)%m_numOfPos];
        m_curPos= (m_curPos-1+m_numOfPos)%m_numOfPos;
    };
     KTile (int numofp);
     ~KTile();
}; 

class KITile : public KTile
{
public: 
    KITile(int numofp);
    //void rotateRight();
    //void rotateLeft();
};

class KJTile : public KTile
{
public: 
    KJTile(int numofp);
    //void rotateRight();
    //void rotateLeft();
};
class KLTile : public KTile
{
public:
    KLTile(int numofp);
};
class KOTile : public KTile
{
public: 
    KOTile(int numofp);
  /*  void rotateRight();
    void rotateLeft();*/
};

class KZTile : public KTile
{
public: 
    KZTile(int numofp);
    //void rotateRight();
    //void rotateLeft();
};

class KTTile : public KTile
{
public: 
    KTTile(int numofp);
    //void rotateRight();
    //void rotateLeft();
};

class KSTile : public KTile
{
public:
    KSTile(int numofp);
    //void rotateRight();
    //void rotateLeft();
};