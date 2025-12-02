//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include "repository/IQuestionRepository.hpp"
#include "database/QuestionDb.hpp"
#include <memory>

/**
 * QuestionRepository - works with questions table
 *
 * Purpose: Provides access to questions for tests. Retrieves questions
 *          by test ID and individual questions by ID.
 *
 * Dependencies: Depends on TestRepository (via test_id foreign key).
 *               Used by TestService to build complete test structure.
 */
class QuestionRepository final: public IQuestionRepository {
public:
    QuestionRepository();

    std::vector<QuestionEntity> getQuestionsByTestId(
       const oatpp::String& testId
    ) override;

    QuestionEntity getQuestionById(
        const oatpp::String& id
    ) override;

private:
    std::shared_ptr<QuestionDb> dbClient_;
};