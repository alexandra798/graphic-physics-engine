#pragma once
#include "ChampForces.h"
#include "Vecteur.h"

// Déclaration anticipée pour éviter les inclusions circulaires
class PointMateriel;

class GravitationConstante : public ChampForces {
private:
    Vecteur gravitation;  // 重力向量

public:
    // 构造函数
    GravitationConstante();
    GravitationConstante(const Vecteur& g);
    
    // 继承自ChampForces的方法
    Vecteur force(const ObjetPhysique& objet, double temps) const override;
    
    // 访问器
    const Vecteur& getGravitation() const;
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const GravitationConstante& g);
};