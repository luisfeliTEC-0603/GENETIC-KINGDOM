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
using namespace std;

class Tower {
private:
    int damage;
    int speed;
    int scope;
    int regTIme;
    int reloadTime;
    int type; //type = 1 arqueros, type = 2 magos, type = 3 artilleros
    string imageDir; // direccion de imagen asociada

public:
    Tower (int damage, int speed, int scope, int regTime, int reloadTime, int type, string imageDir);
    virtual void Upgrade1 ();
    virtual void Upgrade2 ();
    virtual void Upgrade3 ();
    virtual ~Tower() {} // destructor

};


#endif