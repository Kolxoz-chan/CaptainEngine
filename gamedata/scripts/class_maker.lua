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
function ClassMaker:newObject(class, parent)

	-- If hasn't parent
	if parent == nil then
		class.__index = class
		return setmetatable({}, class)
	
	-- If parent is userdata
	elseif type(parent) == "userdata" then
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
	
	-- If parent is table
	elseif type(parent) == "table" then
		for key, val in pairs(class) do
			parent[key] = val			
		end
		return parent
	end
end