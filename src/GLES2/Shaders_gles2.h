#define SHADER_VERSION "#version 100 \n"

static const char* vertex_shader =
SHADER_VERSION
"#if (__VERSION__ > 120)						\n"
"# define IN in									\n"
"# define OUT out								\n"
"#else											\n"
"# define IN attribute							\n"
"# define OUT varying							\n"
"#endif // __VERSION							\n"
"IN highp vec4 aPosition;						\n"
"IN lowp vec4 aColor;							\n"
"IN highp vec2 aTexCoord0;						\n"
"IN highp vec2 aTexCoord1;						\n"
"IN lowp float aNumLights;						\n"
"IN highp vec4 aModify;							\n"
"													\n"
"uniform int uRenderState;							\n"
"uniform int uTexturePersp;							\n"
"													\n"
"uniform lowp int uFogUsage;						\n"
"uniform mediump vec2 uFogScale;					\n"
"uniform mediump vec2 uScreenCoordsScale;			\n"
"													\n"
"uniform mediump vec2 uTexScale;					\n"
"uniform mediump vec2 uTexOffset[2];				\n"
"uniform mediump vec2 uCacheScale[2];				\n"
"uniform mediump vec2 uCacheOffset[2];				\n"
"uniform mediump vec2 uCacheShiftScale[2];			\n"
"uniform lowp ivec2 uCacheFrameBuffer;				\n"
"OUT lowp vec4 vShadeColor;							\n"
"OUT mediump vec2 vTexCoord0;						\n"
"OUT mediump vec2 vTexCoord1;						\n"
"OUT mediump vec2 vLodTexCoord;						\n"
"OUT lowp float vNumLights;							\n"

"mediump vec2 calcTexCoord(in vec2 texCoord, in int idx)		\n"
"{																\n"
"    vec2 texCoordOut = texCoord*uCacheShiftScale[idx];			\n"
"    texCoordOut -= uTexOffset[idx];							\n"
"    if (uCacheFrameBuffer[idx] != 0)							\n"
"      texCoordOut.t = -texCoordOut.t;							\n"
"    return (uCacheOffset[idx] + texCoordOut)* uCacheScale[idx];\n"
"}																\n"
"																\n"
"void main()													\n"
"{																\n"
"  gl_Position = aPosition;										\n"
"  vShadeColor = aColor;										\n"
"  if (uRenderState < 3) {										\n"
"    vec2 texCoord = aTexCoord0;								\n"
"    texCoord *= uTexScale;										\n"
"    if (uTexturePersp == 0 && aModify[2] == 0.0) texCoord *= 0.5;\n"
"    vTexCoord0 = calcTexCoord(texCoord, 0);					\n"
"    vTexCoord1 = calcTexCoord(texCoord, 1);					\n"
"    vLodTexCoord = texCoord * uCacheShiftScale[0];				\n"
"    vNumLights = aNumLights;									\n"
"    if (aModify != vec4(0.0)) {								\n"
"      if (aModify[0] != 0.0) {									\n"
"        gl_Position.xy = gl_Position.xy * uScreenCoordsScale + vec2(-1.0, 1.0);	\n"
"        gl_Position.xy *= gl_Position.w;						\n"
"      }														\n"
"      if (aModify[1] != 0.0)									\n"
"        gl_Position.z *= gl_Position.w;						\n"
"      if (aModify[3] != 0.0)									\n"
"        vNumLights = 0.0;										\n"
"    }															\n"
"    if (uFogUsage == 1) {										\n"
"      lowp float fp;											\n"
"      if (aPosition.z < -aPosition.w && aModify[1] == 0.0)		\n"
"        fp = -uFogScale.s + uFogScale.t;						\n"
"      else														\n"
"        fp = aPosition.z/aPosition.w*uFogScale.s + uFogScale.t;\n"
"      vShadeColor.a = clamp(fp, 0.0, 1.0);						\n"
"    }															\n"
"  } else {														\n"
"    vTexCoord0 = aTexCoord0;									\n"
"    vTexCoord1 = aTexCoord1;									\n"
"    vNumLights = 0.0;											\n"
"  }															\n"
"}																\n"
;

static const char* vertex_shader_notex =
SHADER_VERSION
"#if (__VERSION__ > 120)			\n"
"# define IN in						\n"
"# define OUT out					\n"
"#else								\n"
"# define IN attribute				\n"
"# define OUT varying				\n"
"#endif // __VERSION				\n"
"IN highp vec4 aPosition;			\n"
"IN lowp vec4 aColor;				\n"
"IN lowp float aNumLights;			\n"
"IN highp vec4 aModify;				\n"
"									\n"
"uniform int uRenderState;			\n"
"									\n"
"uniform lowp int uFogUsage;		\n"
"uniform mediump vec2 uFogScale;	\n"
"uniform mediump vec2 uScreenCoordsScale;\n"
"									\n"
"OUT lowp vec4 vShadeColor;			\n"
"OUT lowp float vNumLights;			\n"
"																\n"
"void main()													\n"
"{																\n"
"  gl_Position = aPosition;										\n"
"  vShadeColor = aColor;										\n"
"  if (uRenderState < 3) {										\n"
"    vNumLights = aNumLights;									\n"
"    if (aModify != vec4(0.0)) {								\n"
"      if (aModify[0] != 0.0) {								\n"
"        gl_Position.xy = gl_Position.xy * uScreenCoordsScale + vec2(-1.0, 1.0);	\n"
"        gl_Position.xy *= gl_Position.w;						\n"
"      }														\n"
"      if (aModify[1] != 0.0)									\n"
"        gl_Position.z *= gl_Position.w;						\n"
"      if (aModify[3] != 0.0)									\n"
"        vNumLights = 0.0;										\n"
"    }															\n"
"    if (uFogUsage == 1) {										\n"
"      lowp float fp;											\n"
"      if (aPosition.z < -aPosition.w && aModify[1] == 0.0)		\n"
"        fp = -uFogScale.s + uFogScale.t;						\n"
"      else														\n"
"        fp = aPosition.z/aPosition.w*uFogScale.s + uFogScale.t;\n"
"      vShadeColor.a = clamp(fp, 0.0, 1.0);						\n"
"    }															\n"
"  } else {														\n"
"    vNumLights = 0.0;											\n"
"  }															\n"
"}																\n"
;

static const char* fragment_shader_header_common_variables =
SHADER_VERSION
"#if (__VERSION__ > 120)		\n"
"# define IN in					\n"
"# define OUT out				\n"
"#else							\n"
"# define IN varying			\n"
"# define OUT					\n"
"#endif // __VERSION __			\n"
"uniform sampler2D uTex0;		\n"
"uniform sampler2D uTex1;		\n"
"uniform lowp vec4 uFogColor;	\n"
"uniform lowp vec4 uCenterColor;\n"
"uniform lowp vec4 uScaleColor;	\n"
"uniform lowp vec4 uBlendColor;	\n"
"uniform lowp vec4 uEnvColor;	\n"
"uniform lowp vec4 uPrimColor;	\n"
"uniform lowp float uPrimLod;	\n"
"uniform lowp float uK4;		\n"
"uniform lowp float uK5;		\n"
"uniform mediump vec2 uScreenScale;	\n"
"uniform lowp int uAlphaCompareMode;	\n"
"uniform lowp ivec2 uFbMonochrome;		\n"
"uniform lowp ivec2 uFbFixedAlpha;\n"
"uniform lowp int uEnableAlphaTest;	\n"
"uniform lowp int uCvgXAlpha;	\n"
"uniform lowp int uAlphaCvgSel;	\n"
"uniform lowp float uAlphaTestValue;\n"
"uniform mediump vec2 uDepthScale;	\n"
"uniform lowp ivec4 uBlendMux1;		\n"
"uniform lowp int uForceBlendCycle1;\n"
"IN lowp vec4 vShadeColor;	\n"
"IN mediump vec2 vTexCoord0;\n"
"IN mediump vec2 vTexCoord1;\n"
"IN mediump vec2 vLodTexCoord;\n"
"IN lowp float vNumLights;	\n"
"OUT lowp vec4 fragColor;		\n"
"lowp int nCurrentTile;			\n"
;

static const char* fragment_shader_header_common_variables_notex =
SHADER_VERSION
"#if (__VERSION__ > 120)		\n"
"# define IN in					\n"
"# define OUT out				\n"
"#else							\n"
"# define IN varying			\n"
"# define OUT					\n"
"#endif // __VERSION __			\n"
"uniform lowp vec4 uFogColor;	\n"
"uniform lowp vec4 uCenterColor;\n"
"uniform lowp vec4 uScaleColor;	\n"
"uniform lowp vec4 uBlendColor;	\n"
"uniform lowp vec4 uEnvColor;	\n"
"uniform lowp vec4 uPrimColor;	\n"
"uniform lowp float uPrimLod;	\n"
"uniform lowp float uK4;		\n"
"uniform lowp float uK5;		\n"
"uniform mediump vec2 uScreenScale;	\n"
"uniform lowp int uAlphaCompareMode;	\n"
"uniform lowp int uEnableAlphaTest;	\n"
"uniform lowp int uCvgXAlpha;	\n"
"uniform lowp int uAlphaCvgSel;	\n"
"uniform lowp float uAlphaTestValue;\n"
"uniform mediump vec2 uDepthScale;	\n"
"uniform lowp ivec4 uBlendMux1;		\n"
"uniform lowp int uForceBlendCycle1;\n"
"IN lowp vec4 vShadeColor;	\n"
"IN lowp float vNumLights;	\n"
"OUT lowp vec4 fragColor;		\n"
;

static const char* fragment_shader_header_common_variables_blend_mux_2cycle =
"uniform lowp ivec4 uBlendMux2;			\n"
"uniform lowp int uForceBlendCycle2;	\n"
;

static const char* fragment_shader_header_common_functions =
"															\n"
"lowp float snoise();						\n"
"void calc_light(in lowp float fLights, in lowp vec3 input_color, out lowp vec3 output_color);\n"
"mediump float mipmap(out lowp vec4 readtex0, out lowp vec4 readtex1);		\n"
"lowp vec4 readTex(in sampler2D tex, in mediump vec2 texCoord, in lowp int fbMonochrome, in bool fbFixedAlpha);	\n"
#ifdef USE_TOONIFY
"void toonify(in mediump float intensity);	\n"
#endif
;

static const char* fragment_shader_header_common_functions_notex =
"															\n"
"lowp float snoise();						\n"
"void calc_light(in lowp float fLights, in lowp vec3 input_color, out lowp vec3 output_color);\n"
;

static const char* fragment_shader_calc_light =
"uniform mediump vec3 uLightDirection[8];	\n"
"uniform lowp vec3 uLightColor[8];			\n"
"void calc_light(in lowp float fLights, in lowp vec3 input_color, out lowp vec3 output_color) {\n"
"  output_color = input_color;									\n"
"  lowp int nLights = int(floor(fLights + 0.5));				\n"
"  if (nLights == 0)											\n"
"     return;													\n"
"  output_color = uLightColor[nLights];							\n"
"  mediump float intensity;										\n"
"  mediump vec3 n = normalize(input_color);						\n"
"  for (int i = 0; i < nLights; i++)	{						\n"
"    intensity = max(dot(n, uLightDirection[i]), 0.0);			\n"
"    output_color += intensity*uLightColor[i];					\n"
"  };															\n"
"  clamp(output_color, 0.0, 1.0);								\n"
"}																\n"
;

static const char* fragment_shader_header_main =
"									\n"
"void main()						\n"
"{									\n"
"  lowp mat4 muxPM = mat4(vec4(0.0), vec4(0.0), uBlendColor, uFogColor);	\n"
"  lowp vec4 muxA = vec4(0.0, uFogColor.a, vShadeColor.a, 0.0);				\n"
"  lowp vec4 muxB = vec4(0.0, 1.0, 1.0, 0.0);								\n"
"  lowp vec4 vec_color, combined_color;										\n"
"  lowp float alpha1, alpha2;												\n"
"  lowp vec3 color1, color2, input_color;									\n"
;

#ifdef USE_TOONIFY
static const char* fragment_shader_toonify =
"																	\n"
"void toonify(in mediump float intensity) {							\n"
"   if (intensity > 0.5)											\n"
"	   return;														\n"
"	else if (intensity > 0.125)										\n"
"		fragColor = vec4(vec3(fragColor)*0.5, fragColor.a);\n"
"	else															\n"
"		fragColor = vec4(vec3(fragColor)*0.2, fragColor.a);\n"
"}																	\n"
;
#endif

static const char* fragment_shader_end =
"}                               \n"
;

static const char* fragment_shader_fake_mipmap =
"uniform lowp int uMaxTile;			\n"
"uniform mediump float uMinLod;		\n"
"														\n"
"mediump float mipmap(out lowp vec4 readtex0, out lowp vec4 readtex1) {	\n"
"  readtex0 = texture2D(uTex0, vTexCoord0);				\n"
"  readtex1 = texture2D(uTex1, vTexCoord1);				\n"
"  if (uMaxTile == 0) return 1.0;						\n"
"  return uMinLod;										\n"
"}														\n"
;

static const char* fragment_shader_readtex =
"lowp vec4 readTex(in sampler2D tex, in mediump vec2 texCoord, in lowp int fbMonochrome, in bool fbFixedAlpha)	\n"
"{																			\n"
"  lowp vec4 texColor = texture2D(tex, texCoord); 							\n"
"  if (fbMonochrome == 1) texColor = vec4(texColor.r);						\n"
"  else if (fbMonochrome == 2) 												\n"
"    texColor.rgb = vec3(dot(vec3(0.2126, 0.7152, 0.0722), texColor.rgb));	\n"
"  if (fbFixedAlpha) texColor.a = 0.825;									\n"
"  return texColor;															\n"
"}																			\n"
;

static const char* fragment_shader_readtex_3point =
"uniform mediump vec2 uTextureSize[2];								\n"
"uniform lowp int uTextureFilterMode;								\n"
// 3 point texture filtering.
// Original author: ArthurCarvalho
// GLSL implementation: twinaphex, mupen64plus-libretro project.
"#define TEX_OFFSET(off) texture2D(tex, texCoord - (off)/texSize)	\n"
"lowp vec4 filter3point(in sampler2D tex, in mediump vec2 texCoord)			\n"
"{																			\n"
"  mediump vec2 texSize = uTextureSize[nCurrentTile];						\n"
"  mediump vec2 offset = fract(texCoord*texSize - vec2(0.5));	\n"
"  offset -= step(1.0, offset.x + offset.y);								\n"
"  lowp vec4 c0 = TEX_OFFSET(offset);										\n"
"  lowp vec4 c1 = TEX_OFFSET(vec2(offset.x - sign(offset.x), offset.y));	\n"
"  lowp vec4 c2 = TEX_OFFSET(vec2(offset.x, offset.y - sign(offset.y)));	\n"
"  return c0 + abs(offset.x)*(c1-c0) + abs(offset.y)*(c2-c0);				\n"
"}																			\n"
"lowp vec4 readTex(in sampler2D tex, in mediump vec2 texCoord, in lowp int fbMonochrome, in bool fbFixedAlpha)	\n"
"{																			\n"
"  lowp vec4 texStandard = texture2D(tex, texCoord); 						\n"
"  lowp vec4 tex3Point = filter3point(tex, texCoord); 						\n"
"  lowp vec4 texColor = uTextureFilterMode == 0 ? texStandard : tex3Point;	\n"
"  if (fbMonochrome == 1) texColor = vec4(texColor.r);						\n"
"  else if (fbMonochrome == 2) 												\n"
"    texColor.rgb = vec3(dot(vec3(0.2126, 0.7152, 0.0722), texColor.rgb));	\n"
"  if (fbFixedAlpha) texColor.a = 0.825;									\n"
"  return texColor;															\n"
"}																			\n"
;

static const char* fragment_shader_noise =
"uniform sampler2D uTexNoise;		\n"
"lowp float snoise()									\n"
"{														\n"
"  mediump vec2 texSize = vec2(640.0, 580.0);						\n"
"  mediump vec2 coord = gl_FragCoord.xy/uScreenScale/texSize;		\n"
"  return texture2D(uTexNoise, coord).r;							\n"
"}														\n"
;

static const char* fragment_shader_dummy_noise =
"						\n"
"lowp float snoise()	\n"
"{						\n"
"  return 1.0;			\n"
"}						\n"
;

static const char* default_vertex_shader =
SHADER_VERSION
"#if (__VERSION__ > 120)						\n"
"# define IN in									\n"
"#else											\n"
"# define IN attribute							\n"
"#endif // __VERSION							\n"
"IN highp vec4 	aPosition;										\n"
"void main()                                                    \n"
"{                                                              \n"
"  gl_Position = aPosition;										\n"
"}                                                              \n"
;

static const char* zelda_monochrome_fragment_shader =
SHADER_VERSION
"uniform sampler2D uColorImage;									\n"
"uniform mediump vec2 uScreenSize;								\n"
"void main()													\n"
"{																\n"
"  mediump vec2 coord = gl_FragCoord.xy/uScreenSize;			\n"
"  lowp vec4 tex = texture2D(uColorImage, coord);				\n"
"  lowp float c = dot(vec4(0.2126, 0.7152, 0.0722, 0.0), tex);	\n"
"  gl_FragColor = vec4(c, c, c, 1.0);							\n"
"}																\n"
;

const char * strTexrectDrawerVertexShader =
SHADER_VERSION
"#if (__VERSION__ > 120)		\n"
"# define IN in					\n"
"# define OUT out				\n"
"#else							\n"
"# define IN attribute			\n"
"# define OUT varying			\n"
"#endif // __VERSION			\n"
"IN highp vec4 aPosition;		\n"
"IN highp vec2 aTexCoord0;		\n"
"OUT mediump vec2 vTexCoord0;	\n"
"void main()					\n"
"{								\n"
"  gl_Position = aPosition;		\n"
"  vTexCoord0 = aTexCoord0;		\n"
"}								\n"
;

const char * strTexrectDrawerFragmentShaderTex3Point =
SHADER_VERSION
"#if (__VERSION__ > 120)																						\n"
"# define IN in																									\n"
"# define OUT out																								\n"
"#else																											\n"
"# define IN varying																							\n"
"# define OUT																									\n"
"#endif // __VERSION __																							\n"
"uniform lowp int uTextureFilterMode;																			\n"
"uniform lowp vec4 uTextureBounds;																				\n"
"uniform mediump vec2 uTextureSize;																				\n"
// 3 point texture filtering.
// Original author: ArthurCarvalho
// GLSL implementation: twinaphex, mupen64plus-libretro project.
"#define TEX_OFFSET(off) texture2D(tex, texCoord - (off)/texSize)												\n"
"lowp vec4 filter3point(in sampler2D tex, in mediump vec2 texCoord)												\n"
"{																												\n"
"  mediump vec2 texSize = uTextureSize;																			\n"
"  mediump vec2 texelSize = vec2(1.0) / texSize;																\n"
"  lowp vec4 c = texture2D(tex, texCoord);		 																\n"
"  if (abs(texCoord.s - uTextureBounds[0]) < texelSize.x || abs(texCoord.s - uTextureBounds[2]) < texelSize.x) return c;	\n"
"  if (abs(texCoord.t - uTextureBounds[1]) < texelSize.y || abs(texCoord.t - uTextureBounds[3]) < texelSize.y) return c;	\n"
"																												\n"
"  mediump vec2 offset = fract(texCoord*texSize - vec2(0.5));													\n"
"  offset -= step(1.0, offset.x + offset.y);																	\n"
"  lowp vec4 zero = vec4(0.0);					 																\n"
"  lowp vec4 c0 = TEX_OFFSET(offset);																			\n"
"  lowp vec4 c1 = TEX_OFFSET(vec2(offset.x - sign(offset.x), offset.y));										\n"
"  lowp vec4 c2 = TEX_OFFSET(vec2(offset.x, offset.y - sign(offset.y)));										\n"
"  return c0 + abs(offset.x)*(c1-c0) + abs(offset.y)*(c2-c0);													\n"
"}																												\n"
"																											    \n"
"lowp vec4 readTex(in sampler2D tex, in mediump vec2 texCoord, in lowp int fbMonochrome, in bool fbFixedAlpha)	\n"
"{																												\n"
"  lowp vec4 texStandard = texture2D(tex, texCoord);								 							\n"
"  lowp vec4 tex3Point = filter3point(tex, texCoord); 															\n"
"  lowp vec4 texColor = uTextureFilterMode == 0 ? texStandard : tex3Point;										\n"
"  if (fbMonochrome == 1) texColor = vec4(texColor.r);															\n"
"  else if (fbMonochrome == 2) 																					\n"
"    texColor.rgb = vec3(dot(vec3(0.2126, 0.7152, 0.0722), texColor.rgb));										\n"
"  if (fbFixedAlpha) texColor.a = 0.825;																		\n"
"  return texColor;																								\n"
"}																												\n"
"																												\n"
"uniform sampler2D uTex0;																						\n"
"uniform lowp int uEnableAlphaTest;																				\n"
"IN mediump vec2 vTexCoord0;																					\n"
"OUT lowp vec4 fragColor;																						\n"
"void main()																									\n"
"{																												\n"
"  fragColor = readTex(uTex0, vTexCoord0, 0, false);															\n"
"  if (uEnableAlphaTest != 0 && !(fragColor.a > 0.0)) discard;													\n"
"  gl_FragColor = fragColor;																					\n"
"}																												\n"
;

const char * strTexrectDrawerFragmentShaderTexBilinear =
SHADER_VERSION
"#if (__VERSION__ > 120)																						\n"
"# define IN in																									\n"
"# define OUT out																								\n"
"#else																											\n"
"# define IN varying																							\n"
"# define OUT																									\n"
"#endif // __VERSION __																							\n"
"uniform lowp int uTextureFilterMode;																			\n"
"uniform lowp vec4 uTextureBounds;																				\n"
"uniform mediump vec2 uTextureSize;																				\n"
"#define TEX_OFFSET(off) texture2D(tex, texCoord - (off)/texSize)												\n"
"lowp vec4 filterBiLinear(in sampler2D tex, in mediump vec2 texCoord)											\n"
"{																												\n"
"  mediump vec2 texSize = uTextureSize;																			\n"
"  mediump vec2 texelSize = vec2(1.0) / texSize;																\n"
"  lowp vec4 c = texture2D(tex, texCoord);																		\n"
"  if (abs(texCoord.s - uTextureBounds[0]) < texelSize.x || abs(texCoord.s - uTextureBounds[2]) < texelSize.x) return c;	\n"
"  if (abs(texCoord.t - uTextureBounds[1]) < texelSize.y || abs(texCoord.t - uTextureBounds[3]) < texelSize.y) return c;	\n"
"																												\n"
"  mediump vec2 offset = fract(texCoord*texSize - vec2(0.5));													\n"
"  offset -= step(1.0, offset.x + offset.y);																	\n"
"  lowp vec4 zero = vec4(0.0);																					\n"
"																												\n"
"  lowp vec4 p0q0 = TEX_OFFSET(offset);																			\n"
"  lowp vec4 p1q0 = TEX_OFFSET(vec2(offset.x - sign(offset.x), offset.y));										\n"
"																												\n"
"  lowp vec4 p0q1 = TEX_OFFSET(vec2(offset.x, offset.y - sign(offset.y)));				                        \n"
"  lowp vec4 p1q1 = TEX_OFFSET(vec2(offset.x - sign(offset.x), offset.y - sign(offset.y)));						\n"
"																												\n"
"  mediump vec2 interpolationFactor = abs(offset);																\n"
"  lowp vec4 pInterp_q0 = mix( p0q0, p1q0, interpolationFactor.x ); // Interpolates top row in X direction.		\n"
"  lowp vec4 pInterp_q1 = mix( p0q1, p1q1, interpolationFactor.x ); // Interpolates bottom row in X direction.	\n"
"  return mix( pInterp_q0, pInterp_q1, interpolationFactor.y ); // Interpolate in Y direction.					\n"
"}																												\n"
"																												\n"
"lowp vec4 readTex(in sampler2D tex, in mediump vec2 texCoord, in lowp int fbMonochrome, in bool fbFixedAlpha)	\n"
"{																												\n"
"  lowp vec4 texStandard = texture2D(tex, texCoord);															\n"
"  lowp vec4 texBilinear = filterBiLinear(tex, texCoord);														\n"
"  lowp vec4 texColor = uTextureFilterMode == 0 ? texStandard : texBilinear;									\n"
"  if (fbMonochrome == 1) texColor = vec4(texColor.r);															\n"
"  else if (fbMonochrome == 2) 																					\n"
"    texColor.rgb = vec3(dot(vec3(0.2126, 0.7152, 0.0722), texColor.rgb));										\n"
"  if (fbFixedAlpha) texColor.a = 0.825;																		\n"
"  return texColor;																								\n"
"}																												\n"
"																												\n"
"uniform sampler2D uTex0;																						\n"
"uniform lowp int uEnableAlphaTest;																				\n"
"IN mediump vec2 vTexCoord0;																					\n"
"OUT lowp vec4 fragColor;																						\n"
"void main()																									\n"
"{																												\n"
"  fragColor = readTex(uTex0, vTexCoord0, 0, false);															\n"
"  if (uEnableAlphaTest != 0 && !(fragColor.a > 0.0)) discard;													\n"
"  gl_FragColor = fragColor;																					\n"
"}																												\n"
;

const char * strTexrectDrawerFragmentShaderClean =
SHADER_VERSION
"void main()								\n"
"{											\n"
"  gl_FragColor = vec4(0.0);				\n"
"}											\n"
;
