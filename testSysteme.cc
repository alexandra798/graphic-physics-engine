#include "Systeme.h"
#include "PointMateriel.h"
#include "ChampNewtonien.h"
#include "Libre.h"
#include "IntegrateurEulerCromer.h"
#include <iostream>
#include <memory>

int main() {
    // 创建系统
    Systeme systeme;
    
    // 创建约束
    auto contrainte_libre = std::make_shared<Libre>();
    systeme.ajouter_contrainte(contrainte_libre);
    
    // 创建第一个物体（地球）
    auto terre = std::make_unique<PointMateriel>(
        Vecteur(0, 0, 0),      // 位置
        Vecteur(0, 0, 0),      // 速度
        5.972e24               // 质量（kg）
    );
    
    // 为显示牛顿力场，需要保存地球的共享指针
    auto terre_ptr = std::make_shared<PointMateriel>(
        Vecteur(0, 0, 0),
        Vecteur(0, 0, 0),
        5.972e24
    );
    
    // 创建第二个物体（卫星）
    auto satellite = std::make_unique<PointMateriel>(
        Vecteur(6.37101e6, 0, 0),  // 位置（地球半径处）
        Vecteur(0, 0, 0),           // 速度
        0.1                         // 质量（kg）
    );
    
    // 为显示牛顿力场，需要保存卫星的共享指针
    auto satellite_ptr = std::make_shared<PointMateriel>(
        Vecteur(6.37101e6, 0, 0),
        Vecteur(0, 0, 0),
        0.1
    );
    
    // 创建力场
    auto champ1 = std::make_shared<ChampNewtonien>(terre_ptr);
    auto champ2 = std::make_shared<ChampNewtonien>(satellite_ptr);
    
    // 添加力场到系统
    systeme.ajouter_champ_forces(champ1);
    systeme.ajouter_champ_forces(champ2);
    
    // 添加物体到系统
    systeme.ajouter_objet(std::move(terre));
    systeme.ajouter_objet(std::move(satellite));
    
    // 为物体设置约束
    systeme.ajouter_contrainte_a_objet(0, 0);  // 地球使用自由约束
    systeme.ajouter_contrainte_a_objet(0, 1);  // 卫星使用自由约束
    
    // 显示系统
    std::cout << systeme << std::endl;
    
    return 0;
}