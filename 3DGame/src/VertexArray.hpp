#ifndef VertexArray_hpp
#define VertexArray_hpp

class VertexArray
{
public:
    VertexArray(const float* verticies, unsigned int numVerts, const unsigned int* indicies, unsigned int numIndicies);
    ~VertexArray();

    void SetActive();

    unsigned int GetNumIndicies() const { return mNumIndicies; }
    unsigned int GetNumVerts() const { return mNumVerts; }

private:
    unsigned int mNumIndicies;
    unsigned int mNumVerts;

    unsigned int mVertexBufferID;
    unsigned int mIndexBufferID;
    unsigned int mVertexArrayID;
};


#endif