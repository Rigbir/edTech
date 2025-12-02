//
// Created by Rigbir on 02.12.25.
//

#pragma once

#include <oatpp-postgresql/orm.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

/**
 * UserTestProgressDb - database client for user_test_progress table
 * 
 * Purpose: Defines prepared queries for user test progress operations.
 *          Uses QUERY macros for type-safe database operations.
 */
class UserTestProgressDb : public oatpp::orm::DbClient {
public:
    UserTestProgressDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {}

    QUERY(saveProgress,
          "INSERT INTO user_test_progress "
          "(user_id, test_id, status, score, percentage, time_spent_seconds, "
          "started_at, completed_at, answers_json) "
          "VALUES (:userId, :testId, :status, :score, :percentage, :timeSpentSeconds, "
          "TO_TIMESTAMP(:startedAt), TO_TIMESTAMP(:completedAt), :answersJson::jsonb) "
          "RETURNING id, user_id, test_id, status, score, percentage, "
          "time_spent_seconds, "
          "EXTRACT(EPOCH FROM started_at)::bigint as started_at, "
          "EXTRACT(EPOCH FROM completed_at)::bigint as completed_at, "
          "answers_json::text as answers_json, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
          "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at;",
          PREPARE(true),
          PARAM(oatpp::String, userId),
          PARAM(oatpp::String, testId),
          PARAM(oatpp::String, status),
          PARAM(oatpp::Int32, score),
          PARAM(oatpp::Float32, percentage),
          PARAM(oatpp::Int32, timeSpentSeconds),
          PARAM(oatpp::Int64, startedAt),
          PARAM(oatpp::Int64, completedAt),
          PARAM(oatpp::String, answersJson))

    QUERY(updateProgress,
          "UPDATE user_test_progress SET "
          "status=:status, score=:score, percentage=:percentage, "
          "time_spent_seconds=:timeSpentSeconds, "
          "completed_at=TO_TIMESTAMP(:completedAt), "
          "answers_json=:answersJson::jsonb "
          "WHERE id=:id "
          "RETURNING id, user_id, test_id, status, score, percentage, "
          "time_spent_seconds, "
          "EXTRACT(EPOCH FROM started_at)::bigint as started_at, "
          "EXTRACT(EPOCH FROM completed_at)::bigint as completed_at, "
          "answers_json::text as answers_json, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
          "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at;",
          PREPARE(true),
          PARAM(oatpp::String, id),
          PARAM(oatpp::String, status),
          PARAM(oatpp::Int32, score),
          PARAM(oatpp::Float32, percentage),
          PARAM(oatpp::Int32, timeSpentSeconds),
          PARAM(oatpp::Int64, completedAt),
          PARAM(oatpp::String, answersJson))

    QUERY(getProgress,
          "SELECT id, user_id, test_id, status, score, percentage, "
          "time_spent_seconds, "
          "EXTRACT(EPOCH FROM started_at)::bigint as started_at, "
          "EXTRACT(EPOCH FROM completed_at)::bigint as completed_at, "
          "answers_json::text as answers_json, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
          "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at "
          "FROM user_test_progress "
          "WHERE user_id=:userId AND test_id=:testId "
          "ORDER BY started_at DESC;",
          PREPARE(true),
          PARAM(oatpp::String, userId),
          PARAM(oatpp::String, testId))

    QUERY(getProgressById,
          "SELECT id, user_id, test_id, status, score, percentage, "
          "time_spent_seconds, "
          "EXTRACT(EPOCH FROM started_at)::bigint as started_at, "
          "EXTRACT(EPOCH FROM completed_at)::bigint as completed_at, "
          "answers_json::text as answers_json, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
          "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at "
          "FROM user_test_progress WHERE id=:id;",
          PREPARE(true),
          PARAM(oatpp::String, id))
};

#include OATPP_CODEGEN_END(DbClient)

