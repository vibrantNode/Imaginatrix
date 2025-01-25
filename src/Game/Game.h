#include "Player.h"

namespace Game {

    enum class GameMode { GAME, EDITOR_TOP_DOWN, EDITOR_3D };


    void Create();
    void CreatePlayers(unsigned int playerCount);
    bool IsLoaded();
    void Update();
    const int GetPlayerCount();
  
    //inline std::vector<PlayerData> g_playerData;

    Player* GetPlayerByIndex(unsigned int index);
    void SetPlayerKeyboardAndMouseIndex(int playerIndex, int keyboardIndex, int mouseIndex);

    // Getters
    float GetTime();
}