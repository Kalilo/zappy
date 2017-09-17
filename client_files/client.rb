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

abort "failed to recieve welcome message from server" unless @server.get
