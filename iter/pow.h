// pow.h - powers of a number
#pragma once
#include "enumerator.h"

namespace iter {

	template<class T>
	class pow_ : public enumerator_base<T*, T> {
		T t, t_; // t, t^n
	public:
		pow_(T t = T(0))
			: t(t), t_(1)
		{ }

		operator bool() const
		{
			return true;
		}
		T operator*() const
		{
			return t_;
		}
		pow_& operator++()
		{
			t_ *= t;

			return *this;
		}
		pow_ operator++(int)
		{
			pow_ p(*this);

			operator++();

			return p;
		}
	};
	template<class T>
	inline auto pow(const T& t)
	{
		return pow_<T>(t);
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"

inline void test_pow()
{
	iter::pow_<int> p(2);

	ensure (*p == 1);
	ensure (*++p == 2);
	p++;
	ensure (*p == 4);
	ensure (*++p == 8);
}

#endif // _DEBUG