//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include "repository/ISubjectRepository.hpp"
#include "database/SubjectDb.hpp"
#include <memory>

/** 
 * SubjectRepository - works with subjects table
 * 
 * Purpose: Manages subjects for tests. Retrieves subjects by ID or test ID.
 * 
 * Dependencies: None.
 */
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
    std::shared_ptr<SubjectDb> dbClient_;
};