--In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred

SELECT title FROM
movies JOIN stars ON movies.id = stars.movie_id
JOIN people ON people.id = stars.person_id
WHERE name = "Johnny Depp"
AND movie_id IN
(Select movie_id FROM
stars JOIN people ON people.id = stars.person_id
WHERE name = "Helena Bonham Carter")