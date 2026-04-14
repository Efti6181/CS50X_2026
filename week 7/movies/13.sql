SELECT DISTINCT p.name
FROM people p
JOIN stars s ON p.id = s.person_id
JOIN movies m ON s.movie_id = m.id
WHERE m.id IN (
    SELECT s2.movie_id
    FROM stars s2
    JOIN people kb ON s2.person_id = kb.id
    WHERE kb.name = 'Kevin Bacon' AND kb.birth = 1958
)
AND NOT (p.name = 'Kevin Bacon' AND p.birth = 1958);
