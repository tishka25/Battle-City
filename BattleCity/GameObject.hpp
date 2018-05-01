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
#define BULLET   5


using namespace sf;
using namespace std;

extern RenderWindow window;
extern FloatRect Border;

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


class Bullet{
private:
    float _size=10;
    float speed=10;
public:
    Vector2f size=Vector2f(_size,_size);
    RectangleShape bullet;
    Vector2f startingPosition;
    int dir;
    Bullet(){
        bullet.setSize(size);
    }
    Bullet(Vector2f size,Vector2f startingPosition,int dir){
        this->size=size;
        bullet.setSize(size);
        this->startingPosition=startingPosition;
        bullet.setPosition(Vector2f(startingPosition.x-size.x,startingPosition.y-size.y));
        this->dir=dir;
        
    }
    
    void shoot(){
        switch (dir) {
            case RIGHT:
                bullet.move(speed,0);
                break;
            case LEFT:
                bullet.move(-speed,0);
                break;
            case UP:
                bullet.move(0,-speed);
                break;
            case DOWN:
                bullet.move(0,speed);
                break;
                default:
                    break;
            }
        window.draw(bullet);
    }
    void shoot(Vector2f pos,int dir){
        bullet.setPosition(pos);
        switch (dir) {
            case RIGHT:
                bullet.move(speed,0);
                break;
            case LEFT:
                bullet.move(-speed,0);
                break;
            case UP:
                bullet.move(0,-speed);
                break;
            case DOWN:
                bullet.move(0,speed);
                break;
                
            default:
                break;
        }
        window.draw(bullet);
    }
    
    Vector2f getPosition(){
        return bullet.getPosition();
    }
};
    
    




    class GameObject:public Sprite{
    private:
    public:
        int facingSide;
        Vector2f position;
        Sprite sprite;
        Texture texture;
        int type;
        string filePath;
        float scale;
        float speed=5.0f;
        RectangleShape bullet;
        Vector2f size;
        GameObject();
        
        GameObject(int type,Vector2f startingPosition,float speed,Vector2f size){
            this->size=size;
            this->speed=speed;
            bullet.setSize(size);
        }
        GameObject(int type,Vector2f position,string filePath,float scale){
            this->type=type;
            this->filePath=filePath;
            this->scale=scale;
            if(!texture.loadFromFile(resourcePath()+filePath)){}
            texture.setSmooth(false);
            sprite.setTexture(texture);
            sprite.setScale(scale, scale);
            if(type==MAP){
                sprite.setPosition(Vector2f(position.x*32,position.y*32));
            }
            else
                sprite.setPosition(position);
            sprite.setOrigin(getSize().x/2, getSize().y/2);
        }
        void update(){
            window.draw(sprite);
            if(type!=MAP){
                if(Keyboard::isKeyPressed(Keyboard::E)){
                    sprite.rotate(10);
                }
                if(Keyboard::isKeyPressed(Keyboard::Q)){
                    sprite.rotate(-10);
                }
            }
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
                    facingSide=UP;
                    sprite.setRotation(90);sprite.move(0,-speed);
                }
                if(dir==DOWN){
                    facingSide=DOWN;
                    sprite.setRotation(-90);sprite.move(0,speed);
                }
                if(dir==LEFT){
                    facingSide=LEFT;
                    sprite.setRotation(0);sprite.move(-speed,0);
                }
                if(dir==RIGHT){
                    facingSide=RIGHT;
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
        
        float getSpeed(){
            return speed;
        }
        void setSpeed(float speed){
            this->speed=speed;
        }
    };

#endif /* GameObject_hpp */
