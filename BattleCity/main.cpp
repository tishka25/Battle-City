#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <GameObject.hpp>
#include <MainMenu.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include <fstream>
#include "GameEngine.cpp"

using namespace std;
using namespace sf;

float  WINDOW_WIDTH=800.0f;
float WINDOW_HEIGHT=600.0f;

int width=25;
int height=19;



Color backgroundColor=Color::Black;

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Battle city");
FloatRect Border(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
sf::Font font;




vector<GameObject *>onScreen;
vector<Bullet *>bullets;
GameEngine gameEngine(onScreen);

MainMenu menu;
Bullet bullet;


//auto doObjectsOverlap=[](Vector2f pos1,float size1,Vector2f pos2,float size2){
//    return (fabs((pos1.x-pos2.x) * (pos1.x-pos2.x) + (pos1.y-pos2.y) * (pos1.y-pos2.y)) < (size1*size2));
//};
//
//


//Setup of the code
static void setup(){
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setSize(Vector2u(800,600));
    
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")){}
    
    gameEngine.setGameMap("MapFile.txt");
    gameEngine.addObject(new GameObject(PLAYER1,Vector2f(380,300),"tank.png",2));
    gameEngine.fillMap();
}

//Main loop
static void loop(){
    if(!menu.start){
        menu.update();
    }
    else if(menu.start){
    
        gameEngine.handle();
        
        if(Keyboard::isKeyPressed(Keyboard::Return)){
            bullets.push_back(new Bullet(Vector2f(5,5),gameEngine.getPlayer()->getPosition(),gameEngine.getPlayer()->facingSide));
        }
        
        for(auto &b : bullets){
            for(auto &g : gameEngine.getObjects()){
                if(gameEngine.doObjectsOverlap(b->getPosition(),b->size.x,g->getPosition(),g->getSize().x*g->getScale().x)){
                    if(g->getType()!=PLAYER1){
                        float fDistance=sqrtf((b->getPosition().x-g->getPosition().x) * (b->getPosition().x-g->getPosition().x) + (b->getPosition().y-g->getPosition().y) * (b->getPosition().y-g->getPosition().y));
                        float fOverlap=0.2f*(fDistance-b->size.x-g->getSize().x*g->scale);
                        
                        Vector2f buff=Vector2f(-fOverlap*(b->getPosition().x-g->getPosition().x)/fDistance,-fOverlap*(b->getPosition().y-g->getPosition().y)/fDistance);
//                        g->move(-buff);
                        bullets.erase(bullets.begin());
                    }
                    
                }
            }
            b->shoot();
        }
    }
}








int main(int, char const**)
{
    setup();
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        // Clear screen
        window.clear(backgroundColor);

        // Draw the sprite
        loop();


        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
