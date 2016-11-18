	///////////////////////////////////////////////////////////////////////////
// Author: Guillaume Lavou�
// Year: 2008
// INSA-Lyon, LIRIS UMR 5205, M2DISCO.
//
//According to: Variational Shape Approximation
//		David Cohen-Steiner, Pierre Alliez and Mathieu Desbrun, SIGGRAPH '2004. 
///////////////////////////////////////////////////////////////////////////
#include <mepp_config.h>
#ifdef BUILD_component_VSA

#ifdef _MSC_VER
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#endif

#include "VSA_Component.h"

#include<set>
#include<map>
#include<list>
#include<vector>
#include<stack>

 typedef struct
  {
	Facet_iterator Facet;
	
	double DistanceLLoyd;//distance for the LLoyd algorithm
	
	double PossibleCluster;//cluster for the LLoyd algorithm

  }
  FacetToIntegrate;

   typedef struct
  {
	Vertex_iterator Vertex;
	std::vector<int> TabAdjAnch;


  }
  AnchorVertex;

  double AreaFacetTriangleSeg(Facet_iterator &f)
	{
		Halfedge_around_facet_circulator pHalfedge = f->facet_begin();
		Point3d P = pHalfedge->vertex()->point();
		Point3d Q = pHalfedge->next()->vertex()->point();
		Point3d R = pHalfedge->next()->next()->vertex()->point();

		Vector PQ=Q-P;
                //Vector PR=R-P; // MT
		Vector QR=R-Q;


		Vector normal	=	CGAL::cross_product(PQ,QR);
		double area=0.5*sqrt(normal*normal);

		return area;

	}

  void VSA_Component::Init(int NbProxy)
	{
//------------------------------------------------------------------------------------
// I. Get the Seg Info from file "seg.csv".
//    "seg.csv" is from the output of *MEPP*.
//------------------------------------------------------------------------------------	
	ifstream ifs2( "shapeVariation_Vertex.csv" );	
	
	// When the OFF file is successfully opened.
	if( ifs2.is_open() ) 
	{
		ifs2 >> numOfVertex;
		vertexVariation = new double[numOfVertex];
		
		double variation;
		for( int i=0; i<numOfVertex; i++ )
		{
			ifs2 >> variation;
		    vertexVariation[i] = variation;	
		}			
	}
	else
	{
		printf("\n\nThe file \"shapeVariation_Vertex.csv\" can not be read correctly!!!\n\n");
		ifs2.close();	
	}
	ifs2.close();
	
	//for( int i=0; i<numOfVertex; i++ )
	//{
		//printf("vertexVariation[%d]: %f\n", i, vertexVariation[i]);
	//}	
	// Tag all Vertices.
	    int counter2 = 0;
	    Vertex_iterator pVert = m_Poly->vertices_begin();
		for(;pVert	!= m_Poly->vertices_end();pVert++)
		{
			pVert->tag() = counter2;
			//cout<< pFacet->tag() << endl;
			//printf("ID:\t%d\n", pFacet->m_normal);
			//Vector normal-tmp;
			//pFacet->normal() = faceVariation[counter];
			counter2++;
		}
	
	
//------------------------------------------------------------------------------------
// I. Get the Seg Info from file "seg.csv".
//    "seg.csv" is from the output of *MEPP*.
//------------------------------------------------------------------------------------	
	ifstream ifs( "shapeVariation_Face.csv" );	
	
	
	int numOfFace;
	// When the OFF file is successfully opened.
	if( ifs.is_open() ) 
	{
		ifs >> numOfFace;
		faceVariation = new double[numOfFace];
		
		double variation;
		for( int i=0; i<numOfFace; i++ )
		{
			ifs >> variation;
		    faceVariation[i] = variation;	
		}			
	}
	else
	{
		printf("\n\nThe file \"shapeVariation_Face.csv\" can not be read correctly!!!\n\n");
		ifs.close();		    
	}
	ifs.close();
	
	//for( int i=0; i<numOfFace; i++ )
	//{
		//printf("faceVariation[%d]: %f\n", i, faceVariation[i]);
	//}
	
	
		////Creation of the initial proxies by random seed triangle picking 
		m_Table_Proxy.clear();
        
		
		
		// Tag all faces.
	    int counter = 0;
	    Facet_iterator pFacet = m_Poly->facets_begin();
		for(;pFacet	!= m_Poly->facets_end();pFacet++)
		{
			pFacet->tag() = counter;
			//cout<< pFacet->tag() << endl;
			//printf("ID:\t%d\n", pFacet->m_normal);
			//Vector normal-tmp;
			//pFacet->normal() = faceVariation[counter];
			counter++;
		}
		
		
		
		int NbFacet=m_Poly->size_of_facets();
	    double min, max;
	    min = faceVariation[0];
	    max = faceVariation[0];
	    for( int i=1; i<NbFacet; i++ )
	    {
			if( faceVariation[i]<min )
			{
				min = faceVariation[i];				
			}	
            if( faceVariation[i]>max )
			{
				max = faceVariation[i];				
			}			
		}
		printf("min, max:\t%f, %f\n", min, max);
		
		
		
		
		m_NbProxy=NbProxy;
		//int NbFacet=m_Poly->size_of_facets();
		int offset=NbFacet/NbProxy;
		int i=0; 
		for(Facet_iterator	pface	=	m_Poly->facets_begin();
				pface	!= m_Poly->facets_end();
				pface++)
		{
			int ID = pface->tag(); 

			//if(i%offset==0)///this triangle is chosen
			if( faceVariation[ID] == min || faceVariation[ID] == max )
			{
				//a proxy is created
				Proxy NewProxy;				
				printf("Seed ID:\t%d\t%f\n", ID, faceVariation[ID]);
				NewProxy.Normal=faceVariation[ID];

				NewProxy.Seed=pface;
				///the proxy is added
				m_Table_Proxy.push_back(NewProxy);
			}

			pface->LabelVSA=-1;
			i++;
		}

		m_Poly->NbFaceLabel=m_NbProxy;
	}

	struct CompFacet
	{
	bool operator()(FacetToIntegrate f1, FacetToIntegrate f2) const
	{
		
		return(f1.DistanceLLoyd<f2.DistanceLLoyd);

	}
	};


	double VSA_Component::DistorsionError(Facet_iterator f,Proxy p)
	{
		//Vector v=f->normal()-p.Normal;
		//double nrm=v*v;
		//double area=AreaFacetTriangleSeg(f);
		//return nrm*area;
		
		
		int ID = f->tag(); 
		//printf("faceVariation[%d]: %f-%f = %f\n", ID, faceVariation[ID], p.Normal, ( faceVariation[ID]-p.Normal )*( faceVariation[ID]-p.Normal ));
		return fabs( faceVariation[ID]-p.Normal ); 
	}


VSA_Component::VSA_Component(Viewer* v, PolyhedronPtr p):mepp_component(v, p)
{
	int i=0;
	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.515600;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.531300;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.546900;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.562500;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.578100;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.593800;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.609400;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.625000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.640600;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.656300;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.671900;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.687500;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.703100;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.718800;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.734400;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.750000;
	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.765600;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.781300;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.796900;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.812500;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.828100;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.843800;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.859400;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.875000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.890600;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.906300;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.921900;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.937500;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.953100;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.968800;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.984400;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	1.000000;
	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.015600;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.031300;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.046900;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.062500;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.078100;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.093800;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.109400;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.125000;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.140600;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.156300;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.171900;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.187500;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.203100;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.218800;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.234400;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.250000;	LUT_Seg[i++]=	1.000000;
	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.265600;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.281300;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.296900;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.312500;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.328100;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.343800;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.359400;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.375000;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.390600;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.406300;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.421900;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.437500;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.453100;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.468800;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.484400;	LUT_Seg[i++]=	1.000000;
	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.500000;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.515600;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.531300;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.546900;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.562500;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.578100;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.593800;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.609400;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.625000;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.640600;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.656300;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.671900;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.687500;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.703100;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.718800;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.734400;	LUT_Seg[i++]=	1.000000;
	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.750000;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.765600;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.781300;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.796900;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.812500;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.828100;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.843800;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.859400;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.875000;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.890600;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.906300;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.921900;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.937500;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.953100;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.968800;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.984400;	LUT_Seg[i++]=	1.000000;
	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.015600;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	1.000000;		LUT_Seg[i++]=	0.031300;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.984400;		LUT_Seg[i++]=	0.046900;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.968800;		LUT_Seg[i++]=	0.062500;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.953100;		LUT_Seg[i++]=	0.078100;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.937500;		LUT_Seg[i++]=	0.093800;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.921900;		LUT_Seg[i++]=	0.109400;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.906300;		LUT_Seg[i++]=	0.125000;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.890600;		LUT_Seg[i++]=	0.140600;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.875000;		LUT_Seg[i++]=	0.156300;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.859400;		LUT_Seg[i++]=	0.171900;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.843800;		LUT_Seg[i++]=	0.187500;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.828100;		LUT_Seg[i++]=	0.203100;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.812500;		LUT_Seg[i++]=	0.218800;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.796900;		LUT_Seg[i++]=	0.234400;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.781300;
	LUT_Seg[i++]=	0.250000;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.765600;		LUT_Seg[i++]=	0.265600;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.750000;		LUT_Seg[i++]=	0.281300;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.734400;		LUT_Seg[i++]=	0.296900;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.718800;		LUT_Seg[i++]=	0.312500;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.703100;		LUT_Seg[i++]=	0.328100;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.687500;		LUT_Seg[i++]=	0.343800;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.671900;		LUT_Seg[i++]=	0.359400;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.656300;		LUT_Seg[i++]=	0.375000;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.640600;		LUT_Seg[i++]=	0.390600;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.625000;		LUT_Seg[i++]=	0.406300;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.609400;		LUT_Seg[i++]=	0.421900;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.593800;		LUT_Seg[i++]=	0.437500;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.578100;		LUT_Seg[i++]=	0.453100;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.562500;		LUT_Seg[i++]=	0.468800;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.546900;		LUT_Seg[i++]=	0.484400;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.531300;
	LUT_Seg[i++]=	0.500000;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.515600;		LUT_Seg[i++]=	0.515600;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.500000;		LUT_Seg[i++]=	0.531300;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.484400;		LUT_Seg[i++]=	0.546900;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.468800;		LUT_Seg[i++]=	0.562500;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.453100;		LUT_Seg[i++]=	0.578100;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.437500;		LUT_Seg[i++]=	0.593800;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.421900;		LUT_Seg[i++]=	0.609400;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.406300;		LUT_Seg[i++]=	0.625000;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.390600;		LUT_Seg[i++]=	0.640600;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.375000;		LUT_Seg[i++]=	0.656300;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.359400;		LUT_Seg[i++]=	0.671900;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.343800;		LUT_Seg[i++]=	0.687500;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.328100;		LUT_Seg[i++]=	0.703100;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.312500;		LUT_Seg[i++]=	0.718800;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.296900;		LUT_Seg[i++]=	0.734400;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.281300;
	LUT_Seg[i++]=	0.750000;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.265600;		LUT_Seg[i++]=	0.765600;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.250000;		LUT_Seg[i++]=	0.781300;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.234400;		LUT_Seg[i++]=	0.796900;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.218800;		LUT_Seg[i++]=	0.812500;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.203100;		LUT_Seg[i++]=	0.828100;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.187500;		LUT_Seg[i++]=	0.843800;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.171900;		LUT_Seg[i++]=	0.859400;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.156300;		LUT_Seg[i++]=	0.875000;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.140600;		LUT_Seg[i++]=	0.890600;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.125000;		LUT_Seg[i++]=	0.906300;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.109400;		LUT_Seg[i++]=	0.921900;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.093800;		LUT_Seg[i++]=	0.937500;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.078100;		LUT_Seg[i++]=	0.953100;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.062500;		LUT_Seg[i++]=	0.968800;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.046900;		LUT_Seg[i++]=	0.984400;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.031300;
	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.015600;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.984400;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.968800;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.953100;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.937500;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.921900;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.906300;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.890600;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.875000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.859400;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.843800;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.828100;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.812500;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.796900;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.781300;	LUT_Seg[i++]=	0.000000;
	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.765600;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.750000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.734400;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.718800;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.703100;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.687500;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.671900;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.656300;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.640600;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.625000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.609400;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.593800;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.578100;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.562500;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.546900;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.531300;	LUT_Seg[i++]=	0.000000;
	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.515600;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.500000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.484400;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.468800;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.453100;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.437500;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.421900;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.406300;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.390600;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.375000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.359400;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.343800;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.328100;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.312500;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.296900;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.281300;	LUT_Seg[i++]=	0.000000;
	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.265600;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.250000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.234400;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.218800;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.203100;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.187500;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.171900;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.156300;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.140600;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.125000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.109400;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.093800;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.078100;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.062500;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.046900;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.031300;	LUT_Seg[i++]=	0.000000;
	LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.015600;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	1.000000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.984400;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.968800;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.953100;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.937500;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.921900;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.906300;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.890600;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.875000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.859400;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.843800;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.828100;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.812500;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.796900;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.781300;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;
	LUT_Seg[i++]=	0.765600;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.750000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.734400;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.718800;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.703100;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.687500;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.671900;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.656300;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.640600;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.625000;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.609400;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.593800;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.578100;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.562500;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.546900;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;		LUT_Seg[i++]=	0.531300;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;
	LUT_Seg[i++]=	0.515600;	LUT_Seg[i++]=	0.000000;	LUT_Seg[i++]=	0.000000;

	// from IHM
	displayFaceLabel=false;

	// MEPP 2
	componentName = "VSA_Component";
	init = 1;
}

void VSA_Component::Flooding()
	{
		m_Poly->NbFaceLabel=m_NbProxy;
		typedef std::multiset<FacetToIntegrate,CompFacet> ListFacet_model;
		typedef std::multiset<FacetToIntegrate,CompFacet>::iterator ListFacet_iterator;

		for(Facet_iterator	pface	=	m_Poly->facets_begin();
				pface	!= m_Poly->facets_end();
				pface++)
		{
			pface->LabelVSA=-1;
		}


		ListFacet_model ListFacet;
		for(int i=0;i<m_NbProxy;i++)//For each proxy we select triangles that could grow
		{
			m_Table_Proxy[i].TabAdj.clear();
			Facet_iterator f=m_Table_Proxy[i].Seed;
			f->LabelVSA=i;


			//we extract the three triangles
			Facet_iterator ff1, ff2, ff3;
			FacetToIntegrate f1, f2, f3;

			Halfedge_around_facet_circulator pHalfedge = f->facet_begin();

			if(!pHalfedge->opposite()->is_border())
			{
				ff1 = pHalfedge->opposite()->facet();
				f1.Facet=ff1;
				f1.PossibleCluster=i;
				f1.DistanceLLoyd=DistorsionError(f1.Facet,m_Table_Proxy[i]);
				ListFacet.insert(f1);

			}
			if(!pHalfedge->next()->opposite()->is_border())
			{
				ff2 = pHalfedge->next()->opposite()->facet();
				f2.Facet=ff2;
				f2.PossibleCluster=i;
				f2.DistanceLLoyd=DistorsionError(f2.Facet,m_Table_Proxy[i]);
				ListFacet.insert(f2);
			}


			if(!pHalfedge->next()->next()->opposite()->is_border())
			{
				ff3 = pHalfedge->next()->next()->opposite()->facet();
				f3.Facet=ff3;
				f3.PossibleCluster=i;
				f3.DistanceLLoyd=DistorsionError(f3.Facet,m_Table_Proxy[i]);
				ListFacet.insert(f3);
			}
		}

		ListFacet_iterator it;
		int counter = 0;
		for(it=ListFacet.begin();it!=ListFacet.end();)
		{
			/*if(50 == counter)
			{
				break;
			}*/
				
			if(it->Facet->LabelVSA==-1)
			{
				//printf("it->DistanceLLoyd:\t%f\n", it->DistanceLLoyd);
				
				it->Facet->LabelVSA=it->PossibleCluster;
				//we add adjacent triangles to the queue


				//we extract the three triangles
				Facet_iterator ff1, ff2, ff3;

				Halfedge_around_facet_circulator pHalfedge = it->Facet->facet_begin();


				FacetToIntegrate f1, f2, f3;
				if(!pHalfedge->opposite()->is_border())
				{
					ff1 = pHalfedge->opposite()->facet();
					if(ff1->LabelVSA==-1 )
					{
						f1.Facet=ff1;
						f1.PossibleCluster=it->PossibleCluster;
						f1.DistanceLLoyd=DistorsionError(f1.Facet,m_Table_Proxy[it->PossibleCluster]);
						ListFacet.insert(f1);
					}
				}
				if(!pHalfedge->next()->opposite()->is_border())
				{
					ff2 = pHalfedge->next()->opposite()->facet();
					if(ff2->LabelVSA==-1)
					{
						f2.Facet=ff2;
						f2.PossibleCluster=it->PossibleCluster;
						f2.DistanceLLoyd=DistorsionError(f2.Facet,m_Table_Proxy[it->PossibleCluster]);
						ListFacet.insert(f2);
					}
				}
				if(!pHalfedge->next()->next()->opposite()->is_border())
				{
					ff3 = pHalfedge->next()->next()->opposite()->facet();
					if(ff3->LabelVSA==-1)
					{
						f3.Facet=ff3;
						f3.PossibleCluster=it->PossibleCluster;
						f3.DistanceLLoyd=DistorsionError(f3.Facet,m_Table_Proxy[it->PossibleCluster]);
						ListFacet.insert(f3);
					}
				}
			}
			ListFacet.erase(it);
			it=ListFacet.begin();
			
			counter++;


		}

		//integration of the adjacency information between proxies
	/*	for(Halfedge_iterator pHalfedge	=	m_Poly->halfedges_begin();
				pHalfedge	!= m_Poly->halfedges_end();
				pHalfedge++)
		{
			if(pHalfedge->is_border()||pHalfedge->opposite()->is_border())
				continue;

			int Label1=pHalfedge->facet()->LabelVSA;
			int Label2=pHalfedge->opposite()->facet()->LabelVSA;
			if(Label1!=Label2)
			{

				bool IsFound=false;
				for(unsigned int i=0;i<m_Table_Proxy[Label1].TabAdj.size();i++)
					if(m_Table_Proxy[Label1].TabAdj[i]==Label2)
						IsFound=true;
				if(IsFound==false)
				{
					m_Table_Proxy[Label1].TabAdj.push_back(Label2);
					m_Table_Proxy[Label2].TabAdj.push_back(Label1);

				}


			}


		}*/



	}

	void VSA_Component::ProxyFitting()
	{
		double * TabNormal=new double[m_NbProxy];
		double * TabArea=new double[m_NbProxy];

		double * DistanceMin=new double[m_NbProxy];
		double * DistanceMax=new double[m_NbProxy];
        int *numFace = new int[m_NbProxy];
		
		for (int i=0;i<m_NbProxy;i++)
		{
			TabArea[i]=0;
			TabNormal[i]=0.0;
			numFace[i] = 0;
			DistanceMin[i]=100000000;
			DistanceMax[i]=0;
		}
		
		
		
		for(Facet_iterator	pface	=	m_Poly->facets_begin();
				pface	!= m_Poly->facets_end();
				pface++)
		{
			double area=AreaFacetTriangleSeg(pface);
			TabArea[pface->LabelVSA]+=area;
			
			int ID = pface->tag(); 
			TabNormal[pface->LabelVSA]=TabNormal[pface->LabelVSA]+faceVariation[ID];
			
			//TabNormal[pface->LabelVSA]=TabNormal[pface->LabelVSA]+pface->normal()*area;
            numFace[pface->LabelVSA]++;
		}

		for (int i=0;i<m_NbProxy;i++)
		{

			m_Table_Proxy[i].Normal=TabNormal[i]/numFace[i];
			m_Table_Proxy[i].Area=TabArea[i];
			m_Table_Proxy[i].TotalDistorsion=0;
			
		}



		// a new seed is assigned to each proxy
		for(Facet_iterator	pface	=	m_Poly->facets_begin();
				pface	!= m_Poly->facets_end();
				pface++)
		{
			double distance=DistorsionError(pface,m_Table_Proxy[pface->LabelVSA]);
			m_Table_Proxy[pface->LabelVSA].TotalDistorsion+=distance;
			if(distance<DistanceMin[pface->LabelVSA])
			{

				DistanceMin[pface->LabelVSA]=distance;
				m_Table_Proxy[pface->LabelVSA].Seed=pface;
			}

			//we pick the facet corresponding to the max distorsion
			if(distance>DistanceMax[pface->LabelVSA])
			{

				DistanceMax[pface->LabelVSA]=distance;
				m_Table_Proxy[pface->LabelVSA].MostDistordedFacet=pface;
			}


		}

		delete []DistanceMin;
		delete []TabNormal;
		delete []TabArea;
		delete []DistanceMax;



	}


	void VSA_Component::ProxyInsertion()
	{
		int NumProxMax=0;
		double DistorsionMax=0;

		EvalInsertion(NumProxMax,DistorsionMax);
		CreateNewProxy( NumProxMax);

	}

	void VSA_Component::EvalInsertion(int & NumProxMax,double & DistorsionMax)
	{
		for (int i=0;i<m_NbProxy;i++)
		{
			
			if(	m_Table_Proxy[i].TotalDistorsion>DistorsionMax)
			{
				NumProxMax=i;
				DistorsionMax=m_Table_Proxy[i].TotalDistorsion;

			}
		}

	}

	void VSA_Component::CreateNewProxy(int NumProxMax)
	{
		Proxy NewProxy;
		if(m_Table_Proxy[NumProxMax].MostDistordedFacet!=m_Table_Proxy[NumProxMax].Seed)
			NewProxy.Seed=m_Table_Proxy[NumProxMax].MostDistordedFacet;
		else
		{
			m_Table_Proxy[NumProxMax].MostDistordedFacet++;
			NewProxy.Seed=m_Table_Proxy[NumProxMax].MostDistordedFacet;
		}

        int ID = m_Table_Proxy[NumProxMax].MostDistordedFacet->tag(); 
        printf("Seed ID:\t%d\t%f\n", ID, faceVariation[ID]);		
		NewProxy.Normal=faceVariation[ID];
		//NewProxy.Normal=m_Table_Proxy[NumProxMax].MostDistordedFacet->normal();
		m_NbProxy++;
		m_Table_Proxy.push_back(NewProxy);
		//NewProxy.Seed->tag(15);
	}


	void VSA_Component::Variational_SegmentationIncr(PolyhedronPtr pMesh, int NbRegions, int NbIter)
	{
	    printf("NbRegions(Variational_SegmentationIncr):\t%d\n\n", NbRegions);
		
		m_Poly=pMesh;		
	
		Init(2);
		Flooding();

		for(int i=0;i<NbRegions-2;i++)
		{
			for(int j=0;j<NbIter;j++)
			{
				ProxyFitting();
				Flooding();
			}
			ProxyFitting();
			ProxyInsertion();
			Flooding();
		}
		for(int j=0;j<NbIter;j++)
		{
			ProxyFitting();
			Flooding();
		}
	}

	void VSA_Component::Variational_Segmentation(PolyhedronPtr pMesh, int NbRegions, int NbIter)
	{
	    printf("NbRegions(Variational_Segmentation):\t%d\n\n", NbRegions);
		m_Poly=pMesh;
		Init(NbRegions);
		Flooding();


		for(int i=0;i<NbIter;i++)
		{
			ProxyFitting();
			Flooding();
		}

	}

	void VSA_Component::ConstructFaceColorMap(PolyhedronPtr pMesh)
{
		
        //Vertex_iterator pVertex = NULL; // MT
        
    bool useVertexViz = false;
 
 

//----------------------------------------------------------------------------   
// Visualize the vertex's Variation.
//----------------------------------------------------------------------------   
    if( useVertexViz ) 
    {
		printf("pMesh->NbFaceLabel:\t%d\n\n", pMesh->NbFaceLabel);
	    
	    int NbVertex=numOfVertex;
	    double min, max;
	    min = vertexVariation[0];
	    max = vertexVariation[0];

	    for( int i=1; i<NbVertex; i++ )
	    {
			if( vertexVariation[i]<min )
			{
				min = vertexVariation[i];				
			}	
            if( vertexVariation[i]>max )
			{
				max = vertexVariation[i];				
			}			
		}
		printf("vertexVariation[min, max]:\t%f, %f\n", min, max);
		
		Vertex_iterator pVert	=	pMesh->vertices_begin();
		for(;pVert	!= pMesh->vertices_end();pVert++)
		{
		    
		    //printf("pFacet->LabelVSA:\t%d\t\t", pFacet->LabelVSA); 
			
			// Decide the order of the face.
			// see:
            // scm.gforge.liris.cnrs.fr/public/mepp/trunk/src/mepp/Polyhedron/polyhedron_shared_items.h
			//std::cout <<pFacet->normal() <<endl;
			
			//printf("%d\n", pFacet->LabelVSA);  
			int ID = pVert->tag();
			
			double R=(double)(vertexVariation[ID]-min)/(double)(max-min)*255.0;
			//double R=(double)(pFacet->LabelVSA)/(double)pMesh->NbFaceLabel*255.;
			int indiceLut=floor(R);

			pVert->color(LUT_Seg[3*indiceLut],LUT_Seg[3*indiceLut+1],LUT_Seg[3*indiceLut+2]);
		}
	}
	
		
		
		
//----------------------------------------------------------------------------   
// Mesh segmentation using faceVariation.
//----------------------------------------------------------------------------  	
	else
	{
	    int NbFacet=m_Poly->size_of_facets();
	    double min, max;
	    min = faceVariation[0];
	    max = faceVariation[0];
	    for( int i=1; i<NbFacet; i++ )
	    {
			if( faceVariation[i]<min )
			{
				min = faceVariation[i];				
			}	
            if( faceVariation[i]>max )
			{
				max = faceVariation[i];				
			}			
		}
		printf("faceVariation[min, max]:\t%f, %f\n", min, max); 
	
		
		
	ofstream ofs( "seg.csv" );	
	if( ofs.is_open() )
	{
		ofs << NbFacet << endl;
		
		Facet_iterator pFacet	=	pMesh->facets_begin();
		for(;pFacet	!= pMesh->facets_end();pFacet++)
		{
		    
		    //printf("pFacet->LabelVSA:\t%d\t\t", pFacet->LabelVSA); 
			
			// Decide the order of the face.
			// see:
            // scm.gforge.liris.cnrs.fr/public/mepp/trunk/src/mepp/Polyhedron/polyhedron_shared_items.h
			//std::cout <<pFacet->normal() <<endl;			
			
			//int ID = pFacet->tag();			
			//double R=(double)(faceVariation[ID]-min)/(double)(max-min)*255.0;
			
			
			
			
			ofs << pFacet->LabelVSA << endl;
			//printf("%d\n", pFacet->LabelVSA); 
			double R=(double)(pFacet->LabelVSA)/(double)pMesh->NbFaceLabel*255.;
			int indiceLut=floor(R);

			pFacet->color(LUT_Seg[3*indiceLut],LUT_Seg[3*indiceLut+1],LUT_Seg[3*indiceLut+2]);
		}
		
		
	}
	else
	{
		printf("\n\nThe Face Segmentation file \"seg.csv\" can not be read correctly!!!\n\n");
		ofs.close();	
	}
	ofs.close();
  }
	
}
#endif
