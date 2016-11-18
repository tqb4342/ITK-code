#ifndef Compression_Valence_ITEMS_H
#define Compression_Valence_ITEMS_H

#include <mepp_config.h>
#ifdef BUILD_component_Compression_Valence

#include "../../../../mepp/Polyhedron/polyhedron_shared_items.h"

template <class Refs, class T, class P, class Norm, class Plane>

/**
 \class	Compression_Valence_Facet

 \brief	Compression valence facet. 

 */

class Compression_Valence_Facet : virtual public MEPP_Common_Facet<Refs, T, Norm>
{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Compression_Valence_Facet::Compression_Valence_Facet()
		///
		/// \brief	Default constructor.
		///
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Compression_Valence_Facet() {}

		int Facet_Flag;
		//int Patch_Index;
		int Component_Number;

};


template <class Refs, class Tprev, class Tvertex, class Tface, class Norm>

/**
 \class	Compression_Valence_Halfedge

 \brief	Compression valence halfedge. 

 */

class Compression_Valence_Halfedge : virtual public MEPP_Common_Halfedge<Refs,Tprev,Tvertex,Tface,Norm>
{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Compression_Valence_Halfedge::Compression_Valence_Halfedge()
		///
		/// \brief	Default constructor.
		///
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Compression_Valence_Halfedge() {}
		int Component_Number;
};


template <class Refs, class T, class P, class Norm>

/**
 \class	Compression_Valence_Vertex

 \brief	Compression valence vertex. 

*/

class Compression_Valence_Vertex : virtual public MEPP_Common_Vertex<Refs, T, P, Norm>
{	
	protected:
		
		double Spherical[3];		

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Compression_Valence_Vertex::Compression_Valence_Vertex()
		///
		/// \brief	Default constructor.
		///
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Compression_Valence_Vertex()
		{
			Seed_Edge = -1;
			Region_Number = -1;
			Removal_Order = -1;
			Valid_Vertex = true;

			JCW_Move_Error[0] = 0;
			JCW_Move_Error[1] = 0;
			JCW_Move_Error[2] = 0;
		}

		// float color_float(int index) { return m_color_float[index]; };
		// void color_float(float color0, float color1, float color2) {m_color_float[0] = color0;
		// m_color_float[1] = color1; m_color_float[2] = color2;}; 
		
		int color_int(int index) { return m_color_int[index]; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Compression_Valence_Vertex::color_int(int color0, int color1, int color2)
		///
		/// \brief	Color int.
		///
		/// \param	color0	The color 0.
		/// \param	color1	The first color.
		/// \param	color2	The second color.
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void color_int(int color0, int color1, int color2) { m_color_int[0] = color0; m_color_int[1] = color1; m_color_int[2] = color2; };

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Compression_Valence_Vertex::Spherical_Coordinates(const double * S)
		///
		/// \brief	Spherical coordinates.
		///
		/// \param	S	The.
		////////////////////////////////////////////////////////////////////////////////////////////////////

		void Spherical_Coordinates(const double * S)
		{ 
			Spherical[0] = S[0];
			Spherical[1] = S[1]; 
			Spherical[2] = S[2]; 
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	double Compression_Valence_Vertex::Spherical_Coordinates(const int & index)
		///
		/// \brief	Spherical coordinates.
		///
		/// \param	index	Zero-based index of the.
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////

		double Spherical_Coordinates(const int & index)
		{
			return Spherical[index];
		}
		
		
		//float m_color_float[3];
		int m_color_int[3];

		int JCW_Move_Error[3];
		
		double Watermarked_Position[3];

		int Vertex_Flag;
		int Vertex_Number;
		int Vertex_Color_Index;
		
		//For valence_driven
		int Vertex_Sign;
		int Q_Index;
		int Seed_Edge;

		int Component_Number;

		//JCW
		int Region_Number;
		int Removal_Order;
		bool Valid_Vertex;
};


template <class kernel, class items>

/**
 \class	Compression_Valence_Polyhedron

 \brief	Compression valence polyhedron. 

  */

class Compression_Valence_Polyhedron : virtual public MEPP_Common_Polyhedron<kernel,items>
{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Compression_Valence_Polyhedron::Compression_Valence_Polyhedron()
		///
		/// \brief	Default constructor.
		///
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Compression_Valence_Polyhedron() {}
};

#endif

#endif // Compression_Valence_ITEMS_H
