Player = ClassMaker:newClass()

function Player:new()
	self.__index = self
	return ClassMaker:newObject(self, DrawableEntity())
end

function Player:onUpdate()
	local speed = Core.deltaTime * 100
	local vec = Point(-1 * speed, -0.5 * speed) 
	self:move(vec)
end