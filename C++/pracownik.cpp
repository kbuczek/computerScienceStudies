#include <iostream>

class Pracownik
{
	public:
	Pracownik(std::string, std::string, std::string);
	std::string get_nazwisko(); //{ return Nazwisko; }
	private:	
	std::string Nazwisko;
	std::string Imie;
	std::string PESEL;
};


Pracownik::Pracownik(std::string nazw, std::string imie, std::string pesel)
{
	Nazwisko = nazw;
	Imie = imie;
	PESEL = pesel;
}

std::string Pracownik::get_nazwisko()
{
	return Nazwisko;
}


class Pracownik_etatowy : public Pracownik
{
	public:
	Pracownik_etatowy(std::string, std::string, std::string, double);
	double wynagrodzenie();
	private:
	double Wynagrodzenie;
};

Pracownik_etatowy::Pracownik_etatowy(std::string nazw, std::string imie, std::string pesel, double wynag) : Pracownik(nazw, imie, pesel)
{
	Wynagrodzenie = wynag;
}

int main(void)
{
	Pracownik prac1("Kowalski", "Jan", "87342343");
	Pracownik_etatowy prac2("Nowak", "Maciej", "34515151", 4000);
	std::cout << "get_nazwisko: " << prac1.get_nazwisko() << std::endl;
	 
	return 0;
}
