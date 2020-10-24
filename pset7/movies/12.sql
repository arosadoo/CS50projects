-- SELECT title FROM movies
-- WHERE id IN 
--     (SELECT stars.movie_id FROM stars WHERE stars.person_id IN 
--         (SELECT people.id FROM people WHERE people.name IN 
--             ('Johnny Depp','Helena Bonham Carter')
--         )
    
--     )





SELECT movies.title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Johnny Depp'
INTERSECT
SELECT movies.title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Helena Bonham Carter'



