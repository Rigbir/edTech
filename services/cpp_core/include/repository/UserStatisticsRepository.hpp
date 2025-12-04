//
// Created by Rigbir on 04.12.25.
//

#pragma once

#include "repository/IUserStatisticsRepository.hpp"
#include "database/UserStatisticsDb.hpp"
#include <memory>

/**
 * UserStatisticsRepository - works with user_statistics table
 * 
 * Purpose: Provides access to user statistics. Retrieves statistics by user ID and subject ID.
 * 
 * Dependencies: Depends on UserRepository (user_id FK).
 *               Used by UserService to get user statistics.
 */
class UserStatisticsRepository : public IUserStatisticsRepository {
public:
    UserStatisticsRepository();
    
    std::vector<std::shared_ptr<UserStatisticsEntity>> getStatisticsByUserId(
        const oatpp::String& userId
    ) override;
    
    std::shared_ptr<UserStatisticsEntity> getStatisticsByUserIdAndSubjectId(
        const oatpp::String& userId,
        const oatpp::String& subjectId
    ) override;

private:
    std::shared_ptr<UserStatisticsDb> dbClient_;
};