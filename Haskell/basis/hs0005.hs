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
expo a b = a^b

-- Returns the converted value of a binary number
bin2Int xs = bin2Int_ 0 0 (invert xs)
    where
        bin2Int_ a v [] = v
        bin2Int_ a v (x:xs) = if x=='1' then bin2Int_ (a+1) (v+(expo 2 a)) xs else bin2Int_ (a+1) v xs

-- Returns the result whether the input is prime or odd (0 is prime)
primeCheck a = if rem a 2==0 || a == 0 then True else False

-- Returns a list less the element informed
remo _ [] = []
remo a (x:xs) = if a==x then remo a xs else (x:remo a xs)

-- Returns a sorted lista
sort a = sortL (mini a) a
    where
        sortL x (a:as) = if x == a then remo x (a:as) else ([x,a]++sortL x as)

