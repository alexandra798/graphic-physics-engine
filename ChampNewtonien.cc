#include "ChampNewtonien.h"
#include "ObjetPhysique.h"

// 构造函数
ChampNewtonien::ChampNewtonien(std::shared_ptr<ObjetPhysique> centre)
    : ForceCentrale(centre) {}

// 计算牛顿引力
Vecteur ChampNewtonien::force(const ObjetPhysique& objet, double /* temps */) const {
    // 获取质量
    double masse_objet = objet.getMasse();
    double masse_centre = centre->getMasse();
    
    // 计算平方反比力向量
    Vecteur force_direction = quadratique_inverse(objet);
    
    // 计算牛顿引力：F = G * m1 * m2 / r^2
    return force_direction * (G * masse_objet * masse_centre);
} 