// LisACaView.cpp : implementation of the CLisACaView class
//

#include "stdafx.h"
#include "LisACa.h"
#include "EstPAd.h"
#include "EstTAu.h"
#include "EstTHo.h"
#include "EstAul.h"
#include "EstDoc.h"
#include "EstCur.h"
#include "EstCDo.h"
#include "EstCHo.h"
#include "EstAlu.h"
#include "EstCal.h"
#include "EstCDA.h"
#include "EstHor.h"

#include "LisACaDoc.h"
#include "LisACaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define MAX 2.0e21

char sDirCong[33], sDAEAntg[33], sDAEActg[33], sDirGeng[33];
char sCodColg[8];			// Almacena el codigo del colegio
char sNomColg[51];			// Almacena el nombre del colegio
char sCodTutg[4];			// Codigo de tutor
char sCodAEAlumg[7];		// Cod. Asignatura Exonerada Alumno
short int nNumAEAlumg;		// No.Asig.exon.Alumno
short int nNumANCProg;		// No.Asig.No Considerados p/promedio

// TIPOS DE AULA
char sArrCTAulag[21][4];		// Lista codigos de tipo de aula
char sArrDTAulag[21][32];		// Lista descripcion tipo de aula
char sArrCapAulg[21][3];		// Lista capacidad de aula
int nNumTotTAug;				// Numero Total Tipos de Aula

// TIPOS DE HORA
char sArrCTHorag[11];			// Lista codigos de tipo de aula
char sArrDTHorag[11][16];		// Lista descripcion tipo de aula
int nNumTotTHog;				// Numero Total Tipos de Aula

// AULAS
char sArrCodAulg[41][3];		// Lista codigos de aula
char sArrCTAAsig[41][4];		// Lista codigo tipo aula asignado
char sArrNivAulg[41][11];		// Lista nivel de aula
int nNumTotAulg;				// Numero Total de Aulas
char sArrHDAAulg[41][6][18][10];	// Lista 1 de horas disponibles y asignadas por aula
									// los 6 dias de la semana y las 16 horas del dia
									// los valores son: D(Disponible), Curso y grupo asignado
char sArrHDAAu2g[41][6][18][10];	// Lista 2 de horas disponibles y asignadas por aula
									// los 6 dias de la semana y las 16 horas del dia
									// los valores son: D(Disponible), Curso y grupo asignado
char sArrHDAAu3g[41][6][18][10];	// Lista 3 de horas disponibles y asignadas por aula
									// los 6 dias de la semana y las 16 horas del dia
									// los valores son: D(Disponible), Curso y grupo asignado
// DOCENTES
char sArrCodDocg[200][4];		// Lista codigos de docentes
char sArrCTDispg[200];			// Lista codigos tipo disponibilidad
char sArrAPDoceg[200][16];		// Lista apellido paterno del docente
char sArrAMDoceg[200][16];		// Lista apellido materno del docente
char sArrNomDocg[200][16];		// Lista nombres del docente
int nNumTotDocg;				// Numero Total de Aulas
char sArrHDADocg[200][6][18];	// Lista de horas disponibles y asignadas por docente
								// los 6 dias de la semana y las 16 horas del dia
								// los valores son: D(Disponlble) A(Asignado)
// CURSOS
char sArrCodCurg[200][4];		// Lista codigo de curso
char sArrNomCurg[200][33];		// Lista nombre de curso
char sArrCicCurg[200][3];		// Lista Ciclo de curso
int nNumTotCurg;				// Numero Total de cursos
char sArrHDACurg[200][6][18];	// Lista de horas disponibles y asignadas por curso
								// los 6 dias de la semana y las 16 horas del dia
								// los valores son: D(Disponlble) A(Asignado)
// CURSOS POR HORA
char sArrCCHorag[400][4];		// Lista código de curso por hora
char sArrCTHCHog[400];			// Código tipo de hora por curso hora
char sArrCTACHog[400][4];		// Código tipo aula por curso hora
char sArrNHCHorg[400];			// Número de horas por curso hora
int nNumTotCHog;				// Numero Total de cursos hora

// CURSOS POR DOCENTE POR HORA
char sArrCCCDocg[400][4];		// Lista codigo curso por curso docente
char sArrCDCDocg[400][4];		// Lista codigo docente por curso docente
char sArrCGCDocg[400][4];			// Lista código de grupo por curso docente
int nNumTotCDog;				// Numero Total de cursos por docente
char sArrHDACDog[400][6][18];	// Lista de horas disponibles y asignadas curso por docente
								// los 6 dias de la semana y las 16 horas del dia
								// los valores son: D(Disponlble) A(Asignado)
char sArrCTACDog[400][4];		// Código tipo aula por curso docente
int  nArrNHCDocg[400];			// Lista numero de horas curso por docente
int nArrPCCDocg[400];			// Lista penalidad por ciclo curso docente
int nArrPACDocg[400];			// Lista penalidad por aula curso docente
int nArrPDCDocg[400];			// Lista penalidad por docente curso docente

// CICLOS ACADÉMICOS
char sArrHDACicg[10][6][18][3];		// Lista de horas disponibles y asignadas por ciclos
									// los 6 dias de la semana y las 16 horas del dia
									// los valores son: D(Disponlble), Codigo de curso
char ch_ciclo[11][6][18];	// Tabla muestra el cruce de horas de los cursos
							// que se encuentran en cada uno de los
							// ciclos en los cuales esta el docente, se
							// presenta por dias y horas
char ch_aulas[21][6][18];	// Tabla muestra el cruce de horas de los cursos
							// que se encuentran en cada uno de las
							// aulas en los cuales esta el docente, se
							// presenta por dias y horas
char ch_docen[200][6][18];	// Tabla muestra el cruce de horas del docente,
							// se presenta por dias y horas

// DATOS DE PARAMETROS DE ADMINISTRACION
char sArrNPEBimg[10][21];	// Nombre de periodos en eval.bimestral
char sArrNPETrig[10][21];	// Nombre de periodos en eval.trimestral
char sIndIDMg;				// Indicador Ingreso datos mensuales
char sIndPDMg;				// Indicador Presenta datos mensuales
char sIndDCPg;				// Indicador detalle calificaciones de periodo
char sIPAPPPg;				// Indicador Prom.Asig.Pend.Part.Promedio
char sIOMPPLg;				// Indic.de ord.mérito según posic.prom.en la lista
short int nNCAPerg;			// Nro. de calificaciones x asignatura x periodo
short int nNMPerig;			// Nro, de meses por periodo
char sICPPPog;				// Indic.calc.promedio periodo con porcentaje.
char sIGPMDig;				// Indic.grabar promedio multiplicado por 10.
char sIPPFASg;				// Indicador prom.period.y final area secundaria

int nCicAcag;				// Ciclo académico de consulta

// DATOS DEL NIVEL/GRADO
char sTipCalg;				// Tipo de calificacion
char sTPCCalg;				// Tipo de periodo control de calificaciones

char sCodNivg;				// Codigo de Nivel selccionado
char sCodGrag;				// Codigo de grado seleccionado
char sCodSecg;				// Codigo de Seccion seleccionado
char sNAProcg[5];			// No Año de Proceso(Año Escolar)

char sNivGrag[21];			// Descrip.nivel grado seleccionado
int nNumPerg;				// No periodo seleccionado
int nPLPerig;				// Posicion en la lista de periodos
char sNomPerg[21];			// Nombre periodo seleccionado

char sArrCodAlug[50][7];		// Arreglo de codigos de alumnos (max. 49)
char sArrNomAlug[50][61];		// Arreglo de nombres de alumnos
char sArrEstAlug[50];			// Arreglo de estados de alumnos
char sArrCAEAlug[50][7];		// Arr.Cod.Asignat.Exoner.de Alumno
int nArrNAEAlug[50];			// Arr.Nro.Asignat.Exoner.de Alumno
int nArrNADAlug[50];			// Arr.Nro.Asignat.Desapr.de Alumno
int nArrNAAAlug[50];			// Arr.Nro.Asignat.Aprobad.de Alumno
int nArrPAELAlg[50];			// Arr.Pos.Asi.Exo.Lista de Alumno
int nArrCAPAlug[50][35][10];	// Arr.Cal.Asi.Per.x Alumno
double nArrProAlug[50];			// Arreglo de Promedio de alumnos
double nArrSCAlumg[50];			// Arr.Suma Calificac. de alumno
int nArrNCFProg[50];			// Numero de calificacion faltante para el promedio
int nArrDivProg[50];			// No Asignat./Areas del alumno
int nArrTCPAAlg[50][30];		// Total Calif.promed.por area por alumno
int nArrNAFPAAg[50][30];		// No. Asignat.Falt,Promedio por area por alumno

int nArrNCACAlg[50][35][10];	// No.Calificaciones x Area Curricular x periodo del Alumno
int nArrSCACAlg[50][35][10];	// Suma Calif.x Area Curricular x periodo del Alumno
int nArrPACAlug[50][35][10];	// Promed.x Area Curricular x Periodo de Alumno

int nArrUAAIAlg[50];			// Arreglo Posicion en el arreglo de alumnos
								// El elemento 'n' tiene la posicion en el
                                // arreglo de alumnos, del alumno ´n segun
								// apellidos y nombres
int nArrOrdMe1g[50];			// Arreglo Posicion en el arreglo de alumnos
								// El elemento 'n' tiene la posicion en el
                                // arreglo de alumnos, del alumno ´n segun
								// el promedio, empezando por el mayor
int nArrOrdMe2g[50];			// Arreglo Orden de merito 2
char sIndAsiAlug[50][35];		// Indicador de asignaturas por alumno
int nTotAluRetg;				// Total alumnos retirados
int nTotAluDesg;				// Total de alumnos desaprobados en la sección
int nTotRegImpg;
int nTotAluNGSg;				// Total alumnos nivel/grado/seccion

char sMACalig[11];				// Memoria Almacena Calificacion
int nUbiAsiLAsg;			// Ubic. de Asig.en lista de asignaturas
short int nNumAprg;			// Asignaturas aprobadas
short int nNumDesg;			// Asignaturas desaprobadas
short int nTotAsiExog;		// Total Asignaturas exoneradas en la sección
short int nAluSinCalg;		// No.de Alumnos si calificacion en la sección

int nTotCalAr1g[50];				// Total Calificaciones area 1
int nNumCalAr1g[50];				// Numero Calificaciones area 1
int nTotCalAr2g[50];				// Total Calificaciones area 2
int nNumCalAr2g[50];				// Numero Calificaciones area 2

int nDivProg;		// Divisor para el promedio
int nICFProg;		// Indicador de calificacion faltante para el promedio
					// 0=Cal.faltante NO promedia 1=Calif.faltante SI promedia

int nArrSubPobg[20][50];		// Lista de elementos de la subpoblación con valor
char sArrVarSPog[20][50][100];	// Parte variable de la subpoblación
double nArrPSSPobg[20][50];		// Lista de probabilidad de seleccion subpoblación
double nArrPASPobg[20][50];		// Lista de promedio acumulat.subpoblación
double nDGSPobg[20];			// Datos general  de la subpoblacion
char nArrTSPoblg[20];			// Lista de turnos de la subpoblacion
int nNISPobg[20];				// No. de individuos de la subpoblacion

char sArrDiaSemg[7][16];
int nICIPobg;					// Inidicador de cambio inicial de población

char sArrTCDDig[11][7];		// Arreglo Tipos de Cadena Dos Dias
char sArrTCUDig[11][7];		// Arreglo Tipos de Cadena Un Dia
char sArrTCAUng[11][7];		// Arreglo Tipos de Cadena Aula uno
char sArrTCTHog[11][7];		// Arreglo Tipos de Cadena Tres Horas
char sArrTCDHog[11][7];		// Arreglo Tipos de Cadena Dos Horas

int nNumPobg;				// Numero de población
long nArrTGPoblg[500];		// Tiempo de generaciòn de poblaciòn
int nTPPoblg;				// Total penalidad de la población
//	double nProAcu;

/////////////////////////////////////////////////////////////////////////////
// CLisACaView

IMPLEMENT_DYNCREATE(CLisACaView, CFormView)

BEGIN_MESSAGE_MAP(CLisACaView, CFormView)
	//{{AFX_MSG_MAP(CLisACaView)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_PRO_CPANUA, OnProCpanua)
	ON_UPDATE_COMMAND_UI(ID_PRO_CPANUA, OnUpdateProCpanua)
	ON_COMMAND(ID_PRO_ASIHOR, OnProAsihor)
	ON_UPDATE_COMMAND_UI(ID_PRO_ASIHOR, OnUpdateProAsihor)
	ON_COMMAND(ID_PRO_CONCIL, OnProConcil)
	ON_UPDATE_COMMAND_UI(ID_PRO_CONCIL, OnUpdateProConcil)
	ON_COMMAND(ID_PRO_CONAUL, OnProConaul)
	ON_UPDATE_COMMAND_UI(ID_PRO_CONAUL, OnUpdateProConaul)
	ON_COMMAND(ID_PRO_CONHOR, OnProConhor)
	ON_UPDATE_COMMAND_UI(ID_PRO_CONHOR, OnUpdateProConhor)
	ON_COMMAND(ID_PRO_CONPIN, OnProConpin)
	ON_UPDATE_COMMAND_UI(ID_PRO_CONPIN, OnUpdateProConpin)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLisACaView construction/destruction

CLisACaView::CLisACaView()
	: CFormView(CLisACaView::IDD)
{
	//{{AFX_DATA_INIT(CLisACaView)
	m_sTipEva = _T("");
	m_sTipCal = _T("");
	m_sTotCDo = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CLisACaView::~CLisACaView()
{
}

void CLisACaView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLisACaView)
	DDX_Control(pDX, IDC_LISCHO, m_CtrlLisCHo);
	DDX_Control(pDX, IDC_LISHOR, m_CtrlLisHor);
	DDX_Control(pDX, IDC_LISCDO, m_CtrlLisCDo);
	DDX_Control(pDX, IDC_LISAUL, m_CtrlLisAul);
	DDX_Control(pDX, IDC_LISDOC, m_CtrlLisDoc);
	DDX_Text(pDX, IDC_TIPEVA, m_sTipEva);
	DDX_Text(pDX, IDC_TIPNOT, m_sTipCal);
	DDX_Text(pDX, IDC_TOTCDO, m_sTotCDo);
	//}}AFX_DATA_MAP
}

BOOL CLisACaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CLisACaView::OnInitialUpdate()
{
	static int i=0;
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(false);

	LOGFONT lf;
	memset( &lf, 0, sizeof(LOGFONT) );
	lf.lfHeight = 15;
	strcpy_s(lf.lfFaceName,"Courier New");
	m_Fuente1.CreateFontIndirect(&lf);
	m_CtrlLisDoc.SetFont(&m_Fuente1);
	m_CtrlLisAul.SetFont(&m_Fuente1);
	m_CtrlLisCHo.SetFont(&m_Fuente1);
	m_CtrlLisCDo.SetFont(&m_Fuente1);
	m_CtrlLisHor.SetFont(&m_Fuente1);

	CFile bd1;	// representa la base de datos
	char General[145];
	CString	Cadena;
	CString szNombreFi = "TCONSIS.TXT";
	UINT nModoDeAcceso = CFile::modeRead;
	nModoDeAcceso |= CFile::shareDenyNone;
	bd1.Open(szNombreFi, nModoDeAcceso);
	bd1.Read(&General, 144);
	bd1.Close();
	strcpy_s(sDAEAntg, General+48);
	strcpy_s(sDirGeng, General+80);
	strcpy_s(sDAEActg, General+112);

	if(i==0) {
//		m_Color1 = RGB(255,255, 0x99);
		m_Color1 = RGB(255,255, 175);
		m_Pincel1.CreateSolidBrush(m_Color1);
		CarParAdm();
		CarDatTAu();
		CarDatTHo();
		CarDesAul();
		CarDocent();
		CarCursos();
		CarDesCHo();
		CarDesCDo();
		i=1;
	}
//	tamReg = sizeof(SEstAAl);
//	tamReg1 = sizeof(SEstMOb);
//	m_bOrdMen = true;
	nNumRegg=0;
	UpdateData(false);


}

/////////////////////////////////////////////////////////////////////////////
// CLisACaView printing

BOOL CLisACaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	UpdateData(true);
	if(m_CtrlLisDoc.GetCurSel()<0) {
		AfxMessageBox("Error: Seleccione Docente");
		return false;
	}
	SelRegImp();
	// Longitud del documento
	pInfo->SetMaxPage(int((nTotRegImpg-1)/42)+1);
	
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLisACaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLisACaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLisACaView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add code to print the controls
	int nTamX = pDC->GetDeviceCaps(HORZSIZE) * 10;
	int nTamY = pDC->GetDeviceCaps(VERTSIZE) * 10;
	int nResX = pDC->GetDeviceCaps(HORZRES);
	int nResY = pDC->GetDeviceCaps(VERTRES);

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(nTamX, nTamY);
	pDC->SetViewportExt(nResX, nResY);

	// Convertir coordenadas fisicas a logicas
	pDC->DPtoLP(pInfo->m_rectDraw);

/*	if(pInfo->m_nCurPage == 1)		// si es pagina 1
	{
		PrintTitulo(pDC, pInfo);
		// imprima aqui su historia
		return;
	}
*/
	// imprimir la cabecera
	CString sCabecera = GetDocument()->GetTitle();
	PrintCabecera(pDC, pInfo, sCabecera);

	// establecer el origen para el cuerpo de la página
//	pDC->SetWindowOrg(pInfo->m_rectDraw.left, pInfo->m_rectDraw.top);

	// implementación popr omisión  llama a OnDraw
		CScrollView::OnPrint(pDC, pInfo);
	// TODO: add code to print the controls	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CLisACaView diagnostics

#ifdef _DEBUG
void CLisACaView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLisACaView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLisACaDoc* CLisACaView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLisACaDoc)));
	return (CLisACaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLisACaView message handlers

void CLisACaView::CarParAdm()
{
	CFile bd1;	// representa la base de datos
	SEstPAd ParAdm;
	CString	Cadena;
	CString szNombreFi = sDirGeng;
	
	szNombreFi = szNombreFi + "TParAdm.ct1";
	bd1.Open(szNombreFi, CFile::modeRead|CFile::shareDenyNone);

	long nTamFil1 = (long)bd1.GetLength();		//  posicion final
	int nTamReg1  = sizeof(SEstPAd);

	long nRegs = nTamFil1/(long)nTamReg1;	// numero de registros
	int i=0;
	// busqueda secuencial
	for(long nreg=0; nreg < nRegs; nreg++)
	{
		bd1.Read(&ParAdm, nTamReg1);
		if(ParAdm.m_szannpro[0]!=255 && ParAdm.m_szannpro[0]!=97) {
			if(ParAdm.m_szestpad!='A') {
				sIndIDMg= ParAdm.m_szindidm;
				sIndPDMg= ParAdm.m_szindpdm;
				sIndDCPg= ParAdm.m_szinddcp;
				sIPAPPPg= ParAdm.m_szipappp;
				sIOMPPLg= ParAdm.m_sziomppl;
				sICPPPog= ParAdm.m_szicpppo;
				sIGPMDig= ParAdm.m_szigpmdi;
				sIPPFASg= ParAdm.m_szippfas;
				strcpy_s(sNAProcg, (char *)ParAdm.m_szannpro);
				if(ParAdm.m_szncaper>'0'&&ParAdm.m_szncaper<'6')
					nNCAPerg= ParAdm.m_szncaper-'0';
				for(i=0; i<ParAdm.m_nznumpe1; i++) {
					strcpy_s(sArrNPEBimg[i],ParAdm.m_sznompe1[i]);
				}
				for(i=0; i<ParAdm.m_nznumpe2; i++) {
					strcpy_s(sArrNPETrig[i],ParAdm.m_sznompe2[i]);
				}
			}
		}
	}
	bd1.Close();

}

void CLisACaView::CarDesAul()
{
	CFile bd1;	// representa la base de datos
	SEstAul General;
	CString	Cadena;
	CString szNombreFi = sDirGeng;
	int i, j, k;
	
	szNombreFi = szNombreFi + "TAulas.ct1";

	bd1.Open(szNombreFi, CFile::modeRead);

	long nTamFil1 = (long)bd1.GetLength();		//  posicion final
	int nTamReg1  = sizeof(SEstAul);

	long nRegs = nTamFil1/(long)nTamReg1;	// numero de registros
	i=0;
	// busqueda secuencial
	for(long nreg=0; nreg < nRegs; nreg++)
	{
		bd1.Read(&General, nTamReg1);
		if(General.m_szcodaul[0]!=255 && General.m_szcodaul[0]!=97) {
			strncpy(sArrCodAulg[i], (char *)General.m_szcodaul, 2);
			strncpy(sArrCTAAsig[i], General.m_szctaasi, 3);
			strncpy(sArrNivAulg[i], General.m_sznivaul, 11);
			for(j=0; j<nNumTotTAug; j++)
				if(!strncmp(sArrCTAulag[j], General.m_szctaasi, 3))
					break;
			Cadena.Format("%-2.2s %-3.3s %-15.15s %-10.10s",
				General.m_szcodaul, General.m_szctaasi,
				sArrDTAulag[j], General.m_sznivaul);
			m_CtrlLisAul.AddString(Cadena);
			for(j=0; j<6; j++)
				for(k=0; k<18; k++)
					sArrHDAAulg[i][j][k][0]= sArrHDAAu2g[i][j][k][0]= 'D';
			i++;
		}
	}
	nNumTotAulg=i;
	bd1.Close();
}

void CLisACaView::CarDocent()
{
	CFile bd1;	// representa la base de datos
	char Cad11[121];
	SEstDoc General;
	CString	Cadena;
	CString szNombreFi = sDirGeng;
	int nHotIni, nHorFin;
	int i;
	
	szNombreFi = szNombreFi + "TDocent.ct1";

	bd1.Open(szNombreFi, CFile::modeRead);

	long nTamFil1 = (long)bd1.GetLength();		//  posicion final
	int nTamReg1  = sizeof(SEstDoc);

	long nRegs = nTamFil1/(long)nTamReg1;	// numero de registros
	i=0;
	nHotIni= nHorFin= 0;
	// busqueda secuencial
	for(long nreg=0; nreg < nRegs; nreg++)
	{
		bd1.Read(&General, nTamReg1);
		if(General.m_szcoddoc[0]!=255 && General.m_szcoddoc[0]!=97) {
			strncpy(sArrCodDocg[i], (char *)General.m_szcoddoc, 3);
			sArrCTDispg[i] = General.m_szctdisp;
			strncpy(sArrAPDoceg[i], General.m_szapdoce, 15);
			strncpy(sArrAMDoceg[i], General.m_szamdoce, 15);
			strncpy(sArrNomDocg[i], General.m_sznomdoc, 15);
			strcpy_s(Cad11, General.m_szapdoce);
			strcat_s(Cad11, " ");
			strcat_s(Cad11, General.m_szamdoce);
			strcat_s(Cad11, ", ");
			strcat_s(Cad11, General.m_sznomdoc);
			Cadena.Format("%-3.3s %-25.25s  %c",
				General.m_szcoddoc, Cad11, General.m_szctdisp);
			m_CtrlLisDoc.AddString(Cadena);
			if(General.m_szctdisp=='1') {
				nHotIni= 0;
				nHorFin= 6;
			}
			if(General.m_szctdisp=='2') {
				nHotIni= 6;
				nHorFin= 12;
			}
			if(General.m_szctdisp=='3') {
				nHotIni= 11;
				nHorFin= 17;
			}
			if(General.m_szctdisp=='4') {
				nHotIni= 0;
				nHorFin= 12;
			}
			if(General.m_szctdisp=='5') {
				nHotIni= 6;
				nHorFin= 17;
			}
			if(General.m_szctdisp=='6') {
				nHotIni= 0;
				nHorFin= 17;
			}
			for(int j=0; j<6; j++)
				for(int k=nHotIni; k<nHorFin; k++)
					sArrHDADocg[i][j][k]='D';
			i++;
		}
	}
	nNumTotDocg=i;
	bd1.Close();

}

HBRUSH CLisACaView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID()==IDC_LISDOC||
		pWnd->GetDlgCtrlID()==IDC_TIPEVA||
		pWnd->GetDlgCtrlID()==IDC_TIPNOT||
		pWnd->GetDlgCtrlID()==IDC_LISCHO||
		pWnd->GetDlgCtrlID()==IDC_LISHOR||
		pWnd->GetDlgCtrlID()==IDC_TOTCDO||
		pWnd->GetDlgCtrlID()==IDC_LISCDO){
		
		pDC->SetBkColor(m_Color1);
		pDC->SetTextColor(RGB(55, 0, 0));
		return (HBRUSH)m_Pincel1.GetSafeHandle();
	}
  return hbr;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgLisACa dialog


CDlgLisACa::CDlgLisACa(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLisACa::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLisACa)
	//}}AFX_DATA_INIT
}


void CDlgLisACa::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLisACa)
	DDX_Control(pDX, IDC_LISHOR, m_CtrlLisHor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLisACa, CDialog)
	//{{AFX_MSG_MAP(CDlgLisACa)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLisACa message handlers

BOOL CDlgLisACa::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here

	LOGFONT lf;
	memset( &lf, 0, sizeof(LOGFONT) );
	lf.lfHeight = 14;
	strcpy_s(lf.lfFaceName,"Courier New");
	m_Fuente1.CreateFontIndirect(&lf);
	m_CtrlLisHor.SetFont(&m_Fuente1);

	m_Color1 = RGB(255,255, 175);
	m_Pincel1.CreateSolidBrush(m_Color1);
//	CarDesCar1();
//	nTamRegg = sizeof(SEstCal);

//	ActivaInactivaDialogo(false);
	ActDatPan();
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
}

HBRUSH CDlgLisACa::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID()==IDC_LISHOR||
	    pWnd->GetDlgCtrlID()==IDC_LISHOR){
		
		pDC->SetBkColor(m_Color1);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)m_Pincel1.GetSafeHandle();
	}
	return hbr;
}

void CLisACaView::PrintCabecera(CDC *pDC, CPrintInfo *pInfo, CString sHdr)
{
	CString Cadena, Cadena1;
	char Cad11[61];
	CFile bd1;	// representa al fichero
	int nNumApr=0;
	int nNumDes=0;
	int i1, i2, i8;

//	SEstAlu Alumno;
	CString szNombreFi= sDAEActg;
	szNombreFi= szNombreFi + "TAlumno.ct1";
	UINT nModoDeAcceso = CFile::modeRead;
	nModoDeAcceso |= CFile::shareDenyNone;
	bd1.Open(szNombreFi, nModoDeAcceso);
	long nTamFil1 = (long)bd1.GetLength();		//  posicion final
	int  nTamReg1  = sizeof(SEstAlu);
	long nRegs1   = nTamFil1/(long)nTamReg1;	// numero de registros

	// Fuente para imprimir la cabecera
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT) );
	// En MM_LOMETRIC una unidad logica son 0.1 mm.
	lf.lfHeight = 32;
	strcpy_s(lf.lfFaceName, "Courier New");
	CFont fuente;
	CFont *pFuenteAnterior = NULL;
	if(fuente.CreateFontIndirect(&lf))
		pFuenteAnterior = pDC->SelectObject(&fuente);

	// Imprimir una cabecera consistente en el nombre del documento
	// y una línea horizontal
	int y=100;
	pDC->TextOut(0, y, sNomColg );

	// example for CTime::Format and CTime::FormatGmt
	CTime t = CTime::GetCurrentTime();
	CString s = t.Format( "%d.%m.%y" );
	pDC->TextOut(1800, y, s);

	// Dibujar una linea horizontal por debajo del texto
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	y += tm.tmHeight + 10;
	pDC->MoveTo(0, y);
	pDC->LineTo(pInfo->m_rectDraw.right, y);

	for(int i2=0; i2<nTotAluNGSg; i2++) {
		if(nArrNADAlug[i2]>0)		nNumDes++;
		else						nNumApr++;
	}
	// bajar 10 mm. por debajo de la línea
	y +=10;
	pInfo->m_rectDraw.top -=y;

	if(pInfo->m_nCurPage > 0) {
		y+=40;
		Cadena1=sNomPerg;
		Cadena1.MakeUpper();
		Cadena.Format("LISTA DE CALIFICACIONES %s - TODAS LAS ASIGNATURAS",
			Cadena1);
		pDC->TextOut(400, y, Cadena);

		y+=60;
		pDC->TextOut(100, y, Cadena);
		pDC->TextOut(1100,y,Cadena1);

		y+=60;
		pDC->MoveTo(0, y);
		pDC->LineTo(pInfo->m_rectDraw.right, y);
		y+=30;
		pDC->TextOut(10, y, "Alumno");
		Cadena="";
		Cadena = Cadena + "SC  Prom. Ap De OM";
		pDC->TextOut(650, y, Cadena);
		y+=40;
		Cadena="";
		pDC->TextOut(650, y, Cadena);
		y+=40;
		Cadena="";
		pDC->TextOut(650, y, Cadena);

		y+=60;

		pDC->MoveTo(0, y);
		pDC->LineTo(pInfo->m_rectDraw.right, y);

		int n=0;
		for (int i=int((pInfo->m_nCurPage-1)*42);
		i<nTotRegImpg&&i<(int)((pInfo->m_nCurPage)*42); i++) {
			y=y+50;
			strcpy_s(Cad11,sArrNomAlug[nArrUAAIAlg[i]]);
			int i3=strlen(Cad11);
			for(i1=0; i1<i3; i1++)
				if(Cad11[i1]==',')
					break;
			for(i2=i1+3; i2<i3; i2++)
				if(Cad11[i2]>='A' && Cad11[i2]<='Z')
					Cad11[i2]=Cad11[i2]+('a'-'A');
				else
					i2++;

			Cadena.Format("%02d %-30.30s", i+1, Cad11);
			pDC->TextOut(10, y, Cadena);
			Cadena="";
			if(nArrSCAlumg[nArrUAAIAlg[i]]>0)
				Cadena1.Format("%3.0lf %.2f",nArrSCAlumg[nArrUAAIAlg[i]],
				nArrProAlug[nArrUAAIAlg[i]]);
			else
				Cadena1 = "... .....";
			Cadena = Cadena+Cadena1;
			Cadena1.Format(" %02d %02d",
				nArrNAAAlug[nArrUAAIAlg[i]],nArrNADAlug[nArrUAAIAlg[i]]);
			Cadena = Cadena+Cadena1;

			for(i8=0; i8<nTotAluNGSg; i8++)
				if(nArrUAAIAlg[i]==nArrOrdMe1g[i8])
					break;

			Cadena1.Format("(%02d)",int(nArrOrdMe2g[i8]+1));
			Cadena = Cadena+Cadena1;
			if(sArrEstAlug[nArrUAAIAlg[i]]=='R')
				Cadena=Cadena+"Retirado";
			pDC->TextOut(650, y, Cadena);
		}
	}
	y+=100;
	if(nTotAluRetg)
		Cadena.Format("Matriculados: %02d  Retirados: %02d  Efectivo: %02d   Con Calificaciones: %02d",
		nTotAluNGSg, nTotAluRetg, nTotAluNGSg-nTotAluRetg,nTotAluNGSg-nAluSinCalg);
	else
		if(nAluSinCalg)
			Cadena.Format("Alumnos Matriculados: %02d   Con Calificaciones: %02d",
			nTotAluNGSg,nTotAluNGSg-nAluSinCalg);
		else
			Cadena.Format("Alumnos Matriculados: %02d", nTotAluNGSg);
	pDC->TextOut(10, y, Cadena);
	y+=50;
	if(nTotAsiExog) {
		Cadena.Format("Se tiene(n) %02d Exoneracion(es)",nTotAsiExog);
		pDC->TextOut(10, y, Cadena);
		y+=50;
	}
	Cadena.Format("Invictos:  %02d  %6.2f%%   Con Asignatura(s) Desprobada(s): %02d  %6.2f%%",
		nTotAluNGSg-nAluSinCalg-nTotAluDesg,
		(float(nTotAluNGSg-nAluSinCalg-nTotAluDesg)/float(nTotAluNGSg-nAluSinCalg))*100.00,
		nTotAluDesg,
		(float(nTotAluDesg)/float(nTotAluNGSg-nAluSinCalg))*100.00);
	pDC->TextOut(10, y, Cadena);
	bd1.Close();
	if (pFuenteAnterior != NULL)
		pDC->SelectObject(pFuenteAnterior);

}

void CLisACaView::SelRegImp()
{
}

void CLisACaView::RutOrdCad()
{
	int i, j, k;
	// Todos los caracteres mayores a 'n' se incrementan en 1
	// caracter 'ñ' se trnasforma en 'o'
	// caracter 'Ñ' se trnasforma en 'O'
	for(i=0; i<nTotAluNGSg; i++) {
		k = strlen(sArrNomAlug[i]);
		for(j=0; j<k; j++) {
			if(sArrNomAlug[i][j]>'n' && sArrNomAlug[i][j]<='z')
				sArrNomAlug[i][j]=sArrNomAlug[i][j]+1;
			else
				if(sArrNomAlug[i][j]>'N' && sArrNomAlug[i][j]<='Z')
					sArrNomAlug[i][j]=sArrNomAlug[i][j]+1;
				else
					if(sArrNomAlug[i][j]=='ñ')
						sArrNomAlug[i][j]='o';
					else
						if(sArrNomAlug[i][j]=='Ñ')
							sArrNomAlug[i][j]='O';
		}
	}
	// Se realiza el ordenamiento de apellidos y nombres
	for(i=0; i<nTotAluNGSg-1; i++) {
		for(j=i+1; j<nTotAluNGSg; j++) {
			if(strncmp(sArrNomAlug[nArrUAAIAlg[i]],sArrNomAlug[nArrUAAIAlg[j]],50)>0) {
				nArrUAAIAlg[nTotAluNGSg] = nArrUAAIAlg[j];
				nArrUAAIAlg[j] = nArrUAAIAlg[i];
				nArrUAAIAlg[i] = nArrUAAIAlg[nTotAluNGSg];

			}
		}
	}

	// Se realiza el ordenamiento segun el promedio
	for(i=0; i<nTotAluNGSg-1; i++) {
		for(j=i+1; j<nTotAluNGSg; j++) {
			if(nArrProAlug[nArrOrdMe1g[i]]<nArrProAlug[nArrOrdMe1g[j]]) {
				nArrOrdMe1g[nTotAluNGSg] = nArrOrdMe1g[j];
				nArrOrdMe1g[j] = nArrOrdMe1g[i];
				nArrOrdMe1g[i] = nArrOrdMe1g[nTotAluNGSg];

			}
		}
	}

	// nArrOrdMe2g[] guarda el orden de merito
	// y a veces se repite
	for(i=0; i<nTotAluNGSg-1; i++) {
		if(nArrProAlug[nArrOrdMe1g[i]]==nArrProAlug[nArrOrdMe1g[i+1]]) {
			nArrOrdMe2g[i+1]=nArrOrdMe2g[i];
		}
	}
	if(sIOMPPLg=='S') {
		int x;
		for(i=0; i<nTotAluNGSg-1; i++) {
			if((nArrOrdMe2g[i+1]-nArrOrdMe2g[i])>1) {
				x = nArrOrdMe2g[i+1] - nArrOrdMe2g[i] - 1;
				for(int i1=i+1; i1<nTotAluNGSg; i1++)
					nArrOrdMe2g[i1]=nArrOrdMe2g[i1]-x;
			}
		}
	}
	for(i=0; i<nTotAluNGSg; i++) {
		k = strlen(sArrNomAlug[i]);
		for(j=0; j<k; j++) {
			if(sArrNomAlug[i][j]>('n'+1) && sArrNomAlug[i][j]<=('z'+1))
				sArrNomAlug[i][j]=sArrNomAlug[i][j]-1;
			else
				if(sArrNomAlug[i][j]>('N'+1) && sArrNomAlug[i][j]<=('Z'+1))
					sArrNomAlug[i][j]=sArrNomAlug[i][j]-1;
				else
					if(sArrNomAlug[i][j]=='o')
						sArrNomAlug[i][j]='ñ';
					else
						if(sArrNomAlug[i][j]=='O')
							sArrNomAlug[i][j]='Ñ';
		}
	}

}

void CLisACaView::CarDesCDo()
{
	CFile bd1;	// representa la base de datos
	char Cad11[121];
	SEstCDo General;
	CString	Cadena;
	CString szNombreFi = sDirGeng;
	int nHotIni, nHorFin;
	int i, j, k;
	char sCodCur[4];
	char sCGCDoc;
	int j1;
	int nNHTeor, nNHPrac, nNHLabo;
	char sCTATeo[4], sCTAPra[4], sCTALab[4];
	
	szNombreFi = szNombreFi + "TCDocen.ct1";
	bd1.Open(szNombreFi, CFile::modeRead);
	long nTamFil1 = (long)bd1.GetLength();		//  posicion final
	int nTamReg1  = sizeof(SEstCDo);

	long nRegs = nTamFil1/(long)nTamReg1;	// numero de registros
	i=0;
	nHotIni= nHorFin= 0;
	sCodCur[0]= sCGCDoc= 0;
	sCTATeo[0]= sCTAPra[0] = sCTALab[0]= 0;
	// busqueda secuencial
	for(long nreg=0; nreg < nRegs; nreg++)
	{
		bd1.Read(&General, nTamReg1);
		if(General.m_szcodcur[0]!=255 && General.m_szcodcur[0]!=97) {
			strncpy(sArrCCCDocg[i], (char *)General.m_szcodcur, 3);
			strncpy(sArrCDCDocg[i], General.m_szcoddoc, 3);
			strncpy(sArrCGCDocg[i], General.m_szcodgru, 3);
			for(j=0; j<nNumTotDocg; j++)
				if(!strncmp(sArrCodDocg[j], General.m_szcoddoc, 3))
					break;
			strcpy_s(Cad11, sArrAPDoceg[j]);
			strcat_s(Cad11, " ");
			strcat_s(Cad11, sArrAMDoceg[j]);
			strcat_s(Cad11, ", ");
			strcat_s(Cad11, sArrNomDocg[j]);
			for(k=0; k<nNumTotCurg; k++)
				if(!strncmp(sArrCodCurg[k], (char *)General.m_szcodcur, 3))
					break;

			nNHTeor = nNHPrac = nNHLabo = 0;
			for(j1=0; j1<nNumTotCHog; j1++) {
				if(!strncmp(sArrCCCDocg[i],sArrCCHorag[j1], 3)) {
					if(sArrCTHCHog[j1]=='1') {
						nNHTeor = nNHTeor + (sArrNHCHorg[j1]-'0');
						strncpy(sCTATeo, sArrCTACHog[j1], 3);
					}
					if(sArrCTHCHog[j1]=='2') {
						nNHPrac = nNHPrac + (sArrNHCHorg[j1]-'0');
						strncpy(sCTAPra, sArrCTACHog[j1], 3);
					}
					if(sArrCTHCHog[j1]=='3') {
						nNHLabo = nNHLabo + (sArrNHCHorg[j1]-'0');
						strncpy(sCTALab, sArrCTACHog[j1], 3);
					}
				}
			}
			if(i==0) {
				nArrNHCDocg[i]= nNHTeor + nNHPrac + nNHLabo;
				if(nNHTeor>0)
					strncpy(sArrCTACDog[i], sCTATeo, 3);
				else
					if(nNHPrac>0)
						strncpy(sArrCTACDog[i], sCTAPra, 3);
					else
						if(nNHLabo>0)
							strncpy(sArrCTACDog[i], sCTALab, 3);
			}
			if(i>0) {
				// si es diferente que el anterior
				if(strncmp(sArrCCCDocg[i], sArrCCCDocg[i-1], 3) ) {
					nArrNHCDocg[i]= nNHTeor + nNHPrac + nNHLabo;
					if(nNHTeor>0)
						strncpy(sArrCTACDog[i], sCTATeo, 3);
					else
						if(nNHPrac>0)
							strncpy(sArrCTACDog[i], sCTAPra, 3);
						else
							if(nNHLabo>0)
								strncpy(sArrCTACDog[i], sCTALab, 3);
				}
				// Es igual que el anterior
				else {
					// Solo se tienen dos elementos
					if(i==1) {
						if(nNHTeor>0) {
							if(nNHPrac>0) {
								if(nNHLabo>0) {
									strncpy(sArrCTACDog[i-1], sCTATeo, 3);
									nArrNHCDocg[i-1]= nNHTeor+nNHPrac;
									strncpy(sArrCTACDog[i], sCTALab, 3);
									nArrNHCDocg[i]= nNHLabo;
								}
								else {
									strncpy(sArrCTACDog[i-1], sCTATeo, 3);
									nArrNHCDocg[i-1]= nNHTeor;
									strncpy(sArrCTACDog[i], sCTAPra, 3);
									nArrNHCDocg[i]= nNHPrac;
								}
							}
							else {
								if(nNHLabo>0) {
									strncpy(sArrCTACDog[i-1], sCTATeo, 3);
									nArrNHCDocg[i-1]= nNHTeor;
									strncpy(sArrCTACDog[i], sCTALab, 3);
									nArrNHCDocg[i]= nNHLabo;
								}
								else {
									strncpy(sArrCTACDog[i], sCTATeo, 3);
									nArrNHCDocg[i]= nNHTeor;
								}
							}
						}
						else {
							if(nNHPrac>0) {
								if(nNHLabo>0) {
									strncpy(sArrCTACDog[i-1], sCTAPra, 3);
									nArrNHCDocg[i-1]= nNHPrac;
									strncpy(sArrCTACDog[i], sCTALab, 3);
									nArrNHCDocg[i]= nNHLabo;
								}
								else {
									strncpy(sArrCTACDog[i], sCTAPra, 3);
									nArrNHCDocg[i]= nNHPrac;
								}
							}
							else {
								if(nNHLabo>0) {
									strncpy(sArrCTACDog[i], sCTALab, 3);
									nArrNHCDocg[i]= nNHLabo;
								}
							}
						}
					}
					else  {
						// Si el curso es diferente que el anterior del anterior
						if(strncmp(sArrCCCDocg[i], sArrCCCDocg[i-2], 3)) {
							if(!strncmp(sArrCGCDocg[i-1], "01", 2) &&
								!strncmp(sArrCGCDocg[i], "02", 2)) {
								nArrNHCDocg[i-1]= nNHTeor + nNHPrac + nNHLabo;
								nArrNHCDocg[i]= nNHTeor + nNHPrac + nNHLabo;
								if(nNHTeor>0) {
									strncpy(sArrCTACDog[i-1], sCTATeo, 3);
									strncpy(sArrCTACDog[i], sCTATeo, 3);
								}
								else {
									if(nNHPrac>0) {
										strncpy(sArrCTACDog[i-1], sCTAPra, 3);
										strncpy(sArrCTACDog[i], sCTAPra, 3);
									}
									else {
										if(nNHLabo>0) {
											strncpy(sArrCTACDog[i-1], sCTALab, 3);
											strncpy(sArrCTACDog[i], sCTALab, 3);
										}
									}
								}
							}
							else {
								if(nNHTeor>0) {
									if(nNHPrac>0) {
										if(nNHLabo>0) {
											strncpy(sArrCTACDog[i-1], sCTATeo, 3);
											nArrNHCDocg[i-1]= nNHTeor+nNHPrac;
											strncpy(sArrCTACDog[i], sCTALab, 3);
											nArrNHCDocg[i]= nNHLabo;
										}
										else {
											strncpy(sArrCTACDog[i-1], sCTATeo, 3);
											nArrNHCDocg[i-1]= nNHTeor;
											strncpy(sArrCTACDog[i], sCTAPra, 3);
											nArrNHCDocg[i]= nNHPrac;
										}
									}
									else {
										if(nNHLabo>0) {
											strncpy(sArrCTACDog[i-1], sCTATeo, 3);
											nArrNHCDocg[i-1]= nNHTeor;
											strncpy(sArrCTACDog[i], sCTALab, 3);
											nArrNHCDocg[i]= nNHLabo;
										}
										else {
											strncpy(sArrCTACDog[i], sCTATeo, 3);
											nArrNHCDocg[i]= nNHTeor;
										}
									}
								}
								else {
									if(nNHPrac>0) {
										if(nNHLabo>0) {
											strncpy(sArrCTACDog[i-1], sCTAPra, 3);
											nArrNHCDocg[i-1]= nNHPrac;
											strncpy(sArrCTACDog[i], sCTALab, 3);
											nArrNHCDocg[i]= nNHLabo;
										}
										else {
											strncpy(sArrCTACDog[i], sCTAPra, 3);
											nArrNHCDocg[i]= nNHPrac;
										}
									}
									else {
										if(nNHLabo>0) {
											strncpy(sArrCTACDog[i], sCTALab, 3);
											nArrNHCDocg[i]= nNHLabo;
										}
									}
								}
							}
						}
						else {
							if(!strncmp(sArrCGCDocg[i-2], "01", 2) &&
								!strncmp(sArrCGCDocg[i-1], "90", 2) &&
								!strncmp(sArrCGCDocg[i], "91", 2)) {
								nArrNHCDocg[i-2]= nNHTeor + nNHPrac  ;
								nArrNHCDocg[i-1]= nNHLabo;
								nArrNHCDocg[i]= nNHLabo;
								strncpy(sArrCTACDog[i-2], sCTATeo, 3);
								strncpy(sArrCTACDog[i-1], sCTALab, 3);
								strncpy(sArrCTACDog[i], sCTALab, 3);
							}
							else {
								nArrNHCDocg[i-2]= nNHTeor;
								strncpy(sArrCTACDog[i-2], sCTATeo, 3);
								nArrNHCDocg[i-1]= nNHPrac;
								strncpy(sArrCTACDog[i-1], sCTAPra, 3);
								nArrNHCDocg[i]= nNHLabo;
								strncpy(sArrCTACDog[i], sCTALab, 3);
							}
						}
					}
				}
			}


//				if(!strncmp(sArrCCCDocg[i], sArrCCCDocg[i-1], 3) &&
//					!strncmp(sArrCGCDocg[i], sArrCGCDocg[i-1],3)) {
//				if(!strncmp(sArrCCCDocg[i], sArrCCCDocg[i-1], 3) ) {
//					if(i>1) {
//						if(!strncmp(sArrCCCDocg[i], sArrCCCDocg[i-2], 3) &&
//							!strncmp(sArrCGCDocg[i], sArrCGCDocg[i-2], 3)) {
//						if(!strncmp(sArrCCCDocg[i], sArrCCCDocg[i-2], 3)) {
//						}
//						else {
//					}
//					else {
//					}
//				}
//				else {
//			}

			if(sArrCicCurg[k][0]=='0') {
				if(sArrCicCurg[k][1]>='1' && sArrCicCurg[k][1]<='4') {
					nHotIni= 0;
					nHorFin= 6;
				}
				if(sArrCicCurg[k][1]>='5' && sArrCicCurg[k][1]<='7') {
					nHotIni= 6;
					nHorFin= 12;
				}
				if(sArrCicCurg[k][1]>='8' && sArrCicCurg[k][1]<='9') {
					nHotIni= 11;
					nHorFin= 17;
				}
			}
			else {
				if(sArrCicCurg[k][0]=='1' && sArrCicCurg[k][1]=='0') {
					nHotIni= 11;
					nHorFin= 17;
				}
			}

			for(j=0; j<6; j++)
				for(k=nHotIni; k<nHorFin; k++)
					sArrHDACDog[i][j][k]= 'D';
			i++;
		}
	}
	nNumTotCDog = i;
	m_sTotCDo.Format("%02d", i);


	for(i=0; i<nNumTotCDog; i++) {
		for(j=0; j<nNumTotDocg; j++)
			if(!strncmp(sArrCodDocg[j], sArrCDCDocg[i], 3))
				break;
		strcpy_s(Cad11, sArrAPDoceg[j]);
		strcat_s(Cad11, " ");
		strcat_s(Cad11, sArrAMDoceg[j]);
		strcat_s(Cad11, ", ");
		strcat_s(Cad11, sArrNomDocg[j]);
		for(k=0; k<nNumTotCurg; k++)
			if(!strncmp(sArrCodCurg[k], sArrCCCDocg[i], 3))
				break;
		if(sArrCicCurg[k][0]=='0') {
			if(sArrCicCurg[k][1]>='1' && sArrCicCurg[k][1]<='4') {
				nHotIni= 0;
				nHorFin= 6;
			}
			if(sArrCicCurg[k][1]>='5' && sArrCicCurg[k][1]<='7') {
				nHotIni= 6;
				nHorFin= 12;
			}
			if(sArrCicCurg[k][1]>='8' && sArrCicCurg[k][1]<='9') {
				nHotIni= 11;
				nHorFin= 17;
			}
		}
		else {
			if(sArrCicCurg[k][0]=='1' && sArrCicCurg[k][1]=='0') {
				nHotIni= 11;
				nHorFin= 17;
			}
		}

		Cadena.Format("%-3.3s %-20.20s %-3.3s %-20.20s  %-3.3s  %-3.3s  %d  %s  %02d  %02d",
			sArrCCCDocg[i], sArrNomCurg[k],	sArrCDCDocg[i], Cad11,
			sArrCGCDocg[i], sArrCTACDog[i], nArrNHCDocg[i],
			sArrCicCurg[k], nHotIni ,nHorFin );
		m_CtrlLisCDo.AddString(Cadena);
	}

	for (i=0; i<10; i++)
		for(j=0; j<6; j++)
			for(k=0; k<18; k++)
				sArrHDACicg[i][j][k][0]= 'D';
	bd1.Close();

}

void CLisACaView::CarDatTAu()
{
	CFile bd1;	// representa la base de datos
	SEstTAu General;
	CString	Cadena;
	CString szNombreFi = sDirGeng;
	
	szNombreFi = szNombreFi + "TTAula.ct1";

	bd1.Open(szNombreFi, CFile::modeRead);

	long nTamFil1 = (long)bd1.GetLength();		//  posicion final
	int nTamReg1  = sizeof(SEstTAu);

	long nRegs = nTamFil1/(long)nTamReg1;	// numero de registros
	int i=0;
	// busqueda secuencial
	for(long nreg=0; nreg < nRegs; nreg++)
	{
		bd1.Read(&General, nTamReg1);
		if(General.m_szctaula[0]!=255 && General.m_szctaula[0]!=97) {
			strncpy(sArrCTAulag[i], (char *)General.m_szctaula, 3);
			strncpy(sArrDTAulag[i], General.m_szdtaula, 31);
			strncpy(sArrCapAulg[i], General.m_szcapaul, 2);
			i++;
		}
	}
	nNumTotTAug=i;
	bd1.Close();
}


void CLisACaView::OnProCpanua() 
{
	// TODO: Add your command handler code here
	CDlgProAdi Dlg1;
	Dlg1.DoModal();	
}

void CLisACaView::OnUpdateProCpanua(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
/////////////////////////////////////////////////////////////////////////////
// CDlgLisACF dialog


CDlgLisACF::CDlgLisACF(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLisACF::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLisACF)
	m_sEdiCin = _T("");
	m_sEdiCua = _T("");
	m_sEdiDos = _T("");
	m_sEdiTre = _T("");
	m_sEdiUno = _T("");
	m_sEdiCin2 = _T("");
	m_sEdiCua2 = _T("");
	m_sEdiDos2 = _T("");
	m_sEdiTre2 = _T("");
	m_sEdiUno2 = _T("");
	m_sEdiSes = _T("");
	m_sEdiSes2 = _T("");
	//}}AFX_DATA_INIT
}


void CDlgLisACF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLisACF)
	DDX_Control(pDX, IDC_LISCH2, m_CtrlLisCH2);
	DDX_Control(pDX, IDC_LISCHO, m_CtrlLisCHo);
	DDX_Control(pDX, IDC_EDISES2, m_CtrlEdiSes2);
	DDX_Control(pDX, IDC_EDISES, m_CtrlEdiSes);
	DDX_Control(pDX, IDC_LISCIC, m_CtrlLisCic);
	DDX_Control(pDX, IDC_EDICIN2, m_CtrlEdiCin2);
	DDX_Control(pDX, IDC_EDICIN, m_CtrlEdiCin);
	DDX_Control(pDX, IDC_EDICUA2, m_CtrlEdiCua2);
	DDX_Control(pDX, IDC_EDICUA, m_CtrlEdiCua);
	DDX_Control(pDX, IDC_EDITRE2, m_CtrlEdiTre2);
	DDX_Control(pDX, IDC_EDITRE, m_CtrlEdiTre);
	DDX_Control(pDX, IDC_EDIDOS2, m_CtrlEdiDos2);
	DDX_Control(pDX, IDC_EDIDOS, m_CtrlEdiDos);
	DDX_Control(pDX, IDC_EDIUNO2, m_CtrlEdiUno2);
	DDX_Control(pDX, IDC_EDIUNO, m_CtrlEdiUno);
	DDX_Text(pDX, IDC_EDICIN, m_sEdiCin);
	DDX_Text(pDX, IDC_EDICUA, m_sEdiCua);
	DDX_Text(pDX, IDC_EDIDOS, m_sEdiDos);
	DDX_Text(pDX, IDC_EDITRE, m_sEdiTre);
	DDX_Text(pDX, IDC_EDIUNO, m_sEdiUno);
	DDX_Text(pDX, IDC_EDICIN2, m_sEdiCin2);
	DDX_Text(pDX, IDC_EDICUA2, m_sEdiCua2);
	DDX_Text(pDX, IDC_EDIDOS2, m_sEdiDos2);
	DDX_Text(pDX, IDC_EDITRE2, m_sEdiTre2);
	DDX_Text(pDX, IDC_EDIUNO2, m_sEdiUno2);
	DDX_Text(pDX, IDC_EDISES, m_sEdiSes);
	DDX_Text(pDX, IDC_EDISES2, m_sEdiSes2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLisACF, CDialog)
	//{{AFX_MSG_MAP(CDlgLisACF)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_LISCIC, OnSelchangeLiscic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLisACF message handlers

BOOL CDlgLisACF::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here

	LOGFONT lf;
	memset( &lf, 0, sizeof(LOGFONT) );
	lf.lfHeight = 13;
	strcpy_s(lf.lfFaceName,"Courier New");
	m_Fuente1.CreateFontIndirect(&lf);
	m_CtrlEdiUno.SetFont(&m_Fuente1);
	m_CtrlEdiUno2.SetFont(&m_Fuente1);
	m_CtrlEdiDos.SetFont(&m_Fuente1);
	m_CtrlEdiDos2.SetFont(&m_Fuente1);
	m_CtrlEdiTre.SetFont(&m_Fuente1);
	m_CtrlEdiTre2.SetFont(&m_Fuente1);
	m_CtrlEdiCua.SetFont(&m_Fuente1);
	m_CtrlEdiCua2.SetFont(&m_Fuente1);
	m_CtrlEdiCin.SetFont(&m_Fuente1);
	m_CtrlEdiCin2.SetFont(&m_Fuente1);
	m_CtrlEdiSes.SetFont(&m_Fuente1);
	m_CtrlEdiSes2.SetFont(&m_Fuente1);
	m_CtrlLisCic.SetFont(&m_Fuente1);
	m_CtrlLisCHo.SetFont(&m_Fuente1);
	m_CtrlLisCH2.SetFont(&m_Fuente1);

	m_Color1 = RGB(255,255, 175);
	m_Pincel1.CreateSolidBrush(m_Color1);
//	CarDesCar1();
//	nTamRegg = sizeof(SEstCal);
	m_CtrlLisCic.SetCurSel(0);
	ActDatPan();
//	ActivaInactivaDialogo(false);
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CLisACaView::SelRegPr1()
{

}

HBRUSH CDlgLisACF::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID()==IDC_NIVGRA||
	    pWnd->GetDlgCtrlID()==IDC_LISCHO||
	    pWnd->GetDlgCtrlID()==IDC_LISCH2||
	    pWnd->GetDlgCtrlID()==IDC_EDIUNO||
	    pWnd->GetDlgCtrlID()==IDC_EDIDOS||
		pWnd->GetDlgCtrlID()==IDC_EDITRE||
		pWnd->GetDlgCtrlID()==IDC_EDICUA||
	    pWnd->GetDlgCtrlID()==IDC_EDICIN||
	    pWnd->GetDlgCtrlID()==IDC_EDISES||
	    pWnd->GetDlgCtrlID()==IDC_TEXUNO||
	    pWnd->GetDlgCtrlID()==IDC_TEXDOS||
		pWnd->GetDlgCtrlID()==IDC_TEXTRE||
		pWnd->GetDlgCtrlID()==IDC_TEXCUA||
	    pWnd->GetDlgCtrlID()==IDC_TEXCIN||
	    pWnd->GetDlgCtrlID()==IDC_TEXSES){
		
		pDC->SetBkColor(m_Color1);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)m_Pincel1.GetSafeHandle();
	}
	return hbr;
}

void CLisACaView::CarCursos()
{
	CFile bd1;	// representa la base de datos
	SEstCur General;
	CString	Cadena;
	CString szNombreFi = sDirGeng;
	
	szNombreFi = szNombreFi + "TCursos.ct1";

	bd1.Open(szNombreFi, CFile::modeRead);

	long nTamFil1 = (long)bd1.GetLength();		//  posicion final
	int nTamReg1  = sizeof(SEstCur);

	long nRegs = nTamFil1/(long)nTamReg1;	// numero de registros
	int i=0;
	// busqueda secuencial
	for(long nreg=0; nreg < nRegs; nreg++)
	{
		bd1.Read(&General, nTamReg1);
		if(General.m_szcodcur[0]!=255 && General.m_szcodcur[0]!=97) {
			strncpy(sArrCodCurg[i], (char *)General.m_szcodcur, 3);
			strncpy(sArrNomCurg[i], General.m_sznomcur, 32);
			strncpy(sArrCicCurg[i], General.m_szciccur, 2);
			i++;
		}
	}
	nNumTotCurg=i;
	bd1.Close();

}

void CLisACaView::CarDesCHo()
{
	CFile bd1;	// representa la base de datos
	SEstCHo General;
	CString	Cadena;
	CString szNombreFi = sDirGeng;
	int j, j1, j2;
	
	szNombreFi = szNombreFi + "TCHoras.ct1";

	bd1.Open(szNombreFi, CFile::modeRead);

	long nTamFil1 = (long)bd1.GetLength();		//  posicion final
	int nTamReg1  = sizeof(SEstCHo);

	long nRegs = nTamFil1/(long)nTamReg1;	// numero de registros
	int i=0;
	// busqueda secuencial
	for(long nreg=0; nreg < nRegs; nreg++)
	{
		bd1.Read(&General, nTamReg1);
		if(General.m_szcodcur[0]!=255 && General.m_szcodcur[0]!=97) {
			strncpy(sArrCCHorag[i], (char *)General.m_szcodcur, 3);
			sArrCTHCHog[i]= General.m_szcthora;
			strncpy(sArrCTACHog[i], General.m_szctaula,3);
			sArrNHCHorg[i]= General.m_sznumhor;
			for(j=0; j<nNumTotTHog; j++)
				if(sArrCTHorag[j]==General.m_szcthora)
					break;
			for(j1=0; j1<nNumTotCurg; j1++)
				if(!strncmp(sArrCodCurg[j1], (char *)General.m_szcodcur, 3))
					break;

			for(j2=0; j2<nNumTotTAug; j2++)
				if(!strncmp(sArrCTAulag[j2], General.m_szctaula, 3))
					break;
			Cadena.Format("%-3.3s %-30.30s %c %-8.8s %-3.3s %-12.12s %c", General.m_szcodcur,
				sArrNomCurg[j1], General.m_szcthora, sArrDTHorag[j],
				General.m_szctaula, sArrDTAulag[j2], General.m_sznumhor);
			m_CtrlLisCHo.AddString(Cadena);
			i++;
		}
	}
	nNumTotCHog = i;
	bd1.Close();

}

void CLisACaView::CarDatTHo()
{
	CFile bd1;	// representa la base de datos
	SEstTHo General;
	CString	Cadena;
	CString szNombreFi = sDirGeng;
	
	szNombreFi = szNombreFi + "TTHora.ct1";
	bd1.Open(szNombreFi, CFile::modeRead);

	long nTamFil1 = (long)bd1.GetLength();		//  posicion final
	int nTamReg1  = sizeof(SEstTHo);

	long nRegs = nTamFil1/(long)nTamReg1;	// numero de registros
	int i=0;
	// busqueda secuencial
	for(long nreg=0; nreg < nRegs; nreg++)
	{
		bd1.Read(&General, nTamReg1);
		if(General.m_szcthora!=255 && General.m_szcthora!=97) {
			sArrCTHorag[i] = General.m_szcthora;
			strncpy(sArrDTHorag[i], General.m_szdthora, 12);
			i++;
		}
	}
	nNumTotTHog=i;
	bd1.Close();
}

void CLisACaView::OnProAsihor() 
{
	// TODO: Add your command handler code here
	CString Cadena;
	char sCodCur[4];
	char sCGCDoc;
	int i, j, k;
	int j1, j2, j3;
	int nPosDoc;
	int nPosCur;
	int nNHAsig;			// Numero de horas que se va a asignar
	int nNHPDia;			// Numero horas primer dia
	int nNHSDia;			// Numero horas segundo dia
	int nCicCur;			// Ciclo del curso
	int nIniAul;			// Aula desde el cual se inicia la busqueda de disponibilidad
	i= j= k= 0;
	sCodCur[0]= sCGCDoc= 0;
	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotCDog; k++)
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		for(k=0; k<nNumTotCurg; k++)
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 + sArrCicCurg[nPosCur][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;

		nNHPDia = nNHSDia = 0;
		if(nArrNHCDocg[i]==6) {
			nNHPDia = nNHSDia = 3;
		}
		else {
			if(nArrNHCDocg[i]==5) {
				nNHPDia = 3;
				nNHSDia = 2;
			}
			else {
				if(nArrNHCDocg[i]==4) {
					nNHPDia = nNHSDia = 2;
				}
				else
					nNHPDia = nArrNHCDocg[i];
			}
		}
		nNHAsig = nNHPDia;
		if(nCicCur<4)		nIniAul=nCicCur;
		else
			if(nCicCur<7)		nIniAul=nCicCur-4;
			else
				if(nCicCur==7)		nIniAul=3;
				else
					if(nCicCur==8)		nIniAul=4;
					else				nIniAul=0;



/*
		else {
			nIniAul=0;
			if( (sArrHDAAulg[0][0][11][0]=='D' && sArrHDADocg[nPosDoc][0][11]=='D' &&
				sArrHDAAulg[0][0][12][0]=='D' && sArrHDADocg[nPosDoc][0][12]=='D') ||
				(sArrHDAAulg[0][1][11][0]=='D' && sArrHDADocg[nPosDoc][1][11]=='D' &&
				sArrHDAAulg[0][1][12][0]=='D' && sArrHDADocg[nPosDoc][1][12]=='D') ||
				(sArrHDAAulg[0][2][11][0]=='D' && sArrHDADocg[nPosDoc][2][11]=='D' &&
				sArrHDAAulg[0][2][12][0]=='D' && sArrHDADocg[nPosDoc][2][12]=='D') ||
				(sArrHDAAulg[0][3][11][0]=='D' && sArrHDADocg[nPosDoc][3][11]=='D' &&
				sArrHDAAulg[0][3][12][0]=='D' && sArrHDADocg[nPosDoc][3][12]=='D') )
				nIniAul=0;
			else
				if( (sArrHDAAulg[4][0][11][0]=='D' && sArrHDADocg[nPosDoc][0][11]=='D' &&
					sArrHDAAulg[4][0][12][0]=='D' && sArrHDADocg[nPosDoc][0][12]=='D') ||
					(sArrHDAAulg[4][1][11][0]=='D' && sArrHDADocg[nPosDoc][1][11]=='D' &&
					sArrHDAAulg[4][1][12][0]=='D' && sArrHDADocg[nPosDoc][1][12]=='D') ||
					(sArrHDAAulg[4][2][11][0]=='D' && sArrHDADocg[nPosDoc][2][11]=='D' &&
					sArrHDAAulg[4][2][12][0]=='D' && sArrHDADocg[nPosDoc][2][12]=='D') ||
					(sArrHDAAulg[4][3][11][0]=='D' && sArrHDADocg[nPosDoc][3][11]=='D' &&
					sArrHDAAulg[4][3][12][0]=='D' && sArrHDADocg[nPosDoc][3][12]=='D') )
					nIniAul=4;
				else
					if( (sArrHDAAulg[3][0][11][0]=='D' && sArrHDADocg[nPosDoc][0][11]=='D' &&
						sArrHDAAulg[3][0][12][0]=='D' && sArrHDADocg[nPosDoc][0][12]=='D') ||
						(sArrHDAAulg[3][1][11][0]=='D' && sArrHDADocg[nPosDoc][1][11]=='D' &&
						sArrHDAAulg[3][1][12][0]=='D' && sArrHDADocg[nPosDoc][1][12]=='D') ||
						(sArrHDAAulg[3][2][11][0]=='D' && sArrHDADocg[nPosDoc][2][11]=='D' &&
						sArrHDAAulg[3][2][12][0]=='D' && sArrHDADocg[nPosDoc][2][12]=='D') ||
						(sArrHDAAulg[3][3][11][0]=='D' && sArrHDADocg[nPosDoc][3][11]=='D' &&
						sArrHDAAulg[3][3][12][0]=='D' && sArrHDADocg[nPosDoc][3][12]=='D') )
						nIniAul=3;
					else
						if( (sArrHDAAulg[2][0][11][0]=='D' && sArrHDADocg[nPosDoc][0][11]=='D' &&
							sArrHDAAulg[2][0][12][0]=='D' && sArrHDADocg[nPosDoc][0][12]=='D') ||
							(sArrHDAAulg[2][1][11][0]=='D' && sArrHDADocg[nPosDoc][1][11]=='D' &&
							sArrHDAAulg[2][1][12][0]=='D' && sArrHDADocg[nPosDoc][1][12]=='D') ||
							(sArrHDAAulg[2][2][11][0]=='D' && sArrHDADocg[nPosDoc][2][11]=='D' &&
							sArrHDAAulg[2][2][12][0]=='D' && sArrHDADocg[nPosDoc][2][12]=='D') ||
							(sArrHDAAulg[2][3][11][0]=='D' && sArrHDADocg[nPosDoc][3][11]=='D' &&
							sArrHDAAulg[2][3][12][0]=='D' && sArrHDADocg[nPosDoc][3][12]=='D') )
							nIniAul=2;
						else
							if( (sArrHDAAulg[1][0][11][0]=='D' && sArrHDADocg[nPosDoc][0][11]=='D' &&
								sArrHDAAulg[1][0][12][0]=='D' && sArrHDADocg[nPosDoc][0][12]=='D') ||
								(sArrHDAAulg[1][1][11][0]=='D' && sArrHDADocg[nPosDoc][1][11]=='D' &&
								sArrHDAAulg[1][1][12][0]=='D' && sArrHDADocg[nPosDoc][1][12]=='D') ||
								(sArrHDAAulg[1][2][11][0]=='D' && sArrHDADocg[nPosDoc][2][11]=='D' &&
								sArrHDAAulg[1][2][12][0]=='D' && sArrHDADocg[nPosDoc][2][12]=='D') ||
								(sArrHDAAulg[1][3][11][0]=='D' && sArrHDADocg[nPosDoc][3][11]=='D' &&
								sArrHDAAulg[1][3][12][0]=='D' && sArrHDADocg[nPosDoc][3][12]=='D') )
								nIniAul=1;
			}
			*/
		CString xxyy;
		xxyy.Format("%s nIniAul %d",sArrCCCDocg[i],  nIniAul);
//		AfxMessageBox(xxyy);
		// Busca en las aulas si existe disponibilidad horaria
		for(j1=nIniAul; j1<nNumTotAulg; j1++) {
			if( strncmp(sArrCTACDog[i], sArrCTAAsig[j1], 3))
				continue;
			// Busca en los seis dias de la semana
			for(j2=0; j2<6; j2++) {
				for(j3=0; j3<(18-nNHAsig) && nNHAsig; j3++) {
					if( sArrHDAAulg[j1][j2][j3][0]=='D' &&	// Dispon. aula en el dia y hora
						sArrHDADocg[nPosDoc][j2][j3]=='D'&&	// Dispon. docente en el dia y hora
						sArrHDACDog[i][j2][j3]=='D' &&		// Curso pertenece al dia y hora
						sArrHDACicg[nCicCur][j2][j3][0]=='D' ) {	// Disp. en ciclo el dia y hora
						if(nNHAsig==1) {
							AfxMessageBox("Asigna 1 hora");
							strncpy(sArrHDAAulg[j1][j2][j3], sArrCCCDocg[i], 3);
							strncpy(sArrHDAAulg[j1][j2][j3]+3, sArrCDCDocg[i], 3);
							strncpy(sArrHDAAulg[j1][j2][j3]+6, sArrCGCDocg[i], 3);
							sArrHDADocg[nPosDoc][j2][j3]='A';
							strncpy(sArrHDACicg[nCicCur][j2][j3], sArrCCCDocg[i], 3);
							// Si la asignación es el primer dia
							if(nNHPDia) {
								nNHPDia = 0;
								nNHAsig = nNHSDia;
								j2+=1;
							}
							// Si la asignación es el segundo dia
							else {
								nNHSDia = 0;
							}
							break;
						}
						else {
							if(sArrHDAAulg[j1][j2][j3+1][0]=='D'&&
								sArrHDADocg[nPosDoc][j2][j3+1]=='D'&&
								sArrHDACDog[i][j2][j3+1]=='D' &&
								sArrHDACicg[nCicCur][j2][j3+1][0]=='D' ) {
								if(nNHAsig==2) {
									CString ccdd;
									ccdd.Format("Asigna 2 horas %s nCicCur %d j2 %d j3 %d",sArrCCCDocg[i], nCicCur, j2, j3 );
//									AfxMessageBox(ccdd);
									strncpy(sArrHDAAulg[j1][j2][j3], sArrCCCDocg[i], 3);
									strncpy(sArrHDAAulg[j1][j2][j3]+3, sArrCDCDocg[i], 3);
									strncpy(sArrHDAAulg[j1][j2][j3]+6, sArrCGCDocg[i], 3);
									sArrHDADocg[nPosDoc][j2][j3]='A';
									strncpy(sArrHDACicg[nCicCur][j2][j3], sArrCCCDocg[i], 3);
									strncpy(sArrHDAAulg[j1][j2][j3+1], sArrCCCDocg[i], 3);
									strncpy(sArrHDAAulg[j1][j2][j3+1]+3, sArrCDCDocg[i], 3);
									strncpy(sArrHDAAulg[j1][j2][j3+1]+6, sArrCGCDocg[i], 3);
									sArrHDADocg[nPosDoc][j2][j3+1]='A';
									strncpy(sArrHDACicg[nCicCur][j2][j3+1], sArrCCCDocg[i], 3);
									// Si la asignación es el primer dia
									if(nNHPDia) {
										nNHPDia = 0;
										nNHAsig = nNHSDia;
										j2+=1;
									}
									// Si la asignación es el segundo dia
									else {
										nNHSDia = 0;
									}
									break;
								}
								else {
									if(sArrHDAAulg[j1][j2][j3+2][0]=='D'&&
										sArrHDADocg[nPosDoc][j2][j3+2]=='D'&&
										sArrHDACDog[i][j2][j3+2]=='D' &&
										sArrHDACicg[nCicCur][j2][j3+2][0]=='D' ) {
										if(nNHAsig==3) {
											CString ccdd;
											ccdd.Format("Asigna 3 horas %s",sArrCCCDocg[i] );
//											AfxMessageBox(ccdd);
											strncpy(sArrHDAAulg[j1][j2][j3], sArrCCCDocg[i], 3);
											strncpy(sArrHDAAulg[j1][j2][j3]+3, sArrCDCDocg[i], 3);
											strncpy(sArrHDAAulg[j1][j2][j3]+6, sArrCGCDocg[i], 3);
											sArrHDADocg[nPosDoc][j2][j3]='A';
											strncpy(sArrHDACicg[nCicCur][j2][j3], sArrCCCDocg[i], 3);
											strncpy(sArrHDAAulg[j1][j2][j3+1], sArrCCCDocg[i], 3);
											strncpy(sArrHDAAulg[j1][j2][j3+1]+3, sArrCDCDocg[i], 3);
											strncpy(sArrHDAAulg[j1][j2][j3+1]+6, sArrCGCDocg[i], 3);
											sArrHDADocg[nPosDoc][j2][j3+1]='A';
											strncpy(sArrHDACicg[nCicCur][j2][j3+1], sArrCCCDocg[i], 3);
											strncpy(sArrHDAAulg[j1][j2][j3+2], sArrCCCDocg[i], 3);
											strncpy(sArrHDAAulg[j1][j2][j3+2]+3, sArrCDCDocg[i], 3);
											strncpy(sArrHDAAulg[j1][j2][j3+2]+6, sArrCGCDocg[i], 3);
											sArrHDADocg[nPosDoc][j2][j3+2]='A';
											strncpy(sArrHDACicg[nCicCur][j2][j3+2], sArrCCCDocg[i], 3);
											if(nNHPDia) {
												nNHPDia = 0;
												nNHAsig = nNHSDia;
												j2+=1;
											}
											else {
												nNHSDia = 0;
											}
											break;
										}
									}
								}
							}
						}
					}
				}
				if(nNHPDia==0 && nNHSDia == 0) {
					break;
				}
			}
			if(nNHPDia==0 && nNHSDia == 0) {
				break;
			}
		}
		CString abc1;
		int j4, j5, j6;
		j4=j5=j6=0;
		Cadena = "";
		for(j4=0; j4<nNumTotAulg; j4++) {
			for(j5=0; j5<6; j5++) {
				for(j6=0; j6<18; j6++) {
					if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
						if(Cadena=="")
							abc1.Format("%s %s %s %dh - %d %d %s  ",
							sArrCCCDocg[i],sArrCGCDocg[i],sArrCDCDocg[i],nArrNHCDocg[i],
							j5, j6, sArrCodAulg[j4]);
						else 
							abc1.Format("%d %d %s  ", j5, j6, sArrCodAulg[j4]);

						Cadena = Cadena + abc1;
//						AfxMessageBox(abc1);
//						m_CtrlLisHor.AddString(abc1);
					}
				}
			}
		}
		m_CtrlLisHor.AddString(Cadena);
	}
}

void CLisACaView::OnUpdateProAsihor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(sArrHDAAulg[0][0][0][0]=='D' && sArrHDAAulg[0][0][1][0]=='D' &&
		sArrHDAAulg[0][0][3][0]=='D' && sArrHDAAu2g[0][0][0][0]=='D' &&
		sArrHDAAu2g[0][0][1][0]=='D' && sArrHDAAu2g[0][0][3][0]=='D' );		
}

void CLisACaView::OnProConcil() 
{
	// TODO: Add your command handler code here
	nCicAcag=0;

	CDlgLisACF Dlg1;
	Dlg1.DoModal();
	
}

void CLisACaView::OnUpdateProConcil(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CDlgLisACF::ActDatPan()
{
	// TODO: Add your command handler code here
	CString Cadena, Cadena2;;
	char sCad[6][18][21];
	char sCad2[6][18][21];
	char sCodCur[4];
	char sCGCDoc;
	int i, j, k;
	int nPosCur;
	int nCicCur;
	int j4, j5, j6, j7;
	CString abc1;

	strcpy_s(sArrDiaSemg[0], "Lunes");
	strcpy_s(sArrDiaSemg[1], "Martes");
	strcpy_s(sArrDiaSemg[2], "Miercoles");
	strcpy_s(sArrDiaSemg[3], "Jueves");
	strcpy_s(sArrDiaSemg[4], "Viernes");
	strcpy_s(sArrDiaSemg[5], "Sabado");
	strcpy_s(sArrDiaSemg[6], "Domingo");

	for(j5=0; j5<6; j5++)
		for(j6=0; j6<18; j6++)
			for(j7=0; j7<21; j7++)
			sCad[j5][j6][j7]= sCad2[j5][j6][j7] = 0;
	i= j= k= 0;
	sCodCur[0]= sCGCDoc= 0;
	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotCurg; k++)
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;
		j4=j5=j6=0;
		Cadena = "";
		if(nCicCur == 0) {
			for(j5=0; j5<6; j5++) {
				for(j4=0; j4<nNumTotAulg; j4++) {
					for(j6=0; j6<18; j6++) {
						if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
							!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
							!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
							if(sCad[j5][j6][0]==0) {
								strncpy(sCad[j5][j6], sArrCCCDocg[i], 3);
								sCad[j5][j6][3]=' ';
								strncpy(sCad[j5][j6]+4, sArrCGCDocg[i], 3);
								sCad[j5][j6][7]=' ';
								strncpy(sCad[j5][j6]+8, sArrCDCDocg[i], 3);
								sCad[j5][j6][11]=' ';
								strncpy(sCad[j5][j6]+12, sArrCodAulg[j4], 2);
								sCad[j5][j6][14]=0;
								strncpy(sCad2[j5][j6], sArrNomCurg[nPosCur], 16);
							}
						}
						if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
							!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
							!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
							Cadena2.Format("%-5.5s Hora %d %s %-20.20s %s %s %s",
								sArrDiaSemg[j5], j6,
								sArrCCCDocg[i], sArrNomCurg[nPosCur], sArrCGCDocg[i],
								sArrCDCDocg[i], sArrCodAulg[j4]); 
							m_CtrlLisCHo.AddString(Cadena2);
						}
						if(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
							!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
							!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
							Cadena2.Format("%-5.5s Hora %d %s %-20.20s %s %s %s",
								sArrDiaSemg[j5], j6,
								sArrCCCDocg[i], sArrNomCurg[nPosCur], sArrCGCDocg[i],
								sArrCDCDocg[i], sArrCodAulg[j4]); 
							m_CtrlLisCH2.AddString(Cadena2);
						}
					}
				}
			}
		}
	}
	i= j= k= 0;
	sCodCur[0]= sCGCDoc= 0;
	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotCurg; k++)
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;
		j4=j5=j6=0;
		Cadena = "";
		if(nCicCur == 0) {
			for(j5=0; j5<6; j5++) {
				for(j4=0; j4<nNumTotAulg; j4++) {
					for(j6=0; j6<18; j6++) {
						if(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
							!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
							!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
							if(sCad[j5][j6][0]==0) {
								strncpy(sCad[j5][j6], sArrCCCDocg[i], 3);
								sCad[j5][j6][3]=' ';
								strncpy(sCad[j5][j6]+4, sArrCGCDocg[i], 3);
								sCad[j5][j6][7]=' ';
								strncpy(sCad[j5][j6]+8, sArrCDCDocg[i], 3);
								sCad[j5][j6][11]=' ';
								strncpy(sCad[j5][j6]+12, sArrCodAulg[j4], 2);
								sCad[j5][j6][14]=' ';
								strcpy(sCad[j5][j6]+15, "*M-2*");
								strncpy(sCad2[j5][j6], sArrNomCurg[nPosCur], 16);
							}
						}
					}
				}
			}
		}
	}
	m_sEdiUno.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][0], sCad2[1][0], sCad2[2][0], sCad2[3][0], sCad2[4][0], sCad2[5][0]);
	m_sEdiUno2.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad[0][0]+4, sCad[1][0]+4,	sCad[2][0]+4, sCad[3][0]+4,	sCad[4][0]+4, sCad[5][0]+4);
	m_sEdiDos.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][1], sCad2[1][1], sCad2[2][1], sCad2[3][1], sCad2[4][1], sCad2[5][1]);
	m_sEdiDos2.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad[0][1]+4, sCad[1][1]+4,	sCad[2][1]+4, sCad[3][1]+4, sCad[4][1]+4, sCad[5][1]+4);
	m_sEdiTre.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][2], sCad2[1][2], sCad2[2][2], sCad2[3][2],	sCad2[4][2], sCad2[5][2]);
	m_sEdiTre2.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad[0][2]+4, sCad[1][2]+4,	sCad[2][2]+4, sCad[3][2]+4,	sCad[4][2]+4, sCad[5][2]+4);
	m_sEdiCua.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][3], sCad2[1][3], sCad2[2][3], sCad2[3][3], sCad2[4][3], sCad2[5][3]);
	m_sEdiCua2.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad[0][3]+4, sCad[1][3]+4,	sCad[2][3]+4, sCad[3][3]+4,	sCad[4][3]+4, sCad[5][3]+4);
	m_sEdiCin.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][4], sCad2[1][4], sCad2[2][4], sCad2[3][4], sCad2[4][4], sCad2[5][4]);
	m_sEdiCin2.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad[0][4]+4, sCad[1][4]+4,	sCad[2][4]+4, sCad[3][4]+4,	sCad[4][4]+4, sCad[5][4]+4);
	m_sEdiSes.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][5], sCad2[1][5], sCad2[2][5], sCad2[3][5], sCad2[4][5], sCad2[5][5]);
	m_sEdiSes2.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad[0][5]+4, sCad[1][5]+4,	sCad[2][5]+4, sCad[3][5]+4,	sCad[4][5]+4, sCad[5][5]+4);


}

void CDlgLisACF::OnSelchangeLiscic() 
{
	// TODO: Add your control notification handler code here
	CString Cadena, Cadena2;
	char sCad[6][18][21];
	char sCad2[6][18][21];
	char sCodCur[4];
	char sCGCDoc;
	int i, j, k;
	int nPosCur;
	int nCicCur;
	int j4, j5, j6, j7;
	CString abc1;
	int nDifHor;
	nCicAcag = m_CtrlLisCic.GetCurSel();
	m_CtrlLisCHo.ResetContent();
	m_CtrlLisCH2.ResetContent();
	for(j5=0; j5<6; j5++)
		for(j6=0; j6<18; j6++)
			for(j7=0; j7<21; j7++)
			sCad[j5][j6][j7]= sCad2[j5][j6][j7] = 0;
	i= j= k= 0;
	sCodCur[0]= sCGCDoc= 0;
	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotCurg; k++)
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;

		j4=j5=j6=0;
		Cadena = "";
		if(nCicCur == nCicAcag) {
			for(j5=0; j5<6; j5++) {
				for(j4=0; j4<nNumTotAulg; j4++) {
					for(j6=0; j6<18; j6++) {
						if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
							!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
							!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
							if(sCad[j5][j6][0]==0) {
								strncpy(sCad[j5][j6], sArrCCCDocg[i], 3);
								sCad[j5][j6][3]=' ';
								strncpy(sCad[j5][j6]+4, sArrCGCDocg[i], 3);
								sCad[j5][j6][7]=' ';
								strncpy(sCad[j5][j6]+8, sArrCDCDocg[i], 3);
								sCad[j5][j6][11]=' ';
								strncpy(sCad[j5][j6]+12, sArrCodAulg[j4], 2);
								sCad[j5][j6][14]=0;
								strncpy(sCad2[j5][j6], sArrNomCurg[nPosCur], 16);
							}
						}
						if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
							!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
							!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
							Cadena2.Format("%-5.5s Hora %d %s %-20.20s %s %s %s",
								sArrDiaSemg[j5], j6,
								sArrCCCDocg[i], sArrNomCurg[nPosCur], sArrCGCDocg[i],
								sArrCDCDocg[i], sArrCodAulg[j4]); 
							m_CtrlLisCHo.AddString(Cadena2);
						}
						if(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
							!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
							!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
							Cadena2.Format("%-5.5s Hora %d %s %-20.20s %s %s %s",
								sArrDiaSemg[j5], j6,
								sArrCCCDocg[i], sArrNomCurg[nPosCur], sArrCGCDocg[i],
								sArrCDCDocg[i], sArrCodAulg[j4]); 
							m_CtrlLisCH2.AddString(Cadena2);
						}
					}
				}
			}
		}
	}
	i= j= k= 0;
	sCodCur[0]= sCGCDoc= 0;
	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotCurg; k++)
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;

		j4=j5=j6=0;
		Cadena = "";
		if(nCicCur == nCicAcag) {
			for(j5=0; j5<6; j5++) {
				for(j4=0; j4<nNumTotAulg; j4++) {
					for(j6=0; j6<18; j6++) {
						if(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
							!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
							!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
							if(sCad[j5][j6][0]==0) {
								strncpy(sCad[j5][j6], sArrCCCDocg[i], 3);
								sCad[j5][j6][3]=' ';
								strncpy(sCad[j5][j6]+4, sArrCGCDocg[i], 3);
								sCad[j5][j6][7]=' ';
								strncpy(sCad[j5][j6]+8, sArrCDCDocg[i], 3);
								sCad[j5][j6][11]=' ';
								strncpy(sCad[j5][j6]+12, sArrCodAulg[j4], 2);
								sCad[j5][j6][14]=' ';
								strcpy(sCad[j5][j6]+15, "*M-2*");
								strncpy(sCad2[j5][j6], sArrNomCurg[nPosCur], 16);
							}
						}
					}
				}
			}
		}
	}
	nDifHor=0;
	if(nCicAcag<4) {
		nDifHor=0;
		SetDlgItemText(IDC_TEXUNO, "08:00-08:50");
		SetDlgItemText(IDC_TEXDOS, "08:50-09:40");
		SetDlgItemText(IDC_TEXTRE, "09:40-10:30");
		SetDlgItemText(IDC_TEXCUA, "10:30-11:20");
		SetDlgItemText(IDC_TEXCIN, "11:20-12:10");
		SetDlgItemText(IDC_TEXSES, "12:10-13:00");
	}
	else {
		if(nCicAcag<7) {
			nDifHor=6;
			SetDlgItemText(IDC_TEXUNO, "13:00-13:50");
			SetDlgItemText(IDC_TEXDOS, "13:50-14:40");
			SetDlgItemText(IDC_TEXTRE, "14:40-15:30");
			SetDlgItemText(IDC_TEXCUA, "15:30-16:20");
			SetDlgItemText(IDC_TEXCIN, "16:20-17:10");
			SetDlgItemText(IDC_TEXSES, "17:10-18:00");
		}
		else {
			nDifHor=11;
			SetDlgItemText(IDC_TEXUNO, "17:10-18:00");
			SetDlgItemText(IDC_TEXDOS, "18:00-18:50");
			SetDlgItemText(IDC_TEXTRE, "18:50-19:40");
			SetDlgItemText(IDC_TEXCUA, "19:40-20:30");
			SetDlgItemText(IDC_TEXCIN, "20:30-21:20");
			SetDlgItemText(IDC_TEXSES, "21:20-22:10");
		}
	}

	m_sEdiUno.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][0+nDifHor], sCad2[1][0+nDifHor], sCad2[2][0+nDifHor], sCad2[3][0+nDifHor], sCad2[4][0+nDifHor], sCad2[5][0+nDifHor]);
	m_sEdiUno2.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad[0][0+nDifHor]+4, sCad[1][0+nDifHor]+4,	sCad[2][0+nDifHor]+4, sCad[3][0+nDifHor]+4,	sCad[4][0+nDifHor]+4, sCad[5][0+nDifHor]+4);
	m_sEdiDos.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][1+nDifHor], sCad2[1][1+nDifHor], sCad2[2][1+nDifHor], sCad2[3][1+nDifHor], sCad2[4][1+nDifHor], sCad2[5][1+nDifHor]);
	m_sEdiDos2.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad[0][1+nDifHor]+4, sCad[1][1+nDifHor]+4,	sCad[2][1+nDifHor]+4, sCad[3][1+nDifHor]+4, sCad[4][1+nDifHor]+4, sCad[5][1+nDifHor]+4);
	m_sEdiTre.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][2+nDifHor], sCad2[1][2+nDifHor], sCad2[2][2+nDifHor], sCad2[3][2+nDifHor],	sCad2[4][2+nDifHor], sCad2[5][2+nDifHor]);
	m_sEdiTre2.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad[0][2+nDifHor]+4, sCad[1][2+nDifHor]+4,	sCad[2][2+nDifHor]+4, sCad[3][2+nDifHor]+4,	sCad[4][2+nDifHor]+4, sCad[5][2+nDifHor]+4);
	m_sEdiCua.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][3+nDifHor], sCad2[1][3+nDifHor], sCad2[2][3+nDifHor], sCad2[3][3+nDifHor], sCad2[4][3+nDifHor], sCad2[5][3+nDifHor]);
	m_sEdiCua2.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad[0][3+nDifHor]+4, sCad[1][3+nDifHor]+4,	sCad[2][3+nDifHor]+4, sCad[3][3+nDifHor]+4,	sCad[4][3+nDifHor]+4, sCad[5][3+nDifHor]+4);
	m_sEdiCin.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][4+nDifHor], sCad2[1][4+nDifHor], sCad2[2][4+nDifHor], sCad2[3][4+nDifHor], sCad2[4][4+nDifHor], sCad2[5][4+nDifHor]);
	m_sEdiCin2.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad[0][4+nDifHor]+4, sCad[1][4+nDifHor]+4,	sCad[2][4+nDifHor]+4, sCad[3][4+nDifHor]+4,	sCad[4][4+nDifHor]+4, sCad[5][4+nDifHor]+4);
	m_sEdiSes.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][5+nDifHor], sCad2[1][5+nDifHor], sCad2[2][5+nDifHor], sCad2[3][5+nDifHor], sCad2[4][5+nDifHor], sCad2[5][5+nDifHor]);
	m_sEdiSes2.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad[0][5+nDifHor]+4, sCad[1][5+nDifHor]+4,	sCad[2][5+nDifHor]+4, sCad[3][5+nDifHor]+4,	sCad[4][5+nDifHor]+4, sCad[5][5+nDifHor]+4);

	UpdateData(false);
	
}
/////////////////////////////////////////////////////////////////////////////
// CDlgConAul dialog


CDlgConAul::CDlgConAul(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConAul::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConAul)
	m_sEdiCin = _T("");
	m_sEdiCua = _T("");
	m_sEdiDos = _T("");
	m_sEdiTre = _T("");
	m_sEdiUno = _T("");
	m_sEdiDie = _T("");
	m_sEdiNue = _T("");
	m_sEdiOch = _T("");
	m_sEdiSei = _T("");
	m_sEdiSie = _T("");
	m_sEdiDoc = _T("");
	m_sEdiOnc = _T("");
	m_sEdiCat = _T("");
	m_sEdiTrc = _T("");
	m_sEdiQui = _T("");
	m_sEdiDic = _T("");
	m_sEdiDis = _T("");
	//}}AFX_DATA_INIT
}


void CDlgConAul::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConAul)
	DDX_Control(pDX, IDC_EDIDIS, m_CtrlEdiDis);
	DDX_Control(pDX, IDC_EDIDIC, m_CtrlEdiDic);
	DDX_Control(pDX, IDC_EDITRC, m_CtrlEdiTrc);
	DDX_Control(pDX, IDC_EDIQUI, m_CtrlEdiQui);
	DDX_Control(pDX, IDC_EDICAT, m_CtrlEdiCat);
	DDX_Control(pDX, IDC_EDIONC, m_CtrlEdiOnc);
	DDX_Control(pDX, IDC_EDIDOC, m_CtrlEdiDoc);
	DDX_Control(pDX, IDC_EDISIE, m_CtrlEdiSie);
	DDX_Control(pDX, IDC_EDISEI, m_CtrlEdiSei);
	DDX_Control(pDX, IDC_EDIOCH, m_CtrlEdiOch);
	DDX_Control(pDX, IDC_EDINUE, m_CtrlEdiNue);
	DDX_Control(pDX, IDC_EDIDIE, m_CtrlEdiDie);
	DDX_Control(pDX, IDC_EDIUNO, m_CtrlEdiUno);
	DDX_Control(pDX, IDC_EDITRE, m_CtrlEdiTre);
	DDX_Control(pDX, IDC_EDIDOS, m_CtrlEdiDos);
	DDX_Control(pDX, IDC_EDICUA, m_CtrlEdiCua);
	DDX_Control(pDX, IDC_EDICIN, m_CtrlEdiCin);
	DDX_Control(pDX, IDC_LISAULAS, m_CtrlLisAulas);
	DDX_Text(pDX, IDC_EDICIN, m_sEdiCin);
	DDX_Text(pDX, IDC_EDICUA, m_sEdiCua);
	DDX_Text(pDX, IDC_EDIDOS, m_sEdiDos);
	DDX_Text(pDX, IDC_EDITRE, m_sEdiTre);
	DDX_Text(pDX, IDC_EDIUNO, m_sEdiUno);
	DDX_Text(pDX, IDC_EDIDIE, m_sEdiDie);
	DDX_Text(pDX, IDC_EDINUE, m_sEdiNue);
	DDX_Text(pDX, IDC_EDIOCH, m_sEdiOch);
	DDX_Text(pDX, IDC_EDISEI, m_sEdiSei);
	DDX_Text(pDX, IDC_EDISIE, m_sEdiSie);
	DDX_Text(pDX, IDC_EDIDOC, m_sEdiDoc);
	DDX_Text(pDX, IDC_EDIONC, m_sEdiOnc);
	DDX_Text(pDX, IDC_EDICAT, m_sEdiCat);
	DDX_Text(pDX, IDC_EDITRC, m_sEdiTrc);
	DDX_Text(pDX, IDC_EDIQUI, m_sEdiQui);
	DDX_Text(pDX, IDC_EDIDIC, m_sEdiDic);
	DDX_Text(pDX, IDC_EDIDIS, m_sEdiDis);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConAul, CDialog)
	//{{AFX_MSG_MAP(CDlgConAul)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_LISAULAS, OnSelchangeLisaulas)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConAul message handlers

void CLisACaView::OnProConaul() 
{
	// TODO: Add your command handler code here
	nCicAcag=0;

	CDlgConAul Dlg1;
	Dlg1.DoModal();
	
}

void CLisACaView::OnUpdateProConaul(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

HBRUSH CDlgConAul::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID()==IDC_LISAULAS||
	    pWnd->GetDlgCtrlID()==IDC_EDIUNO||
	    pWnd->GetDlgCtrlID()==IDC_EDIDOS||
		pWnd->GetDlgCtrlID()==IDC_EDITRE||
		pWnd->GetDlgCtrlID()==IDC_EDICUA||
	    pWnd->GetDlgCtrlID()==IDC_EDICIN||
	    pWnd->GetDlgCtrlID()==IDC_EDISEI||
	    pWnd->GetDlgCtrlID()==IDC_TEXUNO||
	    pWnd->GetDlgCtrlID()==IDC_TEXDOS||
		pWnd->GetDlgCtrlID()==IDC_TEXTRE||
		pWnd->GetDlgCtrlID()==IDC_TEXCUA||
	    pWnd->GetDlgCtrlID()==IDC_TEXCIN||
	    pWnd->GetDlgCtrlID()==IDC_TEXSEI){
		
		pDC->SetBkColor(m_Color1);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)m_Pincel1.GetSafeHandle();
	}
	if (pWnd->GetDlgCtrlID()==IDC_EDISIE||
		pWnd->GetDlgCtrlID()==IDC_EDIOCH||
		pWnd->GetDlgCtrlID()==IDC_EDINUE||
	    pWnd->GetDlgCtrlID()==IDC_EDIDIE||
		pWnd->GetDlgCtrlID()==IDC_EDIONC||
	    pWnd->GetDlgCtrlID()==IDC_EDIDOC||
	    pWnd->GetDlgCtrlID()==IDC_EDITRC||
		pWnd->GetDlgCtrlID()==IDC_EDICAT||
	    pWnd->GetDlgCtrlID()==IDC_EDIQUI||
	    pWnd->GetDlgCtrlID()==IDC_EDIDIS||
	    pWnd->GetDlgCtrlID()==IDC_EDIDIC||
	    pWnd->GetDlgCtrlID()==IDC_TEXSIE||
		pWnd->GetDlgCtrlID()==IDC_TEXOCH||
		pWnd->GetDlgCtrlID()==IDC_TEXNUE||
	    pWnd->GetDlgCtrlID()==IDC_TEXDIE||
		pWnd->GetDlgCtrlID()==IDC_TEXONC||
	    pWnd->GetDlgCtrlID()==IDC_TEXDOC||
	    pWnd->GetDlgCtrlID()==IDC_TEXTRC||
		pWnd->GetDlgCtrlID()==IDC_TEXCAT||
	    pWnd->GetDlgCtrlID()==IDC_TEXQUI||
		pWnd->GetDlgCtrlID()==IDC_TEXDIS||
	    pWnd->GetDlgCtrlID()==IDC_TEXDIC){




		
		pDC->SetBkColor(m_Color2);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)m_Pincel2.GetSafeHandle();
	}
	return hbr;
}

BOOL CDlgConAul::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here

	LOGFONT lf;
	memset( &lf, 0, sizeof(LOGFONT) );
	lf.lfHeight = 13;
	strcpy_s(lf.lfFaceName,"Courier New");
	m_Fuente1.CreateFontIndirect(&lf);
	m_CtrlEdiUno.SetFont(&m_Fuente1);
	m_CtrlEdiDos.SetFont(&m_Fuente1);
	m_CtrlEdiTre.SetFont(&m_Fuente1);
	m_CtrlEdiCua.SetFont(&m_Fuente1);
	m_CtrlEdiCin.SetFont(&m_Fuente1);
	m_CtrlEdiSei.SetFont(&m_Fuente1);
	m_CtrlEdiSie.SetFont(&m_Fuente1);
	m_CtrlEdiOch.SetFont(&m_Fuente1);
	m_CtrlEdiNue.SetFont(&m_Fuente1);
	m_CtrlEdiDie.SetFont(&m_Fuente1);
	m_CtrlEdiOnc.SetFont(&m_Fuente1);
	m_CtrlEdiDoc.SetFont(&m_Fuente1);
	m_CtrlEdiTrc.SetFont(&m_Fuente1);
	m_CtrlEdiCat.SetFont(&m_Fuente1);
	m_CtrlEdiQui.SetFont(&m_Fuente1);
	m_CtrlEdiDis.SetFont(&m_Fuente1);
	m_CtrlEdiDic.SetFont(&m_Fuente1);
	m_CtrlLisAulas.SetFont(&m_Fuente1);

	m_Color1 = RGB(255,255, 175);
	m_Pincel1.CreateSolidBrush(m_Color1);
	m_Color2 = RGB(251,251, 238);
	m_Pincel2.CreateSolidBrush(m_Color2);
	CarDesAul();
//	CarDesCar1();
//	nTamRegg = sizeof(SEstCal);
	m_CtrlLisAulas.SetCurSel(0);
	ActDatPan();
//	ActivaInactivaDialogo(false);
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control

}

void CDlgConAul::CarDesAul()
{
	CString Cadena;
	int j4;

	for(j4=0; j4<nNumTotAulg; j4++) {
		Cadena.Format("%-2.2s %-3.3s",sArrCodAulg[j4], sArrCTAAsig[j4]);
		m_CtrlLisAulas.AddString(Cadena);
	}

}

void CDlgConAul::ActDatPan()
{
	CString Cadena;
	char sCad[6][18][12];
	char sCad2[6][18][17];
	char sCodCur[4];
	char sCGCDoc;
	int i, j, k;
	int nPosCur;
	int j4, j5, j6, j7;
	CString abc1;

	for(j5=0; j5<6; j5++)
		for(j6=0; j6<18; j6++)
			for(j7=0; j7<6; j7++)
			sCad[j5][j6][j7]= sCad2[j5][j6][j7] = 0;
	i= j= k= 0;
	sCodCur[0]= sCGCDoc= 0;



	Cadena = "";
	for(j4=0; j4<nNumTotAulg; j4++) {
		if(!strncmp(sArrCodAulg[j4], "A1", 2) ) {
			for(j5=0; j5<6; j5++) {
				for(j6=0; j6<18; j6++) {
					if(sArrHDAAulg[j4][j5][j6][0]!='D') {
						for(k=0; k<nNumTotCurg; k++)
							if(!strncmp(sArrHDAAulg[j4][j5][j6], sArrCodCurg[k], 3)) {
								nPosCur = k;
								break;
							}
						strncpy(sCad[j5][j6], sArrHDAAulg[j4][j5][j6], 3);
						sCad[j5][j6][3]=' ';
						strncpy(sCad[j5][j6]+4, sArrCDCDocg[i], 3);
						sCad[j5][j6][7]=' ';
						strncpy(sCad[j5][j6]+8, sArrCodAulg[j4], 3);
						strncpy(sCad2[j5][j6], sArrNomCurg[nPosCur], 16);
					}
				}
			}
		}
	}

	m_sEdiUno.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][0], sCad2[1][0], sCad2[2][0], sCad2[3][0], sCad2[4][0], sCad2[5][0]);
	m_sEdiDos.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][1], sCad2[1][1], sCad2[2][1], sCad2[3][1], sCad2[4][1], sCad2[5][1]);
	m_sEdiTre.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][2], sCad2[1][2], sCad2[2][2], sCad2[3][2],	sCad2[4][2], sCad2[5][2]);
	m_sEdiCua.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][3], sCad2[1][3], sCad2[2][3], sCad2[3][3], sCad2[4][3], sCad2[5][3]);
	m_sEdiCin.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][4], sCad2[1][4], sCad2[2][4], sCad2[3][4], sCad2[4][4], sCad2[5][4]);
	m_sEdiSei.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][5], sCad2[1][5], sCad2[2][5], sCad2[3][5], sCad2[4][5], sCad2[5][5]);
	m_sEdiSie.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][6], sCad2[1][6], sCad2[2][6], sCad2[3][6], sCad2[4][6], sCad2[5][6]);
	m_sEdiOch.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][7], sCad2[1][7], sCad2[2][7], sCad2[3][7],	sCad2[4][7], sCad2[5][7]);
	m_sEdiNue.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][8], sCad2[1][8], sCad2[2][8], sCad2[3][8], sCad2[4][8], sCad2[5][8]);
	m_sEdiDie.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][9], sCad2[1][9], sCad2[2][9], sCad2[3][9], sCad2[4][9], sCad2[5][9]);
	m_sEdiOnc.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][10], sCad2[1][10], sCad2[2][10], sCad2[3][10], sCad2[4][10], sCad2[5][10]);
	m_sEdiDoc.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][11], sCad2[1][11], sCad2[2][11], sCad2[3][11], sCad2[4][11], sCad2[5][11]);
	m_sEdiTrc.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][12], sCad2[1][12], sCad2[2][12], sCad2[3][12], sCad2[4][12], sCad2[5][12]);
	m_sEdiCat.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][13], sCad2[1][13], sCad2[2][13], sCad2[3][13], sCad2[4][13], sCad2[5][13]);
	m_sEdiQui.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][14], sCad2[1][14], sCad2[2][14], sCad2[3][14], sCad2[4][14], sCad2[5][14]);
	m_sEdiDis.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][15], sCad2[1][15], sCad2[2][15], sCad2[3][15], sCad2[4][15], sCad2[5][15]);
	m_sEdiDic.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][16], sCad2[1][16], sCad2[2][16], sCad2[3][16], sCad2[4][16], sCad2[5][16]);
}

void CDlgConAul::OnSelchangeLisaulas() 
{
	// TODO: Add your control notification handler code here
	char sCad11[61];


	CString Cadena;
	char sCad[6][18][12];
	char sCad2[6][18][17];
	char sCodCur[4];
	char sCGCDoc;
	int i, j, k;
	int nPosCur;
	int j4, j5, j6, j7;
	CString abc1;

	m_CtrlLisAulas.GetLBText(m_CtrlLisAulas.GetCurSel(), sCad11);

	for(j5=0; j5<6; j5++)
		for(j6=0; j6<18; j6++)
			for(j7=0; j7<6; j7++)
			sCad[j5][j6][j7]= sCad2[j5][j6][j7] = 0;
	i= j= k= 0;
	sCodCur[0]= sCGCDoc= 0;



	Cadena = "";
	for(j4=0; j4<nNumTotAulg; j4++) {
		if(!strncmp(sArrCodAulg[j4], sCad11 , 2) ) {
			for(j5=0; j5<6; j5++) {
				for(j6=0; j6<18; j6++) {
					if(sArrHDAAulg[j4][j5][j6][0]!='D') {
						for(k=0; k<nNumTotCurg; k++)
							if(!strncmp(sArrHDAAulg[j4][j5][j6], sArrCodCurg[k], 3)) {
								nPosCur = k;
								break;
							}
						strncpy(sCad[j5][j6], sArrHDAAulg[j4][j5][j6], 3);
						sCad[j5][j6][3]=' ';
						strncpy(sCad[j5][j6]+4, sArrCDCDocg[i], 3);
						sCad[j5][j6][7]=' ';
						strncpy(sCad[j5][j6]+8, sArrCodAulg[j4], 3);
						strncpy(sCad2[j5][j6], sArrNomCurg[nPosCur], 16);
					}
				}
			}
		}
	}

	m_sEdiUno.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][0], sCad2[1][0], sCad2[2][0], sCad2[3][0], sCad2[4][0], sCad2[5][0]);
	m_sEdiDos.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][1], sCad2[1][1], sCad2[2][1], sCad2[3][1], sCad2[4][1], sCad2[5][1]);
	m_sEdiTre.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][2], sCad2[1][2], sCad2[2][2], sCad2[3][2],	sCad2[4][2], sCad2[5][2]);
	m_sEdiCua.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][3], sCad2[1][3], sCad2[2][3], sCad2[3][3], sCad2[4][3], sCad2[5][3]);
	m_sEdiCin.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][4], sCad2[1][4], sCad2[2][4], sCad2[3][4], sCad2[4][4], sCad2[5][4]);
	m_sEdiSei.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][5], sCad2[1][5], sCad2[2][5], sCad2[3][5], sCad2[4][5], sCad2[5][5]);
	m_sEdiSie.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][6], sCad2[1][6], sCad2[2][6], sCad2[3][6], sCad2[4][6], sCad2[5][6]);
	m_sEdiOch.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][7], sCad2[1][7], sCad2[2][7], sCad2[3][7],	sCad2[4][7], sCad2[5][7]);
	m_sEdiNue.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][8], sCad2[1][8], sCad2[2][8], sCad2[3][8], sCad2[4][8], sCad2[5][8]);
	m_sEdiDie.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][9], sCad2[1][9], sCad2[2][9], sCad2[3][9], sCad2[4][9], sCad2[5][9]);
	m_sEdiOnc.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][10], sCad2[1][10], sCad2[2][10], sCad2[3][10], sCad2[4][10], sCad2[5][10]);
	m_sEdiDoc.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][11], sCad2[1][11], sCad2[2][11], sCad2[3][11], sCad2[4][11], sCad2[5][11]);
	m_sEdiTrc.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][12], sCad2[1][12], sCad2[2][12], sCad2[3][12], sCad2[4][12], sCad2[5][12]);
	m_sEdiCat.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][13], sCad2[1][13], sCad2[2][13], sCad2[3][13], sCad2[4][13], sCad2[5][13]);
	m_sEdiQui.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][14], sCad2[1][14], sCad2[2][14], sCad2[3][14], sCad2[4][14], sCad2[5][14]);
	m_sEdiDis.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][15], sCad2[1][15], sCad2[2][15], sCad2[3][15], sCad2[4][15], sCad2[5][15]);
	m_sEdiDic.Format("%-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s  %-16.16s",
		sCad2[0][16], sCad2[1][16], sCad2[2][16], sCad2[3][16], sCad2[4][16], sCad2[5][16]);

	UpdateData(false);

	
}

void CDlgLisACa::ActDatPan()
{
	CString Cadena;
	int i, k;
	int nPosDoc;
	int nPosCur;
	int nCicCur;
	char sDiaSem[7][12];
	char sDesHorIni[20][6];
	char sDesHorFin[20][6];
	int nDia, nHorIni, nHorFin;
	int j4, j5, j6;
	char sCad[121];
	strcpy_s(sDiaSem[0], "Lunes");
	strcpy_s(sDiaSem[1], "Martes");
	strcpy_s(sDiaSem[2], "Miercoles");
	strcpy_s(sDiaSem[3], "Jueves");
	strcpy_s(sDiaSem[4], "Viernes");
	strcpy_s(sDiaSem[5], "Sabado");
	strcpy_s(sDiaSem[6], "Domingo");
	strcpy_s(sDesHorIni[0], "08:00");
	strcpy_s(sDesHorIni[1], "08:50");
	strcpy_s(sDesHorIni[2], "09:40");
	strcpy_s(sDesHorIni[3], "10:30");
	strcpy_s(sDesHorIni[4], "11:20");
	strcpy_s(sDesHorIni[5], "12:10");
	strcpy_s(sDesHorIni[6], "13:00");
	strcpy_s(sDesHorIni[7], "13:50");
	strcpy_s(sDesHorIni[8], "14:40");
	strcpy_s(sDesHorIni[9], "15:30");
	strcpy_s(sDesHorIni[10], "16:20");
	strcpy_s(sDesHorIni[11], "17:10");
	strcpy_s(sDesHorIni[12], "18:00");
	strcpy_s(sDesHorIni[13], "18:50");
	strcpy_s(sDesHorIni[14], "19:40");
	strcpy_s(sDesHorIni[15], "20:30");
	strcpy_s(sDesHorIni[16], "21:20");
	strcpy_s(sDesHorFin[0], "08:50");
	strcpy_s(sDesHorFin[1], "09:40");
	strcpy_s(sDesHorFin[2], "10:30");
	strcpy_s(sDesHorFin[3], "11:20");
	strcpy_s(sDesHorFin[4], "12:10");
	strcpy_s(sDesHorFin[5], "13:00");
	strcpy_s(sDesHorFin[6], "13:50");
	strcpy_s(sDesHorFin[7], "14:40");
	strcpy_s(sDesHorFin[8], "15:30");
	strcpy_s(sDesHorFin[9], "16:20");
	strcpy_s(sDesHorFin[10], "17:10");
	strcpy_s(sDesHorFin[11], "18:00");
	strcpy_s(sDesHorFin[12], "18:50");
	strcpy_s(sDesHorFin[13], "19:40");
	strcpy_s(sDesHorFin[14], "20:30");
	strcpy_s(sDesHorFin[15], "21:20");
	strcpy_s(sDesHorFin[16], "22:10");


	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotCDog; k++)
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		for(k=0; k<nNumTotCurg; k++)
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}

		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);

		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;

		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;

		CString abc1;
		j4=j5=j6=0;
		Cadena = "";
		for(j4=0; j4<nNumTotAulg; j4++) {
			for(j5=0; j5<6; j5++) {
				nDia=nHorIni=nHorFin=-1;
				for(j6=0; j6<18; j6++) {
					if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
						if(nDia == -1) {
							nDia = j5;
							nHorIni = nHorFin = j6;
						}
						else
							nHorFin = j6;

					}
				}
				if(nDia != -1) {


					Cadena.Format("%s %-20.20s %s %s %-20.20s %s %-5.5s %-5.5s %-5.5s",
					sArrCCCDocg[i], sArrNomCurg[nPosCur], sArrCGCDocg[i],sArrCDCDocg[i],
					sCad, sArrCodAulg[j4], sDiaSem[j5], sDesHorIni[nHorIni], sDesHorFin[nHorFin]);
					m_CtrlLisHor.AddString(Cadena);
				}
			}
		}
	}

}

void CLisACaView::OnProConhor() 
{
	// TODO: Add your command handler code here
	CDlgLisACa Dlg1;
	Dlg1.DoModal();
	
}

void CLisACaView::OnUpdateProConhor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
/////////////////////////////////////////////////////////////////////////////
// CDlgPobIni dialog


CDlgPobIni::CDlgPobIni(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPobIni::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPobIni)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPobIni::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPobIni)
	DDX_Control(pDX, IDC_LISPIN, m_CtrlLisPIn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPobIni, CDialog)
	//{{AFX_MSG_MAP(CDlgPobIni)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPobIni message handlers

void CLisACaView::OnProConpin() 
{
	// TODO: Add your command handler code here
	CDlgPobIni Dlg1;
	Dlg1.DoModal();
	
}

void CLisACaView::OnUpdateProConpin(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

HBRUSH CDlgPobIni::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID()==IDC_LISPIN||
	    pWnd->GetDlgCtrlID()==IDC_LISPIN){
		
		pDC->SetBkColor(m_Color1);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)m_Pincel1.GetSafeHandle();
	}
	return hbr;

}

BOOL CDlgPobIni::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here

	LOGFONT lf;
	memset( &lf, 0, sizeof(LOGFONT) );
	lf.lfHeight = 14;
	strcpy_s(lf.lfFaceName,"Courier New");
	m_Fuente1.CreateFontIndirect(&lf);
	m_CtrlLisPIn.SetFont(&m_Fuente1);

	m_Color1 = RGB(255,255, 175);
	m_Pincel1.CreateSolidBrush(m_Color1);
//	CarDesCar1();
//	nTamRegg = sizeof(SEstCal);

//	ActivaInactivaDialogo(false);
	ActDatPan();
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control

}

void CDlgPobIni::ActDatPan()
{
	CString Cadena;
	int i, k;
	int nPosDoc;
	int nPosCur;
	int nCicCur;
	char sDiaSem[7][12];
	char sDesHorIni[20][6];
	char sDesHorFin[20][6];
	int nDia, nHorIni, nHorFin;
	int j4, j5, j6, j8;
	char sCad[121];
	char sCadPob[100];
	int nVal;

	strcpy_s(sDiaSem[0], "Lunes");
	strcpy_s(sDiaSem[1], "Martes");
	strcpy_s(sDiaSem[2], "Miercoles");
	strcpy_s(sDiaSem[3], "Jueves");
	strcpy_s(sDiaSem[4], "Viernes");
	strcpy_s(sDiaSem[5], "Sabado");
	strcpy_s(sDiaSem[6], "Domingo");

	strcpy_s(sDesHorIni[0], "08:00");
	strcpy_s(sDesHorIni[1], "08:50");
	strcpy_s(sDesHorIni[2], "09:40");
	strcpy_s(sDesHorIni[3], "10:30");
	strcpy_s(sDesHorIni[4], "11:20");
	strcpy_s(sDesHorIni[5], "12:10");
	strcpy_s(sDesHorIni[6], "13:00");
	strcpy_s(sDesHorIni[7], "13:50");
	strcpy_s(sDesHorIni[8], "14:40");
	strcpy_s(sDesHorIni[9], "15:30");
	strcpy_s(sDesHorIni[10], "16:20");
	strcpy_s(sDesHorIni[11], "17:10");
	strcpy_s(sDesHorIni[12], "18:00");
	strcpy_s(sDesHorIni[13], "18:50");
	strcpy_s(sDesHorIni[14], "19:40");
	strcpy_s(sDesHorIni[15], "20:30");
	strcpy_s(sDesHorIni[16], "21:20");

	strcpy_s(sDesHorFin[0], "08:50");
	strcpy_s(sDesHorFin[1], "09:40");
	strcpy_s(sDesHorFin[2], "10:30");
	strcpy_s(sDesHorFin[3], "11:20");
	strcpy_s(sDesHorFin[4], "12:10");
	strcpy_s(sDesHorFin[5], "13:00");
	strcpy_s(sDesHorFin[6], "13:50");
	strcpy_s(sDesHorFin[7], "14:40");
	strcpy_s(sDesHorFin[8], "15:30");
	strcpy_s(sDesHorFin[9], "16:20");
	strcpy_s(sDesHorFin[10], "17:10");
	strcpy_s(sDesHorFin[11], "18:00");
	strcpy_s(sDesHorFin[12], "18:50");
	strcpy_s(sDesHorFin[13], "19:40");
	strcpy_s(sDesHorFin[14], "20:30");
	strcpy_s(sDesHorFin[15], "21:20");
	strcpy_s(sDesHorFin[16], "22:10");


	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotDocg; k++)
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		for(k=0; k<nNumTotCurg; k++)
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}

		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);

		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;

		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;

		CString abc1;
		j4=j5=j6=0;
		Cadena = "";
		for(j4=0; j4<nNumTotAulg; j4++) {
			for(j5=0; j5<6; j5++) {
				strcpy_s(sCadPob,"0000000000000000000000");
				nVal = (sArrCDCDocg[i][1]-'0')*10 + (sArrCDCDocg[i][2]-'0');
				for(j8=0; nVal; j8++) {
					if((5-j8)>=0)
						sCadPob[5-j8] = nVal%2+'0';
					nVal = nVal/2;
				}
				sCadPob[6+j5] = '1';

				nVal = j4+1;
				for(j8=0; nVal; j8++) {
					if((15-j8)>=0)
						sCadPob[15-j8] = nVal%2+'0';
					nVal = nVal/2;
				}



				nDia=nHorIni=nHorFin=-1;
				for(j6=0; j6<18; j6++) {
					if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
						if(j6<6)
							sCadPob[16+j6] = '1';
						else
							if(j6<12)
								sCadPob[16+j6-6] = '1';
							else
								sCadPob[16+j6-12] = '1';

						if(nDia == -1) {
							nDia = j5;
							nHorIni = nHorFin = j6;
						}
						else
							nHorFin = j6;

					}
				}
				if(nDia != -1) {
					if(sArrCGCDocg[i][0]=='0')
						Cadena.Format("%s %s T %s",
						sArrCCCDocg[i], sArrCGCDocg[i], sCadPob);
					else
						Cadena.Format("%s %s L %s",
						sArrCCCDocg[i], sArrCGCDocg[i], sCadPob);

					m_CtrlLisPIn.AddString(Cadena);
				}
			}
		}
	}

}
/////////////////////////////////////////////////////////////////////////////
// CDlgProAdi dialog


CDlgProAdi::CDlgProAdi(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProAdi::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProAdi)
	m_sTotPen = _T("");
	m_sNumPob = _T("");
	//}}AFX_DATA_INIT
}


void CDlgProAdi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProAdi)
	DDX_Control(pDX, IDC_ALTASI, m_CtrlAltAsi);
	DDX_Control(pDX, IDC_NUMPOB, m_CtrlNumPob);
	DDX_Control(pDX, IDC_CALPEN, m_CtrlCalPen);
	DDX_Control(pDX, IDC_GNPOBL, m_CtrlGNPobl);
	DDX_Control(pDX, IDC_TOTPEN, m_CtrlTotPen);
	DDX_Control(pDX, IDC_LISSP4, m_CtrlLisSP4);
	DDX_Control(pDX, IDC_LISSP1, m_CtrlLisSP1);
	DDX_Control(pDX, IDC_LISSUBPOB, m_CtrlLisSubPob);
	DDX_Control(pDX, IDC_LISSP3, m_CtrlLisSP3);
	DDX_Control(pDX, IDC_LISSP2, m_CtrlLisSP2);
	DDX_Control(pDX, IDC_LISPAC, m_CtrlLisPAc);
	DDX_Control(pDX, IDC_LISPENAUL, m_CtrlLisPenAul);
	DDX_Control(pDX, IDC_LISPENDOC, m_CtrlLisPenDoc);
	DDX_Control(pDX, IDC_LISPENCIC, m_CtrlLisPenCic);
	DDX_Control(pDX, IDC_LISDOC, m_CtrlLisDoc);
	DDX_Text(pDX, IDC_TOTPEN, m_sTotPen);
	DDX_Text(pDX, IDC_NUMPOB, m_sNumPob);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_GVPOBL, m_CtrlGVPobl);
}


BEGIN_MESSAGE_MAP(CDlgProAdi, CDialog)
	//{{AFX_MSG_MAP(CDlgProAdi)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CALPEN, OnCalpen)
	ON_BN_CLICKED(IDC_GNPOBL, OnGnpobl)
	ON_BN_CLICKED(IDC_ALTASI, OnAltasi)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_GVPOBL, &CDlgProAdi::OnBnClickedGvpobl)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProAdi message handlers

HBRUSH CDlgProAdi::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID()==IDC_LISDOC||
		pWnd->GetDlgCtrlID()==IDC_LISPAC||
		pWnd->GetDlgCtrlID()==IDC_LISSP1||
		pWnd->GetDlgCtrlID()==IDC_LISSP2||
		pWnd->GetDlgCtrlID()==IDC_LISSP3||
		pWnd->GetDlgCtrlID()==IDC_LISSP4||
		pWnd->GetDlgCtrlID()==IDC_TOTPEN||
		pWnd->GetDlgCtrlID()==IDC_NUMPOB||
		pWnd->GetDlgCtrlID()==IDC_LISSUBPOB||
		pWnd->GetDlgCtrlID()==IDC_LISPENCIC||
		pWnd->GetDlgCtrlID()==IDC_LISPENAUL||
	    pWnd->GetDlgCtrlID()==IDC_LISPENDOC){
		
		pDC->SetBkColor(m_Color1);
		pDC->SetTextColor(RGB(0, 0, 0));
		return (HBRUSH)m_Pincel1.GetSafeHandle();
	}
	return hbr;

}

BOOL CDlgProAdi::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	LOGFONT lf;
	memset( &lf, 0, sizeof(LOGFONT) );
	lf.lfHeight = 14;
	strcpy_s(lf.lfFaceName,"Courier New");
	m_Fuente1.CreateFontIndirect(&lf);
	m_CtrlLisDoc.SetFont(&m_Fuente1);

	m_CtrlLisPenCic.SetFont(&m_Fuente1);
	m_CtrlLisPenAul.SetFont(&m_Fuente1);
	m_CtrlLisPenDoc.SetFont(&m_Fuente1);
	lf.lfHeight = 16;
	strcpy_s(lf.lfFaceName,"Courier New");
	m_Fuente1.CreateFontIndirect(&lf);
	m_CtrlLisPAc.SetFont(&m_Fuente1);
	m_CtrlLisSP1.SetFont(&m_Fuente1);
	m_CtrlLisSP2.SetFont(&m_Fuente1);
	m_CtrlLisSP3.SetFont(&m_Fuente1);
	m_CtrlLisSP4.SetFont(&m_Fuente1);
	m_CtrlLisSubPob.SetFont(&m_Fuente1);
	m_CtrlTotPen.SetFont(&m_Fuente1);

	m_Color1 = RGB(255,255, 175);
	m_Pincel1.CreateSolidBrush(m_Color1);
//	CarDesCar1();
//	nTamRegg = sizeof(SEstCal);

//	ActivaInactivaDialogo(false);
	IniCadTip();
	ActDatPan();
	if(nICIPobg==1) {
		m_CtrlAltAsi.EnableWindow(false);
	}
	m_CtrlGNPobl.EnableWindow(false);
	m_CtrlGVPobl.EnableWindow(false);
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgProAdi::ActDatPan()
{
	CString Cadena, Cadena1;
	int i, k, k1;
	int nPosCur;		// Posicion del curso en la tabla de cursos
	int nCicCur;
	int nPosAul;
	int nPosDoc;		// Posición del docente en la tabla de docentes
	int j4, j5, j6, j8;
	char sCad[121];
	char sArrCic[11];	// Arreglo interno de ciclos
	int nArrCicDiaHor[11][6][18];	// Arreglo ciclo dia y hora
	char sCadPob[51];
	int nVal;
	int nDia;
	int nHorIni;
	int nHorFin;
	int nDiaIni;
	int nDiaFin;
	char sArrDesCic[11][11];
	char sArrPosAul[21];		// Aulas ocupadas por el curso
	int nCon;

	strcpy_s(sArrDesCic[0],"I");
	strcpy_s(sArrDesCic[1],"II");
	strcpy_s(sArrDesCic[2],"III");
	strcpy_s(sArrDesCic[3],"IV");
	strcpy_s(sArrDesCic[4],"V");
	strcpy_s(sArrDesCic[5],"VI");
	strcpy_s(sArrDesCic[6],"VII");
	strcpy_s(sArrDesCic[7],"VIII");
	strcpy_s(sArrDesCic[8],"IX");
	strcpy_s(sArrDesCic[9],"X");

	for(i=0; i<nNumTotCDog; i++) {
		for(k1=0; k1<10; k1++)		sArrCic[k1]=0;
		for(k1=0; k1<21; k1++)			sArrPosAul[k1]=0;
		for(k1=0; k1<nNumTotDocg; k1++) {
			if(!strncmp(sArrCodDocg[k1], sArrCDCDocg[i], 3)) {
				nPosDoc = k1;
				break;
			}
		}
		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);
		for(k1=0; k1<nNumTotCurg; k1++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k1], 3)) {
				nPosCur = k1;
				break;
			}
		}
		nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 + sArrCicCurg[nPosCur][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)		nCicCur = 0;
		sArrCic[nCicCur]=1;		// Establece indicador en ciclo al cual pertenece el curso

		nPosAul = -1;
		// Halla las aulas que estan ocupadas por el curso docente
		for(int j4=0; j4<nNumTotAulg; j4++) {
			for(int j5=0; j5<6; j5++) {
				for(int j6=0; j6<18; j6++) {
					if( (!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3)) ||
						(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3)) ) {
						sArrPosAul[j4] = 1;
					}
				}
			}
		}
		nCon = 0;
		// Establece la cadena con el cod.curso, cod.docente y nombre docente
		// seguidamente se adicionara el ciclo y las aulas
		Cadena.Format("%s %s %-25.25s  ",sArrCCCDocg[i],sArrCDCDocg[i],sCad );
		for(k1=0; k1<10; k1++) {
			if(sArrCic[k1]==1) {
				Cadena1.Format("%-4.4s ",sArrDesCic[k1]);
				Cadena = Cadena + Cadena1;
				nCon++;
			}
		}
		Cadena = Cadena + "  ";
		for(k1=0; k1<20; k1++) {
			if(sArrPosAul[k1]==1) {
				Cadena1.Format("%-4.4s ",sArrCodAulg[k1]);
				Cadena = Cadena + Cadena1;
			}
		}
		m_CtrlLisDoc.AddString(Cadena);
	}

	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotDocg; k++) {
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}
		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);
		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;
		CString abc1;
		j4=j5=j6=0;
		Cadena = "";
		strcpy_s(sCadPob,"00000000000000000000000000000000");
		nVal = (sArrCDCDocg[i][1]-'0')*10 + (sArrCDCDocg[i][2]-'0');
		for(j8=0; nVal; j8++) {
			if((5-j8)>=0)
				sCadPob[5-j8] = nVal%2+'0';
			nVal = nVal/2;
		}
		nDiaIni = nDiaFin = -1;
		for(j5=0; j5<6; j5++) {
			for(j4=0; j4<nNumTotAulg; j4++) {
				nDia=nHorIni=nHorFin=-1;
				for(j6=0; j6<18; j6++) {
					if( (!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) ||
						(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3) ) ) {
						if(nDiaIni==-1)		nDiaIni = j5;
						if(nDiaIni == j5) {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(j8=0; nVal; j8++) {
								if((15-j8)>=0)
									sCadPob[15-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[16+j6] = '1';
							else
								if(j6<12)
									sCadPob[16+j6-6] = '1';
								else
									sCadPob[16+j6-12] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
						else {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(int j8=0; nVal; j8++) {
								if((25-j8)>=0)
									sCadPob[25-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[26+j6] = '1';
							else
								if(j6<12)
								sCadPob[26+j6-6] = '1';
									else
										sCadPob[26+j6-12] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
					}
				}
			}
		}
		if(sArrCGCDocg[i][0]=='0')
			Cadena.Format("%s %s T %-6.6s %-6.6s %-10.10s %s",
			sArrCCCDocg[i], sArrCGCDocg[i], sCadPob,sCadPob+6,sCadPob+12,sCadPob+22);
		else
			Cadena.Format("%s %s L %-6.6s %-6.6s %-10.10s %s",
			sArrCCCDocg[i], sArrCGCDocg[i], sCadPob,sCadPob+6,sCadPob+12,sCadPob+22);
		m_CtrlLisPAc.AddString(Cadena);
	}

	for(int k1=0; k1<11; k1++)
		for(int k2=0; k2<6; k2++)
			for(int k3=0; k3<18; k3++)
				nArrCicDiaHor[k1][k2][k3]=0;

	for(j5=0; j5<6; j5++) {
		for(int j6=0; j6<18; j6++) {
			for(int j4=0; j4<nNumTotAulg; j4++) {
				for(k1=0; k1<nNumTotCDog; k1++) {
					if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[k1],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[k1],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[k1],3) ) {
						for(int k2=0; k2<nNumTotCurg; k2++) {
							if(!strncmp(sArrCCCDocg[k1], sArrCodCurg[k2], 3)) {
								nPosCur = k2;
								break;
							}
						}
						nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 +
							sArrCicCurg[nPosCur][1]-'0';
						nCicCur--;
						if(nCicCur<0 || nCicCur>9)
							nCicCur = 0;
						nArrCicDiaHor[nCicCur][j5][j6]=nArrCicDiaHor[nCicCur][j5][j6]+1;
//						if(nArrCicDiaHor[nCicCur][j5][j6]==2)
//							AfxMessageBox(sArrCodCurg[nPosCur]);

					}
				}
			}
		}
	}
}

void CDlgProAdi::OnCalpen() 
{
	// TODO: Add your control notification handler code here
	CFile bd1;		// representa al fichero
	CString szNombreFi;
	CString Cadena, Cadena1;
	int i, j, k, k1;
	int nPosCur;		// Posicion del curso en la tabla de cursos
	int nCicCur;
	int nPosAul;
	int nPosDoc;		// Posicion en tabla de docentes
	int j4, j5, j6, j8;
	char sCad[121];
	char sArrCic[11];	// Arreglo interno de ciclos
	int nArrCicDiaHor[11][6][18];	// Arreglo ciclo dia y hora
	char sArrProHor[200][6][18];
	char sCadPob[51];
	int nVal;
	int nDia;
	int nHorIni;
	int nHorFin;
	int nDiaIni;
	int nDiaFin;

	char sArrDesCic[11][11];
	char sArrPosAul[21];		// Aulas ocupadas por el curso
	int nCon;
	int nValPen;
	double nFunApt;
	double nDGPobl;
	double nPSCInd;
	double nProAcu;
	int nNESPob;		// No. de elemntos de la subpoblación
	int nULSPob;		// Ubicación en la lista de subpoblaciones
	double nArrProAcu[20];	// Lista de probabilidad acumulada de la subpoblacion
	double nArrPSCInd[20];	// Lista de probabilidad seleccionada
	int nTPPobl;			// Total penalidad de la población

	strcpy_s(sArrDesCic[0],"I");
	strcpy_s(sArrDesCic[1],"II");
	strcpy_s(sArrDesCic[2],"III");
	strcpy_s(sArrDesCic[3],"IV");
	strcpy_s(sArrDesCic[4],"V");
	strcpy_s(sArrDesCic[5],"VI");
	strcpy_s(sArrDesCic[6],"VII");
	strcpy_s(sArrDesCic[7],"VIII");
	strcpy_s(sArrDesCic[8],"IX");
	strcpy_s(sArrDesCic[9],"X");

// Inicializa subpoblaciones, el numero de individuo y el valor variable 
	for(i=0; i<20; i++) {
		for(j=0; j<50; j++) {
			nArrSubPobg[i][j] = sArrVarSPog[i][j][0]=0;
		}
	}
	nNESPob = 0;	// Asigna 0 a No. elementos de la subpoblación
	Cadena.Format("LPobla%02d.txt",nNumPobg+1);
	szNombreFi = Cadena;
	if (!bd1.Open(szNombreFi, CFile::modeCreate | CFile::modeWrite)) {
		AfxMessageBox("No se puede  abrir el fichero");
		return;
	}
	m_CtrlLisDoc.ResetContent();
	for(i=0; i<nNumTotCDog; i++) {
		for(k1=0; k1<10; k1++)		sArrCic[k1]=0;
		for(k1=0; k1<21; k1++)			sArrPosAul[k1]=0;
		for(k1=0; k1<nNumTotDocg; k1++) {
			if(!strncmp(sArrCodDocg[k1], sArrCDCDocg[i], 3)) {
				nPosDoc = k1;
				break;
			}
		}

		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);
		for(k1=0; k1<nNumTotCurg; k1++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k1], 3)) {
				nPosCur = k1;
				break;
			}
		}
		nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 + sArrCicCurg[nPosCur][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)		nCicCur = 0;
		sArrCic[nCicCur]=1;		// Establece indicador en ciclo al cual pertenece el curso
		nPosAul = -1;

		for(int j4=0; j4<nNumTotAulg; j4++) {
			for(int j5=0; j5<6; j5++) {
				for(int j6=0; j6<18; j6++) {
					if( (!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3)) ||
						(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3)) ) {
						sArrPosAul[j4] = 1;
					}
				}
			}
		}
		nCon = 0;
		// Establece la cadena con el cod.curso, cod.docente y nombre docente
		// seguidamente se adicionara el ciclo y las aulas
		Cadena.Format("%s %s %-25.25s  ",sArrCCCDocg[i],sArrCDCDocg[i],sCad );
		for(k1=0; k1<10; k1++) {
			if(sArrCic[k1]==1) {
				Cadena1.Format("%-4.4s ",sArrDesCic[k1]);
				Cadena = Cadena + Cadena1;
				nCon++;
			}
		}
		Cadena = Cadena + "  ";
		for(k1=0; k1<20; k1++) {
			if(sArrPosAul[k1]==1) {
				Cadena1.Format("%-4.4s ",sArrCodAulg[k1]);
				Cadena = Cadena + Cadena1;
			}
		}
		m_CtrlLisDoc.AddString(Cadena);
	}

	// Se hallara si el curso del docente en el dia y hora y en el ciclo al cual pertenece
	// tiene cruce
	m_CtrlLisPenCic.ResetContent();
	for(int k1=0; k1<11; k1++)
		for(int k2=0; k2<6; k2++)
			for(int k3=0; k3<18; k3++)
				nArrCicDiaHor[k1][k2][k3]=0;
	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotDocg; k++) {
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}
		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;

		for(int j4=0; j4<nNumTotAulg; j4++) {
			for(j5=0; j5<6; j5++) {
				for(int j6=0; j6<18; j6++) {
					if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
						nArrCicDiaHor[nCicCur][j5][j6] = nArrCicDiaHor[nCicCur][j5][j6]+1;
					}
					if(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
						nArrCicDiaHor[nCicCur][j5][j6] = nArrCicDiaHor[nCicCur][j5][j6]+1;
					}
				}
			}
		}
	}
	for(i=0; i<nNumTotCDog; i++) {
		nValPen = 0;
		for(k=0; k<nNumTotDocg; k++) {
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}
		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);
		nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 + sArrCicCurg[nPosCur][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;

		for(int j4=0; j4<nNumTotAulg; j4++) {
			for(j5=0; j5<6; j5++) {
				for(int j6=0; j6<18; j6++) {
					if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
						if(sArrCCCDocg[i][1]=='0' && sArrCCCDocg[i][2]=='1') {
							CString fff;
							fff.Format("Curso C01 Arreglo 1  Dia %d Hora %d  Aula %s",j5,j6,sArrCodAulg[j4]);
//							AfxMessageBox(fff);
						}
						if(nArrCicDiaHor[nCicCur][j5][j6]>1) {
							nValPen = nValPen + 5;
						}
					}
					else {
						if(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
							!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
							!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
							if(sArrCCCDocg[i][1]=='0' && sArrCCCDocg[i][2]=='1') {
								CString fff;
								fff.Format("Curso 01 Arreglo 2 Dia %d Hora %d  Aula %s ",j5,j6,sArrCodAulg[j4]);
//								AfxMessageBox(fff);
							}
							if(nArrCicDiaHor[nCicCur][j5][j6]>1) {
								nValPen = nValPen + 5;
							}
						}
					}
				}
			}
		}
		nArrPCCDocg[i] = nValPen;		// Lista penalidad por ciclo curso docente
		Cadena.Format("%s %s %-23.23s  %d",sArrCCCDocg[i], sArrCDCDocg[i], sCad, nValPen);
		m_CtrlLisPenCic.AddString(Cadena);
	}

	// Se hallara si el curso del docente en el dia, hora y aula tiene cruce con cualquier
	// otro curso docente
	m_CtrlLisPenAul.ResetContent();
	for(i=0; i<nNumTotCDog; i++) {
		nValPen=0;
		for(k=0; k<nNumTotDocg; k++) {
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}
		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);
		nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 + sArrCicCurg[nPosCur][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;
		for(int j4=0; j4<nNumTotAulg; j4++) {
			for(j5=0; j5<6; j5++) {
				for(int j6=0; j6<18; j6++) {
					if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
						if(sArrHDAAu2g[j4][j5][j6][0]!='D') {
							if(sArrCCCDocg[i][1]=='0' && sArrCCCDocg[i][2]=='1') {
								CString fff;
								fff.Format("Cruce en aula Arreglo 1 con Arreglo 2 Dia %d Hora %d ", j5, j6);
//								AfxMessageBox(fff);
							}
							nValPen = nValPen + 4;
						}
					}
					else {
						if(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
							!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
							!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
							if(sArrHDAAulg[j4][j5][j6][0]!='D') {
								if(sArrCCCDocg[i][1]=='0' && sArrCCCDocg[i][2]=='1') {
									CString fff;
									fff.Format("Cruce en aula Arreglo 2 con Arreglo 1 Dia %d Hora %d ", j5, j6);
//									AfxMessageBox(fff);
								}
								nValPen = nValPen + 4;
							}
						}
					}
				}
			}
		}
		nArrPACDocg[i]= nValPen;		// Lista penalidad por aula curso docente
		Cadena.Format("%s %s %-23.23s  %d",sArrCCCDocg[i], sArrCDCDocg[i], sCad, nValPen);
		m_CtrlLisPenAul.AddString(Cadena);
	}
	// Se hallara si el docente en el dia y hora tiene cruce
	m_CtrlLisPenDoc.ResetContent();
	for(k1=0; k1<200; k1++)
		for(int k2=0; k2<6; k2++)
			for(int k3=0; k3<18; k3++)
				sArrProHor[k1][k2][k3]=0;
	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotDocg; k++) {
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}
		nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 + sArrCicCurg[nPosCur][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;

		for(int j4=0; j4<nNumTotAulg; j4++) {
			for(j5=0; j5<6; j5++) {
				for(int j6=0; j6<18; j6++) {
					if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
						sArrProHor[nPosDoc][j5][j6]=sArrProHor[nPosDoc][j5][j6]+1;
					}
					if(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
						sArrProHor[nPosDoc][j5][j6]=sArrProHor[nPosDoc][j5][j6]+1;
					}
				}
			}
		}
	}
	for(i=0; i<nNumTotCDog; i++) {
		nValPen = 0;
		for(k=0; k<nNumTotDocg; k++) {
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}
		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);
		nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 + sArrCicCurg[nPosCur][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;

		for(int j4=0; j4<nNumTotAulg; j4++) {
			for(j5=0; j5<6; j5++) {
				for(int j6=0; j6<18; j6++) {
					if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
						if(sArrProHor[nPosDoc][j5][j6]>1) {
							nValPen = nValPen + 2;
						}
					}
					if(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
						if(sArrProHor[nPosDoc][j5][j6]>1) {
							nValPen = nValPen + 2;
						}
					}
				}
			}
		}
		nArrPDCDocg[i]= nValPen;		// Lista penalidad por docente curso docente
		Cadena.Format("%s %s %-23.23s  %d",sArrCCCDocg[i], sArrCDCDocg[i], sCad, nValPen);
		m_CtrlLisPenDoc.AddString(Cadena);
	}
	// Halla el Desempeño Global de la Población
	nTPPobl = 0;			// Total penalidad de la población
	nDGPobl = 0;
	for (k1=0; k1<nNumTotCDog; k1++) {
		nValPen = nArrPCCDocg[k1]+nArrPACDocg[k1]+nArrPDCDocg[k1];
		nFunApt = 1.00/(nArrPCCDocg[k1]+nArrPACDocg[k1]+nArrPDCDocg[k1]+1);
		nDGPobl = nDGPobl + nFunApt;
		nTPPobl = nTPPobl + nValPen + 1;
	}
	nProAcu = 0;
	// Muestra el cromosoma y la penalidad
	m_CtrlLisPAc.ResetContent();
	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotDocg; k++) {
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}
		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);
		// Halla el ciclo del curos: de 0 al 9
		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;

		CString abc1;
		j4=j5=j6=0;
		Cadena = "";
		strcpy_s(sCadPob,"00000000000000000000000000000000");
		nVal = (sArrCDCDocg[i][1]-'0')*10 + (sArrCDCDocg[i][2]-'0');
		for(j8=0; nVal; j8++) {
			if((5-j8)>=0)
				sCadPob[5-j8] = nVal%2+'0';
			nVal = nVal/2;
		}
		nDiaIni = nDiaFin = -1;
		for(j5=0; j5<6; j5++) {
			for(j4=0; j4<nNumTotAulg; j4++) {
				nDia=nHorIni=nHorFin=-1;
				for(j6=0; j6<18; j6++) {
					if( (!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3)) ||
						(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3)) ) {
						if(nDiaIni==-1)		nDiaIni = j5;
						if(nDiaIni == j5) {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(j8=0; nVal; j8++) {
								if((15-j8)>=0)
									sCadPob[15-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[16+j6] = '1';
							else
								if(j6<12) {
									if(nCicCur<7)	sCadPob[16+j6-6] = '1';
									if(nCicCur>6)	sCadPob[16] = '1';
								}
								else
									sCadPob[16+j6-11] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
						else {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(int j8=0; nVal; j8++) {
								if((25-j8)>=0)
									sCadPob[25-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[26+j6] = '1';
							else
								if(j6<12) {
									if(nCicCur<7)	sCadPob[26+j6-6] = '1';
									if(nCicCur>6)	sCadPob[26] = '1';
								}
								else
									sCadPob[26+j6-11] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
					}
				}
			}
		}
		nValPen = nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i];
		nFunApt = 1.00/(nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i]+1);
		nPSCInd = nFunApt/nDGPobl;
		nProAcu = nProAcu + nPSCInd;
		if(sArrCGCDocg[i][0]=='0')
			Cadena.Format("%s %s T %-6.6s %-6.6s %-10.10s %s  %02d %5.3lf %5.2lf %lf %lf",
			sArrCCCDocg[i], sArrCGCDocg[i],sCadPob,sCadPob+6,sCadPob+12,sCadPob+22,
			nValPen+1, nFunApt, nDGPobl,nPSCInd,nProAcu);
		else
			Cadena.Format("%s %s L %-6.6s %-6.6s %-10.10s %s  %02d %5.3lf %5.2lf %lf %lf",
			sArrCCCDocg[i], sArrCGCDocg[i],sCadPob,sCadPob+6,sCadPob+12,sCadPob+22,
			nValPen+1, nFunApt, nDGPobl,nPSCInd,nProAcu);
		m_CtrlLisPAc.AddString(Cadena);
		strcpy_s(sCad, Cadena);
		bd1.Write(sCad, strlen(sCad));
		sCad[0]=13;
		sCad[1]=10;
		sCad[2]=0;
		bd1.Write(sCad, strlen(sCad));
	}
	m_sNumPob.Format("%02d",nNumPobg+1); 
	m_sTotPen.Format("%03d",nTPPobl);
	nTPPoblg = nTPPobl;
	if(nTPPobl==102)		GenArcSol();

	// Halla el Desempeño Global de las Sub Poblaciones del turno mañana
	nDGSPobg[0] = nDGSPobg[1] = nDGSPobg[2] = nDGSPobg[3] = nDGSPobg[4] = 0;
	for (i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotDocg; k++)
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}
		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;
		if(nCicCur>3 || sArrCTACDog[i][0]!='A')
			continue;
		if(nArrNHCDocg[i]!=6 && nArrNHCDocg[i]!=5 && nArrNHCDocg[i]!=4 &&
			nArrNHCDocg[i]!=3 && nArrNHCDocg[i]!=2) {
			continue;
		}
		nFunApt = 1.00/(nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i]+1);
		if(nArrNHCDocg[i]==6)	nDGSPobg[0] = nDGSPobg[0] + nFunApt;
		if(nArrNHCDocg[i]==5)	nDGSPobg[1] = nDGSPobg[1] + nFunApt;
		if(nArrNHCDocg[i]==4)	nDGSPobg[2] = nDGSPobg[2] + nFunApt;
		if(nArrNHCDocg[i]==3)	nDGSPobg[3] = nDGSPobg[3] + nFunApt;
		if(nArrNHCDocg[i]==2)	nDGSPobg[4] = nDGSPobg[4] + nFunApt;
	}
	nProAcu = 0;
	// Muestra el cromosoma y la penalidad de las subpoblaciones del turno mañana
	nArrPSCInd[0]= nArrPSCInd[1]= nArrPSCInd[2]= nArrPSCInd[3]= nArrPSCInd[4]= 0;
	nArrProAcu[0]= nArrProAcu[1]= nArrProAcu[2]= nArrProAcu[3]= nArrProAcu[4]= 0;
	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotDocg; k++) {
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}
		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);
		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;
		if(nCicCur>3 || sArrCTACDog[i][0]!='A')
			continue;
		if(nArrNHCDocg[i]!=6 && nArrNHCDocg[i]!=5 && nArrNHCDocg[i]!=4 &&
			nArrNHCDocg[i]!=3 && nArrNHCDocg[i]!=2) {
			continue;
		}
		nULSPob = 0;
		if(nArrNHCDocg[i]==6)	nULSPob = 0;
		if(nArrNHCDocg[i]==5)	nULSPob = 1;
		if(nArrNHCDocg[i]==4)	nULSPob = 2;
		if(nArrNHCDocg[i]==3)	nULSPob = 3;
		if(nArrNHCDocg[i]==2)	nULSPob = 4;

		for(k=0; k<50; k++)
			if(sArrVarSPog[nULSPob][k][0]==0)
				break;
		nArrSubPobg[nULSPob][k] = i;	// Lista de elementos de la subpoblación mañana
		nArrTSPoblg[nULSPob] = 'M';		// El turno de la subpoblacion: Mañana

		CString abc1;
		j4=j5=j6=0;
		Cadena = "";
		strcpy_s(sCadPob,"00000000000000000000000000000000");
		nVal = (sArrCDCDocg[i][1]-'0')*10 + (sArrCDCDocg[i][2]-'0');
		for(j8=0; nVal; j8++) {
			if((5-j8)>=0)
				sCadPob[5-j8] = nVal%2+'0';
			nVal = nVal/2;
		}
		nDiaIni = nDiaFin = -1;
		for(j5=0; j5<6; j5++) {
			for(j4=0; j4<nNumTotAulg; j4++) {
				nDia=nHorIni=nHorFin=-1;
				for(j6=0; j6<18; j6++) {
					if( (!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3)) ||
						(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3)) ) {
						if(nDiaIni==-1)		nDiaIni = j5;
						if(nDiaIni == j5) {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(j8=0; nVal; j8++) {
								if((15-j8)>=0)
									sCadPob[15-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[16+j6] = '1';
							else
								if(j6<12) {
									if(nCicCur<7)	sCadPob[16+j6-6] = '1';
									if(nCicCur>6)	sCadPob[16] = '1';
								}
								else
									sCadPob[16+j6-11] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
						else {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(int j8=0; nVal; j8++) {
								if((25-j8)>=0)
									sCadPob[25-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[26+j6] = '1';
							else
								if(j6<12) {
									if(nCicCur<7)	sCadPob[26+j6-6] = '1';
									if(nCicCur>6)	sCadPob[26] = '1';
								}
								else
									sCadPob[26+j6-11] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
					}
				}
			}
		}
		nValPen = nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i];
		nFunApt = 1.00/(nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i]+1);
		nArrPSCInd[nULSPob] = nFunApt/nDGSPobg[nULSPob];
		nArrProAcu[nULSPob] = nArrProAcu[nULSPob]+nArrPSCInd[nULSPob];

		for(k=0; k<50; k++) {
			if(sArrVarSPog[nULSPob][k][0]==0)
				break;
		}
		nArrPASPobg[nULSPob][k]= nArrProAcu[nULSPob];	// Lista poblacion acumulativa subpoblación
		nArrPSSPobg[nULSPob][k]= nArrPSCInd[nULSPob];	// Lista de probabilidad de seleccion subpoblación
		strcpy_s(sArrVarSPog[nULSPob][k],sCadPob);		// Lista parte variable de la subpoblacion
		nNISPobg[nULSPob] = k+1;
	}
	Cadena.Format("Turno Mañana Teoria 6 horas :  %d ind.", nNISPobg[0]);
	m_CtrlLisSubPob.AddString(Cadena);
	Cadena.Format("Turno Mañana Teoria 5 horas :  %d ind.", nNISPobg[1]);
	m_CtrlLisSubPob.AddString(Cadena);
	Cadena.Format("Turno Mañana Teoria 4 horas :  %d ind.", nNISPobg[2]);
	m_CtrlLisSubPob.AddString(Cadena);
	Cadena.Format("Turno Mañana Teoria 3 horas :  %d ind.", nNISPobg[3]);
	m_CtrlLisSubPob.AddString(Cadena);
	Cadena.Format("Turno Mañana Teoria 2 horas :  %d ind.", nNISPobg[4]);
	m_CtrlLisSubPob.AddString(Cadena);

	// Halla el Desempeño Global de las Sub Poblaciones del turno tarde
	nDGSPobg[5] = nDGSPobg[6] = nDGSPobg[7] = nDGSPobg[8] = nDGSPobg[9] = 0;
	for (i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotDocg; k++)
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}
		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;
		if(nCicCur<4 || nCicCur>6 || sArrCTACDog[i][0]!='A')
			continue;
		if(nArrNHCDocg[i]!=6 && nArrNHCDocg[i]!=5 && nArrNHCDocg[i]!=4 &&
			nArrNHCDocg[i]!=3 && nArrNHCDocg[i]!=2) {
			continue;
		}
		nFunApt = 1.00/(nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i]+1);
		if(nArrNHCDocg[i]==6)	nDGSPobg[5] = nDGSPobg[5] + nFunApt;
		if(nArrNHCDocg[i]==5)	nDGSPobg[6] = nDGSPobg[6] + nFunApt;
		if(nArrNHCDocg[i]==4)	nDGSPobg[7] = nDGSPobg[7] + nFunApt;
		if(nArrNHCDocg[i]==3)	nDGSPobg[8] = nDGSPobg[8] + nFunApt;
		if(nArrNHCDocg[i]==2)	nDGSPobg[9] = nDGSPobg[9] + nFunApt;
	}
	nProAcu = 0;
	// Muestra el cromosoma y la penalidad de las subpoblaciones del turno tarde
	nArrPSCInd[5]= nArrPSCInd[6]= nArrPSCInd[7]= nArrPSCInd[8]= nArrPSCInd[9]= 0;
	nArrProAcu[5]= nArrProAcu[6]= nArrProAcu[7]= nArrProAcu[8]= nArrProAcu[9]= 0;
	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotDocg; k++) {
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}
		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);
		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;
		if(nCicCur<4 || nCicCur>6 || sArrCTACDog[i][0]!='A')
			continue;
		if(nArrNHCDocg[i]!=6 && nArrNHCDocg[i]!=5 && nArrNHCDocg[i]!=4 &&
			nArrNHCDocg[i]!=3 && nArrNHCDocg[i]!=2) {
			continue;
		}
		nULSPob = 4;
		if(nArrNHCDocg[i]==6)	nULSPob = 5;
		if(nArrNHCDocg[i]==5)	nULSPob = 6;
		if(nArrNHCDocg[i]==4)	nULSPob = 7;
		if(nArrNHCDocg[i]==3)	nULSPob = 8;
		if(nArrNHCDocg[i]==2)	nULSPob = 9;

		for(k=0; k<50; k++)
			if(sArrVarSPog[nULSPob][k][0]==0)
				break;
		nArrSubPobg[nULSPob][k] = i;	// Lista de elementos de la subpoblación tarde
		nArrTSPoblg[nULSPob] = 'T';		// Turno de la subpoblacion tarde

		CString abc1;
		j4=j5=j6=0;
		Cadena = "";
		strcpy_s(sCadPob,"00000000000000000000000000000000");
		nVal = (sArrCDCDocg[i][1]-'0')*10 + (sArrCDCDocg[i][2]-'0');
		for(j8=0; nVal; j8++) {
			if((5-j8)>=0)
				sCadPob[5-j8] = nVal%2+'0';
			nVal = nVal/2;
		}
		nDiaIni = nDiaFin = -1;
		for(j5=0; j5<6; j5++) {
			for(j4=0; j4<nNumTotAulg; j4++) {
				nDia=nHorIni=nHorFin=-1;
				for(j6=0; j6<18; j6++) {
					if( (!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3)) ||
						(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3)) ) {
						if(nDiaIni==-1)		nDiaIni = j5;
						if(nDiaIni == j5) {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(j8=0; nVal; j8++) {
								if((15-j8)>=0)
									sCadPob[15-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[16+j6] = '1';
							else
								if(j6<12) {
									if(nCicCur<7)	sCadPob[16+j6-6] = '1';
									if(nCicCur>6)	sCadPob[16] = '1';
								}
								else
									sCadPob[16+j6-11] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
						else {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(int j8=0; nVal; j8++) {
								if((25-j8)>=0)
									sCadPob[25-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[26+j6] = '1';
							else
								if(j6<12) {
									if(nCicCur<7)	sCadPob[26+j6-6] = '1';
									if(nCicCur>6)	sCadPob[26] = '1';
								}
								else
									sCadPob[26+j6-11] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
					}
				}
			}
		}
		nValPen = nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i];
		nFunApt = 1.00/(nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i]+1);
		nArrPSCInd[nULSPob] = nFunApt/nDGSPobg[nULSPob];
		nArrProAcu[nULSPob] = nArrProAcu[nULSPob]+nArrPSCInd[nULSPob];

		for(k=0; k<50; k++) {
			if(sArrVarSPog[nULSPob][k][0]==0)
				break;
		}
		nArrPASPobg[nULSPob][k]= nArrProAcu[nULSPob];	// Lista poblacion acumulativa subpoblación
		nArrPSSPobg[nULSPob][k]= nArrPSCInd[nULSPob];	// Lista de probabilidad de seleccion subpoblación
		strcpy_s(sArrVarSPog[nULSPob][k],sCadPob);		// Lista parte variable de la subpoblacion
		nNISPobg[nULSPob] = k+1;
	}
	Cadena.Format("Turno Tarde Teoria 6 horas :  %d ind.", nNISPobg[5]);
	m_CtrlLisSubPob.AddString(Cadena);
	Cadena.Format("Turno Tarde Teoria 5 horas :  %d ind.", nNISPobg[6]);
	m_CtrlLisSubPob.AddString(Cadena);
	Cadena.Format("Turno Tarde Teoria 4 horas :  %d ind.", nNISPobg[7]);
	m_CtrlLisSubPob.AddString(Cadena);
	Cadena.Format("Turno Tarde Teoria 3 horas :  %d ind.", nNISPobg[8]);
	m_CtrlLisSubPob.AddString(Cadena);
	Cadena.Format("Turno Tarde Teoria 2 horas :  %d ind.", nNISPobg[9]);
	m_CtrlLisSubPob.AddString(Cadena);

	// Halla el Desempeño Global de las Sub Poblaciones del turno noche
	nDGSPobg[10] = nDGSPobg[11] = nDGSPobg[12] = nDGSPobg[13] = nDGSPobg[14] = 0;
	for (i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotDocg; k++)
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}
		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;
		if(nCicCur<7 || sArrCTACDog[i][0]!='A')
			continue;
		if(nArrNHCDocg[i]!=6 && nArrNHCDocg[i]!=5 && nArrNHCDocg[i]!=4 &&
			nArrNHCDocg[i]!=3 && nArrNHCDocg[i]!=2) {
			continue;
		}
		nFunApt = 1.00/(nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i]+1);
		if(nArrNHCDocg[i]==6)	nDGSPobg[10] = nDGSPobg[10] + nFunApt;
		if(nArrNHCDocg[i]==5)	nDGSPobg[11] = nDGSPobg[11] + nFunApt;
		if(nArrNHCDocg[i]==4)	nDGSPobg[12] = nDGSPobg[12] + nFunApt;
		if(nArrNHCDocg[i]==3)	nDGSPobg[13] = nDGSPobg[13] + nFunApt;
		if(nArrNHCDocg[i]==2)	nDGSPobg[14] = nDGSPobg[14] + nFunApt;
	}
	nProAcu = 0;
	// Muestra el cromosoma y la penalidad de las subpoblaciones del turno noche
	nArrPSCInd[10]= nArrPSCInd[11]= nArrPSCInd[12]= nArrPSCInd[13]= nArrPSCInd[14]= 0;
	nArrProAcu[10]= nArrProAcu[11]= nArrProAcu[12]= nArrProAcu[13]= nArrProAcu[14]= 0;
	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotDocg; k++) {
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}
		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);
		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;
		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;
		if(nCicCur<7 || sArrCTACDog[i][0]!='A')
			continue;
		if(nArrNHCDocg[i]!=6 && nArrNHCDocg[i]!=5 && nArrNHCDocg[i]!=4 &&
			nArrNHCDocg[i]!=3 && nArrNHCDocg[i]!=2) {
			continue;
		}
		nULSPob = 8;
		if(nArrNHCDocg[i]==6)	nULSPob = 10;
		if(nArrNHCDocg[i]==5)	nULSPob = 11;
		if(nArrNHCDocg[i]==4)	nULSPob = 12;
		if(nArrNHCDocg[i]==3)	nULSPob = 13;
		if(nArrNHCDocg[i]==2)	nULSPob = 14;

		for(k=0; k<50; k++)
			if(sArrVarSPog[nULSPob][k][0]==0)
				break;
		nArrSubPobg[nULSPob][k] = i;	// Lista de elementos de la subpoblación noche
		nArrTSPoblg[nULSPob] = 'N';		// Turno de la subpoblacion noche

		CString abc1;
		j4=j5=j6=0;
		Cadena = "";
		strcpy_s(sCadPob,"00000000000000000000000000000000");
		nVal = (sArrCDCDocg[i][1]-'0')*10 + (sArrCDCDocg[i][2]-'0');
		for(j8=0; nVal; j8++) {
			if((5-j8)>=0)
				sCadPob[5-j8] = nVal%2+'0';
			nVal = nVal/2;
		}
		nDiaIni = nDiaFin = -1;
		for(j5=0; j5<6; j5++) {
			for(j4=0; j4<nNumTotAulg; j4++) {
				nDia=nHorIni=nHorFin=-1;
				for(j6=0; j6<18; j6++) {
					if( (!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3)) ||
						(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3)) ) {
						if(nDiaIni==-1)		nDiaIni = j5;
						if(nDiaIni == j5) {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(j8=0; nVal; j8++) {
								if((15-j8)>=0)
									sCadPob[15-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[16+j6] = '1';
							else
								if(j6<12) {
									if(nCicCur<7)	sCadPob[16+j6-6] = '1';
									if(nCicCur>6)	sCadPob[16] = '1';
								}
								else
									sCadPob[16+j6-11] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
						else {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(int j8=0; nVal; j8++) {
								if((25-j8)>=0)
									sCadPob[25-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[26+j6] = '1';
							else
								if(j6<12) {
									if(nCicCur<7)	sCadPob[26+j6-6] = '1';
									if(nCicCur>6)	sCadPob[26] = '1';
								}
								else
									sCadPob[26+j6-11] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
					}
				}
			}
		}
		nValPen = nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i];
		nFunApt = 1.00/(nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i]+1);
		nArrPSCInd[nULSPob] = nFunApt/nDGSPobg[nULSPob];
		nArrProAcu[nULSPob] = nArrProAcu[nULSPob]+nArrPSCInd[nULSPob];

		for(k=0; k<50; k++) {
			if(sArrVarSPog[nULSPob][k][0]==0)
				break;
		}
		nArrPASPobg[nULSPob][k]= nArrProAcu[nULSPob];	// Lista poblacion acumulativa subpoblación
		nArrPSSPobg[nULSPob][k]= nArrPSCInd[nULSPob];	// Lista de probabilidad de seleccion subpoblación
		strcpy_s(sArrVarSPog[nULSPob][k],sCadPob);		// Lista parte variable de la subpoblacion
		nNISPobg[nULSPob] = k+1;
	}
	Cadena.Format("Turno Noche Teoria 6 horas :  %d ind.", nNISPobg[10]);
	m_CtrlLisSubPob.AddString(Cadena);
	Cadena.Format("Turno Noche Teoria 5 horas :  %d ind.", nNISPobg[11]);
	m_CtrlLisSubPob.AddString(Cadena);
	Cadena.Format("Turno Noche Teoria 4 horas :  %d ind.", nNISPobg[12]);
	m_CtrlLisSubPob.AddString(Cadena);
	Cadena.Format("Turno Noche Teoria 3 horas :  %d ind.", nNISPobg[13]);
	m_CtrlLisSubPob.AddString(Cadena);
	Cadena.Format("Turno Noche Teoria 2 horas :  %d ind.", nNISPobg[14]);
	m_CtrlLisSubPob.AddString(Cadena);

	m_CtrlLisSP1.ResetContent();
	m_CtrlLisSP2.ResetContent();
	m_CtrlLisSP3.ResetContent();
	m_CtrlLisSP4.ResetContent();

	nProAcu = 0;
	// Muestra el cromosoma y la penalidad de la subpoblación del turno mañana 3 horas
	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotDocg; k++)
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}
		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);
		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;

		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;
		if(nCicCur>3)
			continue;
		// No considera si no es 6 horas y no es toria
		if(nArrNHCDocg[i]!=3 || sArrCTACDog[i][0]!='A') {
			continue;
		}
		CString abc1;
		j4=j5=j6=0;
		Cadena = "";
		strcpy_s(sCadPob,"00000000000000000000000000000000");
		nVal = (sArrCDCDocg[i][1]-'0')*10 + (sArrCDCDocg[i][2]-'0');
		for(j8=0; nVal; j8++) {
			if((5-j8)>=0)
				sCadPob[5-j8] = nVal%2+'0';
			nVal = nVal/2;
		}
		nDiaIni = nDiaFin = -1;
		for(j5=0; j5<6; j5++) {
			for(j4=0; j4<nNumTotAulg; j4++) {
				nDia=nHorIni=nHorFin=-1;
				for(j6=0; j6<18; j6++) {
					if( (!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3)) ||
						(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3)) ) {
						if(nDiaIni==-1)		nDiaIni = j5;
						if(nDiaIni == j5) {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(j8=0; nVal; j8++) {
								if((15-j8)>=0)
									sCadPob[15-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[16+j6] = '1';
							else
								if(j6<12) {
									if(nCicCur<7)	sCadPob[16+j6-6] = '1';
									if(nCicCur>6)	sCadPob[16] = '1';
								}
								else
									sCadPob[16+j6-11] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
						else {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(int j8=0; nVal; j8++) {
								if((25-j8)>=0)
									sCadPob[25-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[26+j6] = '1';
							else
								if(j6<12) {
									if(nCicCur<7)	sCadPob[26+j6-6] = '1';
									if(nCicCur>6)	sCadPob[26] = '1';
								}
								else
									sCadPob[26+j6-11] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
					}
				}
			}
		}
		nValPen = nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i];
		nFunApt = 1.00/(nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i]+1);
		nPSCInd = nFunApt/nDGSPobg[3];
		nProAcu = nProAcu + nPSCInd;

		if(sArrCGCDocg[i][0]=='0')
			Cadena.Format("%s %s T %-6.6s %-6.6s %-10.10s %s %3d %5.3lf %5.2lf %lf %lf",
			sArrCCCDocg[i], sArrCGCDocg[i],sCadPob,sCadPob+6,sCadPob+12,sCadPob+22,
			nValPen+1, nFunApt, nDGSPobg[3],nPSCInd,nProAcu);
		else
			Cadena.Format("%s %s L %-6.6s %-6.6s %-10.10s %s %3d %5.3lf %5.2lf %lf %lf",
			sArrCCCDocg[i], sArrCGCDocg[i],sCadPob,sCadPob+6,sCadPob+12,sCadPob+22,
			nValPen+1, nFunApt, nDGSPobg[3],nPSCInd,nProAcu);
		m_CtrlLisSP1.AddString(Cadena);
	}

	nProAcu = 0;
	// Muestra el cromosoma y la penalidad de la subpoblación del turno tarde 4 horas
	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotDocg; k++)
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
		for(k=0; k<nNumTotCurg; k++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
				nPosCur = k;
				break;
			}
		}

		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);

		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;

		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;
		if(nCicCur<4 || nCicCur>6)
			continue;
		if(nArrNHCDocg[i]!=3 || sArrCTACDog[i][0]!='A') {
//		if(nArrNHCDocg[i]!=4 || sArrCTACDog[i][0]!='A') {
			continue;
		}

		CString abc1;
		j4=j5=j6=0;
		Cadena = "";
		strcpy_s(sCadPob,"00000000000000000000000000000000");
		nVal = (sArrCDCDocg[i][1]-'0')*10 + (sArrCDCDocg[i][2]-'0');
		for(j8=0; nVal; j8++) {
			if((5-j8)>=0)
				sCadPob[5-j8] = nVal%2+'0';
			nVal = nVal/2;
		}
		nDiaIni = nDiaFin = -1;
		for(j5=0; j5<6; j5++) {
			for(j4=0; j4<nNumTotAulg; j4++) {
				nDia=nHorIni=nHorFin=-1;
				for(j6=0; j6<18; j6++) {
					if( (!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3)) ||
						(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3)) ) {
						if(nDiaIni==-1)		nDiaIni = j5;
						if(nDiaIni == j5) {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(j8=0; nVal; j8++) {
								if((15-j8)>=0)
									sCadPob[15-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[16+j6] = '1';
							else
								if(j6<12) {
									if(nCicCur<7)	sCadPob[16+j6-6] = '1';
									if(nCicCur>6)	sCadPob[16] = '1';
								}
								else
									sCadPob[16+j6-11] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
						else {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(int j8=0; nVal; j8++) {
								if((25-j8)>=0)
									sCadPob[25-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[26+j6] = '1';
							else
								if(j6<12) {
									if(nCicCur<7)	sCadPob[26+j6-6] = '1';
									if(nCicCur>6)	sCadPob[26] = '1';
								}
								else
									sCadPob[26+j6-11] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
					}
				}
			}
		}
		nValPen = nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i];
		nFunApt = 1.00/(nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i]+1);
		nPSCInd = nFunApt/nDGSPobg[7];
		nProAcu = nProAcu + nPSCInd;

		if(sArrCGCDocg[i][0]=='0')
			Cadena.Format("%s %s T %-6.6s %-6.6s %-10.10s %s %3d %5.3lf %5.2lf %lf %lf",
			sArrCCCDocg[i], sArrCGCDocg[i],sCadPob,sCadPob+6,sCadPob+12,sCadPob+22,
			nValPen+1, nFunApt, nDGSPobg[7],nPSCInd,nProAcu);
		else
			Cadena.Format("%s %s L %-6.6s %-6.6s %-10.10s %s %3d %5.3lf %5.2lf %lf %lf",
			sArrCCCDocg[i], sArrCGCDocg[i],sCadPob,sCadPob+6,sCadPob+12,sCadPob+22,
			nValPen+1, nFunApt, nDGSPobg[7],nPSCInd,nProAcu);
		m_CtrlLisSP3.AddString(Cadena);
	}
	m_CtrlGNPobl.EnableWindow(true);
	UpdateData(false);
	bd1.Close();
	szNombreFi = "LTieGen.txt";
	if (!bd1.Open(szNombreFi, CFile::modeCreate | CFile::modeWrite)) {
		AfxMessageBox("No se puede  abrir el fichero");
		return;
	}
	for (int i5=0; i5<nNumPobg; i5++) {
		Cadena.Format("%02d %5ld", i5+1, nArrTGPoblg[i5]);
		strcpy_s(sCad, Cadena);
		bd1.Write(sCad, strlen(sCad));
		sCad[0]=13;
		sCad[1]=10;
		sCad[2]=0;
		bd1.Write(sCad, strlen(sCad));
	}
	bd1.Close();

}

void CDlgProAdi::OnGnpobl() 
{
	// TODO: Add your control notification handler code here
	CString Cadena, Cadena1;
	int i, k, i3, k1;
	int nPosCur;				// Posición en la lista de cursos
	int nCicCur;				// Ciclo al cual pertenece el curso
	int nPosDoc;
	int j4, j5, j6, j8;
	char sCad[121];
	char sCadPob[51];
	int nVal;
	int nDia;
	int nHorIni;
	int nHorFin;
	int nDiaIni;
	int nDiaFin;
	int nNumInd;
	int nValPen;
	double nFunApt;
	double nPSCInd;
	double nProAcu;
	double nValAle1;
	double nValAle2;
	double nPSMeno;
	int nUMProb[3];		// Arreglo ubicacion de menor probabilidad
	int nUSele1;		// Ubicacion de seleccion 1
	int nUSele2;		// Ubicacion de seleccion 2
	char sCad1[121], sCad2[121];
	int nUbiAul;		// Ubicacion en la lista de aulas
	int nConDia;		// Contador de dias
	int nHIBusq;		// Hora inicial de busqueda
	int nIACorr;		// Indicador de asignación correcta
	int nISPadr;		// Indicador de selección de padre
	char sArrHDAAul[41][6][18][10];	// Lista 1 de horas disponibles y asignadas por aula
									// los 6 dias de la semana y las 16 horas del dia
									// los valores son: D(Disponible), Curso y grupo asignado
	char sArrHDAAu2[41][6][18][10];	// Lista 1 de horas disponibles y asignadas por aula
									// los 6 dias de la semana y las 16 horas del dia
									// los valores son: D(Disponible), Curso y grupo asignado
	char sArrHDACic[10][6][18][3];		// Lista de horas disponibles y asignadas por ciclos
										// los 6 dias de la semana y las 16 horas del dia
										// los valores son: D(Disponlble), Codigo de curso
	char sArrHDADoc[200][6][18];	// Lista de horas disponibles y asignadas por docente
									// los 6 dias de la semana y las 16 horas del dia
									// los valores son: D(Disponlble) A(Asignado)
	char sArrVarSPo[20][50][100];	// Parte variable de la subpoblación
	int nNVRCHU;		// Número de veces que realiza cambios en cadena hijo uno
	int nNCDias;		// Numero de cadenas dias
	int nNEPCHo;		// No. de elementos primera cadena de horas
	int nNESCHo;		// No. de elementos segunda cadena de horas
	int abc1=0;
	int abc2=0;
	char sArrCodCur[100][4];		// Arreglo codigos de curso
	int nArrNHACur[100];			// Arreglo numero de horas a asignar del curso
	int nArrNHDCur[100];			// Arreglo numero de horas disponible del curso

	i3 = 0;

	CString xxyy;
	long ntime = 0;
	LARGE_INTEGER ntime1, ntime2;
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&ntime1);

	// Inicializa listas 1 y 2 de dias y horas por aula
	for(j4=0; j4<41; j4++) {
		for(j5=0; j5<6; j5++) {
			for(j6=0; j6<18; j6++) {
				sArrHDAAul[j4][j5][j6][0]=sArrHDAAul[j4][j5][j6][1]=0;
				sArrHDAAu2[j4][j5][j6][0]=sArrHDAAu2[j4][j5][j6][1]=0;
			}
		}
	}
	// Inicializa las variables asignación dias y horas por ciclo
	for(j4=0; j4<10; j4++) {
		for(j5=0; j5<6; j5++) {
			for(j6=0; j6<18; j6++) {
				sArrHDACic[j4][j5][j6][0]=0;
			}
		}
	}
	// Inicializa las variables asignación dias y horas por docente
	for(j4=0; j4<200; j4++) {
		for(j5=0; j5<6; j5++) {
			for(j6=0; j6<18; j6++) {
				sArrHDADoc[j4][j5][j6]=0;
			}
		}
	}
	// Inicializa la parte variable de las subpoblaciones
	for(j4=0; j4<20; j4++) {
		for(j5=0; j5<50; j5++) {
			sArrVarSPo[j4][j5][0] = 0;
		}
	}
	nUSele1 = nUSele2 = 0;
	srand((unsigned)time(NULL));
	// Realiza el proceso de todas las sub poblaciones
	for(int i2=0; i2<20; i2++) {
		// Si la poblacion tiene 2 o más individuos
//		if( nNISPobg[i2]>2 || (nNumPobg>5 && nNISPobg[i2]>1) ) {
		if( nNISPobg[i2]>1) {
			nHIBusq = 0;
			if(nArrTSPoblg[i2]=='T')		nHIBusq = 6;
			if(nArrTSPoblg[i2]=='N')		nHIBusq = 11;
			nUSele1 = nUSele2 = 0;
			// Selecciona el primer padre
			nValAle1 = drand48();
			for(k=0; nArrPSSPobg[i2][k]>0; k++) {
				if(k==0) {
					if(nValAle1<=nArrPASPobg[i2][k]) {
						nUSele1 = k;
						break;
					}
				}
				else {
					if(nValAle1>nArrPASPobg[i2][k-1] && nValAle1<=nArrPASPobg[i2][k]) {
						nUSele1 = k;
						break;
					}
				}
			}
			// Selecciona el segundo padre
			// tiene que ser diferente al primero
			nISPadr = 0;
			while (nISPadr == 0) {
				nValAle2 = drand48();
				for(k=0; nArrPSSPobg[i2][k]>0; k++) {
					if(k==0) {
						if(nValAle2<=nArrPASPobg[i2][k] && nUSele1!=k) {
							nUSele2 = k;
							nISPadr = 1;
							break;
						}
					}
					else {
						if(nValAle2>nArrPASPobg[i2][k-1] && nValAle2<=nArrPASPobg[i2][k] &&
							nUSele1!=k) {
			   				nUSele2 = k;
							nISPadr = 1;
							break;
						}
					}
				}
			}
			// Selecciona el primer menor
			nPSMeno = 0;
			nUMProb[0] = 0;
			for(k=0; nArrPSSPobg[i2][k]>0; k++) {
				if(nPSMeno==0) {
					nUMProb[0] = k;
					nPSMeno = nArrPSSPobg[i2][k];
				}
				else {
					if(nArrPSSPobg[i2][k]<=nPSMeno) {
//					if(nArrPSSPobg[i2][k]<nPSMeno) {
						nUMProb[0] = k;
						nPSMeno = nArrPSSPobg[i2][k];
					}
				}
			}
			// Selecciona el menor
			if(nNumPobg==4 || nNumPobg==5) {
				nPSMeno = 0;
				for(k=0; nArrPSSPobg[i2][k]>0; k++) {
					if(nPSMeno==0 && nUMProb[0] != k ) {
						nUMProb[1] = k;
						nPSMeno = nArrPSSPobg[i2][k];
					}
					else {
						if(nArrPSSPobg[i2][k]<nPSMeno && nUMProb[0] != k ) {
							nUMProb[1] = k;
							nPSMeno = nArrPSSPobg[i2][k];
						}
					}
				}
				nUMProb[0] = nUMProb[1];
				nUMProb[1] = 0;
			}
			// Selecciona el menor
			// Poblac. 6,7,8,9    16, 17, 18, 19
//			if((nNumPobg>5 && nNumPobg<10) || (nNumPobg>15 && nNumPobg<20)) {
			IniCadTip();
			if(nNumPobg>8 && (nNumPobg%2==0)) {
				IniCadTi1();
				nValAle1 = drand48();
				for(k=0; nArrPSSPobg[i2][k]>0; k++) {
					if(k==0) {
						if(nValAle1<=nArrPASPobg[i2][k]) {
							nUMProb[1] = k;
							break;
						}
					}
					else {
						if(nValAle1>nArrPASPobg[i2][k-1] && nValAle1<=nArrPASPobg[i2][k]) {
							nUMProb[1] = k;
							break;
						}
					}
				}
				nUMProb[0] = nUMProb[1];
				nUMProb[1] = 0;
			}
/*			if( nNumPobg==12 || nNumPobg==13 || nNumPobg==32 || nNumPobg==33)
				nUMProb[0]=0; 
			if( nNumPobg==14 || nNumPobg==15 || nNumPobg==34 || nNumPobg==35)
				nUMProb[0]=1; 
			if( nNISPobg[i2]>2) {
				if( nNumPobg==16 || nNumPobg==17 || nNumPobg==36 || nNumPobg==37)
					nUMProb[0]=2; 
			}
			if( nNISPobg[i2]>3) {
				if( nNumPobg==18 || nNumPobg==19 || nNumPobg==38 || nNumPobg==39)
					nUMProb[0]=3; 
			}
			if( nNISPobg[i2]>4) {
				if( nNumPobg==20 || nNumPobg==21) nUMProb[0]=4; 
			}
			if( nNISPobg[i2]>5) {
				if( nNumPobg==22 || nNumPobg==23) nUMProb[0]=5; 
			}
			if( nNISPobg[i2]>6) {
				if( nNumPobg==22 || nNumPobg==23) nUMProb[0]=6; 
			}
*/
			if( (nNumPobg<10 || (nNumPobg>9 && (nNumPobg%2==1))) &&
				(nArrPCCDocg[nArrSubPobg[i2][nUMProb[0]]]+
				nArrPACDocg[nArrSubPobg[i2][nUMProb[0]]]+
				nArrPDCDocg[nArrSubPobg[i2][nUMProb[0]]]) == 0)
				continue;
			// Inicializa listas 1 y 2 de dias y horas por aula
			for(j4=0; j4<41; j4++) {
				for(j5=0; j5<6; j5++) {
					for(j6=0; j6<18; j6++) {
						sArrHDAAul[j4][j5][j6][0]=sArrHDAAul[j4][j5][j6][1]=0;
						sArrHDAAu2[j4][j5][j6][0]=sArrHDAAu2[j4][j5][j6][1]=0;
					}
				}
			}
			// Inicializa las variables asignación dias y horas por ciclo
			for(j4=0; j4<10; j4++) {
				for(j5=0; j5<6; j5++) {
					for(j6=0; j6<18; j6++) {
						sArrHDACic[j4][j5][j6][0]=0;
					}
				}
			}
			// Inicializa las variables asignación dias y horas por docente
			for(j4=0; j4<200; j4++) {
				for(j5=0; j5<6; j5++) {
					for(j6=0; j6<18; j6++) {
						sArrHDADoc[j4][j5][j6]=0;
					}
				}
			}	
			// Revisa el elemento menor y asigna como disponible
			// su aula hora y dia
			i3=0;
			// Halla el ciclo al cual pertenece el curso
			nPosCur = 0;
			for(k=0; k<nNumTotCurg; k++) {
				if(!strncmp(sArrCCCDocg[nArrSubPobg[i2][nUMProb[0]]], sArrCodCurg[k], 3)) {
					nPosCur = k;
					break;
				}
			}
			nPosDoc = 0;
			for(k=0; k<nNumTotDocg; k++) {
				if(!strncmp(sArrCDCDocg[nArrSubPobg[i2][nUMProb[0]]], sArrCodDocg[k], 3)) {
					nPosDoc = k;
					break;
				}
			}
			nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 + sArrCicCurg[nPosCur][1]-'0';
			nCicCur--;
			if(nCicCur<0 || nCicCur>9)
				nCicCur = 0;
			nConDia = 0;
			for(int i5=0; i5<6; i5++) {		// Revisa los seis dias
				if(sArrVarSPog[i2][nUMProb[i3]][6+i5]=='1') {	// El dia es seleccionado
					// Halla la ubicacion del aula
					nUbiAul = (sArrVarSPog[i2][nUMProb[i3]][12+(nConDia*10)]-'0')*8;
					nUbiAul = nUbiAul + (sArrVarSPog[i2][nUMProb[i3]][13+(nConDia*10)]-'0')*4;
					nUbiAul = nUbiAul + (sArrVarSPog[i2][nUMProb[i3]][14+(nConDia*10)]-'0')*2;
					nUbiAul = nUbiAul + (sArrVarSPog[i2][nUMProb[i3]][15+(nConDia*10)]-'0');
					nUbiAul = nUbiAul - 1;
					for(int i6=0; i6<6; i6++) {		// Revisa las horas
						if(sArrVarSPog[i2][nUMProb[i3]][16+(nConDia*10)+i6]=='1') {
							if( !strncmp(sArrHDAAulg[nUbiAul][i5][i6+nHIBusq],sArrCCCDocg[nArrSubPobg[i2][nUMProb[i3]]],3) &&
								!strncmp(sArrHDAAulg[nUbiAul][i5][i6+nHIBusq]+3,sArrCDCDocg[nArrSubPobg[i2][nUMProb[i3]]],3) &&
								!strncmp(sArrHDAAulg[nUbiAul][i5][i6+nHIBusq]+6,sArrCGCDocg[nArrSubPobg[i2][nUMProb[i3]]],3)){
								sArrHDAAul[nUbiAul][i5][i6+nHIBusq][0]=sArrHDAAulg[nUbiAul][i5][i6+nHIBusq][0];
								sArrHDAAul[nUbiAul][i5][i6+nHIBusq][1]=sArrHDAAulg[nUbiAul][i5][i6+nHIBusq][1];
								sArrHDAAulg[nUbiAul][i5][i6+nHIBusq][0]='D';
								sArrHDAAulg[nUbiAul][i5][i6+nHIBusq][1]=0;
								sArrHDACic[nCicCur][i5][i6+nHIBusq][0]=sArrHDACicg[nCicCur][i5][i6+nHIBusq][0];
								sArrHDACicg[nCicCur][i5][i6+nHIBusq][0]='D';
								sArrHDADoc[nPosDoc][i5][i6+nHIBusq]='A';
								sArrHDADocg[nPosDoc][i5][i6+nHIBusq]='D';
							}
							if( !strncmp(sArrHDAAu2g[nUbiAul][i5][i6+nHIBusq],sArrCCCDocg[nArrSubPobg[i2][nUMProb[i3]]],3) &&
								!strncmp(sArrHDAAu2g[nUbiAul][i5][i6+nHIBusq]+3,sArrCDCDocg[nArrSubPobg[i2][nUMProb[i3]]],3) &&
								!strncmp(sArrHDAAu2g[nUbiAul][i5][i6+nHIBusq]+6,sArrCGCDocg[nArrSubPobg[i2][nUMProb[i3]]],3)){
								sArrHDAAu2[nUbiAul][i5][i6+nHIBusq][0]=sArrHDAAu2g[nUbiAul][i5][i6+nHIBusq][0];
								sArrHDAAu2[nUbiAul][i5][i6+nHIBusq][1]=sArrHDAAu2g[nUbiAul][i5][i6+nHIBusq][1];
								sArrHDAAu2g[nUbiAul][i5][i6+nHIBusq][0]='D';
								sArrHDAAu2g[nUbiAul][i5][i6+nHIBusq][1]=0;
								if(!strncmp(sArrHDACicg[nCicCur][i5][i6+nHIBusq],sArrCCCDocg[nArrSubPobg[i2][nUMProb[i3]]],3) ) {
									sArrHDACic[nCicCur][i5][i6+nHIBusq][0]=sArrHDACicg[nCicCur][i5][i6+nHIBusq][0];
									sArrHDACicg[nCicCur][i5][i6+nHIBusq][0]='D';
								}
								sArrHDADoc[nPosDoc][i5][i6+nHIBusq]='A';
								sArrHDADocg[nPosDoc][i5][i6+nHIBusq]='D';
							}
						}
					}
					nConDia++;
				}
			}
			// Va a crear la cadena hijo
			strcpy_s(sCad1, "00000000000000000000");
			strncpy(sCad1+6,sArrVarSPog[i2][nUSele1]+6, 6);
			strncpy(sCad1+12,sArrVarSPog[i2][nUSele2]+12, 4);
			strncpy(sCad1+16,sArrVarSPog[i2][nUSele1]+16, 6);
			strncpy(sCad1+22,sArrVarSPog[i2][nUSele2]+22, 4);
			strncpy(sCad1+26,sArrVarSPog[i2][nUSele1]+26, 6);
			if(nCicCur == 0 || nCicCur == 4)	strncpy(sCad1+12, "0001", 4);
			if(nCicCur == 1 || nCicCur == 5)	strncpy(sCad1+12, "0010", 4);
			if(nCicCur == 2 || nCicCur == 6)	strncpy(sCad1+12, "0011", 4);
			if(nCicCur == 3 || nCicCur == 7)	strncpy(sCad1+12, "0100", 4);
			if(nCicCur == 8)					strncpy(sCad1+12, "0101", 4);
			if(nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==6 ||
				nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==5 ||
				nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==4) {
				if(nCicCur == 0 || nCicCur == 4)	strncpy(sCad1+22, "0001", 4);
				if(nCicCur == 1 || nCicCur == 5)	strncpy(sCad1+22, "0010", 4);
				if(nCicCur == 2 || nCicCur == 6)	strncpy(sCad1+22, "0011", 4);
				if(nCicCur == 3 || nCicCur == 7)	strncpy(sCad1+22, "0100", 4);
				if(nCicCur == 8)					strncpy(sCad1+22, "0101", 4);
			}
			CString xyz2;
			xyz2.Format("Cadena 1 %s %-6.6s %-4.4s %s %s %s nCicCur %d nHIBusq %d",
				sArrCCCDocg[nArrSubPobg[i2][nUMProb[0]]], sCad1+6, sCad1+12, sCad1+16,
				sArrHDACicg[8][5][11],sArrHDACicg[8][5][13], nCicCur, nHIBusq);
				
//			AfxMessageBox(xyz2);
			// Guarda la cadena que van a ser cambiadas
			strncpy(sArrVarSPo[i2][nUMProb[0]]+6, sArrVarSPog[i2][nUMProb[0]]+6, 26);
			// Cambia la cadena
			strncpy(sArrVarSPog[i2][nUMProb[0]]+6,sCad1+6, 26);
			nIACorr = 0;
			nNVRCHU= 0;		// Número de veces que realiza cambios en cadena hijo uno
			nNCDias= 6;		// Numero de cadenas dias
			nNEPCHo = 4;	// No. de elementos primera cadena de horas
			nNESCHo = 0;	// No. de elementos segunda cadena de horas
			abc1 = 0;
			abc2 = 0;
			while(1) {
				if(nIACorr==0) {   // Revisa 
					// Revisa si hay disponibilidad para asignar el dia, aula y hora
					// de los dos hijos
					i3=0;
					nConDia = 0;
					for(int i5=0; i5<6; i5++) {		// Revisa los seis dias
						if(sArrVarSPog[i2][nUMProb[i3]][6+i5]=='1') {	// El dia es seleccionado
							// Halla la ubicacion del aula
							nUbiAul = (sArrVarSPog[i2][nUMProb[i3]][12+(nConDia*10)]-'0')*8;
							nUbiAul = nUbiAul + (sArrVarSPog[i2][nUMProb[i3]][13+(nConDia*10)]-'0')*4;
							nUbiAul = nUbiAul + (sArrVarSPog[i2][nUMProb[i3]][14+(nConDia*10)]-'0')*2;
							nUbiAul = nUbiAul + (sArrVarSPog[i2][nUMProb[i3]][15+(nConDia*10)]-'0');
							nUbiAul = nUbiAul - 1;
							for(int i6=0; i6<6; i6++) {		// Revisa la seis horas
								if(sArrVarSPog[i2][nUMProb[i3]][16+(nConDia*10)+i6]=='1') {
									nIACorr = 2;
									if(sArrHDAAulg[nUbiAul][i5][i6+nHIBusq][0]=='D' &&
										sArrHDACicg[nCicCur][i5][i6+nHIBusq][0]=='D' &&
										sArrHDADocg[nPosDoc][i5][i6+nHIBusq]=='D') {
										nIACorr = 1;
									}
//									else {
//										if(sArrHDAAu2g[nUbiAul][i5][i6+nHIBusq][0]=='D') {
//											nIACorr = 1;
//										}
//									}
									if(nIACorr==2) {
										CString hhh;
										hhh.Format("REVISA LAS DOS MATRICES Y NO HALLA LIBRE PARA EL CURSO: %s nCicCur %d nUbiAul %d  i5 %d  i6 %d",
											sArrCCCDocg[nArrSubPobg[i2][nUMProb[i3]]], nCicCur, nUbiAul, i5, i6);
//										AfxMessageBox(hhh);
										break;
									}
								}
							}
							nConDia++;
						}
						if(nIACorr==2) break;
					}
				}
//				if((nNVRCHU+1)==nNCDias) break;
//				if(nNVRCHU==4) break;
				if(nIACorr==2) {
					if(!strncmp(sArrCCCDocg[nArrSubPobg[i2][nUMProb[0]]],"C45", 3) ) {
						CString xyz2;
						xyz2.Format("Cambiara Cadena 1 %s %-6.6s %-4.4s %-6.6s %-4.4s %-6.6s %s %s %s %s",
							sArrCCCDocg[nArrSubPobg[i2][nUMProb[0]]],
							sArrVarSPog[i2][nUMProb[0]]+6,
							sArrVarSPog[i2][nUMProb[0]]+12,
							sArrVarSPog[i2][nUMProb[0]]+16,
							sArrVarSPog[i2][nUMProb[0]]+22,
							sArrVarSPog[i2][nUMProb[0]]+26,
							sArrHDAAulg[4][4][14],sArrHDAAulg[4][4][15],sArrHDAAulg[4][4][16],
							sArrHDAAulg[4][4][17]);
//							AfxMessageBox(xyz2);
					}
					if(nNESCHo==0 )		abc2 = 0;
					if(abc1==nNEPCHo && abc2==nNESCHo) {
						nNVRCHU++;
						abc1=0;
						abc2=0;
					}
					if(nNVRCHU==nNCDias) break;
					if(abc2==nNESCHo) {
						abc2=0;
					}
					if(nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==6 ||
						nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==5 ||
						nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==4) {
						if(nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==6) {
							nNEPCHo = 4;  // No. de elementos primera cadena de horas
							nNESCHo = 4;  // No. de elementos segunda cadena de horas
						}
						if(nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==5) {
							nNEPCHo = 4;  // No. de elementos primera cadena de horas
							nNESCHo = 5;  // No. de elementos segunda cadena de horas
						}
						if(nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==4) {
							nNEPCHo = 5;  // No. de elementos primera cadena de horas
							nNESCHo = 5;  // No. de elementos segunda cadena de horas
						}
						nNCDias = 10;		// Numero de cadenas dias
						strncpy(sArrVarSPog[i2][nUMProb[0]]+6, sArrTCDDig[nNVRCHU], 6);
						if(nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==6) {
							strncpy(sArrVarSPog[i2][nUMProb[0]]+16, sArrTCTHog[abc1], 6);
							strncpy(sArrVarSPog[i2][nUMProb[0]]+26, sArrTCTHog[abc2], 6);
						}
						if(nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==5) {
							strncpy(sArrVarSPog[i2][nUMProb[0]]+16, sArrTCTHog[abc1], 6);
							strncpy(sArrVarSPog[i2][nUMProb[0]]+26, sArrTCDHog[abc2], 6);
						}
						if(nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==4) {
							strncpy(sArrVarSPog[i2][nUMProb[0]]+16, sArrTCDHog[abc1], 6);
							strncpy(sArrVarSPog[i2][nUMProb[0]]+26, sArrTCDHog[abc2], 6);
						}
					}
					if(nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==3 ||
						nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==2) {
						if(nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==3) {
							nNEPCHo = 4;  // No. de elementos primera cadena de horas
							nNESCHo = 0;  // No. de elementos segunda cadena de horas
						}
						if(nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==2) {
							nNEPCHo = 5;  // No. de elementos primera cadena de horas
							nNESCHo = 0;  // No. de elementos segunda cadena de horas
						}
						nNCDias = 6;		// Numero de cadenas dias
						strncpy(sArrVarSPog[i2][nUMProb[0]]+6, sArrTCUDig[nNVRCHU], 6);
						if(nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==3) {
							strncpy(sArrVarSPog[i2][nUMProb[0]]+16, sArrTCTHog[abc1], 6);
							CString xyz2;
							xyz2.Format("abc1 %d  abc2 %d  %s   ", abc1, abc2,
								sArrVarSPog[i2][nUMProb[0]]+12);
//							AfxMessageBox(xyz2);
						}
						if(nArrNHCDocg[nArrSubPobg[i2][nUMProb[0]]]==2) {
							strncpy(sArrVarSPog[i2][nUMProb[0]]+16, sArrTCDHog[abc1], 6);
						}
					}
					abc2++;
					if(nNESCHo==0 || abc2 == nNESCHo ) {
						CString xyz1;
						xyz1.Format("abc1 %d abc2 %d nNESCHo %d", abc1, abc2, nNESCHo);
//						AfxMessageBox(xyz1);
						abc1++;
//						abc2 = 0;
					}
					nIACorr=0;
				}
				else {
					break;
				}
			}
			// NO hay dia, aula y hora para los hijos, vuelve a valores anteriores
			if((nIACorr==2)) {
//				AfxMessageBox("NO Paso Tod");
				CString hhh;
				hhh.Format("NO CAMBIA EL CURSO: %s %s %s",
					sArrCCCDocg[nArrSubPobg[i2][nUMProb[i3]]], sArrCDCDocg[nArrSubPobg[i2][nUMProb[i3]]],
					sArrCGCDocg[nArrSubPobg[i2][nUMProb[i3]]]);
//				AfxMessageBox(hhh);
				strncpy(sArrVarSPog[i2][nUMProb[0]]+6, sArrVarSPo[i2][nUMProb[0]]+6, 26);
				for(j4=0; j4<41; j4++) {
					for(j5=0; j5<6; j5++) {
						for(j6=0; j6<18; j6++) {
							if(sArrHDAAul[j4][j5][j6][0]) {
								sArrHDAAulg[j4][j5][j6][0]=sArrHDAAul[j4][j5][j6][0];
								sArrHDAAulg[j4][j5][j6][1]=sArrHDAAul[j4][j5][j6][1];
								sArrHDAAul[j4][j5][j6][0]=0;
							}
							if(sArrHDAAu2[j4][j5][j6][0]) {
								sArrHDAAu2g[j4][j5][j6][0]=sArrHDAAu2[j4][j5][j6][0];
								sArrHDAAu2g[j4][j5][j6][1]=sArrHDAAu2[j4][j5][j6][1];
								sArrHDAAu2[j4][j5][j6][0]=0;
							}
						}
					}
				}
				// Recupera las variables asignación dias y horas por ciclo
				for(j4=0; j4<10; j4++) {
					for(j5=0; j5<6; j5++) {
						for(j6=0; j6<18; j6++) {
							if(sArrHDACic[j4][j5][j6][0]) {
								sArrHDACicg[j4][j5][j6][0]= sArrHDACic[j4][j5][j6][0];
								sArrHDACic[j4][j5][j6][0]=0;
							}
						}
					}
				}
				// Recupera las variables asignación dias y horas por docente
				for(j4=0; j4<200; j4++) {
					for(j5=0; j5<6; j5++) {
						for(j6=0; j6<18; j6++) {
							if(sArrHDADoc[j4][j5][j6]) {
								sArrHDADocg[j4][j5][j6]='A';
								sArrHDADoc[j4][j5][j6]=0;
							}
						}
					}
				}	
			}
			// SI hay dia, aula y hora para los hijos, realiza la asignación
			else {
				for(i3=0; i3<1; i3++) {		// Revisa los dos elementos menores
					nConDia = 0;
					for(int i5=0; i5<6; i5++) {		// Revisa los seis dias
						if(sArrVarSPog[i2][nUMProb[i3]][6+i5]=='1') {	// El dia es seleccionado
							// Halla la ubicacion del aula
							nUbiAul = (sArrVarSPog[i2][nUMProb[i3]][12+(nConDia*10)]-'0')*8;
							nUbiAul = nUbiAul + (sArrVarSPog[i2][nUMProb[i3]][13+(nConDia*10)]-'0')*4;
							nUbiAul = nUbiAul + (sArrVarSPog[i2][nUMProb[i3]][14+(nConDia*10)]-'0')*2;
							nUbiAul = nUbiAul + (sArrVarSPog[i2][nUMProb[i3]][15+(nConDia*10)]-'0');
							nUbiAul = nUbiAul - 1;
							for(int i6=0; i6<6; i6++) {		// Revisa las horas
								if(sArrVarSPog[i2][nUMProb[i3]][16+(nConDia*10)+i6]=='1') {
									if( !strncmp(sArrCCCDocg[nArrSubPobg[i2][nUMProb[i3]]],"C01", 3)) {
										CString bcd;
										bcd.Format("%-6.6s %-4.4s %-6.6s %-4.4s %-6.6s i5 %d i6 %d",
											sArrVarSPog[i2][nUMProb[i3]]+6,sArrVarSPog[i2][nUMProb[i3]]+12,
											sArrVarSPog[i2][nUMProb[i3]]+16, sArrVarSPog[i2][nUMProb[i3]]+22,
											sArrVarSPog[i2][nUMProb[i3]]+26, i5, i6);
//										AfxMessageBox(bcd);
									}
									if(sArrHDAAulg[nUbiAul][i5][i6+nHIBusq][0]=='D') {
										strncpy(sArrHDAAulg[nUbiAul][i5][i6+nHIBusq],sArrCCCDocg[nArrSubPobg[i2][nUMProb[i3]]],3);
										strncpy(sArrHDAAulg[nUbiAul][i5][i6+nHIBusq]+3,sArrCDCDocg[nArrSubPobg[i2][nUMProb[i3]]],3);
										strncpy(sArrHDAAulg[nUbiAul][i5][i6+nHIBusq]+6,sArrCGCDocg[nArrSubPobg[i2][nUMProb[i3]]],3);
										strncpy(sArrHDACicg[nCicCur][i5][i6+nHIBusq], sArrCCCDocg[nArrSubPobg[i2][nUMProb[i3]]], 3);
										sArrHDADocg[nPosDoc][i5][i6+nHIBusq]='A';
									}
									else {
										if(sArrHDAAu2g[nUbiAul][i5][i6+nHIBusq][0]=='D') {
											strncpy(sArrHDAAu2g[nUbiAul][i5][i6+nHIBusq],sArrCCCDocg[nArrSubPobg[i2][nUMProb[i3]]],3);
											strncpy(sArrHDAAu2g[nUbiAul][i5][i6+nHIBusq]+3,sArrCDCDocg[nArrSubPobg[i2][nUMProb[i3]]],3);
											strncpy(sArrHDAAu2g[nUbiAul][i5][i6+nHIBusq]+6,sArrCGCDocg[nArrSubPobg[i2][nUMProb[i3]]],3);
										}
										else {
											CString hhh;
											hhh.Format("ERROR - SE HALLO LIBRE PERO NO SE ASIGNA CURSO:%s  i5 %d  i6 %d",
												sArrCCCDocg[nArrSubPobg[i2][nUMProb[i3]]], i5, i6);
											AfxMessageBox(hhh);
										}
									}
								}
							}
							nConDia++;
						}
					}
				}
			}
			if(i2==3) {
				nNumInd = 0;
				nProAcu = 0;
				// Muestra el cromosoma y la penalidad de la subpoblación 0
				m_CtrlLisSP2.ResetContent();
				for(i=0; i<nNumTotCDog; i++) {
					for(k=0; k<nNumTotDocg; k++)
						if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
							nPosDoc = k;
							break;
						}
					for(k=0; k<nNumTotCurg; k++) {
						if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
							nPosCur = k;
							break;
						}
					}
					strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
					strcat_s(sCad, " ");
					strcat_s(sCad, sArrAMDoceg[nPosDoc]);
					strcat_s(sCad, ", ");
					strcat_s(sCad, sArrNomDocg[nPosDoc]);
					nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
					nCicCur--;
					if(nCicCur<0 || nCicCur>9)
						nCicCur = 0;
					if(nCicCur>3)
						continue;
					if(nArrNHCDocg[i]!=3 || sArrCTACDog[i][0]!='A') {
						continue;
					}
					CString abc1;
					j4=j5=j6=0;
					Cadena = "";
					strcpy_s(sCadPob,"00000000000000000000000000000000");
					nVal = (sArrCDCDocg[i][1]-'0')*10 + (sArrCDCDocg[i][2]-'0');
					for(j8=0; nVal; j8++) {
						if((5-j8)>=0)
							sCadPob[5-j8] = nVal%2+'0';
						nVal = nVal/2;
					}
					nDiaIni = nDiaFin = -1;
					for(j5=0; j5<6; j5++) {
						for(j4=0; j4<nNumTotAulg; j4++) {
							nDia=nHorIni=nHorFin=-1;
							for(j6=0; j6<18; j6++) {
								if( (!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
									!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
									!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3)) ||
									(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
									!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
									!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3)) ) {
									if(nDiaIni==-1)		nDiaIni = j5;
									if(nDiaIni == j5) {
										sCadPob[6+j5] = '1';
										nVal = j4+1;
										for(j8=0; nVal; j8++) {
											if((15-j8)>=0)
												sCadPob[15-j8] = nVal%2+'0';
											nVal = nVal/2;
										}
										nDia=nHorIni=nHorFin=-1;
										if(j6<6)
											sCadPob[16+j6] = '1';
										else
											if(j6<12) {
												if(nCicCur<7)	sCadPob[16+j6-6] = '1';
												if(nCicCur>6)	sCadPob[16] = '1';
											}
											else
												sCadPob[16+j6-11] = '1';
										if(nDia == -1) {
											nDia = j5;
											nHorIni = nHorFin = j6;
										}
										else
											nHorFin = j6;
									}
									else {
										sCadPob[6+j5] = '1';
										nVal = j4+1;
										for(int j8=0; nVal; j8++) {
											if((25-j8)>=0)
												sCadPob[25-j8] = nVal%2+'0';
											nVal = nVal/2;
										}
										nDia=nHorIni=nHorFin=-1;
										if(j6<6)
											sCadPob[26+j6] = '1';
										else
											if(j6<12) {
												if(nCicCur<7)	sCadPob[26+j6-6] = '1';
												if(nCicCur>6)	sCadPob[26] = '1';
											}
											else
												sCadPob[26+j6-11] = '1';
										if(nDia == -1) {
											nDia = j5;
											nHorIni = nHorFin = j6;
										}
										else
											nHorFin = j6;
									}
								}
							}
						}
					}
					nValPen = nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i];
					nFunApt = 1.00/(nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i]+1);
					nPSCInd = nFunApt/nDGSPobg[3];
					nProAcu = nProAcu + nPSCInd;
					strcpy_s(sCadPob,sArrVarSPog[3][nNumInd]);
					if(nNumInd==nUMProb[0])
						strcpy_s(sCad1, "Men");
					else
						sCad1[0] = 0;
					if(nNumInd==nUSele1 || nNumInd==nUSele2)
						strcpy_s(sCad2, "Sel");
					else
						sCad2[0] = 0;
//					for(k=0; k<50; k++)
//						if(sArrVarSPog[0][k][0]==0)
					if(sArrCGCDocg[i][0]=='0')
						Cadena.Format("%s %s T %-6.6s %-6.6s %-10.10s %s Tuvo Pen.%3d y aptitud %5.3lf %s %s",
						sArrCCCDocg[i], sArrCGCDocg[i],sCadPob,sCadPob+6,sCadPob+12,sCadPob+22,
						nValPen+1, nFunApt, sCad1, sCad2);
					else
						Cadena.Format("%s %s L %-6.6s %-6.6s %-10.10s %s Tuvo Pen.%3d y aptirud %5.3lf %s %s",
						sArrCCCDocg[i], sArrCGCDocg[i],sCadPob,sCadPob+6,sCadPob+12,sCadPob+22,
						nValPen+1, nFunApt, sCad1, sCad2);
					m_CtrlLisSP2.AddString(Cadena);
					nNumInd++;
				}
			}
			if(i2==8) {
				nNumInd = 0;
				nProAcu = 0;
				// Muestra el cromosoma y la penalidad de la subpoblación 3
				m_CtrlLisSP4.ResetContent();
				for(i=0; i<nNumTotCDog; i++) {
					for(k=0; k<nNumTotDocg; k++)
						if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
							nPosDoc = k;
							break;
						}
					for(k=0; k<nNumTotCurg; k++) {
						if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
							nPosCur = k;
							break;
						}
					}
					strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
					strcat_s(sCad, " ");
					strcat_s(sCad, sArrAMDoceg[nPosDoc]);
					strcat_s(sCad, ", ");
					strcat_s(sCad, sArrNomDocg[nPosDoc]);
					nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
					nCicCur--;
					if(nCicCur<0 || nCicCur>9)
						nCicCur = 0;
					if(nCicCur<4 || nCicCur>6)
						continue;
						if(nArrNHCDocg[i]!=3 || sArrCTACDog[i][0]!='A') {
//						if(nArrNHCDocg[i]!=4 || sArrCTACDog[i][0]!='A') {
						continue;
					}
					CString abc1;
					j4=j5=j6=0;
					Cadena = "";
					strcpy_s(sCadPob,"00000000000000000000000000000000");
					nVal = (sArrCDCDocg[i][1]-'0')*10 + (sArrCDCDocg[i][2]-'0');
					for(j8=0; nVal; j8++) {
						if((5-j8)>=0)
							sCadPob[5-j8] = nVal%2+'0';
						nVal = nVal/2;
					}
					nDiaIni = nDiaFin = -1;
					for(j5=0; j5<6; j5++) {
						for(j4=0; j4<nNumTotAulg; j4++) {
							nDia=nHorIni=nHorFin=-1;
							for(j6=0; j6<18; j6++) {
								if( (!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
									!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
									!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3)) ||
									(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[i],3) &&
									!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
									!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[i],3)) ) {
									if(nDiaIni==-1)		nDiaIni = j5;
									if(nDiaIni == j5) {
										sCadPob[6+j5] = '1';
										nVal = j4+1;
										for(j8=0; nVal; j8++) {
											if((15-j8)>=0)
												sCadPob[15-j8] = nVal%2+'0';
											nVal = nVal/2;
										}
										nDia=nHorIni=nHorFin=-1;
										if(j6<6)
											sCadPob[16+j6] = '1';
										else
											if(j6<12) {
												if(nCicCur<7)	sCadPob[16+j6-6] = '1';
												if(nCicCur>6)	sCadPob[16] = '1';
											}
											else
												sCadPob[16+j6-11] = '1';
										if(nDia == -1) {
											nDia = j5;
											nHorIni = nHorFin = j6;
										}
										else
											nHorFin = j6;
									}
									else {
										sCadPob[6+j5] = '1';
										nVal = j4+1;
										for(int j8=0; nVal; j8++) {
											if((25-j8)>=0)
												sCadPob[25-j8] = nVal%2+'0';
											nVal = nVal/2;
										}
										nDia=nHorIni=nHorFin=-1;
										if(j6<6)
											sCadPob[26+j6] = '1';
										else
											if(j6<12) {
												if(nCicCur<7)	sCadPob[26+j6-6] = '1';
												if(nCicCur>6)	sCadPob[26] = '1';
											}
											else
												sCadPob[26+j6-11] = '1';
										if(nDia == -1) {
											nDia = j5;
											nHorIni = nHorFin = j6;
										}
										else
											nHorFin = j6;
									}
								}
							}
						}
					}
					nValPen = nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i];
					nFunApt = 1.00/(nArrPCCDocg[i]+nArrPACDocg[i]+nArrPDCDocg[i]+1);
					nPSCInd = nFunApt/nDGSPobg[8];
					nProAcu = nProAcu + nPSCInd;
					strcpy_s(sCadPob,sArrVarSPog[8][nNumInd]);
					if(nNumInd==nUMProb[0])
						strcpy_s(sCad1, "Men");
					else
						sCad1[0] = 0;
					if(nNumInd==nUSele1 || nNumInd==nUSele2)
						strcpy_s(sCad2, "Sel");
					else
						sCad2[0] = 0;
//					for(k=0; k<50; k++)
//						if(sArrVarSPog[6][k][0]==0)
					if(sArrCGCDocg[i][0]=='0')
						Cadena.Format("%s %s T %-6.6s %-6.6s %-10.10s %s Tuvo Pen.%3d y aptitud %5.3lf %s %s",
						sArrCCCDocg[i], sArrCGCDocg[i],sCadPob,sCadPob+6,sCadPob+12,sCadPob+22,
						nValPen+1, nFunApt, sCad1, sCad2);
					else
						Cadena.Format("%s %s L %-6.6s %-6.6s %-10.10s %s Tuvo Pen.%3d y aptirud %5.3lf %s %s",
						sArrCCCDocg[i], sArrCGCDocg[i],sCadPob,sCadPob+6,sCadPob+12,sCadPob+22,
						nValPen+1, nFunApt, sCad1, sCad2);
					m_CtrlLisSP4.AddString(Cadena);
					nNumInd++;
				}
			}
		}
	}
	m_sTotPen = "";
	m_CtrlAltAsi.EnableWindow(false);
	m_CtrlGNPobl.EnableWindow(false);
	UpdateData(false);
	// Va a pasar de la matriz 1 a la matriz 2
	// Deben ser cursos completos
	k = 0;
	for (i=0; i<100; i++)
		sArrCodCur[i][0]= nArrNHACur[i]= nArrNHDCur[i]= 0;
	for(j4=0; j4<41; j4++) {
		for(j5=0; j5<6; j5++) {
			for(j6=0; j6<18; j6++) {
				if(sArrHDAAu2g[j4][j5][j6][0]!='D' && sArrHDAAu2g[j4][j5][j6][0]!=0) {
					// Guarda el codigo de curso a considerar
					if(sArrCodCur[k][0]==0) {
						strncpy(sArrCodCur[k], sArrHDAAu2g[j4][j5][j6], 3);
						nArrNHACur[k] = 1;
					}
					else {
						if(strncmp(sArrCodCur[k], sArrHDAAu2g[j4][j5][j6],3)) {
							k++;
							strncpy(sArrCodCur[k], sArrHDAAu2g[j4][j5][j6], 3);
							nArrNHACur[k] = 1;
						}
						else {
							nArrNHACur[k] = nArrNHACur[k] + 1;
						}
					}
					// Halla el ciclo del curso
					for(int k1=0; k1<nNumTotCurg; k1++) {
						if(!strncmp(sArrCodCur[k], sArrCodCurg[k1], 3)) {
							nPosCur = k1;
							break;
						}
					}
					nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 + sArrCicCurg[nPosCur][1]-'0';
					nCicCur--;
					if(nCicCur<0 || nCicCur>9) {
						AfxMessageBox("Error en asignacion de ciclo al curso");
						nCicCur = 0;
					}
//					if(sArrHDAAulg[j4][j5][j6][0]=='D' && ) {

					if(sArrHDAAulg[j4][j5][j6][0]=='D' && 
						(!strncmp(sArrHDACicg[nCicCur][j5][j6],sArrCodCur[k],3) ||
						sArrHDACicg[nCicCur][j5][j6][0]=='D') ) {
						nArrNHDCur[k] = nArrNHDCur[k] + 1;
					}
				}
			}
		}
	}
	for(j4=0; j4<41; j4++) {
		for(j5=0; j5<6; j5++) {
			for(j6=0; j6<18; j6++) {
				if(sArrHDAAu2g[j4][j5][j6][0]!='D' && sArrHDAAu2g[j4][j5][j6][0]!=0) {
					for (k=0; sArrCodCur[k][0] && k<100; k++)  {
						if(!strncmp(sArrCodCur[k], sArrHDAAu2g[j4][j5][j6],3))
							break;
					}
					// Halla el ciclo del curso
					for(k1=0; k1<nNumTotCurg; k1++) {
						if(!strncmp(sArrCodCur[k], sArrCodCurg[k1], 3)) {
							nPosCur = k1;
							break;
						}
					}
					nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 + sArrCicCurg[nPosCur][1]-'0';
					nCicCur--;
					if(nCicCur<0 || nCicCur>9) {
						AfxMessageBox("Error en asignacion de ciclo al curso");
						nCicCur = 0;
					}

					CString fff;
					fff.Format("%s k %d nArrNHACur[k] %d nArrNHDCur[k] %d",
						sArrHDAAu2g[j4][j5][j6], k, nArrNHACur[k],nArrNHDCur[k] );
//					AfxMessageBox(fff);

					if(nArrNHACur[k] == nArrNHDCur[k]) {
						strncpy(sArrHDAAulg[j4][j5][j6], sArrHDAAu2g[j4][j5][j6], 9);
						sArrHDAAu2g[j4][j5][j6][0]='D';
						sArrHDAAu2g[j4][j5][j6][1]=0;
						strncpy(sArrHDACicg[nCicCur][j5][j6], sArrCodCur[k], 3);
					}
				}
			}
		}
	}
/*	for(j4=0; j4<41; j4++) {
		for(j5=0; j5<6; j5++) {
			for(j6=0; j6<18; j6++) {
				if(sArrHDAAulg[j4][j5][j6][0]=='D' &&
					sArrHDAAu2g[j4][j5][j6][0]!='D') {
					strncpy(sArrHDAAulg[j4][j5][j6], sArrHDAAu2g[j4][j5][j6], 9);
					sArrHDAAu2g[j4][j5][j6][0]='D';
					sArrHDAAu2g[j4][j5][j6][1]=0;
				}
			}
		}
	}
*/
	QueryPerformanceCounter(&ntime2);
	ntime = (long)((ntime2.QuadPart - ntime1.QuadPart)/(freq.QuadPart/1000));
	xxyy.Format("Tiempo: %ld ms", ntime);
	nArrTGPoblg[nNumPobg] = ntime;
	nNumPobg++;		// Numero de población
//	AfxMessageBox(xxyy);
}

double CDlgProAdi::drand48()
{
	double valor = 0.0;
	double d = RAND_MAX * 1.0;
	double i;
	for(i = MAX; i > rand(); i /= (RAND_MAX + 1)) {
		valor += rand()/d;
		d *= RAND_MAX + 1 ;
	}
	return valor;
}

void CDlgProAdi::IniCadTip()
{
	// Arreglo Tipos de Cadena Dos Dias
	strcpy_s(sArrTCDDig[0],"000101");
	strcpy_s(sArrTCDDig[1],"001001");
	strcpy_s(sArrTCDDig[2],"001010");
	strcpy_s(sArrTCDDig[3],"010001");
	strcpy_s(sArrTCDDig[4],"010010");
	strcpy_s(sArrTCDDig[5],"010100");
	strcpy_s(sArrTCDDig[6],"100010");
	strcpy_s(sArrTCDDig[7],"100100");
	strcpy_s(sArrTCDDig[8],"101000");
	strcpy_s(sArrTCDDig[9],"000011");
	// Arreglo Tipos de Cadena Un Dia
	strcpy_s(sArrTCUDig[0],"000001");
	strcpy_s(sArrTCUDig[1],"000010");
	strcpy_s(sArrTCUDig[2],"000100");
	strcpy_s(sArrTCUDig[3],"001000");
	strcpy_s(sArrTCUDig[4],"010000");
	strcpy_s(sArrTCUDig[5],"100000");

	// Arreglo Tipos de Cadena Aula uno
	strcpy_s(sArrTCAUng[0],"0001");
	strcpy_s(sArrTCAUng[1],"0010");
	strcpy_s(sArrTCAUng[2],"0011");
	strcpy_s(sArrTCAUng[3],"0100");
	strcpy_s(sArrTCAUng[4],"0101");

	// Arreglo Tipos de Cadena Tres Horas
	strcpy_s(sArrTCTHog[0],"111000");
	strcpy_s(sArrTCTHog[1],"011100");
	strcpy_s(sArrTCTHog[2],"001110");
	strcpy_s(sArrTCTHog[3],"000111");
	// Arreglo Tipos de Cadena Dos Horas
	strcpy_s(sArrTCDHog[0],"110000");
	strcpy_s(sArrTCDHog[1],"011000");
	strcpy_s(sArrTCDHog[2],"001100");
	strcpy_s(sArrTCDHog[3],"000110");
	strcpy_s(sArrTCDHog[4],"000011");

}

void CDlgProAdi::OnAltasi() 
{
	// TODO: Add your control notification handler code here
	CString Cadena, Cadena1;
	int i, k, k1;
	int nPosCur;		// Posicion del curso en la tabla de cursos
	int nCicCur;
	int nPosAul;
	int nPosDoc;		// Posición del docente en la tabla de docentes
	int j4, j5, j6, j8;
	char sCad[121];
	char sArrCic[11];	// Arreglo interno de ciclos
	int nArrCicDiaHor[11][6][18];	// Arreglo ciclo dia y hora
	char sCadPob[51];
	int nVal;
	int nDia;
	int nHorIni;
	int nHorFin;
	int nDiaIni;
	int nDiaFin;

	char sArrDesCic[11][11];
	char sArrPosAul[21];		// Aulas ocupadas por el curso
	int nCon;
	int nIRCamb;		// Indicador de realiza cambio
	int nHorCam;		// Horas cambiadas del curso
	int nHDCurs;		// Horas en el dia del cursp
	int nDiaCam;		// Dia al cual se va a cambiar elk curso

	strcpy_s(sArrDesCic[0],"I");
	strcpy_s(sArrDesCic[1],"II");
	strcpy_s(sArrDesCic[2],"III");
	strcpy_s(sArrDesCic[3],"IV");
	strcpy_s(sArrDesCic[4],"V");
	strcpy_s(sArrDesCic[5],"VI");
	strcpy_s(sArrDesCic[6],"VII");
	strcpy_s(sArrDesCic[7],"VIII");
	strcpy_s(sArrDesCic[8],"IX");
	strcpy_s(sArrDesCic[9],"X");

	// Curso C50 asignado aula A5 el sabado hora 03 y 04
	strncpy(sArrHDAAulg[4][5][13], "C50", 3);
	strncpy(sArrHDAAulg[4][5][13]+3, "D18",3);
	strncpy(sArrHDAAulg[4][5][13]+6, "01S",3);
	strncpy(sArrHDAAulg[4][5][14], "C50", 3);
	strncpy(sArrHDAAulg[4][5][14]+3, "D18",3);
	strncpy(sArrHDAAulg[4][5][14]+6, "01S",3);
	strncpy(sArrHDACicg[8][5][13], "C50", 3);
	strncpy(sArrHDACicg[8][5][14], "C50", 3);
	sArrHDADocg[18][5][13]='A';
	sArrHDADocg[18][5][14]='A';

	// Va a escoger 10 cursos y cambiara los datos
	for(i=0; i<nNumTotCDog; i++) {
		if( (i%3)==2 ) {	// Primero se probo con 1
			for(k1=0; k1<10; k1++)	sArrCic[k1]=0;
			for(k1=0; k1<21; k1++)	sArrPosAul[k1]=0;
			for(k1=0; k1<nNumTotDocg; k1++) {
				if(!strncmp(sArrCodDocg[k1], sArrCDCDocg[i], 3)) {
					nPosDoc = k1;
					break;
				}
			}
			for(k1=0; k1<nNumTotCurg; k1++) {
				if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k1], 3)) {
					nPosCur = k1;
					break;
				}
			}
			nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 + sArrCicCurg[nPosCur][1]-'0';
			nCicCur--;
			if(nCicCur<0 || nCicCur>9) {
				AfxMessageBox("Error en asignacion de ciclo al curso");
				nCicCur = 0;
			}
			nPosAul = -1;
			nIRCamb = 0;
			nHorCam = 0;
			nDiaCam = 0;
			nHDCurs = 0;
			// Solo considera el tipo de aula teoria
			for(int j4=0; j4<5; j4++) {
				for(int j5=0; j5<6; j5++) {
					for(k1=0; k1<18; k1++) {
						if(!strncmp(sArrHDAAulg[j4][j5][k1],sArrCCCDocg[i],3) &&
							!strncmp(sArrHDAAulg[j4][j5][k1]+3,sArrCDCDocg[i],3) &&
							!strncmp(sArrHDAAulg[j4][j5][k1]+6,sArrCGCDocg[i],3) ) {
							nHDCurs++;
						}
					}
					for(int j6=0; j6<18; j6++) {
						if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
							!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
							!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
							sArrHDAAulg[j4][j5][j6][0]='D';
							sArrHDAAulg[j4][j5][j6][1]=0;
							sArrHDACicg[nCicCur][j5][j6][0]='D';
							sArrHDADocg[nPosDoc][j5][j6]='D';
							// Busca dia ocupado en matriz 1 y libre en matriz 2 en la misma hora
							if(nHorCam==0) {
								for (k1=0; k1<6; k1++) {
									if(k1 != j5) {
										if(nHDCurs== 2 && 
											strncmp(sArrHDAAulg[j4][k1][j6],sArrCCCDocg[i],3) &&
											strncmp(sArrHDAAulg[j4][k1][j6+1],sArrCCCDocg[i],3) &&
											sArrHDAAu2g[j4][k1][j6][0]=='D' &&
											sArrHDAAu2g[j4][k1][j6+1][0]=='D') {
											nDiaCam = k1;
											strncpy(sArrHDAAu2g[j4][nDiaCam][j6], sArrCCCDocg[i], 3);
											strncpy(sArrHDAAu2g[j4][nDiaCam][j6]+3, sArrCDCDocg[i],3);
											strncpy(sArrHDAAu2g[j4][nDiaCam][j6]+6, sArrCGCDocg[i],3);
											sArrHDADocg[nPosDoc][nDiaCam][j6]='A';
											if(sArrHDACicg[nCicCur][nDiaCam][j6][0]=='D')
												strncpy(sArrHDACicg[nCicCur][nDiaCam][j6], sArrCCCDocg[i], 3);
											break;
										}
										if(nHDCurs== 3 && 
											strncmp(sArrHDAAulg[j4][k1][j6],sArrCCCDocg[i],3) &&
											strncmp(sArrHDAAulg[j4][k1][j6+1],sArrCCCDocg[i],3) &&
											strncmp(sArrHDAAulg[j4][k1][j6+2],sArrCCCDocg[i],3) &&
											sArrHDAAu2g[j4][k1][j6][0]=='D' &&
											sArrHDAAu2g[j4][k1][j6+1][0]=='D' &&
											sArrHDAAu2g[j4][k1][j6+2][0]=='D') {
											nDiaCam = k1;
											strncpy(sArrHDAAu2g[j4][nDiaCam][j6], sArrCCCDocg[i], 3);
											strncpy(sArrHDAAu2g[j4][nDiaCam][j6]+3, sArrCDCDocg[i],3);
											strncpy(sArrHDAAu2g[j4][nDiaCam][j6]+6, sArrCGCDocg[i],3);
											sArrHDADocg[nPosDoc][nDiaCam][j6]='A';
											if(sArrHDACicg[nCicCur][nDiaCam][j6][0]=='D')
												strncpy(sArrHDACicg[nCicCur][nDiaCam][j6], sArrCCCDocg[i], 3);
											break;
										}
									}
								}
							}
							else  {
								strncpy(sArrHDAAu2g[j4][nDiaCam][j6], sArrCCCDocg[i], 3);
								strncpy(sArrHDAAu2g[j4][nDiaCam][j6]+3, sArrCDCDocg[i],3);
								strncpy(sArrHDAAu2g[j4][nDiaCam][j6]+6, sArrCGCDocg[i],3);
								sArrHDADocg[nPosDoc][nDiaCam][j6]='A';
								if(sArrHDACicg[nCicCur][nDiaCam][j6][0]=='D')
									strncpy(sArrHDACicg[nCicCur][nDiaCam][j6], sArrCCCDocg[i], 3);
							}
							nHorCam++;
							nIRCamb = 1;
						}
					}
					if(nIRCamb==1)		break;
				}
				if(nIRCamb==1)		break;
			}
		}
	}

	m_CtrlLisDoc.ResetContent();

	for(i=0; i<nNumTotCDog; i++) {
		for(k1=0; k1<10; k1++)	sArrCic[k1]=0;
		for(k1=0; k1<21; k1++)	sArrPosAul[k1]=0;
		for(k1=0; k1<nNumTotDocg; k1++) {
			if(!strncmp(sArrCodDocg[k1], sArrCDCDocg[i], 3)) {
				nPosDoc = k1;
				break;
			}
		}
		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);
		for(k1=0; k1<nNumTotCurg; k1++) {
			if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k1], 3)) {
				nPosCur = k1;
				break;
			}
		}
		nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 + sArrCicCurg[nPosCur][1]-'0';
		if(nCicCur<0 || nCicCur>9)		nCicCur = 0;
		sArrCic[nCicCur]=1;		// Establece indicador en ciclo al cual pertenece el curso

		nPosAul = -1;
		for(int j4=0; j4<nNumTotAulg; j4++) {
			for(int j5=0; j5<6; j5++) {
				for(int j6=0; j6<18; j6++) {
					if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
						sArrPosAul[j4] = 1;
					}
				}
			}
		}
		nCon = 0;
		Cadena.Format("%s %s %-25.25s  ",sArrCCCDocg[i],sArrCDCDocg[i],sCad );
		for(k1=0; k1<10; k1++) {
			if(sArrCic[k1]==1) {
				Cadena1.Format("%-4.4s ",sArrDesCic[k1]);
				Cadena = Cadena + Cadena1;
				nCon++;
			}
		}
		Cadena = Cadena + "  ";

		for(k1=0; k1<20; k1++) {
			if(sArrPosAul[k1]==1) {
				Cadena1.Format("%-4.4s ",sArrCodAulg[k1]);
				Cadena = Cadena + Cadena1;
			}
		}
		m_CtrlLisDoc.AddString(Cadena);
	}

	m_CtrlLisPAc.ResetContent();
	for(i=0; i<nNumTotCDog; i++) {
		for(k=0; k<nNumTotDocg; k++)
			if(!strncmp(sArrCDCDocg[i], sArrCodDocg[k], 3)) {
				nPosDoc = k;
				break;
			}
			for(k=0; k<nNumTotCurg; k++) {
				if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k], 3)) {
					nPosCur = k;
					break;
				}
			}

		strcpy_s(sCad, sArrAPDoceg[nPosDoc]);
		strcat_s(sCad, " ");
		strcat_s(sCad, sArrAMDoceg[nPosDoc]);
		strcat_s(sCad, ", ");
		strcat_s(sCad, sArrNomDocg[nPosDoc]);

		nCicCur =  (sArrCicCurg[k][0]-'0')*10 + sArrCicCurg[k][1]-'0';
		nCicCur--;

		if(nCicCur<0 || nCicCur>9)
			nCicCur = 0;

		CString abc1;
		j4=j5=j6=0;
		Cadena = "";
		strcpy_s(sCadPob,"00000000000000000000000000000000");
		nVal = (sArrCDCDocg[i][1]-'0')*10 + (sArrCDCDocg[i][2]-'0');
		for(j8=0; nVal; j8++) {
			if((5-j8)>=0)
				sCadPob[5-j8] = nVal%2+'0';
			nVal = nVal/2;
		}
		nDiaIni = nDiaFin = -1;
		for(j4=0; j4<nNumTotAulg; j4++) {
			for(j5=0; j5<6; j5++) {
				nDia=nHorIni=nHorFin=-1;
				for(j6=0; j6<18; j6++) {
					if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
						if(nDiaIni==-1)		nDiaIni = j5;
						if(nDiaIni == j5) {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(j8=0; nVal; j8++) {
								if((15-j8)>=0)
									sCadPob[15-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[16+j6] = '1';
							else
								if(j6<12)
									sCadPob[16+j6-6] = '1';
								else
									sCadPob[16+j6-12] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
						else {
							sCadPob[6+j5] = '1';
							nVal = j4+1;
							for(int j8=0; nVal; j8++) {
								if((25-j8)>=0)
									sCadPob[25-j8] = nVal%2+'0';
								nVal = nVal/2;
							}
							nDia=nHorIni=nHorFin=-1;
							if(j6<6)
								sCadPob[26+j6] = '1';
							else
								if(j6<12)
								sCadPob[26+j6-6] = '1';
									else
										sCadPob[26+j6-12] = '1';
							if(nDia == -1) {
								nDia = j5;
								nHorIni = nHorFin = j6;
							}
							else
								nHorFin = j6;
						}
					}
				}
			}
		}
		if(sArrCGCDocg[i][0]=='0')
			Cadena.Format("%s %s T %-6.6s %-6.6s %-10.10s %s",
			sArrCCCDocg[i], sArrCGCDocg[i], sCadPob,sCadPob+6,sCadPob+12,sCadPob+22);
		else
			Cadena.Format("%s %s L %-6.6s %-6.6s %-10.10s %s",
			sArrCCCDocg[i], sArrCGCDocg[i], sCadPob,sCadPob+6,sCadPob+12,sCadPob+22);
			m_CtrlLisPAc.AddString(Cadena);
	}

	m_CtrlLisPenCic.ResetContent();
	for(int k1=0; k1<11; k1++)
		for(int k2=0; k2<6; k2++)
			for(int k3=0; k3<18; k3++)
				nArrCicDiaHor[k1][k2][k3]=0;

	for(j5=0; j5<6; j5++) {
		for(int j6=0; j6<18; j6++) {
			for(int j4=0; j4<nNumTotAulg; j4++) {
				for(k1=0; k1<nNumTotCDog; k1++) {
					if(!strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[k1],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[k1],3) &&
						!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[k1],3) ) {
						for(int k2=0; k2<nNumTotCurg; k2++) {
							if(!strncmp(sArrCCCDocg[k1], sArrCodCurg[k2], 3)) {
								nPosCur = k2;
								break;
							}
						}
						nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 +
							sArrCicCurg[nPosCur][1]-'0';
						nCicCur--;
						if(nCicCur<0 || nCicCur>9)		nCicCur = 0;
						nArrCicDiaHor[nCicCur][j5][j6]=nArrCicDiaHor[nCicCur][j5][j6]+1;
//						if(sArrCicDiaHor[nCicCur][j5][j6]==2)
//							AfxMessageBox(sArrCodCurg[nPosCur]);

					}
					if(!strncmp(sArrHDAAu2g[j4][j5][j6],sArrCCCDocg[k1],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+3,sArrCDCDocg[k1],3) &&
						!strncmp(sArrHDAAu2g[j4][j5][j6]+6,sArrCGCDocg[k1],3) ) {
//						AfxMessageBox("Paso 1");
						for(int k2=0; k2<nNumTotCurg; k2++) {
							if(!strncmp(sArrCCCDocg[k1], sArrCodCurg[k2], 3)) {
								nPosCur = k2;
								break;
							}
						}
						nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 +
							sArrCicCurg[nPosCur][1]-'0';
						nCicCur--;
						if(nCicCur<0 || nCicCur>9)
							nCicCur = 0;
						nArrCicDiaHor[nCicCur][j5][j6]=nArrCicDiaHor[nCicCur][j5][j6]+1;
//						if(sArrCicDiaHor[nCicCur][j5][j6]==2)
//							AfxMessageBox(sArrCodCurg[nPosCur]);

					}
				}
			}
		}
	}

	m_CtrlAltAsi.EnableWindow(false);
	m_CtrlGVPobl.EnableWindow(true);
	nICIPobg = 1;
	UpdateData(false);
	
}

void CDlgProAdi::IniCadTi1()
{
	// Arreglo Tipos de Cadena Dos Dias
	strcpy_s(sArrTCDDig[0],"101000");
	strcpy_s(sArrTCDDig[1],"100100");
	strcpy_s(sArrTCDDig[2],"100010");
	strcpy_s(sArrTCDDig[3],"010100");
	strcpy_s(sArrTCDDig[4],"010010");
	strcpy_s(sArrTCDDig[5],"010001");
	strcpy_s(sArrTCDDig[6],"001010");
	strcpy_s(sArrTCDDig[7],"001001");
	strcpy_s(sArrTCDDig[8],"000101");
	strcpy_s(sArrTCDDig[9],"000011");
	// Arreglo Tipos de Cadena Un Dia
	strcpy_s(sArrTCUDig[0],"100000");
	strcpy_s(sArrTCUDig[1],"010000");
	strcpy_s(sArrTCUDig[2],"001000");
	strcpy_s(sArrTCUDig[3],"000100");
	strcpy_s(sArrTCUDig[4],"000010");
	strcpy_s(sArrTCUDig[5],"000001");
	// Arreglo Tipos de Cadena Aula uno
	strcpy_s(sArrTCAUng[0],"0001");
	strcpy_s(sArrTCAUng[1],"0010");
	strcpy_s(sArrTCAUng[2],"0011");
	strcpy_s(sArrTCAUng[3],"0100");
	strcpy_s(sArrTCAUng[4],"0101");

	// Arreglo Tipos de Cadena Tres Horas
	strcpy_s(sArrTCTHog[0],"111000");
	strcpy_s(sArrTCTHog[1],"011100");
	strcpy_s(sArrTCTHog[2],"001110");
	strcpy_s(sArrTCTHog[3],"000111");
	// Arreglo Tipos de Cadena Dos Horas
	strcpy_s(sArrTCDHog[0],"110000");
	strcpy_s(sArrTCDHog[1],"011000");
	strcpy_s(sArrTCDHog[2],"001100");
	strcpy_s(sArrTCDHog[3],"000110");
	strcpy_s(sArrTCDHog[4],"000011");

}

void CDlgProAdi::GenArcSol()
{
	CFile bd1;		// representa al fichero
	CString szNombreFi;
	CString Cadena, Cadena1;
	char sCad1[221], sCad2[221];
	int i, j;
	int j4, j5, j6, j7, j8;
	int k1;
	int nPosCur;		// Posicion del curso en la tabla de cursos
	int nPosDoc;		// Posición del docente en la tabla de docentes
	int nCicCur;
	int nArrHorDia[7];	// Arreglo de horas en el dia
	char sDesHorIni[20][6];
	char sDesHorFin[20][6];
	char sArrDesCic[11][11];

	strcpy_s(sArrDesCic[0],"I");
	strcpy_s(sArrDesCic[1],"II");
	strcpy_s(sArrDesCic[2],"III");
	strcpy_s(sArrDesCic[3],"IV");
	strcpy_s(sArrDesCic[4],"V");
	strcpy_s(sArrDesCic[5],"VI");
	strcpy_s(sArrDesCic[6],"VII");
	strcpy_s(sArrDesCic[7],"VIII");
	strcpy_s(sArrDesCic[8],"IX");
	strcpy_s(sArrDesCic[9],"X");

	strcpy_s(sDesHorIni[0], "08:00");
	strcpy_s(sDesHorIni[1], "08:50");
	strcpy_s(sDesHorIni[2], "09:40");
	strcpy_s(sDesHorIni[3], "10:30");
	strcpy_s(sDesHorIni[4], "11:20");
	strcpy_s(sDesHorIni[5], "12:10");
	strcpy_s(sDesHorIni[6], "13:00");
	strcpy_s(sDesHorIni[7], "13:50");
	strcpy_s(sDesHorIni[8], "14:40");
	strcpy_s(sDesHorIni[9], "15:30");
	strcpy_s(sDesHorIni[10], "16:20");
	strcpy_s(sDesHorIni[11], "17:10");
	strcpy_s(sDesHorIni[12], "18:00");
	strcpy_s(sDesHorIni[13], "18:50");
	strcpy_s(sDesHorIni[14], "19:40");
	strcpy_s(sDesHorIni[15], "20:30");
	strcpy_s(sDesHorIni[16], "21:20");

	strcpy_s(sDesHorFin[0], "08:50");
	strcpy_s(sDesHorFin[1], "09:40");
	strcpy_s(sDesHorFin[2], "10:30");
	strcpy_s(sDesHorFin[3], "11:20");
	strcpy_s(sDesHorFin[4], "12:10");
	strcpy_s(sDesHorFin[5], "13:00");
	strcpy_s(sDesHorFin[6], "13:50");
	strcpy_s(sDesHorFin[7], "14:40");
	strcpy_s(sDesHorFin[8], "15:30");
	strcpy_s(sDesHorFin[9], "16:20");
	strcpy_s(sDesHorFin[10], "17:10");
	strcpy_s(sDesHorFin[11], "18:00");
	strcpy_s(sDesHorFin[12], "18:50");
	strcpy_s(sDesHorFin[13], "19:40");
	strcpy_s(sDesHorFin[14], "20:30");
	strcpy_s(sDesHorFin[15], "21:20");
	strcpy_s(sDesHorFin[16], "22:10");


	strcpy_s(sArrDiaSemg[0], "Lunes");
	strcpy_s(sArrDiaSemg[1], "Martes");
	strcpy_s(sArrDiaSemg[2], "Miercoles");
	strcpy_s(sArrDiaSemg[3], "Jueves");
	strcpy_s(sArrDiaSemg[4], "Viernes");
	strcpy_s(sArrDiaSemg[5], "Sabado");
	strcpy_s(sArrDiaSemg[6], "Domingo");


	szNombreFi = "LSolHor.txt";
	if (!bd1.Open(szNombreFi, CFile::modeCreate | CFile::modeWrite)) {
		AfxMessageBox("No se puede  abrir el fichero");
		return;
	}
	for(j=0; j<10; j++) {
		for(i=0; i<nNumTotCDog; i++) {
			for(k1=0; k1<nNumTotDocg; k1++) {
				if(!strncmp(sArrCodDocg[k1], sArrCDCDocg[i], 3)) {
					nPosDoc = k1;
					break;
				}
			}
			for(k1=0; k1<nNumTotCurg; k1++) {
				if(!strncmp(sArrCCCDocg[i], sArrCodCurg[k1], 3)) {
					nPosCur = k1;
					break;
				}
			}
			nCicCur =  (sArrCicCurg[nPosCur][0]-'0')*10 + sArrCicCurg[nPosCur][1]-'0';
			nCicCur--;
			if(nCicCur<0 || nCicCur>9)		nCicCur = 0;
			if(nCicCur!=j) continue;

			strcpy_s(sCad1, sArrAPDoceg[nPosDoc]);
			strcat_s(sCad1, " ");
			strcat_s(sCad1, sArrAMDoceg[nPosDoc]);
			strcat_s(sCad1, ", ");
			strcat_s(sCad1, sArrNomDocg[nPosDoc]);

			for(j7=0; j7<7; j7++)	nArrHorDia[j7]=0;
			j8=0;

			for(j4=0; j4<nNumTotAulg; j4++) {
				for(j5=0; j5<6; j5++) {
					for(j6=0; j6<18; j6++) {
						if( !strncmp(sArrHDAAulg[j4][j5][j6],sArrCCCDocg[i],3) &&
							!strncmp(sArrHDAAulg[j4][j5][j6]+3,sArrCDCDocg[i],3) &&
							!strncmp(sArrHDAAulg[j4][j5][j6]+6,sArrCGCDocg[i],3) ) {
							nArrHorDia[j8++] = j6;
						}
					}
					if(j8) {
						Cadena.Format("%-4.4s %s %-22.22s %s %-22.22s %-3.3s %-6.6s %s %s",
							sArrDesCic[j],
							sArrCodCurg[nPosCur], sArrNomCurg[nPosCur], sArrCodDocg[nPosDoc],
							sCad1, sArrCodAulg[j4], sArrDiaSemg[j5],
							sDesHorIni[nArrHorDia[0]],sDesHorFin[nArrHorDia[j8-1]]);
						strcpy_s(sCad2, Cadena);
						bd1.Write(sCad2, strlen(sCad2));
						sCad2[0]=13;
						sCad2[1]=10;
						sCad2[2]=0;
						bd1.Write(sCad2, strlen(sCad2));
						for(j7=0; j7<7; j7++)	nArrHorDia[j7]=0;
						j8=0;
					}
				}
			}

		}
	}
	bd1.Close();
}

void CDlgProAdi::OnBnClickedGvpobl()
{
	// TODO: Add your control notification handler code here
	int i;
	for(i=0; i<50 && nTPPoblg!=102; i++) {
		OnCalpen();
		OnGnpobl();
		OnCalpen();
	}
}
