//
// Created by Rigbir on 04.12.25.
//

#include "repository/UserRepository.hpp"
#include "database/DatabaseClient.hpp"
#include "utils/EntityMapper.hpp"
#include <stdexcept>

UserRepository::UserRepository()
    : dbClient_(std::make_shared<UserDb>(
        DatabaseClient::getInstance().getExecutor()
    ))
{
    if (!dbClient_) {
        throw std::runtime_error("Failed to initialize UserDb");
    }
}

std::shared_ptr<UserEntity> UserRepository::getUserById(const oatpp::String& id) {
    auto queryResult = dbClient_->getUserById(id);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    if (!rows || rows->size() == 0) {
        return nullptr;
    }

    return std::make_shared<UserEntity>(EntityMapper::mapUser(rows, 0));
}

std::shared_ptr<UserEntity> UserRepository::getUserByEmail(const oatpp::String& email) {
    auto queryResult = dbClient_->getUserByEmail(email);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    if (!rows || rows->size() == 0) {
        return nullptr;
    }
    
    return std::make_shared<UserEntity>(EntityMapper::mapUser(rows, 0));
}