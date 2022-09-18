#ifndef BIT32_H
#define BIT32_H

#if defined(__osf__) && defined(__alpha)
#define BIT32STR "unsigned int"
typedef unsigned int BIT32;
typedef int S_BIT32;
#else
#define BIT32STR "unsigned long"
typedef unsigned long BIT32;
typedef long S_BIT32;
#endif

#endif /* BIT32_H */
