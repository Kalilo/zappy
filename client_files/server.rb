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
		
		@queue_read << 'welcome'
		@queue_read << 'connect_nbr'
		@queue_read << 'pos'

		@@verbose = verbose unless verbose.nil?

		listen_loop
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
		@sock.puts request.to_s + "\n"

		@queue_read << request
	end

	# should only be used for debug messages
	def response_to(msg)
		puts "in Server::response_to(#{msg})" if @@verbose

		@sock.puts msg
		@sock.gets.strip!.delete("\x00")
	end

	def	get_direct
		puts "in Server::get_direct" if @@verbose

		begin
			response = gets
		end while response.nil?
		response
	end

	private

	def listen_loop
		Thread.new do
			loop do
				response = @sock.gets.strip!.delete("\x00")

				if !(%W(death GAMEOVER error moving message).find { |e| response.include? e })
					@response << { @queue_read.pop.to_sym => response }
				elsif %W(moving message).find { |e| response.include? e }
					@response << { move: response } if response.include? 'moving'
					@response << { message: response } if response.include? 'message'
				else
					abort "Server Returned: '#{response}'"
				end
			end
		end
	end
end