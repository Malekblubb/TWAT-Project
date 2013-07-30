/*
 * Copyright (c) 2013 Christoph Malek
 * See LICENSE for more information.
 */

#ifndef SYS_LOOKUP_H
#define SYS_LOOKUP_H


namespace TWAT
{
// main family, platform

#if defined(_WIN64) || defined(WIN64)
	#define OS_WIN 1
#elif defined(WIN32) || defined(_WIN32) || defined(__CYGWIN32__) || defined(__MINGW32__)
	#define OS_WIN 1
	#define WIN32
#endif

#if defined(__LINUX__) || defined(__linux__)
	#define OS_LINUX 1
#endif

#if defined(MACOSX) || defined(__DARWIN__) || defined(__APPLE__)
	#define OS_MAC
#endif


// arch

#if defined(WIN32) || defined(__i386__) || defined(i386) || defined(__x86__)
	#define ARCH "32"
#endif

#if defined(__amd64) || defined(__amd64__) || defined(__x86_64) || defined(__x86_64__) || defined(_M_X64) || defined(__ia64__) || defined(_M_IA64)
	#define ARCH "64"
#endif


// func-name

#if defined(__GCC__) || defined(__GNUC__)
#define FUNC __PRETTY_FUNCTION__
#endif


}
#endif // SYS_LOOKUP_H
