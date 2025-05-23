#include "GravitationConstante.h"
#include "ObjetPhysique.h"
#include "constantes.h"
#include <iostream>

// 默认构造函数使用地球重力常数
GravitationConstante::GravitationConstante()
    : gravitation(constantes::g) {}

// 使用指定重力向量的构造函数
GravitationConstante::GravitationConstante(const Vecteur& g)
    : gravitation(g) {}

// 计算作用于物理对象的重力
Vecteur GravitationConstante::force(const ObjetPhysique& objet, double /* temps */) const {
    // F = m * g
    return gravitation * objet.getMasse();
}

// 获取重力向量
const Vecteur& GravitationConstante::getGravitation() const {
    return gravitation;
}

// 输出运算符重载
std::ostream& operator<<(std::ostream& os, const GravitationConstante& g) {
    os << g.getGravitation() << " # 重力强度";
    return os;
}