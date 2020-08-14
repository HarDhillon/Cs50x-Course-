--In 9.sql, write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year
--DISTINCT	Selects only distinct (different) values    Source: https://www.w3schools.com/sql/sql_ref_keywords.asp

Select name FROM
people JOIN stars ON people.id = person_id
JOIN movies ON movies.id = stars.movie_id
WHERE year = 2004
-- To avoid the issue of ensuring each person only comes up once, but being careful of not removing people with the same name
--we can GROUP BY their unique people.id, so that if that persons id comes up e.g 5 times, the select will only select that GROUP rather than each
-- of the names 5 times, therefore the name is only counted ONCE
GROUP BY people.id
ORDER BY birth