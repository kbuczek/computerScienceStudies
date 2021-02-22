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

    //kolejka
    void put(int x); //dodaje element do kolejki, Enqueue
    int get();//pobiera (i usuwa) pierwszy element z kolejki, Dequeue
    int front();//zwraca element znajdujący się na początku kolejki (bez usuwania),
    void makenull();//usuwa wszystkie elementy z kolejki,
    bool empty();//sprawdza, czy kolejka jest pusta.

    void print(); // wyświetla wszystkie elementy listy
};

Lista::Lista()
{
//    cell * new_cell = new cell;
//    head = new_cell;
//    back = head;
//    head->next = NULL;
    back = head = NULL;
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

void Lista::put(int x)
{
    cell * new_cell = new cell;
    new_cell->element = x;
    new_cell->next = NULL;
    if(back != NULL)
    {
        back->next = new_cell;
        back = new_cell;
    } else {
        head = back = new_cell;
    }

}

int Lista::get()
{
    if(!empty())
    {
        cell * temp = new cell;
        temp = head;
        head = head->next;
        delete temp;
    }
}

int Lista::front()
{
    if(!empty())
    {
        return head->element;
    }
}

void Lista::makenull()
{
    cell * p = new cell;
    while(head)
    {
        p = head->next; //header rowna sie wartosci przechowywanej w wskazniku next
        delete head;
        head = p;
    }
}

bool Lista::empty()
{
    return (head == NULL);
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

////////////////////////
int main()
{
    Lista * l = new Lista();
    l->put(1);
    l->put(2);
    l->get();
    l->get();
    l->print();
    return 0;
}

