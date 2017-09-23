#!/usr/bin/ruby

# debug
require 'pry'

require 'socket'

# Run the argument parser
begin
  require './client_files/parse_args.rb'
rescue
  abort "Error parsing args"
end

# Initialize the Server
begin
  require './client_files/server.rb'

  @server = Server.new(@options[:host], @options[:port], @options[:team])
rescue
  abort "Fatal error initializing the server"
end

abort "failed to recieve welcome message from server" unless (@server.get_direct)[:welcome] == 'WELCOME'

abort "no connections avaliable" if (@server.get_direct)[:connect_nbr].to_i < 0

# pid = spawn("ruby #{$PROGRAM_NAME} -n #{@player.team} -p #{@server.port}")
# Process.detach(pid)

# Initialize the Player
require './client_files/player.rb'
size = (@server.get_direct)[:pos].split(' ')

@player = Player.new(size[0], size[1], @options[:verbose])

@player.team = @options[:team]

# puts "timing ~= #{@server.get_approximate_timing}"

@server.activate_write_loop

require './client_files/ai.rb'

@ai = AI.new @player, @server, @options[:verbose]

@ai.run

# binding.pry
