#include <iostream>
#include <functional>

using std::cout;
using std::endl;

void heapSort(int* array, int Len, std::function<bool(int, int)> op);
void buildHeap(int *array, int Len, std::function<bool(int, int)> op);
void adjustHeap(int* array, int i, int Len, std::function<bool(int, int)> op);
void adjustHeap3Nodes(int* array, int self, int left, int right, int Len, std::function<bool(int, int)> op);
void adjustHeap2Nodes(int* array, int self, int left, int Len, std::function<bool(int, int)> op);
void swap(int* array, int i, int j);

void heapSort(int* array, int Len, std::function<bool(int,int)> op)
{
	buildHeap(array, Len ,op);

	for (int i = Len - 1; i >= 0; i--)
	{
		swap(array, 0, i);
		adjustHeap(array, 0, i, op);
	}

}

void buildHeap(int *array, int Len, std::function<bool(int, int)> op)
{
	for (int i = Len / 2; i >= 0; i--)
	{
		adjustHeap(array, i, Len, op);
	}
}

void adjustHeap(int* array, int i, int Len, std::function<bool(int, int)> op)
{
	int left = i * 2 + 1;
	int right = i * 2 + 2;

	if (left > Len - 1) return;

	bool hasRightChild = true;
	if (right > Len - 1)
	{
		hasRightChild = false;
	}

	if (hasRightChild)
	{
		adjustHeap3Nodes(array, i, left, right, Len, op);
	}
	else
	{
		adjustHeap2Nodes(array, i, left, Len, op);
	}


}

void adjustHeap3Nodes(int* array, int self, int left, int right, int Len, std::function<bool(int, int)> op)
{
	if (op(array[self], array[left]) && op(array[self], array[right]))
	{
		return;
	}
	else
	{
		if (op(array[left], array[right]))
		{
			swap(array, left, self);
			adjustHeap(array, left, Len, op);
		}
		else
		{
			swap(array, right, self);
			adjustHeap(array, right, Len, op);
		}
	}
}

void adjustHeap2Nodes(int* array, int self, int left, int Len, std::function<bool(int, int)> op)
{
	if (!op(array[self], array[left]))
	{
		swap(array, self, left);
		adjustHeap(array, left, Len, op);
	}
}

void swap(int* array, int i, int j)
{
	int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}


int main()
{
	int* array =  new int [10]{ 5, 300, 25, 666, 32, 435, 10, 1234, 2626, 1873 };
	heapSort(array,10 ,std::less<int>());
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	delete array;
	system("pause");
}