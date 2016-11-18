#ifndef BOOLEAN_OPERATIONS_DEFINITIONS_H
#define BOOLEAN_OPERATIONS_DEFINITIONS_H

/*!
 * \file Boolean_Operations_Definitions.h
 * \brief Definitions and functions for convertion between exact and non-exact numbers
 * \author Cyril Leconte
 */

#include "../../../../mepp/Polyhedron/polyhedron.h"
#include <CGAL/Gmpq.h>
#include <CGAL/Lazy_exact_nt.h>

#include <mepp_config.h>

/*!
 * \def BOOLEAN_OPERATIONS_DEBUG
 * \brief Enables computation time measuring
 */

#define BOOLEAN_OPERATIONS_DEBUG

/*!
 * \enum Bool_Op
 * \brief The three Boolean operations
 */
enum Bool_Op {UNION, INTER, MINUS};

/*!
 * \typedef num_type
 * \brief exact number type
 */
typedef CGAL::Lazy_exact_nt<CGAL::Gmpq>		num_type;

/*!
 * \typedef Exact_Kernel
 * \brief Kernel using exact number type
 */
typedef CGAL::Simple_cartesian<num_type>	Exact_Kernel;

/*!
 * \typedef Vector_exact
 * \brief 3d vector using exact number type
 */
typedef CGAL::Vector_3<Exact_Kernel>		Vector_exact;

/*!
 * \typedef Point3d_exact
 * \brief 3d point using exact number type
 */
typedef CGAL::Point_3<Exact_Kernel>			Point3d_exact;

/**
 * \fn inline Point3d_exact point_to_exact(Point3d &p)
 * \brief Convertion from a Point3d (double) to a Point3d_exact (exact)
 * \param p : The Point3d 
 * \return The conversion in Point3d_exact.
 */
inline Point3d_exact point_to_exact(Point3d &p)
{
	return Point3d_exact(p.x(),p.y(),p.z());
}

/**
 * \fn inline Point3d point_to_double(Point3d_exact &pe)
 * \brief Convertion from a Point3d_exact (exact) to a Point3d (double)
 *
 * \param pe : The Point3d_exact
 * \return The conversion in Point3d (double).
 */
inline Point3d point_to_double(Point3d_exact &pe)
{
	return Point3d(to_double(pe.x()),to_double(pe.y()),to_double(pe.z()));
}

/**
 * \fn inline Vector_exact Compute_Normal_direction(Halfedge_handle &he)
 * \brief Compute a vector in the same direction as the normal vector
 *
 * \param he : A Halfedge incident to the facet
 * \return The normal direction (exact).
 */
inline Vector_exact Compute_Normal_direction(Halfedge_handle he)   // MT: suppression référence
{
	return CGAL::cross_product(	point_to_exact(he->next()->vertex()->point())			- point_to_exact(he->vertex()->point()),
								point_to_exact(he->next()->next()->vertex()->point())	- point_to_exact(he->vertex()->point()));
}
	
#ifdef BOOLEAN_OPERATIONS_DEBUG

/**
 * \fn inline double tr(double &n)
 * \brief Truncate a number to 1/1000
 *        (only if BOOLEAN_OPERATIONS_DEBUG is enable)
 * \param n : The input number in double
 * \return The truncation in double.
 */
inline double tr(double &n)
{
	return floor(n*1000)/1000;
}
#endif // BOOLEAN_OPERATIONS_DEBUG
	
#endif // BOOLEAN_OPERATIONS_DEFINITIONS_H
