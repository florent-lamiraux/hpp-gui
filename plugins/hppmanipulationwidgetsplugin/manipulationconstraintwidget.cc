//
// Copyright (c) CNRS
// Authors: Joseph Mirabel and Heidy Dallard
//

#include "hppmanipulationwidgetsplugin/hppmanipulationwidgetsplugin.hh"
#include "hppwidgetsplugin/ui_constraintwidget.h"

#include "manipulationconstraintwidget.hh"

namespace hpp {
  namespace gui {
    ManipulationConstraintWidget::ManipulationConstraintWidget(HppWidgetsPlugin* plugin, QWidget* parent)
        : ConstraintWidget(plugin, parent)
    {
    }

    ManipulationConstraintWidget::~ManipulationConstraintWidget()
    {
    }

    void ManipulationConstraintWidget::applyConstraints()
    {
    }

    void ManipulationConstraintWidget::reset()
    {
      HppManipulationWidgetsPlugin* plugin = dynamic_cast<HppManipulationWidgetsPlugin*>(plugin_);
      hpp::GraphComp_var graphComp;
      hpp::GraphElements_var graphElems;

      plugin->manipClient()->graph()->getGraph(graphComp.out(), graphElems.out());
      for (unsigned i = 0; i < graphElems->edges.length(); ++i) {
        plugin->manipClient()->graph()->resetConstraints(graphElems->edges[i].id);
      }
      for (unsigned i = 0; i < graphElems->nodes.length(); ++i) {
        plugin->manipClient()->graph()->resetConstraints(graphElems->nodes[i].id);
      }
    }
  }
}
