//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include "repository/ISubjectRepository.hpp"
#include <oatpp-postgresql/Executor.hpp>
#include <memory>

class SubjectRepository final: public ISubjectRepository {
public:
    SubjectRepository();

    std::vector<SubjectEntity> getSubjects() override;

    SubjectEntity getSubjectById(
        const oatpp::String &id
    ) override;

    std::vector<SubjectEntity> getSubjectsByTestId(
        const oatpp::String& testId
    ) override;

private:
    std::shared_ptr<oatpp::postgresql::Executor> executor_;
};