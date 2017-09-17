# This class is to handle player positions
enum {
	north,
	east,
	south,
	west
}

class Position
	attr_accessor :x, :y, :dir

	def initialize x, y, dir
		@x, @y, @dir = x, y, dir
	end

	def move direction
		case direction
			when north
				@y -= 1
			when east
				@x += 1
			when south
				@y += 1
			when west
				@x -= 1
			else
				@dir = north
				@y -= 1
		end
	end

	def move x, y
		@x, @y = x, y
	end

	def diff pos
		throw 'Can only run diff on Positions' unless pos.class == Position
		((pos.y - @y) + (pos.x - @x)).abs
	end

	def turn_right
		case @dir
			when north
				@dir = east
			when east
				@dir = south
			when south
				@dir = west
			when west
				@dir = north
			else
				@dir = north
		end
	end

	def turn_left
		case @dir
			when north
				@dir = west
			when east
				@dir = north
			when south
				@dir = east
			when west
				@dir = south
			else
				@dir = north
		end
	end

	def set_opposite_dir
		case @dir
			when north
				@dir = south
			when east
				@dir = west
			when south
				@dir = north
			when west
				@dir = east
			else
				@dir = south
		end
	end

	def advance
		case @dir
			when north
				@y -= 1
			when east
				@x += 1
			when south
				@y += 1
			when west
				@x -= 1
			else
				@dir = north
				@y -= 1
		end
	end

	def get_opposite_dir
		case @dir
			when north
				south
			when east
				west
			when south
				north
			when west
				east
			else
				south
		end
	end

	def get_left_dir
		case @dir
			when north
				west
			when east
				north
			when south
				east
			when west
				south
			else
				north
		end
	end

	def get_right_dir
		case @dir
			when north
				east
			when east
				south
			when south
				west
			when west
				north
			else
				north
		end
	end
end