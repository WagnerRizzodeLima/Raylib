#include "raylib.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
/*
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
*/

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1360;
    const int screenHeight = 768;
    /*
    Player player;
    player.vivo = 1;
    player.vida = 40;
    */
    Vector2 posicaoPlayer = {120, 180};
    /*
    Player inimigo;
    inimigo.vivo = 1;
    inimigo.vida = 40;
    */
    Vector2 posicaoInimigo = {800, 30};    

    //No *r, *fila = NULL;

    int dano = 0, opcao, cont;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    Image image = LoadImage("Sprites/Fundo.png");
    Texture2D texturaFundo = LoadTextureFromImage(image);
    UnloadImage(image);
    
    Image playerImage = LoadImage("Sprites/foxy.png");
    Texture2D texturaPlayer = LoadTextureFromImage(playerImage);
    UnloadImage(playerImage);
    
    Image playerInimigo = LoadImage("Sprites/magko.png");
    Texture2D texturaInimigo = LoadTextureFromImage(playerInimigo);
    UnloadImage(playerInimigo);
    
    Image acoes = LoadImage("Sprites/LayoutAcoes.png");
    Texture2D texturaLayoutAcoes = LoadTextureFromImage(acoes);
    UnloadImage(acoes);

    Image listaAtaques = LoadImage("Sprites/ListaAtaques.png");
    Texture2D texturaListaAtaque = LoadTextureFromImage(listaAtaques);
    UnloadImage(listaAtaques);
    Image botaoAtaques = LoadImage("Sprites/BotaoAtaque.png");
    Texture2D texturaBotaoAtaque = LoadTextureFromImage(botaoAtaques);
    UnloadImage(botaoAtaques);

    // TODO: Load resources / Initialize variables at this point

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update variables / Implement example logic at this point
        //----------------------------------------------------------------------------------
        
        
        
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // TODO: Draw everything that requires to be drawn at this point:
            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);  // Example
            DrawTexture(texturaFundo, 0, 0, WHITE);
            DrawTexture(texturaInimigo,posicaoInimigo.x, posicaoInimigo.y, WHITE);
            DrawTexture(texturaPlayer,posicaoPlayer.x, posicaoPlayer.y, WHITE);
            DrawTexture(texturaLayoutAcoes, 0, 0, WHITE );
            DrawTexture(texturaListaAtaque, 990, 575, WHITE );
            DrawTexture(texturaBotaoAtaque, 7, 590, WHITE );
            /*
            do{
                printf("\t\nEscolha um golpe:\n");
                printf("\t1-Magma\n");
                
                printf("\t2-Fogo\n");
                printf("\t2-Terra\n");
                printf("\tComando:");
                scanf("%d", &opcao);
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
                inimigo.golpe = rand()%3;
                inserir_na_fila(&fila, inimigo.golpe);
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
            */
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded resources at this point

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}