#pragma once

#include <string>
#include <nlohmann/json.hpp>

class Config {
    
public:
    using json = nlohmann::json;
    
    Config(const std::string& path);

    const json& cfg() const;
    
    Config(Config&) = delete;
    Config(Config&&) = delete;
    Config operator=(Config&) = delete;
    Config& operator=(Config&&) = delete;
    
private:
    json _json_cfg;
    
    void Init(const std::string& path);
};

