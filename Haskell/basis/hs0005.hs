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

-- Returns using the sieve of eratosthenes a list of primes
prime (x:xs) = x:(prime(filter (divi x) xs))
    where
        divi a b = (mod b a) /= 0

-- Implements the filter functionality
filtera f (xs) = [x | x<-xs, f x]

-- Gen. the fibo sequence indef
fibao = fibo 0 1
    where
        fibo a b = a:fibo b (b+a)

-- Abstract Type(AT) performing natural number's operations
data Nat = Zero | Sec Nat deriving Show

-- AT natural's autoincrement
inc x = (Suc x)

-- AT natural's sum
summ Zero    y = y
summ (Suc x) y = soma x (Suc y)

--AT natural's product
prod (Suc Zero) y = y
prod Zero       y = Zero
prod y       Zero = Zero
prod x    (Suc y) = summ x (prod x y)

--AT natural's subtraction
subt x  Zero = x
subt Zero  y = Zero
subt (Suc x) (Suc y) = subt x y

--AT natural's division
divy x y = divy2 x y Zero
  where
    divy2 _ Zero       const = error "Error!"
    divy2 x (Suc Zero) const = x
    divy2 Zero y       const = (Suc const)
    divy2 x y          const = dive2 (sube x y) y (Suc const)

--Regular natural to AT natural
natCV 0 = Zero
natCV x = Suc (natCV(x-1))

cvNAT Zero = 0
cvNAT (Suc x) = 1 + (cvNAT(x))

--AT natural to regular natural


