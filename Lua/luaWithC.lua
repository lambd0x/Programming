foo = function(str)

	if(str == nil) then
		print("bar is nil")
	end

	local s, len = bar(str)
	print(s)
	return len
end
