SELECT title, rating FROM
ratings JOIN movies ON ratings.movie_id = movies.id
WHERE year = 2010
ORDER BY rating DESC, title

-- to order by two things put a comma after the first thing to order by. So that here if they have same rating it orders by alphabet