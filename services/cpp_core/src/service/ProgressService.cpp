//
// Created by Rigbir on 01.12.25.
//

#include "utils/JsonUtils.hpp"
#include "service/ProgressService.hpp"
#include "model/entity/UserTestProgressEntity.hpp"

std::shared_ptr<TestProgressDto> ProgressService::saveProgress(
    const oatpp::String& userId,
    const oatpp::String& testId,
    const std::map<oatpp::String, std::vector<oatpp::String>>& userAnswers,
    int timeSpentSeconds
) {
    std::string answersJson = JsonUtils::serializeAnswersToJson(userAnswers);

    UserTestProgressEntity progress;
    progress.userId = userId;
    progress.testId = testId;
    progress.status = "started";  
    progress.score = nullptr; 
    progress.percentage = nullptr;  
    progress.timeSpentSeconds = timeSpentSeconds;
    progress.startedAt = JsonUtils::getCurrentTimestamp(); 
    progress.completedAt = nullptr;  
    progress.answersJson = oatpp::String(answersJson.c_str());

    auto savedEntity = userTestProgressRepository_->saveProgress(progress);
    
    auto dto = convertToDto(savedEntity);
    return dto;
}

std::shared_ptr<TestProgressDto> ProgressService::getProgress(
    const oatpp::String& userId,
    const oatpp::String& testId
) {
    auto progressEntities = userTestProgressRepository_->getProgress(userId, testId);

    for (const auto& entity : progressEntities) {
        if (entity.status == "started") {
            auto dto = convertToDto(entity);
            return dto;
        }
    }

    return nullptr;
}

std::shared_ptr<TestProgressDto> ProgressService::updateProgress(
    const oatpp::String& progressId,
    const std::map<oatpp::String, std::vector<oatpp::String>>& userAnswers,
    int timeSpentSeconds
) {
    auto existingEntity = userTestProgressRepository_->getProgressById(progressId);
    
    std::string answersJson = JsonUtils::serializeAnswersToJson(userAnswers);

    UserTestProgressEntity updatedProgress;
    updatedProgress.userId = existingEntity.userId;  
    updatedProgress.testId = existingEntity.testId;  
    updatedProgress.status = existingEntity.status;  
    updatedProgress.score = existingEntity.score; 
    updatedProgress.percentage = existingEntity.percentage;  
    updatedProgress.timeSpentSeconds = timeSpentSeconds;  
    updatedProgress.startedAt = existingEntity.startedAt; 
    updatedProgress.completedAt = nullptr;  
    updatedProgress.answersJson = oatpp::String(answersJson.c_str());  

    auto savedEntity = userTestProgressRepository_->updateProgress(progressId, updatedProgress);

    auto dto = convertToDto(savedEntity);
    return dto;
}