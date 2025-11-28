CREATE EXTENSION IF NOT EXISTS "uuid-ossp";
CREATE EXTENSION IF NOT EXISTS "pg_trgm";

-- ============================================
-- USERS
-- ============================================

CREATE TABLE users (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    email VARCHAR(255) NOT NULL UNIQUE,
    password_hash VARCHAR(255) NOT NULL,
    username VARCHAR(100),
    role VARCHAR(50) NOT NULL DEFAULT 'student', -- student, teacher, admin, moderator
    first_name VARCHAR(100),
    last_name VARCHAR(100),
    avatar_url TEXT,
    is_active BOOLEAN NOT NULL DEFAULT true,
    email_verified BOOLEAN NOT NULL DEFAULT false,
    created_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
    last_login_at TIMESTAMP WITH TIME ZONE
);

CREATE INDEX idx_users_email ON users(email);
CREATE INDEX idx_users_role ON users(role);
CREATE INDEX idx_users_created_at ON users(created_at);

-- ============================================
-- SUBJECTS
-- ============================================

CREATE TABLE subjects (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    name VARCHAR(200) NOT NULL,
    description TEXT,
    icon_url TEXT,
    color VARCHAR(7),
    display_order INTEGER DEFAULT 0,
    is_active BOOLEAN NOT NULL DEFAULT true,
    created_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- ============================================
-- Tests
-- ============================================

CREATE TABLE tests (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    subject_id UUID NOT NULL REFERENCES subjects(id) ON DELETE RESTRICT,
    title VARCHAR(500) NOT NULL,
    description TEXT,
    difficulty VARCHAR(20) NOT NULL DEFAULT 'medium', -- easy, medium, hard
    estimated_time_minutes INTEGER, -- estimated time to complete the test in minutes
    max_score INTEGER NOT NULL DEFAULT 100,
    passing_score INTEGER, -- percentage of max score required to pass the test
    is_published BOOLEAN NOT NULL DEFAULT false,
    is_archived BOOLEAN NOT NULL DEFAULT false,
    author_id UUID REFERENCES users(id) ON DELETE SET NULL,
    moderator_id UUID REFERENCES users(id) ON DELETE SET NULL,
    moderation_status VARCHAR(20) NOT NULL DEFAULT 'pending', -- pending, approved, rejected
    moderation_comment TEXT,
    version INTEGER NOT NULL DEFAULT 1,
    created_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
    published_at TIMESTAMP WITH TIME ZONE
);

CREATE INDEX idx_tests_subject_id ON tests(subject_id);
CREATE INDEX idx_tests_author_id ON tests(author_id);
CREATE INDEX idx_tests_difficulty ON tests(difficulty);
CREATE INDEX idx_tests_is_published ON tests(is_published);
CREATE INDEX idx_tests_moderation_status ON tests(moderation_status);
CREATE INDEX idx_tests_created_at ON tests(created_at);

CREATE INDEX idx_tests_title_trgm ON tests USING gin(title gin_trgm_ops);
CREATE INDEX idx_tests_description_trgm ON tests USING gin(description gin_trgm_ops);

-- ============================================
-- QUESTIONS
-- ============================================

CREATE TYPE question_type AS ENUM (
    'single_choice',   -- single choice question
    'multiple_choice', -- multiple choice question
    'text',            -- text question
    'number',          -- number question
    'ordering',        -- ordering question
    'matching'         -- matching question
);

CREATE TABLE questions (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    test_id UUID NOT NULL REFERENCES tests(id) ON DELETE CASCADE,
    question_text TEXT NOT NULL,
    question_type question_type NOT NULL DEFAULT 'single_choice',
    explanation TEXT, -- explanation of the question
    points INTEGER NOT NULL DEFAULT 1,
    display_order INTEGER NOT NULL DEFAULT 0,
    image_url TEXT,
    created_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_questions_test_id ON questions(test_id);
CREATE INDEX idx_questions_display_order ON questions(test_id, display_order);

-- ============================================
-- ANSWER OPTIONS
-- ============================================

CREATE TABLE answer_options (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    question_id UUID NOT NULL REFERENCES questions(id) ON DELETE CASCADE,
    option_text TEXT NOT NULL,
    is_correct BOOLEAN NOT NULL DEFAULT false,
    display_order INTEGER NOT NULL DEFAULT 0,
    created_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_answer_options_question_id ON answer_options(question_id);
CREATE INDEX idx_answer_options_display_order ON answer_options(question_id, display_order);

-- ============================================
-- PROGRESS OF USERS
-- ============================================

CREATE TYPE test_status AS ENUM (
    'started',      -- started, but not completed
    'completed',    -- completed
    'abandoned'     -- abandoned
);

CREATE TABLE user_test_progress (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    user_id UUID NOT NULL REFERENCES users(id) ON DELETE CASCADE,
    test_id UUID NOT NULL REFERENCES tests(id) ON DELETE CASCADE,
    status test_status NOT NULL DEFAULT 'started',
    score INTEGER,
    percentage DECIMAL(5,2), -- percentage of correct answers
    time_spent_seconds INTEGER,
    started_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
    completed_at TIMESTAMP WITH TIME ZONE,
    answers_json JSONB, -- detailed answers of the user
    created_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
    
    CONSTRAINT unique_user_test_attempt UNIQUE (user_id, test_id, started_at)
);

CREATE INDEX idx_user_test_progress_user_id ON user_test_progress(user_id);
CREATE INDEX idx_user_test_progress_test_id ON user_test_progress(test_id);
CREATE INDEX idx_user_test_progress_status ON user_test_progress(status);
CREATE INDEX idx_user_test_progress_completed_at ON user_test_progress(completed_at);
CREATE INDEX idx_user_test_progress_user_test ON user_test_progress(user_id, test_id);

-- Index for JSONB queries
CREATE INDEX idx_user_test_progress_answers_json ON user_test_progress USING gin(answers_json);

-- ============================================
-- USER STATISTICS
-- ============================================

CREATE TABLE user_statistics (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    user_id UUID NOT NULL REFERENCES users(id) ON DELETE CASCADE,
    subject_id UUID REFERENCES subjects(id) ON DELETE SET NULL,
    tests_completed INTEGER NOT NULL DEFAULT 0,
    tests_started INTEGER NOT NULL DEFAULT 0,
    total_score INTEGER NOT NULL DEFAULT 0,
    average_score DECIMAL(5,2),
    best_score INTEGER,
    total_time_spent_seconds INTEGER NOT NULL DEFAULT 0,
    last_activity_at TIMESTAMP WITH TIME ZONE,
    created_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
    
    CONSTRAINT unique_user_subject_stat UNIQUE (user_id, subject_id)
);

CREATE INDEX idx_user_statistics_user_id ON user_statistics(user_id);
CREATE INDEX idx_user_statistics_subject_id ON user_statistics(subject_id);
CREATE INDEX idx_user_statistics_last_activity ON user_statistics(last_activity_at);

-- ============================================
-- TAGS (for categorization of tests)
-- ============================================

CREATE TABLE tags (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    name VARCHAR(100) NOT NULL UNIQUE,
    color VARCHAR(7), -- hex color
    created_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_tags_name ON tags(name);

-- Many-to-many relationship between tests and tags
CREATE TABLE test_tags (
    test_id UUID NOT NULL REFERENCES tests(id) ON DELETE CASCADE,
    tag_id UUID NOT NULL REFERENCES tags(id) ON DELETE CASCADE,
    PRIMARY KEY (test_id, tag_id)
);

CREATE INDEX idx_test_tags_test_id ON test_tags(test_id);
CREATE INDEX idx_test_tags_tag_id ON test_tags(tag_id);

-- ============================================
-- TEST HISTORY
-- ============================================

CREATE TABLE test_history (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    test_id UUID NOT NULL REFERENCES tests(id) ON DELETE CASCADE,
    version INTEGER NOT NULL,
    changed_by UUID REFERENCES users(id) ON DELETE SET NULL,
    change_type VARCHAR(50) NOT NULL, -- created, updated, published, archived
    changes_json JSONB, -- details of changes
    created_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_test_history_test_id ON test_history(test_id);
CREATE INDEX idx_test_history_version ON test_history(test_id, version);
CREATE INDEX idx_test_history_created_at ON test_history(created_at);

-- ============================================
-- TRIGGERS FOR updated_at
-- ============================================

CREATE OR REPLACE FUNCTION update_updated_at_column()
RETURNS TRIGGER AS $$
BEGIN
    NEW.updated_at = CURRENT_TIMESTAMP;
    RETURN NEW;
END;
$$ language 'plpgsql';

CREATE TRIGGER update_users_updated_at BEFORE UPDATE ON users
    FOR EACH ROW EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_subjects_updated_at BEFORE UPDATE ON subjects
    FOR EACH ROW EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_tests_updated_at BEFORE UPDATE ON tests
    FOR EACH ROW EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_questions_updated_at BEFORE UPDATE ON questions
    FOR EACH ROW EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_user_test_progress_updated_at BEFORE UPDATE ON user_test_progress
    FOR EACH ROW EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_user_statistics_updated_at BEFORE UPDATE ON user_statistics
    FOR EACH ROW EXECUTE FUNCTION update_updated_at_column();