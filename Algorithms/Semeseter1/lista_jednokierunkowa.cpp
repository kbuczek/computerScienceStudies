#include <iostream>
using namespace std;

struct cell
{
    int element;
    cell * next;
};

class Lista
{
protected:
    cell * head, * back; // głowa listy, wskaznik "cell'owy"
public:
    Lista();    //konstruktor
    ~Lista();  //destruktor
    void Insert(int x, cell * p); // wstawia element x na pozycję next komórki o wskaźniku p
    // (lub w przypadku pustej listy tworzy komórkę z elementem x w miejscu głowy listy)
    void Delete(cell * p); // usuwa komórkę z pozycji next komórki o wskaźniku p
    int Retrieve(cell * p); // zwraca element komórki o wskaźniku p
    cell * Locate(int x); // zwraca wskaźnik do pierwszej komórki z elementem x
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
        p = head->next; //head rowna sie wartosci przechowywanej w wskazniku next
        delete head;
        head = p;
    }
}

void Lista::Insert(int x, cell * p) // wstawia element x na pozycję next komórki o wskaźniku p
{
    cell * new_cell = new cell; //wskaznik *cell'owy na strukture
    new_cell->element = x;

    if(p == NULL)
    {
        new_cell->next = head;
        head = new_cell;
    }
    else
    {
        new_cell->next = p->next;
        p->next = new_cell;
    }
}

void Lista::Delete(cell *p) // usuwa komórkę z pozycji next komórki o wskaźniku p
{
    cell *temp = new cell;
    if(p == NULL)
    {
        return;
    }
    if(p->next == NULL)
    {
        return;
    }
    temp = p->next->next;
    delete p->next;
    p->next = temp;
}

int Lista::Retrieve(cell * p) // zwraca element komórki o wskaźniku p
{
    if(p->next != NULL)
    {
        return p->next->element;
    }
}

cell * Lista::Locate(int x) // zwraca wskaźnik do pierwszej komórki z elementem x
{
    cell *temp = new cell;
    temp = head;
    while(temp->element != x)
    {
        temp = temp->next;
    }
    return temp;
}

cell * Lista::First() // zwraca wskaźnik do pierwszej komórki na liście
{
    return head;
}

cell * Lista::Next(cell * p) // zwraca wskaźnik do kolejnej komórki po komórce o wskaźniku p
{
    return p->next;
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
        cout << temp->element <<"\t";
        temp = temp->next;
    }
}

////////////////////////////////////////////////////////////////////////

int main()
{
    Lista * l = new Lista();
    l->Insert(2, NULL);
    cell * c = l->Locate(2);
    l->Insert(3, c);

    l->Insert(1, NULL);
    cell * k = l->Last();
    l->Insert(4, k);
    l->print();
    return 0;
}

