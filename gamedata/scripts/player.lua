Player = ClassMaker:newClass()

function Player:new()
	return ClassMaker:newObject(self, DrawableEntity())
end

function Player:onUpdate()
	local speed = Core.deltaTime * 100

	if Input.isKeyboardPressed(KB_W) then
		self:move(Point(0, -1 * speed))
	end

	if Input.isKeyboardPressed(KB_A) then
		self:move(Point(-1 * speed, 0))
	end

	if Input.isKeyboardPressed(KB_S) then
		self:move(Point(0, 1 * speed))
	end

	if Input.isKeyboardPressed(KB_D) then
		self:move(Point(1 * speed, 0))
	end
end

