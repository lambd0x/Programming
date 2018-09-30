-- operator overloading == metatables
local function vec2(x,y) end
-- defines the table sum operator
local vec_meta = {
	__add = function(a,b)
		return vec2(
		a.x + b.x,
		a.y + b.y
		)
	end,
	__sub = function(a,b)
		return vec2(
		a.x - b.x,
		a.y - b.y
		)
	end,

}
function vec2(x,y)
	local v = {
		-- If x is nil then x=0
		x = x or 0,
		y = y or 0
	}
	setmetatable(v,vec_meta)
	return v
end
local a = vec2(2,5)
local b = vec2(5,2)
c = a + b
print(c.x,c.y)
c = a - b
print(c.x,c.y)

local function vec3(x,y) end
-- defines the table sum operator
local vec_meta2 = {
	-- meta method
	__add = function(a,b)
		return vec3(
		a.x + b.x,
		a.y + b.y
		)
	end,
	__sub = function(a,b)
		return vec3(
		a.x - b.x,
		a.y - b.y
		)
	end,
	__call = function(self)
		print("{" .. self.x .. "," .. self.y .."}")
	end,
	__tostring = function(self)
		return "{" .. self.x .. "," .. self.y .."}"
	end
}
function vec3(x,y)
	local v = {
		-- If x is nil then x=0
		x = x or 0,
		y = y or 0
	}
	setmetatable(v,vec_meta2)
	return v
end
local a = vec3(2,5)
local b = vec3(5,2)
c = a + b
c()
c = a - b
c()
c(tostring(c))

-- Table as a constant structure
local function c(tab)
	local meta_table = {
		-- this meta method is always by default called whenever a index search is done over the table
		__index = function(self, key)
			if tab[key] == nil then
				error("U tried to access a non-existing index entry: " .. key)
			else
				return tab[key]
			end
		end,
		-- this meta method is always by default called whenever a new entry is attempted to be insert in the table
		__newindex = function(self,key,value)
			error("U tried to access a constant structure: " .. key .." ".. value)
		end,
		__metatable = false
	}
	return setmetatable({}, meta_table)
end
local myStructConst = c{
	Gravity = 100,
	Speed = 50
}
-- will complain for modifying the const
myStructConst.Speed = 20
-- will complain for accessing non-existing entry
local try = myStructConst.Speedd

