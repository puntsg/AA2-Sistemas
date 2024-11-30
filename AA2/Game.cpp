#include "Game.h"
#include "Game/DataSaver.h"
#include "Game/Portal.h"
#include "Utils/ConsoleControl.h"
#include <fstream>
#include "3Nodes/ICodeable.h"

Game::Game(){
    srand(time(NULL));
    std::cout << 
        "1: load game\n" <<
        "other: newgame\n" <<
        "option: ";
    char option;
    std::cin >> option;

    //Creaci� mapa
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
    
    if (option == '1') {
        currentHorizontalZone = HORIZONTAL_MAP_ZONES / 2;
        currentVerticalZone = VERTICAL_MAP_ZONES / 2;
        currentMap = maps[currentHorizontalZone][currentVerticalZone];
        player = new Player(Vector2(ZONE_WIDTH / 2, ZONE_HEIGHT / 2));
        currentMap->SafePickNode(player->position, [this](Node* node) {
            node->SetContent(player, 'J');
            node->DrawContent(player->position);
         });
    }
    else 
        LoadData();

    
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
        SaveData();
        return true;
    });

    //Timer for moving enemies 
    timer->StartLoopTimer(1000, [this]() {
        MoveEnemies();
        return true;
        });

    //Timer for spawing enemies or chests
    timer->StartLoopTimer(1000, [this]() {
        int which = rand() % 11;
        
        if (which > 5) {
            _enemyMutex.lock();
            Enemy* newEnemy = new Enemy(Vector2(1 + (rand() % (ZONE_WIDTH - 1)), 1 + (rand() % (ZONE_HEIGHT - 1))),
                LeftCenterRight(currentHorizontalZone), UpCenterDown(currentVerticalZone));
            allEnemies.push_back(newEnemy);

            currentMap->SafePickNode(allEnemies.back()->position, [this](Node* node) {
                node->SetContent(allEnemies.back(), 'E');
                node->DrawContent(Vector2(0, 0));
            });
            _enemyMutex.unlock();
        }
        else {
        
            Chest* newChest = new Chest(Vector2(1 + (rand() % (ZONE_WIDTH -1)), 1 + (rand() % (ZONE_HEIGHT -1))));
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
        //node->SetContent(enemy, node->GetnodeContent()->GetIcon());
            //node->SetContent(enemy, node->GetnodeContent()->icon);
            node->SetContent(enemy, 'E');
            node->DrawContent(Vector2(0, 0));
        });
    }
}

void Game::SaveData()
{
    //Save Map
    std::ofstream mapFile;
    mapFile.open("map.txt");
    std::string mapString = "";
    saveMutex.lock();
    for (int i = 0; i < HORIZONTAL_MAP_ZONES; i++) {
        for (int j = 0; j < VERTICAL_MAP_ZONES; j++) {
            for (int k = 0; k < ZONE_WIDTH + 2; k++) {
                for (int l = 0; l < ZONE_HEIGHT + 2; l++) {
                    maps[i][j]->SafePickNode(Vector2(k, l), [this, &mapString](Node* node) {
                        if(node->GetnodeContent() == nullptr)
                            mapString += " ";
                        else
                            mapString += node->GetnodeContent()->icon;
                     });
                }
                mapString += "\n";
            }
            mapString += "\n";
        }
    }
   saveMutex.unlock();
    mapFile << mapString;
    mapFile.close();
    //Save Player
    Json::Value json = player->Encode();
    std::ofstream jsonWriteFile = std::ofstream("Player.json", std::ifstream::binary);
    if (!jsonWriteFile.fail()) {
        jsonWriteFile << json;
        jsonWriteFile.close();
    }
}

void Game::LoadData()
{
    std::string line;
    std::ifstream MyReadFile("map.txt");
    for (int i = 0; i < HORIZONTAL_MAP_ZONES; i++) {
        for (int j = 0; j < VERTICAL_MAP_ZONES; j++) {
            
            for (int k = 0; k < ZONE_WIDTH + 2; k++) {
                getline(MyReadFile, line);
                char lineArray[ZONE_WIDTH + 2];
                strcpy_s(lineArray, line.c_str());
                for (int l = 0; l < ZONE_HEIGHT + 2; l++) {
                    maps[i][j]->SafePickNode(Vector2(k, l), [this, i,j,k, l, lineArray](Node* node) {
                        switch (lineArray[l])
                        {
                        case 'J':
                            currentHorizontalZone = i;
                            currentVerticalZone = j;
                            LoadPlayer(Vector2(k,l));
                            node->SetContent(player, 'J');
                            break;
                        case '#':
                            node->SetContent(new Wall(), '#');
                            break;
                        case 'E':
                            node->SetContent(new Enemy(Vector2(k,l),(LeftCenterRight)i,(UpCenterDown)j), 'E');
                            break;
                        case 'C':
                            node->SetContent(new Chest(Vector2(k, l)), 'C');
                            break;
                        case 'P':
                            node->SetContent(new Portal, 'P');
                            break;
                        case ' ':
                            node->SetContent(nullptr, '_');
                            break;
                        default:
                            break;
                        }
                     });
                }
                
            }
            getline(MyReadFile, line);
        }
    }
    MyReadFile.close(); 
    
    currentMap = maps[currentHorizontalZone][currentVerticalZone];
}

void Game::LoadPlayer(Vector2 pos)
{
    player = new Player(pos);
    std::ifstream jsonReadFile = std::ifstream("Player.json", std::ifstream::binary);
    if (!jsonReadFile.fail()) {
        Json::Value ReadedJson;
        jsonReadFile >> ReadedJson;
        player = player->FromJson(ReadedJson, player->position);
        jsonReadFile.close();
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
    std::cout << "Vidas:" << player->lifes << std::endl;
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
            node->SetContent(nullptr,'_');
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
            });
            break;
        }
        currentMap->SafePickNode(player->position, [this](Node* node) {
            node->SetContent(player, player->icon);
            node->DrawContent(Vector2(0, 0));
            });

        timer->StartTimer(500, [this]() {
            canAttackMove = true;
            });
    }
}