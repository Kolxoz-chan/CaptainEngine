ClassMaker = {}

-- Create new class
function ClassMaker:newClass()
	class = {}
	class.__index = class
	class.__call = function(self, ...)
		return self:new(...)
	end
	
	return setmetatable({}, class)
end

-- Create new object
function ClassMaker:newObject(old_class, parent)

	-- copying table --
	local class = {}
	for k,v in pairs(old_class) do
		class[k] = v
	end

	class.__index = class

	-- if parent is userdata
	if type(parent) == "userdata" then
		class.__parent = parent
		parent.self = class
		meta = {}
		 
		-- get index
		meta.__index = function(self, key)
			local parent = self.__parent
			
			if parent[key] ~= nil then
				if type(parent[key]) == "function" then
					return function(self, ...)
						return parent[key](self.__parent, ...)
					end
				else return parent[key] end
			else
				return rawget(self, key)
			end 
		end
		
		-- set new index
		meta.__newindex = function(self, key, value)
			local parent = self.__parent
			
			if parent[key] ~= nil then 
				parent[key] = value
			else 
				rawset(self, key, value)
			end
		end 

		return setmetatable(class, meta)
	
	-- if parent is table
	elseif type(parent) == "table" then
		for key, val in pairs(class) do
			parent[key] = val			
		end
		return parent
	end

	return setmetatable({}, class)
end