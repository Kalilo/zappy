# This class is to control communications with the server
class Server
	def initilize host, port, team
		@host = host
		@port = port.to_i rescue abort 'invalid port number'
		abort 'invalid port number' if @port < 1000 || port > 65000
		@team = team
	end
end