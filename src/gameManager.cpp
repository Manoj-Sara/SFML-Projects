#include "gameManager.h"

GameManager::GameManager() {
    CreateGrid(sf::Vector2i(TILE_WIDTH, TILE_HEIGHT), sf::Vector2f(20, 20), sf::Vector2f(20, 20));
    LoadAssets();
    CreateInstructions();
    SetBrushSize(1);
}

GameManager::~GameManager() {

}

void GameManager::Update() {
    Game::Update();
}

void GameManager::UpdateDisplay() {
    Game::UpdateDisplay();

    window->draw(grid);

    for (auto tile : tiles) {
        tile.second->Render(*window);
    }
}

void GameManager::UpdateInput() {
    Game::UpdateInput();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        switch (brushType) {
            case Draw:
                DrawGameObjects();
                break;
            case Erase:
                EraseGameObjects();
                break;
            case Eyedrop:
                EyedropGameObject();
                break;
            default:
                break;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        brushType = Draw;
        SetBrushTexture(1);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        brushType = Draw;
        SetBrushTexture(2);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        brushType = Draw;
        SetBrushTexture(3);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
        brushType = Draw;
        SetBrushTexture(4);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
        brushType = Draw;
        SetBrushTexture(5);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
        brushType = Draw;
        SetBrushTexture(6);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
        brushType = Draw;
        SetBrushTexture(7);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
        brushType = Draw;
        SetBrushTexture(8);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        brushType = Draw;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        brushType = Erase;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
        brushType = Eyedrop;
        SetBrushSize(1);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        Save();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        Load("tilemap");
    }
}

void GameManager::UpdateEvents() {
    Game::UpdateEvents();
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::MouseWheelScrolled:
                if (event.mouseWheelScroll.delta > 0) {
                    SetBrushSize(brushSize + 1);
                } else if (event.mouseWheelScroll.delta < 0) {
                    SetBrushSize(brushSize - 1);
                }
                break;
            default:
                break;
        }
    }
}

void GameManager::AddAsset(int key, std::string fileName) {
    assets[key] = new sf::Texture();
    assets[key]->loadFromFile(fileName);
}

void GameManager::LoadAssets() {
    #if _WIN32
        assetPath = "../../../assets/textures/";
    #elif __APPLE__
        assetPath = "../../assets/textures/";
    #endif

    AddAsset(1, assetPath + "BrickGameObject.png");
    AddAsset(2, assetPath + "DirtGameObject.png");
    AddAsset(3, assetPath + "GrassGameObject.png");
    AddAsset(4, assetPath + "WaterGameObject.png");
    AddAsset(5, assetPath + "PichuGameObject.png");
    AddAsset(6, assetPath + "PyoroRed.png");
    AddAsset(7, assetPath + "PyoroWhite.png");
    AddAsset(8, assetPath + "PyoroYellow.png");
}

void GameManager::CreateGrid(sf::Vector2i gridDim, sf::Vector2f xMarg, sf::Vector2f yMarg) {
    gridDimensions = sf::Vector2i(gridDim.x + 1, gridDim.y + 1); // hehe
    xMargin = xMarg;
    yMargin = yMarg;

    grid = sf::VertexArray(sf::Lines, gridDimensions.x * gridDimensions.y * 2);
    
    unitDimensions = sf::Vector2f((windowWidth - (xMargin.x + xMargin.y)) / (gridDimensions.x - 1), 
                                  (windowHeight - (yMargin.x + yMargin.y)) / (gridDimensions.y - 1));

    int v = 0;

    for (int i = 0; i < gridDimensions.y; i++) {
        grid[v].position = sf::Vector2f(xMargin.x, unitDimensions.y * i + yMargin.x);
        grid[v+1].position = sf::Vector2f(windowWidth - xMargin.y, unitDimensions.y * i + yMargin.x);
        v += 2;
    }

    for (int i = 0; i < gridDimensions.x; i++) {
        grid[v].position = sf::Vector2f(unitDimensions.x * i + xMargin.x, yMargin.x);
        grid[v+1].position = sf::Vector2f(unitDimensions.x * i + xMargin.x, windowHeight - yMargin.y);
        v += 2;
    }
}

void GameManager::CreateInstructions() {
    font.loadFromFile(assetPath + "../fonts/Helvetica.ttf");
    instructions.setFillColor(sf::Color::White);
    instructions.setFont(font);
    instructions.setCharacterSize(25);
    instructions.setString("  Draw: D         Erase: E        Eyedropper: I \n\n Sprite Type: 1, 2, 3, 4, 5, 6, 7, 8 \n\n Adjust Brush Size: Scroll \n\n Save: Ctrl + S        Load: Ctrl + L");
}

sf::Vector2i GameManager::GetCurrentGameObjectIndex() {
    int currentX = static_cast<int>((mousePosition.x - xMargin.x) / unitDimensions.x);
    int currentY = static_cast<int>((mousePosition.y - yMargin.x) / unitDimensions.y);
    // std::cout << "X: " << currentX << ",Y: " << currentY << std::endl;
    return sf::Vector2i(currentX, currentY);
}

sf::Texture* GameManager::GetBrushTexture() {
    return assets[brushTexture];
}

void GameManager::DrawGameObjects() {
    EraseGameObjects();
    mouseGameObject = GetCurrentGameObjectIndex();
    int tempBrushSize = brushSize - 1;
    for (int i = -tempBrushSize; i <= tempBrushSize; i++) {
        for (int j = -tempBrushSize; j <= tempBrushSize; j++) {
            if (!(mouseGameObject.x + i < 0 || mouseGameObject.x + i >= TILE_WIDTH 
                || mouseGameObject.y + j < 0 || mouseGameObject.y + j >= TILE_HEIGHT)) { // hehehe
                tileIndex = sf::Vector2i(mouseGameObject.x + i, mouseGameObject.y + j);
                localGameObjectPosition = sf::Vector2f(tileIndex.x * unitDimensions.x + xMargin.x, tileIndex.y * unitDimensions.y + yMargin.x);
                // std::cout << "Mouse Position: (" << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
                // std::cout << "GameObject Index: (" << tileIndex.x << ", " << tileIndex.y << ")" << std::endl;
                // std::cout << "local GameObject Position: (" << localGameObjectPosition.x << ", " << localGameObjectPosition.y << ")" << std::endl;
                tileIndexName = std::to_string(tileIndex.x) + " " + std::to_string(tileIndex.y);
                tiles[tileIndexName] = new GameObject(tileIndex, GetBrushTexture(), unitDimensions, localGameObjectPosition, brushTexture);
            }
        }
    }
}

void GameManager::EraseGameObjects() {
    mouseGameObject = GetCurrentGameObjectIndex();
    int tempBrushSize = brushSize - 1;
    for (int i = -tempBrushSize; i <= tempBrushSize; i++) {
        for (int j = -tempBrushSize; j <= tempBrushSize; j++) {
            if (!(mouseGameObject.x + i < 0 || mouseGameObject.x + i >= TILE_WIDTH 
                || mouseGameObject.y + j < 0 || mouseGameObject.y + j >= TILE_HEIGHT)) { // hehehe
                tileIndex = sf::Vector2i(mouseGameObject.x + i, mouseGameObject.y + j);
                tileIndexName = std::to_string(tileIndex.x) + " " + std::to_string(tileIndex.y);
                tiles.erase(tileIndexName);
            }
        }
    }
}

void GameManager::EyedropGameObject() {
    mouseGameObject = GetCurrentGameObjectIndex();
    tileIndexName = std::to_string(mouseGameObject.x) + " " + std::to_string(mouseGameObject.y);
    if (tiles.find(tileIndexName) != tiles.end()) {
        SetBrushTexture(tiles[tileIndexName]->textureNumber);
        brushType = Draw;
    }
}

void GameManager::SetBrushTexture(int index) {
    brushTexture = index;
}

void GameManager::SetBrushSize(int newSize) {
    if (newSize < 1 || newSize > std::min(gridDimensions.x, gridDimensions.y)) {
        return;
    }

    brushSize = newSize;
}

void GameManager::Save() {
    std::string filePath = assetPath + "../../saves/tilemap.txt";
    std::ofstream saveFile;
    saveFile.open(filePath, std::ios::out);

    for (auto tile : tiles) {
        saveFile << tile.first << "," << std::to_string(tile.second->textureNumber) << "\n";
    }

    saveFile.close();
}

void GameManager::Load(std::string filename) {
    std::string filePath = assetPath + "../../saves/tilemap.txt";
    std::ifstream saveFile;
    
    for (auto tile : tiles) {
        delete tile.second;
    }
    tiles.clear();

    saveFile.open(filePath, std::ios::in);
    std::string readLine;
    while (std::getline(saveFile, readLine)) {
        std::string token;
        size_t position;
        while ((position = readLine.find(' ')) != std::string::npos) {
            token = readLine.substr(0, position);
            tileIndexName = token;
            tileIndex = sf::Vector2i(std::stoi(token), 0);
            readLine.erase(0, position + 1);
        }
        while ((position = readLine.find(',')) != std::string::npos) {
            token = readLine.substr(0, position);
            tileIndexName = tileIndexName + " " + token;
            tileIndex = sf::Vector2i(tileIndex.x, std::stoi(token));
            readLine.erase(0, position + 1);
        }
        SetBrushTexture(std::stoi(readLine));

        localGameObjectPosition = sf::Vector2f(tileIndex.x * unitDimensions.x + yMargin.x, tileIndex.y * unitDimensions.y + xMargin.y);
        tiles[tileIndexName] = new GameObject(tileIndex, GetBrushTexture(), unitDimensions, localGameObjectPosition, brushTexture);
    }

    SetBrushTexture(1);
    SetBrushSize(1);
}