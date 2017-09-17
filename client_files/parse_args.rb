require 'optparse'

@options = {}
OptionParser.new do |opts|
  opts.banner = "Usage: #{0} -n <team> -p <port> [-h hostname]"

  opts.on('-v', '--[no-]verbose', 'Run verbosely') do |v|
    @options[:verbose] = v
  end

  opts.on('-h', '--help', 'Prints this help') do
	puts opts
	exit
  end

  opts.on('-nTEAM', '--name=TEAM', 'Set the team name') do |n|
	@options[:team] = n
  end

  opts.on('-pPORT', '--port=PORT', 'Set the port number') do |p|
	@options[:port] = p
  end

  opts.on()
end.parse!

abort 'Please provide team name' unless @options[:team]
abort 'Please provide port number' unless @options[:port]

p @options
