/* FILE NAME: rndres.h
 * PROGRAMMER: KV6
 * DATE: 26.06.2021
 * PURPOSE: Rendering declaration module
 */

#ifndef __rndres_h_
#define __rndres_h_

#include "../../../def.h"

#define KV6_STR_MAX 300
#define KV6_MAX_TEXTURES 30


typedef struct tagkv6SHADER
{
  CHAR Name[KV6_STR_MAX]; /* Shader filename prefix */
  INT ProgId;             /* Shader program Id */
} kv6SHADER;

#define KV6_MAX_SHADERS 30
extern kv6SHADER KV6_RndShaders[KV6_MAX_SHADERS];
extern INT KV6_RndShadersSize;


VOID KV6_RndShadersInit( VOID );
VOID KV6_RndShadersClose( VOID );
INT KV6_RndShaderAdd( CHAR *FileNamePrefix );
VOID KV6_RndShadersUpdate( VOID );

#define KV6_MTL_SIZE 100
#define KV6_MAX_MATERIALS 10

typedef struct tagkv6MATERIAL
{
  CHAR Name[KV6_MTL_SIZE];
  VEC Ka, Kd, Ks;
  FLT Ph;
  FLT Trans;
  INT Tex[8];

  /* Shader string */
  CHAR ShaderStr[KV6_MTL_SIZE];
  INT ShdNo;
} kv6MATERIAL;

extern kv6MATERIAL KV6_RndMaterials[KV6_MAX_MATERIALS];
extern INT KV6_RndMaterialsSize;

VOID KV6_RndMtlInit( VOID );
VOID KV6_RndMtlClose( VOID );
INT KV6_RndMtlAdd( kv6MATERIAL *mtl );
INT KV6_RndMtlApply( INT MtlNo );

/***
 * Textures stock functions
 ***/

typedef struct tagkv6TEXTURE
{
  CHAR Name[KV6_STR_MAX]; /* Texture name */
  INT W, H;               /* Texture size in pixels */
  UINT TexId;             /* OpenGL texture Id */ 
} kv6TEXTURE;

extern kv6TEXTURE KV6_RndTextures[KV6_MAX_TEXTURES];
extern INT KV6_RndTexturesSize;

/***
 * Base textures functions
 ***/

/* Texture stock initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID KV6_RndTexturesInit( VOID );

/* Texture stock deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID KV6_RndTexturesClose( VOID );

/* Texture add to stock function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture size:
 *       INT W, H;
 *   - texture bytes per pixel:
 *       INT C;
 *   - texture pixel colors pointer:
 *       VOID *Bits;
 * RETURNS:
 *   (INT) shader number in stock.
 */
INT KV6_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );

#endif