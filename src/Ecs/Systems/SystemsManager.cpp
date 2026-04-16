#include "SystemsManager.h"

SystemsManager& SystemsManager::AddInitializer(std::shared_ptr<IInitializer> initializer)
{
    _newInitializers.push_back(initializer);
    return *this;
}

SystemsManager& SystemsManager::AddSystem(std::shared_ptr<ISystem> system)
{
    _systems.push_back(system);
    return *this;
}

void SystemsManager::Initialize()
{
    for (auto initializer: _newInitializers)
    {
        initializer->OnInit();
        _initializers.push_back(initializer);
    }
    _newInitializers.clear();
}

void SystemsManager::Update()
{
    Initialize();
    for (auto system: _systems)
        system->OnUpdate();
}
