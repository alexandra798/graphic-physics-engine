#pragma once
#include "ForceCentrale.h"
#include "ObjetPhysique.h"
#include "Vecteur.h"

class ChampNewtonien : public ForceCentrale {
private:
    static constexpr double G = 6.67430e-11;  // 万有引力常数，单位：m^3 kg^-1 s^-2
    
public:
    // 构造函数
    ChampNewtonien(std::shared_ptr<ObjetPhysique> centre);
    
    // 计算牛顿引力
    Vecteur force(const ObjetPhysique& objet, double temps) const override;
    
    // 获取中心物体（用于显示）
    const ObjetPhysique& getCentre() const { return *centre; }
};