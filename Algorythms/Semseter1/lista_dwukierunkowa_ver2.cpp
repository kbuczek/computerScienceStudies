//wersja z cwiczen. Insert wstawia element x na pozycje next komorki o wskazniku p (za komorka p)

#include <iostream>
using namespace std;

struct cell
{
    int element;
    cell * next;
    cell * prev;
};

class Lista
{
public:
    cell * head, * back; // głowa listy, wskaznik "cell'owy"
public:
    Lista();    //konstruktor
    ~Lista();  //destruktor
    void Insert(int x, cell * p); // wstawia element x na pozycję komórki o wskaźniku p
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
        p = head->next; //header rowna sie wartosci przechowywanej w wskazniku next
        delete head;
        head = p;
    }
}

void Lista::Insert(int x, cell * p)
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
    return p->element;
}

cell * Lista::Locate(int x) // zwraca wskaźnik do pierwszej komórki z elementem x
{
    cell *tmp = new cell;
    tmp = head;
    while(tmp->element != x)
    {
        tmp = tmp->next;
    }
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
        cout << temp->element <<"\t";
        temp = temp->next;
    }
}

int main()
{
    Lista * l = new Lista();
    l->Insert(2, NULL); //poczatek
    l->Insert(9, l->head);
    l->Insert(8, NULL); //koniec listy
    cell * g = l->Locate(2);
    l->Insert(3, g);
    l->Insert(1, NULL);
    cell * c = l->Locate(3);
    l->Delete(c);
    cell * k = l->Last();
    l->Insert(4, k);
    l->print();
    return 0;
}

