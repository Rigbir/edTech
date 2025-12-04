//
// Created by Rigbir on 29.11.25.
// 

#pragma once

#include <string>

// Singleton class for application configuration
class AppConfig {
public:
    static AppConfig& getInstance();

    // Server configuration
    int getServerPort() const;
    std::string getServerHost() const;

    // Database configuration
    std::string getDatabaseHost() const;
    int getDatabasePort() const;
    std::string getDatabaseName() const;
    std::string getDatabaseUserName() const;
    std::string getDatabasePassword() const;
    std::string getDatabaseConnectionString() const; 

    // Redis configuration
    std::string getRedisHost() const;
    int getRedisPort() const;
    std::string getRedisPassword() const;

    // Logging configuration
    std::string getLogLevel() const;

    bool validate() const;

    std::string getJwtSecretKey() const;

private:
    AppConfig();
    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;
    AppConfig(AppConfig&&) = delete;
    AppConfig& operator=(AppConfig&&) = delete;

    void loadFromEnvironment();

    // Helper functions
    static std::string getEnvOrDefault(const char* envVar, const std::string& defaultValue);
    static int getEnvIntOrDefault(const char* envVar, int defaultValue);
    static bool isValidPort(int port);

    // Server configuration
    int serverPort_;
    std::string serverHost_;
    
    // Database configuration
    std::string databaseHost_;
    int databasePort_;
    std::string databaseName_;
    std::string databaseUserName_;
    std::string databasePassword_;

    // Redis configuration
    std::string redisHost_;
    int redisPort_;
    std::string redisPassword_;

    // Logging configuration
    std::string logLevel_;

    std::string jwtSecretKey_;
};