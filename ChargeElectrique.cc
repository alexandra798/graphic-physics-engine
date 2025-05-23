#include "ChargeElectrique.h"
#include "Vecteur.h"
#include "SupportADessin.h"
#include <iostream>
#include <stdexcept>
#include <memory>
#include "ChargeElectrique.h"

// 默认构造函数
ChargeElectrique::ChargeElectrique()
    : ObjetPhysique() {}

// 带参数的构造函数
ChargeElectrique::ChargeElectrique(const Vecteur& position, const Vecteur& vitesse, 
                                 double masse, 
                                 std::shared_ptr<ChampForces> champ,
                                 std::shared_ptr<Contrainte> contrainte)
    : ObjetPhysique(position, vitesse, masse, champ, contrainte) {
    
    // 确保位置和速度具有相同的维度
    if (!(position.memeDimension(vitesse))) {
        throw std::runtime_error("位置和速度的维度必须相同");
    }
    
    // 确保质量为正值
    if (masse <= 0) {
        throw std::runtime_error("质量必须为正值");
    }
}

// 计算电荷的演化方程（F = ma）
Vecteur ChargeElectrique::evolution(double temps) const {
    // 使用物理对象的力除以质量得到加速度
    return force(temps) * (1.0 / getMasse());
}

// 输出运算符重载
std::ostream& operator<<(std::ostream& os, const ChargeElectrique& charge) {
    os << static_cast<const ObjetPhysique&>(charge) << std::endl;
    
    // 计算并显示t=0时的力
    os << charge.force(0) << " # 力（电荷）";
    
    return os;
}