objects = familia novela questao04

CC = clang

.PHONY : all
.PHONY : run
.PHONY : clean

all: $(objects)

clean:
	rm -f $(objects)

$(objects): % : %.c
	$(CC) $^ -o $@

