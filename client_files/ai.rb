# This class is for the main AI decision making

class AI
	attr_accessor :server, :player

	@@verbose ||= false

	def initialize(player, server, verbose = nil)
		@player = player
		@server = server
		@@verbose = verbose unless verbose.nil?
	end

	def find_food
		puts "in AI::find_food" if @@verbose

		b = false
		begin
			sight = self.see
			b = b ? false : true
			if b
				self.right && (sight = self.see) unless sight.include? 'food'
				self.right && (sight = self.see) unless sight.include? 'food'
				self.right && (sight = self.see) unless sight.include? 'food'
			else
				self.left && (sight = self.see) unless sight.include? 'food'
				self.left && (sight = self.see) unless sight.include? 'food'
				self.left && (sight = self.see) unless sight.include? 'food'
			end
			@player.level.times { advance } unless sight.include? 'food'
		end while !(sight.include? 'food')

		path = @player.path_to('food')
		@server.execute_list path[:path]
		self.take 'food'
		@player.goto_last_path_result
	end

	def advance
		puts "in AI::advance" if @@verbose

		@server.puts 'advance'
		@player.advance
	end

	def left
		puts "in AI::left" if @@verbose

		@server.puts 'left'
		@player.left
	end

	def right
		puts "in AI::right" if @@verbose

		@server.puts 'right'
		@player.right
	end

	def see
		puts "in AI::see" if @@verbose

		@server.puts 'see'
		k = 0
		begin
			k += 1
			@server.puts 'see' if k % 1000000 == 0
			s = @server.get(:see)
		end while s.nil?
		@player.see s[:see]
		s[:see]
	end

	def take(resource)
		puts "in AI::take('#{resource}')" if @@verbose

		@server.puts "take #{resource}"
		@player.take resource
	end

	def put(resource)
		puts "in AI::put('#{resource}')" if @@verbose

		@server.puts "put #{resource}"
		@player.put resource
	end

	def broadcast(message)
		puts "in AI::broadcast('#{message}')" if @@verbose

		@server.puts "broadcast #{message}"
	end

	def look_for_resources
		puts "in AI::look_for_resources" if @@verbose

		required = @player.required_res
		pos = @player.current_pos
		current_required = required.select { |item| pos.include? item.to_s }
		found = false
		binding.pry
		current_required.each do |e|
			[pos.scan(/(?=#{e})/).count, e[1]].min.times do
				self.take e.first
				found = true
			end
		end
		unless found
			required.each do |e|
				path = @player.path_to e.first.to_s
				unless path[:error]
					@server.execute_list path[:path]
					@player.goto_last_path_result
					self.take e.first
					return true
				end
			end
		end
		found
	end

	def buff_results
		while (r = @server.gets)
			case r.keys.first
				when :advance
					abort "Fatal error: 'advance' returned '#{r.values.first}'" unless r.values.first == 'ok'
				when :right
					abort "Fatal error: 'right' returned '#{r.values.first}'" unless r.values.first == 'ok'
				when :left
					abort "Fatal error: 'left' returned '#{r.values.first}'" unless r.values.first == 'ok'
				when :message
					# handle message case
					recieve_message r.keys.first
				when :move
					@player.move r.values.first.split(' ')[1]
				when :incantation
					# handle incanation
					# should go find food?
				when :inventory
					# handle inventory
					@player.update_inventory r.keys.first
				when :fork
					abort "Fatal error: 'fork' returned '#{r.values.first}'" unless r.values.first == 'ok'
					# handle fork
				when :connect_nbr
					# handle connect_nbr
				when :see
					# handle see
					@player.see r.keys.first
				else
					if r.to_s.include? 'take'
						@player.put r.keys.first.to_s.split(' ')[1] if r.values.first == 'ko'
					elsif r.to_s.include? 'put'
						@player.take r.keys.first.to_s.split(' ')[1] if r.values.first == 'ko'
					elsif r.to_s.include? 'broadcast'
						# handle broadcast
					end
			end
		end
	end

	def run
		loop do
			find_food
			buff_results
			find_food
			pre_check_incanation if look_for_resources
		end
	end

	def can_incanate?(required_res)
		return false unless @incanation[:enough_res]
		return false unless required_res[:player] >= @incanation[:player]
		return true
	end

	private

	def pre_check_incanation(required_res)
		return unless enough_res_to_incanate? required_res

		@incanation[:enough_res] = true

		@server.puts "broadcast can_incanate?"
	end

	def recieve_message(message)
		m = (message.split(','))[1] || ''

		if m == "can_incanate?"
			if @incanation[:enough_res] == true
				@server.puts "can_incanate? yes"
			else
				@server.puts "can_incanate? no"
			end
		elsif m == "can_incanate? yes"
			@incanation[:players] += 1
		elsif m == "incantation" && @incanation[:enough_res] == false
			@incanation[:player] = 0
		end
	end

	def enough_res_to_incanate?(required_res)
		return false unless required_res[:food] >= 10
		return false unless required_res[:linemate] == 0
		return false unless required_res[:deraumere] == 0
		return false unless required_res[:sibur] == 0
		return false unless required_res[:mendiane] == 0
		return false unless required_res[:phiras] == 0
		return false unless required_res[:thystame] == 0

		true
	end

	def init_incanation_variable
		@incanation = {}
		@incanation[:enough_res] = false
		@incanation[:player] = 0
	end
end