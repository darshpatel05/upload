// Matrix.cpp

#include "Matrix.h"
#include <stdexcept>

// Default constructor
Matrix::Matrix() : numRows(0), numCols(0) {}

// Constructor with rows and columns
// YOUR CODE HERE
Matrix::Matrix(int rows, int cols) : numRows(rows), numCols(cols)
{
    // Checks for invalid row or column values
    if (numRows < 0 || numCols < 0)
    {
        throw std::out_of_range("Error: Invalid dimensions in Matrix constructor");
    }

    // Allocates memory for the matrix of the specified dimensions
    data = Vector<Vector<uint8_t>>(numRows);
    for (int i = 0; i < numRows; i++)
    {
        data[i] = Vector<uint8_t>(numCols);
    }
};

// Copy constructor
// YOUR CODE HERE
Matrix::Matrix(const Matrix &other) : numRows(other.numRows), numCols(other.numCols)
{
    // Allocates memory for the matrix of the same dimensions
    data = Vector<Vector<uint8_t>>(numRows);
    for (int i = 0; i < numRows; i++)
    {
        data[i] = Vector<uint8_t>(numCols);

        // Copies the data from the other matrix
        for (int j = 0; j < numCols; j++)
        {
            data[i][j] = other.data[i][j];
        }
    }
};

// Assignment operator
Matrix &Matrix::operator=(const Matrix &other)
{
    // YOUR CODE HERE
    // Checks for self-assignment
    if (this != &other)
    {
        // Checks to see if data needs to be reallocated depending on the compatibility of the sizes of both matrices
        if (numRows != other.getRows() || numCols != other.getCols())
        {
            numRows = other.getRows();
            numCols = other.getCols();

            data = Vector<Vector<uint8_t>>(numRows);
            for (int i = 0; i < numRows; i++)
            {
                data[i] = Vector<uint8_t>(numCols);
            }
        }

        // Copies the data from the other matrix
        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j < numCols; j++)
            {
                data[i][j] = other.data[i][j];
            }
        }
    }

    return *this;
}

// Destructor
Matrix::~Matrix() {}

// Number of rows
int Matrix::getRows() const
{
    return numRows;
}

// Number of columns
int Matrix::getCols() const
{
    return numCols;
}

// Input stream operator
std::istream &operator>>(std::istream &in, Matrix &mat)
{
    // YOUR CODE HERE
    // Inputs the data into the input stream
    for (int i = 0; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getCols(); j++)
        {
            in >> mat.data[i][j];
        }
    }

    return in;
}

// Output stream operator
std::ostream &operator<<(std::ostream &out, const Matrix &mat)
{
    // YOUR CODE HERE
    // Outputs the data into the output stream
    for (int i = 0; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getCols(); j++)
        {
            out << mat.data[i][j] << " ";
        }
        out << "\n";
    }

    return out;
}

// Arithmetic operators
Matrix Matrix::operator+(const Matrix &other) const
{
    // YOUR CODE HERE
    // Checks to see if the sizes of both matrices are compatible
    if (numRows != other.getRows() || numCols != other.getCols())
    {
        throw std::invalid_argument("Error (Matrix.cpp_+): different matrix sizes");
    }

    // Creates a new matrix object with the same dimension
    Matrix result(numRows, numCols);
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            // Adds the data from both matrices and stores it in the new matrix
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }

    return result;
}

Matrix Matrix::operator-(const Matrix &other) const
{
    // YOUR CODE HERE
    // Checks to see if the sizes of both matrices are compatible
    if (numRows != other.getRows() || numCols != other.getCols())
    {
        throw std::invalid_argument("Error (Matrix.cpp_-): different matrix sizes");
    }

    // Creates a new matrix object with the same dimension
    Matrix result(numRows, numCols);
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            // Subtracts the data from both matrices and stores it in the new matrix
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }

    return result;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    // YOUR CODE HERE
    // Checks to see if the sizes of both matrices are compatible
    if (numCols != other.getRows())
    {
        throw std::invalid_argument("Error (Matrix.cpp_-): different respective matrix sizes");
    }

    // Creates a new matrix object with the respective dimensions for the cross product of both matrices
    Matrix result(numRows, other.getCols());
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < other.getCols(); j++)
        {
            for (int k = 0; k < numCols; k++)
            {
                // Stores the values of the cross product in the new matrix
                result.data[i][j] = data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

// Subscript operator
Vector<uint8_t> &Matrix::operator[](int index)
{
    // YOUR CODE HERE
    // Checks to see if the index is within bounds
    if (index < 0 || index >= numRows)
    {
        throw std::out_of_range("Error (Matrix.cpp_[]): index out of bounds");
    }
    return data[index];
}

const Vector<uint8_t> &Matrix::operator[](int index) const
{
    // YOUR CODE HERE
    // Checks to see if the index is within bounds
    if (index < 0 || index >= numRows)
    {
        throw std::out_of_range("Error (Matrix.cpp_const[]const): index out of bounds");
    }
    return data[index];
}

// Transpose function (in-place)
void Matrix::transpose()
{
    // YOUR CODE HERE
    // Creates a new matrix object with the respective dimensions for the transposed matrix
    Matrix result(numCols, numRows);
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            // Stores the values of the transposed matrix in the new matrix
            result.data[j][i] = data[i][j];
        }
    }

    // Copies the data from the new matrix to the original matrix
    *this = result;
}
