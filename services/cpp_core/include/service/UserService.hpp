//
// Created by Rigbir on 04.12.25.
//

#pragma once

#include "repository/UserRepository.hpp"
#include "model/entity/UserEntity.hpp"
#include <oatpp/core/Types.hpp>
#include <memory>

class UserService {
public:
    UserService();

    std::shared_ptr<UserEntity> authenticate(
        const oatpp::String& email,
        const oatpp::String& password
    ) const;

private:
    bool verifyPassword(
        const oatpp::String& password,
        const oatpp::String& passwordHash
    ) const;

private:
    std::unique_ptr<UserRepository> userRepository_;
};