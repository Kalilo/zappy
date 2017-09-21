# This class is to control communications with the server
class Server
	attr_reader :host, :port, :team

	def initialize host, port, team
		@host = host
		@host ||= 'localhost'
		@port = port.to_i rescue abort('invalid port number')
		abort 'invalid port number' if @port < 1000 || @port > 65000
		@team = team
		@response ||= []

		@sock = TCPSocket.new @host, @port rescue abort "failed to connect to #{@host} on port #{@port}"
		@sock.puts @team
	end

	def gets
		@response.shift
	end

	def puts(msg)
		run_request msg
	end

	def execute_list(list)
		list.each do |command|
			run_request command.to_s << "\n"
		end
	end

	def run_request(request)
		Thread.new do
			@sock.puts request.to_s
			begin
				response = @sock.gets.strip!.delete("\x00")
				if !(%W(death GAMEOVER moving message).find { |e| response.include? e })
					unless %W(right left advance).include? request
						@response << { request.to_sym => response }
						done = true
					end
				elsif %W(moving message).find { |e| response.include? e }
					@response << { move: response } if response.include? 'moving'
					@response << { message: response } if response.include? 'message'
					done = false
				else
					abort response
				end
			end while !done 
		end
	end

	# should only be used for debug messages
	def response_to(msg)
		@sock.puts msg
		@sock.gets.strip!.delete("\x00")
	end

	def	get_direct
		@sock.gets
	end
end