//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include "repository/IAnswerOptionRepository.hpp"
#include "database/AnswerOptionDb.hpp"
#include <memory>

/**
 * AnswerOptionRepository - works with answer_options table
 * 
 * Purpose: Manages answer options for test questions. Retrieves options
 *          by question ID and provides correct answer IDs for validation.
 * 
 * Dependencies: Depends on QuestionRepository (question_id FK).
 */
class AnswerOptionRepository final: public IAnswerOptionRepository {
public:
    AnswerOptionRepository();

    std::vector<AnswerOptionEntity> getAnswerOptionsByQuestionId(
        const oatpp::String& questionId
    ) override;

    AnswerOptionEntity getAnswerOptionById(
        const oatpp::String& id
    ) override;

    std::vector<oatpp::String> getCorrectAnswerIds(
        const oatpp::String& questionId
    ) override;

private:
    std::shared_ptr<AnswerOptionDb> dbClient_;
};