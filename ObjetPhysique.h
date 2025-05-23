#pragma once
#include "ObjetMobile.h"
#include "ChampForces.h"
#include "Contrainte.h"
#include <memory>
#include <iostream>
#include <stdexcept>

class ObjetPhysique : public ObjetMobile {
private:

    std::shared_ptr<ChampForces> champ;    // 力场
    std::shared_ptr<Contrainte> contrainte; // 约束
    double masse;

public:
    // 构造函数
    ObjetPhysique();
    // 在ObjetPhysique.h中修改为
    ObjetPhysique(const Vecteur& param, const Vecteur& deriv, double m = 1.0,
              std::shared_ptr<ChampForces> ch = nullptr,
              std::shared_ptr<Contrainte> con = nullptr);  // 移除实现部分，只保留声明
    

    // 析构函数
    virtual ~ObjetPhysique() = default;


    // 访问器
    
    const ChampForces& getChampForces() const;
    const Contrainte& getContrainte() const;
    
    // 修改器

    void setChampForces(std::shared_ptr<ChampForces> ch);
    void setContrainte(std::shared_ptr<Contrainte> con);

    
    // 计算作用在物体上的力
    Vecteur force(double temps = 0) const;
    
    
    // 获取物体的实际位置和速度
    Vecteur position() const;  
    Vecteur vitesse() const;

    double getMasse() const;  
    
    // 继承自ObjetMobile的虚函数，计算运动方程
    Vecteur evolution(double temps) const override;

    
    double energieCinetique() const {
        // 计算 E = 1/2 * m * v^2
        return 0.5 * getMasse() * vitesse().norme2();
    }
    
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const ObjetPhysique& obj);


}; 