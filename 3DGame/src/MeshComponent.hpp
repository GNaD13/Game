#ifndef MeshComponent_hpp
#define MeshComponent_hpp

#include "Component.hpp"
#include <cstddef>

class Shader;
class Mesh;

class MeshComponent : public Component
{
public:
    MeshComponent(Actor* owner);
    ~MeshComponent();

    virtual void Draw(Shader* shader);
    virtual void SetMesh(Mesh* mesh) { mMesh = mesh; }

    void SetTextureIndex(size_t index) { mTextureIndex = index; }
protected:
    Mesh* mMesh;
    size_t mTextureIndex;
};


#endif