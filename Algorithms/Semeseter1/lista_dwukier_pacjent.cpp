#include <iostream>
using namespace std;

class Pacjent
{
private:
    string Imie;
    string Nazwisko;
    string PESEL;
    string Godzina;
public:
    Pacjent(string, string, string, string);
    Pacjent();
    string get_pesel();
    void print_imie_nazwisko();
    void print();
};

Pacjent::Pacjent()
{
    Imie = "";
    Nazwisko = "";
    PESEL = "";
    Godzina = "";
}

Pacjent::Pacjent(string imie, string nazwisko, string pesel, string godzina)
{
    Imie = imie;
    Nazwisko = nazwisko;
    PESEL = pesel;
    Godzina = godzina;
}

string Pacjent::get_pesel()
{
    return PESEL;
}

void Pacjent::print_imie_nazwisko()
{
    cout << "Imie: " << Imie << endl;
    cout << "Nazwisko: " << Nazwisko << endl;
}

void Pacjent::print() {
    cout << "Imie: " << Imie << endl;
    cout << "Nazwisko: " << Nazwisko << endl;
    cout << "PESEL: " << PESEL << endl;
    cout << "Godziny: " << Godzina << endl << endl;
}

struct cell
{
    Pacjent element;
    cell * next;
    cell * prev;
};

class Lista
{
private:
    cell * head, * back; // głowa listy, wskaznik "cell'owy"
public:
    Lista();    //konstruktor
    ~Lista();  //destruktor
    void Insert(Pacjent x, cell * p); // wstawia element x na pozycję komórki o wskaźniku p
    // (lub w przypadku pustej listy tworzy komórkę z elementem x w miejscu głowy listy)
    void Delete(cell * p); // usuwa komórkę z pozycji next komórki o wskaźniku p
    int Retrieve(cell * p); // zwraca element komórki o wskaźniku p
    cell * Locate(string); // zwraca wskaźnik do pierwszej komórki z elementem x
    cell * First(); // zwraca wskaźnik do pierwszej komórki na liście
    cell * Next(cell * p); // zwraca wskaźnik do kolejnej komórki po komórce o wskaźniku p
    cell * Previous(cell * p); // zwraca wskaźnik do komórki poprzedzającej komórkę o wskaźniku p - tylko dla listy dwukierunkowej
    cell * Last(); // zwraca wskaźnik do ostatniej komórki na liście
    void print(); // wyświetla wszystkie elementy listy
};

Lista::Lista()
{
    head = back = NULL;
}

Lista::~Lista()
{
    cell * p;
    while(head)
    {
        p = head->next; //header rowna sie wartosci przechowywanej w wskazniku next
        delete head;
        head = p;
    }
}

void Lista::Insert(Pacjent x, cell * p)
{
    cell * new_cell = new cell; //wskaznik *cell'owy na strukture
    cell * tmp;

        if(p == NULL) //poczatek listy
        {
            new_cell->element = x;
            new_cell->next = head;
            new_cell->prev = NULL;
            if(new_cell->next != NULL)
            {
                new_cell->next->prev = new_cell;
            }
            head = new_cell;
        }
        else
        {
            tmp = p->next;
            p->next = new_cell;
            new_cell->element = x;
            new_cell->next = tmp;
            new_cell->prev = p;
            if(new_cell->next != NULL)
            {
                tmp->prev = new_cell;
            }
        }
}

void Lista::Delete(cell *p) // usuwa komórkę z pozycji komórki o wskaźniku p
{
    if(head != NULL)
    {
        if(p->prev != NULL) p->prev->next = p->next;
        if(p->next != NULL) p->next->prev = p->prev;
        if(p == head) head = p->next;
        delete p;
    }
}

int Lista::Retrieve(cell * p) // zwraca element komórki o wskaźniku p
{
    p->element.print();
}

cell * Lista::Locate(string pesel) // zwraca wskaźnik do pierwszej komórki z elementem x
{
    cell *tmp = new cell;
    tmp = head;

    while(tmp->element.get_pesel() != pesel)
    {
        tmp = tmp->next;
    }
    cout << "Znaleziono osobe: " << endl;
    tmp->element.print();

    if(tmp->prev != NULL)
    {
        cout << "Osoba poprzedzajaca: " << endl;
        tmp->prev->element.print_imie_nazwisko();
    }
    else
    {
        cout << "Osoba jest na koncu kolejki" << endl;
    }

    cout << endl;
    return tmp;
}

cell * Lista::First() // zwraca wskaźnik do pierwszej komórki na liście
{
    return head;
}

cell * Lista::Next(cell * p) // zwraca wskaźnik do kolejnej komórki po komórce o wskaźniku p
{
    return p->next;
}

cell * Lista::Previous(cell *p) // zwraca wskaźnik do komórki poprzedzającej komórkę o wskaźniku p
{
    return p->prev;
}

cell * Lista::Last() // zwraca wskaźnik do ostatniej komórki na liście
{
    cell *temp = new cell;
    temp = head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    back = temp;
    return back;
}


void Lista::print()
{
    cell *temp = new cell;
    temp = head;
    while(temp != NULL)
    {
        temp->element.print();
        temp = temp->next;
    }
}

int main()
{
//    Lista * l = new Lista();
//    l->Insert(2, NULL); //poczatek
////    l->Insert(9, l->head);
//    l->Insert(8, NULL); //koniec listy
//    cell * g = l->Locate(2);
//    l->Insert(3, g);
//    l->Insert(1, NULL);
//    cell * c = l->Locate(3);
//    l->Delete(c);
//    cell * k = l->Last();
//    l->Insert(4, k);
//    l->print();
    Lista * l = new Lista();
    Pacjent pacjent1("Maciej", "Nowak", "98009800", "18:00");
    l->Insert(pacjent1, NULL);
    Pacjent pacjent2("Irena", "Olechowska", "99009900", "19:00");
    l->Insert(pacjent2, NULL);
    Pacjent pacjent3("Krzysztof", "Babel", "10001000", "20:00");
    cell * c = l->Last();
    l->Insert(pacjent3, c);
    cell * g = l->Locate("98009800");
    cell * d = l->Locate("99009900");
    l->Delete(d);
    l->print();
    return 0;
}