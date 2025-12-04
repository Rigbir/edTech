//
// Created by Rigbir on 29.11.25.
//

#include "utils/EntityMapper.hpp"

AnswerOptionEntity EntityMapper::mapAnswerOption(
    const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows,
    size_t rowIndex
) {
    auto row = rows[rowIndex];
    AnswerOptionEntity entity;

    entity.id = row["id"].retrieve<oatpp::String>();
    entity.questionId = row["question_id"].retrieve<oatpp::String>();
    entity.optionText = row["option_text"].retrieve<oatpp::String>();
    entity.isCorrect = row["is_correct"].retrieve<oatpp::Boolean>();
    entity.displayOrder = row["display_order"].retrieve<oatpp::Int32>();
    entity.createdAt = row["created_at"].retrieve<oatpp::Int64>();

    return entity;
}

QuestionEntity EntityMapper::mapQuestion(
    const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows,
    size_t rowIndex
) {
    auto row = rows[rowIndex];
    QuestionEntity entity;

    entity.id = row["id"].retrieve<oatpp::String>();
    entity.testId = row["test_id"].retrieve<oatpp::String>();
    entity.questionText = row["question_text"].retrieve<oatpp::String>();
    entity.questionType = row["question_type"].retrieve<oatpp::String>();
    entity.explanation = row["explanation"].retrieve<oatpp::String>();
    entity.points = row["points"].retrieve<oatpp::Int32>();
    entity.displayOrder = row["display_order"].retrieve<oatpp::Int32>();
    entity.imageUrl = row["image_url"].retrieve<oatpp::String>();
    entity.createdAt = row["created_at"].retrieve<oatpp::Int64>();
    entity.updatedAt = row["updated_at"].retrieve<oatpp::Int64>();

    return entity;
}

SubjectEntity EntityMapper::mapSubject(
    const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows,
    size_t rowIndex
) {
    auto row = rows[rowIndex];
    SubjectEntity entity;

    entity.id = row["id"].retrieve<oatpp::String>();
    entity.name = row["name"].retrieve<oatpp::String>();
    entity.description = row["description"].retrieve<oatpp::String>();
    entity.iconUrl = row["icon_url"].retrieve<oatpp::String>();
    entity.color = row["color"].retrieve<oatpp::String>();
    entity.displayOrder = row["display_order"].retrieve<oatpp::Int32>();
    entity.isActive = row["is_active"].retrieve<oatpp::Boolean>();
    entity.createdAt = row["created_at"].retrieve<oatpp::Int64>();
    entity.updatedAt = row["updated_at"].retrieve<oatpp::Int64>();

    return entity;
}

TagEntity EntityMapper::mapTag(
    const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows,
    size_t rowIndex
) {
    auto row = rows[rowIndex];
    TagEntity entity;

    entity.id = row["id"].retrieve<oatpp::String>();
    entity.name = row["name"].retrieve<oatpp::String>();
    entity.color = row["color"].retrieve<oatpp::String>();
    entity.createdAt = row["created_at"].retrieve<oatpp::Int64>();

    return entity;
}

TestEntity EntityMapper::mapTest(
    const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows,
    size_t rowIndex
) {
    auto row = rows[rowIndex];
    TestEntity entity;

    entity.id = row["id"].retrieve<oatpp::String>();
    entity.subjectId = row["subject_id"].retrieve<oatpp::String>();
    entity.title = row["title"].retrieve<oatpp::String>();
    entity.description = row["description"].retrieve<oatpp::String>();
    entity.difficulty = row["difficulty"].retrieve<oatpp::String>();
    entity.estimatedTimeMinutes = row["estimated_time_minutes"].retrieve<oatpp::Int32>();
    entity.maxScore = row["max_score"].retrieve<oatpp::Int32>();
    entity.passingScore = row["passing_score"].retrieve<oatpp::Int32>();
    entity.isPublished = row["is_published"].retrieve<oatpp::Boolean>();
    entity.isArchived = row["is_archived"].retrieve<oatpp::Boolean>();
    entity.authorId = row["author_id"].retrieve<oatpp::String>();
    entity.moderatorId = row["moderator_id"].retrieve<oatpp::String>();
    entity.moderationStatus = row["moderation_status"].retrieve<oatpp::String>();
    entity.moderationComment = row["moderation_comment"].retrieve<oatpp::String>();
    entity.version = row["version"].retrieve<oatpp::Int32>();
    entity.createdAt = row["created_at"].retrieve<oatpp::Int64>();
    entity.updatedAt = row["updated_at"].retrieve<oatpp::Int64>();
    entity.publishedAt = row["published_at"].retrieve<oatpp::Int64>();

    return entity;
}

UserEntity EntityMapper::mapUser(
    const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows,
    size_t rowIndex
) {
    auto row = rows[rowIndex];
    UserEntity entity;
    
    entity.id = row["id"].retrieve<oatpp::String>();
    entity.email = row["email"].retrieve<oatpp::String>();
    entity.passwordHash = row["password_hash"].retrieve<oatpp::String>();
    entity.username = row["username"].retrieve<oatpp::String>();
    entity.role = row["role"].retrieve<oatpp::String>();
    entity.firstName = row["first_name"].retrieve<oatpp::String>();
    entity.lastName = row["last_name"].retrieve<oatpp::String>();
    entity.avatarUrl = row["avatar_url"].retrieve<oatpp::String>();
    entity.isActive = row["is_active"].retrieve<oatpp::Boolean>();
    entity.emailVerified = row["email_verified"].retrieve<oatpp::Boolean>();
    entity.createdAt = row["created_at"].retrieve<oatpp::Int64>();
    entity.updatedAt = row["updated_at"].retrieve<oatpp::Int64>();
    entity.lastLoginAt = row["last_login_at"].retrieve<oatpp::Int64>();

    return entity;
}

UserStatisticsEntity EntityMapper::mapUserStatistics(
    const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows,
    size_t rowIndex
) {
    auto row = rows[rowIndex];
    UserStatisticsEntity entity;

    entity.id = row["id"].retrieve<oatpp::String>();
    entity.userId = row["user_id"].retrieve<oatpp::String>();
    entity.subjectId = row["subject_id"].retrieve<oatpp::String>();
    entity.testsCompleted = row["tests_completed"].retrieve<oatpp::Int32>();
    entity.testsStarted = row["tests_started"].retrieve<oatpp::Int32>();
    entity.totalScore = row["total_score"].retrieve<oatpp::Int32>();
    entity.averageScore = row["average_score"].retrieve<oatpp::Float32>();
    entity.bestScore = row["best_score"].retrieve<oatpp::Int32>();
    entity.totalTimeSpentSeconds = row["total_time_spent_seconds"].retrieve<oatpp::Int32>();
    entity.lastActivityAt = row["last_activity_at"].retrieve<oatpp::Int64>();
    entity.createdAt = row["created_at"].retrieve<oatpp::Int64>();
    entity.updatedAt = row["updated_at"].retrieve<oatpp::Int64>();

    return entity;
}

UserTestProgressEntity EntityMapper::mapUserTestProgress(
    const oatpp::Vector<oatpp::Fields<oatpp::Any>>& rows,
    size_t rowIndex
) {
    auto row = rows[rowIndex];
    UserTestProgressEntity entity;

    entity.id = row["id"].retrieve<oatpp::String>();
    entity.userId = row["user_id"].retrieve<oatpp::String>();
    entity.testId = row["test_id"].retrieve<oatpp::String>();
    entity.status = row["status"].retrieve<oatpp::String>();
    entity.score = row["score"].retrieve<oatpp::Int32>();
    entity.percentage = row["percentage"].retrieve<oatpp::Float32>();
    entity.timeSpentSeconds = row["time_spent_seconds"].retrieve<oatpp::Int32>();
    entity.startedAt = row["started_at"].retrieve<oatpp::Int64>();
    entity.completedAt = row["completed_at"].retrieve<oatpp::Int64>();
    entity.answersJson = row["answers_json"].retrieve<oatpp::String>();
    entity.createdAt = row["created_at"].retrieve<oatpp::Int64>();
    entity.updatedAt = row["updated_at"].retrieve<oatpp::Int64>();

    return entity;
}