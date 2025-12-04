//
// Created by Rigbir on 04.12.25.
//

#pragma once

#include "model/entity/UserEntity.hpp"
#include <oatpp/core/Types.hpp>
#include <memory>

class IUserRepository {
public:
    virtual std::shared_ptr<UserEntity> getUserById(const oatpp::String& id) = 0;
    virtual std::shared_ptr<UserEntity> getUserByEmail(const oatpp::String& email) = 0;
    virtual ~IUserRepository() = default;
};