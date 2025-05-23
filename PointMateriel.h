#pragma once
#include "ObjetPhysique.h"
#include "Dessinable.h"
#include "SupportADessin.h"
#include <memory>
#include "Vecteur.h"
#include "ChampForces.h"
#include "Contrainte.h"

class PointMateriel : public ObjetPhysique, public Dessinable {
public:
    // Constructors
    PointMateriel();
    PointMateriel(const Vecteur& position, const Vecteur& vitesse, double masse,
                  std::shared_ptr<ChampForces> champ = nullptr,
                  std::shared_ptr<Contrainte> contrainte = nullptr);

    // Destructor
    virtual ~PointMateriel() = default;

    // 实现Dessinable的绘制方法
    virtual void dessine_sur(SupportADessin& support) override
    { support.dessine(*this); }

    // 添加显示方法
    void affiche() const;
    void affiche(double temps) const;

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const PointMateriel& point);
};