#ifndef __smtk_model_Operator_h
#define __smtk_model_Operator_h

#include "smtk/util/SharedFromThis.h"
#include "smtk/model/Events.h"
#include "smtk/model/Parameter.h"

namespace smtk {
  namespace model {

class Operator;
typedef smtk::shared_ptr<Operator> OperatorPtr;
typedef std::set<OperatorPtr> Operators;

/**\brief A base class for solid modeling operations.
  *
  * Subclasses must implement name(), ableToOperate(), and operateInternal().
  * Additionally, their constructors should call setParameter() with
  * the list of accepted parameters.
  */
class SMTKCORE_EXPORT Operator : smtkEnableSharedPtr(Operator)
{
public:
  smtkTypeMacro(Operator);
  virtual std::string name() const = 0;
  virtual bool ableToOperate() { return false; }
  virtual OperatorResult operate();

  Parameters parameters() const;
  const Parameter& parameter(const std::string& name) const;
  Parameter parameter(const std::string& name);
  virtual void setParameter(const Parameter& p);
  bool hasFloatParameter(const std::string& name, int minSize = 1, int maxSize = -1, bool validate = true);
  bool hasStringParameter(const std::string& name, int minSize = 1, int maxSize = -1, bool validate = true);
  bool hasIntegerParameter(const std::string& name, int minSize = 1, int maxSize = -1, bool validate = true);
  bool hasUUIDParameter(const std::string& name, int minSize = 1, int maxSize = -1, bool validate = true);

  void observe(OperatorEventType event, ParameterChangeCallback functionHandle, void* callData);
  void observe(OperatorEventType event, WillOperateCallback functionHandle, void* callData);
  void observe(OperatorEventType event, DidOperateCallback functionHandle, void* callData);

  void unobserve(OperatorEventType event, ParameterChangeCallback functionHandle, void* callData);
  void unobserve(OperatorEventType event, WillOperateCallback functionHandle, void* callData);
  void unobserve(OperatorEventType event, DidOperateCallback functionHandle, void* callData);

  int trigger(OperatorEventType event, const Parameter& oldVal, const Parameter& newVal);
  int trigger(OperatorEventType event);
  int trigger(OperatorEventType event, const OperatorResult& result);

  bool operator < (const Operator& other) const;

protected:
  Parameters m_parameters;
  std::set<ParameterChangeObserver> m_parameterChangeTriggers;
  std::set<WillOperateObserver> m_willOperateTriggers;
  std::set<DidOperateObserver> m_didOperateTriggers;

  virtual OperatorResult operateInternal() = 0;

  bool checkParameterSize(int actualSize, int minSize, int maxSize);
};

  } // model namespace
} // smtk namespace

#endif // __smtk_model_Operator_h
