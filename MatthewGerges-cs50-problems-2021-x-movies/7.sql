--In 7.sql, write a SQL query to list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title.

SELECT title, rating FROM movies JOIN ratings ON movies.id = ratings.movie_id 
where id IN (SELECT id FROM movies WHERE year = 2010) ORDER BY rating DESC, title;

--ON movies.id = ratings.movie_id means JOIN (connect) the movies and ratings table only if they have the same movie id

/*
SELECT first_name, last_name, base_name
-- First name, last name and base name are the column names you want to select when you combine the tables
FROM martian 
-- FROM martian is the name of the first table
INNER JOIN base 
-- Inner JOIN base is the name of the second table you want to connect
ON martian.base_id = base.base_id
--Specify how to connect the 2 rows, only connect the marian and base row if they have the same base_id
--table.column
*/