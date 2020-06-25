###############################################################################
##    Makefile-gcc
##
##    This file is part of Object Script Module
##    Copyright (C) 2004 Tom N Harris <telliamed@whoopdedo.cjb.net>
##
##    Permission is hereby granted, free of charge, to any person obtaining
##    a copy of this software and associated documentation files (the 
##    "Software"), to deal in the Software without restriction, including 
##    without limitation the rights to use, copy, modify, merge, publish, 
##    distribute, sublicense, and/or sell copies of the Software, and to 
##    permit persons to whom the Software is furnished to do so.
##    
##    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
##    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
##    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-
##    INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS 
##    BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN 
##    AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
##    IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
##    THE SOFTWARE.
##
###############################################################################

.PHONY: all install run clean

.SUFFIXES:
.SUFFIXES: .o .cpp .rc 
.PRECIOUS: %.o

srcdir = .

INSTALLDIR = e:\\dev\\T2FM\\test_delve
RUNDIR = e:\\dev\\TMA1.27
RUN = $(RUNDIR)\\Dromed.exe

GAME = 2

LGDIR = liblg

CP = cp
CC = gcc
CXX = g++
AR = ar
DLLWRAP = dllwrap

DEFINES = -DWINVER=0x0500 -D_WIN32_WINNT=0x0500 -DWIN32_LEAN_AND_MEAN -D_DARKGAME=$(GAME)

ifdef DEBUG
DEFINES := $(DEFINES) -D_DEBUG 
CCDEBUG = -g -O0
CXXDEBUG = -g -O0
LDDEBUG = -g
LGLIB = lg-d
else
DEFINES := $(DEFINES) -DNDEBUG
CCDEBUG = -O3 
CXXDEBUG = -O3 
LDDEBUG =
LGLIB = lg
endif

ARFLAGS = rc
LDFLAGS = -mwindows -mdll -Wl,--enable-auto-image-base 
LIBDIRS = -L$(LGDIR) 
LIBS = -l$(LGLIB) -luuid -lstdc++
INCLUDES = -I$(LGDIR)
# If you care for this... # -Wno-unused-variable 
# A lot of the callbacks have unused parameters, so I turn that off.
CFLAGS = -W -Wall -Wno-unused-parameter \
		-Wno-unused-const-variable \
		-masm=att \
		-fno-pcc-struct-return -mms-bitfields
CXXFLAGS = -W -Wall -Wno-unused-parameter \
		-std=c++11 -masm=att \
		-fno-pcc-struct-return -mms-bitfields
DLLFLAGS =  --target i386-mingw32

all: delve.osm

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(CCDEBUG) $(DEFINES) $(INCLUDES) -o $@ -c $<

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) $(CXXDEBUG) $(DEFINES) $(INCLUDES) -o $@ -c $<

delve.osm: delve.o guids.o $(LGDIR)/lib$(LGLIB).a
	$(DLLWRAP) $(DLLFLAGS) --def script.def -o $@ $< guids.o $(LDFLAGS) $(LDDEBUG) $(LIBDIRS) $(LIBS)

%.osm: %.o ScriptModule.o Script.o $(LGDIR)/lib$(LGLIB).a
	$(DLLWRAP) $(DLLFLAGS) --def script.def -o $@ $< ScriptModule.o Script.o $(LDFLAGS) $(LDDEBUG) $(LIBDIRS) $(LIBS)

$(LGDIR)/lib$(LGLIB).a:
	$(MAKE) -C $(LGDIR)

clean:
	$(RM) *.o *.osm
	$(MAKE) -C $(LGDIR) clean

install: delve.osm
	$(CP) delve.osm "$(INSTALLDIR)" && echo Installed.

run: install
	cd "$(RUNDIR)" && "$(RUN)" -fm=test_delve
