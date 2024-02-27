CC=gcc
CFLAGS=-Wall -Wextra -std=c11
LDFLAGS=

SRCDIR=.
OBJDIR=obj

SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
DEPS=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.d,$(SOURCES))

EXECUTABLE=myprogram

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)