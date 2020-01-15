//=========================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//=========================================================================
#include "smtk/project/Project.h"

#include "smtk/resource/Manager.h"

namespace smtk
{
namespace project
{
Project::Project(const std::string& typeName)
  : m_resources(smtk::resource::Resource::m_manager)
  , m_operations(std::weak_ptr<smtk::operation::Manager>())
  , m_typeName(typeName)
{
}
} // namespace project
} // namespace smtk
