// cycle.h - cyclic enumerator
#pragma once
#include "enumerator.h"

namespace iter {

	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class cycle_ : public I {
		I b; // begin
	public:
		cycle_()
		{ }
		cycle_(I i)
			: I(i), b(i)
		{ }

		explicit operator bool() const
		{
			return I::operator bool();
		}
		T operator*() const
		{
			return I::operator*();
		}
		cycle_& operator++()
		{
			I::operator++();
			if (!I::operator bool())
				I::operator=(b);

			return *this;
		}
		cycle_ operator++(int)
		{
			cycle_ c(*this);

			operator++();

			return c;
		}
	};
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto cycle(I i)
	{
		return cycle_<I,T>(i);
	}

} // iter
#ifdef _DEBUG
#include "include/ensure.h"
#include "enumerator/counted.h"

inline void test_cycle()
{
	int a[] = {0,1};
	auto b = cycle(ce(a));
	auto c(b);
	b = c;
	ensure (b == c);
	ensure (*b == 0);
	ensure (*++b == 1);
	ensure (b != c);
	ensure (*++b == 0);
	ensure (*++b == 1);
	ensure (*++b == 0);
}

#endif // _DEBUG