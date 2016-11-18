//--------------------------------------------------------------------
// DCELFace.h: interface for the DCELFace class.
//--------------------------------------------------------------------
#ifndef DCELFace_H
#define DCELFace_H


#include <stdio.h>

#include "Vector.h"
#include "DCELHalfEdge.h"



class DCELFace  
{
	friend class DCELMesh;
	friend class DCELTools;
	
public:
	Vector normal;  // Normal Vector.  
	DCELHalfEdge* edge;  // HalfEdge has this Face as its face.

	void* auxData;  // Store auxiliary data (e.g. IDs).

protected:
	DCELFace* globalPrev;  // Previous "DCELFace" in the DCELMesh::faceList.
	DCELFace* globalNext;  // Next "DCELFace" in the DCELMesh::faceList.

public:
	DCELFace();
	~DCELFace();
	

	// Update the Normal Vector of this Face.
	void updateNormal();

	// Update the Normal Vector of this Face's vertices.
	void updateVertexNormals() const;


	// Get the Number of the edges/vertices of this Face. 
	int  getEdgeCount() const;	
};
#endif