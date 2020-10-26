Player = ClassMaker:newClass()

function Player:new()
	return ClassMaker:newObject(self, DrawableEntity())
end

function Player:onUpdate()
	local speed = Core.deltaTime * 100

	if Input.isKeyboardPressed(KB_W) or Input.isKeyboardPressed(KB_UP) then
		self:move(Point(0, -1 * speed))
	end

	if Input.isKeyboardPressed(KB_A) or Input.isKeyboardPressed(KB_LEFT) then
		self:move(Point(-1 * speed, 0))
	end

	if Input.isKeyboardPressed(KB_S) or Input.isKeyboardPressed(KB_DOWN) then
		self:move(Point(0, 1 * speed))
	end

	if Input.isKeyboardPressed(KB_D) or Input.isKeyboardPressed(KB_RIGHT) then
		self:move(Point(1 * speed, 0))
	end

	local position = self:getPosition()
	Core.current_camera:setPosition(position)
end

