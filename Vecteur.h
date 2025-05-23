#pragma once
#include <initializer_list>
#include <vector>
#include <iostream>
#include <stdexcept>

/**
 * @class Vecteur
 * @brief Represents a mathematical vector of arbitrary dimension
 * 
 * This class provides a complete implementation of vector operations including:
 * - Basic arithmetic (addition, subtraction, multiplication)
 * - Vector operations (dot product, cross product)
 * - Vector properties (norm, unit vector)
 * - Element access and manipulation
 */
class Vecteur {
private:
    std::vector<double> coords;  ///< Vector coordinates

public:
    // Constructors
    /// @brief Default constructor (creates empty vector)
    Vecteur() = default;
    
    /// @brief Creates a zero vector of specified dimension
    /// @param dimension The dimension of the vector
    explicit Vecteur(size_t dimension);
    
    /// @brief Creates a 3D vector from coordinates
    /// @param x First coordinate
    /// @param y Second coordinate
    /// @param z Third coordinate
    Vecteur(double x, double y, double z);
    
    /// @brief Creates a vector from an initializer list
    /// @param values List of coordinate values
    Vecteur(std::initializer_list<double> values);
    
    /// @brief Copy constructor
    /// @param autre Vector to copy
    Vecteur(const Vecteur& autre) = default;
    
    /// @brief Move constructor
    /// @param autre Vector to move from
    Vecteur(Vecteur&& autre) = default;

    // Assignment operators
    /// @brief Copy assignment operator
    /// @param autre Vector to copy from
    /// @return Reference to this vector
    Vecteur& operator=(const Vecteur& autre) = default;
    
    /// @brief Move assignment operator
    /// @param autre Vector to move from
    /// @return Reference to this vector
    Vecteur& operator=(Vecteur&& autre) = default;

    // Element access
    /// @brief Access element by index (no bounds checking)
    /// @param index Element index
    /// @return Reference to the element
    double& operator[](size_t index);
    
    /// @brief Access element by index (no bounds checking, const version)
    /// @param index Element index
    /// @return Const reference to the element
    const double& operator[](size_t index) const;
    
    /// @brief Safe element access with bounds checking
    /// @param index Element index
    /// @return Reference to the element
    /// @throw std::out_of_range if index is invalid
    double& at(size_t index);
    
    /// @brief Safe element access with bounds checking (const version)
    /// @param index Element index
    /// @return Const reference to the element
    /// @throw std::out_of_range if index is invalid
    const double& at(size_t index) const;

    // Vector operations
    /// @brief Check if two vectors have the same dimension
    /// @param autre Vector to compare with
    /// @return true if dimensions match
    bool memeDimension(const Vecteur& autre) const;
    
    /// @brief Add a new coordinate to the vector
    /// @param valeur Value of the new coordinate
    void augmente(double valeur);
    
    /// @brief Set coordinate value
    /// @param index Coordinate index
    /// @param valeur New value
    /// @throw std::out_of_range if index is invalid
    void set_coord(size_t index, double valeur);

    // Arithmetic operators
    /// @brief Unary minus operator
    /// @return Negated vector
    Vecteur operator-() const;
    
    /// @brief Unit vector operator
    /// @return Unit vector in same direction
    /// @throw std::runtime_error if vector is zero
    Vecteur operator~() const;
    
    /// @brief Vector addition
    /// @param autre Vector to add
    /// @return Sum vector
    /// @throw std::runtime_error if dimensions don't match
    Vecteur operator+(const Vecteur& autre) const;
    
    /// @brief Vector addition with assignment
    /// @param autre Vector to add
    /// @return Reference to this vector
    /// @throw std::runtime_error if dimensions don't match
    Vecteur& operator+=(const Vecteur& autre);
    
    /// @brief Vector subtraction
    /// @param autre Vector to subtract
    /// @return Difference vector
    /// @throw std::runtime_error if dimensions don't match
    Vecteur operator-(const Vecteur& autre) const;
    
    /// @brief Vector subtraction with assignment
    /// @param autre Vector to subtract
    /// @return Reference to this vector
    /// @throw std::runtime_error if dimensions don't match
    Vecteur& operator-=(const Vecteur& autre);
    
    /// @brief Scalar multiplication
    /// @param scalaire Scalar value
    /// @return Scaled vector
    Vecteur operator*(double scalaire) const;
    
    /// @brief Scalar multiplication with assignment
    /// @param scalaire Scalar value
    /// @return Reference to this vector
    Vecteur& operator*=(double scalaire);
    
    /// @brief Dot product
    /// @param autre Vector to multiply with
    /// @return Dot product value
    /// @throw std::runtime_error if dimensions don't match
    double operator*(const Vecteur& autre) const;
    
    /// @brief Cross product (3D only)
    /// @param autre Vector to multiply with
    /// @return Cross product vector
    /// @throw std::runtime_error if vectors are not 3D
    Vecteur operator^(const Vecteur& autre) const;
    
    /// @brief Cross product with assignment (3D only)
    /// @param autre Vector to multiply with
    /// @return Reference to this vector
    /// @throw std::runtime_error if vectors are not 3D
    Vecteur& operator^=(const Vecteur& autre);

    // Comparison operators
    /// @brief Equality comparison
    /// @param autre Vector to compare with
    /// @return true if vectors are equal
    bool operator==(const Vecteur& autre) const;
    
    /// @brief Inequality comparison
    /// @param autre Vector to compare with
    /// @return true if vectors are not equal
    bool operator!=(const Vecteur& autre) const;

    // Vector properties
    /// @brief Calculate squared norm
    /// @return Squared norm value
    double norme2() const;
    
    /// @brief Calculate norm
    /// @return Norm value
    double norme() const;

    // Friend functions
    /// @brief Scalar multiplication (commutative)
    /// @param scalaire Scalar value
    /// @param v Vector to multiply
    /// @return Scaled vector
    friend Vecteur operator*(double scalaire, const Vecteur& v);
    
    /// @brief Stream output operator
    /// @param os Output stream
    /// @param v Vector to output
    /// @return Reference to output stream
    friend std::ostream& operator<<(std::ostream& os, const Vecteur& v);

    // Legacy methods (kept for compatibility)
    Vecteur addition(const Vecteur& autre) const;
    Vecteur soustraction(const Vecteur& autre) const;
    Vecteur oppose() const;
    Vecteur mult(double scalaire) const;
    double prod_scal(const Vecteur& autre) const;
    Vecteur prod_vect(const Vecteur& autre) const;
    Vecteur unitaire() const;
    void affiche() const;
    bool compare(const Vecteur& autre) const;
};