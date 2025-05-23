#include "Vecteur.h"
#include <cmath>
#include <stdexcept>

// Constructors
Vecteur::Vecteur(size_t dimension) {
    if (dimension == 0) {
        throw std::invalid_argument("Vector dimension cannot be zero");
    }
    coords.resize(dimension, 0.0);
}

Vecteur::Vecteur(double x, double y, double z) {
    coords = {x, y, z};
}

Vecteur::Vecteur(std::initializer_list<double> values) {
    if (values.size() == 0) {
        throw std::invalid_argument("Vector cannot be empty");
    }
    coords.assign(values.begin(), values.end());
}

// Element access
double& Vecteur::operator[](size_t index) {
    return coords[index];
}

const double& Vecteur::operator[](size_t index) const {
    return coords[index];
}

double& Vecteur::at(size_t index) {
    if (index >= coords.size()) {
        throw std::out_of_range("Vector index out of range");
    }
    return coords[index];
}

const double& Vecteur::at(size_t index) const {
    if (index >= coords.size()) {
        throw std::out_of_range("Vector index out of range");
    }
    return coords[index];
}

// Vector operations
bool Vecteur::memeDimension(const Vecteur& autre) const {
    return coords.size() == autre.coords.size();
}

void Vecteur::augmente(double valeur) {
    coords.push_back(valeur);
}

void Vecteur::set_coord(size_t index, double valeur) {
    at(index) = valeur;  // at() will throw if index is invalid
}

// Arithmetic operators
Vecteur Vecteur::operator-() const {
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); ++i) {
        resultat.coords[i] = -coords[i];
    }
    return resultat;
}

Vecteur Vecteur::operator~() const {
    const double n = norme();
    if (n < 1e-10) {
        throw std::runtime_error("Cannot normalize zero vector");
    }
    return *this * (1.0 / n);
}

Vecteur Vecteur::operator+(const Vecteur& autre) const {
    if (!memeDimension(autre)) {
        throw std::runtime_error("Vector dimensions do not match for addition");
    }
    
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); ++i) {
        resultat.coords[i] = coords[i] + autre.coords[i];
    }
    return resultat;
}

Vecteur& Vecteur::operator+=(const Vecteur& autre) {
    if (!memeDimension(autre)) {
        throw std::runtime_error("Vector dimensions do not match for addition");
    }
    
    for (size_t i = 0; i < coords.size(); ++i) {
        coords[i] += autre.coords[i];
    }
    return *this;
}

Vecteur Vecteur::operator-(const Vecteur& autre) const {
    if (!memeDimension(autre)) {
        throw std::runtime_error("Vector dimensions do not match for subtraction");
    }
    
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); ++i) {
        resultat.coords[i] = coords[i] - autre.coords[i];
    }
    return resultat;
}

Vecteur& Vecteur::operator-=(const Vecteur& autre) {
    if (!memeDimension(autre)) {
        throw std::runtime_error("Vector dimensions do not match for subtraction");
    }
    
    for (size_t i = 0; i < coords.size(); ++i) {
        coords[i] -= autre.coords[i];
    }
    return *this;
}

Vecteur Vecteur::operator*(double scalaire) const {
    Vecteur resultat(coords.size());
    for (size_t i = 0; i < coords.size(); ++i) {
        resultat.coords[i] = coords[i] * scalaire;
    }
    return resultat;
}

Vecteur& Vecteur::operator*=(double scalaire) {
    for (size_t i = 0; i < coords.size(); ++i) {
        coords[i] *= scalaire;
    }
    return *this;
}

double Vecteur::operator*(const Vecteur& autre) const {
    if (!memeDimension(autre)) {
        throw std::runtime_error("Vector dimensions do not match for dot product");
    }
    
    double somme = 0.0;
    for (size_t i = 0; i < coords.size(); ++i) {
        somme += coords[i] * autre.coords[i];
    }
    return somme;
}

Vecteur Vecteur::operator^(const Vecteur& autre) const {
    if (coords.size() != 3 || autre.coords.size() != 3) {
        throw std::runtime_error("Cross product is only defined for 3D vectors");
    }
    
    Vecteur resultat(3);
    resultat.coords[0] = coords[1] * autre.coords[2] - coords[2] * autre.coords[1];
    resultat.coords[1] = coords[2] * autre.coords[0] - coords[0] * autre.coords[2];
    resultat.coords[2] = coords[0] * autre.coords[1] - coords[1] * autre.coords[0];
    return resultat;
}

Vecteur& Vecteur::operator^=(const Vecteur& autre) {
    *this = *this ^ autre;
    return *this;
}

// Comparison operators
bool Vecteur::operator==(const Vecteur& autre) const {
    if (!memeDimension(autre)) {
        return false;
    }
    
    for (size_t i = 0; i < coords.size(); ++i) {
        if (std::abs(coords[i] - autre.coords[i]) > 1e-10) {
            return false;
        }
    }
    return true;
}

bool Vecteur::operator!=(const Vecteur& autre) const {
    return !(*this == autre);
}

// Vector properties
double Vecteur::norme2() const {
    double somme = 0.0;
    for (size_t i = 0; i < coords.size(); ++i) {
        somme += coords[i] * coords[i];
    }
    return somme;
}

double Vecteur::norme() const {
    return std::sqrt(norme2());
}

// Friend functions
Vecteur operator*(double scalaire, const Vecteur& v) {
    return v * scalaire;
}

std::ostream& operator<<(std::ostream& os, const Vecteur& v) {
    for (size_t i = 0; i < v.coords.size(); ++i) {
        os << v.coords[i];
        if (i < v.coords.size() - 1) {
            os << " ";
        }
    }
    return os;
}

// Legacy methods (implemented using operators)
Vecteur Vecteur::addition(const Vecteur& autre) const {
    return *this + autre;
}

Vecteur Vecteur::soustraction(const Vecteur& autre) const {
    return *this - autre;
}

Vecteur Vecteur::oppose() const {
    return -(*this);
}

Vecteur Vecteur::mult(double scalaire) const {
    return *this * scalaire;
}

double Vecteur::prod_scal(const Vecteur& autre) const {
    return *this * autre;
}

Vecteur Vecteur::prod_vect(const Vecteur& autre) const {
    return *this ^ autre;
}

Vecteur Vecteur::unitaire() const {
    return ~(*this);
}

void Vecteur::affiche() const {
    std::cout << *this;
}

bool Vecteur::compare(const Vecteur& autre) const {
    return *this == autre;
}