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

  @server = Server.new @options[:host], @options[:port], @options[:team]
rescue
  abort "Fatal error initializing the server"
end

abort "failed to recieve welcome message from server" unless @server.get_direct

abort "no connections avaliable" if @server.get_direct.to_i == -1

# Initialize the Player
require './player.rb'

size = @server.get_direct.split(' ')

@player = Player.new(size[0], size[1])

# @player.see @server.response_to 'see'

require './ai.rb'

@ai = AI.new @player, @server, @options[:verbose]

binding.pry
