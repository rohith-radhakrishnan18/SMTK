//=============================================================================
//
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//
//=============================================================================
#include "smtk/graph/Resource.h"

namespace smtk
{
namespace graph
{
std::shared_ptr<smtk::resource::Component> ResourceBase::find(
  const smtk::common::UUID& compId) const
{
  // Components are stored in a set, so we construct a dummy component to find
  // the component we want.
  struct QueryKey : resource::Component
  {
    QueryKey(const smtk::common::UUID& id)
      : m_id(id)
    {
    }
    const smtk::common::UUID& id() const final { return m_id; }
    bool setId(const smtk::common::UUID&) final { return false; }
    const smtk::resource::ResourcePtr resource() const final
    {
      return smtk::resource::ResourcePtr();
    }

    const smtk::common::UUID& m_id;
  };

  auto it = m_nodes.find(std::make_shared<QueryKey>(compId));
  if (it != m_nodes.end())
  {
    return *it;
  }
  return std::shared_ptr<smtk::resource::Component>();
}

std::function<bool(const smtk::resource::Component&)> ResourceBase::queryOperation(
  const std::string&) const
{
  return [](const smtk::resource::Component& comp) -> bool {
    auto gcomp = dynamic_cast<const smtk::graph::Component*>(&comp);
    return !!gcomp;
  };
}

void ResourceBase::visit(std::function<void(const smtk::resource::ComponentPtr&)>& v) const
{
  for (const auto& node : m_nodes)
  {
    v(node);
  }
}

} // namespace graph
} // namespace smtk
