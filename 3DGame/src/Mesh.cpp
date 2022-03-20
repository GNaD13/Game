#include "Mesh.hpp"
#include "Renderer.hpp"
#include "VertexArray.hpp"
#include <fstream>
#include <sstream>
#include <string>

Mesh::Mesh()
{

}
    
Mesh::~Mesh()
{

}

bool Mesh::Load(const std::string& fileName, Renderer* renderer)
{
    std::ifstream file(fileName);
    if(!file.is_open())
    {
        SDL_Log("File not found %s", fileName.c_str());
        return false;
    }

    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string contents = fileStream.str();
    rapidjson::StringStream jsonStr(contents.c_str());

    rapidjson::Document doc;
    doc.ParseStream(jsonStr);
    if(!doc.IsObject())
    {
        SDL_Log("Mesh %s is not valid json", fileName.c_str());
        return false;
    }

    int ver = doc["version"].GetInt();
    if(ver != 1)
    {
        SDL_Log("Mesh %s wrong version", fileName.c_str());
        return false;
    }

    mShaderName = doc["shader"].GetString();

    size_t vertSize = 8;

    const rapidjson::Value& textures = doc["textures"];
    if(!textures.IsArray() || textures.Size() < 1)
    {
        SDL_Log("Mesh %s has no textures, there should be at least one", fileName.c_str());
        return false;
    }

    mSpecPower = static_cast<float>(doc["specularPower"].GetDouble());

    for(rapidjson::SizeType i = 0; i < textures.Size(); i++)
    {
        std::string texName = textures[i].GetString();
        Texture* t = renderer->GetTexture(texName);
        if(t == nullptr)
        {
            t = renderer->GetTexture(texName);
            if(t == nullptr)
            {
                t = renderer->GetTexture("../Assets/Default.png");
            }
        }
        mTextures.emplace_back(t);
    }

    const rapidjson::Value& vertsJson = doc["vertices"];
    if(!vertsJson.IsArray() || vertsJson.Size() < 1)
    {
        SDL_Log("Unexpected vertex format for %s", fileName.c_str());
        return false;
    }

    std::vector<float> verticies;
    verticies.reserve(vertsJson.Size() * vertSize);
    mRadius = 0.0f;
    for(rapidjson::SizeType i = 0; i < vertsJson.Size(); i++)
    {
        const rapidjson::Value& vert = vertsJson[i];
        if(!vert.IsArray() || vert.Size() != vertSize)
        {
            SDL_Log("Unexpected vertex format for %s", fileName.c_str());
            return false;
        }

        Vector3 pos(vert[0].GetDouble(), vert[1].GetDouble(), vert[2].GetDouble());
        mRadius = Math::Max(mRadius, pos.LengthSq());
        
        for(rapidjson::SizeType i = 0; i < vert.Size(); i++)
        {
            verticies.emplace_back(static_cast<float>(vert[i].GetDouble()));
        }
    }

    mRadius = Math::Sqrt(mRadius);

    const rapidjson::Value& indJson = doc["indicies"];
    if(!indJson.IsArray() || indJson.Size() < 1)
    {
        SDL_Log("Mesh %s has no indicies", fileName.c_str());
        return false;
    }

    std::vector<unsigned int> indicies;
    indicies.reserve(indJson.Size() * 3);
    for(rapidjson::SizeType i = 0; i < indJson.Size(); i++)
    {
        const rapidjson::Value& ind = indJson[i];
        if(!ind.IsArray() || ind.Size() != 3)
        {
            SDL_Log("Unexpected indicies format for %s", fileName.c_str());
            return false;
        }

        indicies.emplace_back(ind[0].GetInt());
        indicies.emplace_back(ind[1].GetInt());
        indicies.emplace_back(ind[2].GetInt());
    }

    mVertexArray = new VertexArray(verticies.data(), (unsigned int)(verticies.size() / vertSize), indicies.data(), (unsigned int)(indicies.size()));
    return true;
}

void Mesh::Unload()
{
    delete mVertexArray;
    mVertexArray = nullptr;
}

Texture* Mesh::GetTexture(size_t index)
{
    if(index < mTextures.size())
    {
        return mTextures[index];
    }
    else
    {
        return nullptr;
    }
    
}