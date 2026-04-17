#include "KillerSystem.h"

void KillerSystem::OnInit()
{

}

void KillerSystem::OnUpdate()
{
    while (_clients.Count()){
        world.RemoveEntity(_clients.Entities()[0]);
    }
}
