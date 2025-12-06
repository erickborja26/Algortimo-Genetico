// Estructura correspondiente a los datos de Cursos horas
struct SEstCHo
{
	unsigned char m_szcodcur[4];	/* 004  004 */
	char m_szcthora;				/* 001  005 */
	char m_szlibre2;				/* 001  006 */
	char m_szctaula[4];		    	/* 004  010 */
	char m_sznumhor;		    	/* 001  011 */
	char m_szlibre1[21];			/* 021  032 */
};
