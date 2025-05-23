#pragma once
#include "Contrainte.h"
#include "Vecteur.h"

// 前向声明
class ObjetPhysique;

class Libre : public Contrainte {
public:
    // 构造函数
    Libre() = default;
    
    // 实现基类的抽象方法
    Vecteur applique_force(const ObjetPhysique& objet, const Vecteur& force, double temps) const override;
    
    Vecteur position(const ObjetPhysique& objet) const override;
    
    Vecteur vitesse(const ObjetPhysique& objet) const override;
};