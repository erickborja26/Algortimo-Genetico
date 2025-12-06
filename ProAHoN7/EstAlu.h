// Estructura correspondiente a los Datos de Alumnos
#define WM_OPENDATABASE (WM_USER+100)
#define WM_SAVEDATABASE (WM_USER+101)

struct SEstAlu
{
	unsigned char m_szcodalu[7];		/* 007  007 */
	char m_szcodmod[15];				/* 015  022 */
    char m_szapalum[21];			    /* 021  043 */
    char m_szamalum[21];			    /* 021  064 */
	char m_sznomalu[31];			    /* 031  095 */
	char m_szfnalum[11];				/* 011  106 */
	char m_szsexalu;					/* 001  107 */
	char m_sztipsan[3];					/* 003  110 */
	char m_szsegesc;					/* 001  111 */ // seguro escolar
	char m_szdiralu[48];			    /* 051  162 */
	char m_szdisalu[7];					/* 004  166 */
	char m_sztfalum[11];			    /* 011  177 */
	char m_sztmalum[11];			    /* 011  188 */
	char m_szcomalu[51];			    /* 051  239 */
	char m_szestalu;					/* 001  240 */
	char m_szFIDato[9];					/* 009  249 */
	char m_szlnalum[31];				/* 031  280 */
	char m_szcodcat;					/* 001  281 */
	char m_szcodniv;					/* 001  282 */
	char m_szcodgra;					/* 001  283 */
	char m_szcodsec;					/* 001  284 */
	char m_szarcima[16];				/* 016  300 */
	char m_szlenmat;			  		/* 001  301 */	// lengua materna
	char m_szaumatr[5];					/* 005  306 */	// año ultima matricula
	char m_szlibre1[94];		  		/* 094  400 Real = xxx */
};


