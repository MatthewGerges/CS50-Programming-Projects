--In 7.sql, write a SQL query that returns the average energy of songs that are by Drake.
-- We have to combine two of the past queries:
--SELECT SUM(energy)/COUNT(name) FROM songs 
--SELECT name FROM songs WHERE artist_id IN (SELECT id FROM artists WHERE name = "Drake")
--drakesongs = SELECT name FROM songs WHERE artist_id IN (SELECT id FROM artists WHERE name = "Drake")
--SELECT SUM(SELECT energy FROM songs WHERE artist_id IN (SELECT id FROM artists WHERE name = "Drake"))/COUNT(SELECT energy FROM songs WHERE artist_id IN (SELECT id FROM artists WHERE name = "Drake"))
SELECT SUM(energy) / COUNT(energy) FROM songs WHERE artist_id IN (SELECT id FROM artists WHERE name = "Drake");
-- COULD have used AVG function