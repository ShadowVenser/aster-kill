#include "Config.h"
#include <fstream>
#include <stdexcept>

Config::Config(const std::string& path) 
{
    Init(path);
}

void Config::Init(const std::string& path)
{
    std::ifstream cfgFile(path);
    if (!cfgFile.is_open())
        throw std::runtime_error("Config is not allowed");
    cfgFile >> _json_cfg;
}

const Config::json& Config::cfg() const
{
    return _json_cfg;
}