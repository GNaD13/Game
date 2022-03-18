#include "VertexArray.hpp"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verticies, unsigned int numVerts, const int* indicies, unsigned int numIndicies)
    :   mNumVerts(numVerts),
        mNumIndicies(numIndicies)
{
    // Create Vertex Array
    glCreateVertexArrays(1, &mVertexArrayID);
    glBindVertexArray(mVertexArrayID);

    // Create Vertex Buffer
    glCreateBuffers(1, &mVertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
    // Pass data to Vertex Buffer
    glBufferData(GL_ARRAY_BUFFER, numVerts * 8 * sizeof(float), verticies, GL_STATIC_DRAW);

    // Create Index Buffer
    glCreateBuffers(1, &mIndexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
    // Pass data to Indicies Buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndicies * sizeof(unsigned int), indicies, GL_STATIC_DRAW);

    // Enable vertex attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void*)(sizeof(float) * 3));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void*)(sizeof(float) * 6));
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &mVertexBufferID);
    glDeleteBuffers(1, &mIndexBufferID);
    glDeleteVertexArrays(1, &mVertexArrayID);
}

void VertexArray::SetActive()
{
    glBindVertexArray(mVertexArrayID);
}