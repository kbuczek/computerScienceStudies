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

    /////////////////////////////////////////////////////////////////////

    void createcell(int value);
    void display();
    void insert_start(int value);
    void insert_position(int pos, int value);
    void delete_first();
    void delete_last();
    void delete_position(int pos);
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
    while(temp != NULL)
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

//////////////////////////////////////////////////////////

void Lista::createcell(int value) //dodaj na koncu
{
    cell *temp = new cell;
    temp->element = value;
    temp->next = NULL;
    if(head == NULL)
    {
        head=temp;
        back=temp;
        temp=NULL;
    }
    else
    {
        back->next = temp; //tworzymy powiaznie miedzy back, a temp
        back = temp; //temp staje sie backiem
    }
}

void Lista::display()
{
    cell *temp = new cell;
    temp = head;
    while(temp != NULL)
    {
        cout << temp->element <<"\t";
        temp = temp->next;
    }
}

void Lista::insert_start(int value)
{
    cell *temp = new cell;
    temp->element = value;
    temp->next = head; //wskaznik (*temp).next na adres obecnego head
    head = temp;
}

void Lista::insert_position(int pos, int value)
{
    cell *pre = new cell;
    cell *cur=new cell;
    cell *temp=new cell;
    cur = head;

    for(int i = 1; i < pos; i++)
    {
        pre = cur;
        cur = cur->next;
    }

    temp->element = value;
    pre->next = temp;
    temp->next = cur;
}

void Lista::delete_first()
{
    cell *temp = new cell;
    temp = head;
    head = head->next;
    delete temp;
}

void Lista::delete_last()
{
    cell *current=new cell;
    cell *previous=new cell;
    current = head;

    while(current->next != NULL)
    {
        previous = current;
        current = current->next;
    }

    back = previous;
    previous->next = NULL;
    delete current;
}

void Lista::delete_position(int pos)
{
    cell *current = new cell;
    cell *previous = new cell;
    current = head;
    for(int i = 1; i < pos; i++)
    {
        previous = current;
        current = current->next;
    }
    previous->next = current->next;
    delete current;
}

/////////////////////////////////////////////////////////////////

int main()
{
    Lista * l = new Lista();
//    l->createcell(3);
//    l->display();

    l->Insert(2, NULL);
    cell * c = l->Locate(2);
    l->Insert(3, c);
    l->Insert(1, NULL);
    l->print();
    return 0;
}

