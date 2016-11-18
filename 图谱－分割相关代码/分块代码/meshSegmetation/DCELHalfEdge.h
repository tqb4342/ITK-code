//--------------------------------------------------------------------
// DCELHalfEdge.h: interface for the DCELHalfEdge class.
//--------------------------------------------------------------------
#ifndef DCELHalfEdge_H
#define DCELHalfEdge_H


#include <stdio.h>



class DCELVertex;
class DCELFace;

class DCELHalfEdge  
{
	friend class DCELVertex;
	friend class DCELFace;
	friend class DCELMesh;
	friend class DCELTools;
	
public:	
	enum DCEL_EDGE_BITS 
	{
		// Set during any Processing Loop to indicate that the half-edge has
		// been processed. (e.g. when running through all half-edges and
		// rendering edges, set on the twin to prevent re-rendering an edge)
		// This is volatile... that is, it should not be assumed to be set or
		// unset at the beginning of a function, and need not be left in a
		// meaningful state at the end of a function
		DCEL_EDGE_PROCESSED_BIT	= (1 << 0) /* 1 */,
		
		// Indicate that this HalfEdge or its twin face is the Infinite Face.
		DCEL_EDGE_BOUNDARY_BIT = (1 << 1) /* 2 */,
		
		// Indicate that this HalfEdge is Selected.
		DCEL_EDGE_SELECTED_BIT = (1 << 2) /* 4 */,
		
		// Indicate that this HalfEdge is Marked.
		DCEL_EDGE_MARKED_BIT = (1 << 3) /* 8 */,
		
		// Indicate that this HalfEdge and its twin comprise a silhouette edge.
		DCEL_EDGE_SILHOUETTE_BIT = (1 << 4) /* 16 */
	};
	
public:
	DCELVertex* origin;  // From which the HalfEdge starts.
	DCELHalfEdge* twin;  // HalfEdge on the "right" side of this HalfEdge.
	DCELHalfEdge* next;  // Next HalfEdge of THE Face, traveling counterclockwise.
	DCELFace* face;  // Face on the "left" side of this HalfEdge.
	
	void* auxData;  // Store auxiliary data (e.g. IDs).

	// Optional member to store some state during operations. 
	// Not maintained internally,except by user-initiated calls on the full mesh.
	unsigned int displayBits;

protected:
	DCELHalfEdge* globalPrev;  // Previous "DCELHalfEdge" in the DCELMesh::halfEdgeList.
	DCELHalfEdge* globalNext;  // Next "DCELHalfEdge" in the DCELMesh::halfEdgeList.	

public:
	DCELHalfEdge();
	~DCELHalfEdge();

	// Helper functions for manipulating the displayBits property.
	bool isMaskSet(unsigned int mask) const 
	{ 
		return ( (displayBits & mask) == mask ); 
	}
	
	void setMask(unsigned int mask, bool value) 
	{
		displayBits=(value ? (displayBits | mask) : (displayBits & ~mask)); 
	}

	
	// Get the previous HalfEdge of THE Face, traveling counterclockwise.
	DCELHalfEdge* getPrev();	
};
#endif