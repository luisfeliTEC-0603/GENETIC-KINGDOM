/*
Cada torre tiene los siguientes atributos: 
-daño
-velocidad
-alcance 
-tiempo de regeneración del poder especial
-tiempo de recarga de ataque

Las torres atacan a los enemigos cuando están en su alcance. Con cada 
muerte de enemigo, se considera su categoría y tipo para devolver cierta 
cantidad de oro al jugador. La cantidad de oro retornado debe ser 
calculado de forma justa y consistente. El grupo de trabajo define esto. 

Cada torre debe tener 3 upgrades

Hay 3 tipos de torres: 
• Arqueros: bajo costo, alto alcance, poco daño, tiempo de recarga de 
ataque bajo 
• Magos: costo medio, alcance medio, daño medio, tiempo de recarga 
de ataque medio 
• Artilleros:  costo  alto,  alcance  bajo,  daño  alto,  tiempo  de  recarga  de 
ataque alto 

*/
#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <iostream>
#include <vector>
#include "../Enemies/gameEnemies.hpp"

using namespace std;

struct Bullet {
    Vector2 position;
    Vector2 direction;
    float speed;
    int damage;
    Enemy* selectedEnemy;

    Bullet(Vector2 pos, Vector2 dir, float spd, int dmg, Enemy* selected)
        : position(pos), direction(dir), speed(spd), damage(dmg), selectedEnemy(selected){}
};


class Tower {
private:
    int xpos;
    int ypos;
    int damage;
    int speed;
    int scope;
    int regTime;
    int reloadTime;
    int activeBullets = 0;
    float timeSinceLastShot = 0.0f;
    int type; //type = 1 arqueros, type = 2 magos, type = 3 artilleros
    int towerVision;
    int actualLevel = 0;

public:
    Tower (int xpos, int ypos, int damage, int speed, int scope, int regTime, int reloadTime, int type, int vision);
    virtual void Upgrade1 ();
    virtual void Upgrade2 ();
    virtual void Upgrade3 ();
    virtual void CheckIfEnemiesInRange(vector<Enemy*>& enemies, vector<Bullet>& bulletList, float deltaTime);
    virtual void ShootEnemy(Enemy& enemy, vector<Bullet>& bulletList);

    virtual ~Tower() = default;

    //Getters and setters for the upgrades
    // Getters
    int getDamage() const { return damage; }
    int getSpeed() const { return speed; }
    int getScope() const { return scope; }
    int getRegTime() const { return regTime; }
    int getReloadTime() const { return reloadTime; }
    int getType() const { return type; }
    int getXpos() const { return xpos; }
    int getYpos() const { return ypos; }
    int getActiveBullets() const { return activeBullets; }
    int getVision() const {return towerVision;}
    int getLevel() const {return actualLevel;}

    // Setters
    void setDamage(int d) { damage = d; }
    void setSpeed(int s) { speed = s; }
    void setScope(int sc) { scope = sc; }
    void setRegTime(int rt) { regTime = rt; }
    void setReloadTime(int rlt) { reloadTime = rlt; }
    void setType(int t) { type = t; }
    void setActiveBullets(int count) { activeBullets = count; }
    void setVisionPos (int newPos) { towerVision = newPos;}

    // Extra functions
    void increaseLevel () {actualLevel++;}

};


#endif