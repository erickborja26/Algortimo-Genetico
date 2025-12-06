// LisACaDoc.cpp : implementation of the CLisACaDoc class
//

#include "stdafx.h"
#include "LisACa.h"

#include "LisACaDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLisACaDoc

IMPLEMENT_DYNCREATE(CLisACaDoc, CDocument)

BEGIN_MESSAGE_MAP(CLisACaDoc, CDocument)
	//{{AFX_MSG_MAP(CLisACaDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLisACaDoc construction/destruction

CLisACaDoc::CLisACaDoc()
{
	// TODO: add one-time construction code here

}

CLisACaDoc::~CLisACaDoc()
{
}

BOOL CLisACaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLisACaDoc serialization

void CLisACaDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CLisACaDoc diagnostics

#ifdef _DEBUG
void CLisACaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLisACaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLisACaDoc commands
