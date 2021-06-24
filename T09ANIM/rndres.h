/* FILE NAME: rndres.h
 * PROGRAMMER: KV6
 * DATE: 24.06.2021
 * PURPOSE: render shader data module
 */

#ifndef __rndres_h_
#define __rndres_h_



/* KV6_RndShadersInit */
VOID KV6_RndShadersInit( VOID );

/* KV6_RndShadersClose */
VOID KV6_RndShadersClose( VOID );

/* KV6_RndShadersUpdate */
VOID KV6_RndShadersUpdate( VOID );

/* KV6_RndShdFree */
VOID KV6_RndShdFree( INT ProgId );

/* KV6_RndShdLoad */
INT KV6_RndShdLoad( CHAR *FileNamePrefix );

/* KV6_RndShaderAdd */
INT KV6_RndShaderAdd( CHAR *FileNamePrefix );

/* KV6_RndLoadTextFromFile */
CHAR * KV6_RndLoadTextFromFile( CHAR *FileName );

/* KV6_RndShdLog */
VOID KV6_RndShdLog( CHAR *FileNamePrefix, CHAR *ShaderName, CHAR *Text );



#endif /* __rndres_h_ */

/* END OF 'rndres.h' FILE */