//
// Created by Rigbir on 04.12.25.
//

#pragma once

#include "model/entity/UserStatisticsEntity.hpp"
#include <oatpp/core/Types.hpp>
#include <memory>
#include <vector>

class IUserStatisticsRepository {
public:
    virtual std::vector<std::shared_ptr<UserStatisticsEntity>> getStatisticsByUserId(
        const oatpp::String& userId
    ) = 0;
    
    virtual std::shared_ptr<UserStatisticsEntity> getStatisticsByUserIdAndSubjectId(
        const oatpp::String& userId,
        const oatpp::String& subjectId
    ) = 0;
    
    virtual ~IUserStatisticsRepository() = default;
};