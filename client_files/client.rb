require 'socket'

# Run the argument parser
begin
  require './parse_args.rb'
rescue
  abort "Error parsing args"
end

require './server.rb'

@server = Server.new @options[:host], @options[:port], @options[:team]

# # Set defaults
# @port ||= 4000
# @host ||= 'localhost'
# @team ||= "Team00"

# sock = TCPSocket.new @host, @port.to_i rescue abort "failed to connect to #{@host} on port #{@port}"
# # sock.puts @team

# # while line = sock.gets # Read lines from socket
# #   puts line         # and print them
# # end

# puts "end"
# sock.close