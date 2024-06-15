##
# chu lisp
#
# @file
# @version 0.2

CXXFLAGS ?= -g -Wall -Wextra -Werror

step0_repl: src/step0_repl.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

step1_read_print: src/step1_read_print.cpp src/reader.cpp src/printer.cpp src/types.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
# end
