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

		@@verbose = verbose unless verbose.nil?
		@read_lock = Mutex.new
		@write_lock = Mutex.new
	end

	def gets
		puts "in Server::gets" if @@verbose

		@response.shift
	end

	def get(key_value)
		puts "in Server::get(#{value})" if @@verbose

		key_value = key_value.to_sym
		pos = @response.find_index { |e| e.keys.first == key_value }
		@response.delete_at(pos) unless pos.nil?
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
		abort "invalid request" unless request

		puts "in Server::run_request(#{request})" if @@verbose

		Thread.new do
			@write_lock.lock
			@sock.puts (request.to_s << "\n")
			@write_lock.unlock

			request.strip!
			@read_lock.lock

			begin
				response = @sock.gets.strip!.delete("\x00")

				if !(%W(death GAMEOVER error moving message).find { |e| response.include? e })
					# unless %W(right left advance).include? request
						@response << { request.to_sym => response }
						done = true
					# end
				elsif %W(moving message).find { |e| response.include? e }
					@response << { move: response } if response.include? 'moving'
					@response << { message: response } if response.include? 'message'
					done = false
				else
					abort response
				end
			end while !done

			@read_lock.unlock
		end
	end

	# should only be used for debug messages
	def response_to(msg)
		puts "in Server::response_to(#{msg})" if @@verbose

		@sock.puts msg
		@sock.gets.strip!.delete("\x00")
	end

	def	get_direct
		puts "in Server::get_direct" if @@verbose

		@sock.gets
	end
end