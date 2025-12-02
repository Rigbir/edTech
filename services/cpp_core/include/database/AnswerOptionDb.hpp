//
// Created by Rigbir on 02.12.25.
//

#pragma once

#include <oatpp-postgresql/orm.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

/**
 * AnswerOptionDb - database client for answer_options table
 * 
 * Purpose: Defines prepared queries for answer options operations.
 *          Uses QUERY macros for type-safe database operations.
 */
class AnswerOptionDb : public oatpp::orm::DbClient {
public:
    AnswerOptionDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {}

    QUERY(getAnswerOptionsByQuestionId,
          "SELECT id, question_id, option_text, is_correct, display_order, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at "
          "FROM answer_options WHERE question_id=:questionId "
          "ORDER BY display_order ASC;",
          PREPARE(true),
          PARAM(oatpp::String, questionId))

    QUERY(getAnswerOptionById,
          "SELECT id, question_id, option_text, is_correct, display_order, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at "
          "FROM answer_options WHERE id=:id;",
          PREPARE(true),
          PARAM(oatpp::String, id))

    QUERY(getCorrectAnswerIds,
          "SELECT id FROM answer_options WHERE question_id=:questionId AND is_correct = TRUE;",
          PREPARE(true),
          PARAM(oatpp::String, questionId))
};

#include OATPP_CODEGEN_END(DbClient)

