//
// Created by Rigbir on 29.11.25.
//

#include "repository/AnswerOptionRepository.hpp"
#include "utils/EntityMapper.hpp"
#include <stdexcept>

AnswerOptionRepository::AnswerOptionRepository()
    : executor_(DatabaseClient::getInstance().getExecutor()) 
{
    if (!executor_) {
        throw std::runtime_error("Failed to initialize executor");
    }
}

std::vector<AnswerOptionEntity> AnswerOptionRepository::getAnswerOptionsByQuestionId(
    const oatpp::String& questionId
) {
    auto result = executor_->execute(
        "SELECT id, question_id, option_text, is_correct, display_order, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at "
        "FROM answer_options WHERE question_id = $1 ORDER BY display_order ASC",
        {questionId}
    );

    std::vector<AnswerOptionEntity> entities;
    auto rows = result->fetch();

    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapAnswerOption(result, i));
    }

    return entities;
}

AnswerOptionEntity AnswerOptionRepository::getAnswerOptionById(
    const oatpp::String& id
) {
    auto result = executor_->execute(
        "SELECT id, question_id, option_text, is_correct, display_order, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at "
        "FROM answer_options WHERE id = $1",
        {id}
    );

    auto rows = result->fetch();
    if (!rows || rows->size() == 0) {
        throw std::runtime_error("Answer option not found");
    }

    return EntityMapper::mapAnswerOption(result, 0);
}

std::vector<oatpp::String> AnswerOptionRepository::getCorrectAnswerIds(
    const oatpp::String& questionId
) {
    auto result = executor_->execute(
        "SELECT id FROM answer_options WHERE question_id = $1 AND is_correct = TRUE",
        {questionId}
    );

    std::vector<oatpp::String> ids;
    auto rows = result->fetch();

    for (size_t i = 0; i < rows->size(); ++i) {
        auto row = rows->get(i);
        ids.push_back(row->get(0)->toString());
    }

    return ids;
}