#pragma once
/*
dimA=L��M��T��I�Ħ���N��J��,�������ٵ�ͨʽ��ʽ�е�ָ����,��,�á���Ϊ����ָ����ȫ��ָ����Ϊ�������������Ϊ�����������羫ϸ�ṹ������Ϊһ����������
���⣬���ٶȵ�����dimV=LT��1�����ٶ�a������dima=LT��2��[1]
��_Vector��ʾ����ָ��
*/
template<class T, T ...Args>
struct _Vector
{
	typedef _Vector<T, Args...> type;
};
typedef _Vector<int, 0, 0, 0, 0, 0, 0, 0>  _Const_Var;
typedef _Vector<int, 1, 0, 0, 0, 0, 0, 0>  _Length;
typedef _Vector<int, 0, 1, 0, 0, 0, 0, 0>  _Mass;
typedef _Vector<int, 0, 0, 1, 0, 0, 0, 0>  _Time;
typedef _Vector<int, 0, 0, 0, 1, 0, 0, 0>  _Electric_Current;
typedef _Vector<int, 0, 0, 0, 0, 1, 0, 0>  _Thermodynamic_Temperature;
typedef _Vector<int, 0, 0, 0, 0, 0, 1, 0>  _Amount_of_Substance;
typedef _Vector<int, 0, 0, 0, 0, 0, 0, 1>  _Luminous_Intensity;

template<class T, class Vector>
class _Physical_Quantity
{
public:
	explicit _Physical_Quantity() :_m_Value(0) {}
	explicit _Physical_Quantity(const T& val) :_m_Value(val) {}
	_Physical_Quantity<T, Vector>& operator=(const _Physical_Quantity<T, Vector>& other)
	{
		_m_Value = other._m_Value;
		return *this;
	}
	bool operator==(const _Physical_Quantity<T, Vector>& other)	const
	{
		return _m_Value == other._m_Value;
	}
	bool operator>(const _Physical_Quantity<T, Vector>& other)	const
	{
		return _m_Value > other._m_Value;
	}
	bool operator<(const _Physical_Quantity<T, Vector>& other)	const
	{
		return _m_Value < other._m_Value;
	}
	bool operator>=(const _Physical_Quantity<T, Vector>& other)	const
	{
		return _m_Value >= other._m_Value;
	}
	bool operator<=(const _Physical_Quantity<T, Vector>& other)	const
	{
		return _m_Value <= other._m_Value;
	}
	bool operator!=(const _Physical_Quantity<T, Vector>& other)	const
	{
		return _m_Value != other._m_Value;
	}
	T value() const 
	{
		return _m_Value;
	}
private:
	T _m_Value;
};

/*
�������ٱ�׼��λ����
ConstVar��ʾ��������
*/
typedef _Physical_Quantity < double, _Const_Var >					ConstVar;
typedef _Physical_Quantity < double, _Length >						Meter;
typedef _Physical_Quantity < double, _Mass>							Kilogram;
typedef _Physical_Quantity < double, _Time>							Second;
typedef _Physical_Quantity < double, _Electric_Current>				Ampere;
typedef _Physical_Quantity < double, _Thermodynamic_Temperature>	Kelvin;
typedef _Physical_Quantity < double, _Amount_of_Substance>			Mole;
typedef _Physical_Quantity < double, _Luminous_Intensity>			Candela;

/*
�������ٶ���
*/
const ConstVar PI(3.141592653);


/*
����ָ���Ӽ�����
*/
template<class T,T Vector1, T Vector2>
struct _Vector_Plus_Impl
{
	typedef _Vector_Plus_Impl<T, Vector1, Vector2> type;
	const static T _value = Vector1 + Vector2;
};

struct _Vector_Plus
{
	template<class T, T Vector1, T Vector2>
	struct _impl : _Vector_Plus_Impl<T,Vector1,Vector2>
	{
	};
};

template<class T, T Vector1, T Vector2>
struct _Vector_Minus_Impl
{
	typedef _Vector_Minus_Impl<T, Vector1, Vector2> type;
	const static T _value = Vector1 - Vector2;
};

struct _Vector_Minus
{
	template<class T, T Vector1, T Vector2>
	struct _impl : _Vector_Minus_Impl<T, Vector1, Vector2>
	{
	};
};

template<class T1, class T2, class TransFunc>
struct _Vector_Transform
{

};

/*
_Vector_Transform��ƫ�ػ�
ʹ��Vector1��Vector2 ��TransFuc::template _impl<T,Vector1,Vector2>::value...����������ӻ����
���Զ���������ٽ��г˳�����,�µ�����ָ������type
*/
template<
	template<class T,T...Args1> class Vector1,
	template<class T,T...Args2> class Vector2,
	class T, T...Args1, T...Args2,
	class TransFunc>
struct _Vector_Transform<Vector1<T, Args1...>, Vector2<T, Args2...>, TransFunc>
{
	typedef _Vector<T, TransFunc::template _impl<T, Args1, Args2>::_value...> type;
};

/*
�ӷ�
*/
template<class T, class Vector>
inline _Physical_Quantity<T, Vector> operator+(const _Physical_Quantity<T, Vector>& leftelem, const _Physical_Quantity<T, Vector>& rightelem)
{
	auto _value = leftelem.value() + rightelem.value();
	return _Physical_Quantity<T, Vector>(_value);
}

/*
����
*/
template<class T, class Vector>
inline _Physical_Quantity<T, Vector> operator-(const _Physical_Quantity<T, Vector>& leftelem, const _Physical_Quantity<T, Vector>& rightelem)
{
	auto _value = leftelem.value() - rightelem.value();
	return _Physical_Quantity<T, Vector>(_value);
}

/*
�˷�
������µ�����ָ������,��ԭ����ָ������ֱ����
*/
template<class T,class Vector1, class Vector2>
inline _Physical_Quantity<T, typename _Vector_Transform<Vector1, Vector2, _Vector_Plus>::type>
operator*(const _Physical_Quantity<T, Vector1>& leftelem, const _Physical_Quantity<T, Vector2>& rightelem)
{
	typedef _Vector_Transform<Vector1, Vector2, _Vector_Plus>::type _My_Vector;
	return _Physical_Quantity<T, _My_Vector>(leftelem.value() * rightelem.value());
}

/*
֧����������ϵ��
*/
template<class T, class Vector,class T2>
inline _Physical_Quantity<T, Vector>
operator*(const _Physical_Quantity<T, Vector>& leftelem, const T2& rightval)
{
	ConstVar right(rightval);
	return leftelem * right;
}

template<class T, class Vector,class T2>
inline _Physical_Quantity<T, Vector>
operator*(const T2& leftval, const _Physical_Quantity<T, Vector>& rightelem)
{
	ConstVar left(leftval);
	return left * rightelem;
}


/*
����
������µ�����ָ������,��ԭ����ָ������ֱ����
*/
template<class T, class Vector1, class Vector2>
inline _Physical_Quantity<T, typename _Vector_Transform<Vector1, Vector2, _Vector_Minus>::type>
operator/(const _Physical_Quantity<T, Vector1>& leftelem, const _Physical_Quantity<T, Vector2>& rightelem)
{
	typedef _Vector_Transform<Vector1, Vector2, _Vector_Minus>::type _My_Vector;
	return _Physical_Quantity<T, _My_Vector>(leftelem.value() / rightelem.value());
}

/*
֧����������ϵ��
*/
template<class T, class Vector ,class T2>
inline _Physical_Quantity<T, Vector>
operator/(const _Physical_Quantity<T, Vector>& leftelem, const T2& rightval)
{
	ConstVar right(rightval);
	return leftelem / right;
}

template<class T, class Vector, class T2>
inline _Physical_Quantity<T, Vector>
operator/(const T2& leftval, const _Physical_Quantity<T, Vector>& rightelem)
{
	ConstVar left(leftval);
	return left / rightelem;
}