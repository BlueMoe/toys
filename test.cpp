#include <iostream>
#include <time.h>
#include "AOP.h"
#include <functional>
template<class...Args>
struct used_time
{
	void Before(Args...args)
	{
		m_time = clock();
	}
	void After(Args...args)
	{
		std::cout << static_cast<double>(clock() - m_time) / CLOCKS_PER_SEC << std::endl;
	}
	clock_t m_time;
};

struct JustBefore
{
	void Before(int, int, int)
	{
		std::cout << 11;
	}
};

struct JustAfter
{
	void After(int, int, int)
	{
		std::cout << 22;
	}
};

int main()
{

	auto f = [](int a)
	{
		std::cout << a << std::endl;
	};

	Invoke<used_time<int>,used_time<float> >(f, 1);
// 	Invoke<JustBefore>(f, 1, 1, 1);
// 	Invoke<JustAfter>(f, 1, 1, 1);
	system("pause");
	return 0;
}