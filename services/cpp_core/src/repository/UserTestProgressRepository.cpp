//
// Created by Rigbir on 29.11.25.
//

#include "repository/UserTestProgressRepository.hpp"
#include "database/DatabaseClient.hpp"
#include "utils/EntityMapper.hpp"
#include <stdexcept>

UserTestProgressRepository::UserTestProgressRepository()
    : executor_(DatabaseClient::getInstance().getExecutor()) 
{
    if (!executor_) {
        throw std::runtime_error("Failed to initialize executor");
    }
}

UserTestProgressEntity UserTestProgressRepository::saveProgress(
    const UserTestProgressEntity& progress
) {
    auto result = executor_->execute(
        "INSERT INTO user_test_progress "
        "(user_id, test_id, status, score, percentage, time_spent_seconds, "
        "started_at, completed_at, answers_json) "
        "VALUES ($1, $2, $3, $4, $5, $6, "
        "TO_TIMESTAMP($7), TO_TIMESTAMP($8), $9::jsonb) "
        "RETURNING id, user_id, test_id, status, score, percentage, "
        "time_spent_seconds, "
        "EXTRACT(EPOCH FROM started_at)::bigint as started_at, "
        "EXTRACT(EPOCH FROM completed_at)::bigint as completed_at, "
        "answers_json::text as answers_json, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
        "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at",
        {
            progress.userId,
            progress.testId,
            progress.status,
            progress.score,
            progress.percentage,
            progress.timeSpentSeconds,
            progress.startedAt,
            progress.completedAt,
            progress.answersJson
        }
    );

    auto rows = result->fetch();
    if (!rows || rows->size() == 0) {
        throw std::runtime_error("Failed to save progress");
    }

    return EntityMapper::mapUserTestProgress(result, 0);
}

UserTestProgressEntity UserTestProgressRepository::updateProgress(
    const oatpp::String& id,
    const UserTestProgressEntity& progress
) {
    auto result = executor_->execute(
        "UPDATE user_test_progress SET "
        "status = $1, score = $2, percentage = $3, time_spent_seconds = $4, "
        "completed_at = TO_TIMESTAMP($5), answers_json = $6::jsonb "
        "WHERE id = $7 "
        "RETURNING id, user_id, test_id, status, score, percentage, "
        "time_spent_seconds, "
        "EXTRACT(EPOCH FROM started_at)::bigint as started_at, "
        "EXTRACT(EPOCH FROM completed_at)::bigint as completed_at, "
        "answers_json::text as answers_json, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
        "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at",
        {
            progress.status,
            progress.score,
            progress.percentage,
            progress.timeSpentSeconds,
            progress.completedAt,
            progress.answersJson,
            id
        }
    );

    auto rows = result->fetch();
    if (!rows || rows->size() == 0) {
        throw std::runtime_error("Progress not found");
    }

    return EntityMapper::mapUserTestProgress(result, 0);
}

std::vector<UserTestProgressEntity> UserTestProgressRepository::getProgress(
    const oatpp::String& userId,
    const oatpp::String& testId
) {
    auto result = executor_->execute(
        "SELECT id, user_id, test_id, status, score, percentage, "
        "time_spent_seconds, "
        "EXTRACT(EPOCH FROM started_at)::bigint as started_at, "
        "EXTRACT(EPOCH FROM completed_at)::bigint as completed_at, "
        "answers_json::text as answers_json, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
        "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at "
        "FROM user_test_progress "
        "WHERE user_id = $1 AND test_id = $2 "
        "ORDER BY started_at DESC",
        {userId, testId}
    );

    std::vector<UserTestProgressEntity> entities;
    auto rows = result->fetch();

    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapUserTestProgress(result, i));
    }

    return entities;
}

UserTestProgressEntity UserTestProgressRepository::getProgressById(
    const oatpp::String& id
) {
    auto result = executor_->execute(
        "SELECT id, user_id, test_id, status, score, percentage, "
        "time_spent_seconds, "
        "EXTRACT(EPOCH FROM started_at)::bigint as started_at, "
        "EXTRACT(EPOCH FROM completed_at)::bigint as completed_at, "
        "answers_json::text as answers_json, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
        "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at "
        "FROM user_test_progress WHERE id = $1",
        {id}
    );

    auto rows = result->fetch();
    if (!rows || rows->size() == 0) {
        throw std::runtime_error("Progress not found");
    }

    return EntityMapper::mapUserTestProgress(result, 0);
}