#pragma once
#include "ObjetPhysique.h"
#include <memory>

class PointMateriel : public ObjetPhysique {
public:
    // Constructors
    PointMateriel();
    PointMateriel(const Vecteur& position, const Vecteur& vitesse, double masse,
                  std::shared_ptr<ChampForces> champ = nullptr,
                  std::shared_ptr<Contrainte> contrainte = nullptr);

    // Destructor
    virtual ~PointMateriel() = default;


    // void setMasse(double m);
    // Vecteur evolution(double temps) const override;

    // 添加显示方法
    void affiche() const;
    void affiche(double temps) const;

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const PointMateriel& point);
};