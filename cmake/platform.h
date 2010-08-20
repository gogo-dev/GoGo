#pragma once

#cmakedefine UNIX
#cmakedefine MSVC
#cmakedefine PLATFORM_SUPPORTS_INTERLOCKEDINCREMENT64

#include <boost/cstdint.hpp>

#if defined(UNIX)
	#define SynchronizedInteger(name)	\
		volatile boost::uint64_t name

	#define SynchronizedIncrement(name)	__sync_fetch_and_add(&name, 1)

#elif defined(PLATFORM_SUPPORTS_INTERLOCKEDINCREMENT64)

	#include <windows.h>
	#define SynchronizedInteger(name) \
		volatile boost::uint64_t name

	#define SynchronizedIncrement(name) InterlockedIncrement64(&name)

#else
	#pragma message("Your platform does not support 64-bit atomics. Falling back to mutexes.")

	#include <boost/thread/mutex.hpp>

	#define SynchronizedInteger(name) \
		volatile boost::uint64_t name; \
		boost::mutex name##_mutex

	inline boost::uint64_t SynchronizedIncrementImpl(volatile boost::uint64_t& num, boost::mutex& mut)
	{
		boost::unique_lock<boost::mutex> lock(mut);
		return ++num;
	}

	#define SynchronizedIncrement(name) \
		SynchronizedIncrementImpl(name, name##_mutex)

#endif
