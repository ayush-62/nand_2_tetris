SRCDIR   := src
BUILDDIR := build
INCDIR   := inc

CC  := gcc
CPP := g++
AS := as 
LD := gcc
OBJDUMP := objdump

ifeq ($(SHELL),cmd.exe)
MD := mkdir.exe -p
RM := rm.exe -rf
else
MD := mkdir -p
RM := rm -rf
endif

APP := build/hack

INC := \
	-I$(INCDIR)

SRC := \
	$(SRCDIR)/assembler.cpp\
	$(SRCDIR)/compiler.cpp \
	$(SRCDIR)/main.cpp\
	$(SRCDIR)/vm_translator.cpp\

OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))


$(APP): clean create_build_dir $(OBJS)
	@$(CPP) -o $(APP) $(OBJS) $(INC)

$(OBJS):$(BUILDDIR)/%.o:$(SRCDIR)/%.cpp | $(BUILDDIR)
	@$(CPP) -c $< -o $@ $(INC)
create_build_dir:
	@$(MD) $(BUILDDIR)
clean:
	@$(RM) $(BUILDDIR)

.PHONY : $(APP) clean
