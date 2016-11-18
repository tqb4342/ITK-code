//--------------------------------------------------------------------
// DCELTools.h: interface for the DCELTools class.
//
// Static function class to demonstrate some operations on a DCELMesh,
// including validation,construction,and storing to an OFF file.
//--------------------------------------------------------------------
#ifndef DCELTools_H
#define DCELTools_H


#include <stdio.h>

#include "DCELMesh.h"



class DCELTools  
{
private:
	DCELTools();
	~DCELTools();

public:
//--------------------------------------------------------------------
// Check the Consistency of the Objects.
//--------------------------------------------------------------------
	static bool isConsistent(DCELVertex* v);
	static bool isConsistent(DCELHalfEdge* e);
	static bool isConsistent(DCELFace* f);	
	static bool isConsistent(DCELMesh* m);
//--------------------------------------------------------------------
// I/O operations for the DCELMesh.
//--------------------------------------------------------------------
	static bool loadFromOFF(const char *filename, DCELMesh* m);
	static bool storeToOFF(char *filename, DCELMesh* m);
};
#endif