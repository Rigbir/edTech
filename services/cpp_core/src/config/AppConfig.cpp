//
// Created by Rigbir on 29.11.25.
// 

#include "config/AppConfig.hpp"
#include <stdexcept>
#include <cstdlib>
#include <limits>

AppConfig::AppConfig() {
    loadFromEnvironment();
}

AppConfig& AppConfig::getInstance() {
    static AppConfig instance;
    return instance;
}

std::string AppConfig::getEnvOrDefault(const char* envVar, const std::string& defaultValue) {
    const char* value = std::getenv(envVar);
    return value ? std::string(value) : defaultValue;
}

int AppConfig::getEnvIntOrDefault(const char* envVar, int defaultValue) {
    const char* value = std::getenv(envVar);
    if (!value) {
        return defaultValue;
    }

    try {
        return std::stoi(value);
    } catch (const std::invalid_argument& e) {
        return defaultValue;
    } catch (const std::out_of_range& e) {
        return defaultValue;
    }
}

bool AppConfig::isValidPort(int port) {
    return port >= 1 && port <= 65535;
}

void AppConfig::loadFromEnvironment() {
    serverPort_ = getEnvIntOrDefault("SERVER_PORT", 8080);
    serverHost_ = getEnvOrDefault("SERVER_HOST", "0.0.0.0");

    if (!isValidPort(serverPort_)) {
        serverPort_ = 8080; 
    }

    databaseHost_ = getEnvOrDefault("DATABASE_HOST", "localhost");
    databasePort_ = getEnvIntOrDefault("DATABASE_PORT", 5432);
    databaseName_ = getEnvOrDefault("DATABASE_NAME", "edTech");
    databaseUserName_ = getEnvOrDefault("DATABASE_USER", "postgres");
    databasePassword_ = getEnvOrDefault("DATABASE_PASSWORD", "");

    if (!isValidPort(databasePort_)) {
        databasePort_ = 5432; 
    }

    redisHost_ = getEnvOrDefault("REDIS_HOST", "localhost");
    redisPort_ = getEnvIntOrDefault("REDIS_PORT", 6379);
    redisPassword_ = getEnvOrDefault("REDIS_PASSWORD", "");

    if (!isValidPort(redisPort_)) {
        redisPort_ = 6379; 
    }

    logLevel_ = getEnvOrDefault("LOG_LEVEL", "INFO");
}

// =========================    
// Server configuration
// =========================
int AppConfig::getServerPort() const {
    return serverPort_;
}

std::string AppConfig::getServerHost() const {
    return serverHost_;
}

// =========================
// Database configuration
// =========================
std::string AppConfig::getDatabaseHost() const {
    return databaseHost_;
}

int AppConfig::getDatabasePort() const {
    return databasePort_;
}

std::string AppConfig::getDatabaseName() const {
    return databaseName_;
}

std::string AppConfig::getDatabaseUserName() const {
    return databaseUserName_;
}

std::string AppConfig::getDatabasePassword() const {
    return databasePassword_;
}

std::string AppConfig::getDatabaseConnectionString() const {
    return "postgresql://" + databaseUserName_ + ":" + databasePassword_ + 
           "@" + databaseHost_ + ":" + std::to_string(databasePort_) + 
           "/" + databaseName_;
}

// =========================
// Redis configuration
// =========================
std::string AppConfig::getRedisHost() const {
    return redisHost_;
}

int AppConfig::getRedisPort() const {
    return redisPort_;
}

std::string AppConfig::getRedisPassword() const {
    return redisPassword_;
}

// =========================
// Logging configuration
// =========================
std::string AppConfig::getLogLevel() const {
    return logLevel_;
}

bool AppConfig::validate() const {
    return isValidPort(serverPort_) &&
           isValidPort(databasePort_) &&
           isValidPort(redisPort_) &&
           !databaseName_.empty() &&
           !databaseUserName_.empty() &&
           !logLevel_.empty();
}
