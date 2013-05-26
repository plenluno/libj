#!/usr/bin/ruby

require 'set'

prevLine = ""
numObjects = 0

callStack = []
callStacks = {}

objects = Set.new
staticObjects = Set.new

STDIN.each do |line|
  if /\[LIBJ TRACE\] enter: (\[.*\])/ =~ line
    callStack.push($1)
  end

  if /\[LIBJ TRACE\] exit:  (\[.*\])/ =~ line
    call = callStack.pop
    if call != $1
      raise "not enter: " + $1
    end
  end

  if /\[LIBJ DEBUG\] construct: 0x(\w*)/ =~ line
    if objects.include?($1)
      raise "already constructed: " + $1
    else
      objects.add($1)
      callStacks[$1] = callStack.inspect
    end
  end

  if /\[LIBJ DEBUG\] destruct:  0x(\w*)/ =~ line
    if !objects.include?($1)
      warn "not constructed: " + $1
    else
      objects.delete($1)
      callStacks.delete($1)
      if staticObjects.include?($1)
        staticObjects.delete($1)
      end
    end
  end

  if /\[LIBJ DEBUG\] static: (.*) 0x(\w*)/ =~ line
    if staticObjects.include?($2)
      raise "already constructed: " + $2
    else
      staticObjects.add($2)
    end
  end

  if /\[LIBJ DEBUG\] symbol: \[.*\] 0x(\w*)/ =~ line
    if staticObjects.include?($1)
      raise "already constructed: " + $1
    else
      staticObjects.add($1)
    end
  end

  if  /\[LIBJ DEBUG\] symbol: \[.*/ =~ prevLine and /^\] 0x(\w*)/ =~ line
    if staticObjects.include?($1)
      raise "already constructed: " + $1
    else
      staticObjects.add($1)
    end
  end

  if /\[LIBJ DEBUG\] remaining objects: (\d*)/ =~ line
    numObjects = $1
    break;
  end

  prevLine = line
end

if objects.size != numObjects.to_i
  raise "remaining objects: not " + numObjects + " but " + objects.size.to_s
end

leakedObjects = objects ^ staticObjects

leakedObjects.each do |addr|
  puts "leaked object: " + addr
  puts callStacks[addr]
  puts
end
