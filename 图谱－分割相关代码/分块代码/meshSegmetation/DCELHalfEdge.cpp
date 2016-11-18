//--------------------------------------------------------------------
// DCELHalfEdge.cpp: implementation of the DCELHalfEdge class.
//--------------------------------------------------------------------
#include "DCELHalfEdge.h"



//--------------------------------------------------------------------
// Constructor & Destructor.
//--------------------------------------------------------------------
DCELHalfEdge::DCELHalfEdge() : twin(NULL), next(NULL), face(NULL), 
				origin(NULL), auxData(NULL), displayBits(0),
				globalPrev(NULL), globalNext(NULL) {}
DCELHalfEdge::~DCELHalfEdge(){}


//--------------------------------------------------------------------
// Get the previous HalfEdge of THE Face, traveling counterclockwise.
//--------------------------------------------------------------------
DCELHalfEdge* DCELHalfEdge::getPrev()
{
	DCELHalfEdge* rval = twin->next->twin;
	
	while (rval->next != this)		
	{
		rval = rval->next->twin;
	}

	return rval;
}