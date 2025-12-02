//
// Created by Rigbir on 02.12.25.
//

#pragma once

#include <oatpp-postgresql/orm.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

/**
 * TagDb - database client for tags table
 * 
 * Purpose: Defines prepared queries for tags operations.
 *          Uses QUERY macros for type-safe database operations.
 */
class TagDb : public oatpp::orm::DbClient {
public:
    TagDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {}

    QUERY(getAllTags,
          "SELECT id, name, color, "
          "EXTRACT(EPOCH FROM created_at)::bigint as created_at "
          "FROM tags "
          "ORDER BY name ASC;",
          PREPARE(true))

    QUERY(getTagsByTestId,
          "SELECT t.id, t.name, t.color, "
          "EXTRACT(EPOCH FROM t.created_at)::bigint as created_at "
          "FROM tags t "
          "INNER JOIN test_tags tt ON tt.tag_id = t.id "
          "WHERE tt.test_id=:testId "
          "ORDER BY t.name ASC;",
          PREPARE(true),
          PARAM(oatpp::String, testId))
};

#include OATPP_CODEGEN_END(DbClient)

