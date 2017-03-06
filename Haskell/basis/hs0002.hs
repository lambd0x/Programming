-- Return the biggest element from a list
biggest [x] = x
biggest (x:xs) = if x > biggest xs then x else biggest xs
