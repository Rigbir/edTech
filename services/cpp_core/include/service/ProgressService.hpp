//
// Created by Rigbir on 01.12.25.
//

#pragma once

#include "repository/UserTestProgressRepository.hpp"
#include "model/dto/TestProgressDto.hpp"
#include <oatpp/core/Types.hpp>
#include <memory>
#include <vector>
#include <string>
#include <map>

/**
 * ProgressService - works with user test progress
 * 
 * Purpose: Manages user test progress. Saves and retrieves progress,
 *          including answers stored as JSONB. Handles test attempts and
 *          completion status.
 * 
 * Dependencies: Depends on TestService (test_id FK) and User (user_id FK).
 *               Used by TestController to build complete test structure.
 */
class ProgressService {
public:
    oatpp::Object<TestProgressDto> saveProgress(
        const oatpp::String& userId,
        const oatpp::String& testId,
        const std::map<std::string, std::vector<std::string>>& userAnswers,
        int timeSpentSeconds
    );

    oatpp::Object<TestProgressDto> getProgress(
        const oatpp::String& userId,
        const oatpp::String& testId
    );

    oatpp::Object<TestProgressDto> updateProgress(
        const oatpp::String& progressId,
        const std::map<std::string, std::vector<std::string>>& userAnswers,
        int timeSpentSeconds
    );

private:
    oatpp::Object<TestProgressDto> convertToDto(const UserTestProgressEntity& entity);

private:
    std::unique_ptr<UserTestProgressRepository> userTestProgressRepository_;
};