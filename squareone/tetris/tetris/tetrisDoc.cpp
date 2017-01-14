// tetrisDoc.cpp : implementation of the CtetrisDoc class
//

#include "stdafx.h"
#include "tetris.h"

#include "tetrisDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtetrisDoc

IMPLEMENT_DYNCREATE(CtetrisDoc, CDocument)

BEGIN_MESSAGE_MAP(CtetrisDoc, CDocument)
END_MESSAGE_MAP()


// CtetrisDoc construction/destruction

CtetrisDoc::CtetrisDoc()
{
	// TODO: add one-time construction code here

}

CtetrisDoc::~CtetrisDoc()
{
}

BOOL CtetrisDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
    firstTime = TRUE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CtetrisDoc serialization

void CtetrisDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CtetrisDoc diagnostics

#ifdef _DEBUG
void CtetrisDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CtetrisDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CtetrisDoc commands
