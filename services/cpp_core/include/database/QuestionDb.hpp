//
// Created by Rigbir on 02.12.25.
//

#pragma once

#include <oatpp-postgresql/orm.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

/**
 * QuestionDb - database client for questions table
 * 
 * Purpose: Defines prepared queries for questions operations.
 *          Uses QUERY macros for type-safe database operations.
 */
class QuestionDb : public oatpp::orm::DbClient {
public:
    QuestionDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {}

    QUERY(getQuestionsByTestId,
          "SELECT id, test_id, question_text, question_type, explanation, points, "
          "display_order, image_url, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
          "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at "
          "FROM questions WHERE test_id=:testId ORDER BY display_order ASC;",
          PREPARE(true),
          PARAM(oatpp::String, testId))

    QUERY(getQuestionById,
          "SELECT id, test_id, question_text, question_type, explanation, points, "
          "display_order, image_url, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
          "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at "
          "FROM questions WHERE id=:id;",
          PREPARE(true),
          PARAM(oatpp::String, id))
};

#include OATPP_CODEGEN_END(DbClient)

