//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include "repository/IUserTestProgressRepository.hpp"
#include <oatpp-postgresql/Executor.hpp>
#include <memory>

/**
 * UserTestProgressRepository - works with user_test_progress table
 * 
 * Purpose: Manages user progress for tests. Saves and retrieves progress,
 *          including answers stored as JSONB. Handles test attempts and
 *          completion status.
 * 
 * Dependencies: Depends on TestRepository (test_id FK) and User (user_id FK).
 *               Used by ProgressService to save/load user test progress.
 */
class UserTestProgressRepository : public IUserTestProgressRepository {
public:
    UserTestProgressRepository();

    UserTestProgressEntity saveProgress(
        const UserTestProgressEntity& progress
    ) override;

    UserTestProgressEntity updateProgress(
        const oatpp::String& id,
        const UserTestProgressEntity& progress
    ) override;

    std::vector<UserTestProgressEntity> getProgress(
        const oatpp::String& userId,
        const oatpp::String& testId
    ) override;

    UserTestProgressEntity getProgressById(
        const oatpp::String& id
    ) override;

private:
    std::shared_ptr<oatpp::postgresql::Executor> executor_;
};