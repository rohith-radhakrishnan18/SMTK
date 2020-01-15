//=========================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//=========================================================================

#ifndef __smtk_project_AddToProject_h
#define __smtk_project_AddToProject_h

#include "smtk/project/Operation.h"

namespace smtk
{
namespace project
{

class SMTKCORE_EXPORT AddToProject : public smtk::project::Operation
{
public:
  smtkTypeMacro(smtk::project::AddToProject);
  smtkCreateMacro(AddToProject);
  smtkSharedFromThisMacro(smtk::operation::Operation);

  bool configure(const smtk::attribute::AttributePtr&, const smtk::attribute::ItemPtr&) override;

protected:
  Result operateInternal() override;
  virtual const char* xmlDescription() const override;
};
} // namespace project
} // namespace smtk

#endif
