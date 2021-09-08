--In 9.sql, write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year.
Select name FROM people where id IN
(SELECT person_id FROM stars WHERE movie_id IN (SELECT id FROM movies WHERE year = 2004)) ORDER BY birth;
-- My program automatically did this: If a person appeared in more than one movie in 2004, they should only appear in your results once.
-- But how to do it manually?