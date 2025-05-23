#include "ObjetPhysique.h"
#include <stdexcept>

#include <iostream>

// 构造函数实现
ObjetPhysique::ObjetPhysique()
    : ObjetMobile(), masse(1.0) {}

ObjetPhysique::ObjetPhysique(const Vecteur& param, const Vecteur& deriv, double m,
                           std::shared_ptr<ChampForces> ch,
                           std::shared_ptr<Contrainte> con)
    : ObjetMobile(param, deriv), champ(ch), contrainte(con), masse(m) {
    if (masse <= 0) {
        throw std::runtime_error("质量必须为正值");
    }
}

// 访问器


const ChampForces& ObjetPhysique::getChampForces() const {
    if (!champ) {
        throw std::runtime_error("未设置力场");
    }
    return *champ;
}

const Contrainte& ObjetPhysique::getContrainte() const {
    if (!contrainte) {
        throw std::runtime_error("未设置约束");
    }
    return *contrainte;
}

// 修改器


void ObjetPhysique::setChampForces(std::shared_ptr<ChampForces> ch) {
    champ = ch;
}

void ObjetPhysique::setContrainte(std::shared_ptr<Contrainte> con) {
    contrainte = con;
}

// 计算作用在物体上的力
Vecteur ObjetPhysique::force(double temps) const {
    if (!champ) {
        // 如果没有设置力场，返回零向量
        return Vecteur(3);
    }
    return champ->force(*this, temps);
}

// 获取物体的实际位置
Vecteur ObjetPhysique::position() const {
    if (!contrainte) {
        // 如果没有设置约束，直接返回参数向量
        return getParametres();
    }
    return contrainte->position(*this);
}

// 获取物体的实际速度
Vecteur ObjetPhysique::vitesse() const {
    if (!contrainte) {
        // 如果没有设置约束，直接返回参数导数向量
        return getDeriveeParametres();
    }
    return contrainte->vitesse(*this);
}

// 计算物体的运动方程
Vecteur ObjetPhysique::evolution(double temps) const {
    if (!contrainte) {
        // 如果没有设置约束，返回零向量
        return Vecteur(3);
    }
    
    // 计算力并应用约束
    Vecteur f = force(temps);
    return contrainte->applique_force(*this, f, temps);
}

// 输出运算符重载
std::ostream& operator<<(std::ostream& os, const ObjetPhysique& obj) {
    os << obj.getMasse() << " # 质量" << std::endl;
    os << obj.position() << " # 位置" << std::endl;
    os << obj.vitesse() << " # 速度";
    return os;
}

// 访问器实现
double ObjetPhysique::getMasse() const {
    return masse;
} 