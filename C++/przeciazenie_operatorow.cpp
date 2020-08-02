#include<stdio.h>
#include<iostream>

class Complex {
	friend Complex operator+(const Complex&, const Complex&);
	friend Complex operator*(const Complex&, const Complex&);
	public:
	Complex(){ re = 0; im = 0; };
	Complex(double a, double b){ re = a; im = b; };
	Complex operator +=(Complex &c);
	void display() const { std::cout << re << ", " << im << std::endl; }
	private:
	double re,im;
};

Complex Complex::operator +=(Complex &c){
	this->re += c.re;
	this->im += c.im;
	return *this;
}

Complex operator+(const Complex& c1, const Complex& c2){
	Complex c(c1.re + c2.re, c1.im + c2.im);
	return c;
}

Complex operator*(const Complex& c1, const Complex& c2){
	Complex c(c1.re * c2.re - c1.im * c2.im,
		c1.re * c2.im + c2.re * c1.im);	
	return c;
}

int main (void) {
	Complex c1(1, 1), c2(2, -1), c;
	c = c1 + c2; //c.re = 3, c.im = 0
	c.display();
	c = c1 * c2; //c.re = 3, c.im = 1
	c.display();
	c += c1; //c.re = 4, c.im = 2
	c.display();
}
