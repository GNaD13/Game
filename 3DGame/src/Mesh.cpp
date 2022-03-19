#include "Mesh.hpp"
#include "Renderer.hpp"
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
        const rapidjson::Value& 
    }
}

void Mesh::Unload()
{

}

Texture* Mesh::GetTexture(size_t index)
{

}