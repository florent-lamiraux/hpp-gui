#ifndef HPP_GUI_HPPWIDGETSPLUGIN_HH
#define HPP_GUI_HPPWIDGETSPLUGIN_HH

#include <gepetto/gui/plugin-interface.hh>
#include <hpp/corbaserver/client.hh>

namespace hpp {
  namespace gui {
    class SolverWidget;
    class PathPlayer;
    class JointTreeWidget;
    class ConfigurationListWidget;
    class JointTreeItem;
    class Roadmap;
    class ConstraintWidget;

    /// Plugin that add a lot of features to work with hpp.
    class HppWidgetsPlugin : public QObject, public gepetto::gui::PluginInterface,
    public gepetto::gui::ModelInterface, public gepetto::gui::CorbaInterface
    {
      Q_OBJECT
        Q_INTERFACES (gepetto::gui::PluginInterface
            gepetto::gui::ModelInterface
            gepetto::gui::CorbaInterface)

      public:
        struct JointElement {
          std::string name;
          std::string bodyName;
          JointTreeItem* item;
          bool updateViewer;

          JointElement ()
            : name (), bodyName (), item (NULL), updateViewer (false) {}
          JointElement (std::string n, std::string bn, JointTreeItem* i, bool updateV = true)
            : name (n), bodyName (bn), item (i), updateViewer (updateV) {}
        };
        typedef QMap <std::string, JointElement> JointMap;
        typedef hpp::corbaServer::Client HppClient;

        explicit HppWidgetsPlugin ();

        virtual ~HppWidgetsPlugin ();

        // PluginInterface interface
      public:
        /// Initialize the plugin.
        void init();

        /// Returns the plugin's name.
        QString name() const;

        // ModelInterface interface
      public:
        /// Load a robot in the corba server.
        /// \param rd robot definition
        void loadRobotModel (gepetto::gui::DialogLoadRobot::RobotDefinition rd);

        /// Load an environment in the corba server.
        /// \param ed environment definition
        void loadEnvironmentModel (gepetto::gui::DialogLoadEnvironment::EnvironmentDefinition ed);


        /// Get the name of a joint's body.
        /// \param jointName joint name
        std::string getBodyFromJoint (const std::string& jointName) const;
signals:
        void configurationValidationStatus (bool valid);
        void configurationValidationStatus (QStringList collision);

        // CorbaInterface interface
      public:
        virtual bool corbaException (int jobId, const CORBA::Exception &excep) const;

        /// Open a connection to a corba server.
        virtual void openConnection ();

        /// Close connection to corbaserver.
        virtual void closeConnection ();
signals:
        /// Log the failure of a job in the MainWindow.
        void logJobFailed  (int id, const QString& text) const;

        public slots:
        /// Apply the current configuration of the robot.
          void applyCurrentConfiguration ();

        /// Build a list of bodies in collision.
        void configurationValidation ();

        /// Select a joint in the joint tree from a body's name.
        /// \param bodyName name of the body
        void selectJointFromBodyName (const QString bodyName);

      public:
        /// Get the possible actions on a joint.
        /// \param jointName name of the joint
        QList <QAction*> getJointActions (const std::string &jointName);

      public:
        /// Get the corbaserver client.
        HppClient* client () const;

        /// Get the jointMap.
        JointMap& jointMap ();

        /// Get the pathPlayer widget.
        PathPlayer* pathPlayer() const;

        /// Get the list of joints from corbaserver and update internal joint map.
        /// \param robotName name of the robot
        virtual void updateRobotJoints (const QString robotName);

        /// Get the currently selected joint name.
        std::string getSelectedJoint ();

        /// Create the roadmap of a given joint.
        /// \param jointName name of the joint
        virtual Roadmap* createRoadmap (const std::string& jointName);

      signals:
        void logSuccess (const QString& text);
        void logFailure (const QString& text);

        protected slots:
        /// Display the roadMap of a given joint.
        /// \param jointName name of the joint
          virtual void displayRoadmap (const std::string& jointName);

        /// Add XYZ axis at the joint's position
        /// \param jointName name of the joint
        void addJointFrame (const std::string& jointName);

      private:

        PathPlayer* pathPlayer_;
        SolverWidget* solverWidget_;
        ConfigurationListWidget* configListWidget_;

        HppClient* hpp_;

      protected:
        /// Change all "/" in jn to "__"
        /// \param jn string to escape
        static std::string escapeJointName (const std::string jn);

        /// Create a group from the given joint.
        /// \param jn joint name
        std::string createJointGroup (const std::string jn);

        QString getIIOPurl () const;

        /// Replace all the bodies according to their position in hpp.
        void computeObjectPosition();

        QList <QDockWidget*> dockWidgets_;
        JointTreeWidget* jointTreeWidget_;
        ConstraintWidget* constraintWidget_;
        JointMap jointMap_;
        std::list <std::string> jointFrames_;
    };
  } // namespace gui
} // namespace hpp

#endif // HPP_GUI_HPPWIDGETSPLUGIN_HH
