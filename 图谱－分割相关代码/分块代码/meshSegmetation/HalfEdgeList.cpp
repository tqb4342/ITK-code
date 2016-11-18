//--------------------------------------------------------------------
// HalfEdgeList.cpp: implementation of the HalfEdgeList class.
//--------------------------------------------------------------------
#include "HalfEdgeList.h"



//--------------------------------------------------------------------
// Constructor & Destructor.
//--------------------------------------------------------------------
HalfEdgeList::HalfEdgeList(void) : edge(NULL),next(NULL){}
HalfEdgeList::~HalfEdgeList(void){}


//--------------------------------------------------------------------
// Add a DCELHalfEdge to the List. 
//--------------------------------------------------------------------
void HalfEdgeList::addToList(HalfEdgeList* &head, DCELHalfEdge* newEdge)
{
	HalfEdgeList* newList = new HalfEdgeList();	
	newList->edge = newEdge;
	
	addToList(head, newList);
}

//--------------------------------------------------------------------
// Add a HalfEdgeList item to the List. 
//--------------------------------------------------------------------
void HalfEdgeList::addToList(HalfEdgeList* &head, HalfEdgeList* newItem)
{
	newItem->next = head;
	head = newItem;
}

//--------------------------------------------------------------------
// Remove a DCELHalfEdge from the List. 
//--------------------------------------------------------------------
bool HalfEdgeList::removeFromList(HalfEdgeList* &head, DCELHalfEdge* edge)
{
	bool rval = false;

	HalfEdgeList* walker = head;
	HalfEdgeList* follower = NULL;
	while (!rval && walker) 
	{
		if (walker->edge == edge) 
		{
			if (follower) 
			{
				follower->next = walker->next;
			} 
			else 
			{
				head = walker->next;
			}
			
			delete walker;
			rval = true;
		} 
		else 
		{
			follower = walker;
			walker = walker->next;
		}
	}

	return rval;
}


//--------------------------------------------------------------------
// Delete the List. 
//--------------------------------------------------------------------
void HalfEdgeList::deleteList(HalfEdgeList* &head)
{
	HalfEdgeList* walker = NULL;

	while (walker = head) 
	{
		head = head->next;
		
		delete walker;
	}
}


//--------------------------------------------------------------------
// Get the Length of the List. 
//--------------------------------------------------------------------
int HalfEdgeList::getListLength(HalfEdgeList* head)
{
	int rval = 0;

	HalfEdgeList* walker = head;
	while(walker) 
	{
		rval++;
		walker = walker->next;
	}

	return rval;
}