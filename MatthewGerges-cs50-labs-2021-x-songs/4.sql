-- In 4.sql, write a SQL query that lists the names of any songs that have danceability, energy, and valence greater than 0.75.

SELECT name FROM songs WHERE danceability > 0.75 AND valence > 0.75 AND energy > 0.75;

--Past attempts and Rough Work:

--SELECT name FROM songs WHERE valence > 0.75 IN (SELECT name FROM songs WHERE (danceability > 0.75)) 
--and WHERE energy > 0.75 and WHERE valence > 0.75