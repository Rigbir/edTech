//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include <oatpp/core/Types.hpp>

class TagEntity {
public:
    oatpp::String id;
    oatpp::String name;
    oatpp::String color;  // hex color (nullable)
    oatpp::Int64 createdAt;  // timestamp
};

