#include "Game.h"
#include "Game/DataSaver.h"
#include "Game/Portal.h"
#include "Utils/ConsoleControl.h"

/*
Lo que está mal, es que player o character, ninguno de ellos debe ser un Node.
Solo debe ser iNodeContent, y implementar la función draw.
Despues, una vez tienes el puntero del nodo donde quieres que este, solo tienes que usar la función del node de setContent.

Porque lo que tienes que hacer no es cambiar el nodo, si no el contenido de dentro del nodo.
*/
Game::Game()
{
    map = new NodeMap(Vector2(ZONE_WIDTH+2, ZONE_HEIGHT+2), Vector2(0, 0));
    for (int i = 0; i < ZONE_WIDTH + 2; i++) {
        for (int j = 0; j < ZONE_HEIGHT + 2; j++) {
            if (i == 0 || i == ZONE_WIDTH + 1 ||   j == 0 || j == ZONE_HEIGHT +1 ) {
                if ((i == ZONE_WIDTH / 2 && j == 0) || (i == ZONE_WIDTH / 2 && j == ZONE_HEIGHT + 1) ||
                    (i == 0 && j == ZONE_HEIGHT / 2) || (i == ZONE_WIDTH + 1 && j == ZONE_HEIGHT / 2)) {
                    map->SafePickNode(Vector2(i, j), [this](Node* node) {
                        node->SetContent(new Portal(), 'P');
                        node->DrawContent(Vector2(0, 0));
                    });
                }
                else {
                    map->SafePickNode(Vector2(i, j), [this](Node* node) {
                        node->SetContent(new Wall(), '#');
                        node->DrawContent(Vector2(0, 0));
                    });
                }
            }
        }
    }
    player = new Player(Vector2(1,1));
    map->SafePickNode(player->position, [this](Node* node) {
        node->SetContent(player, 'J');
        node->DrawContent(player->position);
    });
    is = new InputSystem();   
    //WASD movement
    InputSystem::KeyBinding* kb1 = is->KeyAddListener(K_D, [this]() {
        MovePlayer(EDirection::RIGHT);
    });
    InputSystem::KeyBinding* kb2 = is->KeyAddListener(K_S, [this]() {
        MovePlayer(EDirection::DOWN);
    });
    InputSystem::KeyBinding* kb3 = is->KeyAddListener(K_A, [this]() {
        MovePlayer(EDirection::LEFT);
    });
    InputSystem::KeyBinding* kb4 = is->KeyAddListener(K_W, [this]() {
        MovePlayer(EDirection::UP);
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

void Game::MovePlayer(EDirection dir)
{
    if (canAttackMove) {

        canAttackMove = false;
        map->SafePickNode(player->position, [this](Node* node) {
            node->SetContent(nullptr, '_');
            node->DrawContent(Vector2(0, 0));
            });
        switch (dir)
        {
        case Game::UP:
            map->SafePickNode(Vector2(player->position.x, player->position.y -1), [this](Node* node) {
                if (node->GetnodeContent() == nullptr)
                    player->position.y--;
                else if (node->GetnodeContent() == new Portal()) 
                    std::cout << "----------------------------------------------teleport";
            }); 
            
            break;
        case Game::DOWN:
            map->SafePickNode(Vector2(player->position.x, player->position.y + 1), [this](Node* node) {
                if (node->GetnodeContent() == nullptr)
                player->position.y++;
                else if (node->GetnodeContent() == new Portal())
                    std::cout << "----------------------------------------------teleport";
            });
            
            break;
        case Game::LEFT:
            map->SafePickNode(Vector2(player->position.x - 1, player->position.y), [this](Node* node) {
                if (node->GetnodeContent() == nullptr)
                    player->position.x--;
                else if (node->GetnodeContent() == new Portal())
                    std::cout << "----------------------------------------------teleport";
            });
            break;
        case Game::RIGHT:
            map->SafePickNode(Vector2(player->position.x + 1, player->position.y), [this](Node* node) {
                if (node->GetnodeContent() == nullptr)
                    player->position.x++;
                else if (dynamic_cast<Portal*>(node->GetnodeContent())) 
                    std::cout << "----------------------------------------------teleport";
                });
            
            break;
        default:
            break;
        }
        map->SafePickNode(player->position, [this](Node* node) {
            node->SetContent(player, 'J');
            node->DrawContent(Vector2(0, 0));
            });

        timer->StartTimer(500, [this]() {
            canAttackMove = true;
            });
    }
}
