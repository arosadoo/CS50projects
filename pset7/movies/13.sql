-- SELECT people.name FROM people
-- JOIN stars ON people.id = stars.person_id
-- WHERE stars.movie_id IN
-- (SELECT stars.movie_id FROM stars
-- WHERE people.name = 'Kevin Bacon' AND birth = 1958 )


-- SELECT people.name FROM people
-- WHERE people.id IN
-- (SELECT stars.person_id 
-- FROM 
-- (stars FULL OUTER JOIN () ON stars.movie_id
-- )



SELECT people.name FROM people
JOIN stars ON people.id = stars.person_id
WHERE (NOT name = "Kevin Bacon") AND movie_id IN
(SELECT stars.movie_id FROM stars
WHERE stars.person_id IN
(SELECT people.id FROM people
WHERE people.name = 'Kevin Bacon' AND people.birth = 1958))
GROUP BY people.name;