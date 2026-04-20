#include "Randomiser.h"
#include <iostream>

Randomiser::Randomiser(const Config& c):
    _seed(c.cfg()["window"].value("seed", std::random_device{}()))
{
    #ifdef DEBUG
        std::clog << "seed: " << _seed << '\n';
    #endif
    _gen.seed(_seed);
    
    _dstMM = {
        c.cfg().at("asteroid").at("destonation").at("min").get<float>(), 
        c.cfg().at("asteroid").at("destonation").at("max").get<float>() 
    };

    _dstMS = _GetMeanStd(_dstMM.x, _dstMM.y);
    
    _src = {
        c.cfg().at("asteroid").at("source").at("min").get<float>(), 
        c.cfg().at("asteroid").at("source").at("max").get<float>() 
    };

    _speedMM = {
        c.cfg().at("asteroid").at("speed").at("min").get<float>(), 
        c.cfg().at("asteroid").at("speed").at("max").get<float>() 
    };
    
    _speedMS = _GetMeanStd(_speedMM.x, _speedMM.y);

    _rotate = {
        c.cfg().at("asteroid").at("rotate").at("min").get<float>(), 
        c.cfg().at("asteroid").at("rotate").at("max").get<float>() 
    };

    _sprite = {0, c.cfg().at("asteroid").at("texture").at("sprite_count").get<int>() - 1};

    _spawn_time = _GetMeanStd(
        c.cfg().at("asteroid").at("spawn_time").at("min").get<float>(), 
        c.cfg().at("asteroid").at("spawn_time").at("max").get<float>() 
    );
}

float Randomiser::GetSrcPosition()
{
    static std::uniform_real_distribution<float> src(_src.x, _src.y);
    return src(_gen);
}

float Randomiser::GetDstPosition()
{
    static std::normal_distribution<float> dst {_dstMS.x, _dstMS.y};
    return std::clamp(dst(_gen), _dstMM.x, _dstMM.y);
}

float Randomiser::GetSpeed()
{
    static std::normal_distribution<float> speed {_speedMS.x, _speedMS.y};
    return std::clamp(speed(_gen), _speedMM.x, _speedMM.y);
}

float Randomiser::GetRotate()
{
    static std::uniform_real_distribution<float> rotate {_rotate.x, _rotate.y};
    return rotate(_gen);
}

int Randomiser::GetSprite()
{
    static std::uniform_int_distribution<int> sprite {_sprite.x, _sprite.y};
    return sprite(_gen);
}

float Randomiser::GetSpawnTime()
{
    static std::normal_distribution<float> spawn_time {_spawn_time.x, _spawn_time.y};
    auto ret = spawn_time(_gen);
    return ret;
}