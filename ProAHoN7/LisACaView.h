// LisACaView.h : interface of the CLisACaView class
//
/////////////////////////////////////////////////////////////////////////////

#include "afxwin.h"
#if !defined(AFX_LISACAVIEW_H__A56FABD7_0FEB_4463_BEAD_D7BCE530408D__INCLUDED_)
#define AFX_LISACAVIEW_H__A56FABD7_0FEB_4463_BEAD_D7BCE530408D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLisACaView : public CFormView
{
protected: // create from serialization only
	CLisACaView();
	DECLARE_DYNCREATE(CLisACaView)

public:
	//{{AFX_DATA(CLisACaView)
	enum { IDD = IDD_LISACA_FORM };
	CListBox	m_CtrlLisCHo;
	CListBox	m_CtrlLisHor;
	CListBox	m_CtrlLisCDo;
	CComboBox	m_CtrlLisAul;
	CComboBox	m_CtrlLisDoc;
	CString	m_sTipEva;
	CString	m_sTipCal;
	CString	m_sTotCDo;
	//}}AFX_DATA

// Attributes
public:
	CLisACaDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLisACaView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void CarDatTHo();
	void CarDesCHo();
	void CarCursos();
	void SelRegPr1();
	long lPosArcg;
	void CarDatTAu();
	void CarDesCDo();
	void RutOrdCad();
	void SelRegImp();
	void PrintCabecera(CDC *pDC, CPrintInfo *pInfo, CString sHdr);
	void CarDocent();
	void CarDesAul();
	void CarParAdm();
	int nNumRegg;
	CBrush m_Pincel1;
	COLORREF m_Color1;
	CFont m_Fuente1;
	virtual ~CLisACaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLisACaView)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnProCpanua();
	afx_msg void OnUpdateProCpanua(CCmdUI* pCmdUI);
	afx_msg void OnProAsihor();
	afx_msg void OnUpdateProAsihor(CCmdUI* pCmdUI);
	afx_msg void OnProConcil();
	afx_msg void OnUpdateProConcil(CCmdUI* pCmdUI);
	afx_msg void OnProConaul();
	afx_msg void OnUpdateProConaul(CCmdUI* pCmdUI);
	afx_msg void OnProConhor();
	afx_msg void OnUpdateProConhor(CCmdUI* pCmdUI);
	afx_msg void OnProConpin();
	afx_msg void OnUpdateProConpin(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LisACaView.cpp
inline CLisACaDoc* CLisACaView::GetDocument()
   { return (CLisACaDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDlgLisACa dialog

class CDlgLisACa : public CDialog
{
// Construction
public:
	void ActDatPan();
	long lPosArcg;
	CBrush m_Pincel1;
	COLORREF m_Color1;
	CFont m_Fuente1;
	CDlgLisACa(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLisACa)
	enum { IDD = IDD_DLGLISACA };
	CListBox	m_CtrlLisHor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLisACa)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLisACa)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDlgLisACF dialog

class CDlgLisACF : public CDialog
{
// Construction
public:
	void ActDatPan();
	long lPosArcg;
	CBrush m_Pincel1;
	COLORREF m_Color1;
	CFont m_Fuente1;
	CDlgLisACF(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLisACF)
	enum { IDD = IDD_DLGLISACF };
	CListBox	m_CtrlLisCH2;
	CListBox	m_CtrlLisCHo;
	CEdit	m_CtrlEdiSes2;
	CEdit	m_CtrlEdiSes;
	CComboBox	m_CtrlLisCic;
	CEdit	m_CtrlEdiCin2;
	CEdit	m_CtrlEdiCin;
	CEdit	m_CtrlEdiCua2;
	CEdit	m_CtrlEdiCua;
	CEdit	m_CtrlEdiTre2;
	CEdit	m_CtrlEdiTre;
	CEdit	m_CtrlEdiDos2;
	CEdit	m_CtrlEdiDos;
	CEdit	m_CtrlEdiUno2;
	CEdit	m_CtrlEdiUno;
	CString	m_sEdiCin;
	CString	m_sEdiCua;
	CString	m_sEdiDos;
	CString	m_sEdiTre;
	CString	m_sEdiUno;
	CString	m_sEdiCin2;
	CString	m_sEdiCua2;
	CString	m_sEdiDos2;
	CString	m_sEdiTre2;
	CString	m_sEdiUno2;
	CString	m_sEdiSes;
	CString	m_sEdiSes2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLisACF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLisACF)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchangeLiscic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDlgConAul dialog

class CDlgConAul : public CDialog
{
// Construction
public:
	CBrush m_Pincel2;
	COLORREF m_Color2;
	void ActDatPan();
	void CarDesAul();
	CBrush m_Pincel1;
	CFont m_Fuente1;
	COLORREF m_Color1;
	CDlgConAul(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgConAul)
	enum { IDD = IDD_DLGCONAUL };
	CEdit	m_CtrlEdiDis;
	CEdit	m_CtrlEdiDic;
	CEdit	m_CtrlEdiTrc;
	CEdit	m_CtrlEdiQui;
	CEdit	m_CtrlEdiCat;
	CEdit	m_CtrlEdiOnc;
	CEdit	m_CtrlEdiDoc;
	CEdit	m_CtrlEdiSie;
	CEdit	m_CtrlEdiSei;
	CEdit	m_CtrlEdiOch;
	CEdit	m_CtrlEdiNue;
	CEdit	m_CtrlEdiDie;
	CEdit	m_CtrlEdiUno;
	CEdit	m_CtrlEdiTre;
	CEdit	m_CtrlEdiDos;
	CEdit	m_CtrlEdiCua;
	CEdit	m_CtrlEdiCin;
	CComboBox	m_CtrlLisAulas;
	CString	m_sEdiCin;
	CString	m_sEdiCua;
	CString	m_sEdiDos;
	CString	m_sEdiTre;
	CString	m_sEdiUno;
	CString	m_sEdiDie;
	CString	m_sEdiNue;
	CString	m_sEdiOch;
	CString	m_sEdiSei;
	CString	m_sEdiSie;
	CString	m_sEdiDoc;
	CString	m_sEdiOnc;
	CString	m_sEdiCat;
	CString	m_sEdiTrc;
	CString	m_sEdiQui;
	CString	m_sEdiDic;
	CString	m_sEdiDis;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConAul)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgConAul)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeLisaulas();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDlgPobIni dialog

class CDlgPobIni : public CDialog
{
// Construction
public:
	void ActDatPan();
	CBrush m_Pincel1;
	COLORREF m_Color1;
	CFont m_Fuente1;
	CDlgPobIni(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPobIni)
	enum { IDD = IDD_DLGPOBINI };
	CListBox	m_CtrlLisPIn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPobIni)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPobIni)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDlgProAdi dialog

class CDlgProAdi : public CDialog
{
// Construction
public:
	void GenArcSol();
	void IniCadTi1();
	void IniCadTip();
	double drand48(void);
	void ActDatPan();
	CBrush m_Pincel1;
	COLORREF m_Color1;
	CFont m_Fuente1;
	CDlgProAdi(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProAdi)
	enum { IDD = IDD_DLGPROADI };
	CButton	m_CtrlAltAsi;
	CEdit	m_CtrlNumPob;
	CButton	m_CtrlCalPen;
	CButton	m_CtrlGNPobl;
	CEdit	m_CtrlTotPen;
	CListBox	m_CtrlLisSP4;
	CListBox	m_CtrlLisSP1;
	CListBox	m_CtrlLisSubPob;
	CListBox	m_CtrlLisSP3;
	CListBox	m_CtrlLisSP2;
	CListBox	m_CtrlLisPAc;
	CListBox	m_CtrlLisPenAul;
	CListBox	m_CtrlLisPenDoc;
	CListBox	m_CtrlLisPenCic;
	CListBox	m_CtrlLisDoc;
	CString	m_sTotPen;
	CString	m_sNumPob;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProAdi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProAdi)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnCalpen();
	afx_msg void OnGnpobl();
	afx_msg void OnAltasi();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGvpobl();
	CButton m_CtrlGVPobl;
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISACAVIEW_H__A56FABD7_0FEB_4463_BEAD_D7BCE530408D__INCLUDED_)
