--In 4.sql, write a SQL query to determine the number of movies with an IMDb rating of 10.0.
SELECT COUNT(movie_id) FROM ratings WHERE rating = 10.0;

--could do COUNT(movie_id) OR COUNT(rating): same output of 45
-- you can put 10.0 in quotes if you want