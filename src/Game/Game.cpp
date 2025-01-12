#include "Game.h"
#include "Renderer/Renderer.h"
#include "Input/Input.h"
#include "Input/Camera/FPS_Input.h"
#include "Scene.h"
#include <iostream>
#include "Core/Camera.h"

namespace Game {

    bool _isLoaded = false;
    double _deltaTimeAccumulator = 0.0;
    double _fixedDeltaTime = 1.0 / 60.0;
    std::vector<Player> g_players;

    bool g_firstFrame = true;
    double g_lastFrame = 0;
    double g_thisFrame = 0;
    float g_time = 0;

    //Camera* g_camera;


    // Initialize the game and renderer, and create players
    void Create() {
        _isLoaded = true;
        g_firstFrame = true;

 
        CreatePlayers(1);

        std::cout << "Game::Create() succeeded\n";
    }

    // Check if the game is loaded
    bool IsLoaded() {
        return _isLoaded;
    }

    // Update the game each frame
    void Update() {
        if (g_firstFrame) {
            g_thisFrame = glfwGetTime();
            g_firstFrame = false;
        }

        // Calculate delta time
        g_lastFrame = g_thisFrame;
        g_thisFrame = glfwGetTime();
        double deltaTime = g_thisFrame - g_lastFrame;
        _deltaTimeAccumulator += deltaTime;
        g_time += deltaTime;

        // Update input handling
        FPS_Input::Update();

        // Update players
        for (Player& player : g_players) {
            player.Update(deltaTime);
        }
        FPS_Input::ResetMouseOffsets();

        Scene::Update(deltaTime);

        // Process window resizing or input state
        //Input::ProcessWindowInput();


        // Handle game restart or other actions
        if (Input::KeyPressed(GLFW_KEY_R)) {
            //RestartGame();
        }
    }

    void CreatePlayers(unsigned int playerCount) {
        g_players.clear();
        g_players.resize(1);

        for (int i = 0; i < playerCount; i++) {
            Game::g_players.push_back(Player(i));
        }

        SetPlayerKeyboardAndMouseIndex(0, 0, 0);
    }

    void SetPlayerKeyboardAndMouseIndex(int playerIndex, int keyboardIndex, int mouseIndex) {
        if (playerIndex >= 0 && playerIndex < Game::GetPlayerCount()) {
            g_players[playerIndex].SetKeyboardIndex(keyboardIndex);
            g_players[playerIndex].SetMouseIndex(mouseIndex);
        }
    }

    Player* GetPlayerByIndex(unsigned int index) {
        if (index >= 0 && index < g_players.size()) {
            return &g_players[index];
        }
        else {
            //std::cout << "Game::GetPlayerByIndex() failed because index was out of range. Size of Game::_players is " << GetPlayerCount() << "\n";
            return nullptr;
        }
    }


    // Getters
    const int GetPlayerCount() {
        return g_players.size();
    }

  
}