set(simoncontextadapter_LIB_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/contextadapter.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/situation.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/cachedmodel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/modelsource.cpp
)

set(simoncontextadapter_LIB_HDRS
  simoncontextadapter_export.h
  situation.h
  contextadapter.h
)

kde4_add_library(simoncontextadapter  SHARED ${simoncontextadapter_LIB_SRCS})
target_link_libraries(simoncontextadapter ${QT_LIBRARIES} ${KDE4_KDECORE_LIBS} 
  ${QT_QTXML_LIBRARY} ${KDE4_KDEUI_LIBS} simonmodelcompilation simonscenarios
)

set_target_properties(simoncontextadapter PROPERTIES VERSION ${CMAKE_SIMON_VERSION_STRING} SOVERSION ${CMAKE_SIMON_VERSION_MAJOR})

install(FILES ${simoncontextdetection_LIB_HDRS} DESTINATION ${INCLUDE_INSTALL_DIR}/simon/contextadapter COMPONENT simonddevel)
install(TARGETS simoncontextadapter DESTINATION ${SIMON_LIB_INSTALL_DIR} COMPONENT simond)
