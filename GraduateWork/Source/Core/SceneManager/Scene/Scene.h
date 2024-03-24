#pragma once

class Scene
{
public:
	virtual ~Scene() = default;
	
    // Called when scene initially created. Called once.
    virtual void OnCreate() = 0; 
	
    // Called when scene destroyed. Called at most once (if a scene 
    // is not removed from the game, this will never be called).
    virtual void OnDestroy() = 0; 
    
    // Called whenever a scene is transitioned into. Can be 
    // called many times in a typical game cycle.
    virtual void OnActivate() = 0; 
	
    // Called whenever a transition out of a scene occurs. 
    // Can be called many times in a typical game cycle.
    virtual void OnDeactivate() = 0;
	
    virtual void Update(float DeltaTime) = 0;
	virtual void Draw() = 0;
};
