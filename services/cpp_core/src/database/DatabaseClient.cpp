//
// Created by Rigbir on 29.11.25.
// 

#include "database/DatabaseClient.hpp"
#include <string>

DatabaseClient::DatabaseClient() {
    initialize();
}

DatabaseClient& DatabaseClient::getInstance() {
    static DatabaseClient instance;
    return instance;
}

void DatabaseClient::initialize() {
    auto config = AppConfig::getInstance();
    auto connectionString = config.getDatabaseConnectionString();

    connectionProvider_ = std::make_shared<oatpp::postgresql::ConnectionProvider>(
        connectionString
    );

    executor_ = std::make_shared<oatpp::postgresql::Executor>(
        connectionProvider_
    );
}

std::shared_ptr<oatpp::postgresql::Executor> DatabaseClient::getExecutor() const {
    return executor_ ? executor_ : nullptr;
}

std::shared_ptr<oatpp::postgresql::ConnectionProvider> DatabaseClient::getConnectionProvider() const {
    return connectionProvider_ ? connectionProvider_ : nullptr;
}

bool DatabaseClient::isConnected() const {
    return connectionProvider_ && executor_;
}

void DatabaseClient::disconnect() {
    executor_.reset();
    connectionProvider_.reset();
}