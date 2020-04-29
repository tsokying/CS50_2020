SELECT DISTINCT(name) FROM people
JOIN stars ON people.id = stars.person_id
WHERE stars.movie_id IN
(SELECT movie_id FROM stars
JOIN people on stars.person_id = people.id
WHERE name = 'Kevin Bacon' and birth = 1958)
AND name != "Kevin Bacon";