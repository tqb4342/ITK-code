//--------------------------------------------------------------------
// DCELMesh.h: interface for the DCELMesh class.
//--------------------------------------------------------------------
#ifndef DCELMesh_H
#define DCELMesh_H


#include <stdio.h>

#include "Vector.h"
#include "DCELVertex.h"
#include "DCELHalfEdge.h"
#include "DCELFace.h"



//class DCELVertex;
class DCELFace;

class DCELMesh  
{
public:
	DCELVertex* vertexList;  // Doubly-linked lists for Vertices.
	DCELHalfEdge* halfEdgeList;  // Doubly-linked lists for Edges.
	DCELFace* faceList;  // Doubly-linked lists for Faces.
	
	int numVertices;   // Number of Vertices in this Mesh.
	int numHalfEdges;  // Number of HalfEdges in this Mesh.
	int numFaces;      // Number of Faces in this Mesh.

	Vector min;  // Left-down the of the Bounding Box.
	Vector max;  // Right-up the of the Bounding Box.
	Vector vertexTotal;  // Sum of ALL the Vertices Vector.

	DCELFace infiniteFace;  // THE Infinite Face.

public:
	DCELMesh();
	~DCELMesh();

	// Delete ALL Objects in this Mesh,except the auxData Objects.
	void clear();
	
	// True iff this Mesh contains no Objects.
	bool isEmpty() const;

	// Return current counts of member objects.
	int getNumVertices()  const { return numVertices;  }
	int getNumHalfEdges() const { return numHalfEdges; }
	int getNumFaces()     const { return numFaces;     }

	
//--------------------------------------------------------------------
// Simple ITERATION interface.Support FORWARD traversal only.
//--------------------------------------------------------------------
	// Get FIRST Object.
	DCELVertex* firstVertex()        { return vertexList; }
	DCELHalfEdge* firstHalfEdge()    { return halfEdgeList; }
	DCELFace* firstFace()            { return faceList; }
	
	// Get NEXT Object.
	DCELVertex* next(DCELVertex* v)        { return    (v!=NULL) ? v->globalNext : NULL; }
	DCELHalfEdge* next(DCELHalfEdge* e)    { return    (e!=NULL) ? e->globalNext : NULL; }
	DCELFace* next(DCELFace* f)            { return    (f!=NULL) ? f->globalNext : NULL; }
	
	// Advance to the NEXT Object.
	void advance(DCELVertex* &v)    {    v = (v!=NULL) ? v->globalNext : NULL; }
	void advance(DCELHalfEdge* &e)  {    e = (e!=NULL) ? e->globalNext : NULL; }
	void advance(DCELFace* &f)      {    f = (f!=NULL) ? f->globalNext : NULL; }
//--------------------------------------------------------------------
// Insert the Object at the HEAD of the appropriate List. 
// This means that insertion is a safe operation during processing 
// of all objects of a particular type, because they will be 
// inserted before the current iterator position.
//--------------------------------------------------------------------
	void insert(DCELVertex* v);	
	void insert(DCELHalfEdge* e);
	void insert(DCELFace* f);
//--------------------------------------------------------------------	
// Removes the Object from the appropriate List, but DOES NOT delete 
// the Object. Caller is responsible for correct usage. 
// Removing an object that is not in the mesh is an unsafe operation.
//--------------------------------------------------------------------
	void remove(DCELVertex* v);	
	void remove(DCELHalfEdge* e);
	void remove(DCELFace* f);
//--------------------------------------------------------------------
// Update functions.
//--------------------------------------------------------------------
	// Calculates a Normal for each face based on its geometry.
	void updateFaceNormals();
	
	// Calculates a Normal for each vertex based on the normals of the Faces Around it.
	// Requires updateFaceNormals() call BEFORE, or Manual setting of Face normals.
	void updateVertexNormals();
	
	// Sets purely geometric edge bits. 
	// Does not affect viewing or view-specific bits.
	void updateEdgeBits();
	
	// Calculates Bounding Box and internal statistics.
	void updateStatistics();
	
	// Shorthand for calling the above four update functions.
	void updateAll();
//--------------------------------------------------------------------	
//--------------------------------------------------------------------
	// Only valid after an updateStatistics() or updateAll() call.
	// Returns center of mass of this Mesh, 
	// assuming all vertices have equal mass.
	Vector getCentroid() const;	
	
	
	// Get the the info of the Bounding Box.
	void loadBoundingBox(Vector &minPoint, Vector &maxPoint) const 
	{    
		minPoint = min; 
		maxPoint = max;    
	}
	
	
	// Returns the only infiniteFace pointer. This never changes 
	// during the lifetime of the Mesh.
	DCELFace* getInfiniteFace() { return &infiniteFace; }
	
	// Helper function to set or clear a particular mask 
	// on all the HalfEdge*s.
	void setHalfEdgeMasks(unsigned int mask, bool value);

	
	// Calculate the Number of Triangles in this Mesh.
	int getNumTriangles();
	
	// Calculate the Number of Quads in this Mesh.
	int getNumQuads();	
};
#endif