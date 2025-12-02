//
// Created by Rigbir on 29.11.25.
//

#include "repository/QuestionRepository.hpp"
#include "database/DatabaseClient.hpp"
#include "utils/EntityMapper.hpp"
#include <stdexcept>

QuestionRepository::QuestionRepository()
    : dbClient_(std::make_shared<QuestionDb>(
          DatabaseClient::getInstance().getExecutor()
      ))
{
    if (!dbClient_) {
        throw std::runtime_error("Failed to initialize QuestionDb");
    }
}

std::vector<QuestionEntity> QuestionRepository::getQuestionsByTestId(
    const oatpp::String& testId
) {
    auto queryResult = dbClient_->getQuestionsByTestId(testId);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    std::vector<QuestionEntity> entities;
    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapQuestion(rows, i));
    }

    return entities;
}

QuestionEntity QuestionRepository::getQuestionById(
    const oatpp::String& id
) {
    auto queryResult = dbClient_->getQuestionById(id);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    if (!rows || rows->size() == 0) {
        throw std::runtime_error("Question not found");
    }

    return EntityMapper::mapQuestion(rows, 0);
}
