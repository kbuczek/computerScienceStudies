#include <iostream>

template<class T>
class mypair {
	T a, b;
	public:
	mypair (T first, T second)
		{a = first; b = second;}
	T getmax();
};

template<class T>
T mypair<T>::getmax() {
	T retval;
	retval = a>b? a : b;
	return retval;
}

template <>
class mypair<char> {
	char a, b;
	public:
	mypair (const char& first, const char& second) {
		a = first; b = second;
	}
	char getmax() {
	return 0;
	}
};

int main() {
	mypair <double>p(1.1, 2.2);
	std::cout << p.getmax() << std::endl;
	mypair <int> ip(1, 2);
	std::cout << ip.getmax() << std::endl;
	mypair <char> op(1, 2);
	std::cout << ip.getmax() << std::endl;
}
