#pragma once
#include "Dessinable.h"
#include "ObjetPhysique.h"
#include "ChampForces.h"
#include "Contrainte.h"
#include "Integrateur.h"
#include <memory>
#include <vector>
#include <iostream>

// 更新后的Systeme类，包含了之前Contenu类的功能
class Systeme : public Dessinable {
private:
    // 物理系统组件
    std::vector<std::shared_ptr<ObjetPhysique>> objets;
    std::vector<std::shared_ptr<ChampForces>> champs;
    std::vector<std::shared_ptr<Contrainte>> contraintes;
    std::shared_ptr<Integrateur> integrateur;
    

    double temps;
    
public:
    // 构造函数
    Systeme();
    Systeme(std::shared_ptr<Integrateur> integ);
    //...
    
    // 析构函数
    virtual ~Systeme() = default;
    
    // 添加物理组件的方法
    void ajoute_objet(std::shared_ptr<ObjetPhysique> objet);
    void ajoute_contrainte(std::shared_ptr<Contrainte> contrainte);
    void ajoute_champ(std::shared_ptr<ChampForces> champ);
    


    
    // 设置积分器
    void set_integrateur(std::shared_ptr<Integrateur> integ);
    
    // 将约束和力场应用到物体的方法
    void applique_contrainte(size_t i_contrainte, size_t i_objet);
    void applique_champ(size_t i_champ, size_t i_objet);
    
    // 时间演化方法
    void evolue(double dt);
    
    // 获取当前时间
    double get_temps() const;
    
    // 获取系统组件
    const std::vector<std::shared_ptr<ObjetPhysique>>& get_objets() const;
    const std::vector<std::shared_ptr<ChampForces>>& get_champs() const;
    const std::vector<std::shared_ptr<Contrainte>>& get_contraintes() const;

    
    // 从Dessinable继承的方法
    virtual void dessine_sur(SupportADessin& support) override;
    
    // 输出运算符
    friend std::ostream& operator<<(std::ostream& os, const Systeme& systeme);
};