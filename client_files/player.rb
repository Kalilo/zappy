require './client_files/position.rb'

# This class is the main class for managing a player
class Player
	attr_accessor :width, :height, :map, :level, :pos, :team, :inventory

	@@verbose ||= false

	def initialize(width, height, verbose = nil)
		@pos = Position.new(0, 0, :north)
		@level = 1
		@width = width.to_i
		@height = height.to_i
		@pos.set_global_width @width
		@pos.set_global_height @height
		@map = Array.new(@width) { Array.new(@height, '') }
		@inventory = Hash.new(0)
		@path_result = @pos
		@@verbose = verbose unless verbose.nil?
	end

	def see(vision)
		puts "in Player::see('#{vision}')" if @@verbose

		v = vision.delete('{').delete('}').split(',').each { |x| x.strip! } rescue return
		min = @pos.dup
		max = min.dup
		k = 0
		(@level + 1).times do
			l = 0
			(min.diff(max) + 1).times do
				if min.x == max.x
					@map[min.x % @width][(min.y + l) % @height] = v[k] || ''
				else
					@map[(min.x + l) % @width][min.y % @height] = v[k] || ''
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
		puts "in Player::advance" if @@verbose

		@pos.advance
		@pos.x -= @width if @pos.x > @width
		@pos.x += @width if @pos.x < 0
		@pos.y -= @height if @pos.y > @height
		@pos.y += @height if @pos.y < 0
	end

	def right
		puts "in Player::right" if @@verbose

		@pos.turn_right
	end

	def left
		puts "in Player::left" if @@verbose

		@pos.turn_left
	end

	def take(item)
		puts "in Player::take('#{item}')" if @@verbose

		@map[@pos.x][@pos.y].slice! item.to_s
		@inventory[item.to_sym] += 1
	end

	def put(item)
		puts "in Player::put('#{item}')" if @@verbose

		@map[@pos.x][@pos.y] += " #{item.to_s}"
		@inventory[item.to_sym] -= 1
	end

	def move(dir)
		puts "in Player::move(#{dir})"

		@pos.move dir.to_sym
	end

	def path_to_pos(coord)
		puts "in Player::path_to_pos(#{coord})" if @@verbose

		gen_path_to_resource(coord)
	end

	def goto_last_path_result
		puts "in Player::goto_last_path_result" if @@verbose

		@pos = @path_result
	end

	def kick
		puts "in Player::kick" if @@verbose

		pos = @pos.dup
		pos.advance
		map[@pos.x][@pos.y].scan(/(?=#{'player'})/).count.times do
			map[pos.x][pos.y] += " player"
		end
		map[pos.x][pos.y].strip!
	end

	def required_res
		puts "in Player::required_res" if @@verbose

		case @level
			when 1
				{
					food: (@inventory[:food] >= 10 ? 0 : 10 - @inventory[:food]),
					linemate: (1 - @inventory[:linemate]),
					deraumere: 0,
					sibur: 0,
					mendiane: 0,
					phiras: 0,
					thystame: 0,
					player: 1 - @map[@pos.x % @width][@pos.y % @height].scan(/(?=#{'player'})/).count
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
					player: 2 - @map[@pos.x % @width][@pos.y % @height].scan(/(?=#{'player'})/).count
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
					player: 2 - @map[@pos.x % @width][@pos.y % @height].scan(/(?=#{'player'})/).count
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
					player: 4 - @map[@pos.x % @width][@pos.y % @height].scan(/(?=#{'player'})/).count
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
					player: 4 - @map[@pos.x % @width][@pos.y % @height].scan(/(?=#{'player'})/).count
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
					player: 6 - @map[@pos.x % @width][@pos.y % @height].scan(/(?=#{'player'})/).count
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
					player: 6 - @map[@pos.x % @width][@pos.y % @height].scan(/(?=#{'player'})/).count
				}
		end
	end

	def remaining_resources
		required = required_res || Hash.new(0)
		remaing = Hash.new(0)
		required.each { |k| remaing[k[0]] = @inventory[k[0]] - k[1] }
	end

	def path_to(resource)
		puts "in Player::path_to('#{resource}')" if @@verbose

		res_pos_hash = scan_map(resource)
		return { error: true } unless res_pos_hash[:count] > 0
		{ error: false, path: gen_path_to_resource(res_pos_hash) }
	end

	def update_inventory(inventory)
		puts "in Player::update_inventory('#{inventory}')" if @@verbose

		inventory.delete('{').delete('}').split(',').each do |item|
			item = item.split(' ')
			@inventory[item[0].to_sym] = item[1].to_i
		end
		@inventory
	end

	def exec_path(path)
		puts "in Player::exec_path('#{path}')" if @@verbose

		path.each do |command|
			case command
				when :advance
					@pos.advance
				when :left
					@pos.turn_left
				when :right
					@pos.turn_right
			end
		end
	end

	def current_pos
		puts "in Player::current_path" if @@verbose

		@map[@pos.x][@pos.y]
	end

	def scan_nearby(resource)
		puts "in Player::scan_nearby('#{resource}')" if @@verbose

		(0..2).each do |k|
			result = scan_square(k, resource)
		end
	end

	def get_food_level
		@inventory[:food]
	end

	private

	def scan_square(radius, resource)
		puts "in Player::scan_square('#{radius}', '#{resource}')" if @@verbose

		if (radius == 0)
			{ count: @map[@pos.x % @width][@pos.y % @height].scan(/(?=#{resource})/).count, x: @pos.x, y: @pos.y }
		else
			((@pos.x - radius)..(@pos.x + radius)).each do |k|
				count = @map[k % @width][(@pos.y - radius) % @height].scan(/(?=#{resource})/).count
				return { count: count, x: k % @width, y: (@pos.y - radius) % @height } if count > 0
				count = @map[k % @width][(@pos.y + radius) % @height].scan(/(?=#{resource})/).count
				return { count: count, x: k % @width, y: (@pos.y - radius) % @height } if count > 0
			end
			((@pos.y - radius + 1)..(@pos.y + radius - 1)).each do |k|
				count = @map[(@pos.x - radius) % @width][k % @height].scan(/(?=#{resource})/).count
				return { count: count, x: (@pos.x - radius) % @width, y: k % @height } if count > 0
				count = @map[(@pos.x + radius) % @width][k % @height].scan(/(?=#{resource})/).count
				return { count: count, x: (@pos.x + radius) % @width, y: k % @height } if count > 0
			end
		end
		{ count: 0 }
	end

	def scan_map(resource)
		puts "in Player::scan_map('#{resource}')" if @@verbose

		(0..(((@width > @height ? @width : @height) / 20.to_f).ceil)).each do |k|
			result = scan_square(k, resource)
			return result if result[:count] > 0
		end
		{ count: 0 }
	end

	def gen_path_to_resource(res_pos_hash)
		puts "in Player::gen_path_to_resource('#{res_pos_hash}')" if @@verbose

		res_pos = Position.new(res_pos_hash[:x], res_pos_hash[:y], @pos.dir)
		result = []
		pos = @pos.dup

		while (diff = pos.diff(res_pos)) > 0
			result << "take food".to_sym if @map[@pos.x][@pos.y].include? 'food'

			if res_pos.diff(pos.advance_pos) < diff
				pos.advance
				result << :advance
			elsif res_pos.diff(pos.right_pos) < diff
				pos.right
				result << :right << :advance
			elsif res_pos.diff(pos.left_pos) < diff
				pos.left
				result << :left << :advance
			elsif res_pos.x == pos.x && res_pos.y == pos.y
				next
			else
				if rand(0..1) == 1
					pos.turn_right
					pos.turn_right
					pos.advance
					result << :right << :right << :advance
				else
					pos.turn_left
					pos.turn_left
					pos.advance
					result << :left << :left << :advance
				end
			end
		end
		@path_result = res_pos
		result
	end
end