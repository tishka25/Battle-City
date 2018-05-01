//
//  GameEngine.cpp
//  BattleCity
//
//  Created by Teodor Stanishev on 30.04.18.
//  Copyright © 2018 Teodor Stanishev. All rights reserved.
//

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <GameObject.hpp>
#include <MainMenu.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include <fstream>



class GameEngine{
private:
    vector<GameObject *>objOnScren;
    string mapFilePath;
    bool shoot=false;
    
    
    //Map width and height
    int width=25;
    int height=19;
    
    void collisionDetection(){
        //Draw tileMap and collide
        for(auto &g1 : objOnScren){
            for(auto &g2 : objOnScren){
                if(&g1!=&g2){
                    if(doObjectsOverlap(g1->getPosition(),g1->getSize().x*g1->scale,g2->getPosition(),g2->getSize().x*g2->scale)){
                        float fDistance=sqrtf((g1->getPosition().x-g2->getPosition().x) * (g1->getPosition().x-g2->getPosition().x) + (g1->getPosition().y-g2->getPosition().y) * (g1->getPosition().y-g2->getPosition().y));
                        
                        float fOverlap=0.2f*(fDistance-g1->getSize().x*g1->scale-g2->getSize().x*g2->scale); //Width of the object
                        
                        Vector2f buff=Vector2f(-fOverlap*(g1->getPosition().x-g2->getPosition().x)/fDistance,-fOverlap*(g1->getPosition().y-g2->getPosition().y)/fDistance);
                        
                        if((g1->getType()==PLAYER1 || g2->getType()==PLAYER2) ||(g1->getType()==PLAYER2 || g2->getType()==PLAYER1) ){
                            g1->move(buff);
                            if(shoot){
                             g2->move(-buff);
                            }
                        }
                    }
                }
            }
        }
    }
    
    void drawEverything(){
        for(auto &g : objOnScren){
            g->update();
            
        }
    }
    
    void controlMovable(){
        //Move objects
        for(auto &gameObject : objOnScren){
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
        }
    }
    
    
    
    
public:
    
    GameEngine();
    GameEngine(vector<GameObject *> objOnScren){
        this->objOnScren=objOnScren;
    }
    
    void setGameMap(string mapFilePath){
        this->mapFilePath=mapFilePath;
    }
    void addObject(GameObject *g){
        objOnScren.push_back(g);
    }
    void fillMap(){
        std::fstream file(resourcePath()+mapFilePath,std::ios_base::in);
        vector<int>_map;
        char a;
        while (file >> a) {
            int buff=a-'0';
            _map.push_back(buff);
        }
        //Fill with objOnScren
        for(int x=0;x<=width;x++){
            for(int y=0;y<=height;y++){
                int buff=y*width+x;
                switch (_map[buff]) {
                    case 1:
                        objOnScren.push_back(new GameObject(MAP,Vector2f(x,y),"stela.jpg",0.13f));
                        break;
                    case 2:
                        objOnScren.push_back(new GameObject(MAP,Vector2f(x,y),"icon.png",0.1f));
                        break;
                    case 3:
                        objOnScren.push_back(new GameObject(MAP,Vector2f(x,y),"elsys.png",0.1f));
                    default:
                        break;
                }
            }
        }
    }
    
    
    GameObject* getPlayer(){
        for(auto &g : objOnScren){
            if(g->getType()==PLAYER1){
                return g;
            }
        }
        return NULL;
    }
    
    vector<GameObject *> getObjects(){
        return objOnScren;
    }
    
    
    void handle(){
        collisionDetection();
        drawEverything();
        controlMovable();
    }

    bool doObjectsOverlap(Vector2f pos1,float size1,Vector2f pos2,float size2){
        if(fabs((pos1.x-pos2.x) * (pos1.x-pos2.x) + (pos1.y-pos2.y) * (pos1.y-pos2.y)) < (size1*size2))
            return true;
        else
            return false;
    }
    bool isInCircle(Vector2f pos1,float size,Vector2f pos2){
        return (fabs((pos1.x-pos2.x) * (pos1.x-pos2.x) + (pos1.y-pos2.y) * (pos1.y-pos2.y) < (size*size)));
    }

    
};
