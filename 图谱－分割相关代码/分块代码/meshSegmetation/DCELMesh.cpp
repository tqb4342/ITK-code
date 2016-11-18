//--------------------------------------------------------------------
// DCELVertex.cpp: implementation of the DCELVertex class.
//--------------------------------------------------------------------
#include "DCELMesh.h"



//--------------------------------------------------------------------
// Constructor & Destructor.
//--------------------------------------------------------------------
DCELMesh::DCELMesh()
{
	vertexList = NULL;
	halfEdgeList = NULL;
	faceList = NULL;
	
	numVertices = 0;
	numHalfEdges = 0;	
	numFaces = 0;
	
	min.x = min.y = min.z = -1.0;
	max.x = max.y = max.z = 1.0;
	
	vertexTotal.zero();
}

DCELMesh::~DCELMesh()    
{    
	clear();   
}


//--------------------------------------------------------------------
// Delete ALL Objects in this Mesh,except the auxData Objects.
//--------------------------------------------------------------------
void DCELMesh::clear()
{
	// Delete ALL DCELFace Objects.
	DCELFace* walkerF = faceList;
	DCELFace* tempF = NULL;
	while(walkerF) 
	{
		tempF = walkerF->globalNext;
		delete walkerF;
		
		walkerF = tempF;
	}	
	faceList = NULL;
	
	// Delete ALL DCELVertex Objects.
	DCELVertex* walkerV = vertexList;
	DCELVertex* tempV = NULL;
	while(walkerV) 
	{
		tempV = walkerV->globalNext;
		delete walkerV;
		
		walkerV = tempV;
	}	
	vertexList = NULL;
	
	// Delete ALL DCELHalfEdge Objects.
	DCELHalfEdge* walkerE = halfEdgeList;
	DCELHalfEdge* tempE = NULL;
	while(walkerE) 
	{
		tempE = walkerE->globalNext;
		delete walkerE;
		
		walkerE = tempE;
	}
	halfEdgeList = NULL;

	numFaces = 0;
	numHalfEdges = 0;
	numVertices = 0;
	
	min.x = min.y = min.z = -1.0;
	max.x = max.y = max.z = 1.0;
	
	vertexTotal.zero();
}

//--------------------------------------------------------------------
// True iff this Mesh contains no Objects.
//--------------------------------------------------------------------
bool DCELMesh::isEmpty() const
{
	return ( (vertexList == NULL) && 
		     (faceList == NULL) && 
		     (halfEdgeList == NULL) );
}


//-------------------------------------------------------------------------------------
// Insert DCELVertex Object at the HEAD of the vertexList. 
//-------------------------------------------------------------------------------------
void DCELMesh::insert(DCELVertex* v)
{
	if(v) 
	{
		if(vertexList) 
		{
			v->globalNext = vertexList;
			vertexList->globalPrev = v;
			vertexList = v;
		} 
		else 
		{
			vertexList = v;
		}
		
		numVertices++;
	}
}

//--------------------------------------------------------------------
// Insert DCELHalfEdge Object at the HEAD of the halfEdgeList. 
//--------------------------------------------------------------------
void DCELMesh::insert(DCELHalfEdge* e)
{
	if(e) 
	{
		if(halfEdgeList)
		{
			e->globalNext = halfEdgeList;
			halfEdgeList->globalPrev = e;
			halfEdgeList = e;
		} 
		else 
		{
			halfEdgeList = e;
		}
		
		numHalfEdges++;
	}
}

//--------------------------------------------------------------------
// Insert DCELFace Object at the HEAD of the faceList. 
//--------------------------------------------------------------------
void DCELMesh::insert(DCELFace* f)
{
	if(f) 
	{
		if(faceList) 
		{
			f->globalNext = faceList;
			faceList->globalPrev = f;
			faceList = f;
		} 
		else 
		{
			faceList = f;
		}
		
		numFaces++;
	}
}


//-------------------------------------------------------------------------------------
// Removes DCELVertex Object from the vertexList.
//-------------------------------------------------------------------------------------
void DCELMesh::remove(DCELVertex* v)
{
	if(v) 
	{
		// When the DCELVertex to be removed at the HEAD of the vertexList.
		if (vertexList == v) 
		{
			vertexList = vertexList->globalNext;
			if(vertexList) 
			{
				vertexList->globalPrev = NULL;
			}
		} 
		else 
		{
			v->globalPrev->globalNext = v->globalNext;
			if(v->globalNext) 
			{
				v->globalNext->globalPrev = v->globalPrev;
			}
		}
		
		v->globalNext = NULL;
		v->globalPrev = NULL;
		numVertices--;
	}
}

//--------------------------------------------------------------------
// Removes DCELHalfEdge Object from the halfEdgeList.
//--------------------------------------------------------------------
void DCELMesh::remove(DCELHalfEdge* e)
{
	if (e) 
	{
		// When the DCELHalfEdge to be removed at the HEAD of the halfEdgeList.
		if (halfEdgeList == e) 
		{
			halfEdgeList = halfEdgeList->globalNext;
			if (halfEdgeList) 
			{
				halfEdgeList->globalPrev = NULL;
			}
		} 
		else 
		{
			e->globalPrev->globalNext = e->globalNext;
			if (e->globalNext) 
			{
				e->globalNext->globalPrev = e->globalPrev;
			}
		}
		
		e->globalNext = NULL;
		e->globalPrev = NULL;
		numHalfEdges--;
	}
}

//--------------------------------------------------------------------
// Removes DCELFace Object from the faceList.
//--------------------------------------------------------------------
void DCELMesh::remove(DCELFace* f)
{
	if (f) 
	{
		// When the DCELFace to be removed at the HEAD of the faceList.
		if (faceList == f) 
		{
			faceList = faceList->globalNext;
			if (faceList) 
			{
				faceList->globalPrev = NULL;
			}
		} 
		else 
		{
			f->globalPrev->globalNext = f->globalNext;
			if (f->globalNext) 
			{
				f->globalNext->globalPrev = f->globalPrev;
			}
		}
		
		f->globalNext = NULL;
		f->globalPrev = NULL;
		numFaces--;
	}
}


//-------------------------------------------------------------------------------------
// Update the Normal Vector of the Faces in this Mesh.
//-------------------------------------------------------------------------------------
void DCELMesh::updateFaceNormals()
{
	for (DCELFace* walker=faceList; walker; advance(walker))
	{
		walker->updateNormal();
	}
}

//--------------------------------------------------------------------
// Update the Normal Vector of the Face's vertices in this Mesh.
//--------------------------------------------------------------------
void DCELMesh::updateVertexNormals()
{
	DCELVertex* walkerV;
	for (walkerV=vertexList; walkerV; advance(walkerV)) 
	{
		walkerV->normal.zero();
	}
	
	for (DCELFace* walkerF=faceList; walkerF ;advance(walkerF)) 
	{
		walkerF->updateVertexNormals();
	}
	
	for (walkerV=vertexList; walkerV; advance(walkerV)) 
	{
		walkerV->normal.normalize();
	}
}

//--------------------------------------------------------------------
// Sets purely geometric edge bit: DCEL_EDGE_BOUNDARY_BIT.
//--------------------------------------------------------------------
void DCELMesh::updateEdgeBits()
{
	for (DCELHalfEdge* walkerE=halfEdgeList; walkerE; advance(walkerE)) 
	{
		if( walkerE->face == &infiniteFace ||
		    walkerE->twin->face == &infiniteFace) 
		{
			walkerE->setMask(DCELHalfEdge::DCEL_EDGE_BOUNDARY_BIT,true);
		} 
		else 
		{
			walkerE->setMask(DCELHalfEdge::DCEL_EDGE_BOUNDARY_BIT,false);
		}
	}
}

//--------------------------------------------------------------------
// Calculates Bounding Box and internal statistics.
//--------------------------------------------------------------------
void DCELMesh::updateStatistics()
{
	vertexTotal.zero();

	DCELVertex* walkerV = vertexList;
	if(walkerV) 
	{
		min = walkerV->coords;
		max = walkerV->coords;
		vertexTotal.translateBy(walkerV->coords);
		walkerV = walkerV->globalNext;
	}
	
	while(walkerV) 
	{
		if (walkerV->coords.x < min.x) 
		{
			min.x = walkerV->coords.x;
		} 
		else if (walkerV->coords.x > max.x) 
		{
			max.x = walkerV->coords.x;
		}
		
		if (walkerV->coords.y < min.y) 
		{
			min.y = walkerV->coords.y;
		} 
		else if (walkerV->coords.y > max.y) 
		{
			max.y = walkerV->coords.y;
		}
		
		if (walkerV->coords.z < min.z) 
		{
			min.z = walkerV->coords.z;
		} 
		else if (walkerV->coords.z > max.z) 
		{
			max.z = walkerV->coords.z;
		}
		
		vertexTotal.translateBy(walkerV->coords);
		
		advance(walkerV);
	}
}

//--------------------------------------------------------------------
// Shorthand for calling ALL the update functions.
//--------------------------------------------------------------------
void DCELMesh::updateAll()
{
	// Should call BEFORE updateVertexNormals().
	updateFaceNormals();	
	updateVertexNormals();		
	updateEdgeBits();
	updateStatistics();
}


//--------------------------------------------------------------------
// Get center of mass of this Mesh.
//--------------------------------------------------------------------
Vector DCELMesh::getCentroid() const
{
	return vertexTotal*(1.0/(double)numVertices);
}


//--------------------------------------------------------------------
// Helper function to set or clear a particular mask 
// on all the HalfEdge*s.
//--------------------------------------------------------------------
void DCELMesh::setHalfEdgeMasks(unsigned int mask, bool value)
{
	for(DCELHalfEdge* walkerE = halfEdgeList; walkerE; advance(walkerE)) 
	{
		walkerE->setMask(mask, value);
	}
}


//--------------------------------------------------------------------
// Calculate the Number of Triangles in this Mesh.
//--------------------------------------------------------------------
int DCELMesh::getNumTriangles()
{
	int rval = 0;
	
	for (DCELFace* walkerF=faceList; walkerF; advance(walkerF)) 
	{
		if( 3 == walkerF->getEdgeCount() )
		{
			rval++;
		}
		
		/*if (walkerF->edge->next->next->next == walkerF->edge) 
		{
			rval++;		
		}*/
	}
	
	return rval;
}

//--------------------------------------------------------------------
// Calculate the Number of Quads in this Mesh.
//--------------------------------------------------------------------
int DCELMesh::getNumQuads()
{
	int rval = 0;
	
	for (DCELFace* walkerF=faceList; walkerF; advance(walkerF)) 
	{
		if( 4 == walkerF->getEdgeCount() )
		{
			rval++;
		}
		
		/*if (walkerF->edge->next->next->next->next == walkerF->edge) 
		{
			rval++;
		}*/
	}
	
	return rval;
}