-- Return the reversed list.
invert = temp []
     where
        temp accumulator [] = accumulator
        temp accumulator (x:xs) = temp (x:accumulator) xs
