// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

/**
 * @file pylith/topology/Mesh.hh
 *
 * @brief PyLith finite-element mesh.
 *
 * Extends Sieve mesh to include coordinate system associated with
 * domain.
 */

#if !defined(pylith_topology_mesh_hh)
#define pylith_topology_mesh_hh

// Include directives ---------------------------------------------------
#define NEWPYLITHMESH 1
#include "pylith/utils/sievetypes.hh"

// Forward declarations -------------------------------------------------
namespace pylith {
  namespace topology {
    class Mesh;
  } // topology
} // pylith

namespace spatialdata {
  namespace geocoords {
    class CoordSys;
  } // geocoords
} // spatialdata

// Mesh -----------------------------------------------------------------
class pylith::topology::Mesh
{ // Mesh

// PUBLIC METHODS ///////////////////////////////////////////////////////
public :

  /** Default constructor.
   *
   * @param comm MPI communicator for mesh.
   * @param dim Dimension associated with mesh cells.
   */
  Mesh(const MPI_Comm& comm =PETSC_COMM_WORLD,
       const int dim =3); 

  /// Default destructor
  ~Mesh(void);

  /** Get Sieve mesh.
   *
   * @returns Sieve mesh.
   */
  const ALE::Obj<SieveMesh>& sieveMesh(void) const;

  /** Get Sieve mesh.
   *
   * @returns Sieve mesh.
   */
  ALE::Obj<SieveMesh>& sieveMesh(void);

  /** Set coordinate system.
   *
   * @param cs Coordinate system.
   */
  void coordsys(const spatialdata::geocoords::CoordSys* cs);

  /** Get coordinate system.
   *
   * @returns Coordinate system.
   */
  const spatialdata::geocoords::CoordSys* coordsys(void) const;

  /// Initialize the finite-element mesh.
  void initialize(void);

// PRIVATE MEMBERS //////////////////////////////////////////////////////
private :

  ALE::Obj<SieveMesh> _mesh; ///< Sieve mesh
  spatialdata::geocoords::CoordSys* _coordsys; ///< Coordinate system

// NOT IMPLEMENTED //////////////////////////////////////////////////////
private :

  Mesh(const Mesh&); ///< Not implemented
  const Mesh& operator=(const Mesh&); ///< Not implemented

}; // Mesh

#include "Mesh.icc"

#endif // pylith_topology_mesh_hh


// End of file
