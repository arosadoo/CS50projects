-- SELECT people.name FROM people
-- WHERE people.id IN 
-- SELECT DISTINCT directors.person_id FROM directors
-- JOIN movies ON directors.movie_id = movies.movie_id 
-- JOIN ratings ON movies.movie_id = ratings.movie_id
-- WHERE ratings.rating >= 9;



SELECT people.name FROM people
WHERE people.id IN (SELECT DISTINCT directors.person_id FROM directors WHERE directors.movie_id IN (SELECT ratings.movie_id FROM ratings WHERE ratings.rating >= 9.0));
-- WHERE movies.movie_id IN 
-- SELECT ratings.movie_id FROM ratings
-- WHERE ratings.rating >= 9.0;