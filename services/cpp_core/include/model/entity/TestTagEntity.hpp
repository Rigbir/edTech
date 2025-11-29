//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>

// Many-to-many relationship between tests and tags
class TestTagEntity {
public:
    oatpp::String testId;  // FK to tests (part of composite PK)
    oatpp::String tagId;   // FK to tags (part of composite PK)
};

