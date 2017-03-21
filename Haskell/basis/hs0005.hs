-- Returns a joined list
join [] xa = xa
join (xa:xas) xb = (xa: join xas xb)

-- Returns if element is present in the list
exists a [] = False
exists a (x:xs) = if a == x then True else exists a xs

-- Returns the biggest element from a list
biggest [x] = x
biggest (x:xs) = if x > biggest xs then x else biggest xs

-- Returns the fatorial of n
fato 0 = 1
fato n = n * fato(n-1)

-- Returns the reversed list.
invert = temp []
     where
        temp accumulator [] = accumulator
        temp accumulator (x:xs) = temp (x:accumulator) xs

-- Returns n elements from a list
gen _ [] = []
gen 0  _ = []
gen n (x:xs) = x:gen(n-1) xs

-- Returns the intersection of two lists
inter a b = inter2 a b []
    where
        inter2 as [] la = la
        inter2 as (x:xs) la = if elem x as then inter2 as xs (la++[x]) else inter2 as xs la

-- Returns the smallest element of a list
mini (x:xa) = min2 x xa
    where
        min2 x [] = x
        min2 y (x:xs) = if y<x then min2 y xs else min2 x xs

-- Returns the exponential of n
powr a 0 = 1
powr a x = a * (powr a (x-1))

-- Returns the converted value of a binary number
bin xs = bin2 (reverse xs)
 where
  bin2 [x] = bin3 x
  bin2 (x:xs) = bin3 x + 2 * (bin2 xs)
  bin3 '0' = 0
  bin3 '1' = 1

-- Returns the result whether the input is even or odd (0 is even)
evk a = if rem a 2==0 || a == 0 then True else False

-- Returns the list according to the predicative's rule
pApply _ [] = []
pApply a (x:xs) = if a x == True then x:pApply a xs else pApply a xs

-- Returns the list according to the negation of the predicative's rule
pNApply xs = pApply (not . evk) xs

-- Returns a list with the first elements from a list of tuples.
firstList = map (\(a,b) -> a)

-- Returns True or False according to the truth list
truth a = foldr (&&) True a

-- Returns the sum of the element's list
sumL (x:xs) = foldr (+) x xs

-- Returns a list of tuples from two lists
tupAll [] [] = []
tupAll (x:xs) (y:ys) = (x,y):tupAll xs ys

-- Returns True if a element doesn't divide anyone else.
notd _ [] = []
notd a (x:xs) = if (mod x a /= 0) then True:notd a xs else False:notd a xs


-- Returns using the sieve of eratosthenes a list of primes
--siev a = test [2..a]
--    where
--        test [] = []
--        test (x:xs) =  if truth (notd  x xs) && not (evk x) then x:test xs else test xs
