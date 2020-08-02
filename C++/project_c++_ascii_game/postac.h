#ifndef PROJEKT_C_EXTRA_H
#define PROJEKT_C_EXTRA_H


class Postac {

protected:
    int level;
    int health;
    int attack;
    int defense;
    int experience;
    int x;
    int y;
public:
    Postac();
    Postac(int level, int health, int attack, int defense, int experience);
    //setter
    void setPosition(int x, int y);
    //getter
    void getPosition(int &x, int &y);
    //funkcja wirtualna
    virtual int takeDamage(int) = 0;
};


#endif //PROJEKT_C_EXTRA_H
