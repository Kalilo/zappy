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
end