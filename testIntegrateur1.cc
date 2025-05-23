
#include <iostream>
#include <memory>
#include <iomanip>
#include "PointMateriel.h"
#include "GravitationConstante.h"
#include "Libre.h"
#include "IntegrateurEulerCromer.h"

int main() {
    try {
        // Create gravitational field (constant gravity)
        auto gravite = std::make_shared<GravitationConstante>();
        
        // Create free motion constraint
        auto libre = std::make_shared<Libre>();
        
        // Create material point with mass 0.127 kg
        // Initial position (0,0,1) and velocity (0,1,2)
        auto point = std::make_shared<PointMateriel>(
            Vecteur(0, 0, 1),    // position
            Vecteur(0, 1, 2),    // velocity
            0.127,               // mass
            gravite,             // force field
            libre                // constraint
        );
        
        // Create Euler-Cromer integrator with time step 0.01s
        IntegrateurEulerCromer integrateur;
        
        // Display initial state
        std::cout << std::fixed << std::setprecision(5);
        std::cout << "Initial state:" << std::endl;
        std::cout << point->getParametres() << " # parametre" << std::endl;
        std::cout << point->getDeriveeParametres() << " # vitesse" << std::endl;
        std::cout << std::endl;
        
        // Integrate for several time steps
        double dt = 0.01;  // Time step
        double t = 0.0;    // Current time
        
        // First step (t = 0.01)
        t += dt;
        integrateur.integre(*point, t, dt);
        std::cout << "t = " << t << std::endl;
        std::cout << point->getParametres() << " # parametre" << std::endl;
        std::cout << point->getDeriveeParametres() << " # vitesse" << std::endl;
        std::cout << std::endl;
        
        // Second step (t = 0.02)
        t += dt;
        integrateur.integre(*point, t, dt);
        std::cout << "t = " << t << std::endl;
        std::cout << point->getParametres() << " # parametre" << std::endl;
        std::cout << point->getDeriveeParametres() << " # vitesse" << std::endl;
        std::cout << std::endl;
        
        // Test with zero initial velocity
        std::cout << "\nTesting with zero initial velocity:" << std::endl;
        point = std::make_shared<PointMateriel>(
            Vecteur(0, 0, 1),    // position
            Vecteur(0, 0, 0),    // zero velocity
            0.127,               // mass
            gravite,             // force field
            libre                // constraint
        );
        
        t = 0.0;
        std::cout << "Initial state:" << std::endl;
        std::cout << point->getParametres() << " # parametre" << std::endl;
        std::cout << point->getDeriveeParametres() << " # vitesse" << std::endl;
        std::cout << std::endl;
        
        // Integrate for a few steps
        for (int i = 0; i < 3; ++i) {
            t += dt;
            integrateur.integre(*point, t, dt);
            std::cout << "t = " << t << std::endl;
            std::cout << point->getParametres() << " # parametre" << std::endl;
            std::cout << point->getDeriveeParametres() << " # vitesse" << std::endl;
            std::cout << std::endl;
        }
        
        // Test with upward initial velocity
        std::cout << "\nTesting with upward initial velocity:" << std::endl;
        point = std::make_shared<PointMateriel>(
            Vecteur(0, 0, 1),    // position
            Vecteur(0, 0, 5),    // upward velocity
            0.127,               // mass
            gravite,             // force field
            libre                // constraint
        );
        
        t = 0.0;
        std::cout << "Initial state:" << std::endl;
        std::cout << point->getParametres() << " # parametre" << std::endl;
        std::cout << point->getDeriveeParametres() << " # vitesse" << std::endl;
        std::cout << std::endl;
        
        // Integrate for a few steps
        for (int i = 0; i < 3; ++i) {
            t += dt;
            integrateur.integre(*point, t, dt);
            std::cout << "t = " << t << std::endl;
            std::cout << point->getParametres() << " # parametre" << std::endl;
            std::cout << point->getDeriveeParametres() << " # vitesse" << std::endl;
            std::cout << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}