cc = gcc
INCS = -I./include
srcDir = src
objDir = bin
program = build/app

src = $(wildcard $(srcDir)/*.c)
obj = $(patsubst $(srcDir)/%.c, $(objDir)/%.o, $(src))

all: $(program)

$(objDir)/%.o: $(srcDir)/%.c
	@$(cc) $(INCS) -c $< -o $@

$(program): $(obj)
	@$(cc) $^ -o $@

.PHONY: clean
clean:
	@rm -f $(objDir)/*.o
	@rm -f $(program)
