//
// Created by Rigbir on 04.12.25.
//

#pragma once

#include "repository/IUserRepository.hpp"
#include "database/UserDb.hpp"
#include <memory>

class UserRepository : public IUserRepository {
public:
    UserRepository();

    std::shared_ptr<UserEntity> getUserById(const oatpp::String& id) override;
    std::shared_ptr<UserEntity> getUserByEmail(const oatpp::String& email) override;
    
private:
    std::shared_ptr<UserDb> dbClient_;
};