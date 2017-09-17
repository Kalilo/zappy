# This class is to control communications with the server
class Server
	attr_reader :host, :port, :team

	def initialize host, port, team
		@host = host
		@port = port.to_i rescue abort('invalid port number')
		abort 'invalid port number' if @port < 1000 || @port > 65000
		@team = team

		@sock = TCPSocket.new @host, @port rescue abort "failed to connect to #{@host} on port #{@port}"
		@sock.puts @team
	end

	def get
		@sock.gets
	end

	def puts msg
		sock.puts msg
	end
end