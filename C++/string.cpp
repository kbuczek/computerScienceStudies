#include <stdio.h>
#include <string.h>

class string {
	public:
		string(const char *);
		string(const string& src);
		~string();
	private:
		char* str; int dlg;
};

string::string(const char *src) { //konstruktor 
	dlg = strlen(src);
	str = new char[dlg + 1]; //blok pamięci
	strcpy(str, src);
	printf("Jestem konstruktorem %s\n", str);
}

string::string(const string& src) { //konstruktor kopiujący
	dlg = src.dlg;
	str = new char[dlg + 1]; //blok pamięci
	strcpy(str, src.str);
	printf("Jestem konstruktorem kopiującym %s\n", str);
}

string::~string() { //destruktor
	printf("Jestem destruktorem %s\n", str);
	delete str;
}

int main(void) {
	string s1("tresc");
	string s2 = s1; //kopiowanie obiektu s1 do s2
	string s3(s1); //kopiowanie obiektu s1 do s3
}
