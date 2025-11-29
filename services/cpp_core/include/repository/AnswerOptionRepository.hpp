//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include "repository/IAnswerOptionRepository.hpp"
#include <oatpp-postgresql/Executor.hpp>
#include "database/DatabaseClient.hpp"
#include <memory>

class AnswerOptionRepository: public IAnswerOptionRepository {
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
    std::shared_ptr<oatpp::postgresql::Executor> executor_;
};