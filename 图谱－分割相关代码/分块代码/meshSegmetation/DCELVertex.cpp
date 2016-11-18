//--------------------------------------------------------------------
// DCELVertex.cpp: implementation of the DCELVertex class.
//--------------------------------------------------------------------
#include "DCELVertex.h"



//--------------------------------------------------------------------
// Constructor & Destructor.
//--------------------------------------------------------------------
//DCELVertex::DCELVertex() : leaving(NULL),auxData(NULL),auxSVertex(NULL),globalPrev(NULL),globalNext(NULL){}
DCELVertex::DCELVertex() : leaving(NULL),auxData(NULL),globalPrev(NULL),globalNext(NULL){}
DCELVertex::~DCELVertex(){}


//--------------------------------------------------------------------
// Get the HalfEdge directed to the "DCELVertex v". 
//--------------------------------------------------------------------
DCELHalfEdge* DCELVertex::getEdgeTo(const DCELVertex* v) const
{
	DCELHalfEdge* rval = NULL;

	if (leaving) 
	{
		if (leaving->twin->origin == v) 
		{
			rval = leaving;
		} 
		else 
		{
			DCELHalfEdge* test = leaving->twin->next;
			while (rval == NULL && test != leaving) 
			{
				if (test->twin->origin == v) 
				{
					rval = test;
				} 
				else 
				{
					test = test->twin->next;
				}
			}
		}
	}
	
	return rval;
}