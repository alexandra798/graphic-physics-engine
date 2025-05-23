#include "PointMateriel.h"
#include "Vecteur.h"
#include <iostream>
#include <stdexcept>
#include <memory>

// Default constructor
PointMateriel::PointMateriel()
    : ObjetPhysique() {}

// Parameterized constructor
PointMateriel::PointMateriel(const Vecteur& position, const Vecteur& vitesse, double masse,
                           std::shared_ptr<ChampForces> champ,
                           std::shared_ptr<Contrainte> contrainte)
    : ObjetPhysique(position, vitesse, masse, champ, contrainte) {
    // 母类构造函数已经验证了参数
}

// 不显示力的affiche方法
void PointMateriel::affiche() const {
    std::cout << getMasse() << " # masse" << std::endl;
    std::cout << position() << " # position" << std::endl;
    std::cout << vitesse() << " # vitesse";
}

// 显示力的affiche方法
void PointMateriel::affiche(double temps) const {
    affiche();
    std::cout << std::endl;
    std::cout << force(temps) << " # force";
}

// Output operator - 只调用不带参数的affiche
std::ostream& operator<<(std::ostream& os, const PointMateriel& point) {
    point.affiche();
    return os;
}