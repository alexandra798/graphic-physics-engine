#include "Systeme.h"
#include "IntegrateurEulerCromer.h"
#include "PointMateriel.h"
#include "ChargeElectrique.h"
#include "ChampNewtonien.h"
#include "GravitationConstante.h"
#include "Libre.h"
#include <stdexcept>
#include <iomanip>

// 默认构造函数
Systeme::Systeme() 
    : integrateur(std::make_unique<IntegrateurEulerCromer>()),temps_actuel(0.0) {}

// 带积分器的构造函数
Systeme::Systeme(std::unique_ptr<Integrateur> integ)
    : integrateur(std::move(integ)), temps_actuel(0.0) {
    if (!integrateur) {
        throw std::runtime_error("积分器不能为空");
    }
}

// 添加物体
void Systeme::ajouter_objet(std::unique_ptr<ObjetPhysique> objet) {
    if (!objet) {
        throw std::runtime_error("不能添加空物体");
    }
    objets.push_back(std::move(objet));
}

// 添加约束
void Systeme::ajouter_contrainte(std::shared_ptr<Contrainte> contrainte) {
    if (!contrainte) {
        throw std::runtime_error("不能添加空约束");
    }
    contraintes.push_back(contrainte);
}

// 添加力场
void Systeme::ajouter_champ_forces(std::shared_ptr<ChampForces> champ) {
    if (!champ) {
        throw std::runtime_error("不能添加空力场");
    }
    champs.push_back(champ);
}

// 设置积分器
void Systeme::set_integrateur(std::unique_ptr<Integrateur> integ) {
    if (!integ) {
        throw std::runtime_error("积分器不能为空");
    }
    integrateur = std::move(integ);
}

// 为物体添加约束
void Systeme::ajouter_contrainte_a_objet(size_t index_contrainte, size_t index_objet) {
    if (index_contrainte >= contraintes.size()) {
        throw std::out_of_range("约束索引超出范围");
    }
    if (index_objet >= objets.size()) {
        throw std::out_of_range("物体索引超出范围");
    }
    objets[index_objet]->setContrainte(contraintes[index_contrainte]);
}

// 为物体添加力场
void Systeme::ajouter_champ_a_objet(size_t index_champ, size_t index_objet) {
    if (index_champ >= champs.size()) {
        throw std::out_of_range("力场索引超出范围");
    }
    if (index_objet >= objets.size()) {
        throw std::out_of_range("物体索引超出范围");
    }
    objets[index_objet]->setChampForces(champs[index_champ]);
}

// 系统演化
void Systeme::evolue(double dt) {
    if (!integrateur) {
        throw std::runtime_error("没有设置积分器");
    }
    
    // 对每个物体进行积分
    for (auto& objet : objets) {
        integrateur->integre(*objet, temps_actuel, dt);
    }
    
    // 更新时间
    temps_actuel += dt;
}

// 访问器
const ObjetPhysique& Systeme::get_objet(size_t i) const {
    if (i >= objets.size()) {
        throw std::out_of_range("物体索引超出范围");
    }
    return *objets[i];
}

const Contrainte& Systeme::get_contrainte(size_t i) const {
    if (i >= contraintes.size()) {
        throw std::out_of_range("约束索引超出范围");
    }
    return *contraintes[i];
}

const ChampForces& Systeme::get_champ(size_t i) const {
    if (i >= champs.size()) {
        throw std::out_of_range("力场索引超出范围");
    }
    return *champs[i];
}

// 输出运算符
std::ostream& operator<<(std::ostream& os, const Systeme& sys) {
    os << "Systeme : à t = " << sys.temps_actuel << " :" << std::endl;
    
    // 显示所有物体
    for (size_t i = 0; i < sys.objets.size(); ++i) {
        os << "Objet no " << (i + 1) << " : ";
        
        // 根据对象类型显示不同的标签
        if (dynamic_cast<const PointMateriel*>(sys.objets[i].get())) {
            os << "Point Matériel :" << std::endl;
        } else if (dynamic_cast<const ChargeElectrique*>(sys.objets[i].get())) {
            os << "Charge Électrique :" << std::endl;
        } else {
            os << "Objet Physique :" << std::endl;
        }
        
        // 显示参数
        os << sys.objets[i]->getParametres() << " # parametre" << std::endl;
        os << sys.objets[i]->getDeriveeParametres() << " # vitesse" << std::endl;
        os << sys.objets[i]->position() << " # position physique" << std::endl;
        os << sys.objets[i]->vitesse() << " # vitesse physique" << std::endl;
        os << sys.objets[i]->getMasse() << " # masse" << std::endl;
        
        // 显示约束信息
        os << "contrainte : contrainte ";
        if (dynamic_cast<const Libre*>(&sys.objets[i]->getContrainte())) {
            os << "Libre";
        } else {
            os << "Inconnue";
        }
        os << std::endl;
        
        if (i < sys.objets.size() - 1) {
            os << std::endl;
        }
    }
    
    // 显示所有力场
    if (!sys.champs.empty()) {
        os << std::endl;
        for (size_t i = 0; i < sys.champs.size(); ++i) {
            os << "Champ no " << (i + 1) << " : ";
            
            // 根据力场类型显示不同的信息
            if (auto cn = dynamic_cast<const ChampNewtonien*>(sys.champs[i].get())) {
                os << "champ newtonien, centre : " << cn->getCentre().position() 
                   << ", masse : " << cn->getCentre().getMasse();
            } else if (auto gc = dynamic_cast<const GravitationConstante*>(sys.champs[i].get())) {
                os << "gravitation constante : " << *gc;
            } else {
                os << "champ inconnu";
            }
            os << std::endl;
        }
    }
    
    // 显示所有约束
    if (!sys.contraintes.empty()) {
        os << std::endl;
        for (size_t i = 0; i < sys.contraintes.size(); ++i) {
            os << "Contrainte no " << (i + 1) << " : contrainte ";
            if (dynamic_cast<const Libre*>(sys.contraintes[i].get())) {
                os << "Libre";
            } else {
                os << "Inconnue";
            }
            if (i < sys.contraintes.size() - 1) {
                os << std::endl;
            }
        }
    }
    
    return os;
}