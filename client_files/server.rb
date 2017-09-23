# This class is to control communications with the server
class Server
	attr_reader :host, :port, :team

	@@verbose ||= false

	def initialize(host, port, team, verbose = nil)
		@host = host
		@host ||= 'localhost'
		@port = port.to_i rescue abort('invalid port number')
		abort 'invalid port number' if @port < 1000 || @port > 65000
		@team = team
		@response ||= []

		@sock = TCPSocket.new @host, @port rescue abort "failed to connect to #{@host} on port #{@port}"
		@sock.puts @team

		@queue_read = Queue.new
		@queue_write = Queue.new
		@missing = Queue.new 
		
		@queue_read << 'welcome'
		@queue_read << 'connect_nbr'
		@queue_read << 'pos'

		@response_lock = Mutex.new

		@@verbose = verbose unless verbose.nil?

		@time_unit ||= 1 / 30

		listen_loop
		write_loop
	end

	def gets
		puts "in Server::gets" if @@verbose

		@response.empty? ? nil : @response.shift
	end

	def get(key_value)
		puts "in Server::get(#{value})" if @@verbose

		@response_lock.lock
		key_value = key_value.to_sym
		pos = @response.find_index { |e| e.keys.first == key_value }
		# binding.pry if pos.nil? && @response.size > 0
		r = @response.delete_at(pos) unless pos.nil?
		@response_lock.unlock

		r
	end

	def puts(msg)
		puts "in Server::puts('#{msg}')" if @@verbose

		run_request msg
	end

	def execute_list(list)
		puts "in Server::execute_list(#{list})" if @@verbose

		return if list.nil?

		list.each do |command|
			run_request command
		end
	end

	def run_request(request)
		@queue_write << request.to_s
	end

	# # should only be used for debug messages
	# def response_to(msg)
	# 	puts "in Server::response_to(#{msg})" if @@verbose

	# 	# @sock.puts msg
	# 	@queue_write << msg
	# 	@sock.gets.strip!.delete("\x00")
	# end

	def	get_direct
		puts "in Server::get_direct" if @@verbose

		begin
			response = gets
		end while response.nil?
		response
	end

	def get_approximate_timing
		t1 = Time.now
		@sock.puts 'connect_nbr'
		@sock.gets
		@sock.puts 'connect_nbr'
		@sock.gets
		t2 = Time.now

		@time_unit = (t2 - t1) / 2
	end

	def wait_for(key_value)
		t1 = Time.now
		loop do
			@last_response = get(key_value)
			break unless @last_response.nil?
			t2 = Time.now
			
			if (t2 - t1) > (7 * @time_unit) && @queue_write.empty?
				@queue_write << key_value.to_s
				t = Time.now
			end
		end
		@last_response
	end

	private

	def listen_loop
		Thread.new do
			loop do
				response = @sock.gets.strip!.delete("\x00")

				STDOUT.write "response: #{response}\n" # debug

				@response_lock.lock

				# interprate_response(response)

				key = (@queue_read.empty?) ? :unknown : @queue_read.pop.to_sym

				if !(%W(death GAMEOVER error moving message).find { |e| response.include? e })
					@response << { key => response }
				elsif %W(moving message).find { |e| response.include? e }
					@response << { move: response } if response.include? 'moving'
					@response << { message: response } if response.include? 'message'
				else
					abort "Server Returned: '#{response}'"
				end

				@response_lock.unlock
			end
		end
	end

	def write_loop
		Thread.new do
			loop do
				# t1 = Time.now
				loop do
					break if @queue_read.size < 10 && @queue_write.size > 0
					# t2 = Time.now
					# if (t2 - t1) >= 1
					# 	@sock.puts "connect_nbr\n"
					# 	@queue_read << 'connect_nbr'
					# 	binding.pry if @queue_read.size >= 11
					# 	t1 = Time.now
					# end
				end
				msg = @queue_write.pop
				@sock.puts msg + "\n"
				@queue_read << msg

				STDOUT.write "sent: #{msg}\n"
			end
		end
	end

	def interprate_response(response)
		if response.include?('{')
			key = (@queue_read.empty?) ? :unknown : @queue_read.pop.to_sym
			if (i.count(',') == 6)
				@missing << key if key != :inventory
				@response << { inventory: response }
			else
				@missing << key if key != :see
				@response << { see: response }
			end
		elsif %W(ok ko).include? response
			key = (@queue_read.empty?) ? :unknown : @queue_read.pop.to_sym
			@response << { key => response }
		elsif %W(moving message).find { |e| response.include? e }
			if response.include? 'moving'
				@response << { move: response } if response.include? 'moving'
			else
				@response << { message: response } if response.include? 'message'
			end
		elsif %W(death GAMEOVER error).include? response
			abort "Server Returned: '#{response}'"
		elsif response.to_i
			key = (@queue_read.empty?) ? :unknown : @queue_read.pop.to_sym
			@response << { key => response }
		end
	end
end