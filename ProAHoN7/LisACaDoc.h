// LisACaDoc.h : interface of the CLisACaDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISACADOC_H__0D2769AD_93AD_44BB_8E3B_5D5C3112B0EC__INCLUDED_)
#define AFX_LISACADOC_H__0D2769AD_93AD_44BB_8E3B_5D5C3112B0EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLisACaDoc : public CDocument
{
protected: // create from serialization only
	CLisACaDoc();
	DECLARE_DYNCREATE(CLisACaDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLisACaDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLisACaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLisACaDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISACADOC_H__0D2769AD_93AD_44BB_8E3B_5D5C3112B0EC__INCLUDED_)
