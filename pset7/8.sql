--In 8.sql, write a SQL query to list the names of all people who starred in Toy Story

Select name FROM 
people JOIN stars ON people.id = person_id
JOIN movies ON movies.id = stars.movie_id
WHERE title ="Toy Story"

--joining 3 table together