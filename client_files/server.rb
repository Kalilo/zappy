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
		# @missing = Queue.new 
		
		@queue_read << 'welcome'
		@queue_read << 'connect_nbr'
		@queue_read << 'pos'

		@response_lock = Mutex.new

		@@verbose = verbose unless verbose.nil?

		@time_unit ||= (1.0 / 2.0)

		listen_loop
		# write_loop
	end

	def gets
		puts "in Server::gets" if @@verbose

		@response_lock.lock
		r = @response.empty? ? nil : @response.shift
		@response_lock.unlock

		r
	end

	def get(key_value)
		puts "in Server::get(#{value})" if @@verbose

		@response_lock.lock
		key_value = key_value.to_sym
		r = @response.find { |h| h.keys.first == key_value }
		@response.reject! { |h| h.keys.first == key_value }
		# pos = @response.find_index { |e| e.keys.first == key_value }
		# binding.pry if pos.nil? && @response.size > 0
		# r = @response.delete_at(pos) unless pos.nil?
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

	def	get_direct
		puts "in Server::get_direct" if @@verbose

		begin
			response = gets
		end while response.nil?
		response
	end

	def get_approximate_timing
		sleep(0.5)
		# Thread.new do
			t1 = Time.now
			@sock.puts "connect_nbr\n"
			@sock.gets
			@sock.puts "connect_nbr\n"
			@sock.gets
			t2 = Time.now

			@time_unit = (t2.to_f - t1.to_f).fdiv(2.0)
		# end
		@time_unit
	end

	def wait_for(key_value)
		t1 = Time.now
		loop do
			@last_response = get(key_value)
			break unless @last_response.nil?
			t2 = Time.now

			if ((t2 - t1) > (7 * @time_unit) && @queue_write.empty?) || ((t2 - t1) > 7 && @queue_read.empty?)
				@queue_write << key_value.to_s
				t = Time.now
			end
		end
		@last_response
	end

	def activate_write_loop
		return unless @queue_write.nil?
		@queue_write = Queue.new
		write_loop
	end

	private

	def listen_loop
		Thread.new do
			loop do
				response = @sock.gets.strip!.delete("\x00")

				STDOUT.write "response: #{response}\n" # debug

				@response_lock.lock

				interprate_response(response)

				# key = (@queue_read.empty?) ? :unknown : @queue_read.pop.to_sym

				# if !(%W(death GAMEOVER error moving message).find { |e| response.include? e })
				# 	@response << { key => response }
				# elsif %W(moving message).find { |e| response.include? e }
				# 	@response << { move: response } if response.include? 'moving'
				# 	@response << { message: response } if response.include? 'message'
				# else
				# 	abort "Server Returned: '#{response}'"
				# end

				@response_lock.unlock
			end
		end
	end

	def write_loop
		Thread.new do
			loop do
				loop do
					break if @queue_read.size < 10 && @queue_write.size > 0
				end
				msg = @queue_write.pop
				@sock.puts msg + "\n"
				@queue_read << msg

				STDOUT.write "sent: #{msg}\n"
			end
		end
	end

	def interprate_response(response)
		# binding.pry if response == 'ko'
		if response.include?('{')
			key = (@queue_read.empty?) ? :unknown : @queue_read.pop.to_sym
			if (response.count(',') == 6)
				# @missing << key if key != :inventory
				@response << { inventory: response }
			else
				# @missing << key if key != :see
				@response << { see: response }
			end
		elsif %W(ok ko).include? response
			key = (@queue_read.empty?) ? :unknown : @queue_read.pop.to_sym
			if %W(advance right left fork).include? key.to_s && response == 'ko'
				# @missing << key
				# @response << { key => 'ok' }
			else
				@response << { key => response }
			end
		elsif response.to_i.to_s == response
			key = (@queue_read.empty?) ? :unknown : @queue_read.pop.to_sym
			# @missing << key if key != :connect_nbr || key != :pos
			@response << { key => response }
		elsif %W(moving message).find { |e| response.include? e }
			if response.include? 'moving'
				@response << { move: response } if response.include? 'moving'
			else
				@response << { message: response } if response.include? 'message'
			end
		elsif %W(error).include? response
			key = (@queue_read.empty?) ? :unknown : @queue_read.pop.to_sym
			@response << { key => response }
		elsif %W(death GAMEOVER).include? response
			abort "Server Returned: '#{response}'"
		elsif response.to_i
			key = (@queue_read.empty?) ? :unknown : @queue_read.pop.to_sym
			@response << { key => response }
		end
	end
end