# This class is for the main AI decision making

class AI
	attr_accessor :server, :player

	def initialize(player, server)
		@player = player
		@server = server
	end

	def find_food
		begin
			sight = self.see
			self.right && (sight = self.see) unless sight.include? 'food'
			self.right && (sight = self.see) unless sight.include? 'food'
			self.right && (sight = self.see) unless sight.include? 'food'
			@player.level.times { advance } unless sight.include? 'food'
		end while !(sight.include? 'food')
		@server.execute_list @player.path_to 'food'
		@player.goto_last_path_result
	end

	def advance
		@server.puts 'advance'
		@player.advance
	end

	def left
		@server.puts 'left'
		@player.left
	end

	def right
		@server.puts 'right'
		@player.right
	end

	def see
		@server.puts 'see'
		s = nil
		while s.nil? do
			s = @server.get(:see)
		end
		@player.see s[:see]
		s[:see]
	end
end