#ifndef SIMONLISTCOMMAND_EXPORT_H
#define SIMONLISTCOMMAND_EXPORT_H
 
// needed for KDE_EXPORT and KDE_IMPORT macros
#include <kdemacros.h>
#include <KGenericFactory>
 
#ifndef SIMONLISTCOMMAND_EXPORT
# if defined(MAKE_SIMONLISTCOMMAND_LIB)
   // We are building this library
#  define SIMONLISTCOMMAND_EXPORT KDE_EXPORT
# else
   // We are using this library
#  define SIMONLISTCOMMAND_EXPORT KDE_IMPORT
# endif
#endif
 
# ifndef SIMONLISTCOMMAND_EXPORT_DEPRECATED
#  define SIMONLISTCOMMAND_EXPORT_DEPRECATED KDE_DEPRECATED SIMONLISTCOMMAND_EXPORT
# endif

  

#endif