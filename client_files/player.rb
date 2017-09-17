require './position.rb'

# This class is the main class for managing a player
class Player
	attr_accessor :width, :height, :map, :level, :pos

	def initialize width, height
		@pos = Position.new(0, 0, north)
		@level = 1
		@width = width
		@height = height
		map = Array.new(width) { Array.new(height, '') }
	end

	def see vision
		vision = vision[1..-2].split(',')
		level = @level
		min = max = @pos
		k = 0
		level.times do
			l = 0
			min.diff(max).times do
				if min.x == max.x do
					map[(min.x + l) % @width][min.y % @height] = vision[k]
				else
					map[min.x % @width][(min.y + l) % @height] = vision[k]
				end
				l += 1
				k += 1
			end
			min.advance
			max.advance
			min.move pos.get_left_dir
			max.move pos.get_right_dir
		end
	end
end