// tetrisDoc.h : interface of the CtetrisDoc class
//


#pragma once


class CtetrisDoc : public CDocument
{
protected: // create from serialization only
	CtetrisDoc();
	DECLARE_DYNCREATE(CtetrisDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
    BOOL firstTime;
// Implementation
public:
	virtual ~CtetrisDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


