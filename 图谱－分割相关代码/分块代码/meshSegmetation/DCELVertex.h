//--------------------------------------------------------------------
// DCELVertex.h: interface for the DCELVertex class.
//--------------------------------------------------------------------
#ifndef DCELVertex_H
#define DCELVertex_H


#include <stdio.h>

#include "Vector.h"
#include "DCELHalfEdge.h"

//#include "simplexVertex.h"



class SimplexVertex;

class DCELVertex  
{
	friend class DCELFace;
	friend class DCELMesh;
	friend class DCELTools; 
	
public:
	Vector coords;  // Coordinate Vector.
	Vector normal;  // Normal Vector.
	DCELHalfEdge* leaving;  // HalfEdge originate from this Vertex.

    void* auxData;  // Store auxiliary data (e.g. IDs).

	//SimplexVertex *auxSVertex;  // Store corresponding _SimplexVertex_.


protected:
	DCELVertex* globalPrev;  // Previous "DCELVertex" in the DCELMesh::vertexList.
	DCELVertex* globalNext;  // Next "DCELVertex" in the DCELMesh::vertexList.	

public:
	DCELVertex();
	~DCELVertex();
	
	// Get the HalfEdge directed to the "DCELVertex v". 
	DCELHalfEdge* getEdgeTo(const DCELVertex* v) const;
};
#endif