#include "Game.h"
#include "Game/DataSaver.h"
#include "Utils/ConsoleControl.h"
/*
Lo que está mal, es que player o character, ninguno de ellos debe ser un Node.
Solo debe ser iNodeContent, y implementar la función draw.
Despues, una vez tienes el puntero del nodo donde quieres que este, solo tienes que usar la función del node de setContent.

Porque lo que tienes que hacer no es cambiar el nodo, si no el contenido de dentro del nodo.
*/
Game::Game()
{
    map = new NodeMap(Vector2(ZONE_WIDTH, ZONE_HEIGHT), Vector2(0, 0));
    player = new Player(Vector2(1,1));
    map->SafePickNode(player->position, [this](Node* node) {
        node->SetContent(player, 'J');
    });
    is = new InputSystem();   
    //WASD movement
    InputSystem::KeyBinding* kb1 = is->KeyAddListener(K_D, [this]() {
        if (((player->position + Vector2(1, 0)).x < Vector2(10, 6).x) && canAttackMove) {
            player->Move(Vector2(1, 0));
            canAttackMove = false;
            timer->StartTimer(1000, [this]() {
                canAttackMove = true;
            });
        }
    });
    InputSystem::KeyBinding* kb2 = is->KeyAddListener(K_S, [this]() {
        if (((player->position + Vector2(0, 1)).y < Vector2(10, 6).y) && canAttackMove){
            player->Move(Vector2(0, 1));
            canAttackMove = false; 
            timer->StartTimer(1000, [this]() {
                canAttackMove = true;
            });
        }
    });
    InputSystem::KeyBinding* kb3 = is->KeyAddListener(K_A, [this]() {
        if (((player->position + Vector2(-1, 0)).x >= 0) && canAttackMove) {
            player->Move(Vector2(-1, 0));
            canAttackMove = false;
            timer->StartTimer(1000, [this]() {
                canAttackMove = true;
            });
        }
    });
    InputSystem::KeyBinding* kb4 = is->KeyAddListener(K_W, [this]() {
        if (((player->position + Vector2(0, -1)).y >= 0) && canAttackMove) {
            player->Move(Vector2(0, -1));
            canAttackMove = false;
            timer->StartTimer(1000, [this]() {
                canAttackMove = true;
            });
        }
    });
    //Healing
    InputSystem::KeyBinding* kb5 = is->KeyAddListener(K_0, [this]() {
        if ((player->potions > 0) && canAttackMove) {
            player->potions--;
            player->lifes++;
            canAttackMove = false;
            timer->StartTimer(1000, [this]() {
                canAttackMove = true;
            });
        }
    });
    //Timer for saving files
    timer->StartLoopTimer(5000, [this]() {
        //DataSaver::Instance().SaveData();
        return true;
    });

    PrintMapAndHud();
}

void Game::GameUpdate()
{
    is->StartListen();
    while (true){}
}

void Game::PrintMapAndHud()
{
    map->UnsaveDraw();
    std::cout << "\nMonedas:" << player->coins << std::endl;
    std::cout << "\nPociones:" << player->potions << std::endl;
}
