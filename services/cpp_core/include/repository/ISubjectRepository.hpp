//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include "model/entity/SubjectEntity.hpp"
#include <oatpp/core/Types.hpp>
#include <vector>

class ISubjectRepository {
public:
    virtual std::vector<SubjectEntity> getSubjects() = 0;

    virtual SubjectEntity getSubjectById(
        const oatpp::String& id
    ) = 0;

    virtual std::vector<SubjectEntity> getSubjectsByTestId(
        const oatpp::String& testId
    ) = 0;

    virtual ~ISubjectRepository() = default;
};