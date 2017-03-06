-- Joins two lists
join [] xa = xa
join (xa:xas) xb = (xa: join xas xb)
