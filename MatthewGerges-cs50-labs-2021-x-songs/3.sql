--In 3.sql, write a SQL query to list the names of the top 5 longest songs, in descending order of length.
SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;
-- Desc makes sure they are in descending order of length
-- LIMIT 5 limits the query to the top 5 longest songs (limits number of rows)