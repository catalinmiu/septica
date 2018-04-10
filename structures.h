#ifndef STRUCTURES_H
#define STRUCTURES_H
struct carte
{
    int valoare;
    char simbol;
};

struct player
{
    struct carte mana[4];
    int puncte;
};
#endif

