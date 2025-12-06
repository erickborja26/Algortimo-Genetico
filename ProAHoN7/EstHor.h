// Estructura correspondiente a los datos de Horarios
struct SEstHor
{
	unsigned char m_szcodcur[4];	/* 004  004 */
	char m_szcodgru[4];				/* 004  008 */
	char m_szcoddoc[4];				/* 004  012 */
	char m_szcodaul[3];				/* 003  015 */
	char m_sznumdia;				/* 001  016 */
	char m_szhorini[6];				/* 006  022 */
	char m_szhorfin[6];				/* 006  028 */
	char m_szlibre1[20];			/* 020  048 */
};
