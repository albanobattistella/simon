#ifndef SIMON_SIMONRECOGNITIONRESULT_EXPORT_H_4FA87AEF3A384359BC5F62307EE59A64
#define SIMON_SIMONRECOGNITIONRESULT_EXPORT_H_4FA87AEF3A384359BC5F62307EE59A64

// needed for KDE_EXPORT and KDE_IMPORT macros
#include <kdemacros.h>

#ifndef SIMONRECOGNITIONRESULT_EXPORT
# if defined(MAKE_SIMONRECOGNITIONRESULT_LIB)
// We are building this library
#  define SIMONRECOGNITIONRESULT_EXPORT KDE_EXPORT
# else
// We are using this library
#  define SIMONRECOGNITIONRESULT_EXPORT KDE_IMPORT
# endif
#endif

# ifndef SIMONRECOGNITIONRESULT_EXPORT_DEPRECATED
#  define SIMONRECOGNITIONRESULT_EXPORT_DEPRECATED KDE_DEPRECATED SIMONRECOGNITIONRESULT_EXPORT
# endif
#endif
