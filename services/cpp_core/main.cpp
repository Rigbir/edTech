#include "config/AppConfig.hpp"
#include <iostream>

int main() {
    auto& config = AppConfig::getInstance();
    
    std::cout << "=== Configuration ===" << std::endl;
    std::cout << "Server: " << config.getServerHost() << ":" << config.getServerPort() << std::endl;
    std::cout << "Database: " << config.getDatabaseHost() << ":" << config.getDatabasePort() << std::endl;
    std::cout << "Database Name: " << config.getDatabaseName() << std::endl;
    std::cout << "Database User: " << config.getDatabaseUserName() << std::endl;
    std::cout << "Database Password: " << (config.getDatabasePassword().empty() ? "[not set]" : "[set]") << std::endl;
    std::cout << "Redis: " << config.getRedisHost() << ":" << config.getRedisPort() << std::endl;
    std::cout << "Log Level: " << config.getLogLevel() << std::endl;
    std::cout << std::endl;
    
    std::string connectionString = config.getDatabaseConnectionString();
    std::cout << "Connection String: " << connectionString << std::endl;
    
    if (config.validate()) {
        std::cout << "Configuration is valid!" << std::endl;
    } else {
        std::cout << "WARNING: Configuration validation failed!" << std::endl;
    }
    
    return 0;
}