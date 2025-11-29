//
// Created by Rigbir on 29.11.25.
//

#include "repository/SubjectRepository.hpp"
#include "database/DatabaseClient.hpp"
#include "utils/EntityMapper.hpp"
#include <stdexcept>

SubjectRepository::SubjectRepository()
    : executor_(DatabaseClient::getInstance().getExecutor())
{
    if (!executor_) {
        throw std::runtime_error("Failed to initialize executor");
    }
}

std::vector<SubjectEntity> SubjectRepository::getSubjects() {
    auto result = executor_->execute(
        "SELECT id, name, description, icon_url, color, display_order, is_active, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
        "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at "
        "FROM subjects WHERE is_active = TRUE ORDER BY display_order ASC"
    );

    std::vector<SubjectEntity> entities;
    auto rows = result->fetch();

    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapSubject(result, i));
    }

    return entities;
}

SubjectEntity SubjectRepository::getSubjectById(
    const oatpp::String& id
) {
    auto result = executor_->execute(
        "SELECT id, name, description, icon_url, color, display_order, is_active, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
        "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at "
        "FROM subjects WHERE id = $1 AND is_active = TRUE",
        {id}
    );

    auto rows = result->fetch();
    if (!rows || rows->size() == 0) {
        throw std::runtime_error("Subject not found");
    }

    return EntityMapper::mapSubject(result, 0);
}

std::vector<SubjectEntity> SubjectRepository::getSubjectsByTestId(
    const oatpp::String& testId
) {
    auto result = executor_->execute(
        "SELECT s.id, s.name, s.description, s.icon_url, s.color, s.display_order, s.is_active, "
        "EXTRACT(EPOCH FROM s.created_at)::bigint as created_at, "
        "EXTRACT(EPOCH FROM s.updated_at)::bigint as updated_at "
        "FROM subjects s "
        "INNER JOIN tests t ON t.subject_id = s.id "
        "WHERE t.id = $1 AND s.is_active = TRUE",
        {testId}
    );

    std::vector<SubjectEntity> entities;
    auto rows = result->fetch();

    for (size_t i = 0; i < rows->size(); ++i) {
        entities.push_back(EntityMapper::mapSubject(result, i));
    }

    return entities;
}
