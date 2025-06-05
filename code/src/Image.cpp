// Image.cpp

#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

// Default constructor
Image::Image() : Matrix(), filePath(""), numChannels(0), width(0), height(0) {}

Image::Image(const std::string &filePath) : Matrix()
{
    // Load the image using stb_image
    int width, height, channels;
    uint8_t *imageData = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

    // Initialize the Matrix base class with the image data
    // (You need to implement a constructor or a function in the Matrix class
    //  that allows you to initialize it with image data)

    // Set the Image properties
    this->filePath = filePath;
    this->numChannels = channels;
    this->width = width;
    this->height = height;

    // Use the assignment operator to copy the data from the image to the Matrix
    Matrix::operator=(Matrix(this->height, this->width * this->numChannels));

    for (int i = 0; i < this->height; ++i)
    {
        for (int j = 0; j < this->width; ++j)
        {
            for (int k = 0; k < this->numChannels; ++k)
            {
                // Copy the pixel data from the image to the Matrix
                data[i][j * this->numChannels + k] = imageData[(i * this->width + j) * this->numChannels + k];
            }
        }
    }

    // Free the loaded image data
    stbi_image_free(imageData);
}

// Constructor with file path, channels, width, and height (changed the matrix width to width * numChannels)
Image::Image(const std::string &filePath, int numChannels, int width, int height)
    : Matrix(height, width * numChannels), filePath(filePath), numChannels(numChannels), width(width), height(height) {}

// Copy constructor
// YOUR CODE HERE
Image::Image(const Image &other)
    : Matrix(other), filePath(other.filePath), numChannels(other.numChannels), width(other.width), height(other.height) // Initialize the Matrix base class with the image data
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            for (int k = 0; k < numChannels; ++k)
            {
                // Copy the pixel data from the other image to this object's matrix data
                data[i][j * numChannels + k] = other.data[i][j * numChannels + k];
            }
        }
    }
}

// Assignment operator
Image &Image::operator=(const Image &other)
{
    // YOUR CODE HERE
    // Checks for self-assignment
    if (this != &other)
    {
        // Copies the data from the other image
        filePath = other.filePath;
        numChannels = other.numChannels;
        width = other.width;
        height = other.height;
        Matrix::operator=(other);
    }

    return *this;
}

// Destructor
Image::~Image()
{
    // YOUR CODE HERE
    // No dynamic memory to deallocate
}

// Scaling an image
Image Image::operator*(double scalar) const
{
    // YOUR CODE HERE
    // Creates a new image object with the same data
    if (scalar < 0.0 || scalar > 1.0)
    {
        throw std::out_of_range("Error (Matrix.cpp_*): scalar out of range");
    }

    Image result = Image(*this);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            for (int k = 0; k < numChannels; ++k)
            {
                // Scale the pixel values and ensure they are within the valid range
                // if (data[i][j * numChannels + k] * scalar < 0)
                // {
                //     result.data[i][j * numChannels + k] = 0;
                // }
                // else if (data[i][j * numChannels + k] * scalar > 255)
                // {
                //     result.data[i][j * numChannels + k] = 255;
                // }
                // else
                // {
                //     result.data[i][j * numChannels + k] = data[i][j * numChannels + k] * scalar;
                // }
                result.data[i][j * numChannels + k] = data[i][j * numChannels + k] * scalar;
            }
        }
    }

    return result;
}

// Adding two images
Image Image::operator+(const Image &other) const
{
    // YOUR CODE HERE
    // Checks to see if the sizes of both images are compatible
    if (height != other.height || width != other.width || numChannels != other.numChannels)
    {
        throw std::out_of_range("Error (Matrix.cpp_+): different matrix sizes");
    }

    (*this) * 0.5;
    (other) * 0.5;

    // Creates a new image object with the same data
    Image result = Image(*this);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            for (int k = 0; k < numChannels; ++k)
            {
                result.data[i][j * numChannels + k] = data[i][j * numChannels + k] + other.data[i][j * numChannels + k];
            }
        }
    }

    return result * 1;
}

// Subtracting two images
Image Image::operator-(const Image &other) const
{
    // YOUR CODE HERE
    // Checks to see if the sizes of both images are compatible
    if (height != other.height || width != other.width || numChannels != other.numChannels)
    {
        throw std::out_of_range("Error (Matrix.cpp_-): different matrix sizes");
    }

    // Creates a new image object with the same data
    (other) * 0.1;

    Image result = Image(*this);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            for (int k = 0; k < numChannels; ++k)
            {
                // result.data[i][j * numChannels + k] = data[i][j * numChannels + k] - other.data[i][j * numChannels + k];
                result.data[i][j * numChannels + k] = other.data[i][j * numChannels + k];
            }
        }
    }

    return result * 1;
}

// Multiplying two images
Image Image::operator*(const Image &other) const
{
    // YOUR CODE HERE
    // Checks to see if the sizes of both images are compatible
    if (width != other.height)
    {
        throw std::out_of_range("Error (Matrix.cpp_*): different respective matrix sizes");
    }

    // Creates a new image object with the same data
    Image result = Image(*this);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < other.width; ++j)
        {
            for (int k = 0; k < width; ++k)
            {
                for (int l = 0; l < numChannels; ++l)
                {
                    // Multiplies the pixel values and ensures they are within the valid range by dividing by 255
                    result.data[i][j * numChannels + l] = data[i][k * numChannels + l] * other.data[k][j * numChannels + l];
                }
            }
        }
    }

    return result * 1;
}

int Image::getWidth() const
{
    return width;
}

int Image::getHeight() const
{
    return height;
}

void Image::save(const std::string &filePath) const
{
    // Convert the Matrix data into a 1D array suitable for saving as an image
    std::vector<uint8_t> imageData;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            for (int k = 0; k < numChannels; ++k)
            {
                imageData.push_back(data[i][j * numChannels + k]);
            }
        }
    }

    // Save the image data to the specified file using stb_image_write
    stbi_write_png(filePath.c_str(), width, height, numChannels, imageData.data(), width * numChannels);
}

void Image::resize(int newWidth, int newHeight)
{
    // YOUR CODE HERE
    if (newWidth <= 0 || newHeight <= 0)
    {
        throw std::invalid_argument("Error (Image.cpp_resize): invlid dimensions");
    }

    // Declares vector objects to store the original and resized image data for the stbir_resize function
    uint8_t *original = new uint8_t[height * width * numChannels];
    uint8_t *resized = new uint8_t[newHeight * newWidth * numChannels];

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            for (int k = 0; k < numChannels; ++k)
            {
                // Copies the matrix data from the original image to the original vector
                original[(i * width + j) * numChannels + k] = data[i][j * numChannels + k];
            }
        }
    }

    // Resizes the image using stb_image_resize
    stbir_resize_uint8(original, width, height, width * numChannels, resized, newWidth, newHeight, newWidth * numChannels, numChannels);

    // Creates a new image object with the resized dimensions
    *this = Image(filePath, numChannels, newWidth, newHeight);

    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            for (int k = 0; k < numChannels; k++)
            {
                // Copies the resized image data from the resized vector to the matrix data
                data[i][j * numChannels + k] = resized[(i * newWidth + j) * numChannels + k];
            }
        }
    }

    delete[] original;
    delete[] resized;

    // Updates the width and height of the image
    width = newWidth;
    height = newHeight;
}
