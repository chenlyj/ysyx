all:
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	verilator --cc --exe -Wall --build csrc/main.cpp vsrc/top.v --trace
	make -C obj_dir/ -f obj_dir/Vtop.mk Vtop
	./vsrc/obj_dir/Vtop

include ../Makefile
