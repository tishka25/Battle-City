//
//  GameObject.hpp
//  BattleCity
//
//  Created by Teodor Stanishev on 13.04.18.
//  Copyright © 2018 Teodor Stanishev. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include <ResourcePath.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <SFML/Audio.hpp>



#define ENEMY    1
#define PLAYER1  2
#define PLAYER2  3
#define MAP      4




using namespace sf;
using namespace std;

extern RenderWindow window;
extern FloatRect Border;

int width=25;
int height=19;

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


namespace gameobject {
    class GameObject:public Sprite{
    public:
        Vector2f position;
        Sprite sprite;
        Texture texture;
        int type;
        string filePath;
        float scale=2;
        float speed=5.0f;
        RectangleShape rect;
        Vector2f size;
        GameObject();
        GameObject(RectangleShape rect,Vector2f size){
            this->rect=rect;
            this->size=size;
        }
        GameObject(int type,Vector2f position,string filePath){
            this->type=type;
            this->filePath=filePath;
            if(!texture.loadFromFile(resourcePath()+filePath)){}
            texture.setSmooth(false);
            sprite.setTexture(texture);
            sprite.setScale(scale, scale);
            sprite.setPosition(position);
            sprite.setOrigin(getSize().x/2, getSize().y/2);
        }
        
        
        
        
        void update(){
            window.draw(sprite);
        }
        
        void move(float x, float y){
            sprite.move(x,y);
            window.draw(sprite);
        }
        
        void move(Vector2f pos){
            sprite.move(pos);
            window.draw(sprite);
        }
        
        void control(int dir){
            if (type==PLAYER1 || type==PLAYER2 ) {
                if(dir==UP){
                    sprite.setRotation(90);sprite.move(0,-speed);
                }
                if(dir==DOWN){
                    sprite.setRotation(-90);sprite.move(0,speed);
                }
                if(dir==LEFT){
                    sprite.setRotation(0);sprite.move(-speed,0);
                }
                if(dir==RIGHT){
                    sprite.setRotation(180);sprite.move(speed,0);
                }
            }
        }
        
        
        Vector2u getSize(){
            return texture.getSize();
        }
        
        int getType(){
            return type;
        }
        void setType(int type){
            this->type=type;
        }
        Vector2f getPosition(){
            return sprite.getPosition();
        }
        void setPosition(Vector2f position){
            this->position=position;
        }
        Sprite getSprite(){
            return sprite;
        }
        void setOrigin(Vector2f pos){
            sprite.setOrigin(pos);
        }
        void setRotaion(float angle){
            sprite.setRotation(angle);
        }
        
        void setSprite(string filePath){
            if(!texture.loadFromFile(resourcePath()+filePath)){}
            texture.setSmooth(false);
            sprite.setTexture(texture);
            sprite.setScale(2, 2);
            sprite.setPosition(position);
        }
        Vector2f getScale(){
            return sprite.getScale();
        }
        void setScale(float scale){
            sprite.setScale(scale, scale);
        }
    };

};

using namespace gameobject;
namespace  bullet{
    class Bullet{
    public:
        gameobject::GameObject gameObject;
        Vector2f size=Vector2f(10,10);
        Bullet();
        Bullet(GameObject gameObject,Vector2f size);
    };

};


#endif /* GameObject_hpp */
