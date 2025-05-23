#pragma once
#include "ChampForces.h"
#include <memory>

class ForceCentrale : public ChampForces {
protected:
    std::shared_ptr<ObjetPhysique> centre;  // 中心物体
    
    // 计算平方反比力矢量
    Vecteur quadratique_inverse(const ObjetPhysique& objet) const;
    
public:
    // 构造函数
    ForceCentrale(std::shared_ptr<ObjetPhysique> centre);
    
    // 析构函数
    virtual ~ForceCentrale() = default;
    
    // 纯虚函数，需要由子类实现
    virtual Vecteur force(const ObjetPhysique& objet, double temps) const override = 0;
}; 