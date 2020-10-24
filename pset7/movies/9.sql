-- SELECT  count(name) FROM PEOPLE
-- JOIN stars ON  people.id = stars.person_id
-- JOIN movies ON stars.movie_id = movies.id
-- WHERE movies.year = 2004 AND  people.id IN (SELECT DISTINCT people.id FROM stars)
-- ORDER BY people.birth;

SELECT name FROM people 
WHERE id IN (SELECT DISTINCT person_id FROM STARS WHERE movie_id IN (SELECT id FROM movies WHERE year = 2004))
ORDER BY people.birth;