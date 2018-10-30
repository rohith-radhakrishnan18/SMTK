//=========================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//=========================================================================

#ifndef __smtk_mesh_Component_h
#define __smtk_mesh_Component_h

#include "smtk/CoreExports.h"
#include "smtk/PublicPointerDefs.h"
#include "smtk/TupleTraits.h"

#include "smtk/resource/Component.h"

#include "smtk/mesh/core/Collection.h"
#include "smtk/mesh/core/MeshSet.h"

namespace smtk
{
namespace mesh
{
class Component;

typedef std::vector<smtk::mesh::Component> ComponentList;
typedef std::set<smtk::mesh::Component> Components;

/// A lightweight object for representing meshset information as a resource
/// component. This is useful for constructing links between meshsets and other
/// resources/components and for representing meshsets within smtk's attribute
/// system.
class SMTKCORE_EXPORT Component : public smtk::resource::Component
{
protected:
  Component(const smtk::mesh::CollectionPtr&, const smtk::common::UUID&);
  Component(const smtk::mesh::MeshSet&);

public:
  smtkTypeMacro(Component);
  smtkSharedFromThisMacro(smtk::resource::Component);

  /// Construct a mesh component corresponding to a meshset from the input
  /// collection and id. No checking is performed that the collection has a
  /// meshset with this id; if this is the case, the resolved mesh() will return
  /// a default-constructed (and invalid) mesh.
  static std::shared_ptr<Component> create(
    const smtk::mesh::CollectionPtr&, const smtk::common::UUID&);

  /// Construct a mesh component correpsonding to the input meshset.
  static std::shared_ptr<Component> create(const smtk::mesh::MeshSet&);

  /// Access the component's resource.
  const smtk::resource::ResourcePtr resource() const override;

  /// Access the component's id.
  const smtk::common::UUID& id() const override { return m_id; }

  /// Set the component's id. No checking is performed that the collection has a
  /// meshset with this id; if this is the case, the resolved mesh() will return
  /// a default-constructed (and invalid) mesh.
  bool setId(const smtk::common::UUID& myID) override
  {
    m_id = myID;
    return true;
  }

  /// Access the meshset represented by this component.
  const smtk::mesh::MeshSet mesh() const;
  smtk::mesh::MeshSet mesh();

private:
  std::weak_ptr<smtk::mesh::Collection> m_collection;
  smtk::common::UUID m_id;
};

} // namespace mesh
} // namespace smtk

#endif