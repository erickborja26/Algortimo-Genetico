// Estructura correspondiente a los datos de Docentes
struct SEstDoc
{
	unsigned char m_szcoddoc[4];	/* 004  004 */
	char m_szctdisp;				/* 001  005 */
	char m_szlibre2;				/* 001  006 */
	char m_szapdoce[16];	    	/* 016  022 */
	char m_szamdoce[16];	    	/* 016  038 */
	char m_sznomdoc[16];	    	/* 016  054 */
	char m_szlibre1[10];			/* 010  064 */
};
