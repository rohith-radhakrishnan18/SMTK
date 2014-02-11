#ifndef __smtk_model_EntityPhrase_h
#define __smtk_model_EntityPhrase_h

#include "smtk/model/DescriptivePhrase.h"

namespace smtk {
  namespace model {

/**\brief Describe an entity for user presentation.
  */
class SMTKCORE_EXPORT EntityPhrase : public DescriptivePhrase
{
public:
  smtkTypeMacro(EntityPhrase);
  smtkSharedPtrCreateMacro(DescriptivePhrase);
  Ptr setup(const Cursor& entity, DescriptivePhrase::Ptr parent = DescriptivePhrasePtr());

  virtual std::string title();
  virtual bool isTitleMutable() const;
  virtual bool setTitle(const std::string& newTitle);
  virtual std::string subtitle();

  virtual Cursor relatedEntity() const;
  virtual FloatList relatedColor() const;
  virtual bool isRelatedColorMutable() const;
  virtual bool setRelatedColor(const FloatList& rgba);

  void setMutability(int whatsMutable);

  static DescriptivePhrases PhrasesFromUUIDs(smtk::model::StoragePtr, const smtk::util::UUIDs&);

protected:
  EntityPhrase();

  Cursor m_entity;
  int m_mutability;
};

  } // model namespace
} // smtk namespace

#endif // __smtk_model_EntityPhrase_h
