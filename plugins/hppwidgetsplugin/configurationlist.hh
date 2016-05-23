#ifndef CONFIGURATIONLIST_HH
#define CONFIGURATIONLIST_HH

#include <QListWidget>

namespace hpp {
  namespace gui {
    /// A QListWidget that accept drag and drop of configurations.
    class ConfigurationList : public QListWidget
    {
      Q_OBJECT

    signals:
      void configurationChanged();

    public:
      ConfigurationList(QWidget* parent);
      virtual ~ConfigurationList();

    protected:
      void dragEnterEvent(QDragEnterEvent* event);
      void dragMoveEvent(QDragMoveEvent* event);
      void dropEvent(QDropEvent *event);
      void startDrag(Qt::DropActions supportedActions);
    };
  }
}

#endif // CONFIGURATIONLIST_HH
