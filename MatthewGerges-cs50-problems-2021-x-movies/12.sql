--In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
--SELECT title FROM movies where id IN (select movie_id FROM stars WHERE person_id IN(SELECT id FROM people where name = "Johnny Depp" AND name = "Helena Bonham Carter")) 

SELECT title FROM movies where id IN 
(select movie_id FROM stars WHERE person_id IN
(SELECT id FROM people WHERE name = "Johnny Depp")) 
AND id IN(SELECT movie_id FROM stars WHERE person_id IN
(SELECT id FROM people WHERE name = "Helena Bonham Carter")); 

-- the movie id links to the stars -> people where Johnny depp is found and the stars -> people where Helena Carter is found
-- Initial Mistake = checking if the person_id linked to both their person ids