//
// Created by Rigbir on 04.12.25.
//

#pragma once

#include <oatpp-postgresql/orm.hpp>
#include <oatpp/core/Types.hpp>

/**
 * UserStatisticsDb - database client for user_statistics table
 * 
 * Purpose: Defines prepared queries for user statistics operations.
 *          Uses QUERY macros for type-safe database operations.
 */
#include OATPP_CODEGEN_BEGIN(DbClient)

class UserStatisticsDb : public oatpp::orm::DbClient {
public:
    UserStatisticsDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {}

    QUERY(getStatisticsByUserId,
          "SELECT id, user_id, subject_id, tests_completed, tests_started, "
          "total_score, average_score, best_score, total_time_spent_seconds, "
          "EXTRACT(EPOCH FROM last_activity_at)::bigint as last_activity_at, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
          "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at "
          "FROM user_statistics WHERE user_id=:userId;",
          PREPARE(true),
          PARAM(oatpp::String, userId))

    QUERY(getStatisticsByUserIdAndSubjectId,
          "SELECT id, user_id, subject_id, tests_completed, tests_started, "
          "total_score, average_score, best_score, total_time_spent_seconds, "
          "EXTRACT(EPOCH FROM last_activity_at)::bigint as last_activity_at, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
          "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at "
          "FROM user_statistics WHERE user_id=:userId AND subject_id=:subjectId;",
          PREPARE(true),
          PARAM(oatpp::String, userId),
          PARAM(oatpp::String, subjectId))
};

#include OATPP_CODEGEN_END(DbClient)