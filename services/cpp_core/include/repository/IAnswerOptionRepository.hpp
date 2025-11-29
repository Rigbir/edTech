//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <vector>
#include <oatpp/core/Types.hpp>
#include "model/entity/AnswerOptionEntity.hpp"

class IAnswerOptionRepository {
public:
    virtual std::vector<AnswerOptionEntity> getAnswerOptionsByQuestionId(
        const oatpp::String& questionId
    ) = 0;

    virtual AnswerOptionEntity getAnswerOptionById(
        const oatpp::String& id
    ) = 0;
    
    virtual std::vector<oatpp::String> getCorrectAnswerIds(
        const oatpp::String& questionId
    ) = 0;
    
    virtual ~IAnswerOptionRepository() = default;
};