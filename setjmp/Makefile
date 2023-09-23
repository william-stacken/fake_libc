OUT         := libsetjmp.so
SRC         := errno_internal.c  __restore.S           setjmp.h  sigaction.cpp  sigblock.c     sigemptyset.cpp  siginterrupt.c   signal.cpp    sigpending.cpp   sigqueue.cpp  sigsuspend.cpp    sigwait.cpp \
assert.cpp         ___rt_sigqueueinfo.S  setjmp.S  sigaddset.cpp  sigdelset.cpp  sigfillset.cpp   sigismember.cpp  signalfd.cpp  sigprocmask.cpp  sigsetmask.c  sigtimedwait.cpp  sigwaitinfo.cpp

OBJ         := $(patsubst %.c, %.o, $(filter %.c, $(SRC)))
OBJ         += $(patsubst %.cpp, %.o, $(filter %.cpp, $(SRC)))
DEP         := $(OBJ:.o=.d)

CFLAGS      := -Wall
CXXFLAGS    := -Wall -Werror
LDFLAGS     := -nostdlib -shared -Wl,--hash-style=sysv
LDLIBS      := 

DEBUG       ?= 0
VERBOSE     ?= 0

ifeq ($(DEBUG),1)
	CFLAGS += -O0 -g -ggdb -DDEBUG=1
	CXXFLAGS += -O0 -g -ggdb -DDEBUG=1
	LDFLAGS +=
endif

ifeq ($(VERBOSE),1)
	MSG := @true
	CMD :=
else
	MSG := @echo
	CMD := @
endif

.PHONY: release clean

release: CFLAGS += -O3
release: CXXFLAGS += -O3
release: $(OUT)

clean:
	$(MSG) -e "\tCLEAN\t"
	$(CMD)$(RM) $(OBJ) $(DEP) $(OUT)

$(OUT): $(OBJ)
	$(MSG) -e "\tLINK\t$@"
	$(CMD)$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	$(CMD)strip $(OUT)

%.o: %.c %.d
	$(MSG) -e "\tCC\t$@"
	$(CMD)$(CC) $(CFLAGS) -c $< -o $@

%.d: %.c
	$(MSG) -e "\tDEP\t$@"
	$(CMD)$(CC) $(CFLAGS) -MF $@ -MM $<

%.o: %.cpp %.d
	$(MSG) -e "\tCXX\t$@"
	$(CMD)$(CXX) $(CXXFLAGS) -c $< -o $@

%.d: %.cpp
	$(MSG) -e "\tDEP\t$@"
	$(CMD)$(CXX) $(CXXFLAGS) -MF $@ -MM $<

ifneq ($(MAKECMDGOALS),clean)
-include $(DEP)
endif

