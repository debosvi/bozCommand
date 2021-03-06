/* ISC license. */

#ifndef SYSDEPS_H
#define SYSDEPS_H

#define SKALIBS_TARGET "i686-w64-mingw32"
#define SKALIBS_HASCLOCKRT
#define SKALIBS_HASCLOCKMON
#define SKALIBS_HASPOSIXSPAWN
#define SKALIBS_ENDIANNESS "little"
#define SKALIBS_SIZEOFUSHORT 2
#define SKALIBS_USHORT_BITS 16
#define SKALIBS_SIZEOFUINT 4
#define SKALIBS_UINT_BITS 32
#define SKALIBS_SIZEOFULONG 4
#define SKALIBS_ULONG_BITS 32
#define SKALIBS_SIZEOFGID 4
#define SKALIBS_GID_BITS 32
#define SKALIBS_SIZEOFTIME 4
#define SKALIBS_TIME_BITS 32
#define SKALIBS_HASACCEPT4
#undef SKALIBS_HASANCILAUTOCLOSE
#undef SKALIBS_HASCMSGCLOEXEC
#define SKALIBS_HASDEVURANDOM
#define SKALIBS_HASEPROTO
#define SKALIBS_HASEVENTFD
#define SKALIBS_HASFLOCK
#undef SKALIBS_HASGETPEEREID
#define SKALIBS_HASSOPEERCRED
#undef SKALIBS_HASGETPEERUCRED
#define SKALIBS_HASIPV6
#define SKALIBS_HASMALLOC0
#define SKALIBS_HASMSGDONTWAIT
#define SKALIBS_HASNBWAITALL
#define SKALIBS_HASOPENAT
#define SKALIBS_HASLINKAT
#define SKALIBS_HASPIPE2
#define SKALIBS_HASPPOLL
#undef SKALIBS_HASREVOKE
#define SKALIBS_HASSENDFILE
#define SKALIBS_HASSETGROUPS
#define SKALIBS_HASSETTIMEOFDAY
#undef SKALIBS_HASSIGNALFD
#undef SKALIBS_HASSPLICE
#define SKALIBS_HASSTRCASESTR
#define SKALIBS_HASSTRNLEN
#define SKALIBS_HASUINT64T
#undef SKALIBS_HASFUTIMENS
#define SKALIBS_HASFUTIMES
#define SKALIBS_HASDEVRANDOM
#endif
