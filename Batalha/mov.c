#include "raylib.h"

#define SCREEN_WIDTH 1360
#define SCREEN_HEIGHT 768
#define MAP_WIDTH 1500
#define MAP_HEIGHT 900

int main(void)
{
    // Inicializa a janela e define seu título
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Map Movement");

    // Carrega as imagens do mapa e do personagem como texturas
    Image mapImage = LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Sprites/Mapa.png");
    Texture2D mapTexture = LoadTextureFromImage(mapImage);
    UnloadImage(mapImage);  // Libera a memória utilizada pela imagem

    Image characterImage = LoadImage("C:/Users/wagne/OneDrive/Documentos/Raylib/Batalha/Sprites/Jogador01.png");
    Texture2D characterTexture = LoadTextureFromImage(characterImage);
    UnloadImage(characterImage);  // Libera a memória utilizada pela imagem

    // Define a posição inicial do personagem no centro da tela
    Vector2 characterPos = { 900, 1200 };

    // Configura a câmera para acompanhar o personagem com um deslocamento em relação ao centro da tela
    Camera2D camera = { 0 };
    camera.target = characterPos;  // Define o alvo da câmera como a posição do personagem
    camera.offset = (Vector2){ SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Define a taxa de atualização da janela
    SetTargetFPS(60);

    // Loop principal do jogo
    while (!WindowShouldClose())
    {
        // Atualiza a posição do personagem com as teclas de seta do teclado
        if (IsKeyDown(KEY_RIGHT)) characterPos.x += 5;
        if (IsKeyDown(KEY_LEFT)) characterPos.x -= 5;
        if (IsKeyDown(KEY_DOWN)) characterPos.y += 5;
        if (IsKeyDown(KEY_UP)) characterPos.y -= 5;

        // Atualiza a posição do alvo da câmera com a posição do personagem
        camera.target = characterPos;

        // Inicia o desenho na janela
        BeginDrawing();

            // Limpa a tela com a cor branca
            ClearBackground(RAYWHITE);

            // Aplica a câmera ao desenho do mapa e do personagem
            BeginMode2D(camera);

                // Desenha a textura do mapa em posição fixa na tela
                DrawTextureEx(mapTexture, (Vector2){0,0}, 0, 1, WHITE);

                // Desenha a textura do personagem na posição atualizada
                DrawTextureEx(characterTexture, characterPos, 0, 1, WHITE);

            EndMode2D();

        // Encerra o desenho na janela
        EndDrawing();
    }

    // Libera a memória utilizada pelas texturas
    UnloadTexture(mapTexture);
    UnloadTexture(characterTexture);

    // Fecha a janela
    CloseWindow();

    return 0;
}