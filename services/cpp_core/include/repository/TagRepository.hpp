//
// Created by Rigbir on 29.11.25.
//

#pragma once

#include "repository/ITagRepository.hpp"
#include <oatpp-postgresql/Executor.hpp>
#include <memory>

class TagRepository final: public ITagRepository {
public:
    TagRepository();

    std::vector<TagEntity> getAllTags() override;

    std::vector<TagEntity> getTagsByTestId(
        const oatpp::String& testId
    ) override;
private:
    std::shared_ptr<oatpp::postgresql::Executor> executor_;
};