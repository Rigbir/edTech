//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include "model/entity/TestEntity.hpp"
#include <oatpp/core/Types.hpp>
#include <vector>

class ITestRepository {
public:
    virtual TestEntity getTestById(
        const oatpp::String& id
    ) = 0;

    virtual std::vector<TestEntity> getTestsBySubjectId(
        const oatpp::String& subjectId
    ) = 0;

    virtual std::vector<TestEntity> getPublishedTests() = 0;
    
    virtual ~ITestRepository() = default;
};