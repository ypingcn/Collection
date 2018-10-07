#ifndef LIBDES_GLOBAL_H
#define LIBDES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBDES_LIBRARY)
#  define LIBDESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBDESSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBDES_GLOBAL_H
