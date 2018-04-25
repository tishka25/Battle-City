//
//  MainMenu.hpp
//  BattleCity
//
//  Created by Teodor Stanishev on 24.04.18.
//  Copyright © 2018 Teodor Stanishev. All rights reserved.
//

#ifndef MainMenu_hpp
#define MainMenu_hpp

#include <stdio.h>
#include <ResourcePath.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

extern int WINDOW_HEIGHT;
extern int WINDOW_WIDTH;
extern RenderWindow window;
Time t;

class MainMenu{
public:
    bool start=false;
    Text text;
    Font font;
    Clock clock;
    MainMenu(){
        if(!font.loadFromFile(resourcePath()+"sansation.ttf")){
            return EXIT_FAILURE;
        }
        text.setFont(font);
        text.setCharacterSize(24);
        text.setString("Press Spacebar realy fast to change to mode destruction\n\n"
                       "Player1 moves with WASD and can use mode \"Destruction\" \n\n"
                       "Player2 moves with arrow keys\n\n"
                       "Press Return key to start");
        text.setPosition(WINDOW_WIDTH/2-text.getLocalBounds().width/2,WINDOW_HEIGHT/2-text.getLocalBounds().height/2);
    }
    void update(){
        t=clock.getElapsedTime();
        if(t.asMilliseconds()>200){
            text.setFillColor(Color(rand()%255,rand()%255,rand()%255));
            clock.restart();
        }
        
        window.draw(text);
        _start();
    }
    
    
private:
    void _start(){
        if(Keyboard::isKeyPressed(Keyboard::Return)){
            start=true;
        }
    }
    
};

#endif /* MainMenu_hpp */
