//--------------------------------------------------------------------
// HalfEdgeList.h: interface for the HalfEdgeList class.
//
// Simple structure to manipulate a Singly Linked List of
// DCELHalfEdge*s. Used as temporary structure hung from auxData
// pointers during a mesh-building operation.
//--------------------------------------------------------------------
#ifndef HalfEdgeList_H
#define HalfEdgeList_H


#include <stdio.h>

#include "DCELHalfEdge.h"



class HalfEdgeList
{
	friend class DCELTools;
	
private:
	DCELHalfEdge* edge;
	HalfEdgeList* next;

public:
	HalfEdgeList(void);
	~HalfEdgeList(void);	


	// Add a DCELHalfEdge to the List.
	static void addToList(HalfEdgeList* &head, DCELHalfEdge* newEdge);

	// Add a HalfEdgeList item to the List. 
	static void addToList(HalfEdgeList* &head, HalfEdgeList* newItem);
	
	// Remove a DCELHalfEdge from the List.
	static bool removeFromList(HalfEdgeList* &head, DCELHalfEdge* edge);


	// Delete the List. 
	static void deleteList(HalfEdgeList* &head);	


	// Get the Length of the List. 
	static int  getListLength(HalfEdgeList* head);	
};
#endif