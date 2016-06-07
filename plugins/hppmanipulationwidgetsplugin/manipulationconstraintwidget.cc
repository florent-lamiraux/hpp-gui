#include "hppmanipulationwidgetsplugin/hppmanipulationwidgetsplugin.hh"
#include "hppmanipulationwidgetsplugin/ui_constraintwidget.h"

#include "hppmanipulationwidgetsplugin/manipulationncpicker.hh"
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

    void ManipulationConstraintWidget::confirmNumerical()
    {
      HppManipulationWidgetsPlugin* plugin = dynamic_cast<HppManipulationWidgetsPlugin*>(plugin_);
      QStringList l;

      for (int i = 0; i < ui->nameList->count(); i++) {
        QListWidgetItem* item = ui->nameList->item(i);
        l << item->text();
      }
      ManipulationNCPicker* ncp = new ManipulationNCPicker(l, plugin);

      ncp->show();
    }
  }
}