//
// Created by Rigbir on 29.11.25.
//

#include "utils/EntityMapper.hpp"

AnswerOptionEntity EntityMapper::mapAnswerOption(
    const std::shared_ptr<oatpp::postgresql::ResultSet>& result,
    size_t rowIndex
) {
    auto row = result->getRow(rowIndex);
    AnswerOptionEntity entity;

    entity.id = row->get(0)->toString();
    entity.questionId = row->get(1)->toString();
    entity.optionText = row->get(2)->toString();
    entity.isCorrect = row->get(3)->toBool();
    entity.displayOrder = row->get(4)->toInt32();
    entity.createdAt = row->get(5)->toInt64();

    return entity;
}

QuestionEntity EntityMapper::mapQuestion(
    const std::shared_ptr<oatpp::postgresql::ResultSet>& result,
    size_t rowIndex
) {
    auto row = result->getRow(rowIndex);
    QuestionEntity entity;

    entity.id = row->get(0)->toString();
    entity.testId = row->get(1)->toString();
    entity.questionText = row->get(2)->toString();
    entity.questionType = row->get(3)->toString();
    entity.explanation = row->get(4)->toString();
    entity.points = row->get(5)->toInt32();
    entity.displayOrder = row->get(6)->toInt32();
    entity.imageUrl = row->get(7)->toString();
    entity.createdAt = row->get(8)->toInt64();
    entity.updatedAt = row->get(9)->toInt64();

    return entity;
}

SubjectEntity EntityMapper::mapSubject(
    const std::shared_ptr<oatpp::postgresql::ResultSet>& result,
    size_t rowIndex
) {
    auto row = result->getRow(rowIndex);
    SubjectEntity entity;

    entity.id = row->get(0)->toString();
    entity.name = row->get(1)->toString();
    entity.description = row->get(2)->toString();
    entity.iconUrl = row->get(3)->toString();
    entity.color = row->get(4)->toString();
    entity.displayOrder = row->get(5)->toInt32();
    entity.isActive = row->get(6)->toBool();
    entity.createdAt = row->get(7)->toInt64();
    entity.updatedAt = row->get(8)->toInt64();

    return entity;
}

TagEntity EntityMapper::mapTag(
    const std::shared_ptr<oatpp::postgresql::ResultSet>& result,
    size_t rowIndex
) {
    auto row = result->getRow(rowIndex);
    TagEntity entity;

    entity.id = row->get(0)->toString();
    entity.name = row->get(1)->toString();
    entity.color = row->get(2)->toString();
    entity.createdAt = row->get(3)->toInt64();

    return entity;
}

TestEntity EntityMapper::mapTest(
    const std::shared_ptr<oatpp::postgresql::ResultSet>& result,
    size_t rowIndex
) {
    auto row = result->getRow(rowIndex);
    TestEntity entity;

    entity.id = row->get(0)->toString();
    entity.subjectId = row->get(1)->toString();
    entity.title = row->get(2)->toString();
    entity.description = row->get(3)->toString();
    entity.difficulty = row->get(4)->toString();
    entity.estimatedTimeMinutes = row->get(5)->toInt32();
    entity.maxScore = row->get(6)->toInt32();
    entity.passingScore = row->get(7)->toInt32();
    entity.isPublished = row->get(8)->toBool();
    entity.isArchived = row->get(9)->toBool();
    entity.authorId = row->get(10)->toString();
    entity.moderatorId = row->get(11)->toString();
    entity.moderationStatus = row->get(12)->toString();
    entity.moderationComment = row->get(13)->toString();
    entity.version = row->get(14)->toInt32();
    entity.createdAt = row->get(15)->toInt64();
    entity.updatedAt = row->get(16)->toInt64();
    entity.publishedAt = row->get(17)->toInt64();

    return entity;
}

UserTestProgressEntity EntityMapper::mapUserTestProgress(
    const std::shared_ptr<oatpp::postgresql::ResultSet>& result,
    size_t rowIndex
) {
    auto row = result->getRow(rowIndex);
    UserTestProgressEntity entity;

    entity.id = row->get(0)->toString();
    entity.userId = row->get(1)->toString();
    entity.testId = row->get(2)->toString();
    entity.status = row->get(3)->toString();
    entity.score = row->get(4)->toInt32();
    entity.percentage = row->get(5)->toFloat32();
    entity.timeSpentSeconds = row->get(6)->toInt32();
    entity.startedAt = row->get(7)->toInt64();
    entity.completedAt = row->get(8)->toInt64();
    entity.answersJson = row->get(9)->toString();
    entity.createdAt = row->get(10)->toInt64();
    entity.updatedAt = row->get(11)->toInt64();

    return entity;
}