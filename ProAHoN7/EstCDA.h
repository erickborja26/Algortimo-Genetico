// Estructura correspondiente a los datos Calificaciones Detalladas de Alumnos
struct SEstCDA
{
	unsigned char m_szcodniv;		/* 001  001 */
	char m_szcodgra;				/* 001  002 */
	char m_szcodsec;				/* 001  003 */
	char m_szcodalu[7];				/* 007  010 */
	char m_szcodasi[7];				/* 007  017 */
	short int m_nzcalifi[21];		/* 042  059 */
	short int m_nzpromed;			/* 002  061 */
	char m_szestcal;				/* 001  062 */
	char m_szlibre1[16];			/* 016  080 */
};
