print "Hello World"

-- Variables are containers to values
-- Default scope is global unless local myvar is specified, confining the variable to the current scope only
-- Possible operations between values: + - / * ^ %
-- Unary: -
-- type(my_var) displays its type within Lua
-- Floar precision goes up to 13 digits
-- Math functions available = floor ceil max min sin cos tan asin acos exp log log10 pow sqrt random randomseed
print("floor(2.345)  = ", math.floor(2.345))--rounds down
print("ceil(2.345)   = ", math.ceil(2.345))--rounds up
math.randomseed(os.time())
print("random() = ", math.random())
print("random(10) = ", math.random(10))-- between 1 and 10
print("random(5,100)   = ", math.floor(5,100))

var1 = 50
var2 = 50
result = var1 % var2;
print(result)

-- Strings can be refined multilined or single lined.
shortStr = "Test"
print(shortStr)

longerStr = [[
Testing possibilities
Nice.
I'm done for now.
]]
print(longerStr)

-- String concatenation operator is .. between part1 and part2
full = shortStr .. result
print(full)

-- String format-like C
print(string.format("AHAH = %.10f", math.pi))

-- Binary operators: == >= <= ~= > <
-- Logical operators: and or not
print(var1 == var2)
print(var1 <= var2)
print(var1 >= var2)
print(var1 ~= var2)
print(var1 > var2)
print(var1 < var2)

-- ternary operator in Lua
local name = "Right"
local amI = name == "Right" and true or false
print(amI)

-- I/O:
-- read: io.read
print("Your name")
input = io.read()
print("Hi there " .. input .. ".")

print("Inform hello")
input2 = io.read()
check = (input2 == "hello")
print(check)

-- Conditionals: if else elseif
if input == "name" then
	print("Your name is awesome!")
elseif input2 == "hello" then
	print("Hi there, hello!")
else
	print("Your name is not good!")
end

-- Loops: for while repeat
local t1 = 100
local t2 = 50
while (t1 > t2) do
	print ("Hello " .. t2)
	t2 = t2 + 1
end

-- the third comma value is the counter step :)
for i=0, 50, 3 do
	print ("Hello2 " .. i)
end

--local t2 = 50
-- Equivalent to do-while, exits when true
repeat
	print ("Hello3 " .. t2)
until(t2 == t1)
