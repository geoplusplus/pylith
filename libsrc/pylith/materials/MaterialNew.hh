// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
// Charles A. Williams, GNS Science
// Matthew G. Knepley, University of Chicago
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

/** @file libsrc/materials/MaterialNew.hh
 *
 * @brief C++ abstract base class for Material object.
 */

#if !defined(pylith_materials_materialnew_hh)
#define pylith_materials_materialnew_hh

// Include directives ---------------------------------------------------
#include "materialsfwd.hh" // forward declarations

#include "pylith/feassemble/IntegratorPointWise.hh" // ISA IntegratorPointWise

#include "pylith/topology/topologyfwd.hh" // forward declarations
#include "spatialdata/spatialdb/spatialdbfwd.hh" // forward declarations
#include "spatialdata/units/unitsfwd.hh" // forward declarations

#include <string> // HASA std::string

// Material -------------------------------------------------------------
/** @brief C++ abstract base class for Material object.
 *
 * Interface definition for a material. 
 */

class pylith::materials::MaterialNew : public pylith::feassemble::IntegratorPointWise
{ // class Material
  friend class TestMaterialNew; // unit testing

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /** Default constructor.
   *
   * @param dimension Spatial dimension associated with material.
   */
  Material(const int dimension);

  /// Destructor.
  virtual
  ~Material(void);

  /// Deallocate PETSc and local data structures.
  virtual
  void deallocate(void);
  
  /** Get spatial dimension of material.
   *
   * @returns Spatial dimension.
   */
  int dimension(void) const;

  /** Set identifier of material.
   *
   * @param value Material identifier
   */
  void id(const int value);

  /** Get identifier of material.
   *
   * @returns Material identifier
   */
  int id(void) const;

  /** Set label of material.
   *
   * @param value Label of material
   */
  void label(const char* value);

  /** Get label of material.
   *
   * @returns Label of material
   */
  const char* label(void) const;

  /** Set scales used to nondimensionalize physical properties.
   *
   * @param dim Nondimensionalizer
   */
  void normalizer(const spatialdata::units::Nondimensional& dim);

  /** Initialize material. Setup auxiliary fields.
   *
   * @param mesh Finite-element mesh.
   */
  void initialize(const topology::Mesh& mesh);
  
  /** Get flag indicating whether Jacobian matrix must be reformed for
   * current state.
   *
   * @returns True if Jacobian matrix must be reformed, false otherwise.
   */
  bool needNewJacobian(void) const;

   /** Check whether material generates a symmetric Jacobian.
    *
    * @returns True if material generates symmetric Jacobian.
    */
   bool isJacobianSymmetric(void) const;

  /// Reset flag indicating whether Jacobian matrix must be reformed for
  /// current state.
  void resetNeedNewJacobian(void);

  /** Check whether material has a given auxiliary field.
   *
   * @param name Name of field.
   *
   * @returns True if material has auxiliary field, false otherwise.
   */
  bool hasAuxField(const char* name);

  /** Get auxiliary field.
   *
   * @param field Field over material.
   * @param name Name of field to retrieve.
   */
  void getAuxField(topology::Field *field,
		   const char* name) const;

  /** Set spatial database for auxiliary fields.
   *
   * @param value Pointer to database.
   */
  void dbAuxFields(spatialdata::spatialdb::SpatialDB* value);

  // PROTECTED METHODS //////////////////////////////////////////////////
protected :

  /// Initialize auxiliary fields using spatial database.
  void _initializeAuxFieldsDB(void);   

  // --------------------------------------------------------------------
  // These methods should be implemented by every constitutive model.
  // --------------------------------------------------------------------

  /** Compute properties from values in spatial database.
   *
   * @param auxValues Array of auxiliary values.
   * @param numAuxValues Number of auxiliary values.
   * @param dbValues Array of database values.
   */
  virtual
  void _dbToAuxFields(PylithScalar const auxValues[],
		      const int numAuxValues,
		      const scalar_array& dbValues) = 0;

  /** Nondimensionalize auxiliary fields. Nondimensionalization is
   * done in place (no copy).
   *
   * @param values Array of values.
   * @param nvalues Number of values.
   */
  virtual
  void _nondimAuxFields(PylithScalar const values[],
			const int nvalues) const = 0;

  /** Dimensionalize auxiliary fields. Dimensionalization is done in
   * place (no copy).
   *
   * @param values Array of values.
   * @param nvalues Number of values.
   */
  virtual
  void _dimAuxFields(PylithScalar const values[],
		     const int nvalues) const = 0;

  // PROTECTED MEMBERS //////////////////////////////////////////////////
protected :

  /// Field containing physical properties of material.
  topology::Field* _auxFields;

  spatialdata::units::Nondimensional* _normalizer; ///< Nondimensionalizer
  
  topology::StratumIS* _materialIS; ///< Index set for material cells.

  const int _dimension; ///< Spatial dimension of material.
  bool _needNewJacobian; ///< True if need to reform Jacobian, false otherwise.
  bool _isJacobianSymmetric; ///< True if Jacobian is symmetric;

  // PRIVATE MEMBERS ////////////////////////////////////////////////////
private :

  /// Database of parameters for physical properties of material.
  spatialdata::spatialdb::SpatialDB* _dbAuxFields;

  int _id; ///< Material identifier.
  std::string _label; ///< Label of material.

  // NOT IMPLEMENTED ////////////////////////////////////////////////////
private :

  MaterialNew(const MaterialNew&); ///< Not implemented.
  const MaterialNew& operator=(const MaterialNew&); ///< Not implemented

}; // class Material

#include "MaterialNew.icc" // inline methods

#endif // pylith_materials_material_hh


// End of file 
