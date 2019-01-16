
/***********************************************************
Copyright � Vitaliy Buturlin, Evgeny Danilovich, 2017, 2018
See the license in LICENSE
***********************************************************/

#ifndef __GEOM_OPTIMIZE_H
#define __GEOM_OPTIMIZE_H

#include <gdefines.h>

void OptimizeIndecesInSubsetUint16(uint16_t* ib, uint16_t numFaces, uint16_t numVerts);
void OptimizeIndecesInSubsetUint32(uint32_t* ib, uint32_t numFaces, uint32_t numVerts);

#endif