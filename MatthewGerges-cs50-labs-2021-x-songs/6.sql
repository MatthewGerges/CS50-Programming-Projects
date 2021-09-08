--In 6.sql, write a SQL query that lists the names of songs that are by Post Malone.
-- STEP 1) get the ID  of the artist post malone from the artists table
-- STEP 2) find the names of the song where the ID matches the one found in step 2
-- STEP 1: SELECT id FROM artists WHERE name = "Post Malone"
-- STEP 2:
SELECT name FROM songs WHERE artist_id IN (SELECT id FROM artists WHERE name = "Post Malone");

--make sure the names of the ids match the names of the IDs in the table
--first mistake was SELECT name FROM songs WHERE id IN (SELECT id FROM artists WHERE name = "Post Malone")
-- But id was not in the songs table

-- Could also have done:
-- SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = "Post Malone")
-- = can replace IN and use only 1 equal sign instead of 2
