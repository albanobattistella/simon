set (simonkeyboardcommandplugin_SRCS 
  keyboardcommandmanager.cpp 
  keyboardconfiguration.cpp
  keyboardtab.cpp
  keyboardset.cpp
  keyboardsetcontainer.cpp
  keyboardbutton.cpp
  keyboardmodifybuttondialog.cpp
  flowlayout.cpp
)

kde4_add_ui_files(simonkeyboardcommandplugin_SRCS 
  keyboardwidget.ui
  keyboardconfigurationdlg.ui
  modifybuttondlg.ui
)

kde4_add_plugin(simonkeyboardcommandplugin ${simonkeyboardcommandplugin_SRCS})

target_link_libraries(simonkeyboardcommandplugin ${KDE4_KDEUI_LIBS} ${QT_QTXML_LIBRARY}
  simonscenarios simonactions eventsimulation simonscenariobase)

install(TARGETS simonkeyboardcommandplugin DESTINATION ${PLUGIN_INSTALL_DIR} COMPONENT simoncommandkeyboardplugin )
install( FILES simonkeyboardcommandplugin.desktop DESTINATION ${SERVICES_INSTALL_DIR} COMPONENT simoncommandkeyboardplugin )

install(FILES keyboardsets.xml DESTINATION ${DATA_INSTALL_DIR}/simon/conf COMPONENT simoncommandkeyboardplugin)
