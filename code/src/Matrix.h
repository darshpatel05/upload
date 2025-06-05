// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstdint>
#include "Vector.h"

class Matrix
{

protected:
    Vector<Vector<uint8_t>> data;

private:
    int numRows;
    int numCols;

public:
    // Default constructor
    Matrix();

    /* Parameterized Constructor
    ** @param rows: number of rows
    ** @param cols: number of columns
    */
    Matrix(int rows, int cols);

    /* Copy Constructor
    ** @param other: matrix object to copy (creates a new Matrix object with the same data)
    */
    Matrix(const Matrix &other);

    /* Assignment Operator
    ** @param other: matrix object to assign (copies data)
    */
    Matrix &operator=(const Matrix &other);

    // Destructor
    ~Matrix();

    /* Input stream operator
    ** @param in: input stream
    ** @param mat: Matrix object to assign
    */
    friend std::istream &operator>>(std::istream &in, Matrix &mat);

    /* Output stream operator
    ** @param out: output stream
    ** @param mat: Matrix object to assign
    */
    friend std::ostream &operator<<(std::ostream &out, const Matrix &mat);

    /* Addition operator
    ** @param other: matrix object to add
    ** @return: matrix object with the result of the addition
    */
    Matrix operator+(const Matrix &other) const;

    /* Subtraction operator
    ** @param other: matrix object to subtract
    ** @return: matrix object with the result of the subtraction
    */
    Matrix operator-(const Matrix &other) const;

    /* Multiplication operator (Cross product)
    ** @param other: matrix object to multiply by
    ** @return: matrix object with the result of the multiplication
    */
    Matrix operator*(const Matrix &other) const;

    /* Subscript operator
    ** @param index: index of the element to access
    ** @return: element at the specified index
    */
    Vector<uint8_t> &operator[](int index);
    const Vector<uint8_t> &operator[](int index) const;

    // Number of rows
    int getRows() const;

    // Number of columns
    int getCols() const;

    // Transpose function (in-place)
    void transpose();
};

#endif // MATRIX_H
