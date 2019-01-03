## Makefile ##

#
# notes:
#
#

CXX           = g++
CXXDEPEND     = -MM
CXXFLAGS      = -g -Wall -fPIC -O0

UNAME := $(shell uname)

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --evelibs) 
ROOTGLIBS    := $(shell root-config --glibs)

CXXFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS) $(SYSLIBS)
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)

INCDIR = ./include
SRCDIR = ./src
TMPDIR = ./tmp
LIBDIR = ./lib
BINDIR = ./bin

INCLUDES = -I$(INCDIR)

.PHONY: 
	all

all: clean rootcint shared

ROOTSO := $(LIBDIR)/libEventDisplay.so

ROOTDICT := $(SRCDIR)/EvtDisplayRootDict.cc

ROOTSRC := $(SRCDIR)/EventDisplay3D.cc $(INCDIR)/EventDisplay3D.hh $(SRCDIR)/EventDisplay2D.cc $(INCDIR)/EventDisplay2D.hh $(INCDIR)/EventDisplayLinkDef.hh

ROOTOBJS := $(TMPDIR)/EventDisplay3D.o $(TMPDIR)/EventDisplay2D.o $(TMPDIR)/EvtDisplayRootDict.o

$(TMPDIR)/%.o : $(SRCDIR)/%.cc
	@echo "<**Compiling $@**>"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(TMPDIR)/%.d: $(SRCDIR)/%.cc
	@echo "<**Depend $@**>"
	set -e; $(CXX) $(CXXDEPEND) $(CXXFLAGS) $(INCLUDES) $< \
	| sed 's!$*\.o!& $@!' >$@;\
	[ -s $@ ] || rm -f $@

$(ROOTDICT) : $(ROOTSRC)

rootcint : $(ROOTSRC)
	@echo "<**Rootcint**>"
	rootcint -f $(ROOTDICT) -c -I$(INCDIR) -I$(shell root-config --incdir) EventDisplay3D.hh EventDisplay2D.hh
shared: $(ROOTDICT) $(ROOTSRC) $(ROOTOBJS)
	@echo "<**Shared**>"
ifeq ($(UNAME), Darwin) 
	g++ -dynamiclib $(ROOTLIBS) $(ROOTGLIBS) -O $(ROOTOBJS) -o $(ROOTSO)
endif
ifeq ($(UNAME), Linux) 
	g++ -shared $(ROOTLIBS) $(ROOTGLIBS) -O $(ROOTOBJS) -o $(ROOTSO)
endif

clean :
	@echo "<**Clean**>"
	rm -f $(SRCDIR)/*~ $(INCDIR)/*~ $(TMPDIR)/*.o $(TMPDIR)/*.d $(TMPDIR)/*.a $(LIBDIR)/*.so $(SRCDIR)/EvtDisplayRootDict.*

DEPS = $(ROOTOBJS:$(TMPDIR)/%.o=$(TMPDIR)/%.d)

ifeq ($(MAKECMDGOALS),all)
 include $(DEPS)
endif

ifeq ($(MAKECMDGOALS),shared)
 include $(DEPS)
endif
