#ifndef Mesh_hpp
#define Mesh_hpp

#include <string>
#include <vector>
#include <rapidjson/document.h>

class Renderer;
class VertexArray;
class Texture;

class Mesh
{
public:
    Mesh();
    ~Mesh();

    bool Load(const std::string& fileName, Renderer* renderer);
    void Unload();

    Texture* GetTexture(size_t index);
    VertexArray* GetVertexArray() { return mVertexArray; }
    const std::string& GetShaderName() const { return mShaderName; }
    float GetRadius() const { return mRadius; }
    float GetSpecPower() const { return mSpecPower; }
private:
    std::vector<Texture*> mTextures;
    VertexArray* mVertexArray;
    std::string mShaderName;
    float mRadius;
    float mSpecPower;
};

#endif