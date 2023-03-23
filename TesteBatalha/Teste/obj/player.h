#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

typedef struct bixinho{
    int vida;
    bool vivo;
    int poder[3];
}Bixinho;

void atacar(Bixinho player, inimigo){
    int poder;
    printf("Digite um numero de 0 a 3:");
    scanf("%d", &poder);
    switch(poder){
    case 0:
        player.poder[0] = 0;
        inimigo.poder[0] = rand()%3;
        if(player.poder[0] == inimigo.poder[0]){

        }
    break;
    case 1:
        player.poder[1] = 1;
        inimigo.poder[1] = rand()%3;
    break;
    case 2:
        player.poder[2] = 2;
        inimigo.poder[2] = rand()%3;
    break;
    case 3:
        player.poder[3] = 3;
        inimigo.poder[3] = rand()%3;
    break;
    default:
        printf("numero invalido!");
    }

    if()


}

#endif // PLAYER_H_INCLUDED
