//=========================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//=========================================================================

#ifndef pybind_smtk_task_Task_h
#define pybind_smtk_task_Task_h

#include <pybind11/pybind11.h>

#include "smtk/task/Task.h"

#include "smtk/task/State.h"

namespace py = pybind11;

inline PySharedPtrClass< smtk::task::Task > pybind11_init_smtk_task_Task(py::module &m)
{
  PySharedPtrClass< smtk::task::Task > instance(m, "Task");
  instance
    .def("typeName", &smtk::task::Task::typeName)
    .def_static("create", (std::shared_ptr<smtk::task::Task> (*)()) &smtk::task::Task::create)
    .def_static("create", (std::shared_ptr<smtk::task::Task> (*)(::std::shared_ptr<smtk::task::Task> &)) &smtk::task::Task::create, py::arg("ref"))
    .def("configure", [](smtk::task::Task& task, const std::string& jsonConfig)
      {
        auto config = nlohmann::json::parse(jsonConfig);
        task.configure(config);
      })
    .def("title", &smtk::task::Task::title)
    .def("setTitle", &smtk::task::Task::setTitle, py::arg("title"))
    .def("state", &smtk::task::Task::state)
    .def("markCompleted", &smtk::task::Task::markCompleted, py::arg("completed"))
    .def("dependencies", &smtk::task::Task::dependencies)
    .def("addDependency", &smtk::task::Task::addDependency, py::arg("dependency"))
    .def("removeDependency", &smtk::task::Task::removeDependency, py::arg("dependency"))
    .def("observers", &smtk::task::Task::observers)
    .def("internalState", &smtk::task::Task::internalState)
    .def_readonly_static("type_name", &smtk::task::Task::type_name)
    ;
  return instance;
}

#endif
