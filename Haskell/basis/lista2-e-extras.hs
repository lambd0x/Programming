import Data.List
type Doc = String
type Line = String
type Word = String



linhas x = lines x

numLines (y:ys) = zip [1..] (y:ys)

allNumWords [] = []
allNumWords ((l, s):xs) = zip (repeat l) (words s) ++ allNumWords(xs)


compare1 (_, s1) (_, s2) = compare s1 s2
compare3 (_, s1) (_, s2) = s1 == s2

sortLs (xs) = sortBy compare1 (xs)

al a [] = []
al a ((l, s):xs)= if a == s then l:(al a xs)
                  else []

al2 a (l, s) = if a == s then l
                  else -1
                 

almalgamate [] = []
almalgamate ((l, s):xs) = ((l:(al s xs)), s):almalgamate (dropWhile (compare3 (l,s))xs)

shorten [] = []
shorten (((l:ls),s):xs) = ((l:dropWhile (==(l)) ls),s): shorten xs

data Arvore a = No a (Arvore a)(Arvore a)|Folha

instance (Show a)=>Show (Arvore a) where
  show Folha="folha"
  show (No x e d)="("++show e++")"++show x++"("++show d++")"
  
  
import Data.Functor

instance Functor Arvore where
  fmap g Folha = Folha
  fmap g(No x e d)= No (g x) (fmap g e) (fmap g d)
