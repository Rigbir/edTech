//
// Created by Rigbir on 02.12.25.
//

#pragma once

#include <oatpp-postgresql/orm.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

/**
 * SubjectDb - database client for subjects table
 * 
 * Purpose: Defines prepared queries for subjects operations.
 *          Uses QUERY macros for type-safe database operations.
 */
class SubjectDb : public oatpp::orm::DbClient {
public:
    SubjectDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {}

    QUERY(getSubjects,
          "SELECT id, name, description, icon_url, color, display_order, is_active, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
          "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at "
          "FROM subjects WHERE is_active = TRUE ORDER BY display_order ASC;",
          PREPARE(true))

    QUERY(getSubjectById,
          "SELECT id, name, description, icon_url, color, display_order, is_active, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
          "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at "
          "FROM subjects WHERE id=:id AND is_active = TRUE;",
          PREPARE(true),
          PARAM(oatpp::String, id))

    QUERY(getSubjectsByTestId,
          "SELECT s.id, s.name, s.description, s.icon_url, s.color, s.display_order, s.is_active, "
          "EXTRACT(EPOCH FROM s.created_at)::bigint as created_at, "
          "EXTRACT(EPOCH FROM s.updated_at)::bigint as updated_at "
          "FROM subjects s "
          "INNER JOIN tests t ON t.subject_id = s.id "
          "WHERE t.id=:testId AND s.is_active = TRUE;",
          PREPARE(true),
          PARAM(oatpp::String, testId))
};

#include OATPP_CODEGEN_END(DbClient)

