-- In 5.sql, write a SQL query that returns the average energy of all the songs.
SELECT SUM(energy)/COUNT(name) FROM songs; 
--SUM(energy) returns the total sum of a numeric column
--COUNT(name) returns the total number of songs
--sum of energy of each song / total # of songs = average energy for each song

-- COULD ALSO HAVE DONE:
--SELECT AVG(energy) FROM songs
