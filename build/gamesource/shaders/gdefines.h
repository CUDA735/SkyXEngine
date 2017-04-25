
#ifndef G_DEFINES
#define G_DEFINES
#define GREEN_ALPHATEST_VALUE 	0.5
#define PSSM_SHADING_LAST 		0.1
#define SHADOWGEN_JITTER_SCALE 1024.0

#define PI 3.141592654f

#define NOTLIGHTING_NOTTRANSPARENCY 0.0
#define LIGHTING_NOTTRANSPARENCY 	0.333333
#define NOTLIGHTING_TRANSPARENCY 	0.666667
#define LIGHTING_TRANSPARENCY 		1.0
#else
	#error G_DEFINES double include
#endif