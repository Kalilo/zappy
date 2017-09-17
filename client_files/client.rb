require 'socket'

# Run the argument parser
require './parse_args.rb'

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