#ifndef SIMON_SIMONDCONFIGURATION_EXPORT_H_65AD5ED111734E259F13C9B166245649
#define SIMON_SIMONDCONFIGURATION_EXPORT_H_65AD5ED111734E259F13C9B166245649

// needed for KDE_EXPORT and KDE_IMPORT macros
#include <kdemacros.h>

#ifndef SIMONDCONFIGURATION_EXPORT
# if defined(MAKE_SIMONDCONFIGURATION_LIB)
// We are building this library
#  define SIMONDCONFIGURATION_EXPORT KDE_EXPORT
# else
// We are using this library
#ifdef Q_OS_WIN
#  define SIMONDCONFIGURATION_EXPORT
#else
#  define SIMONDCONFIGURATION_EXPORT KDE_IMPORT
#endif
# endif
#endif

# ifndef SIMONDCONFIGURATION_EXPORT_DEPRECATED
#  define SIMONDCONFIGURATION_EXPORT_DEPRECATED KDE_DEPRECATED SIMONDCONFIGURATION_EXPORT
# endif
#endif
