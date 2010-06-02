objects = familia novela questao04

gtk_objects = questao03

CC = clang

.PHONY : all
.PHONY : run
.PHONY : clean

all: $(objects) $(gtk_objects)

clean:
	rm -f $(objects)

$(gtk_objects): % : %.c
	$(CC) `pkg-config --cflags --libs gtk+-2.0` $^ -o $@

$(objects): % : %.c
	$(CC) $^ -o $@

