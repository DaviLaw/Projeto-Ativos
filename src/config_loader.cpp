#include "config_loader.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

EmailConfig loadEmailConfig(const std::string& filename) {
    std::ifstream configFile(filename);
    if (!configFile.is_open()) {
        std::cerr << "[loadEmailConfig] Nao foi possivel abrir o arquivo: " << filename << std::endl;
    }

    json j;
    configFile >> j;

    EmailConfig emailConfig;
    emailConfig.smtp_server = j["smtp_server"];
    emailConfig.smtp_user = j["smtp_user"];
    emailConfig.smtp_pass = j["smtp_pass"];
    emailConfig.email_to = j["email_to"];
    emailConfig.email_from = j["email_from"];
    emailConfig.ibov_token = j["ibov_token"];

    return emailConfig;
}
