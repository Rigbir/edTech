//
// Created by Rigbir on 04.12.25.
//

#pragma once

#include <oatpp-postgresql/orm.hpp>
#include <oatpp/core/Types.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

class UserDb : public oatpp::orm::DbClient {
public:
    UserDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {}

    QUERY(getUserById,
        "SELECT id, email, password_hash, username, role, first_name, last_name, "
        "avatar_url, is_active, email_verified, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
        "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at, "
        "EXTRACT(EPOCH FROM last_login_at)::bigint as last_login_at "
        "FROM users WHERE id=:id AND is_active = TRUE;",
        PREPARE(true),
        PARAM(oatpp::String, id))

  QUERY(getUserByEmail,
        "SELECT id, email, password_hash, username, role, first_name, last_name, "
        "avatar_url, is_active, email_verified, "
        "EXTRACT(EPOCH FROM created_at)::bigint as created_at, "
        "EXTRACT(EPOCH FROM updated_at)::bigint as updated_at, "
        "EXTRACT(EPOCH FROM last_login_at)::bigint as last_login_at "
        "FROM users WHERE email=:email AND is_active = TRUE;",
        PREPARE(true),
        PARAM(oatpp::String, email))
};

#include OATPP_CODEGEN_END(DbClient)