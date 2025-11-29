//
// Created by Rigbir on 29.11.25.
//

#include "repository/QuestionRepository.hpp"
#include "database/DatabaseClient.hpp"
#include "utils/EntityMapper.hpp"
#include <stdexcept>

QuestionRepository::QuestionRepository()
    : executor_(DatabaseClient::getInstance().getExecutor())
{
    if (!executor_) {
        throw std::runtime_error("Failed to initialize executor");
    }
}

std::vector<QuestionEntity> QuestionRepository::getQuestionsByTestId(
    const oatpp::String& testId
) {
    auto result = executor_->execute(
        "SELECT id, test_id, question_text, question_type, explanation, points, "
        "display_order, image_url, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
        "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at "
        "FROM questions WHERE test_id = $1 ORDER BY display_order ASC",
        {testId}
    );

    std::vector<QuestionEntity> entities;
    auto rows = result->fetch();

    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapQuestion(result, i));
    }

    return entities;
}

QuestionEntity QuestionRepository::getQuestionById(
    const oatpp::String& id
) {
    auto result = executor_->execute(
        "SELECT id, test_id, question_text, question_type, explanation, points, "
        "display_order, image_url, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
        "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at "
        "FROM questions WHERE id = $1",
        {id}
    );

    auto rows = result->fetch();
    if (!rows || rows->size() == 0) {
        throw std::runtime_error("Question not found");
    }

    return EntityMapper::mapQuestion(result, 0);
}