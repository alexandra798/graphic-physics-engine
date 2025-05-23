#include <iostream>
#include <memory>
#include <iomanip>
#include "Systeme.h"
#include "PointMateriel.h"
#include "ChampNewtonien.h"
#include "Libre.h"
#include "IntegrateurEulerCromer.h"

int main() {
    try {
        // 创建系统
        Systeme systeme;
        
        // 创建地球（质心在原点）
        double masse_terre = 5.972e24;  // 单位：kg
        double rayon_terre = 6371e3;    // 单位：m
        
        auto terre = std::make_shared<PointMateriel>(
            Vecteur(0, 0, 0),           // 位置
            Vecteur(0, 0, 0),           // 速度
            masse_terre,                // 质量
            nullptr,                    // 暂时没有力场
            std::make_shared<Libre>()   // 自由约束
        );
        
        // 创建苹果（在地球表面上方10米处）
        double masse_pomme = 0.1;       // 单位：kg
        double altitude = rayon_terre + 10.0;  // 距离地心的距离
        
        auto pomme = std::make_shared<PointMateriel>(
            Vecteur(0, 0, altitude),    // 位置
            Vecteur(0, 0, 0),           // 初始速度为0
            masse_pomme,                // 质量
            nullptr,                    // 暂时没有力场
            std::make_shared<Libre>()   // 自由约束
        );
        
        // 创建牛顿引力场
        auto champ_newton = std::make_shared<ChampNewtonien>(terre);
        
        // 将对象添加到系统
        systeme.ajoute_objet(terre);
        systeme.ajoute_objet(pomme);
        
        // 添加力场
        systeme.ajoute_champ(champ_newton);
        
        // 应用力场到苹果
        systeme.applique_champ(0, 1);  // 地球的引力作用于苹果
        
        // 设置积分器（Euler-Cromer方法，时间步长1ms）
        systeme.set_integrateur(std::make_shared<IntegrateurEulerCromer>());
        
        // 设置输出精度
        std::cout << std::fixed << std::setprecision(6);
        
        // 初始状态
        std::cout << "=== 初始状态 ===" << std::endl;
        std::cout << "时间: 0.000000 s" << std::endl;
        std::cout << "苹果位置: " << pomme->position() << std::endl;
        std::cout << "苹果速度: " << pomme->vitesse() << std::endl;
        std::cout << "苹果加速度: " << pomme->evolution(0) << std::endl;
        std::cout << std::endl;
        
        // 模拟参数
        double dt = 1e-3;  // 时间步长：1ms
        double temps_total = 2.0;  // 总模拟时间：2秒
        int pas = 0;
        
        // 开始模拟
        while (systeme.get_temps() < temps_total) {
            // 演化系统
            systeme.evolue(dt);
            
            // 每100步输出一次状态
            if (pas % 100 == 0) {
                std::cout << "=== 时间: " << systeme.get_temps() << " s ===" << std::endl;
                std::cout << "苹果位置: " << pomme->position() << std::endl;
                std::cout << "苹果速度: " << pomme->vitesse() << std::endl;
                std::cout << "苹果加速度: " << pomme->evolution(systeme.get_temps()) << std::endl;
                std::cout << std::endl;
            }
            
            pas++;
        }
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }
} 