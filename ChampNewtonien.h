#pragma once
#include "ForceCentrale.h"

class ChampNewtonien : public ForceCentrale {
private:
    static constexpr double G = 6.67430e-11;  // 万有引力常数，单位：m^3 kg^-1 s^-2
    
public:
    // 构造函数
    ChampNewtonien(std::shared_ptr<ObjetPhysique> centre);
    
    // 计算牛顿引力
    Vecteur force(const ObjetPhysique& objet, double temps) const override;
}; 