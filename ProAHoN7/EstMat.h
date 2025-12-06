// Estructura correspondiente a los Datos de Matricula
#define WM_OPENDATABASE (WM_USER+100)
#define WM_SAVEDATABASE (WM_USER+101)

struct SEstMat
{
	unsigned char m_sznummat[7];		/* 007  007 */
	char m_szcodniv;					/* 001  008 */
	char m_szcodgra;					/* 001  009 */
	char m_szsecalu;					/* 001  010 */
	short int m_nztipalu;               /* 002  012 */ 
    char m_szapalum[21];			    /* 021  033 */
    char m_szamalum[21];			    /* 021  054 */
	char m_szasiexo[7];				    /* 007  061 */
	char m_szfaalum[9];					/* 009  070 */
	char m_szsaperi[10];				/* 010  080 */
	char m_szlibre2[2];					/* 002  082 */
    char m_szsexalu;					/* 001  083 */
	char m_szcodalu[7];			  		/* 007  090 */
	char m_szcodmod[15];				/* 015  105 */ 
	char m_szfnalum[11];				/* 011  116 */
	char m_szlnalum[31];				/* 031  147 */
	char m_szfecmat[9];					/* 009  156 */
	char m_szcsalum[3];					/* 003  159 */ /* Cod.Seccion de Alumno   */
	char m_szfiasec[3][9];				/* 027  186 */ /* Fec.Ingreso a Seccio    */
	char m_szccalum[2];					/* 002  188 */ /* Cod.Categoria de Alumno */
	char m_szficalu[2][9];				/* 018  206 */ /* Fec.Ingreso a Categoria */
	char m_szfralum[9];					/* 009  215 */ /* Fec.Retiro de Alumno    */
	char m_sznomalu[31];				/* 031  246 */
	char m_szccpag1;					/* 001  247 */ /* Cod.Con.Pag.1 de Alumno */
	short int m_nzimpcp1;               /* 002  249 */ /* Importe Con.Pag.1       */ 
	char m_szlibre3[3];					/* 002  281 */
	short int m_nzscfalu;               /* 002  254 */ /* Sum.Cal.Finales de Alumno */
	short int m_nzncfalu;               /* 002  256 */ /* Num.Cal.Finales de Alumno */
	short int m_nzuasecc;               /* 002  258 */ /* Ubicac.de alumno en seccion */
	short int m_nztppalu[10];			/* 020  278 */ /* Tot.Punt.Per.del Alumno */
	char m_szlibre4[3];					/* 003  281 */
	char m_szdiralu[48];			    /* 048  329 */
	char m_szdisalu[7];					/* 007  336 */
	char m_sztfalum[11];			    /* 011  347 */
	char m_sztmalum[11];			    /* 011  358 */
	char m_szfmalum[11];				/* 011  369 */
	char m_szcpalum[31];				/* 031  400 */
	char m_sztpalum;					/* 001  401 */
	char m_szcomalu[51];			    /* 051  452 */
	char m_szcomdos[31];			    /* 031  483 */
	char m_szcodcpr[8];					/* 008  491 */
	char m_szncproc[31];				/* 031  522 */
	char m_szcodcat;					/* 001  523 */
	char m_szFIDato[9];					/* 009  532 */
	char m_szestmat;					/* 001  533 */
	char m_sznapalu[10];		  		/* 010  600 */ /* No.Asig.en Periodo de Alumno */  
	char m_szpspalu[10];		  		/* 010  600 */ /* Pos.en la Secc.en Per.de Alumno */
	char m_szlibre5[3];					/* 002  281 */
	char m_szaematr[5];			  		/* 005  600 */ /* Año Escolar de Matricula */
	char m_nzicdocu;					/* 001  600 */ /* Ind.Control documentos   */
	char m_nzied001;					/* 001  600 */ /* Ind.Entrega documento 1  */
	char m_nzied002;					/* 001  600 */ /* Ind.Entrega documento 2  */
	char m_nzied003;					/* 001  600 */ /* Ind.Entrega documento 3  */
	char m_nzied004;					/* 001  600 */ /* Ind.Entrega documento 4  */
	char m_nzied005;					/* 001  600 */ /* Ind.Entrega documento 5  */
	char m_nzied006;					/* 001  600 */ /* Ind.Entrega documento 5  */
	char m_szlibre1[38];		  		/* 050  600 Real = xxx */
};


