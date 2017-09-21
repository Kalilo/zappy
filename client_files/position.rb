# This class is to handle player positions

class Position
	attr_accessor :x, :y, :dir

	@@width ||= 100
	@@height ||= 100

	@@verbose ||= nil

	def initialize(x, y, dir, verbose = nil)
		@x, @y, @dir = x, y, dir

		@@verbose = verbose unless verbose.nil?
	end

	def move direction
		puts "in Player::direction" if @@verbose
		case direction
			when :north
				@y -= 1
			when :east
				@x += 1
			when :south
				@y += 1
			when :west
				@x -= 1
			else
				@dir = :north
				@y -= 1
		end
	end

	def move_to(x, y)
		puts "in Player::move_to(#{x}, #{y})" if @@verbose
		@x, @y = x, y
	end

	def self.set_width(width)
		puts "in Player::set_width(#{width})" if @@verbose
		@@width = width
	end

	def self.set_height(height)
		puts "in Player::set_height(#{height})" if @@verbose
		@@height = height
	end

	def diff pos
		puts "in Player::diff(#{pos})" if @@verbose

		throw 'Can only run diff on Positions' unless pos.class == Position

		y_diff = (pos.y - @y).abs
		y_diff = (@@height - y_diff).abs if (@@height - y_diff).abs < y_diff

		x_diff = (pos.x - @x).abs
		x_diff = (@@width - x_diff).abs if (@@width - x_diff).abs < x_diff

		y_diff + x_diff
	end

	def right
		puts "in Player::right" if @@verbose
		turn_right
		advance
	end

	def left
		puts "in Player::left" if @@verbose
		turn_left
		advance
	end

	def turn_right
		puts "in Player::turn_right" if @@verbose
		case @dir
			when :north
				@dir = :east
			when :east
				@dir = :south
			when :south
				@dir = :west
			when :west
				@dir = :north
			else
				@dir = :north
		end
	end

	def turn_left
		puts "in Player::turn_left" if @@verbose
		case @dir
			when :north
				@dir = :west
			when :east
				@dir = :north
			when :south
				@dir = :east
			when :west
				@dir = :south
			else
				@dir = :north
		end
	end

	def set_opposite_dir
		puts "in Player::turn_left" if @@verbose
		case @dir
			when :north
				@dir = :south
			when :east
				@dir = :west
			when :south
				@dir = :north
			when :west
				@dir = :east
			else
				@dir = :south
		end
	end

	def advance
		puts "in Player::advance" if @@verbose
		case @dir
			when :north
				@y = wrap_adjust_y(-1)
			when :east
				@x = wrap_adjust_x(1)
			when :south
				@y = wrap_adjust_y(1)
			when :west
				@x = wrap_adjust_x(-1)
			else
				@dir = :north
				@y = wrap_adjust_y(-1)
		end
	end

	def advance_pos
		puts "in Player::advance_pos" if @@verbose

		y_new = @y
		x_new = @x
		case @dir
			when :north
				y_new = wrap_adjust_y(-1)
			when :east
				x_new = wrap_adjust_x(1)
			when :south
				y_new = wrap_adjust_y(1)
			when :west
				x_new = wrap_adjust_x(-1)
			else
				@dir = :north
				y_new = wrap_adjust_y(-1)
		end
		Position.new(x_new, y_new, :north)
	end

	def left_pos
		puts "in Player::left_pos" if @@verbose

		case @dir
			when :north
				Position.new(wrap_adjust_x(-1), @y, :west)
			when :east
				Position.new(@x, wrap_adjust_y(-1), :north)
			when :south
				Position.new(wrap_adjust_x(1), @y, :east)
			when :west
				Position.new(@x, wrap_adjust_y(1), :south)
			else
				Position.new(wrap_adjust_x(-1), @y, :west)
		end
	end

	def right_pos
		puts "in Player::right_pos" if @@verbose

		case @dir
			when :north
				Position.new(wrap_adjust_x(1), @y, :east)
			when :east
				Position.new(@x, wrap_adjust_y(1), :south)
			when :south
				Position.new(wrap_adjust_x(-1), @y, :west)
			when :west
				Position.new(@x, wrap_adjust_y(-1), :north)
			else
				Position.new(wrap_adjust_x(1), @y, :east)
		end
	end

	def get_opposite_dir
		puts "in Player::get_opposite_dir" if @@verbose

		case @dir
			when :north
				:south
			when :east
				:west
			when :south
				:north
			when :west
				:east
			else
				:south
		end
	end

	def get_left_dir
		puts "in Player::get_left_dir" if @@verbose

		case @dir
			when :north
				:west
			when :east
				:north
			when :south
				:east
			when :west
				:south
			else
				:north
		end
	end

	def get_right_dir
		puts "in Player::get_right_dir" if @@verbose

		case @dir
			when :north
				:east
			when :east
				:south
			when :south
				:west
			when :west
				:north
			else
				:north
		end
	end

	private

	def wrap_adjust_x(diff)
		puts "in Player::wrap_adjust_x(#{diff})" if @@verbose

		x = @x
		x += diff
		x %= @@width
	end

	def wrap_adjust_y(diff)
		puts "in Player::wrap_adjust_y(#{diff})" if @@verbose

		y = @y
		y += diff
		y %= @@height
	end
end