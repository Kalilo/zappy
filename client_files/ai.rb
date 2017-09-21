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

		begin
			sight = self.see
			self.right && (sight = self.see) unless sight.include? 'food'
			self.right && (sight = self.see) unless sight.include? 'food'
			self.right && (sight = self.see) unless sight.include? 'food'
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
		s = nil
		while s.nil? do
			s = @server.get(:see)
		end
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
		current_required.each do |e|
			[pos.scan(/(?=#{e})/).count, e[1]].min.times do
				self.take e.first
				found = true
			end
		end
		unless found
			current_required.each do |e|
				path = @player.path_to e.first.to_s
				unless path[:error]
					@server.execute_list path
					@player.goto_last_path_result
					self.take e.first
					return true
				end
			end
		end
		found
	end

	# def run
	# end
end