objects = familia novela questao04 haha uhm

gtk_objects = questao03 #test

CC = gcc

CFLAGS = -ggdb -std=c99

.PHONY : all
.PHONY : run
.PHONY : clean

all: $(objects) $(gtk_objects)

clean:
	rm -f $(objects) $(gtk_objects)

$(gtk_objects): % : %.c
	$(CC) $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0` $^ -o $@

$(objects): % : %.c
	$(CC) $(CFLAGS) $^ -o $@

