//
// Created by Rigbir on 29.11.25.
//

#include "repository/UserTestProgressRepository.hpp"
#include "database/DatabaseClient.hpp"
#include "utils/EntityMapper.hpp"
#include <stdexcept>

UserTestProgressRepository::UserTestProgressRepository()
    : dbClient_(std::make_shared<UserTestProgressDb>(
          DatabaseClient::getInstance().getExecutor()
      ))
{
    if (!dbClient_) {
        throw std::runtime_error("Failed to initialize UserTestProgressDb");
    }
}

UserTestProgressEntity UserTestProgressRepository::saveProgress(
    const UserTestProgressEntity& progress
) {
    auto queryResult = dbClient_->saveProgress(
        progress.userId,
        progress.testId,
        progress.status,
        progress.score,
        progress.percentage,
        progress.timeSpentSeconds,
        progress.startedAt,
        progress.completedAt,
        progress.answersJson
    );
    
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    if (!rows || rows->size() == 0) {
        throw std::runtime_error("Failed to save progress");
    }

    return EntityMapper::mapUserTestProgress(rows, 0);
}

UserTestProgressEntity UserTestProgressRepository::updateProgress(
    const oatpp::String& id,
    const UserTestProgressEntity& progress
) {
    auto queryResult = dbClient_->updateProgress(
        id,
        progress.status,
        progress.score,
        progress.percentage,
        progress.timeSpentSeconds,
        progress.completedAt,
        progress.answersJson
    );
    
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    if (!rows || rows->size() == 0) {
        throw std::runtime_error("Progress not found");
    }

    return EntityMapper::mapUserTestProgress(rows, 0);
}

std::vector<UserTestProgressEntity> UserTestProgressRepository::getProgress(
    const oatpp::String& userId,
    const oatpp::String& testId
) {
    auto queryResult = dbClient_->getProgress(userId, testId);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    std::vector<UserTestProgressEntity> entities;
    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapUserTestProgress(rows, i));
    }

    return entities;
}

UserTestProgressEntity UserTestProgressRepository::getProgressById(
    const oatpp::String& id
) {
    auto queryResult = dbClient_->getProgressById(id);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    if (!rows || rows->size() == 0) {
        throw std::runtime_error("Progress not found");
    }

    return EntityMapper::mapUserTestProgress(rows, 0);
}
