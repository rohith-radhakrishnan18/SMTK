//=========================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//=========================================================================

// .NAME vtkMergeOperation - Merge a set of geometric model entities
// .SECTION Description
// Operation to merge a set of source geometric model entities into
// a target geometric entity on the server.  The properties of the target entity
// (e.g. color, BCS/ModelEntityGroup associations) will not be changed.
// Warning: This may only currently work from model faces.

#ifndef __smtkdiscrete_vtkMergeOperation_h
#define __smtkdiscrete_vtkMergeOperation_h

#include "smtk/session/discrete/Exports.h" // For export macro
#include "vtkMergeOperationBase.h"

class vtkDiscreteModelWrapper;

class SMTKDISCRETESESSION_EXPORT vtkMergeOperation : public vtkMergeOperationBase
{
public:
  static vtkMergeOperation* New();
  vtkTypeMacro(vtkMergeOperation, vtkMergeOperationBase);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  using Superclass::Operate;

  // Description:
  // Modify the color, user name, and/or the visibility of an object.
  virtual void Operate(vtkDiscreteModelWrapper* ModelWrapper);

  // Description:
  // Returns success (1) or failue (0) for Operation.
  vtkGetMacro(OperateSucceeded, int);

  // Description:
  // Get the target geometric model entity.
  vtkDiscreteModelGeometricEntity* GetTargetModelEntity(vtkDiscreteModelWrapper*);

protected:
  vtkMergeOperation();
  ~vtkMergeOperation() override;

  bool AbleToOperate(vtkDiscreteModel* model) override
  {
    return this->Superclass::AbleToOperate(model);
  }

  // Description:
  // Check to see if everything is properly set for the operator.
  virtual bool AbleToOperate(vtkDiscreteModelWrapper* ModelWrapper);

private:
  // Description:
  // Flag to indicate that the operation on the model succeeded (1) or not (0).
  int OperateSucceeded;

  vtkMergeOperation(const vtkMergeOperation&); // Not implemented.
  void operator=(const vtkMergeOperation&);    // Not implemented.
};

#endif