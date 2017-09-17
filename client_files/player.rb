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
		level.times do
		end
	end
end