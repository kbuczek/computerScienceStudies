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
    unsigned counter;
public:
    Lista();    //konstruktor
    ~Lista();  //destruktor

    //stos
    void Push(int x); //dodaje element x na szczyt stosu,
    cell * Pop(); //pobiera (i usuwa) element ze szczytu stosu,
    cell * Top(); //zwraca element znajdujący się na szczycie stosu (bez usuwania),
    void Makenull(); //usuwa wszystkie elementy ze stosu,
    bool Empty(); //sprawdza, czy stos jest pusty.

    //lista jednokierunkowa
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
    counter = 0;
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

void Lista::Push(int x)
{
    Insert(x, NULL); //wstawia na poczatku listy
}

cell * Lista::Pop()
{
    cell * temp = new cell;
    temp = head->next;
    delete head;
    head = temp;
}

cell * Lista::Top()
{
    Retrieve(head);
}

void Lista::Makenull()
{
    cell * p = new cell;
    while(head)
    {
        p = head->next; //header rowna sie wartosci przechowywanej w wskazniku next
        delete head;
        head = p;
    }
}

bool Lista::Empty()
{
    if(head == NULL)
    {
        printf("Stos pusty");
    }
}

///////////////////////////////////////////////

void Lista::Insert(int x, cell * p)
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
        temp = head->next;
        delete head;
        head = temp;
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
    return p->element;
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

int main()
{
    Lista * l = new Lista();
    l->Push(4);
    l->Push(3);
    l->Push(2);
    l->Push(1);
//    l->Pop();
//    l->Pop();
//    l->Pop();
//    l->Pop();
    l->Makenull();
    l->Empty();
    l->print();
    return 0;
}

