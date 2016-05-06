
#
# Defines Part
#
CROSS ?=
CC := $(CROSS)gcc
CFLAGS := -ggdb3 -Wall -O0
LDFLAGS := -lpthread -lm

TARGET_SERVER := vaois_server
TARGET_CLIENT := vaois_client

.PHONY: all clean distclean

#
# Routines Part
#
all: $(TARGET_SERVER) $(TARGET_CLIENT)

$(TARGET_SERVER): server.o
	$(CC) $(LDFLAGS) $< -o $@

$(TARGET_CLIENT): client.o
	$(CC) $(LDFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#
# Cleanup Part
#
clean:
	rm -Rf *.o

distclean: clean
	rm -Rf $(TARGET_SERVER) $(TARGET_CLIENT)


