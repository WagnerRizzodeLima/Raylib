#include "raylib.h"
#include "raymath.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

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

const int screenWidth = 1360;
const int screenHeight = 768;

const Rectangle ATK1_BUTTON_RECTANGLE = {12, 560, 200, 80};
const Rectangle ATK2_BUTTON_RECTANGLE = {222, 560, 200, 80};
const Rectangle ATK3_BUTTON_RECTANGLE = {442, 560, 200, 80};
const Color BUTTON_COLOR_NORMAL = GRAY;
const Color BUTTON_COLOR_HOVER = LIGHTGRAY;
const Color BUTTON_COLOR_CLICK = BLACK;
bool jogando;
bool showPopup = false;

// Enumerador para indicar qual botão foi clicado
typedef enum { NO_BUTTON, ATK1_BUTTON, ATK2_BUTTON, ATK3_BUTTON } ButtonType;

int main(void)
{
    // Initialization
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    //--------------------------------------------------------------------------------------
    
    Player player;
    player.vivo = 1;
    player.vida = 40;
    Vector2 posicaoPlayer = {120, 180};
    
    Player inimigo;
    inimigo.vivo = 1;
    inimigo.vida = 40;
    Vector2 posicaoInimigo = {800, 30}; 
    
    No *r;
    No *fila = NULL;

    int dano = 0;
    
    //int golpeInimigo[20];
    char *status = "Escolha um golpe";

    // Adiciona valores à fila
    
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
    
    Color buttonColor1 = BUTTON_COLOR_NORMAL;
    Color buttonColor2 = BUTTON_COLOR_NORMAL;
    Color buttonColor3 = BUTTON_COLOR_NORMAL;
    
    // Inicializa a variável que irá indicar qual botão foi clicado
    ButtonType clickedButton = NO_BUTTON;

    // TODO: Load resources / Initialize variables at this point
    int framesCounter = 0;
    SetTargetFPS(60);
    fflush(stdin);
    int golpeInimigo[20],i;
    //--------------------------------------------------------------------------------------
    fflush(stdin);
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        // Update
        // Atualiza a posição do mouse a cada quadro
        SetMousePosition(GetMouseX(), GetMouseY());
        Vector2 mousePosition = GetMousePosition();
        for(int i = 0; i <= 20; i++){
            
            golpeInimigo [i]= rand()%3;
            inserir_na_fila(&fila, golpeInimigo[i]);
        }
        // Verifica se o mouse está sobre um dos botões e muda a cor do botão para indicar que ele está selecionado
        if (CheckCollisionPointRec(mousePosition, ATK1_BUTTON_RECTANGLE))
        {
            buttonColor1 = BUTTON_COLOR_HOVER;
            // Verifica se o botão foi clicado
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                clickedButton = ATK1_BUTTON;
                player.golpe = 0;
                r = remover_da_fila(&fila);
                if(player.golpe == r->valor){
                    WaitTime(1);
                    status = "Voces usaram golpes que se\n anularam!";
                }
                if(player.golpe == 0 && r->valor == 2){
                    dano = 8;
                    inimigo.vida -= dano;
                    WaitTime(1);
                    status = "Voce usou Gelo! \nMagko sofreu 8 de dano!";
                }
                if(player.golpe == 0 && r->valor == 1){
                    dano = 8;
                    player.vida -= dano;
                    WaitTime(1);
                    status = "Magko usou Lava! \nVoce sofreu 8 de dano!";
                }
                clickedButton = NO_BUTTON;
                //status = "Escolha um golpe";
            }
        }
        else
        {
            buttonColor1 = BUTTON_COLOR_NORMAL;
        }
        
        if (CheckCollisionPointRec(mousePosition, ATK2_BUTTON_RECTANGLE))
        {
            buttonColor2 = BUTTON_COLOR_HOVER;
            // Verifica se o botão foi clicado
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                clickedButton = ATK2_BUTTON;
                player.golpe = 1;
                r = remover_da_fila(&fila);
                
                if(player.golpe == r->valor){
                    WaitTime(1);
                    status = "Voces usaram golpes que se\n anularam!";
                }
                if(player.golpe == 1 && r->valor == 0){
                    dano = 8;
                    inimigo.vida -= dano;
                    WaitTime(1);
                    status = "Voce usou Agua!\nMagko sofreu 8 de dano!";
                }
                if(player.golpe == 1 && r->valor == 2){
                    dano = 8;
                    player.vida -= dano;
                    WaitTime(1);
                    status = "Magko usou Fogo!\nVoce sofreu 8 de dano!";
                }
                clickedButton = NO_BUTTON;
            }
        }
        else
        {
            buttonColor2 = BUTTON_COLOR_NORMAL;
            
        }
        
        if (CheckCollisionPointRec(mousePosition, ATK3_BUTTON_RECTANGLE))
        {
            buttonColor3 = BUTTON_COLOR_HOVER;
            // Verifica se o botão foi clicado
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                clickedButton = ATK3_BUTTON;
                player.golpe = 2;
                r = remover_da_fila(&fila);
                if(player.golpe == r->valor){
                    WaitTime(1);
                    status = "Voces usaram golpes que se\n anularam!";
                }
                if(player.golpe == 2 && r->valor == 1){
                    dano = 8;
                    inimigo.vida -= dano;
                    WaitTime(1);
                    status = "Voce usou vento!\nMagko sofreu 8 de dano!";
                }
                if(player.golpe == 2 && r->valor == 0){
                    dano = 8;
                    player.vida -= dano;
                    WaitTime(1);
                    status = "Magko usou Terra!\nVoce sofreu 8 de dano!";
                }
                clickedButton = NO_BUTTON;
            }
        }
        else
        {
            buttonColor3 = BUTTON_COLOR_NORMAL;
        }
        
        if(inimigo.vida <= 0){
        inimigo.vivo = 0;
        status = "Magko Morreu!\nVoce venceu a batalha!";
        }
        if(player.vida <= 0){
           player.vivo = 0;
           status = "Voce Morreu!";
        } 
        //----------------------------------------------------------------------------------
        // Draw
        BeginDrawing();
            
            //desenhar:
            ClearBackground(RAYWHITE);

            // TODO: Draw everything that requires to be drawn at this point:
            DrawTexture(texturaFundo, 0, 0, WHITE);
            DrawTexture(texturaInimigo,posicaoInimigo.x, posicaoInimigo.y, WHITE);
            DrawTexture(texturaPlayer,posicaoPlayer.x, posicaoPlayer.y, WHITE);
            DrawTexture(texturaLayoutAcoes, 0, 520, WHITE );
            DrawTexture(texturaListaAtaque, 990, 575, WHITE );
            
            // Renderiza os botões do menu com a cor apropriada
            DrawRectangleRec(ATK1_BUTTON_RECTANGLE, buttonColor1);
            DrawText("Gelo", ATK1_BUTTON_RECTANGLE.x+20, ATK1_BUTTON_RECTANGLE.y+20, 20, RAYWHITE);
            DrawRectangleRec(ATK2_BUTTON_RECTANGLE, buttonColor2);
            DrawText("Agua", ATK2_BUTTON_RECTANGLE.x+20, ATK2_BUTTON_RECTANGLE.y+20, 20, RAYWHITE);
            DrawRectangleRec(ATK3_BUTTON_RECTANGLE, buttonColor3);
            DrawText("Vento", ATK3_BUTTON_RECTANGLE.x+20, ATK3_BUTTON_RECTANGLE.y+20, 20, RAYWHITE);
            DrawText(status,1010, 605, 20, MAROON);
            
            
            
        EndDrawing();
        //--------------------------------------------------------------------------------
        if(inimigo.vivo == 0){
            WaitTime(2);
            return 0;
        }
        if(player.vivo == 0){
            WaitTime(2);
            return 0;
        }
    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded resources at this point
    }
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}