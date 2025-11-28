# Database Schema

## Migration Structure

- `001_initial_schema.sql` - main database schema
- `002_seed_data.sql` - initial data (subjects, tags)

## Applying Migrations

- `users` - system users
- `subjects` - subjects (mathematics, physics, etc.)
- `tests` - tests
- `questions` - questions in tests
- `answer_options` - answer options
- `user_test_progress` - user progress
- `user_statistics` - aggregated statistics
- `tags` - tags for categorization
- `test_tags` - relationship between tests and tags
- `test_history` - test change history