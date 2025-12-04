//
// Created by Rigbir on 04.12.25.
//

#include "repository/UserStatisticsRepository.hpp"
#include "database/DatabaseClient.hpp"
#include "utils/EntityMapper.hpp"
#include <stdexcept>

UserStatisticsRepository::UserStatisticsRepository()
    : dbClient_(std::make_shared<UserStatisticsDb>(
          DatabaseClient::getInstance().getExecutor()  
      ))
{
    if (!dbClient_) {
        throw std::runtime_error("Failed to initialize UserStatisticsDb");
    }
}

std::vector<std::shared_ptr<UserStatisticsEntity>> 
UserStatisticsRepository::getStatisticsByUserId(const oatpp::String& userId) {
    auto queryResult = dbClient_->getStatisticsByUserId(userId);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    std::vector<std::shared_ptr<UserStatisticsEntity>> result;
    if (!rows || rows->size() == 0) {
        return result;
    }
    
    for (size_t i = 0; i < rows->size(); ++i) {
        result.push_back(std::make_shared<UserStatisticsEntity>(
            EntityMapper::mapUserStatistics(rows, i)
        ));
    }
    
    return result;
}

std::shared_ptr<UserStatisticsEntity> 
UserStatisticsRepository::getStatisticsByUserIdAndSubjectId(
    const oatpp::String& userId,
    const oatpp::String& subjectId
) {
    auto queryResult = dbClient_->getStatisticsByUserIdAndSubjectId(userId, subjectId);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    if (!rows || rows->size() == 0) {
        return nullptr;
    }
    
    return std::make_shared<UserStatisticsEntity>(
        EntityMapper::mapUserStatistics(rows, 0)
    );
}