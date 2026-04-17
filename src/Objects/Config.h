#pragma once

#include <string>
#include <nlohmann/json.hpp>

class Config {
    
public:
    using json = nlohmann::json;

    static const json& cfg();
    static void Init(const std::string& path);

    Config(Config&) = delete;
    Config(Config&&) = delete;
    Config operator=(Config&) = delete;
    Config& operator=(Config&&) = delete;

private:
    Config() = default;
    json _json_cfg;
    static Config _config;
};

