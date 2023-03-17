#include "raylib.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
typedef struct Player{
    int id;
    int hp;
    int atq1, atq2, atq3, atq4;
    int def1, def2, def3, def4;
    Vector2 posicao;
}Player;

typedef struct Inimigo{
    int id;
    int hp;
    int atq1, atq2, atq3, atq4;
    int def1, def2, def3, def4;
    Vector2 posicao;
}Inimigo;

void init_player(Player player){
    player.id =1;
    player.hp = 30;
    player.atq1 = 1;
    player.atq2 = 2;
    player.atq3 = 3;
    player.atq4 = 4;
    player.def1 = 1;
    player.def2 = 2;
    player.def3 = 3;
    player.def4 = 4;
}

void init_inimigo(Inimigo inimigo){
    inimigo.id =1;
    inimigo.hp = 30;
    inimigo.atq1 = 1;
    inimigo.atq2 = 2;
    inimigo.atq3 = 3;
    inimigo.atq4 = 4;
    inimigo.def1 = 1;
    inimigo.def2 = 2;
    inimigo.def3 = 3;
    inimigo.def4 = 4;
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1360;
    const int screenHeight = 768;
    
    Player player;
    init_player(player);
    Vector2 posicaoPlayer = {200, 450};
    
    Inimigo inimigo;
    init_inimigo(inimigo);
    Vector2 posicaoInimigo = {1100, 150};
    

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    Image image = LoadImage("Sprites/Fundo.png");
    Texture2D texturaFundo = LoadTextureFromImage(image);
    UnloadImage(image);
    
    Image playerImage = LoadImage("Sprites/Largato.png");
    Texture2D texturaPlayer = LoadTextureFromImage(playerImage);
    UnloadImage(playerImage);
    
    Image playerInimigo = LoadImage("Sprites/Espirito3.png");
    Texture2D texturaInimigo = LoadTextureFromImage(playerInimigo);
    UnloadImage(playerInimigo);

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

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // TODO: Draw everything that requires to be drawn at this point:
            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);  // Example
            DrawTexture(texturaFundo, 0, 0, WHITE);
            DrawTexture(texturaPlayer, posicaoPlayer.x, posicaoPlayer.y, WHITE);
            DrawTexture(texturaInimigo,posicaoInimigo.x, posicaoInimigo.y, WHITE);
            
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