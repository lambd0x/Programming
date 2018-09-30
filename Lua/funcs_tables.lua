-- function
-- lua functions are first-class functions, meaning a function is a value.
-- functions must have a defined goal and its name should reflect that
-- function purety means a function should not modify things beyond their scope
function func_name()
	print("Hello World")
end
func_name()

function func_name2(a,b)
	return a+b
end
local c = func_name2(5,3)
print(c)

function operation(a,b,operate)
	return operate(a,b)
end
local add = operation(5,3, function(a,b) return a + b end)
print(add)

-- function recursion
function fac(a)
	if a == 0 then
		return 1
	else
		return a*fac(a-1)
	end
end
print(fac(5))

-- nested function
function outerFunc()
	local function innerFunc()
		local myLocal = 10
	end
	local myLocal = 20
	print(myLocal)
end
print(outerFunc())

-- Table is a collection of variables in a single variable. Indexed from 1 onward
-- #tableName gives its length
-- {} is a empty table

-- Table used as an array
local myTable = {11,22,33,44,55}
-- Check table index value
print(myTable[1])
-- Change defined table index value
myTable[1] = 12345
-- Insert a new table index value
table.insert(myTable, 65)
table.insert(myTable, "str")
table.insert(myTable, fac(11))
print(myTable[1].."\n")
for i=1,#myTable,1 do
	print(myTable[i])
end
print()
-- Remove a defined table index value by specifying its table index
table.remove(myTable,#myTable)
for i=1,#myTable do
	print(myTable[i])
end

-- Table as structures
local myTable2 = {
	1,2,3,
	hello = 123
}
print(myTable2.hello)

local twodPoint = {
	x = 2,
	y = 5
}
print(twodPoint.y)

-- 2d Table ...
local myTable2 = {
	{1,2,3},
	{1,2,3}
}
for i=1, #myTable2 do
	for j=1, #myTable2[i] do
		-- I/O: print over same line -> io.write
		io.write(myTable2[i][j] .. " ")
	end
	print()
end
