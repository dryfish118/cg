#ifndef _PRE_H_
#define _PRE_H_

#ifndef CGEXPORT
#define CG_EXPORT __declspec(dllimport)
#else
#define CG_EXPORT _declspec(dllexport)
#endif

#endif
