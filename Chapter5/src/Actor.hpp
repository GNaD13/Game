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

    const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& position) { mPosition = position; }

    float GetScale() const { return mScale; }
    void SetScale(float scale) { mScale = scale; }

    float GetRotation() const { return mRotation; }
    void SetRotation(float rotation) { mRotation = rotation; }

    void AddComponents(Component* component);
    void RemoveComponents(Component* component);

    Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

    Game* GetGame() { return mGame; }
private:  
    State mState;

    // Transform of Actor
    Vector2 mPosition;
    float mScale;
    float mRotation;

    std::vector<Component*> mComponents;
    Game* mGame;
};

#endif