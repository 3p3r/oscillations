#ifndef INDEXED_SINGLETON_H_
#define INDEXED_SINGLETON_H_

/*!
 * \struct ProxyStorage
 * \brief A proxy type that generates a new symbol in the type table if
 * passed different integers. Useful for compile-time static naming.
 * \note Proxy produces the same type for the same integer.
 */
template<typename T, int index>
struct ProxyStorage
{
	enum { mIndex = index };
	T mStorage;
};

/*!
 * \struct Singleton
 * \brief Convenience to wrap a singleton object (and even multiple of
 * them at the same time).
 *
 * \example
 *     Singleton<YourClass>::get() //equivalent to index 0
 *     Singleton<YourClass, 1>::get()
 *     Singleton<YourClass, 2>::get()
 *
 * \note Singleton<T,i>::get() is thread safe
 */
template<typename T, int i = 0>
struct Singleton
{
	// get the indexed instance of the singleton.
	static T& get()
	{
		// static allocation is thread-safe. no need for synchronizing.
		static ProxyStorage<T, i> instance;
		return instance.mStorage;
	}

	// get the index of the current instance.
	static int index()
	{
		return ProxyStorage<T, i>::mIndex;
	}
};

/*!
 * \name IndexedSingleton
 * \note Alias to Singleton
 * \see Singleton
 */
template<typename T, int index = 0>
using IndexedSingleton = Singleton < T, index > ;

#endif //!INDEXED_SINGLETON_H_
