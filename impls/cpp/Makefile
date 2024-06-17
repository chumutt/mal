##
# chu lisp
#
# @file
# @version 0.3
CXXFLAGS ?= -std=c++17 -g -Wall -Wextra -Werror

build: step0_repl step1_read_print

clean: rm -f step0_repl step1_read_print # step2_eval step3_env step4_if_fn_do

step0_repl: src/step0_repl.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

step1_read_print: src/step1_read_print.cpp src/reader.cpp src/printer.cpp src/types.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< src/reader.cpp src/printer.cpp src/types.cpp
# end
