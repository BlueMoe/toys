#pragma once

class My__NonCopyable__Define
{
public:
	My__NonCopyable__Define() = default;
	~My__NonCopyable__Define() = default;
	My__NonCopyable__Define(const My__NonCopyable__Define&) = delete;
	My__NonCopyable__Define& operator=(const My__NonCopyable__Define&) = delete;
};

#define HAS_MEMBER(member) \
template<class T,class...Args> struct has_member_##member\
{\
private:\
	template<class U>static auto Check(int) -> decltype(std::declval<U>().member(std::declval<Args>()...),std::true_type());\
	template<class U>static std::false_type Check(...);\
public:\
	enum{value = std::is_same<decltype(Check<T>(0)),std::true_type>::value};\
};\


HAS_MEMBER(Before)
HAS_MEMBER(After)
HAS_MEMBER(Foo)

template<class Func,class...Args>
class Aspect : public My__NonCopyable__Define
{
public:
	Aspect(Func&& f) : m_func(std::forward<Func>(f))
	{
	}

	template<class T>
	typename std::enable_if<has_member_Before<T,Args...>::value&&
		has_member_After<T, Args...>::value>::type Invoke(Args&&...args, T&& aspect)
	{
		aspect.Before(std::forward<Args>(args)...);
		m_func(std::forward<Args>(args)...);
		aspect.After(std::forward<Args>(args)...);
	}

	template<class T>
	typename std::enable_if<has_member_Before<T, Args...>::value&&
		!has_member_After<T, Args...>::value>::type Invoke(Args&&...args, T&& aspect)
	{
		aspect.Before(std::forward<Args>(args)...);
		m_func(std::forward<Args>(args)...);
	}

	template<class T>
	typename std::enable_if<!has_member_Before<T, Args...>::value&&
		has_member_After<T, Args...>::value>::type Invoke(Args&&...args, T&& aspect)
	{
		m_func(std::forward<Args>(args)...);
		aspect.After(std::forward<Args>(args)...);
	}

	template<class Head,class...Tail>
	void Invoke(Args&&...args,Head&& headaspect,Tail&&...tailaspect)
	{
		headaspect.Before(std::forward<Args>(args)...);
		Invoke(std::forward<Args>(args)..., std::forward<Tail>(tailaspect)...);
		headaspect.After(std::forward<Args>(args)...);
	}

private:
	Func m_func;
};

template<class T> using identity_t = T;

template<class...AP,class...Args,class Func>
void Invoke(Func&&f, Args&&...args)
{
	Aspect<Func, Args...> asp(std::forward<Func>(f));
	asp.Invoke(std::forward<Args>(args)..., identity_t<AP>()...);
}

