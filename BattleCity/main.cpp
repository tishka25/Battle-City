#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <GameObject.hpp>
#include <MainMenu.hpp>
#include <vector>
#include <iostream>
#include <math.h>


using namespace std;
using namespace sf;
using namespace gameobject;

int WINDOW_HEIGHT=600;
int WINDOW_WIDTH=800;
Color backgroundColor=Color::Black;


int Map1[]{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Battle city");
FloatRect Border(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
sf::Font font;

vector<GameObject *>Map;
vector<GameObject *>Movable;
vector<GameObject *>onScreen;

MainMenu menu;

bool shoot=false;


//Fill the vector map from the int *map

static void fillMap(vector<GameObject *>&Map, int *map){
    for(int x=0;x<=width;x++){
        for(int y=0;y<=height;y++){
            int buff=y*width+x;
            if(map[buff]!=0){
                onScreen.push_back(new GameObject(MAP,Vector2f(x*32,y*32),"bricks.png"));
            }
        }
    }
}

auto doObjectsOverlap=[](Vector2f pos1,float size1,Vector2f pos2,float size2){
    return (fabs((pos1.x-pos2.x) * (pos1.x-pos2.x) + (pos1.y-pos2.y) * (pos1.y-pos2.y)) <= (size1*size2));
};


//Setup of the code
static void setup(){
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(true);
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    onScreen.push_back(new GameObject(PLAYER1,Vector2f(380,300),"tank.png"));
    onScreen.push_back(new GameObject(PLAYER2,Vector2f(200,300),"tank.png"));
    fillMap(Map, Map1);
}

//Main loop
static void loop(){
    if(!menu.start){
        menu.update();
    }
    else if(menu.start){
        //Move objects
        for(auto gameObject : onScreen){
            if(gameObject->getType()==PLAYER1){
                if(Keyboard::isKeyPressed(Keyboard::D)){
                    gameObject->control(RIGHT);
                }
                else if(Keyboard::isKeyPressed(Keyboard::A)){
                    gameObject->control(LEFT);
                }
                else if(Keyboard::isKeyPressed(Keyboard::S)){
                    gameObject->control(DOWN);
                }
                else if(Keyboard::isKeyPressed(Keyboard::W)){
                    gameObject->control(UP);
                }
                
                if(Keyboard::isKeyPressed(Keyboard::Space) && shoot==false){
                    shoot=true;
                }
                else if(Keyboard::isKeyPressed(Keyboard::Space) && shoot==true){
                    shoot=false;
                }
            }
            if(gameObject->getType()==PLAYER2){
                if(Keyboard::isKeyPressed(Keyboard::Right)){
                    gameObject->control(RIGHT);
                }
                else if(Keyboard::isKeyPressed(Keyboard::Left)){
                    gameObject->control(LEFT);
                }
                else if(Keyboard::isKeyPressed(Keyboard::Down)){
                    gameObject->control(DOWN);
                }
                else if(Keyboard::isKeyPressed(Keyboard::Up)){
                    gameObject->control(UP);
                }
                
            }
            gameObject->update();
        }
        
        //Draw tileMap and collide
        for(auto &gameObject1 : onScreen){
            for(auto &gameObject2 : onScreen){
                if(&gameObject1!=&gameObject2){
                    if(doObjectsOverlap(gameObject1->getPosition(),gameObject1->getSize().x*2,gameObject2->getPosition(),gameObject2->getSize().x*2)){
                        float fDistance=sqrtf((gameObject1->getPosition().x-gameObject2->getPosition().x) * (gameObject1->getPosition().x-gameObject2->getPosition().x) + (gameObject1->getPosition().y-gameObject2->getPosition().y) * (gameObject1->getPosition().y-gameObject2->getPosition().y));
                        
                        float fOverlap=(fDistance-36);
                        Vector2f buff=Vector2f(-fOverlap*(gameObject1->getPosition().x-gameObject2->getPosition().x)/fDistance,-fOverlap*(gameObject1->getPosition().y-gameObject2->getPosition().y)/fDistance);
                        
                        if((gameObject1->getType()!=PLAYER1 || gameObject2->getType()==PLAYER2) ||(gameObject1->getType()==PLAYER2 || gameObject2->getType()==PLAYER1) ){
                            gameObject1->move(buff);

                            //If you want to move everything (it is pretty cool) uncomment the line
                            //                        gameObject2->move(-buff);
                            if(shoot){
                                gameObject2->move(-buff);
                            }
                            
                        }
                    }
                }
            }
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
