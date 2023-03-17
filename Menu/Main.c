#include "raylib.h"

// Constantes
const int SCREEN_WIDTH = 1360;
const int SCREEN_HEIGHT = 768;
const char* WINDOW_TITLE = "Meu menu com Raylib";
const Rectangle START_BUTTON_RECTANGLE = {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 75, 200, 50};
const Rectangle OPTIONS_BUTTON_RECTANGLE = {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 5, 200, 50};
const Rectangle CLOSE_BUTTON_RECTANGLE = {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 70, 200, 50};
const Color BUTTON_COLOR_NORMAL = GRAY;
const Color BUTTON_COLOR_HOVER = LIGHTGRAY;
const Color BUTTON_COLOR_CLICK = BLACK;



// Enumerador para indicar qual botão foi clicado
typedef enum { NO_BUTTON, START_BUTTON, CLOSE_BUTTON, OPTIONS_BUTTON } ButtonType;

int main()
{
    // Inicializa a janela
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    // Define as cores iniciais dos botões
    Color buttonColorStart = BUTTON_COLOR_NORMAL;
    Color buttonColorClose = BUTTON_COLOR_NORMAL;
    Color buttonColorOptions = BUTTON_COLOR_NORMAL;

    // Inicializa a variável que irá indicar qual botão foi clicado
    ButtonType clickedButton = NO_BUTTON;

    // Loop principal do jogo
    while (!WindowShouldClose())
    {
        // Atualiza a posição do mouse a cada quadro
        SetMousePosition(GetMouseX(), GetMouseY());
        Vector2 mousePosition = GetMousePosition();

        // Verifica se o mouse está sobre um dos botões e muda a cor do botão para indicar que ele está selecionado
        if (CheckCollisionPointRec(mousePosition, START_BUTTON_RECTANGLE))
        {
            buttonColorStart = BUTTON_COLOR_HOVER;
            // Verifica se o botão foi clicado
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                clickedButton = START_BUTTON;
            }
        }
        else
        {
            buttonColorStart = BUTTON_COLOR_NORMAL;
        }

        if (CheckCollisionPointRec(mousePosition, CLOSE_BUTTON_RECTANGLE))
        {
            buttonColorClose = BUTTON_COLOR_HOVER;
            // Verifica se o botão foi clicado
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                clickedButton = CLOSE_BUTTON;
            }
        }
        else
        {
            buttonColorClose = BUTTON_COLOR_NORMAL;
        }
        
        if (CheckCollisionPointRec(mousePosition, OPTIONS_BUTTON_RECTANGLE)){
            buttonColorOptions = BUTTON_COLOR_HOVER;
            // Verifica se o botão foi clicado
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    clickedButton = OPTIONS_BUTTON;
                }
        }
        else
        {
            buttonColorOptions = BUTTON_COLOR_NORMAL;
        }


        // Limpa o buffer de tela
        BeginDrawing();
        ClearBackground(RAYWHITE);
    
            // Renderiza os botões do menu com a cor apropriada
        DrawRectangleRec(START_BUTTON_RECTANGLE, buttonColorStart);
        DrawText("START", START_BUTTON_RECTANGLE.x + 35, START_BUTTON_RECTANGLE.y + 15, 20, RAYWHITE);
        DrawRectangleRec(OPTIONS_BUTTON_RECTANGLE, buttonColorOptions);
        DrawText("OPTIONS", OPTIONS_BUTTON_RECTANGLE.x + 20, OPTIONS_BUTTON_RECTANGLE.y + 15, 20, RAYWHITE);
        DrawRectangleRec(CLOSE_BUTTON_RECTANGLE, buttonColorClose);
        DrawText("CLOSE", CLOSE_BUTTON_RECTANGLE.x + 35, CLOSE_BUTTON_RECTANGLE.y + 15, 20, RAYWHITE);
        
            

        // Finaliza o quadro
        EndDrawing();

        // Verifica qual botão foi clicado e toma a ação correspondente
        switch (clickedButton)
        {
            case START_BUTTON:
            int i = 1;
                // Código para iniciar o jogo
                do{
                     BeginDrawing();
                        ClearBackground(BLACK);
                            clickedButton = NO_BUTTON;
                        EndDrawing();
                }while(i ==1);
               
                break;
            case CLOSE_BUTTON:
                // Fecha a janela
                CloseWindow();
                return 0;
                break;
            case OPTIONS_BUTTON:
                // Código para mostrar as opções
                break;
            default:
                // Nenhum botão foi clicado ainda
                break;
        }
    }

    // Encerra a janela
    CloseWindow();
    return 0;
}