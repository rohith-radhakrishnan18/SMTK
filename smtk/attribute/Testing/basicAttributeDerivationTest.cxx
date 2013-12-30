/*=========================================================================

Copyright (c) 1998-2012 Kitware Inc. 28 Corporate Drive,
Clifton Park, NY, 12065, USA.

All rights reserved. No part of this software may be reproduced, distributed,
or modified, in any form or by any means, without permission in writing from
Kitware Inc.

IN NO EVENT SHALL THE AUTHORS OR DISTRIBUTORS BE LIABLE TO ANY PARTY FOR
DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
OF THE USE OF THIS SOFTWARE, ITS DOCUMENTATION, OR ANY DERIVATIVES THEREOF,
EVEN IF THE AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

THE AUTHORS AND DISTRIBUTORS SPECIFICALLY DISCLAIM ANY WARRANTIES,
INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE, AND NON-INFRINGEMENT.  THIS SOFTWARE IS PROVIDED ON AN
"AS IS" BASIS, AND THE AUTHORS AND DISTRIBUTORS HAVE NO OBLIGATION TO
PROVIDE
MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
=========================================================================*/

#include "smtk/attribute/Manager.h"
#include "smtk/attribute/Definition.h"
#include "smtk/attribute/Attribute.h"
#include "smtk/attribute/IntItem.h"
#include "smtk/attribute/IntItemDefinition.h"
#include "smtk/attribute/DoubleItem.h"
#include "smtk/attribute/DoubleItemDefinition.h"
#include "smtk/attribute/StringItem.h"
#include "smtk/attribute/StringItemDefinition.h"
#include <iostream>

std::string itemNames[] = {
  "IntComp1",
  "IntComp2",
  "DoubleComp1",
  "DoubleComp2",
  "StringComp1",
  "StringComp2"
};

int main()
{
  int status = 0;
  {
  typedef smtk::attribute::IntItemDefinition IntCompDef;
  typedef smtk::attribute::DoubleItemDefinition DoubleCompDef;
  typedef smtk::attribute::StringItemDefinition StringCompDef;
  typedef smtk::attribute::ValueItem ValueComp;
  typedef smtk::attribute::Item AttComp;

  smtk::attribute::Manager manager;
  std::cout << "Manager Created\n";
  smtk::attribute::DefinitionPtr base = manager.createDefinition("BaseDef");
  // Lets add some item definitions
  base->addItemDefinition<IntCompDef>(itemNames[0]);
  smtk::attribute::IntItemDefinitionPtr icompdef2 = base->addItemDefinition<IntCompDef>(itemNames[1]);
  icompdef2->setDefaultValue(10);

  smtk::attribute::DefinitionPtr def1 = manager.createDefinition("Derived1", "BaseDef");
   // Lets add some item definitions
  def1->addItemDefinition<DoubleCompDef>(itemNames[2]);
  smtk::attribute::DoubleItemDefinitionPtr dcompdef2 = def1->addItemDefinition<DoubleCompDef>(itemNames[3]);
  dcompdef2->setDefaultValue(-35.2);

  smtk::attribute::DefinitionPtr def2 = manager.createDefinition("Derived2", "Derived1");
   // Lets add some item definitions
  def2->addItemDefinition<StringCompDef>(itemNames[4]);
  smtk::attribute::StringItemDefinitionPtr scompdef2 = def2->addItemDefinition<StringCompDef>(itemNames[5]);
  scompdef2->setDefaultValue("Default");

  // Lets test out the find item position method
  int j, pstatus = 0;
  for (j =0; j < 6; j++)
    {
    if (def2->findItemPosition(itemNames[j]) != j)
      {
      std::cerr << "Incorrect Position Returned for " << itemNames[j]
                << ", position returned is " << def2->findItemPosition(itemNames[j])
                << ", but it should be " << j << "\n";
      pstatus = status = -1;
      }
    }
  if (!pstatus)
    {
    std::cout << "Initial Position Test Passed!\n";
    }
  else
    {
    std::cout << "Initial Position Test Failed!\n";
    }

  // Lets add a  component to the base def and verify that positions are reordered
  base->addItemDefinition<StringCompDef>("InsertStringItem");
  pstatus = 0;
  for (j =2; j < 6; j++)
    {
    if (def2->findItemPosition(itemNames[j]) != (j+1))
      {
      std::cerr << "Incorrect Position Returned for " << itemNames[j]
                << ", position returned is " << def2->findItemPosition(itemNames[j])
                << ", but it should be " << j+1 << "\n";
      pstatus = status = -1;
      }
    }

  if (!pstatus)
    {
    std::cout << "Insertion Position Test Passed!\n";
    }
  else
    {
    std::cout << "Insertion Position Test Failed!\n";
    }


  smtk::attribute::AttributePtr att = manager.createAttribute("testAtt", "Derived2");
  if (att)
    {
    std::cout << "Attribute testAtt created\n";
    }
  else
    {
    std::cout << "ERROR: Attribute testAtt not created\n";
    status = -1;
    }

  smtk::attribute::ValueItemPtr vcomp;
  smtk::attribute::ItemPtr comp;

  //test the find of base def
  comp = att->find("DoubleComp1");
  if (comp)
    {
    vcomp = smtk::dynamic_pointer_cast<ValueComp>(comp);
    std::cout << " Value = "  << vcomp->valueAsString() << std::endl;
    }
  else
    {
    std::cout << "ERROR: could not find the base's item" << std::endl;
    status = -1;
    }

  int i, n = static_cast<int>(att->numberOfItems());
  std::cout << "Items of testAtt:\n";
  for (i = 0; i < n; i++)
    {
    comp = att->item(i);
    std::cout << "\t" << comp->name() << " Type = " << AttComp::type2String(comp->type()) << ", ";
    vcomp = smtk::dynamic_pointer_cast<ValueComp>(comp);
    if (vcomp)
      {
      switch (vcomp->type())
        {
        case AttComp::DOUBLE:
        case AttComp::INT:
          std::cout << " Value = "  << vcomp->valueAsString() << std::endl;
          break;
        case AttComp::STRING:
          std::cout << " String Val = " << vcomp->valueAsString() << std::endl;
          break;
        default:
          break;
        }
      }
    }
  std::cout << "Manager destroyed\n";
  }
  return status;
}
