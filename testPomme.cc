#include <iostream>
#include <iomanip>
#include <memory>
#include "PointMateriel.h"
#include "ChampNewtonien.h"
#include "Libre.h"
#include "IntegrateurEulerCromer.h"

int main() {
    // 物理常数
    const double RAYON_TERRE = 6.371e6;        // 地球半径（米）
    const double MASSE_TERRE = 5.972e24;       // 地球质量（千克）
    const double MASSE_POMME = 0.1;            // 苹果质量（千克）
    const double ALTITUDE_INITIALE = 10.0;     // 初始高度（米）
    const double DT = 1e-3;                    // 时间步长（秒）
    
    // 创建地球（作为中心天体，位于原点）
    auto terre = std::make_shared<PointMateriel>(
        Vecteur(0.0, 0.0, 0.0),                // 地球位置（原点）
        Vecteur(0.0, 0.0, 0.0),                // 地球速度（静止）
        MASSE_TERRE                             // 地球质量
    );
    
    // 创建牛顿引力场（地球作为引力中心）
    auto champ_gravite = std::make_shared<ChampNewtonien>(terre);
    
    // 创建自由约束
    auto contrainte_libre = std::make_shared<Libre>();
    
    // 创建苹果（位于地球表面上方10米处）
    auto pomme = std::make_shared<PointMateriel>(
        Vecteur(0.0, RAYON_TERRE + ALTITUDE_INITIALE, 0.0),  // 初始位置
        Vecteur(0.0, 0.0, 0.0),                               // 初始速度（静止）
        MASSE_POMME,                                          // 苹果质量
        champ_gravite,                                        // 引力场
        contrainte_libre                                      // 约束
    );
    
    // 创建Euler-Cromer积分器
    IntegrateurEulerCromer integrateur;
    
    // 输出格式设置
    std::cout << std::fixed << std::setprecision(4);
    
    // 模拟参数
    double temps = 0.0;
    
    // 第一部分：输出前100步的高度
    for (int i = 0; i <= 100; ++i) {
        // 计算当前高度
        Vecteur pos = pomme->position();
        double altitude = pos.norme() - RAYON_TERRE;
        
        // 输出时间和高度
        std::cout << temps << "  " << std::setprecision(6) << altitude << std::endl;
        
        // 进行一步积分（除了最后一次）
        if (i < 100) {
            integrateur.integre(*pomme, temps, DT);
            temps += DT;
        }
    }
    
    std::cout << std::endl;
    std::cout << std::endl;
    
    // 重置模拟
    temps = 0.0;
    std::cout << std::setprecision(4);
    
    // 重新创建苹果
    pomme = std::make_shared<PointMateriel>(
        Vecteur(0.0, RAYON_TERRE + ALTITUDE_INITIALE, 0.0),
        Vecteur(0.0, 0.0, 0.0),
        MASSE_POMME,
        champ_gravite,
        contrainte_libre
    );
    
    // 第二部分：输出前1.4秒，每0.1秒输出一次
    const int STEPS_PER_OUTPUT = 100;  // 每100步输出一次（0.1秒）
    const int TOTAL_OUTPUTS = 15;      // 总共输出15次（0到1.4秒）
    
    for (int output = 0; output < TOTAL_OUTPUTS; ++output) {
        // 计算当前高度
        Vecteur pos = pomme->position();
        double altitude = pos.norme() - RAYON_TERRE;
        
        // 输出时间和高度
        std::cout << temps << "  " << std::setprecision(6) << altitude << std::endl;
        
        // 进行100步积分（除了最后一次）
        if (output < TOTAL_OUTPUTS - 1) {
            for (int step = 0; step < STEPS_PER_OUTPUT; ++step) {
                integrateur.integre(*pomme, temps, DT);
                temps += DT;
            }
        }
    }
    
    return 0;
}