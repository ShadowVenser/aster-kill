#include "Config.h"
#include <fstream>
#include <stdexcept>

Config Config::_config {};

void Config::Init(const std::string& path)
{
    std::ifstream cfgFile(path);
    if (!cfgFile.is_open())
        throw std::runtime_error("Config is not allowed");
    cfgFile >> _config._json_cfg;
}

const Config::json& Config::cfg() 
{
    return _config._json_cfg;
}