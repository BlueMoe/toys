#include <iostream>
#include <time.h>
#include "AOP.h"
#include <functional>
#include"Quantity.h"
using std::cout;
using std::endl;
template<class...Args>
struct used_time
{
	void Before(Args...args)
	{
		m_time = clock();
	}
	void After(Args...args)
	{
		cout << static_cast<double>(clock() - m_time) / CLOCKS_PER_SEC << endl;
	}
	clock_t m_time;
};

int main()
{
	auto f = [](int a)
	{
		cout << a << std::endl;
	};
	Invoke<used_time<int>,used_time<float> >(f, 1);
	
	Meter radius(5);
	Meter height(10);
	Kilogram mass(400);
	auto volume = PI*radius*radius*height;
	auto density = mass / volume;
	cout << volume.value() << endl;
	cout << density.value() << endl;
	
	system("pause");
	return 0;
}
