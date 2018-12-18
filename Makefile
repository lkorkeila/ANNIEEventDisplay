## Makefile ##

#
# notes:
#  LAPPD_INCDIR  points to LAPPD .hh files
#  LAPPD_LIBDIR  points to LAPPD .o files
#

CXX           = g++
CXXDEPEND     = -MM
CXXFLAGS      = -g -Wall -fPIC -O0
LD            = g++
LDFLAGS       = -g 

UNAME := $(shell uname)

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLDFLAGS  := $(shell root-config --ldflags)
ROOTLIBS     := $(shell root-config --evelibs) 
# $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)

CXXFLAGS     += $(ROOTCFLAGS)
LDFLAGS      += $(ROOTLDFLAGS)
LIBS          = $(ROOTLIBS) $(SYSLIBS)
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)

INCDIR = ./include
SRCDIR = ./src
TMPDIR = ./tmp
LIBDIR = ./lib
BINDIR = ./bin

INCLUDES = -I$(INCDIR)

EVTDISP_INCDIR = ./include
EVTDISP_LIBDIR = ./tmp

EVTDISP_INCLUDES = -I$(EVTDISP_INCDIR)
EVTDISP_LDFLAGS += -L$(EVTDISP_LIBDIR)
EVTDISP_LIBS += -lEVTDISP

.PHONY: 
	all

all: clean rootcint shared

ROOTSO := $(LIBDIR)/EventDisplay.so

ROOTDICT := $(SRCDIR)/EvtDisplayRootDict.cc

ROOTSRC := $(SRCDIR)/EventDisplay3D.cc $(INCDIR)/EventDisplay3D.hh $(SRCDIR)/EventDisplay2D.cc $(INCDIR)/EventDisplay2D.hh $(INCDIR)/EventDisplayLinkDef.hh

ROOTOBJS := $(TMPDIR)/EventDisplay3D.o $(TMPDIR)/EventDisplay2D.o $(TMPDIR)/EvtDisplayRootDict.o

$(TMPDIR)/%.o : $(SRCDIR)/%.cc
	@echo "<**Compiling $@**>"
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(EVTDISP_INCLUDES) -c $< -o $@

$(TMPDIR)/%.d: $(SRCDIR)/%.cc
	@echo "<**Depend $@**>"
	set -e; $(CXX) $(CXXDEPEND) $(CXXFLAGS) $(INCLUDES) $(EVTDISP_INCLUDES) $< \
	| sed 's!$*\.o!& $@!' >$@;\
	[ -s $@ ] || rm -f $@

$(ROOTDICT) : $(ROOTSRC)

rootcint : $(ROOTSRC)
	@echo "<**Rootcint**>"
	rootcint -f $(ROOTDICT) -c -I$(INCDIR) -I$(EVTDISP_INCDIR) -I$(shell root-config --incdir) EventDisplay3D.hh EventDisplay2D.hh
shared: $(ROOTDICT) $(ROOTSRC) $(ROOTOBJS)
	@echo "<**Shared**>"
ifeq ($(UNAME), Darwin) 
	g++ -dynamiclib $(ROOTLIBS) $(ROOTGLIBS) -O $(ROOTOBJS) -lMinuit -o $(ROOTSO)
endif
ifeq ($(UNAME), Linux) 
	g++ -shared $(ROOTLIBS) $(ROOTGLIBS) -O $(ROOTOBJS) -o $(ROOTSO)
endif

clean :
	@echo "<**Clean**>"
	rm -f $(SRCDIR)/*~ $(INCDIR)/*~ $(TMPDIR)/*.o $(TMPDIR)/*.d $(TMPDIR)/*.a $(LIBDIR)/*.so $(SRCDIR)/EvtDisplayRootDict.*

reco.o : reco.cc 
	@echo "making $@ from $<"
	@echo $(CXX) $(CXXFLAGS) $(INCLUDES) $(EVTDISP_INCLUDES) -c $< -o $@
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(EVTDISP_INCLUDES) -c $< -o $@

reco : reco.o $(ROOTSO)
	@echo "Making reco executable for WCSimAnalysis..."
	g++ -o reco $(CXXFLAGS) reco.o $(EVTDISP)/libWCSimRoot.so $(ROOTSO) $(ROOTLIBS) $(ROOTGLIBS) -lMinuit 

DEPS = $(ROOTOBJS:$(TMPDIR)/%.o=$(TMPDIR)/%.d)

ifeq ($(MAKECMDGOALS),all)
 include $(DEPS)
endif

ifeq ($(MAKECMDGOALS),shared)
 include $(DEPS)
endif
