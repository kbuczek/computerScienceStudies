#include <iostream>

template <class myType>
myType GetMax (myType a, myType b) { //funkcja ktorej mozemy podac typy liczb
	return (a>b?a:b);
}

int main() {
	int x = 1, y = 2;
	double dx = 1.1, dy = 2.1;
	std::cout << GetMax <int> (x,y) << std::endl;
	std::cout << GetMax(x,y) << std::endl;
	std::cout << GetMax(dx, dy) << std::endl;
}
