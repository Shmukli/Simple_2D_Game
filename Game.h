//
// Created by Banana on 07.03.2021.
//

#ifndef UNTITLED2_GAME_H
#define UNTITLED2_GAME_H

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
/*
    Class that acts as the game engine.
    Wrapper class.
 */

class Game {
private:
    // Variables
    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    // Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Resources
    sf::Font font;

    // Text
    sf::Text uiText;

    //Game logic
    bool endGame;
    unsigned points;
    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;


    // Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;


    // Private functions
    void initVariables();
    void initFonts();
    void initText();
    void initWindow();
    void initEnemies();
public:
    // Constructors and destructors
    Game();
    virtual ~Game();

    // Accessors

    const bool running() const;
    const bool getEndGame() const;


    // Functions
    void spawnEnemy();

    void pollEvents();
    void updateMousePositions();
    void updateText();
    void updateEnemies();
    void update();

    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void render();

};


#endif //UNTITLED2_GAME_H
