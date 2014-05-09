#ifndef _NEPGEAR_THREAD_H_
#define _NEPGEAR_THREAD_H_

#include <tinythread.h>

// Nepgear/threads.h
namespace Nepgear
{
	typedef tthread::thread Thread;
	typedef tthread::mutex Mutex;

	/* A bit ugly. I wish there was a nicer way to alias a template, I might
	* just change how this bit of API works later to be more specific. */
	// ideal: template<typename T> tthread::lock_guard<T> LockGuard2;
	template<typename T>
	struct LockGuard
	{
		typedef tthread::lock_guard<T> type;
	};
}

#endif
