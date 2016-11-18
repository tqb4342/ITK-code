//--------------------------------------------------------------------
// DCELFace.cpp: implementation of the DCELFace class.
//--------------------------------------------------------------------
#include "DCELFace.h"
#include "DCELVertex.h"



//--------------------------------------------------------------------
// Constructor & Destructor.
//--------------------------------------------------------------------
DCELFace::DCELFace() : edge(NULL),auxData(NULL),globalPrev(NULL),globalNext(NULL){}
DCELFace::~DCELFace(){}


//--------------------------------------------------------------------
// Update the Normal Vector of this Face. 
//--------------------------------------------------------------------
void DCELFace::updateNormal()
{
	normal.zero();
	
	Vector backEdge;
	Vector forwardEdge;
	
	DCELHalfEdge* walkerE = edge;
	if (walkerE) 
	{
		forwardEdge = walkerE->twin->origin->coords - walkerE->origin->coords;
		walkerE = walkerE->next;
	}
	
	while (walkerE != edge) 
	{
		backEdge = forwardEdge * -1.0;
		forwardEdge = walkerE->twin->origin->coords - walkerE->origin->coords;
		normal.translateBy(forwardEdge.Cross(backEdge));
		walkerE = walkerE->next;
	}
	
	backEdge = forwardEdge * -1.0;
	forwardEdge = walkerE->twin->origin->coords - walkerE->origin->coords;	
	normal.translateBy(forwardEdge.Cross(backEdge));
	
	normal.normalize();
}

//--------------------------------------------------------------------
// Update the Normal Vector of this Face's vertices. 
//--------------------------------------------------------------------
void DCELFace::updateVertexNormals() const
{
	DCELHalfEdge* walkerE = edge;
	if(walkerE) 
	{
		walkerE->origin->normal.translateBy(normal);
		walkerE = walkerE->next;
	}
	
	while (walkerE != edge) 
	{
		walkerE->origin->normal.translateBy(normal);
		walkerE = walkerE->next;
	}
}


//--------------------------------------------------------------------
// Get the Number of the edges/vertices of this Face. 
//--------------------------------------------------------------------
int DCELFace::getEdgeCount() const
{
	int rval = 0;
	
	if(edge) 
	{
		DCELHalfEdge* walkerE = edge->next;
		rval = 1;
		
		while (walkerE != edge) 
		{
			rval++;
			walkerE = walkerE->next;
		}
	}
	
	return rval;
}