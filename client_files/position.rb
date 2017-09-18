# This class is to handle player positions
NORTH = 0
EAST = 1
SOUTH = 2
WEST = 3

class Position
	attr_accessor :x, :y, :dir

	def initialize x, y, dir
		@x, @y, @dir = x, y, dir
	end

	def move direction
		case direction
			when NORTH
				@y -= 1
			when EAST
				@x += 1
			when SOUTH
				@y += 1
			when WEST
				@x -= 1
			else
				@dir = NORTH
				@y -= 1
		end
	end

	# def move x, y
	# 	@x, @y = x, y
	# end

	def diff pos
		throw 'Can only run diff on Positions' unless pos.class == Position
		((pos.y - @y) + (pos.x - @x)).abs
	end

	def turn_right
		case @dir
			when NORTH
				@dir = EAST
			when EAST
				@dir = SOUTH
			when SOUTH
				@dir = WEST
			when WEST
				@dir = NORTH
			else
				@dir = NORTH
		end
	end

	def turn_left
		case @dir
			when NORTH
				@dir = WEST
			when EAST
				@dir = NORTH
			when SOUTH
				@dir = EAST
			when WEST
				@dir = SOUTH
			else
				@dir = NORTH
		end
	end

	def set_opposite_dir
		case @dir
			when NORTH
				@dir = SOUTH
			when EAST
				@dir = WEST
			when SOUTH
				@dir = NORTH
			when WEST
				@dir = EAST
			else
				@dir = SOUTH
		end
	end

	def advance
		case @dir
			when NORTH
				@y -= 1
			when EAST
				@x += 1
			when SOUTH
				@y += 1
			when WEST
				@x -= 1
			else
				@dir = NORTH
				@y -= 1
		end
	end

	def advance_pos
		y_new = @y.dup
		x_new = @x.dup
		case @dir
			when NORTH
				y_new -= 1
			when EAST
				x_new += 1
			when SOUTH
				y_new += 1
			when WEST
				x_new -= 1
			else
				@dir = NORTH
				y_new -= 1
		end
		Position.new x_new, y_new, @dir
	end

	def left_pos
		case @dir
			when NORTH
				Position.new(@x - 1, @y, WEST)
			when EAST
				Position.new(@x, @y - 1, NORTH)
			when SOUTH
				Position.new(@x + 1, @y, EAST)
			when WEST
				Position.new(@x, @y + 1, SOUTH)
			else
				Position.new(@x - 1, @y, WEST)
		end
	end

	def right_pos
		case @dir
			when NORTH
				Position.new(@x + 1, @y, EAST)
			when EAST
				Position.new(@x, @y + 1, SOUTH)
			when SOUTH
				Position.new(@x - 1, @y, WEST)
			when WEST
				Position.new(@x, @y - 1, NORTH)
			else
				Position.new(@x + 1, @y, EAST)
		end
	end

	def get_opposite_dir
		case @dir
			when NORTH
				SOUTH
			when EAST
				WEST
			when SOUTH
				NORTH
			when WEST
				EAST
			else
				SOUTH
		end
	end

	def get_left_dir
		case @dir
			when NORTH
				WEST
			when EAST
				NORTH
			when SOUTH
				EAST
			when WEST
				SOUTH
			else
				NORTH
		end
	end

	def get_right_dir
		case @dir
			when NORTH
				EAST
			when EAST
				SOUTH
			when SOUTH
				WEST
			when WEST
				NORTH
			else
				NORTH
		end
	end
end