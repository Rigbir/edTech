//
// Created by Rigbir on 29.11.25.
// 

#pragma once

#include <memory>
#include "config/AppConfig.hpp"
#include <oatpp-postgresql/Executor.hpp>
#include <oatpp-postgresql/ConnectionProvider.hpp>

// Singleton class for database client
// Initializes the database connection and executor
class DatabaseClient {
public:
    static DatabaseClient& getInstance();
    
    std::shared_ptr<oatpp::postgresql::Executor> getExecutor() const;
    std::shared_ptr<oatpp::postgresql::ConnectionProvider> getConnectionProvider() const;

    bool isConnected() const;
    void disconnect();

private:
    DatabaseClient();
    DatabaseClient(const DatabaseClient&) = delete;
    DatabaseClient& operator=(const DatabaseClient&) = delete;
    DatabaseClient(DatabaseClient&&) = delete;
    DatabaseClient& operator=(DatabaseClient&&) = delete;

    void initialize();

private: 
    std::shared_ptr<oatpp::postgresql::Executor> executor_;
    std::shared_ptr<oatpp::postgresql::ConnectionProvider> connectionProvider_;
};