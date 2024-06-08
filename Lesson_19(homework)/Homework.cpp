#include <iostream>

using namespace std;

template <typename T>
class smart_point_unique
{
private:
	T *ptr;
	T operator = (const smart_point_unique<T> obj) = delete;
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

int main()
{
	smart_point_unique<int> ptr_1(new int(100));
	*ptr_1 = 200;
	cout << *ptr_1 << endl;

	/*smart_point_unique<int> ptr_2;
	ptr_2 = ptr_1;
	cout << *ptr_2 << endl;*/

	smart_point_unique<int> ptr_2(move(ptr_1));
	cout << *ptr_2 << endl; 
	return 0;
}