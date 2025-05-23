#pragma once
#include "Dessinable.h"
#include "ObjetPhysique.h"
#include "ChampForces.h"
#include "Contrainte.h"
#include "Integrateur.h"
#include "SupportADessin.h"
#include <vector>
#include <memory>
#include <iostream>


class SupportADessin;

/**
 * @class Systeme
 * @brief 表示整个物理系统
 * 
 * 包含物理对象集合、约束集合、力场集合和一个积分器
 */
class Systeme : public Dessinable {
private:
    // 使用智能指针管理对象
    std::vector<std::unique_ptr<ObjetPhysique>> objets;
    std::vector<std::shared_ptr<Contrainte>> contraintes;
    std::vector<std::shared_ptr<ChampForces>> champs;
    std::unique_ptr<Integrateur> integrateur;
    double temps_actuel;

public:
    // 默认构造函数
    Systeme();
    
    // 带参数的构造函数
    Systeme(std::unique_ptr<Integrateur> integ);
    
    // 析构函数
    virtual ~Systeme() = default;
    
    // 删除拷贝构造和赋值（因为包含unique_ptr）
    Systeme(const Systeme&) = delete;
    Systeme& operator=(const Systeme&) = delete;
    
    // 移动构造和赋值
    Systeme(Systeme&&) = default;
    Systeme& operator=(Systeme&&) = default;
    
    // 添加物体到系统
    void ajouter_objet(std::unique_ptr<ObjetPhysique> objet);
    
    // 添加约束到系统
    void ajouter_contrainte(std::shared_ptr<Contrainte> contrainte);
    
    // 添加力场到系统
    void ajouter_champ_forces(std::shared_ptr<ChampForces> champ);
    
    // 设置积分器
    void set_integrateur(std::unique_ptr<Integrateur> integ);
    
    // 为第j个物体添加第i个约束
    void ajouter_contrainte_a_objet(size_t index_contrainte, size_t index_objet);
    
    // 为第j个物体添加第i个力场
    void ajouter_champ_a_objet(size_t index_champ, size_t index_objet);
    
    // 获取当前时间
    double get_temps() const { return temps_actuel; }
    
    // 设置当前时间
    void set_temps(double t) { temps_actuel = t; }
    
    // 系统演化一步
    void evolue(double dt);
    
    // 实现Dessinable接口
    virtual void dessine_sur(SupportADessin& support) override
    { support.dessine(*this); }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const Systeme& sys);
    
    // 获取对象数量（用于显示）
    size_t nombre_objets() const { return objets.size(); }
    size_t nombre_contraintes() const { return contraintes.size(); }
    size_t nombre_champs() const { return champs.size(); }
    
    // 访问器（只读）
    const ObjetPhysique& get_objet(size_t i) const;
    const Contrainte& get_contrainte(size_t i) const;
    const ChampForces& get_champ(size_t i) const;
};