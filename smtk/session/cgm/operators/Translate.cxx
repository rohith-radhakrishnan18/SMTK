//=========================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//=========================================================================
#include "smtk/session/cgm/operators/Translate.h"

#include "smtk/session/cgm/CAUUID.h"
#include "smtk/session/cgm/Engines.h"
#include "smtk/session/cgm/Session.h"
#include "smtk/session/cgm/TDUUID.h"

#include "smtk/io/Logger.h"

#include "smtk/model/CellEntity.h"
#include "smtk/model/Manager.h"
#include "smtk/model/Model.h"

#include "smtk/attribute/Attribute.h"
#include "smtk/attribute/DoubleItem.h"
#include "smtk/attribute/IntItem.h"
#include "smtk/attribute/StringItem.h"

#include "CGMApp.hpp"
#include "CubitAttribManager.hpp"
#include "CubitCompat.hpp"
#include "CubitDefines.h"
#include "DLIList.hpp"
#include "DagType.hpp"
#include "GeometryModifyTool.hpp"
#include "GeometryQueryEngine.hpp"
#include "GeometryQueryTool.hpp"
#include "InitCGMA.hpp"
#include "RefEntity.hpp"
#include "RefEntityFactory.hpp"

#include "smtk/session/cgm/Translate_xml.h"

using namespace smtk::model;

namespace smtk
{
namespace session
{
namespace cgm
{

smtk::operation::OperationResult Translate::operateInternal()
{
  smtk::attribute::DoubleItemPtr offset = this->findDouble("offset");

  Models bodiesIn = this->associatedEntitiesAs<Models>();

  Models::iterator it;
  DLIList<RefEntity*> cgmEntitiesIn;
  DLIList<RefEntity*> cgmEntitiesOut;
  RefEntity* refEntity;
  for (it = bodiesIn.begin(); it != bodiesIn.end(); ++it)
  {
    refEntity = this->cgmEntity(*it);
    if (refEntity)
    {
      cgmEntitiesIn.append(refEntity);
      this->manager()->erase(
        *it); // We will re-transcribe momentarily. TODO: This could be more efficient.
    }
  }

  int nb = cgmEntitiesIn.size();

  GeometryQueryTool::instance()->translate(cgmEntitiesIn, offset->value(0), offset->value(1),
    offset->value(2),
    true, // (check before transforming)
    cgmEntitiesOut);
  if (cgmEntitiesOut.size() != nb)
  {
    smtkInfoMacro(log(), "Failed to translate bodies or wrong number"
        << " (" << cgmEntitiesOut.size() << " != " << nb << ")"
        << " of resulting bodies.");
    return this->createResult(smtk::operation::Operation::OPERATION_FAILED);
  }

  smtk::operation::OperationResult result =
    this->createResult(smtk::operation::Operation::OPERATION_SUCCEEDED);

  this->addEntitiesToResult(cgmEntitiesOut, result, MODIFIED);
  // Nothing expunged.

  return result;
}

} // namespace cgm
} //namespace session
} // namespace smtk

smtkImplementsModelOperation(SMTKCGMSESSION_EXPORT, smtk::session::cgm::Translate, cgm_translate,
  "translate", Translate_xml, smtk::session::cgm::Session);