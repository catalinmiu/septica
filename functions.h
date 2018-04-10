#include "constante.h"
#include <unistd.h>

void initializarePachet(struct carte pachet[])
{
    int i,valoare=7,k=0;
    for(i=0; i<8; i++)
    {
        pachet[k].valoare=valoare;
        pachet[k].simbol='C';
        k++;
        pachet[k].valoare=valoare;
        pachet[k].simbol='S';
        k++;
        pachet[k].valoare=valoare;
        pachet[k].simbol='H';
        k++;
        pachet[k].valoare=valoare;
        pachet[k].simbol='D';
        k++;
        valoare++;
    }

}

void initializareJoc(struct player *player1, struct player *player2)
{
    int i;
    player1->puncte=0;
    player2->puncte=0;
    for(i=0; i<4; i++)
    {
        player1->mana[i].valoare=-1;
        player2->mana[i].valoare=-1;
    }
}

void amestecarePachet(struct carte pachet[], struct carte pachetAmestecat[])
{
    int v[32],i,r,k=32,j;
    for(i=0; i<32; i++)
        v[i]=i;
    for(i=0; i<32; i++)
    {
        srand(time(NULL));
        r=rand() % k;

        pachetAmestecat[i] = pachet[v[r]];
        for(j=r; j<k-1; j++)
            v[j]=v[j+1];
        k--;
    }

}

struct carte extragere(int *cartiRamase, struct carte pachetAmestecat[])
{
    int r,i;
    srand(time(NULL));
    if(*cartiRamase==1)
        r=0;
    else
        r=rand()%(*cartiRamase-1);
    struct carte carte_extrasa = pachetAmestecat[r];
    for(i=r; i<*cartiRamase-1; i++)
    {
        pachetAmestecat[i]=pachetAmestecat[i+1];
    }
    (*cartiRamase)--;
    return carte_extrasa;

}

void completareMana(struct player* unplayer, int k, int *cartiRamase, struct carte pachetAmestecat[])
{

    int i, counter=0;
    for(i=0; i<4; i++)
    {
        if(unplayer->mana[i].valoare==-1 && *cartiRamase>0)
        {
            counter++;
            unplayer->mana[i]=extragere(cartiRamase, pachetAmestecat);
        }
        if(counter>=(*cartiRamase/2)&&k==1)
            break;
    }

}

void incepereMana(struct player* player1, struct player* player2, int *cartiRamase, struct carte pachetAmestecat[])
{
    completareMana(player1,1, cartiRamase, pachetAmestecat);
    completareMana(player2,0, cartiRamase, pachetAmestecat);
}

void afisareMana(struct player* unplayer, struct carte cartiMasa[], int pozitieCartePachet)
{
    int i,j=0;
    struct carte copie;
    for(i=0; i<4; i++)
    {
        copie= unplayer->mana[i];

        if(copie.valoare>0)
        {
            if(pozitieCartePachet>=1 && j==0)
            {
                printf("%c ---------------------                              ---------------------%c",NEWLINE, NEWLINE);
                if(copie.valoare<10)
                    printf("| %d)%d%c                |                              %d%c                   %c",i,unplayer->mana[i].valoare, unplayer->mana[i].simbol,cartiMasa[pozitieCartePachet-1].valoare, cartiMasa[pozitieCartePachet-1].simbol, NEWLINE);
                else
                    printf("| %d)%d%c               |                              %d%c                  %c",i,unplayer->mana[i].valoare, unplayer->mana[i].simbol,cartiMasa[pozitieCartePachet-1].valoare, cartiMasa[pozitieCartePachet-1].simbol, NEWLINE);
                printf("|                     |                            |                     |%c", NEWLINE);
                printf("|                     |                            |                     |%c", NEWLINE);
                printf("|                     |                            |                     |%c", NEWLINE);
                printf("|                     |                            |                     |%c", NEWLINE);
                printf("|                     |                            |                     |%c", NEWLINE);
                printf("|                     |                            |                     |%c", NEWLINE);
                printf(" ---------------------                              ---------------------%c", NEWLINE);
                j=1;
            }
            else
            {
                printf("\n ---------------------\n");
                if(unplayer->mana[i].valoare/10==0)
                    printf("| %d)%d%c                |%c",i,unplayer->mana[i].valoare, unplayer->mana[i].simbol, NEWLINE);
                else
                    printf("| %d)%d%c               |%c",i,unplayer->mana[i].valoare, unplayer->mana[i].simbol, NEWLINE);
                printf("|                     |%c", NEWLINE);
                printf("|                     |%c", NEWLINE);
                printf("|                     |%c", NEWLINE);
                printf("|                     |%c", NEWLINE);
                printf("|                     |%c", NEWLINE);
                printf("|                     |%c", NEWLINE);
                printf(" ---------------------%c", NEWLINE);
            }


        }
    }
}

void punereMasa(struct player* unplayer, struct carte* uncarte, int pozitieCarteJucator, int *cartiConsumate, int *pozitieCartePachet, struct carte cartiMasa[])
{
    cartiMasa[*pozitieCartePachet]=*uncarte;
    unplayer->mana[pozitieCarteJucator].valoare=-1;
    (*pozitieCartePachet)++;
    (*cartiConsumate)++;
}

void rundaPlayerVsPlayer(struct player* player1, struct player* player2, int ordine, int *cartiRamase, int *cartiConsumate, int *castigator, struct carte pachetAmestecat[])
{
    struct carte cartiMasa[32];
    int pozitieCarteJucator,c1,c2,i,puncte=0,rasp,intreaba;
    int pozitieCartePachet=0;
    struct carte uncarte; //carte in care se memoreaza cartea pe care fiecare jucator a pus-o pe masa
    if(ordine==1)
    {
        c1=1;
        c2=2;
    }
    else
    {
        c1=2;
        c2=1;
    }
    incepereMana(player1, player2, cartiRamase, pachetAmestecat);
CONTINUARE:
    intreaba=0;
    printf("%cmanaplayer%d:", NEWLINE,c1);
    afisareMana(player1, cartiMasa, pozitieCartePachet);
    printf("%c%c",NEWLINE, NEWLINE);
MAI_INCEARCA1:
    printf("Alege cartea pe care vrei sa o pui 0) 1) 2) 3)");
    scanf("%d", &pozitieCarteJucator);

    //tratarea cazului in care inputul este un numar invalid
    if(pozitieCarteJucator<0 || pozitieCarteJucator >3 || player1->mana[pozitieCarteJucator].valoare==-1 || (pozitieCartePachet>=2 && player1->mana[pozitieCarteJucator].valoare!=7 && player1->mana[pozitieCarteJucator].valoare!=cartiMasa[0].valoare))
    {
        printf("Alege un numar intre 0 si 3");
        goto MAI_INCEARCA1; //daca se introduce un numar invalid sa se reia citirea de la tastatura
    }
    uncarte = player1->mana[pozitieCarteJucator];
    if(uncarte.valoare==10 || uncarte.valoare==11)
        puncte++;
    punereMasa(player1, &uncarte, pozitieCarteJucator, cartiConsumate, &pozitieCartePachet, cartiMasa);

    printf("%cmanaplayer%d:",NEWLINE, c2);
    afisareMana(player2, cartiMasa, pozitieCartePachet);
    printf("%c%c", NEWLINE, NEWLINE);
MAI_INCEARCA2:
    printf("Alege cartea pe care vrei sa o pui 0) 1) 2) 3)");
    scanf("%d", &pozitieCarteJucator);
    if(pozitieCarteJucator<0 || pozitieCarteJucator >3 || player2->mana[pozitieCarteJucator].valoare==-1)
    {
        printf("Alege un numar intre 0 si 3");
        goto MAI_INCEARCA2;
    }
    uncarte = player2->mana[pozitieCarteJucator];
    if(uncarte.valoare==10 || uncarte.valoare==11)
        puncte++;
    punereMasa(player2, &uncarte, pozitieCarteJucator, cartiConsumate, &pozitieCartePachet, cartiMasa);
    if(uncarte.valoare==cartiMasa[0].valoare || uncarte.valoare==7)
    {
        for(i=0; i<4; i++)
        {
            if(player1->mana[i].valoare==7 || player1->mana[i].valoare==cartiMasa[0].valoare)
            {
                intreaba=1;
            }
        }
        if(intreaba==1)
        {
            printf("Player%d doriti sa continuati?0/1", c1);
            scanf("%d", &rasp);
            if(rasp==1)
                goto CONTINUARE;
            else
            {
                player2->puncte+=puncte;
                *castigator=c2;
            }
        }
        else
        {
            player2->puncte+=puncte;
            *castigator=c2;
        }


    }
    else
    {
        player1->puncte+=puncte;
        *castigator=c1;
    }
    pozitieCartePachet=0;
}

void rundaComputerVsPlayer(struct player* player1, struct player* player2, int ordine, int *cartiRamase, int *cartiConsumate, int *castigator, struct carte pachetAmestecat[])
{
    struct carte cartiMasa[32];
    int pozitieCarteJucator,c1,c2,i,puncte=0,rasp,intreaba;
    int r;
    int pozitieCartePachet=0;
    struct carte uncarte; //carte in care se memoreaza cartea pe care fiecare jucator a pus-o pe masa
    if(ordine==1)
    {
        c1=1;
        c2=2;
    }
    else
    {
        c1=2;
        c2=1;
    }
    incepereMana(player1, player2, cartiRamase, pachetAmestecat);
CONTINUARE:
    if(ordine==2)
    {
        printf("%cmanaplayer%d:", NEWLINE, c1);
        afisareMana(player1, cartiMasa, pozitieCartePachet);
        printf("%c%c",NEWLINE,NEWLINE);
    }
    intreaba=0;

MAI_INCEARCA1:
    if(ordine==2)
    {
        printf("Alege cartea pe care vrei sa o pui 0) 1) 2) 3)");
        scanf("%d", &pozitieCarteJucator);

        //tratarea cazului in care inputul este un numar invalid
        if(pozitieCarteJucator<0 || pozitieCarteJucator >3 || player1->mana[pozitieCarteJucator].valoare==-1 || (pozitieCartePachet>=2 && player1->mana[pozitieCarteJucator].valoare!=7 && player1->mana[pozitieCarteJucator].valoare!=cartiMasa[0].valoare))
        {
            printf("Alege un numar intre 0 si 3");
            goto MAI_INCEARCA1; //daca se introduce un numar invalid sa se reia citirea de la tastatura
        }
    }
    else
    {
        srand(time(NULL));
        r=rand()%4;
        if(player1->mana[r].valoare==-1 || (pozitieCartePachet>=2 && player1->mana[r].valoare!=7 && player1->mana[r].valoare!=cartiMasa[0].valoare))
        {
            goto MAI_INCEARCA1; //daca se introduce un numar invalid sa se reia citirea de la tastatura
        }
    }
    if(ordine==2)
    {
        uncarte = player1->mana[pozitieCarteJucator];
        punereMasa(player1, &uncarte, pozitieCarteJucator, cartiConsumate, &pozitieCartePachet, cartiMasa);
    }
    else
    {
        uncarte = player1->mana[r];
        punereMasa(player1, &uncarte, r, cartiConsumate, &pozitieCartePachet, cartiMasa);
    }
    if(uncarte.valoare==10 || uncarte.valoare==11)
        puncte++;

    if(ordine==1)
    {
        printf("%cmanaplayer%d:", NEWLINE,c2);
        afisareMana(player2, cartiMasa, pozitieCartePachet);
        printf("%c%c",NEWLINE,NEWLINE);
    }

MAI_INCEARCA2:
    if(ordine==1)
    {
        printf("Alege cartea pe care vrei sa o pui 0) 1) 2) 3)");
        scanf("%d", &pozitieCarteJucator);
        if(pozitieCarteJucator<0 || pozitieCarteJucator >3 || player2->mana[pozitieCarteJucator].valoare==-1)
        {
            printf("Alege un numar intre 0 si 3");
            goto MAI_INCEARCA2;
        }
    }
    else
    {
        srand(time(NULL));
        r=rand()%4;
        if(player2->mana[r].valoare==-1)
        {
            goto MAI_INCEARCA2;
        }
    }

    if(ordine==1)
    {
        uncarte = player2->mana[pozitieCarteJucator];
        punereMasa(player2, &uncarte, pozitieCarteJucator, cartiConsumate, &pozitieCartePachet, cartiMasa);
    }
    else
    {
        uncarte = player2->mana[r];
        punereMasa(player2, &uncarte, r, cartiConsumate, &pozitieCartePachet, cartiMasa);
    }
    if(uncarte.valoare==10 || uncarte.valoare==11)
        puncte++;

    if(uncarte.valoare==cartiMasa[0].valoare || uncarte.valoare==7)
    {
        for(i=0; i<4; i++)
        {
            if(player1->mana[i].valoare==7 || player1->mana[i].valoare==cartiMasa[0].valoare)
            {
                intreaba=1;
            }
        }
        if(intreaba==1)
        {
            if(ordine==2)
            {
                printf("Player%d doriti sa continuati?0/1", c1);
                scanf("%d", &rasp);
            }
            else
            {
                srand(time(NULL));
                rasp=rand()%2;
            }
            if(rasp==1)
                goto CONTINUARE;
            else
            {
                player2->puncte+=puncte;
                *castigator=c2;
            }
        }
        else
        {
            player2->puncte+=puncte;
            *castigator=c2;
        }
    }
    else
    {
        player1->puncte+=puncte;
        *castigator=c1;
    }
    pozitieCartePachet=0;
}

void joc(struct player* player1, struct player* player2, struct carte pachetAmestecat[])
{
    int cartiRamase=32, cartiConsumate=0, castigator, tipJoc;
    printf("P vs P / Comp vs Comp 0/1");
    scanf("%d", &tipJoc);
    if(tipJoc==0)
    {
        printf("Cine doriti sa inceapa?player 1 sau 2");
        scanf("%d", &castigator);
        while(cartiConsumate<32)
        {
            if(castigator==1)
                rundaPlayerVsPlayer(player1, player2, 1, &cartiRamase, &cartiConsumate, &castigator, pachetAmestecat);
            else
                rundaPlayerVsPlayer(player2, player1, 2, &cartiRamase, &cartiConsumate, &castigator, pachetAmestecat);
        }
        if(player1->puncte>player2->puncte)
        {
            printf("Player1 a castigat cu %d puncte/8 puncte", player1->puncte);
        }
        else
        {
            if(player1->puncte<player2->puncte)
            {
                printf("Player2 a castigat cu %d puncte/8 puncte", player2->puncte);
            }
            else
            {
                printf("Este egalitate. Aveti amandoi 4 puncte");
            }
        }
    }
    else
    {
        printf("Cine doriti sa inceapa?1)Calculatorul sau 2)Dumneavoastra 1/2");
        scanf("%d", &castigator);
        if(tipJoc==1)
        {
            while(cartiConsumate<32)
            {
                if(castigator==1)
                    rundaComputerVsPlayer(player1, player2, 1, &cartiRamase, &cartiConsumate, &castigator, pachetAmestecat);
                else
                    rundaComputerVsPlayer(player2, player1, 2, &cartiRamase, &cartiConsumate, &castigator, pachetAmestecat);
                    rundaComputerVsPlayer(player2, player1, 2, &cartiRamase, &cartiConsumate, &castigator, pachetAmestecat);
            }
            if(player1->puncte>player2->puncte)
            {
                printf("Calculatorul a castigat cu %d puncte/8 puncte", player1->puncte);
            }
            else
            {
                if(player1->puncte<player2->puncte)
                {
                    printf("Felicitari ati castigat cu %d puncte/8 puncte", player2->puncte);
                }
                else
                {
                    printf("Este egalitate. Aveti amandoi 4 puncte");
                }
            }
        }
    }

}
