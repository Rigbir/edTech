//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include "model/entity/TagEntity.hpp"
#include <oatpp/core/Types.hpp>
#include <vector>

class ITagRepository {
public:
    virtual std::vector<TagEntity> getAllTags() = 0;

    virtual std::vector<TagEntity> getTagsByTestId(
        const oatpp::String& testId
    ) = 0;

    virtual ~ITagRepository() = default;
};