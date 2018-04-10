#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "functions.h"


int main()
{

    struct carte pachet[32],pachet_amestecat[32];
    struct player player1, player2;
    initializare_pachet(pachet);
    amestecare_pachet(pachet, pachet_amestecat);
    initializare_joc(&player1, &player2);
    joc(&player1, &player2,pachet_amestecat);

    return 0;
}
