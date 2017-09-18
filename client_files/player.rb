require './position.rb'

# This class is the main class for managing a player
class Player
	attr_accessor :width, :height, :map, :level, :pos

	def initialize width, height
		@pos = Position.new(0, 0, NORTH)
		@level = 1
		@width = width.to_i
		@height = height.to_i
		@map = Array.new(@width) { Array.new(@height, '') }
	end

	def see vision
		v = vision.delete('{').delete('}').split(',').each { |x| x.strip! }
		min = @pos.dup
		max = min.dup
		k = 0
		(@level + 1).times do
			l = 0
			(min.diff(max) + 1).times do
				if min.x == max.x
					@map[min.x][min.y + l] = v[k]
				else
					@map[min.x + l][min.y] = v[k]
				end
				l += 1
				k += 1
			end
			min.advance
			max.advance
			min.move @pos.get_left_dir
			max.move @pos.get_right_dir
		end
	end
end