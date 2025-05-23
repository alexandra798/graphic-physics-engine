#pragma once
#include "ObjetPhysique.h"
#include "Dessinable.h"
#include "SupportADessin.h"
#include <memory>

class ChargeElectrique : public ObjetPhysique, public Dessinable {
private:
    double charge;
public:
    // 构造函数
    ChargeElectrique();
    ChargeElectrique(const Vecteur& position, const Vecteur& vitesse, 
                 double masse, 
                 std::shared_ptr<ChampForces> champ = nullptr,
                 std::shared_ptr<Contrainte> contrainte = nullptr);

    // 获取电荷量
    double getCharge() const;
    
    // 设置电荷量
    void setCharge(double q);
    
    // 计算运动方程（实现ObjetMobile中的虚函数）
    virtual Vecteur evolution(double temps) const override;
    
    // 实现Dessinable的绘制方法
    virtual void dessine_sur(SupportADessin& support) override {
        support.dessine(*this); }
    
    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const ChargeElectrique& pm);
};