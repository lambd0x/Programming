-- Returns if element is present in the list
exists a [] = False
exists a (x:xs) = if a == x then True else exists a xs
