require './position.rb'

# This class is the main class for managing a player
class Player
	attr_accessor :width, :height, :map, :level, :pos

	def initialize(width, height)
		@pos = Position.new(0, 0, NORTH)
		@level = 1
		@width = width.to_i
		@height = height.to_i
		@map = Array.new(@width) { Array.new(@height, '') }
		@inventory = Hash.new(0)
	end

	def see(vision)
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

	def advance
		@pos.advance
	end

	def right
		@pos.right
	end

	def left
		@pos.left
	end

	def take(item)
		@inventory[item.to_sym] += 1
	end

	def put(item)
		@inventory[item.to_sym] -= 1
	end

	def kick
		pos = @pos.dup
		pos.advance
		map[@pos.x][@pos.y].scan(/(?=#{'player'})/).count.times do
			map[pos.x][pos.y] += " player"
		end
		map[pos.x][pos.y].strip!
	end

	def required_res
		case @level
			when 1
				{
					food: (3 - @inventory[:food]),
					linemate: (1 - @inventory[:linemate]),
					deraumere: 0,
					sibur: 0,
					mendiane: 0,
					phiras: 0,
					thystame: 0,
					player: 1 - @map[@pos.x][@pos.y].scan(/(?=#{'player'})/).count
				}
			when 2
				{
					food: (3 - @inventory[:food]),
					linemate: (1 - @inventory[:linemate]),
					deraumere: (1 - @inventory[:deraumere]),
					sibur: (1 - @inventory[:sibur]),
					mendiane: 0,
					phiras: 0,
					thystame: 0,
					player: 2 - @map[@pos.x][@pos.y].scan(/(?=#{'player'})/).count
				}
			when 3
				{
					food: (3 - @inventory[:food]),
					linemate: (2 - @inventory[:linemate]),
					deraumere: 0,
					sibur: (1 - @inventory[:sibur]),
					mendiane: 0,
					phiras: (2 - @inventory[:phiras]),
					thystame: 0,
					player: 2 - @map[@pos.x][@pos.y].scan(/(?=#{'player'})/).count
				}
			when 4
				{
					food: (3 - @inventory[:food]),
					linemate: (1 - @inventory[:linemate]),
					deraumere: (1 - @inventory[:deraumere]),
					sibur: (2 - @inventory[:sibur]),
					mendiane: 0,
					phiras: (1 - @inventory[:phiras]),
					thystame: 0,
					player: 4 - @map[@pos.x][@pos.y].scan(/(?=#{'player'})/).count
				}
			when 5
				{
					food: (3 - @inventory[:food]),
					linemate: (1 - @inventory[:linemate]),
					deraumere: (2 - @inventory[:deraumere]),
					sibur: (1 - @inventory[:sibur]),
					mendiane: (3 - @inventory[:mendiane]),
					phiras: 0,
					thystame: 0,
					player: 4 - @map[@pos.x][@pos.y].scan(/(?=#{'player'})/).count
				}
			when 6
				{
					food: (3 - @inventory[:food]),
					linemate: (1 - @inventory[:linemate]),
					deraumere: (2 - @inventory[:deraumere]),
					sibur: (3 - @inventory[:sibur]),
					mendiane: 0,
					phiras: (1 - @inventory[:phiras]),
					thystame: 0,
					player: 6 - @map[@pos.x][@pos.y].scan(/(?=#{'player'})/).count
				}
			when 7
				{
					food: (3 - @inventory[:food]),
					linemate: (2 - @inventory[:linemate]),
					deraumere: (2 - @inventory[:deraumere]),
					sibur: (2 - @inventory[:sibur]),
					mendiane: (2 - @inventory[:mendiane]),
					phiras: (1 - @inventory[:phiras]),
					thystame: (1 - @inventory[:thystame]),
					player: 6 - @map[@pos.x][@pos.y].scan(/(?=#{'player'})/).count
				}
		end
	end
end