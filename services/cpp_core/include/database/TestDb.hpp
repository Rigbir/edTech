//
// Created by Rigbir on 02.12.25.
//

#pragma once

#include <oatpp-postgresql/orm.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

/**
 * TestDb - database client for tests table
 * 
 * Purpose: Defines prepared queries for tests operations.
 *          Uses QUERY macros for type-safe database operations.
 */
class TestDb : public oatpp::orm::DbClient {
public:
    TestDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {}

    QUERY(getTestById,
          "SELECT id, subject_id, title, description, difficulty, "
          "estimated_time_minutes, max_score, passing_score, "
          "is_published, is_archived, author_id, moderator_id, "
          "moderation_status, moderation_comment, version, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
          "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at, "
          "EXTRACT(EPOCH FROM published_at)::bigint as published_at "
          "FROM tests WHERE id=:id;",
          PREPARE(true),
          PARAM(oatpp::String, id))

    QUERY(getTestsBySubjectId,
          "SELECT id, subject_id, title, description, difficulty, "
          "estimated_time_minutes, max_score, passing_score, "
          "is_published, is_archived, author_id, moderator_id, "
          "moderation_status, moderation_comment, version, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
          "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at, "
          "EXTRACT(EPOCH FROM published_at)::bigint as published_at "
          "FROM tests "
          "WHERE subject_id=:subjectId AND is_published = true AND is_archived = false "
          "ORDER BY created_at DESC;",
          PREPARE(true),
          PARAM(oatpp::String, subjectId))

    QUERY(getPublishedTests,
          "SELECT id, subject_id, title, description, difficulty, "
          "estimated_time_minutes, max_score, passing_score, "
          "is_published, is_archived, author_id, moderator_id, "
          "moderation_status, moderation_comment, version, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
          "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at, "
          "EXTRACT(EPOCH FROM published_at)::bigint as published_at "
          "FROM tests "
          "WHERE is_published = true AND is_archived = false "
          "ORDER BY published_at DESC;",
          PREPARE(true))
};

#include OATPP_CODEGEN_END(DbClient)

