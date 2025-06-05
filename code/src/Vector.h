// Vector.h

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Vector
{

private:
    T *data;
    int size;

public:
    /* Default Constructor
    ** @param size: size of the vector (default is 0)
    */
    Vector(int size = 0) : size(size)
    {
        // Checks for invalid size value
        if (size < 0)
        {
            throw std::invalid_argument("Error (Vector.h/Default_Constructor): size < 0");
        }

        // Allocates memory for the vector of the specified size
        data = new T[size]{};
    }

    /* Copy Constructor
    ** @param other: vector object to copy (creates a new Vector object with the same data)
    */
    Vector(const Vector &other) : size(other.size)
    {
        // Allocates memory for the vector of the same size
        data = new T[size];

        // Copies the data from the other vector
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }

    /* Assignment Operator
    ** @param other: vector object to assign (copies data)
    */
    Vector &operator=(const Vector &other)
    {
        // Checks for self-assignment
        if (this != &other)
        {
            // Checks to see if data needs to be reallocated depending on the compatibility of the sizes of both vectors
            if (other.size != size)
            {
                delete[] data;
                size = other.size;
                data = new T[size];
            }

            // Copies the data from the other vector
            for (int i = 0; i < size; i++)
            {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    // Destructor
    ~Vector()
    {
        // Deallocates memory for the vector
        delete[] data;
    }

    /* Input stream operator
    ** @param in: input stream
    ** @param vec: vector object to assign
    */
    friend std::istream &operator>>(std::istream &in, Vector &vec)
    {
        // Inputs the data into the input stream
        for (int i = 0; i < vec.size; i++)
        {
            in >> vec.data[i];
        }

        return in;
    }

    /* Output stream operator
    ** @param out: output stream
    ** @param vec: vector object to assign
    */
    friend std::ostream &operator<<(std::ostream &out, const Vector &vec)
    {
        // Outputs the data into the output stream
        for (int i = 0; i < vec.size; i++)
        {
            out << vec.data[i] << " ";
        }
        out << "\n";

        return out;
    }

    /* Addition operator
    ** @param other: vector object to add
    ** @return: vector object with the result of the addition
    */
    Vector<T> operator+(const Vector<T> &other) const
    {
        // Checks to see if the sizes of both vectors are compatible
        if (size != other.size)
        {
            throw std::invalid_argument("Error (Vector.h/operator+): different vector sizes");
        }

        // Creates a new vector object with the same size as the other vector
        Vector<T> result(size);

        // Adds the data from both vectors and stores it in the new vector
        for (int i = 0; i < size; i++)
        {
            result.data[i] = data[i] + other.data[i];
        }

        return result;
    }

    /* Subtraction operator
    ** @param other: vector object to subtract
    ** @return: vector object with the result of the subtraction
    */
    Vector<T> operator-(const Vector<T> &other) const
    {
        // Checks to see if the sizes of both vectors are compatible
        if (size != other.size)
        {
            throw std::invalid_argument("Error (Vector.h/operator-): different vector sizes");
        }

        // Creates a new vector object with the same size as the other vector
        Vector<T> result(size);

        // Subtracts the data from both vectors and stores it in the new vector
        for (int i = 0; i < size; i++)
        {
            result.data[i] = data[i] - other.data[i];
        }

        return result;
    }

    /* Multiplication operator (element-wise)
    ** @param other: vector object to multiply by
    ** @return: vector object with the result of the multiplication
    */
    Vector<T> operator*(const Vector<T> &other) const
    {
        // Checks to see if the sizes of both vectors are compatible
        if (size != other.size)
        {
            throw std::invalid_argument("Error (Vector.h/operator-): different vector sizes");
        }

        // Creates a new vector object with the same size as the other vector
        Vector<T> result(size);

        // Multiplies the data from both vectors and stores it in the new vector
        for (int i = 0; i < size; i++)
        {
            result.data[i] = data[i] * other.data[i];
        }
        return result;
    }

    /* Subscript operator
    ** @param index: index of the element to access
    ** @return: element at the specified index
    */
    T &operator[](int index)
    {
        // Checks to see if the index is within bounds
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Error (Vector.h_[]): index out of bounds");
        }

        return data[index];
    }

    const T &operator[](int index) const
    {
        // Checks to see if the index is within bounds
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Error (Vector.h_[]const): index out of bounds, 1");
        }

        return data[index];
    }

    /* Size Getter
    ** @return: size of the vector
    */
    int getSize() const
    {
        return size;
    }
};

#endif // VECTOR_H
