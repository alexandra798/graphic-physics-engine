#pragma once
#include "Vecteur.h"
#include <stdexcept>

// 前向声明以避免循环引用
class ObjetPhysique;

class Contrainte {
public:
    // 构造函数和虚析构函数
    Contrainte() = default;
    virtual ~Contrainte() = default;
    



    virtual Vecteur applique_force(const ObjetPhysique& objet, const Vecteur& force, double temps) const = 0;

    virtual Vecteur position(const ObjetPhysique& objet) const = 0;

    virtual Vecteur vitesse(const ObjetPhysique& objet) const = 0;
    

}; 