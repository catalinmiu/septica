#ifndef STRUCTURES_H
#define STRUCTURES_H
struct carte
{
    int valoare; //poti sa folosesti sa iti ia doar de la 7 la 14
    char simbol;
};

struct player
{
    struct carte mana[4];
    int puncte;
};
#endif // STRUCTURES_H
