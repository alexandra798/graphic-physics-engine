#include <iostream>
#include <memory>
#include "PointMateriel.h"
#include "GravitationConstante.h"
#include "Libre.h"
#include "Vecteur.h"

using namespace std;

int main() {
    try {
        // 创建垂直向下的重力场 (0, 0, -9.81)
        auto gravite = make_shared<GravitationConstante>(Vecteur(0.0, 0.0, -9.81));
        
        // 创建自由约束（无约束）
        auto libre = make_shared<Libre>();
        
        // 显示重力场信息
        cout << "Nous avons :" << endl;
        cout << "un champ de force :" << endl;
        cout << *gravite << endl;
        cout << endl;
        
        // 创建第一个点质量
        // 质量：0.1 kg
        // 位置：(1, 2, 3)
        // 速度：(0, 0.1, 0.2)
        PointMateriel point1(
            Vecteur(1.0, 2.0, 3.0),      // position
            Vecteur(0.0, 0.1, 0.2),       // vitesse
            0.1,                          // masse
            gravite,                      // champ de force
            libre                         // contrainte
        );
        
        // 创建第二个点质量
        // 质量：2 kg
        // 位置：(-1.1, 1.2, 1.3)
        // 速度：(0.2, 0.1, 0)
        PointMateriel point2(
            Vecteur(-1.1, 1.2, 1.3),      // position
            Vecteur(0.2, 0.1, 0.0),       // vitesse
            2.0,                          // masse
            gravite,                      // champ de force
            libre                         // contrainte
        );
        
        // 显示第一个点质量的信息
        cout << "un point matériel :" << endl;
        point1.affiche(0.0);  // 显示在时间 t=0 时的状态
        cout << endl << endl;
        
        // 显示第二个点质量的信息
        cout << "et un autre point matériel :" << endl;
        point2.affiche(0.0);  // 显示在时间 t=0 时的状态
        cout << endl;
        
        // 可选：测试更多功能
        cout << "\n--- Tests supplémentaires ---" << endl;
        
        // 测试能量计算
        cout << "\nÉnergie cinétique du premier point : " 
             << point1.energieCinetique() << " J" << endl;
        cout << "Énergie cinétique du second point : " 
             << point2.energieCinetique() << " J" << endl;
        
        // 测试evolution方法（加速度）
        cout << "\nAccélération du premier point : " 
             << point1.evolution(0.0) << " m/s²" << endl;
        cout << "Accélération du second point : " 
             << point2.evolution(0.0) << " m/s²" << endl;
        
        // 测试没有重力场的点质量
        cout << "\n--- Point sans champ de force ---" << endl;
        PointMateriel point3(
            Vecteur(0.0, 0.0, 0.0),       // position
            Vecteur(1.0, 0.0, 0.0),       // vitesse
            1.0                           // masse
        );
        cout << "Point matériel sans champ :" << endl;
        cout << point3 << endl;
        cout << "Force : " << point3.force(0.0) << " # (devrait être nulle)" << endl;
        
    } catch (const exception& e) {
        cerr << "Erreur : " << e.what() << endl;
        return 1;
    }
    
    return 0;
}