#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no{
    int valor;
    struct no *proximo;

}No;

typedef struct player{
    int vivo;
    int golpe, vida;
}Player;

void inserir_na_fila(No **fila, int num){
    No *aux, *novo = malloc(sizeof(No));
    if(novo){
        novo->valor = num;
        novo->proximo = NULL;
        if(*fila == NULL){
            *fila = novo;
        }else{
            aux = *fila;
            while(aux->proximo)
                aux = aux->proximo;
        }
    }else
    printf("\nErro ao alocar memoria");
}

No* remover_da_fila(No **fila){
    No *remover = NULL;
    if(*fila){
        remover = *fila;
        *fila = remover->proximo;
    }else{
        printf("\tFila vazia\n");
    }
    return remover;
}

/*
    Procedimento para imprimir a fila
*/
void imprimir(No *fila){
    printf("\t------- FILA --------\n\t");
    while(fila){
        printf("\n%d ", &fila->valor);
        fila = fila->proximo;
    }
    printf("\n\t------- FIM FILA --------\n");
}

int main()
{
    Player player;
    player.vivo = 1;
    player.vida = 40;

    Player inimigo;
    inimigo.vivo = 1;
    inimigo.vida = 40;

    No *r, *fila = NULL;

    int dano = 0, opcao, cont, golpeInimigo[20], i;

    // Adiciona valores à fila
    fflush(stdin);
    do{
        for(i = 0; i <= 20; i++){
            golpeInimigo[i] = rand()%3;
            inserir_na_fila(&fila, golpeInimigo[i]);
        }
        //imprimir(fila);
        printf("\t\nEscolha um golpe:\n");
        printf("\t1-Magma\n");
        printf("\t2-Fogo\n");
        printf("\t2-Terra\n");
        printf("\tComando:");
        scanf("%d", &opcao);
        //r = remover_da_fila(&fila);
        switch(opcao){
            case 1:
                player.golpe = 0;
                break;
            case 2:
                player.golpe = 1;
                break;
            case 3:
                player.golpe = 2;
                break;
            default:
                if(opcao != 0){
                    printf("\nOpcao invalida!\n");
                }
        }
        r = remover_da_fila(&fila);
        if(player.golpe == r->valor){
            printf("\t\nOs golpes se anularam!");
        }else if(player.golpe == 0 && r->valor == 2){
            dano = 8;
            inimigo.vida -= dano;
            printf("\t\nO inimigo sofreu: %i de dano", dano);
            printf("\t\nVida Inimigo %i", inimigo.vida);
            printf("\t\nVida Player %i", player.vida);
        }else if(player.golpe == 0 && r->valor == 1){
            dano = 8;
            player.vida -= dano;
            printf("\t\nO player sofreu: %i de dano", dano);
            printf("\t\nVida Inimigo %i", inimigo.vida);
            printf("\rt\nVida Player %i", player.vida);
        }else if(player.golpe == 1 && r->valor == 0){
            dano = 8;
            inimigo.vida -= dano;
            printf("\t\nO inimigo sofreu: %i de dano", dano);
            printf("\t\nVida Inimigo %i", inimigo.vida);
            printf("\rt\nVida Player %i", player.vida);
        }else if(player.golpe == 1 && r->valor == 2){
            dano = 8;
            player.vida -= dano;
            printf("\t\nO player sofreu: %i de dano", dano);
            printf("\t\nVida Inimigo %i", inimigo.vida);
            printf("\rt\nVida Player %i", player.vida);
        }else if(player.golpe == 2 && r->valor == 1){
            dano = 8;
            inimigo.vida -= dano;
            printf("\t\nO inimigo sofreu: %i de dano", dano);
            printf("\t\nVida Inimigo %i", inimigo.vida);
            printf("\rt\nVida Player %i", player.vida);
        }else if(player.golpe == 2 && r->valor == 0){
            dano = 8;
            player.vida -= dano;
            printf("\t\nO player sofreu: %i de dano", dano);
            printf("\t\nVida Inimigo %i", inimigo.vida);
            printf("\rt\nVida Player %i", player.vida);
        }
        if(inimigo.vida <= 0){
            inimigo.vivo = 0;
            //return 0;
        }
        if(player.vida <= 0){
           player.vivo = 0;
           //return 0;
        }
  }while(inimigo.vivo!=0);
}
