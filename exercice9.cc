#include <iostream>
#include <memory>
#include "Systeme.h"
#include "PointMateriel.h"
#include "GravitationConstante.h"
#include "Libre.h"
#include "IntegrateurEulerCromer.h"
#include "TextViewer.h"

int main() {
    try {
        // 创建系统
        auto integrateur = std::make_shared<IntegrateurEulerCromer>(0.01);
        Systeme systeme(integrateur);
        
        // 创建重力场
        auto gravite = std::make_shared<GravitationConstante>();
        
        // 创建自由约束
        auto libre = std::make_shared<Libre>();
        
        // 添加约束和力场到系统
        systeme.ajoute_contrainte(libre);
        systeme.ajoute_champ(gravite);
        
        // 创建苹果（初始高度为10米，初始速度为0）
        auto pomme = std::make_shared<PointMateriel>(
            Vecteur(0, 0, 10),  // 初始位置
            Vecteur(0, 0, 0),   // 初始速度
            0.1,                 // 质量（kg）
            gravite,             // 重力场
            libre                // 自由约束
        );
        
        // 添加苹果到系统
        systeme.ajoute_objet(pomme);
        
        // 创建文本查看器
        TextViewer viewer(std::cout);
        
        // 初始状态
        std::cout << "Initial state:" << std::endl;
        systeme.dessine_sur(viewer);
        std::cout << std::endl;
        
        // 模拟下落
        double dt = 0.1;  // 时间步长
        
        for (int i = 0; i < 10; ++i) {
            // 演化系统
            systeme.evolue(dt);
            
            // 显示状态
            std::cout << "After " << (i + 1) * dt << " seconds:" << std::endl;
            systeme.dessine_sur(viewer);
            std::cout << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}