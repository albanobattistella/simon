set(simonappcore_LIB_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/simoncontrol.cpp
)

set(simonappcore_LIB_HDRS
  ${CMAKE_CURRENT_SOURCE_DIR}/simoncontrol.h
  ${CMAKE_CURRENT_SOURCE_DIR}/simonappcore_export.h
)

kde4_add_kcfg_files(simonappcore_LIB_SRCS coreconfiguration.kcfgc)
kde4_add_library(simonappcore SHARED ${simonappcore_LIB_SRCS} )

target_link_libraries(simonappcore ${QT_LIBRARIES} ${KDE4_KDEUI_LIBS}
  simoninfo simonlogging simonrecognitioncontrol simonactions
  simonmodelmanagementui simonscenarios simonrecognitionresult
  simonsound simontts simoncontextdetection
)

set_target_properties(simonappcore PROPERTIES VERSION ${CMAKE_SIMON_VERSION_STRING} SOVERSION ${CMAKE_SIMON_VERSION_MAJOR})

install(FILES ${simonappcore_LIB_HDRS} DESTINATION ${INCLUDE_INSTALL_DIR}/simon/AppCore COMPONENT simondevel)
install(TARGETS simonappcore DESTINATION ${SIMON_LIB_INSTALL_DIR} COMPONENT simon)

set( kcm_simonappcore_LIB_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/generalsettings.cpp)
kde4_add_ui_files(kcm_simonappcore_LIB_SRCS generalsettingsdlg.ui)
kde4_add_kcfg_files(kcm_simonappcore_LIB_SRCS coreconfiguration.kcfgc)

kde4_add_plugin(simonappcorekcm ${kcm_simonappcore_LIB_SRCS})
target_link_libraries( simonappcorekcm ${KDE4_KDEUI_LIBS})

install(TARGETS simonappcorekcm DESTINATION ${PLUGIN_INSTALL_DIR} COMPONENT simon)
install(FILES simongeneralconfig.desktop DESTINATION ${SERVICES_INSTALL_DIR} COMPONENT simon)
