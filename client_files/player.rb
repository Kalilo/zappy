require './position.rb'

# This class is the main class for managing a player
class Player
	attr_accessor :width, :height, :x, :y, :map, :level, :dir

	def initialize width, height
		@x = 0
		@y = 0
		@level = 1
		@width = width
		@height = height
		map = Array.new(width) { Array.new(height, '') }
	end

	def see vision
		vision = vision[1..-2].split(',')
	end
end