#!/usr/bin/ruby

# debug
require 'pry'

require 'socket'

# Run the argument parser
begin
  require './parse_args.rb'
rescue
  abort "Error parsing args"
end

# Initialize the Server
begin
  require './server.rb'

  @server = Server.new(@options[:host], @options[:port], @options[:team])
rescue
  abort "Fatal error initializing the server"
end

abort "failed to recieve welcome message from server" unless (@server.get_direct)[:welcome] == 'WELCOME'

abort "no connections avaliable" if (@server.get_direct)[:connect_nbr].to_i < 0

# Initialize the Player
require './player.rb'

size = (@server.get_direct)[:pos].split(' ')

@player = Player.new(size[0], size[1], @options[:verbose])

# @player.see @server.response_to 'see'

require './ai.rb'

@ai = AI.new @player, @server, @options[:verbose]

@ai.run

# binding.pry
