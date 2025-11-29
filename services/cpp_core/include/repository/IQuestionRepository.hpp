//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include "model/entity/QuestionEntity.hpp"
#include <oatpp/core/Types.hpp>
#include <vector>

class IQuestionRepository {
public:
    virtual std::vector<QuestionEntity> getQuestionsByTestId(
        const oatpp::String& testId
    ) = 0;

    virtual QuestionEntity getQuestionById(
        const oatpp::String& id
    ) = 0;

    virtual ~IQuestionRepository() = default;
};