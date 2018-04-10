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

void amestecarePachet(struct carte pachet[], struct carte pachet_amestecat[])
{
    int v[32],i,r,k=32,j;
    for(i=0; i<32; i++)
        v[i]=i;
    for(i=0; i<32; i++)
    {
        srand(time(NULL));
        r=rand() % k;

        pachet_amestecat[i] = pachet[v[r]];
        for(j=r; j<k-1; j++)
            v[j]=v[j+1];
        k--;
    }

}

struct carte extragere(int *carti_ramase, struct carte pachet_amestecat[])
{
    int r,i;
    srand(time(NULL));
    if(*carti_ramase==1)
        r=0;
    else
        r=rand()%(*carti_ramase-1);
    struct carte carte_extrasa = pachet_amestecat[r];
    for(i=r; i<*carti_ramase-1; i++)
    {
        pachet_amestecat[i]=pachet_amestecat[i+1];
    }
    (*carti_ramase)--;
    return carte_extrasa;

}

void completareMana(struct player* unplayer, int k, int *carti_ramase, struct carte pachet_amestecat[])
{

    int i, counter=0;
    for(i=0; i<4; i++)
    {
        if(unplayer->mana[i].valoare==-1 && *carti_ramase>0)
        {
            counter++;
            unplayer->mana[i]=extragere(carti_ramase, pachet_amestecat);
        }
        if(counter>=(*carti_ramase/2)&&k==1)
            break;
    }

}

void incepere_mana(struct player* player1, struct player* player2, int *carti_ramase, struct carte pachet_amestecat[])
{
    completareMana(player1,1, carti_ramase, pachet_amestecat);
    completareMana(player2,0, carti_ramase, pachet_amestecat);
}

void afisareMana(struct player* unplayer, struct carte carti_masa[], int pozitie_carte_pachet)
{
    int i,j=0;
    struct carte copie;
    for(i=0; i<4; i++)
    {
        copie = unplayer->mana[i];

        if(copie.valoare>0)
        {
            if(pozitie_carte_pachet>=1 && j==0)
            {
                printf("\n ---------------------                              ---------------------\n");
                if(copie.valoare<10)
                    printf("| %d)%d\n                |                              %d\n                  \n",i,unplayer->mana[i].valoare, unplayer->mana[i].simbol,carti_masa[pozitie_carte_pachet-1].valoare, carti_masa[pozitie_carte_pachet-1].simbol, NEWLINE);
                else
                    printf("| %d)%d\n               |                              %d\n                  \n",i,unplayer->mana[i].valoare, unplayer->mana[i].simbol,carti_masa[pozitie_carte_pachet-1].valoare, carti_masa[pozitie_carte_pachet-1].simbol, NEWLINE);
                printf("|                     |                            |                     |\n", NEWLINE);
                printf("|                     |                            |                     |\n", NEWLINE);
                printf("|                     |                            |                     |\n", NEWLINE);
                printf("|                     |                            |                     |\n", NEWLINE);
                printf("|                     |                            |                     |\n", NEWLINE);
                printf("|                     |                            |                     |\n", NEWLINE);
                printf(" ---------------------                              ---------------------\n", NEWLINE);
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

void punereMasa(struct player* unplayer, struct carte* uncarte, int pozitie_carte_jucator, int *carti_consumate, int *pozitie_carte_pachet, struct carte carti_masa[])
{
    carti_masa[*pozitie_carte_pachet]=*uncarte;
    unplayer->mana[pozitie_carte_jucator].valoare=-1;
    (*pozitie_carte_pachet)++;
    (*carti_consumate)++;
}

void rundaPlayerVsPlayer(struct player* player1, struct player* player2, int ordine, int *carti_ramase, int *carti_consumate, int *castigator, struct carte pachet_amestecat[])
{
    struct carte carti_masa[32];
    int pozitie_carte_jucator,c1,c2,i,puncte=0,rasp,intreaba;
    int pozitie_carte_pachet=0;
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
    incepere_mana(player1, player2, carti_ramase, pachet_amestecat);
CONTINUARE:
    intreaba=0;
    printf("%cmanaplayer%d:", NEWLINE,c1);
    afisareMana(player1, carti_masa, pozitie_carte_pachet);
    printf("%c%c",NEWLINE, NEWLINE);
MAI_INCEARCA1:
    printf("Alege cartea pe care vrei sa o pui 0) 1) 2) 3)");
    scanf("%d", &pozitie_carte_jucator);

    //tratarea cazului in care inputul este un numar invalid
    if(pozitie_carte_jucator<0 || pozitie_carte_jucator >3 || player1->mana[pozitie_carte_jucator].valoare==-1 || (pozitie_carte_pachet>=2 && player1->mana[pozitie_carte_jucator].valoare!=7 && player1->mana[pozitie_carte_jucator].valoare!=carti_masa[0].valoare))
    {
        printf("Alege un numar intre 0 si 3");
        goto MAI_INCEARCA1; //daca se introduce un numar invalid sa se reia citirea de la tastatura
    }
    uncarte = player1->mana[pozitie_carte_jucator];
    if(uncarte.valoare==10 || uncarte.valoare==11)
        puncte++;
    punereMasa(player1, &uncarte, pozitie_carte_jucator, carti_consumate, &pozitie_carte_pachet, carti_masa);

    printf("%cmanaplayer%d:",NEWLINE, c2);
    afisareMana(player2, carti_masa, pozitie_carte_pachet);
    printf("%c%c", NEWLINE, NEWLINE);
MAI_INCEARCA2:
    printf("Alege cartea pe care vrei sa o pui 0) 1) 2) 3)");
    scanf("%d", &pozitie_carte_jucator);
    if(pozitie_carte_jucator<0 || pozitie_carte_jucator >3 || player2->mana[pozitie_carte_jucator].valoare==-1)
    {
        printf("Alege un numar intre 0 si 3");
        goto MAI_INCEARCA2;
    }
    uncarte = player2->mana[pozitie_carte_jucator];
    if(uncarte.valoare==10 || uncarte.valoare==11)
        puncte++;
    punereMasa(player2, &uncarte, pozitie_carte_jucator, carti_consumate, &pozitie_carte_pachet, carti_masa);
    if(uncarte.valoare==carti_masa[0].valoare || uncarte.valoare==7)
    {

        for(i=0; i<4; i++)
        {
            if(player1->mana[i].valoare==7 || player1->mana[i].valoare==carti_masa[0].valoare)
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
    pozitie_carte_pachet=0;
}

void rundaComputerVsPlayer(struct player* player1, struct player* player2, int ordine, int *carti_ramase, int *carti_consumate, int *castigator, struct carte pachet_amestecat[])
{
    struct carte carti_masa[32];
    int pozitie_carte_jucator,c1,c2,i,puncte=0,rasp,intreaba;
    int r;
    int pozitie_carte_pachet=0;
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
    incepere_mana(player1, player2, carti_ramase, pachet_amestecat);
CONTINUARE:
    if(ordine==2)
    {
        printf("%cmanaplayer%d:", NEWLINE, c1);
        afisareMana(player1, carti_masa, pozitie_carte_pachet);
        printf("%c%c",NEWLINE,NEWLINE);
    }
    intreaba=0;

MAI_INCEARCA1:
    if(ordine==2)
    {
        printf("Alege cartea pe care vrei sa o pui 0) 1) 2) 3)");
        scanf("%d", &pozitie_carte_jucator);

        //tratarea cazului in care inputul este un numar invalid
        if(pozitie_carte_jucator<0 || pozitie_carte_jucator >3 || player1->mana[pozitie_carte_jucator].valoare==-1 || (pozitie_carte_pachet>=2 && player1->mana[pozitie_carte_jucator].valoare!=7 && player1->mana[pozitie_carte_jucator].valoare!=carti_masa[0].valoare))
        {
            printf("Alege un numar intre 0 si 3");
            goto MAI_INCEARCA1; //daca se introduce un numar invalid sa se reia citirea de la tastatura
        }
    }
    else
    {
        srand(time(NULL));
        r=rand()%4;
        if(player1->mana[r].valoare==-1 || (pozitie_carte_pachet>=2 && player1->mana[r].valoare!=7 && player1->mana[r].valoare!=carti_masa[0].valoare))
        {
            goto MAI_INCEARCA1; //daca se introduce un numar invalid sa se reia citirea de la tastatura
        }
    }
    if(ordine==2)
    {
        uncarte = player1->mana[pozitie_carte_jucator];
        punereMasa(player1, &uncarte, pozitie_carte_jucator, carti_consumate, &pozitie_carte_pachet, carti_masa);
    }
    else
    {
        uncarte = player1->mana[r];
        punereMasa(player1, &uncarte, r, carti_consumate, &pozitie_carte_pachet, carti_masa);
    }
    if(uncarte.valoare==10 || uncarte.valoare==11)
        puncte++;

    if(ordine==1)
    {
        printf("%cmanaplayer%d:", NEWLINE,c2);
        afisareMana(player2, carti_masa, pozitie_carte_pachet);
        printf("%c%c",NEWLINE,NEWLINE);
    }

MAI_INCEARCA2:
    if(ordine==1)
    {
        printf("Alege cartea pe care vrei sa o pui 0) 1) 2) 3)");
        scanf("%d", &pozitie_carte_jucator);
        if(pozitie_carte_jucator<0 || pozitie_carte_jucator >3 || player2->mana[pozitie_carte_jucator].valoare==-1)
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
        uncarte = player2->mana[pozitie_carte_jucator];
        punereMasa(player2, &uncarte, pozitie_carte_jucator, carti_consumate, &pozitie_carte_pachet, carti_masa);
    }
    else
    {
        uncarte = player2->mana[r];
        punereMasa(player2, &uncarte, r, carti_consumate, &pozitie_carte_pachet, carti_masa);
    }
    if(uncarte.valoare==10 || uncarte.valoare==11)
        puncte++;

    if(uncarte.valoare==carti_masa[0].valoare || uncarte.valoare==7)
    {

        for(i=0; i<4; i++)
        {
            if(player1->mana[i].valoare==7 || player1->mana[i].valoare==carti_masa[0].valoare)
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
    pozitie_carte_pachet=0;
}

void joc(struct player* player1, struct player* player2, struct carte pachet_amestecat[])
{
    int carti_ramase=32, carti_consumate=0, castigator, tip_joc;
    printf("P vs P / Comp vs Comp 0/1");
    scanf("%d", &tip_joc);
    FILE * f;
    if(tip_joc==0)
    {
        printf("Cine doriti sa inceapa?player 1 sau 2");
        scanf("%d", &castigator);
        while(carti_consumate<32)
        {
            if(castigator==1)
                rundaPlayerVsPlayer(player1, player2, 1, &carti_ramase, &carti_consumate, &castigator, pachet_amestecat);
            else
                rundaPlayerVsPlayer(player2, player1, 2, &carti_ramase, &carti_consumate, &castigator, pachet_amestecat);
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

        if( access( "evidenta.txt", F_OK ) != -1 ) {
            f = fopen("evidenta_p_p.txt", "a");
            printf(f, "%d                                     %d", player1->puncte, player2->puncte);


        } else {
                f = fopen("evidenta_p_p.txt", "w");
                printf(f, "Player1                            Player2");
                printf(f, "%d                                     %d", player1->puncte, player2->puncte);
        }
    }
    else
    {
        printf("Cine doriti sa inceapa?1)Calculatorul sau 2)Dumneavoastra 1/2");
        scanf("%d", &castigator);
        if(tip_joc==1)
        {
            while(carti_consumate<32)
            {
                if(castigator==1)
                    rundaComputerVsPlayer(player1, player2, 1, &carti_ramase, &carti_consumate, &castigator, pachet_amestecat);
                else
                    rundaComputerVsPlayer(player2, player1, 2, &carti_ramase, &carti_consumate, &castigator, pachet_amestecat);
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
    if (f) // dacă fişier existent
        fclose(f); // închide fişier
}
