//
// Created by Banana on 07.03.2021.
//

#include "Game.h"
// Private functions
void Game::initVariables() {
     this->window = nullptr;

     // Game logic

    this->endGame = false;
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer =  this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
    this->health = 10;
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}
void Game::initFonts(){

    if(this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {

        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";

    }

}

void Game::initText(){

    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(14);
    this->uiText.setFillColor(sf::Color::Red);
    this->uiText.setString("NONE");

}

void Game::initEnemies(){
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    //this->enemy.setOutlineColor(sf::Color::Green);
    // this->enemy.setOutlineThickness(1.f);
}
// Constructors and destructors
Game::Game(){
     this->initVariables();
     this->initWindow();
     this->initFonts();
     this->initText();
     this->initEnemies();
}

Game::~Game(){
    delete this->window;
}

// Accessors
const bool Game::getEndGame() const{

    return this->endGame;

}

const bool Game::running() const {

    return this->window->isOpen();

}


// Functions
void Game::spawnEnemy(){

    /*
     @return void

     Spawns enemies and sets their colours and positions
     -Sets a random position
     -Sets a random colour
     -Adds enemy to the vector
     */

    this->enemy.setPosition(
            static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
            0.f

            );

    this->enemy.setFillColor(sf::Color::Green);

    //Spawn the enemy
        this->enemies.push_back(this->enemy);



}

void Game::pollEvents() {
    while(this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}
void Game::updateMousePositions(){

    /*
    @ return void

     Updates the mouse positions:
            - Mouse position relative to window (Vector2i)
     */
    this->mousePosWindow= sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText() {

    std::stringstream ss;

    ss << "Points: " << this->points;

    this->uiText.setString(ss.str());

}

void Game::updateEnemies(){
    /*
     @return void

     Updates the enemy spawn timer and spawn enemies
     when the total amount of enemies smaller than maxEnemies
     Moves the enemies downwards.
     Removes the enemies at the edge of the screen.
     */
              // Updating the timer for enemy spawning
    if(this->enemies.size() < this->maxEnemies)
    {
        // Spawn the enemy and reset the timer

        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            // Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;

        }
        else
            this->enemySpawnTimer += 1.f;
    }




    //Moving and updating enemies
    for(int i = 0; i < this->enemies.size(); ++i)
    {
        this->enemies[i].move(0.f, 2.f);


        // If the enemy is past the bottom of the screen
        if(this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            std::cout << "Health: " << this->health << "\n";
        }

    }
    // Check if clicked upon
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; ++i) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {

                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);

                    this->points += 1.f;
                    std::cout << "Points: " << this->points << "\n";

                }
            }
        }
    }
    else
        this->mouseHeld = false;

}

void Game::update() {

    this->pollEvents();

    if(this->endGame == false)
    {

        this->updateMousePositions();

        this->updateEnemies();
        this->updateText();
    }
    if(this->health<= 0)
        this->endGame = true;
}

void Game::renderText(sf::RenderTarget& target){

       target.draw(this->uiText);

}

void Game::renderEnemies(sf::RenderTarget& target){

    // Rendering all the enemies
    for(auto &e : this->enemies)
    {
        target.draw(e);
    }


}


void Game::render(){

    /*
       @return void

     - clear old frame
     - render objects
     - display frame in window
      Renders the game objects.
     */

this->window->clear();

// Draw game objects
this->renderEnemies(*this->window);

this->renderText(*this->window);


this->window->display();

}