#pragma once
#include "Vecteur.h"
#include <stdexcept>

// 前向声明以避免循环引用
class ObjetPhysique;

class ChampForces {
public:
    // 构造函数和虚析构函数
    ChampForces() = default;
    virtual ~ChampForces() = default;
    

    
    // 纯虚函数，计算作用于物理对象的力
    virtual Vecteur force(const ObjetPhysique& objet, double temps) const = 0;

}; 

