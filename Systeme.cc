#include "Systeme.h"
#include "SupportADessin.h"
#include "IntegrateurEulerCromer.h" // 默认积分器
#include <stdexcept>

// 默认构造函数
Systeme::Systeme()
    : integrateur(std::make_shared<IntegrateurEulerCromer>()), temps(0.0) {}

// 带积分器的构造函数
Systeme::Systeme(std::shared_ptr<Integrateur> integ)
    : integrateur(integ), temps(0.0) {
    if (!integ) {
        throw std::runtime_error("无效的积分器");
    }
}

// 添加物理对象
void Systeme::ajoute_objet(std::shared_ptr<ObjetPhysique> objet) {
    if (!objet) {
        throw std::runtime_error("无法添加空对象");
    }
    objets.push_back(objet);
}

// 添加约束
void Systeme::ajoute_contrainte(std::shared_ptr<Contrainte> contrainte) {
    if (!contrainte) {
        throw std::runtime_error("无法添加空约束");
    }
    contraintes.push_back(contrainte);
}

// 添加力场
void Systeme::ajoute_champ(std::shared_ptr<ChampForces> champ) {
    if (!champ) {
        throw std::runtime_error("无法添加空力场");
    }
    champs.push_back(champ);
}



// 设置积分器
void Systeme::set_integrateur(std::shared_ptr<Integrateur> integ) {
    if (!integ) {
        throw std::runtime_error("无效的积分器");
    }
    integrateur = integ;
}

// 应用约束到物体
void Systeme::applique_contrainte(size_t i_contrainte, size_t i_objet) {
    if (i_contrainte >= contraintes.size()) {
        throw std::out_of_range("约束索引超出范围");
    }
    if (i_objet >= objets.size()) {
        throw std::out_of_range("物体索引超出范围");
    }
    
    objets[i_objet]->setContrainte(contraintes[i_contrainte]);
}

// 应用力场到物体
void Systeme::applique_champ(size_t i_champ, size_t i_objet) {
    if (i_champ >= champs.size()) {
        throw std::out_of_range("力场索引超出范围");
    }
    if (i_objet >= objets.size()) {
        throw std::out_of_range("物体索引超出范围");
    }
    
    objets[i_objet]->setChampForces(champs[i_champ]);
}

// 时间演化方法
void Systeme::evolue(double dt) {
    if (dt <= 0) {
        throw std::runtime_error("时间步长必须为正");
    }
    if (!integrateur) {
        throw std::runtime_error("未设置积分器");
    }
    
    // 为系统中的每个物理对象应用积分器
    for (auto& objet : objets) {
        integrateur->integre(*objet, temps);
    }
    

    
    // 更新系统时间
    temps += dt;
}

// 获取当前时间
double Systeme::get_temps() const {
    return temps;
}

// 获取系统组件
const std::vector<std::shared_ptr<ObjetPhysique>>& Systeme::get_objets() const {
    return objets;
}

const std::vector<std::shared_ptr<ChampForces>>& Systeme::get_champs() const {
    return champs;
}

const std::vector<std::shared_ptr<Contrainte>>& Systeme::get_contraintes() const {
    return contraintes;
}



// 绘制方法
void Systeme::dessine_sur(SupportADessin& support) {
    // 首先绘制物理系统
    support.dessine(*this);
    

}

// 输出运算符重载
std::ostream& operator<<(std::ostream& os, const Systeme& systeme) {
    os << "Systeme : à t = " << systeme.temps << " :" << std::endl;
    
    // 输出物体信息
    for (size_t i = 0; i < systeme.objets.size(); ++i) {
        os << "Objet no " << (i + 1) << " : ";
        if (auto point = std::dynamic_pointer_cast<PointMateriel>(systeme.objets[i])) {
            os << "Point Matériel :" << std::endl;
        } else {
            os << "Objet Physique:" << std::endl;
        }
        
        os << *systeme.objets[i] << std::endl;
        
        // 输出约束信息
        os << "contrainte : ";
        try {
            os << "contrainte " << typeid(systeme.objets[i]->getContrainte()).name() << std::endl;
        } catch (const std::exception&) {
            os << "aucune contrainte" << std::endl;
        }
        os << std::endl;
    }
    
    // 输出力场信息
    for (size_t i = 0; i < systeme.champs.size(); ++i) {
        os << "Champ no " << (i + 1) << " : ";
        if (auto newtonien = dynamic_cast<const ChampNewtonien*>(systeme.champs[i].get())) {
            os << "champ newtonien";
            // 这里可以添加更多关于牛顿力场的信息
        } else {
            os << "champ de force";
        }
        os << std::endl;
    }
    
    // 输出约束信息
    for (size_t i = 0; i < systeme.contraintes.size(); ++i) {
        os << "Contrainte no " << (i + 1) << " : ";
        if (auto libre = dynamic_cast<const Libre*>(systeme.contraintes[i].get())) {
            os << "contrainte Libre";
        } else {
            os << "contrainte";
        }
        os << std::endl;
    }
    

    }
    
    return os;
}