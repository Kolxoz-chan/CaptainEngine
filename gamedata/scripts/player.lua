Player = ClassMaker:newClass()

function Player:new()
	self:setTarget(Point(300, 300))
	return ClassMaker:newObject(self, DrawableEntity())
end

function Player:onUpdate()
	-- Update control --
	self:contol_update()

	-- Getting values --
	local pos = self:getPosition()

	-- Move to target --
	if self.target then
		self:move_to(self.target, Core.deltaTime * 100)

		-- Reset target --
		--[[if self:target.x == pos.x and self:target.y == pos.y then
			resetTarget()
		end]]
	end

	-- Update camera --
	Core.current_camera:setPosition(pos)
end

-- Target reseting --
function Player:resetTarget()
	self.target = nil
end

-- Target seting --
function Player:setTarget(point)
	self.target = point
end

-- Update user actions --
function Player:contol_update()
	local speed = Core.deltaTime * 150

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
end

