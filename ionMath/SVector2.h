#ifndef _CABBAGE_CORE_SVECTOR2_H_INCLUDED_
#define _CABBAGE_CORE_SVECTOR2_H_INCLUDED_

#include "SVector.h"


template <typename T>
class SVector2 : public SVector<T, 2, SVector2<T> >
{

public:

	T & X, & Y;

	SVector2()
		: X(Values[0]), Y(Values[1])
	{
		SVectorSimple<T, 2>::set((T) 0);
	}

	SVector2(T const in)
		: X(Values[0]), Y(Values[1])
	{
		SVectorSimple<T, 2>::set(in);
	}

	SVector2(T const x, T const y)
		: X(Values[0]), Y(Values[1])	
	{
		this->Values[0] = x;
		this->Values[1] = y;
	}

	SVector2(T const & x, T const & y, ForceReference)
		: X(x), Y(y)
	{}

	SVector2(SVector2<T> const & vec)
		: X(Values[0]), Y(Values[1])
	{
		set(vec);
	}
	
	template <typename U, int otherDimension, typename otherImplementation>
	SVector2(SVector<U, otherDimension, otherImplementation> const & vec)
		: X(Values[0]), Y(Values[1])
	{
		set(vec);
	}

	SVector2<T> & operator = (SVector2<T> const & vec)
	{
		set(vec);

		return * this;
	}
	
	template <typename U, int otherDimension, typename otherImplementation>
	SVector2<T> & operator = (SVector<U, otherDimension, otherImplementation> const & vec)
	{
		set(vec);

		return * this;
	}

};

typedef SVector2<float> SVector2f;
typedef SVector2<double> SVector2d;
typedef SVector2<int> SVector2i;
typedef SVector2<unsigned int> SVector2u;

typedef SVector2f vec2f;
typedef SVector2d vec2d;
typedef SVector2i vec2i;
typedef SVector2u vec2u;

#endif
