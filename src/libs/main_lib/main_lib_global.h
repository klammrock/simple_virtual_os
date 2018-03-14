#ifndef MAIN_LIB_GLOBAL_H
#define MAIN_LIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MAIN_LIB_LIBRARY)
#  define MAIN_LIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MAIN_LIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MAIN_LIB_GLOBAL_H
