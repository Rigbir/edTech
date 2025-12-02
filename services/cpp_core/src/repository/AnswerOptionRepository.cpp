//
// Created by Rigbir on 29.11.25.
//

#include "repository/AnswerOptionRepository.hpp"
#include "database/DatabaseClient.hpp"
#include "utils/EntityMapper.hpp"
#include <stdexcept>

AnswerOptionRepository::AnswerOptionRepository()
    : dbClient_(std::make_shared<AnswerOptionDb>(
          DatabaseClient::getInstance().getExecutor()
      ))
{
    if (!dbClient_) {
        throw std::runtime_error("Failed to initialize AnswerOptionDb");
    }
}

std::vector<AnswerOptionEntity> AnswerOptionRepository::getAnswerOptionsByQuestionId(
    const oatpp::String& questionId
) {
    auto queryResult = dbClient_->getAnswerOptionsByQuestionId(questionId);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    std::vector<AnswerOptionEntity> entities;
    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapAnswerOption(rows, i));
    }

    return entities;
}

AnswerOptionEntity AnswerOptionRepository::getAnswerOptionById(
    const oatpp::String& id
) {
    auto queryResult = dbClient_->getAnswerOptionById(id);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    if (!rows || rows->size() == 0) {
        throw std::runtime_error("Answer option not found");
    }

    return EntityMapper::mapAnswerOption(rows, 0);
}

std::vector<oatpp::String> AnswerOptionRepository::getCorrectAnswerIds(
    const oatpp::String& questionId
) {
    auto queryResult = dbClient_->getCorrectAnswerIds(questionId);
    auto rows = queryResult->fetch<oatpp::Vector<oatpp::Fields<oatpp::Any>>>();
    
    std::vector<oatpp::String> ids;
    for (size_t i = 0; i < rows->size(); ++i) {
        auto row = rows[i];
        ids.push_back(row["id"].retrieve<oatpp::String>());
    }

    return ids;
}
