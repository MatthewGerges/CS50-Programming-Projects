--In 8.sql, write a SQL query that lists the names of the songs that feature other artists.
--Songs that feature other artists will include “feat.” in the name of the song.
SELECT name FROM songs WHERE name LIKE "%feat.%";

--The Like function checks if the name INCLUDES "feat."
-- the % says it doesn't matter what is on the right of feat or left of the string