#ifndef Actor_hpp
#define Actor_hpp

#include <vector>
#include "Math.h"
#include <stdint.h>

class Game;
class Component;

class Actor
{
public:
    enum State
    {
        EActive,
        EReborn,
        EPaused,
        EDead
    };

    Actor(Game* game);
    virtual ~Actor();

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime) {}

    void ProcessInput(const uint8_t* keyState);
    virtual void ActorInput(const uint8_t* keyState) {}

    // Get/Set function
    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }
    const Vector3& GetPosition() const { return mPosition; }
    void SetPosition(const Vector3& position) { mPosition = position; mRecomputeWorldTransform = true; }
    float GetScale() const { return mScale; }
    void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true; }
    Quaternion GetRotation() const { return mRotation; }
    void SetRotation(Quaternion rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }

    void ComputeWorldTransform();
    const Matrix4& GetWorldTransform() const { return mWorldTransform; }

    void AddComponents(Component* component);
    void RemoveComponents(Component* component);

    Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

    Game* GetGame() { return mGame; }
private:  
    State mState;

    // Transform of Actor
    Vector3 mPosition;
    float mScale;
    Quaternion mRotation;
    Matrix4 mWorldTransform;
    bool mRecomputeWorldTransform;

    std::vector<Component*> mComponents;
    Game* mGame;
};

#endif