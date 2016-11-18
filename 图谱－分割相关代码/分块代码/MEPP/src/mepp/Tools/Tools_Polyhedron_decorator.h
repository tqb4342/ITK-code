// ======================================================================
//
// Copyright (c) 2002 SurfLab of CISE of University of Florida
//
// File          : libs/src/cgalExt/Polyhedron_decorator.h
// Description   : Provides auxiliary functions to examine and modify a 
//                 polyhedron
// Creation_date : 28 Jan 2002
// Author(s)     : Le-Jeng Shiue <sle-jeng@cise.ufl.edu>
//
// ======================================================================

// $Id: Polyhedron_decorator.h,v 1.4 2004/05/15 23:27:06 sle-jeng Exp $

#ifndef _POLYHEDRON_DECORATOR_H_01282002
#define _POLYHEDRON_DECORATOR_H_01282002

template <class _Poly>
class Polyhedron_decorator {
  typedef _Poly                                        Polyhedron;

  typedef typename Polyhedron::Traits                  Traits;
  typedef typename Traits::Kernel                      Kernel;

  typedef typename Polyhedron::Halfedge_data_structure HDS;
  typedef typename Polyhedron::Vertex                  Vertex;
  typedef typename Polyhedron::Halfedge                Halfedge;
  typedef typename Polyhedron::Facet                   Facet;
  
  typedef typename Polyhedron::Vertex_handle           Vertex_handle;
  typedef typename Polyhedron::Halfedge_handle         Halfedge_handle;
  typedef typename Polyhedron::Facet_handle            Facet_handle;

  typedef typename Polyhedron::Vertex_iterator         Vertex_iterator;
  typedef typename Polyhedron::Halfedge_iterator       Halfedge_iterator;
  typedef typename Polyhedron::Edge_iterator           Edge_iterator;
  typedef typename Polyhedron::Facet_iterator          Facet_iterator;

  typedef typename Polyhedron::Halfedge_around_facet_circulator  
                                            Halfedge_around_facet_circulator;
  typedef typename Polyhedron::Halfedge_around_vertex_circulator 
                                            Halfedge_around_vertex_circulator;

  typedef typename Polyhedron::Point_3                 Point;
  typedef typename Kernel::FT                          FT;
public:
  /** Insert a new vertex into an helfedge h (a--b)

      Precondition:
           h
      a <-----> b
          -h
      h is the halfedge connecting vertex a to b
      -h is the oppsite halfedge connecting b to a

      Postcondition:
           h         r
      a <-----> V <-----> b  
          -h         -r
      V is the return vertex whose geometry is UNDEFINED.
      -r is the return halfedge that is pointing to V 
  */
  static Vertex* insert_vertex(Polyhedron& p, Halfedge* h) { 
    return insert_vertex(p, Halfedge_handle(h)).ptr();
  }
  static Vertex* insert_vertex(Polyhedron& p, Vertex* a, Vertex* b) {
    return insert_vertex(p, Vertex_handle(a), Vertex_handle(b)).ptr();
  }
  static Vertex_handle insert_vertex(Polyhedron& p, Halfedge_handle h) {
    return insert_vertex_return_edge(p, h)->vertex();
  }
  static Vertex_handle insert_vertex(Polyhedron& p,
				     Vertex_handle a, Vertex_handle b) {
    return insert_vertex_return_edge(p, a, b)->vertex();
  }
  static Halfedge* insert_vertex_return_edge(Polyhedron& p, Halfedge* h) { 
    return insert_vertex_return_edge(p, Halfedge_handle(h)).ptr();
  }
  static Halfedge* insert_vertex_return_edge(Polyhedron& p, 
					     Vertex* a, Vertex* b) {
    return insert_vertex_return_edge(p, Vertex_handle(a), 
				     Vertex_handle(b)).ptr();
  }
  static inline Halfedge_handle insert_vertex_return_edge(Polyhedron& p, 
							  Halfedge_handle h);
  static inline Halfedge_handle insert_vertex_return_edge(Polyhedron& p, 
							  Vertex_handle a, 
							  Vertex_handle b);

  /** Insert a new edge (two halfwdges) between the two vertices
      
      Precondition:
      vertex a and b are in the SAME facet and do NOT connect to each other 

      Postcondition:
             H
      a <----------> b
      H is the return helfedge connecting vertex a to b.      
  */
  static Halfedge* insert_edge(Polyhedron& p, Vertex* a, Vertex* b) {
    return insert_edge(Vertex_handle(a), Vertex_handle(b)).ptr();
  }
  static Halfedge_handle insert_edge(Polyhedron& p, 
				     Halfedge_handle a, 
				     Halfedge_handle b) {
    return p.split_facet(a, b);
  }
  static inline Halfedge_handle insert_edge(Polyhedron& p, 
					    Vertex_handle a, 
					    Vertex_handle b);

  /** Set the vertex of index vidx to the new position to the new 
      position (x,y,z)

      Precondition:
      0 <= vidx < p.size_of_vertices() 
      
      Postcondition:
      If failed procondition, do nothing.
      The new vertex of index vidx has the new position (x,y,z)
  */
  static void set_vertex_position(Polyhedron& p, int vidx, FT x, FT y, FT z) {
    if (vidx >= 0 && vidx < p.size_of_vertices()) {
      Vertex_iterator vitr = p.vertices_begin();
      for (int i = 0; i < vidx; i++) ++vitr;
      vitr->point() = Point(x,y,z);
    }
  }

protected:
private:

//@}
};

template <class _Poly> 
typename Polyhedron_decorator<_Poly>::Halfedge_handle 
Polyhedron_decorator<_Poly>::insert_vertex_return_edge(Polyhedron& p,
						    Halfedge_handle h) {
  Halfedge_handle hopp = h->opposite();
  Halfedge_handle r = p.split_vertex(hopp->prev(), h);
  if (!h->is_border())
    ((typename HDS::Face_handle) h->facet())->set_halfedge(r);
  if (!hopp->is_border())
    ((typename HDS::Face_handle) hopp->facet())->set_halfedge(hopp);
  return r->opposite();
}

template <class _Poly> 
typename Polyhedron_decorator<_Poly>::Halfedge_handle 
Polyhedron_decorator<_Poly>::insert_vertex_return_edge(Polyhedron& p,
						    Vertex_handle a, 
						    Vertex_handle b) {
  Halfedge_around_vertex_circulator a_cir_begin = a->vertex_begin();
  Halfedge_around_vertex_circulator a_cir = a_cir_begin;
  do {
    if (a_cir->opposite()->vertex() == b)
      return insert_vertex_return_edge(p, a_cir->opposite());
  } while (++a_cir != a_cir_begin);
  CGAL_precondition_msg(0, "vertex a and b must be incident to each other");  
  return Halfedge_handle(NULL);
}


template <class _Poly> 
typename Polyhedron_decorator<_Poly>::Halfedge_handle 
Polyhedron_decorator<_Poly>::insert_edge(Polyhedron& p,
				      Vertex_handle a, 
				      Vertex_handle b) {
  Halfedge_around_vertex_circulator a_cir_begin = a->vertex_begin();
  Halfedge_around_vertex_circulator a_cir = a_cir_begin;
  Halfedge_around_vertex_circulator b_cir_begin = b->vertex_begin();
  Halfedge_around_vertex_circulator b_cir = b_cir_begin;
  do {
    do {
      if (a_cir->facet() == b_cir->facet())
	return p.split_facet(a_cir, b_cir);
    } while (++b_cir != b_cir_begin);
  } while (++a_cir != a_cir_begin);
  CGAL_precondition_msg(0, "vertex a and b must share the same face");  
  return Halfedge_handle(NULL);
}

#endif //_POLYHEDRON_DECORATOR_H_01282002
