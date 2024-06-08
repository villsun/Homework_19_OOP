#include <iostream>

using namespace std;

template <typename T>
class smart_point_unique
{
private:
	T *ptr;
	/*T operator = (const smart_point_unique<T> obj) = delete;*/
public:
	smart_point_unique(T* ptr = nullptr) : ptr(ptr) {}

	smart_point_unique(smart_point_unique<T>&& obj)
	{
		ptr = obj.ptr;
		obj.ptr = nullptr;
	}

	T& operator*()
	{
		if (ptr == nullptr)
		{
			exit(-1);
		}
		return *ptr;
	}

	~smart_point_unique()
	{
		if (ptr != nullptr)
		{
			delete ptr;
		}
	}
};

template <typename T>
class smart_point_shared
{
private:
	T* ptr;
	int* counter;

public:
	smart_point_shared(T* ptr = nullptr) : ptr(ptr), counter(new int(1)) {}

	smart_point_shared<T>& operator=(const smart_point_shared<T>& other)
	{
		if (this == &other)
			return *this;

		if (--(*counter) == 0)
		{
			delete ptr;
			delete counter;
		}

		ptr = other.ptr;
		counter = other.counter;
		(*counter)++;
		return *this;
	}

	T& operator*()
	{
		if (ptr == nullptr)
		{
			exit(-1);
		}
		return *ptr;
	}

	~smart_point_shared()
	{
		if (--(*counter) == 0)
		{
			delete ptr;
			delete counter;
		}
	}
};

int main()
{
	//smart_point_unique<int> ptr_1(new int(100));
	//*ptr_1 = 200;
	//cout << *ptr_1 << endl;

	///*smart_point_unique<int> ptr_2;
	//ptr_2 = ptr_1;
	//cout << *ptr_2 << endl;*/

	//smart_point_unique<int> ptr_2(move(ptr_1));
	//cout << *ptr_2 << endl; 

	smart_point_shared<int> ptr_1(new int(1));
	cout << *ptr_1 << endl;
	*ptr_1 = 200;

	smart_point_shared<int> ptr_2 = ptr_1;
	cout << *ptr_2 << endl;

	return 0;
}