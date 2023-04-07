#include <raylib.h>
#include "raymath.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

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
        printf("/tFila vazia\n");
    }
    return remover;
}

const int screenWidth = 1366;
const int screenHeight = 768;

const Rectangle ATK1_BUTTON_RECTANGLE = {5, 600, 200, 80};
const Rectangle ATK2_BUTTON_RECTANGLE = {275, 600, 200, 80};
const Rectangle ATK3_BUTTON_RECTANGLE = {545, 600, 180, 80};
const Color BUTTON_COLOR_NORMAL = GRAY;
const Color BUTTON_COLOR_HOVER = LIGHTGRAY;
const Color BUTTON_COLOR_CLICK = BLACK;
bool jogando;
bool showPopup = false;

// Enumerador para indicar qual botão foi clicado
typedef enum { NO_BUTTON, ATK1_BUTTON, ATK2_BUTTON, ATK3_BUTTON } ButtonType;

int main(void)
{
    // Inicializa a janela
    const int screenWidth = 1366;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "Menu Principal");

    // Carrega a imagem de background
    Texture2D background = LoadTexture("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/Fundo Tela Inicial (1).png");
    
    // Carrega as imagens
    Texture2D startButtonBackground = LoadTexture("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/Botao.png");
    Texture2D aboutButtonBackground = LoadTexture("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/Botao.png");
    Texture2D exitButtonBackground = LoadTexture("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/Botao.png");
    Texture2D character = LoadTexture("C:/raylib/raylib/examples/textures/resources/scarfy_run.gif");
    Texture2D pauseButton = LoadTexture("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/ConfButton.png");
    Texture2D pauseButtonBG = LoadTexture("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/Borda Menu.png");
    Rectangle pauseButtonRec = { screenWidth - pauseButton.width - 10, 10, pauseButton.width, pauseButton.height };
    Color pauseButtonColor = WHITE;
    Image image = LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/Fundo de batalha.png");
    Texture2D texturaFundo = LoadTextureFromImage(image);
    UnloadImage(image);
    
    Image playerImage = LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/foxy.png");
    Texture2D texturaPlayer = LoadTextureFromImage(playerImage);
    UnloadImage(playerImage);
    
    Image playerInimigo = LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/magko.png");
    Texture2D texturaInimigo = LoadTextureFromImage(playerInimigo);
    UnloadImage(playerInimigo);
    
    Image acoes = LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/Borda Painel de ataque.png");
    Texture2D texturaLayoutAcoes = LoadTextureFromImage(acoes);
    UnloadImage(acoes);

    Image atk1= LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/Botao2.png");
    Texture2D texturaAtk1 = LoadTextureFromImage(atk1);
    UnloadImage(atk1);
    
    Image atk2= LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/Botao1.png");
    Texture2D texturaAtk2 = LoadTextureFromImage(atk2);
    UnloadImage(atk2);
    
    Image atk3= LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/BotaoAr.png");
    Texture2D texturaAtk3 = LoadTextureFromImage(atk3);
    UnloadImage(atk3);
    
    Image painelAcoes = LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/Tela.png");
    Texture2D texturaTelaInfo = LoadTextureFromImage(painelAcoes);
    UnloadImage(painelAcoes);
    
    Image painel = LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/PainelAtaques.png");
    Texture2D texturaPainelAtaques = LoadTextureFromImage(painel);
    UnloadImage(painel);
    
    Image imgInimigo1 = LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/VidaVaziaHpInimigo.png");
    Texture2D texturaInimigo1 = LoadTextureFromImage(imgInimigo1);
    UnloadImage(imgInimigo1);
    
    Image imgInimigo2 = LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/fundoHpInimigo.png");
    Texture2D texturaInimigo2 = LoadTextureFromImage(imgInimigo2);
    UnloadImage(imgInimigo2);
    
    Image imgInimigo3 = LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/VidaHpInimigo.png");
    Texture2D texturaInimigo3 = LoadTextureFromImage(imgInimigo3);
    UnloadImage(imgInimigo3);
    
    Image imgPlayer1 = LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/VidaVaziaPlayer.png");
    Texture2D texturaPlayer1 = LoadTextureFromImage(imgPlayer1);
    UnloadImage(imgPlayer1);
    
    Image imgPlayer2 = LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/fundoHpPlayer.png");
    Texture2D texturaPlayer2 = LoadTextureFromImage(imgPlayer2);
    UnloadImage(imgPlayer2);
    
    Image imgPlayer3 = LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/FundoPlayer.png");
    Texture2D texturaPlayer3 = LoadTextureFromImage(imgPlayer3);
    UnloadImage(imgPlayer3);
    
    // Carrega a imagem da seta
    Texture2D arrow = LoadTexture("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Imagens/Seta.png");

    // Define as cores utilizadas
    Color buttonColor1 = BUTTON_COLOR_NORMAL;
    Color buttonColor2 = BUTTON_COLOR_NORMAL;
    Color buttonColor3 = BUTTON_COLOR_NORMAL;
  
    Color white = (Color){ 255, 255, 255, 255 };

    // Define as dimensões e posição dos botões
    const int buttonWidth = 330;
    const int buttonHeight = 125;
    const int buttonPadding = 5;
    const int buttonX = 60;
    const int buttonY = 480;
    bool jogando = true;
    bool showPopup = false;
    
     // Renderiza o Pop-Up de pausa
     Rectangle pauseMenuRec = { screenWidth / 2 - 200, screenHeight / 2 - 100, 400, 200 };
     
     bool pauseMenuExit = false;
    
    // Definindo o estado do jogo
    enum GameState { MENU, LOADING, PLAYING, ABOUT, EXIT};
    int gameState = MENU;
    
    // Define a posição inicial do personagem com uma margem de 50 pixels à esquerda
    float characterPositionX = -character.width / 2 + 50;
    
    // Define a velocidade do personagem em pixels por segundo
    float characterSpeed = 400;
    
    // Definindo as propriedades da barra de loading
    Rectangle loadingBar = { screenWidth/2 - 700, screenHeight/2 + 200, 1380, 20 };
    float loadingProgress = 0;
    
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
    
    Color corTexto = WHITE;
    
    //int golpeInimigo[20];
    char *status = "Escolha um golpe";
    char *vida;
    // Adiciona valores à fila

    
    // Inicializa a variável que irá indicar qual botão foi clicado
    ButtonType clickedButton = NO_BUTTON;

    // TODO: Load resources / Initialize variables at this point
    int framesCounter = 0;
    fflush(stdin);
    int golpeInimigo[20],i;
    //--------------------------------------------------------------------------------------
    fflush(stdin);
    
    SetTargetFPS(60);
    // Loop principal
    while (!WindowShouldClose())
    {

        // Atualizando o estado do jogo
        switch (gameState)
        {
             case PLAYING:{
                // Código para iniciar o jogo
               
                    // Limpa a tela
                 ClearBackground(RAYWHITE);

                 // Loop do jogo7
                 while (jogando)
                 {
                     // Verifica se o botão de pausa foi clicado
                     if (CheckCollisionPointRec(GetMousePosition(), pauseButtonRec))
                     {
                         pauseButtonColor = GRAY;
               
                         if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                         {
                            
               
                             while (!pauseMenuExit)
                             {
                                 // Verifica se o botão de retorno foi clicado
                                 if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){pauseMenuRec.x + 50, pauseMenuRec.y + 100, 100, 50}))
                                 {
                                     pauseButtonColor = WHITE;
                                    
               
                                     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                                     {
                                         pauseMenuExit = true;
                                     }
                                 }
                                 else if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){pauseMenuRec.x + 250, pauseMenuRec.y + 100, 100, 50}))
                                 {
                                     pauseButtonColor = WHITE;
                                     
               
                                     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                                     {
                                         UnloadTexture(background);
                                         UnloadTexture(startButtonBackground);
                                         UnloadTexture(aboutButtonBackground);
                                         UnloadTexture(exitButtonBackground);
                                         UnloadTexture(pauseButton);
                                         UnloadTexture(character);
                                         UnloadTexture(arrow);
                                         
                                         UnloadTexture(texturaAtk1);
                                         UnloadTexture(texturaAtk2);
                                         UnloadTexture(texturaAtk3);
                                         UnloadTexture(texturaFundo);
                                         UnloadTexture(texturaInimigo);
                                         UnloadTexture(texturaInimigo1);
                                         UnloadTexture(texturaInimigo2);
                                         UnloadTexture(texturaInimigo3);
                                         UnloadTexture(texturaLayoutAcoes);
                                         UnloadTexture(texturaPainelAtaques);
                                         UnloadTexture(texturaPlayer);
                                         UnloadTexture(texturaPlayer1);
                                         UnloadTexture(texturaPlayer2);
                                         UnloadTexture(texturaPlayer3);
                                         UnloadTexture(texturaTelaInfo);
                                         pauseMenuExit = false;
                                         jogando = false;
                                         return main();
                                     }
                                 }
                                 else
                                 {
                                     pauseButtonColor = WHITE;
                                     
                                 }
                                 // Renderiza o Pop-Up de pausa
                                 BeginDrawing();
                                 DrawTexture(pauseButton, pauseButtonRec.x, pauseButtonRec.y, pauseButtonColor);
                                 DrawTexture(pauseButtonBG, 390, 170, RAYWHITE);
                                 DrawText("Pause menu", pauseMenuRec.x + 90, pauseMenuRec.y + 30, 40, RAYWHITE);
                                 DrawText("Return", pauseMenuRec.x + 70, pauseMenuRec.y + 110, 30, PURPLE);
                                 DrawText("Exit", pauseMenuRec.x + 280, pauseMenuRec.y + 110, 30, RED);
                                 EndDrawing();
                             }
               
                             pauseButtonColor = WHITE;
                         }
                     }
                     else
                     {
                         pauseButtonColor = WHITE;
                     }
                     
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
                                    WaitTime(0.7);
                                    status = "Voces usaram golpes que se\n anularam!";
                                    corTexto = GRAY;
                                }
                                if(player.golpe == 0 && r->valor == 2){
                                    dano = 8;
                                    inimigo.vida -= dano;
                                    WaitTime(0.7);
                                    status = "Voce usou Gelo! \nMagko sofreu 8 de dano!";
                                    corTexto = GREEN;                }
                                if(player.golpe == 0 && r->valor == 1){
                                    dano = 8;
                                    player.vida -= dano;
                                    WaitTime(0.7);
                                    status = "Magko usou Lava! \nVoce sofreu 8 de dano!";
                                    corTexto = RED;
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
                                    WaitTime(0.7);
                                    status = "Voces usaram golpes que se\n anularam!";
                                    corTexto = GRAY;
                                }
                                if(player.golpe == 1 && r->valor == 0){
                                    dano = 8;
                                    inimigo.vida -= dano;
                                    WaitTime(0.7);
                                    status = "Voce usou Agua!\nMagko sofreu 8 de dano!";
                                    corTexto = GREEN;
                                }
                                if(player.golpe == 1 && r->valor == 2){
                                    dano = 8;
                                    player.vida -= dano;
                                    WaitTime(0.7);
                                    status = "Magko usou Fogo!\nVoce sofreu 8 de dano!";
                                    corTexto = RED;
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
                                    WaitTime(0.7);
                                    status = "Voces usaram golpes que se\n anularam!";
                                    corTexto = GRAY;
                                }
                                if(player.golpe == 2 && r->valor == 1){
                                    dano = 8;
                                    inimigo.vida -= dano;
                                    WaitTime(0.7);
                                    status = "Voce usou vento!\nMagko sofreu 8 de dano!";
                                    corTexto = GREEN;
                                }
                                if(player.golpe == 2 && r->valor == 0){
                                    dano = 8;
                                    player.vida -= dano;
                                    WaitTime(0.7);
                                    status = "Magko usou Terra!\nVoce sofreu 8 de dano!";
                                    corTexto = RED;
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
                        WaitTime(2);
                        }
                        if(player.vida <= 0){
                        player.vivo = 0;
                        status = "Voce Morreu!";
                        WaitTime(2);
                        } 
                        //----------------------------------------------------------------------------------
                        // Draw
                    
                        //--------------------------------------------------------------------------------
                        if(inimigo.vivo == 0){
                            WaitTime(2);
                            UnloadTexture(background);
                            UnloadTexture(startButtonBackground);
                            UnloadTexture(aboutButtonBackground);
                            UnloadTexture(exitButtonBackground);
                            UnloadTexture(pauseButton);
                            UnloadTexture(character);
                            UnloadTexture(arrow);
                            
                            UnloadTexture(texturaAtk1);
                            UnloadTexture(texturaAtk2);
                            UnloadTexture(texturaAtk3);
                            UnloadTexture(texturaFundo);
                            UnloadTexture(texturaInimigo);
                            UnloadTexture(texturaInimigo1);
                            UnloadTexture(texturaInimigo2);
                            UnloadTexture(texturaInimigo3);
                            UnloadTexture(texturaLayoutAcoes);
                            UnloadTexture(texturaPainelAtaques);
                            UnloadTexture(texturaPlayer);
                            UnloadTexture(texturaPlayer1);
                            UnloadTexture(texturaPlayer2);
                            UnloadTexture(texturaPlayer3);
                            UnloadTexture(texturaTelaInfo);
                            
                            pauseMenuExit = false;
                            jogando = false;
                            return main();
                        }
                        if(player.vivo == 0){
                            WaitTime(2);
                            UnloadTexture(background);
                            UnloadTexture(startButtonBackground);
                            UnloadTexture(aboutButtonBackground);
                            UnloadTexture(exitButtonBackground);
                            UnloadTexture(pauseButton);
                            UnloadTexture(character);
                            UnloadTexture(arrow);
                            
                            UnloadTexture(texturaAtk1);
                            UnloadTexture(texturaAtk2);
                            UnloadTexture(texturaAtk3);
                            UnloadTexture(texturaFundo);
                            UnloadTexture(texturaInimigo);
                            UnloadTexture(texturaInimigo1);
                            UnloadTexture(texturaInimigo2);
                            UnloadTexture(texturaInimigo3);
                            UnloadTexture(texturaLayoutAcoes);
                            UnloadTexture(texturaPainelAtaques);
                            UnloadTexture(texturaPlayer);
                            UnloadTexture(texturaPlayer1);
                            UnloadTexture(texturaPlayer2);
                            UnloadTexture(texturaPlayer3);
                            UnloadTexture(texturaTelaInfo);
                            pauseMenuExit = false;
                            jogando = false;
                            return main();
                        }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    // TODO: Unload all loaded resources at this point 
                    
                            
                        // Renderiza a tela do jogo
                        BeginDrawing();
                        // TODO: Draw everything that requires to be drawn at this point:
                        DrawTexture(texturaFundo, 0, 0, WHITE);
                        //desenhar:
                        //ClearBackground(RAYWHITE);
            
                        
                        
                        // Renderiza os botões do menu com a cor apropriada
                        //DrawRectangleRec(ATK1_BUTTON_RECTANGLE, buttonColor1);
                        
                        
                        DrawTexture(texturaInimigo,posicaoInimigo.x, posicaoInimigo.y, WHITE);
                        DrawTexture(texturaPlayer,posicaoPlayer.x, posicaoPlayer.y, WHITE);
                        DrawTexture(texturaPainelAtaques, 0, 558, WHITE );
                        DrawTexture(texturaLayoutAcoes, 0, 520, WHITE );
                        DrawTexture(texturaAtk1, ATK1_BUTTON_RECTANGLE.x, ATK1_BUTTON_RECTANGLE.y, WHITE);
                        DrawTexture(texturaAtk2, ATK2_BUTTON_RECTANGLE.x, ATK2_BUTTON_RECTANGLE.y, WHITE);
                        DrawTexture(texturaAtk3, ATK3_BUTTON_RECTANGLE.x, ATK3_BUTTON_RECTANGLE.y, WHITE);
                        
                        DrawTexture(texturaTelaInfo, 850, 570, WHITE);
                        DrawTexture(texturaInimigo1, 65, 45, WHITE);
                        DrawRectangle(188, 55, inimigo.vida*10, 27,RED);
                        DrawTexture(texturaInimigo2, 65, 40, WHITE);
                        
                        DrawTexture(texturaPlayer1, 760, 402, WHITE);
                        DrawRectangle(846, 415, player.vida*10, 23,GREEN);
                        DrawTexture(texturaPlayer2, 790, 411, WHITE);     
                        DrawTexture(texturaPlayer3, 762, 402, WHITE);   
                        DrawTexture(pauseButton, pauseButtonRec.x, pauseButtonRec.y, pauseButtonColor);
                        DrawText(status,880, 600, 28, corTexto);
                        DrawText("Gelo", ATK1_BUTTON_RECTANGLE.x+120, ATK1_BUTTON_RECTANGLE.y+50, 30, RAYWHITE);
                        DrawText("Agua", ATK2_BUTTON_RECTANGLE.x+120, ATK2_BUTTON_RECTANGLE.y+50, 30, RAYWHITE);
                        DrawText("Ar", ATK3_BUTTON_RECTANGLE.x+120, ATK3_BUTTON_RECTANGLE.y+50, 30, RAYWHITE);
                        DrawText(TextFormat("%i/40", player.vida),843, 455, 28, MAGENTA);
                        
                        
                        EndDrawing();
                }
               
                UnloadTexture(pauseButton);
                    
                
            }break;
            
            case MENU:{
                
                // Desenha a imagem de background
                DrawTexture(background, 0, 0, WHITE);
                
                // Verifica se o mouse está sobre os botões
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, (Rectangle){buttonX, buttonY - (buttonHeight + buttonPadding), buttonWidth, buttonHeight})){
                    DrawTexture(arrow, buttonX - arrow.width, buttonY - (buttonHeight + buttonPadding) + (buttonHeight / 2) - (arrow.height / 2), WHITE);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        jogando = true;
                        gameState = LOADING;
                        
                    }
                    
                }
                if (CheckCollisionPointRec(mousePosition, (Rectangle){buttonX, buttonY, buttonWidth, buttonHeight})){
                    DrawTexture(arrow, buttonX - arrow.width, buttonY + (buttonHeight / 2) - (arrow.height / 2), WHITE);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                       // gameState = ABOUT;
                        showPopup = true;
                    }
                }
                if (CheckCollisionPointRec(mousePosition, (Rectangle){buttonX, buttonY + (buttonHeight + buttonPadding), buttonWidth, buttonHeight})){
                    DrawTexture(arrow, buttonX - arrow.width, buttonY + (buttonHeight + buttonPadding) + (buttonHeight / 2) - (arrow.height / 2), WHITE);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        gameState = EXIT;
                    }
                }
                
                // Verifica se o Pop-Up deve ser exibido e o exibe
                if (showPopup) {
                    DrawTexture(pauseButtonBG, 390, 170, WHITE); // Desenha um fundo 
                    DrawText("Este é um breve texto.", GetScreenWidth()/2 - 120, GetScreenHeight()/2 - 40, 20, WHITE); // Desenha o texto do Pop-Up
                    DrawText("CLOSE", GetScreenWidth()/2 - 35, GetScreenHeight()/2 + 25, 20, PURPLE); // Desenha o texto do botão "CLOSE"
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Verifica se o botão esquerdo do mouse foi pressionado
                        Vector2 mousePos = GetMousePosition();
                        Rectangle closeButton = (Rectangle){GetScreenWidth()/2 - 50, GetScreenHeight()/2 + 20, 100, 40};
                        if (CheckCollisionPointRec(mousePos, closeButton)) { // Verifica se o mouse está sobre o botão "CLOSE"
                            showPopup = false; // Define o estado do Pop-Up como "não mostrar"
                        }
                    }
                }
                
                BeginDrawing();
                ClearBackground(RAYWHITE);
        
                // Desenha os botões
                DrawTextureRec(startButtonBackground, (Rectangle){0, 0, startButtonBackground.width, -startButtonBackground.height}, (Vector2){buttonX, buttonY - (buttonHeight + buttonPadding)}, WHITE);
                DrawText("Start", buttonX + (buttonWidth / 2) - (MeasureText("Start", 30) / 2), buttonY - (buttonHeight + buttonPadding) + (buttonHeight / 2) - 15, 30, white);
                DrawTextureRec(aboutButtonBackground, (Rectangle){0, 0, aboutButtonBackground.width, -aboutButtonBackground.height}, (Vector2){buttonX, buttonY}, WHITE);
                DrawText("About", buttonX + (buttonWidth / 2) - (MeasureText("About", 30) / 2), buttonY + (buttonHeight / 2) - 15, 30, white);
                DrawTextureRec(exitButtonBackground, (Rectangle){0, 0, exitButtonBackground.width, -exitButtonBackground.height}, (Vector2){buttonX, buttonY + (buttonHeight + buttonPadding)}, WHITE);
                DrawText("Close", buttonX + (buttonWidth / 2) - (MeasureText("Close", 30) / 2), buttonY + (buttonHeight + buttonPadding) + (buttonHeight / 2) - 15, 30, white);
                
        
                // Atualiza a janela
                EndDrawing();
 
            }break;

            case LOADING:{
                loadingProgress += 0.5f;
                if (loadingProgress >= 100)
                {
                    UnloadTexture(character);
                    UnloadTexture(background);
                    gameState = PLAYING;
                }
                
                // Começa o processo de renderização
                BeginDrawing();
                
                // Limpa a tela com a cor preta
                DrawTexture(background, 0, 0, WHITE);
                
                // Desenha o personagem na posição atual
                DrawTexture(character, characterPositionX, 450, WHITE);
                
                DrawRectangleRec(loadingBar, GRAY);
                DrawRectangle(loadingBar.x, loadingBar.y, loadingBar.width * (loadingProgress / 100), loadingBar.height, SKYBLUE);
                DrawText("Carregando...", screenWidth/2 - 50, screenHeight/2 + 250, 50, WHITE);
                
                // Atualiza a posição do personagem com base no tempo passado desde o último quadro
                float deltaTime = GetFrameTime();
                characterPositionX += characterSpeed * deltaTime;
                
                // Se o personagem saiu da tela, coloca-o de volta no começo
                if (characterPositionX > GetScreenWidth()) {
                    characterPositionX = -character.width / 2 + 50;
                }
                
 
                // Finaliza o processo de renderização
                EndDrawing();
                
                
            }break;
  
            case ABOUT:{
                
                
            }break;
            
            case EXIT:{
                // Descarrega a imagem de background e fecha a janela
                UnloadTexture(background);
                UnloadTexture(startButtonBackground);
                UnloadTexture(aboutButtonBackground);
                UnloadTexture(exitButtonBackground);
                UnloadTexture(pauseButton);
                UnloadTexture(character);
                UnloadTexture(arrow);
                
                UnloadTexture(texturaAtk1);
                UnloadTexture(texturaAtk2);
                UnloadTexture(texturaAtk3);
                UnloadTexture(texturaFundo);
                UnloadTexture(texturaInimigo);
                UnloadTexture(texturaInimigo1);
                UnloadTexture(texturaInimigo2);
                UnloadTexture(texturaInimigo3);
                UnloadTexture(texturaLayoutAcoes);
                UnloadTexture(texturaPainelAtaques);
                UnloadTexture(texturaPlayer);
                UnloadTexture(texturaPlayer1);
                UnloadTexture(texturaPlayer2);
                UnloadTexture(texturaPlayer3);
                UnloadTexture(texturaTelaInfo);
                
                // Fecha a janela
                CloseWindow();
            }break;
               
        }
       
    }

    // Descarrega a imagem de background e fecha a janela
   
    
    // Fecha a janela
    CloseWindow();


    return 0;
}