//--------------------------------------------------------------------
// DCELTools.cpp: implementation of the DCELTools class.
//--------------------------------------------------------------------
#include "DCELTools.h"
#include "HalfEdgeList.h"

#include <fstream>
#include <string>

using namespace std;



//--------------------------------------------------------------------
// Constructor & Destructor.
//--------------------------------------------------------------------
DCELTools::DCELTools(){}
DCELTools::~DCELTools(){}


//--------------------------------------------------------------------
// Check the Consistency of the DCELVertex*s.
//--------------------------------------------------------------------
bool DCELTools::isConsistent(DCELVertex* v)
{
	bool rval = true;

	if( (v->leaving == NULL) || (v->leaving->origin !=v ) ) 
	{
		rval = false;
	}

	return rval;
}

//--------------------------------------------------------------------
// Check the Consistency of the DCELHalfEdge*s.
//--------------------------------------------------------------------
bool DCELTools::isConsistent(DCELHalfEdge* e)
{
	bool rval = true;

	if( (e->twin == NULL) || (e->twin->twin != e) ||
	    (e->origin == NULL) || (e->face == NULL) ||
	    (e->next == NULL) || (e->next->face != e->face) ) 
	{
		rval = false;
	}

	return rval;
}

//--------------------------------------------------------------------
// Check the Consistency of the DCELFace*s.
//--------------------------------------------------------------------
bool DCELTools::isConsistent(DCELFace* f)
{
	bool rval = true;

	if ( (f->edge==NULL) || (f->edge->face!=f) ) 
	{
		rval = false;
	}

	return rval;
}

//--------------------------------------------------------------------
// Check the Consistency of the DCELMesh*s.
//--------------------------------------------------------------------
bool DCELTools::isConsistent(DCELMesh* m)
{
	bool rval = true;

	DCELHalfEdge* eWalker = m->firstHalfEdge();
	while(rval && eWalker) 
	{
		if (!isConsistent(eWalker)) 
		{
			rval = false;
		} 
		else 
		{
			m->advance(eWalker);
		}
	}
	
	DCELVertex* vWalker = m->firstVertex();
	while(rval && vWalker) 
	{
		if (!isConsistent(vWalker)) 
		{
			rval = false;
		} 
		else 
		{
			m->advance(vWalker);
		}
	}
	
	DCELFace* fWalker = m->firstFace();
	while(rval && fWalker) 
	{
		if (!isConsistent(fWalker)) 
		{
			rval = false;
		} 
		else 
		{
			m->advance(fWalker);
		}
	}

	return rval;
}


//--------------------------------------------------------------------
// Load a DCELMesh from the OFF file.
//--------------------------------------------------------------------
bool DCELTools::loadFromOFF(const char *filename, DCELMesh* m)
{
	bool rval = false;

	// Open the OFF file.
	ifstream ifs(filename);

	// Initialize the DCELMesh to be loaded.
	m->clear();

	// When the OFF file is successfully opened.
	if (ifs.is_open()) 
	{
		string inputLine;
		
		// Whether the DCELMesh is Manifold.
		bool isManifold = true;  
		
	//--------------------------------------------------------------------------------
	// Reading File Header.
	//--------------------------------------------------------------------------------
		//::getline(ifs, inputLine);
		ifs >> inputLine;
		if(inputLine == "OFF") 
		{			
	//--------------------------------------------------------------------------------
	// Reading the Number of the Objects.
	//--------------------------------------------------------------------------------	
			int numVertices = 0;
			int numFaces = 0;
			int numEdges;
			
			// numEdges is present but ignored in this format
			ifs >> numVertices >> numFaces >> numEdges; 
	
			if(numVertices>0 && numFaces>0) 
			{
				DCELVertex* tempVertex = NULL;
				DCELHalfEdge* tempHalfEdge = NULL;
				DCELFace* tempFace = NULL;
				
				// Temporary array to give us indexed access to 
				// the vertices during the building.
				DCELVertex** vertices = new DCELVertex*[numVertices];
	//--------------------------------------------------------------------------------
	// Reading ALL the Vertices.
	//--------------------------------------------------------------------------------
				for (int i = 0; i < numVertices; i++) 
				{
					tempVertex = new DCELVertex();
					ifs >> tempVertex->coords.x 
					    >> tempVertex->coords.y 
					    >> tempVertex->coords.z;
					
					vertices[i] = tempVertex;			
					m->insert(tempVertex);
				}
	//--------------------------------------------------------------------------------
	// Reading ALL the Faces.
	//--------------------------------------------------------------------------------
				int vIndex;
				HalfEdgeList* pList;
				
				for (int i = 0; i < numFaces; i++) 
				{
					// Number of edges/vertices in this polygon.
					ifs >> numEdges; 
					
					// First HalfEdge of this DCELFace.
					tempFace = new DCELFace();
					m->insert(tempFace);					
					tempHalfEdge = new DCELHalfEdge();
					m->insert(tempHalfEdge);				
					tempFace->edge = tempHalfEdge;
					tempHalfEdge->face = tempFace;
					
					ifs >> vIndex;					
					tempHalfEdge->origin = vertices[vIndex];
					vertices[vIndex]->leaving = tempHalfEdge;
					
					pList = (HalfEdgeList*)vertices[vIndex]->auxData;
					HalfEdgeList::addToList(pList, tempHalfEdge);		
					vertices[vIndex]->auxData = pList;
					
					// Remaining HalfEdges.
					for(int j = 1; j < numEdges; j++) 
					{
						// Set the "next pointer" of the previous HalfEdge.
						tempHalfEdge->next = new DCELHalfEdge();
						tempHalfEdge = tempHalfEdge->next;		
						
						m->insert(tempHalfEdge);
						tempHalfEdge->face = tempFace;
						
						ifs >> vIndex;
						tempHalfEdge->origin = vertices[vIndex];
						vertices[vIndex]->leaving = tempHalfEdge;
						
						pList = (HalfEdgeList*)vertices[vIndex]->auxData;
						HalfEdgeList::addToList(pList, tempHalfEdge);
						vertices[vIndex]->auxData = pList;
					}
					tempHalfEdge->next = tempFace->edge;
				}
	//--------------------------------------------------------------------------------
	// Finding every HalfEdge*'s twin HalfEdge.
	//--------------------------------------------------------------------------------
				HalfEdgeList* listWalker;
				DCELHalfEdge* eWalker = m->firstHalfEdge();
				DCELHalfEdge* newTwin;				
				int numFound;
				
				while (isManifold && (eWalker != NULL)) 
				{
					// Haven't matched this half-edge yet.
					if (eWalker->twin == NULL) 
					{ 
						pList = (HalfEdgeList*)eWalker->next->
						         origin->auxData;
						listWalker = pList;
						
						numFound = 0;
						newTwin = NULL;					
						while(listWalker) 
						{
							if(listWalker->edge->next->origin == 
							    eWalker->origin) 
							{
								newTwin = listWalker->edge;
								numFound++;
							}
							
							listWalker = listWalker->next;
						}
						
						// Must be a boundary edge.
						if (numFound == 0) 
						{ 
							newTwin = new DCELHalfEdge();
							m->insert(newTwin);
							
							newTwin->twin = eWalker;
							eWalker->twin = newTwin;
							
							newTwin->face = m->getInfiniteFace();
							newTwin->origin = eWalker->next->origin;
						} 
						else if (numFound == 1) 
						{
							HalfEdgeList::removeFromList(pList,newTwin);
							eWalker->next->origin->auxData = pList;
							
							eWalker->twin = newTwin;
							newTwin->twin = eWalker;
						} 
						else  // Two or more edges originate from this list. 
						{  
							isManifold = false;
						}
						
						pList = (HalfEdgeList*)eWalker->origin->auxData;
						HalfEdgeList::removeFromList(pList, eWalker);
						eWalker->origin->auxData = pList;
					}
					m->advance(eWalker);
				}
	//--------------------------------------------------------------------------------
	// Even if we've decided that the mesh is non-manifold, 
	// we need to clean up the auxData pointers before we clear the mesh.
	// (If the mesh is manifold, this is easy. 
	// If not, we almost definitely have auxData pointers to clear)
	//--------------------------------------------------------------------------------
				for(DCELVertex* vWalker=m->firstVertex();vWalker;
				     m->advance(vWalker)) 
				{
					// No linked lists should be left.
					if (vWalker->auxData) 
					{ 
						// If one is found, this was a bad mesh.
						isManifold = false; 
						
						// Clean up to prevent memory leaks from bad meshes.
						pList = (HalfEdgeList*)vWalker->auxData; 
						HalfEdgeList::deleteList(pList);
						vWalker->auxData = NULL;
					}
				}
	//--------------------------------------------------------------------------------
	// Set the "next pointer" for every Boundary HalfEdge.
	// No point in doing this if we've decided it's non-manifold already.
	//--------------------------------------------------------------------------------
				if (isManifold) 
				{ 
					DCELHalfEdge* previous = NULL;
					for(eWalker = m->firstHalfEdge();eWalker; 
					     m->advance(eWalker)) 
					{
						if (eWalker->face == m->getInfiniteFace()) 
						{
							previous = eWalker->twin->next->twin;
							
						// Note, this is dangerous if the file is very ill-formed.
						// This could be an infinite loop.
							while(previous->next) 
							{ 
								previous = previous->next->twin;
							}
							previous->next = eWalker;
						}
					}
				}
	//--------------------------------------------------------------------------------		
	//--------------------------------------------------------------------------------		
				delete[] vertices;

				if (isManifold) 
				{
					rval = true;
					m->updateAll();
				} 
				else 
				{
					m->clear();
				}
			}
		}
		ifs.close();
	}

	return rval;
}

//--------------------------------------------------------------------
// Store the DCELMesh to an OFF file.
//--------------------------------------------------------------------
bool DCELTools::storeToOFF(char *filename, DCELMesh* m)
{
	bool rval = false;

	// Open the OFF file. 
	ofstream ofs(filename);

	// When the OFF file is successfully opened.
	if(ofs.is_open()) 
	{
		unsigned int pointCounter = m->getNumVertices();		
		int numFaces = m->getNumFaces();
		int numEdges = m->getNumHalfEdges()/2;
		
		
		// Create a temporary index array to associate with vertices through
		// their auxData pointers. These will be used as IDs during the write
		// process. The existing pointers are stored in case they were in use
		// before the save, and are restored at the end of this function.		
		void** pointerBuffer = new void*[pointCounter];
		unsigned int* indexBuffer = new unsigned int[pointCounter];
		pointCounter = 0;
		DCELVertex* walkerV;
		
		for (walkerV = m->firstVertex(); walkerV; m->advance(walkerV)) 
		{
			pointerBuffer[pointCounter] = walkerV->auxData;
			indexBuffer[pointCounter] = pointCounter;
			walkerV->auxData = &(indexBuffer[pointCounter]);
			
			pointCounter++;
		}
		
		
	//--------------------------------------------------------------------------------
	// Writing File Header.
	//--------------------------------------------------------------------------------
		ofs << "OFF" << endl;
		ofs << pointCounter << " " << numFaces << " " << numEdges << endl;
	//--------------------------------------------------------------------------------
	// Writing ALL the Vertices.
	//--------------------------------------------------------------------------------
		for (walkerV = m->firstVertex(); walkerV; m->advance(walkerV)) 
		{
			ofs << walkerV->coords.x << " " 
			    << walkerV->coords.y << " " 
			    << walkerV->coords.z;
			ofs << endl;
		}		
	//--------------------------------------------------------------------------------
	// Writing ALL the Faces.
	//--------------------------------------------------------------------------------
		// For each poly, count the number of edges it has, then
		// go around and actually output the IDs of the vertices.
		int polySize=0;	
		
		DCELHalfEdge* walkerE;
		
		for(DCELFace* walkerF = m->firstFace(); walkerF; m->advance(walkerF)) 
		{
			walkerE = walkerF->edge;
			
			// Calculate the number of the Edges.
			polySize = walkerF->getEdgeCount();			
			
			//--------------------------------------------
			// Another method to calculate the polySize.
			//--------------------------------------------
			/*polySize++;
			walkerE = walkerE->next;
			while (walkerE != walkerF->edge) 
			{
				polySize++;
				walkerE = walkerE->next;
			}
			walkerE = walkerF->edge;
			*/	
			
			// Start writing Vertex's ID.
			ofs << polySize << " " 
			    << *((unsigned int*)(walkerE->origin->auxData));
			
			walkerE = walkerE->next;
			while (walkerE != walkerF->edge) 
			{
				ofs << " " << *((unsigned int*)(walkerE->origin->auxData));
				walkerE = walkerE->next;
			}
			
			ofs << endl;
		}
	//--------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------
		// Set the auxData pointers back.
		pointCounter = 0;
		for (walkerV = m->firstVertex(); walkerV ; m->advance(walkerV))
		{
			walkerV->auxData = pointerBuffer[pointCounter];
			pointCounter++;
		}
		delete[] indexBuffer;
		delete[] pointerBuffer;
		
		ofs.close();
		rval = true;
	}

	return rval;
}