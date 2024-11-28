#include "Game.h"
#include "Game/DataSaver.h"
#include "Game/Portal.h"
#include "Utils/ConsoleControl.h"

#define MIN_DIST 2

Game::Game(){
    srand(time(NULL));

    for (int i = 0; i < HORIZONTAL_MAP_ZONES; i++) {
        for (int j = 0; j < VERTICAL_MAP_ZONES; j++) {
            currentMap = new NodeMap(Vector2(ZONE_WIDTH + 2, ZONE_HEIGHT + 2), Vector2(0, 0));
            for (int k = 0; k < ZONE_WIDTH + 2; k++) {
                for (int l = 0; l < ZONE_HEIGHT + 2; l++) {
                    if (k == 0 || k == ZONE_WIDTH + 1 || l == 0 || l == ZONE_HEIGHT + 1) {

                        if (((k == ZONE_WIDTH / 2 && l == 0) && (j!=0) )||
                            ((k == ZONE_WIDTH / 2 && l == ZONE_HEIGHT + 1) && (j!=VERTICAL_MAP_ZONES-1)) ||
                            ((k == 0 && l == ZONE_HEIGHT / 2) &&  (i!=0)) ||
                            ((k == ZONE_WIDTH + 1 && l == ZONE_HEIGHT / 2) && (i!= HORIZONTAL_MAP_ZONES-1))) 
                        {
                            currentMap->SafePickNode(Vector2(k, l), [this](Node* node) {
                                node->SetContent(new Portal(), 'P');
                                node->DrawContent(Vector2(0, 0));
                                });
                        }
                        else {
                            currentMap->SafePickNode(Vector2(k, l), [this](Node* node) {
                                node->SetContent(new Wall(), '#');
                                node->DrawContent(Vector2(0, 0));
                                });
                        }
                    }
                }
            }
            maps[i][j] = currentMap;
        }
    }
    currentHorizontalZone = HORIZONTAL_MAP_ZONES/2;
    currentVerticalZone = VERTICAL_MAP_ZONES / 2;
    currentMap = maps[currentHorizontalZone][currentVerticalZone];
    //player = new Player(Vector2(ZONE_WIDTH/2,ZONE_HEIGHT/2));
    player = new Player(Vector2(3,4));
    currentMap->SafePickNode(player->position, [this](Node* node) {
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

    //Timer for moving enemies 
    timer->StartLoopTimer(1000, [this]() {
        MoveEnemies();
        return true;
        });

    //Timer for spawing enemies or chests
    timer->StartLoopTimer(1000, [this]() {
        
        //Randomize enemy or chest generation and position
        int which = rand() % 11;
        Vector2 randomPos;

        do
        {
            randomPos.x = 1 + (rand() % (ZONE_WIDTH - 1));
        } while (MIN_DIST > abs(player->position.x - randomPos.x));
        do
        {
            randomPos.y = 1 + (rand() % (ZONE_HEIGHT - 1));
        } while (MIN_DIST > abs(player->position.y - randomPos.y));

        if (which > 5) {
            _enemyMutex.lock();
            Enemy* newEnemy = new Enemy(randomPos,
                LeftCenterRight(currentHorizontalZone), UpCenterDown(currentVerticalZone));
            allEnemies.push_back(newEnemy);

            currentMap->SafePickNode(allEnemies.back()->position, [this](Node* node) {
                node->SetContent(allEnemies.back(), 'E');
                node->DrawContent(Vector2(0, 0));
            });
            _enemyMutex.unlock();
        }
        else {
        
            Chest* newChest = new Chest(randomPos);
            allchests.push_back(newChest);

            currentMap->SafePickNode(allchests.back()->position, [this](Node* node) {
                node->SetContent(allchests.back(), 'C');
                node->DrawContent(Vector2(0,0));
            });
        }
        
        return true;
    });


    
    PrintMapAndHud();
}

void Game::MoveEnemies() {
    _enemyMutex.lock(); 
    for (Enemy* oneEnemy : allEnemies)
    {
        if (oneEnemy != nullptr)
        {
            if (oneEnemy->iCanMove == true)
            {
                MoveEnemy(EDirection(rand() % 4), oneEnemy);
                oneEnemy->DoneActing();
            }
        }
    }
    _enemyMutex.unlock();
}

void Game::MoveEnemy(EDirection dir, Enemy* enemy) {

    if (int(enemy->xArea) == int(currentHorizontalZone) && int(enemy->yArea) == int(currentVerticalZone))
    {
        currentMap->SafePickNode(enemy->position, [this](Node* node) {
            node->SetContent(nullptr, '_');
            node->DrawContent(Vector2(0, 0));
        });
    }
    
    switch (dir)
    {
    case EDirection::UP:
        currentMap->SafePickNode(Vector2(enemy->position.x, enemy->position.y - 1), [this, enemy](Node* node) {
            if (node->GetnodeContent() == nullptr)
                enemy->position.y--;
            else if (node->GetnodeContent() == dynamic_cast<Player*>(node->GetnodeContent()))
                player->Hurt();
            
            });

        break;
    case EDirection::DOWN:
        currentMap->SafePickNode(Vector2(enemy->position.x, enemy->position.y + 1), [this, enemy](Node* node) {
            if (node->GetnodeContent() == nullptr)
                enemy->position.y++;
            else if (node->GetnodeContent() == dynamic_cast<Player*>(node->GetnodeContent()))
                player->Hurt();
            });

        break;
    case EDirection::LEFT:
        currentMap->SafePickNode(Vector2(enemy->position.x - 1, enemy->position.y), [this, enemy](Node* node) {
            if (node->GetnodeContent() == nullptr)
                enemy->position.x--;
            else if (node->GetnodeContent() == dynamic_cast<Player*>(node->GetnodeContent()))
                player->Hurt();
            
            });
        break;
    case EDirection::RIGHT:
        currentMap->SafePickNode(Vector2(enemy->position.x + 1, enemy->position.y), [this, enemy](Node* node) {
            if (node->GetnodeContent() == nullptr)
                enemy->position.x++;
            else if (node->GetnodeContent() == dynamic_cast<Player*>(node->GetnodeContent()))
                player->Hurt();
            
            });
        break;
    }

    if (int(enemy->xArea) == int(currentHorizontalZone) && int(enemy->yArea) == int(currentVerticalZone)) {
        currentMap->SafePickNode(enemy->position, [this, enemy](Node* node) {
        node->SetContent(enemy, 'E');
        node->DrawContent(Vector2(0, 0));
        });
    }
}

void Game::GameUpdate()
{
    is->StartListen();
    while (true){}
}

void Game::PrintMapAndHud()
{
    currentMap->UnsaveDraw();
    std::cout << "\nMonedas:" << player->coins << std::endl;
    std::cout << "Vidas:" << player->potions << std::endl;
    std::cout << "Pociones:" << player->potions << std::endl;
    std::cout << "Weapon";
}

void Game::ChangeMapZone(EDirection dir)
{
    switch (dir)
    {
    case EDirection::UP:
        player->position.y = ZONE_HEIGHT;
        currentVerticalZone--;
        break;
    case EDirection::DOWN:
        player->position.y = 1;
        currentVerticalZone++;
        break;
    case EDirection::LEFT:
        player->position.x = ZONE_WIDTH;
        currentHorizontalZone--;
        break;
    case EDirection::RIGHT:
        player->position.x = 1;
        currentHorizontalZone++;
        break;
    }
    currentMap = maps[currentHorizontalZone][currentVerticalZone];
    PrintMapAndHud();
}

void Game::MovePlayer(EDirection dir)
{
    if (canAttackMove) {

        canAttackMove = false;
        currentMap->SafePickNode(player->position, [this](Node* node) {
            node->SetContent(nullptr, '_');
            node->DrawContent(Vector2(0, 0));
            });
        switch (dir)
        {
        case EDirection::UP:
            currentMap->SafePickNode(Vector2(player->position.x, player->position.y -1), [this](Node* node) {
                if (node->GetnodeContent() == nullptr)
                    player->position.y--;
                else if (dynamic_cast<Portal*>(node->GetnodeContent()))
                    ChangeMapZone(EDirection::UP);
            }); 
            
            break;
        case EDirection::DOWN:
            currentMap->SafePickNode(Vector2(player->position.x, player->position.y + 1), [this](Node* node) {
                if (node->GetnodeContent() == nullptr)
                    player->position.y++;
                else if (dynamic_cast<Portal*>(node->GetnodeContent()))
                    ChangeMapZone(EDirection::DOWN);
            });
            
            break;
        case EDirection::LEFT:
            currentMap->SafePickNode(Vector2(player->position.x - 1, player->position.y), [this](Node* node) {
                if (node->GetnodeContent() == nullptr)
                    player->position.x--;
                else if (dynamic_cast<Portal*>(node->GetnodeContent()))
                    ChangeMapZone(EDirection::LEFT);
            });
            break;
        case EDirection::RIGHT:
            currentMap->SafePickNode(Vector2(player->position.x + 1, player->position.y), [this](Node* node) {
                if (node->GetnodeContent() == nullptr)
                    player->position.x++;
                else if (dynamic_cast<Portal*>(node->GetnodeContent())) 
                    ChangeMapZone(EDirection::RIGHT);   
                /*else if (dynamic_cast<Enemy*>(node->GetnodeContent())) {
                    //_enemyMutex.lock();
                    for (int i = 0; i < allEnemies.size(); i++) {
                        if (allEnemies[i] == node->GetnodeContent())
                        {

                            //currentMap->SafePickNode(Vector2(player->position.x + 1, player->position.y),
                                //[this](Node* node) {
                                    //node->SetContent(nullptr, '_');
                                    //node->DrawContent(Vector2(0, 0));
                                //});

                            allEnemies.erase(allEnemies.begin() + i);

                        }
                    }
                    //_enemyMutex.unlock();
                }*/
            });
            break;
        }
        currentMap->SafePickNode(player->position, [this](Node* node) {
            node->SetContent(player, 'J');
            node->DrawContent(Vector2(0, 0));
            });

        timer->StartTimer(500, [this]() {
            canAttackMove = true;
            });
    }
}
