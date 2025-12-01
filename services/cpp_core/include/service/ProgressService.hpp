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
    std::shared_ptr<TestProgressDto> saveProgress(
        const oatpp::String& userId,
        const oatpp::String& testId,
        const std::map<oatpp::String, std::vector<oatpp::String>>& userAnswers,
        int timeSpentSeconds
    );

    std::shared_ptr<TestProgressDto> getProgress(
        const oatpp::String& userId,
        const oatpp::String& testId
    );

    std::shared_ptr<TestProgressDto> updateProgress(
        const oatpp::String& progressId,
        const std::map<oatpp::String, std::vector<oatpp::String>>& userAnswers,
        int timeSpentSeconds
    );

private:
    std::unique_ptr<UserTestProgressRepository> userTestProgressRepository_;
};