#ifndef _GRIND_SINGLETON_H_
#define _GRIND_SINGLETON_H_

template <class T>
struct Singleton
{
	static T *getSingleton()
	{
		static T ptr;
		return &ptr;
	}
};

#endif
