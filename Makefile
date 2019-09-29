# Project description
EXE=test.exe
OBJS=test.obj iadf.obj
LIBS=
# Project options
EXETYPE=NT
SUBSYSTEM=CONSOLE
# Command lines
CC=C:\DM\BIN\dmc.exe
CFLAGS=-w-
LINK=C:\DM\BIN\dmc.exe
LINKOPT=exet:$(EXETYPE)/su:$(SUBSYSTEM)
COMPILE.c=$(CC) $(CFLAGS) -c
LINK.exe=$(LINK)
# Explicit rules
all: $(EXE)
$(EXE): $(OBJS)
	$(LINK.exe) $(OBJS) $(LIBS) -L/$(LINKOPT)
clean:
	del *.exe
	del *.obj
	del *.map
# Explicit rules
.c.obj:
	$(COMPILE.c) $< -o $@
