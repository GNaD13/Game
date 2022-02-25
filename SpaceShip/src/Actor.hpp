#ifndef Actor_hpp
#define Actor_hpp

#include <vector>
#include "Math.h"

class Game;
class Component;

class Actor
{
public:
    enum State
    {
        EActive,
        EPaused,
        EDead
    };

    Actor(Game* game);
    virtual ~Actor();

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime) {}

    // Get/Set function
    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }

    Vector2 GetPosition() const { return mPosition; }
    void SetPosition(Vector2 position) { mPosition = position; }

    float GetScale() const { return mScale; }
    void SetScale(float scale) { mScale = scale; }

    float GetRotation() const { return mRotation; }
    void SetRotation(float rotation) { mRotation = rotation; }

    void AddComponents(Component* component);
    void RemoveComponents(Component* component);

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