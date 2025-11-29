//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include "model/entity/UserTestProgressEntity.hpp"
#include <oatpp/core/Types.hpp>
#include <vector>

class IUserTestProgressRepository {
public:
    virtual UserTestProgressEntity saveProgress(
        const UserTestProgressEntity& progress
    ) = 0;

    virtual UserTestProgressEntity updateProgress(
        const oatpp::String& id,
        const UserTestProgressEntity& progress
    ) = 0;

    virtual std::vector<UserTestProgressEntity> getProgress(
        const oatpp::String& userId,
        const oatpp::String& testId
    ) = 0;

    virtual UserTestProgressEntity getProgressById(
        const oatpp::String& id
    ) = 0;
    
    virtual ~IUserTestProgressRepository() = default;
};