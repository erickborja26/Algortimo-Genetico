// Estructura correspondiente a los Parametros de Administracion

struct SEstPAd
{
	unsigned char m_szannpro[5];	/* 005  005 */
	char m_szfecini[9];				/* 009  014 */
	char m_szfecter[9];				/* 009  023 */
	short int m_nznumpe1;			/* 002  025 */
	char m_sznompe1[9][16]	;		/* 144  169 */
	char m_sznteva1[16];			/* 016  185 */
	char m_szfiper1[9][9];			/* 081  266 */
	char m_szlibre2[9];				/* 009  275 */
	char m_szftper1[9][9];			/* 081  356 */
	char m_szlibre3[9];				/* 009  365 */
	char m_szestpe1[10];			/* 010  375 */	// Estado del periodo bimestre
	char m_sznompe2[9][16];			/* 144  519 */
	char m_sznteva2[16];			/* 016  535 */
	char m_szfiper2[9][9];			/* 081  616 */
	char m_szlibre4[2];				/* 002  618 */
	char m_sziamora;				/* 001  275 */	// Indicador de aplicación de mora
	char m_szitmora;				/* 001  275 */	// Indicador de tipo de mora
	char m_szicpcpr;				/* 001  275 */	// Indicador cambio de parámetros cálculo de promedio
	char m_sziracal;				/* 001  275 */	// Indicador de rgistro auxiliar de calificación
	char m_sznccper;				/* 001  275 */	// No.Calificaciones por criterio por periodo
	char m_sznmcper;				/* 001  275 */	// No.Meses por criterio por periodo
	char m_szippfas;				/* 001  275 */	// Indicador prom.period.y final area secundaria
	char m_szftper2[9][9];			/* 081  365 */
	short int m_nzlibnot;			/* 002  407 */
	short int m_nzcibnot;			/* 002  407 */
	short int m_nzlibpag;			/* 002  407 */
	short int m_nzcibpag;			/* 002  407 */
	char m_szestpe2[10];			/* 010  375 */	// Estado del periodo trimestre
	short int m_nznumcuo;			/* 002  377 */
	char m_szestpad;		    	/* 001  378 */
	char m_szFIDato[9];		    	/* 009  387 */
	char m_sztipev1;		    	/* 001  388 */
	char m_sztipev2;		    	/* 001  389 */
	short int m_nznumpe2;			/* 002  391 */
	short int m_nznmalum;			/* 002  407 */
	char m_szitpcca;				/* 001  407 */	// Indicador tipo proceso concolidado calificacion
	char m_szgiapli;				/* 001  407 */	// Grado de inicio de aplicacion
	char m_szicpppo;				/* 001  407 */	// Indic.calc.promedio periodo con porcentaje.
	char m_szigpmdi;			  	/* 001  424 */	// Indic.grabar promedio multiplicado por 10.
	char m_szlisval[20];			/* 020  407 */	// Lista de valores
	char m_sziipmes;				/* 001  407 */	// Indic.de ingreso promedio mensual
	char m_sznmp001;				/* 001  407 */	// Num.meses periodo 001
	char m_sznmp002;				/* 001  407 */	// Num.meses periodo 002
	char m_sznmp003;				/* 001  407 */	// Num.meses periodo 003
	char m_sznmp004;				/* 001  407 */	// Num.meses periodo 004
	char m_szindpsm;				/* 001  407 */	// Indic.de presentar solo matriculados
	char m_szindimp;			  	/* 001  424 */	// Indic.de importación
	char m_szindexp;			  	/* 001  425 */	// Indic.de exportación
	char m_szindidm;				/* 001  426 */	// Indic.de ingreso datos mensuales
	char m_szindpdm;				/* 001  427 */	// Indic.de presentac.datos mensuales
	char m_szinddcp;				/* 001  428 */	// Indic.detalle califi.de periodo
	char m_szncaper;				/* 001  429 */	// numero de calificac.de periodo
	char m_szipappp;				/* 001  430 */	// Indic.de prom.asig.pen part.en proces.calculo
	char m_sziomppl;				/* 001  431 */	// Indic.de ord.mérito según posic.prom.en la lista
	char m_szctdsol[9][4];		  	/* 036  467 */	// Código tipo documento solicitado
	char m_szipbanc;				/* 001  468 */	// Indicador de Pago por Banco
	char m_sziipuni;				/* 001  469 */	// Indicador Ingreso Promedio Unidad
	char m_szippatr;				/* 001  469 */	// Indicador Presenta Pago con Atraso
	char m_szlibre1[5];				/* 007  475 Real = xxx */
};
