--In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
--There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
--Kevin Bacon himself should not be included in the resulting list.

--SELECT name FROM people WHERE id IN (SELECT person_id FROM stars )

-- 1)list the names of all the movies that Kevin Bacon was in and , where name and birth = condition
--2)list the names of all the stars in those movies by nesting the above step

SELECT name FROM people WHERE name 
NOT IN("Kevin Bacon") 
AND id IN (SELECT person_id FROM stars where movie_id IN 
(SELECT id FROM movies where id IN 
(SELECT movie_id FROM stars WHERE person_id IN 
(SELECT id FROM people WHERE name = "Kevin Bacon" and birth = 1958))));

--Not in kevin bacon tells the program not to list kevin bacon in the actors list (could also come after last brackets)
-- Or could have done: and name != Kevin Bacon