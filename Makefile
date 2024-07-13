# -*- mode: makefile-mode; -*-
#
# Copyright 2023-2024 Angelo Rossi <angelo.rossi.homelab@gmail.com>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#     1. Redistributions of source code must retain the above copyright notice,
#        this list of conditions and the following disclaimer.
#
#     2. Redistributions in binary form must reproduce the above copyright
#        notice, this list of conditions and the following disclaimer in the
#        documentation and/or other materials provided with the distribution.
#
#     3. Neither the name of the copyright holder nor the names of its
#        contributors may be used to endorse or promote products derived from
#        this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

OS=${shell uname -s}
ifeq (${OS},OpenBSD)
	TOOLCHAIN=egcc
	CC=$(shell which egcc)
	CXX=$(shell which eg++)
	G95=$(shell which egfortran)
	LD=${CC}
else
	$(error "Unknown OS.")
endif

DEBUG=1
INCLUDES_PATH=./includes

CCFLAGS=-std=gnu99		\
	-I${INCLUDES_PATH}	\
        -c

G95FLAGS=-c

LDFLAGS=-lc		\
	-lm		\
	-lutil		\
	-lgfortran	\
	-z wxneeded

ifeq (${DEBUG},1)
	CCFLAGS+=-gdwarf-2
	G95FLAGS+=-gdwarf-2
	LDFLAGS+=-gdwarf-2
endif

all: ${TOOLCHAIN}
all: ${TOOLCHAIN}/alarm
all: ${TOOLCHAIN}/append-buf
all: ${TOOLCHAIN}/append-char
all: ${TOOLCHAIN}/append-line
all: ${TOOLCHAIN}/append2
all: ${TOOLCHAIN}/bg
all: ${TOOLCHAIN}/blocks
all: ${TOOLCHAIN}/client
all: ${TOOLCHAIN}/cputime
all: ${TOOLCHAIN}/difftime
all: ${TOOLCHAIN}/disklabel
all: ${TOOLCHAIN}/disklabel2
all: ${TOOLCHAIN}/ezshell
all: ${TOOLCHAIN}/factorial
all: ${TOOLCHAIN}/find-word
all: ${TOOLCHAIN}/fseekdemo
all: ${TOOLCHAIN}/fseekreadback
all: ${TOOLCHAIN}/getprocs
all: ${TOOLCHAIN}/group
all: ${TOOLCHAIN}/hostent
all: ${TOOLCHAIN}/inet-client
all: ${TOOLCHAIN}/inet-server
all: ${TOOLCHAIN}/inode
all: ${TOOLCHAIN}/irc-client
all: ${TOOLCHAIN}/listfiles
all: ${TOOLCHAIN}/ls
all: ${TOOLCHAIN}/mailer
all: ${TOOLCHAIN}/mqclient
all: ${TOOLCHAIN}/mqserver
#all: ${TOOLCHAIN}/mutex
all: ${TOOLCHAIN}/ondisk-inode
all: ${TOOLCHAIN}/ouch1
all: ${TOOLCHAIN}/ouch2
all: ${TOOLCHAIN}/pager
all: ${TOOLCHAIN}/passwd
all: ${TOOLCHAIN}/rusage
all: ${TOOLCHAIN}/select
all: ${TOOLCHAIN}/semcreate
all: ${TOOLCHAIN}/servent
all: ${TOOLCHAIN}/server
all: ${TOOLCHAIN}/setlim
#all: ${TOOLCHAIN}/setupjc
all: ${TOOLCHAIN}/shm-client
all: ${TOOLCHAIN}/shm-server
all: ${TOOLCHAIN}/sigaction
all: ${TOOLCHAIN}/sigblock
all: ${TOOLCHAIN}/sigstack
all: ${TOOLCHAIN}/snprintf
all: ${TOOLCHAIN}/sort
all: ${TOOLCHAIN}/speaker
all: ${TOOLCHAIN}/stopproc
all: ${TOOLCHAIN}/strerror
all: ${TOOLCHAIN}/strsignal
all: ${TOOLCHAIN}/superblock
all: ${TOOLCHAIN}/time
all: ${TOOLCHAIN}/timeout
all: ${TOOLCHAIN}/timezone
all: ${TOOLCHAIN}/utmp
all: ${TOOLCHAIN}/waitfor
all: ${TOOLCHAIN}/winsize
all: ${TOOLCHAIN}/wsmux

# FORTRAN vs C
all: ${TOOLCHAIN}/hello1
all: ${TOOLCHAIN}/hello2
all: ${TOOLCHAIN}/mean
all: ${TOOLCHAIN}/norm2
all: ${TOOLCHAIN}/fft
all: ${TOOLCHAIN}/ifft

# wscons
all: ${TOOLCHAIN}/wsdisplay
all: ${TOOLCHAIN}/wsdisplay2
all: ${TOOLCHAIN}/wsdisplay-colormap
all: ${TOOLCHAIN}/wskbd
all: ${TOOLCHAIN}/wskbd-leds
all: ${TOOLCHAIN}/wskbd-enc

${TOOLCHAIN}/%.o: %.c
	@if [ 'x${VERBOSE}' = x ]; then			\
		echo " [ CC ] ${<}";			\
	else						\
		echo ${CC} ${CCFLAGS} -o ${@} ${<};	\
	fi
	@${CC} ${CCFLAGS} -o ${@} ${<}

${TOOLCHAIN}/%.o: %.f90
	@if [ 'x${VERBOSE}' = x ]; then			\
		echo " [ G95 ] ${<}";			\
	else						\
		echo ${G95} ${G95FLAGS} ${<} -o ${@};	\
	fi
	@${G95} ${G95FLAGS} ${<} -o ${@}

${TOOLCHAIN}:
	@if [ 'x${VERBOSE}' = x ];		\
	then					\
		echo " [ MKDIR ] ${TOOLCHAIN}";	\
	else					\
		echo "mkdir -p ${TOOLCHAIN}";	\
	fi
	@mkdir -p ${TOOLCHAIN}

${TOOLCHAIN}/%:
	@if [ 'x${VERBOSE}' = x ]; then			\
		echo " [ LD ] ${@}";			\
	else						\
		echo ${LD} $(filter %.o %.a, ${^})	\
		           ${LDFLAGS}			\
			   -o ${@};			\
	fi
	@${LD} $(filter %.o %.a, ${^})		\
	       ${LDFLAGS}			\
	       -o ${@}

clean:
	@if [ 'x${VERBOSE}' = x ]; then				\
		echo " [ CLEAN ] ${<}";				\
	else							\
		echo "rm -rf ${TOOLCHAIN} ${wildcard *~} ${<}";	\
	fi
	@rm -rf ${TOOLCHAIN} ${wildcard *~} ${<}

${TOOLCHAIN}/alarm: ${TOOLCHAIN}/alarm.o
${TOOLCHAIN}/append-buf: ${TOOLCHAIN}/append-buf.o
${TOOLCHAIN}/append-char: ${TOOLCHAIN}/append-char.o
${TOOLCHAIN}/append-line: ${TOOLCHAIN}/append-line.o
${TOOLCHAIN}/append2: ${TOOLCHAIN}/append2.o
${TOOLCHAIN}/bg: ${TOOLCHAIN}/bg.o
${TOOLCHAIN}/blocks: ${TOOLCHAIN}/blocks.o
${TOOLCHAIN}/client: ${TOOLCHAIN}/client.o
${TOOLCHAIN}/cputime: ${TOOLCHAIN}/cputime.o
${TOOLCHAIN}/difftime: ${TOOLCHAIN}/difftime.o
${TOOLCHAIN}/disklabel: ${TOOLCHAIN}/disklabel.o
${TOOLCHAIN}/disklabel2: ${TOOLCHAIN}/disklabel2.o
${TOOLCHAIN}/ezshell: ${TOOLCHAIN}/ezshell.o
${TOOLCHAIN}/factorial: ${TOOLCHAIN}/factorial.o
${TOOLCHAIN}/find-word: ${TOOLCHAIN}/list.o
${TOOLCHAIN}/find-word: ${TOOLCHAIN}/find-word.o
${TOOLCHAIN}/fseekdemo: ${TOOLCHAIN}/fseekdemo.o
${TOOLCHAIN}/fseekreadback: ${TOOLCHAIN}/fseekreadback.o
${TOOLCHAIN}/getprocs: ${TOOLCHAIN}/getprocs.o
${TOOLCHAIN}/group: ${TOOLCHAIN}/group.o
${TOOLCHAIN}/hostent: ${TOOLCHAIN}/hostent.o
${TOOLCHAIN}/inet-client: ${TOOLCHAIN}/inet-client.o
${TOOLCHAIN}/inet-server: ${TOOLCHAIN}/inet-server.o
${TOOLCHAIN}/inode: ${TOOLCHAIN}/inode.o
${TOOLCHAIN}/irc-client: ${TOOLCHAIN}/irc-client.o
${TOOLCHAIN}/listfiles: ${TOOLCHAIN}/listfiles.o
${TOOLCHAIN}/ls: ${TOOLCHAIN}/ls.o
${TOOLCHAIN}/mailer: ${TOOLCHAIN}/mailer.o
${TOOLCHAIN}/mqclient: ${TOOLCHAIN}/mqclient.o
${TOOLCHAIN}/mqserver: ${TOOLCHAIN}/mqserver.o
#${TOOLCHAIN}/mutex: ${TOOLCHAIN}/mutex.o
${TOOLCHAIN}/ondisk-inode: ${TOOLCHAIN}/ondisk-inode.o
${TOOLCHAIN}/ouch1: ${TOOLCHAIN}/ouch1.o
${TOOLCHAIN}/ouch2: ${TOOLCHAIN}/ouch2.o
${TOOLCHAIN}/pager: ${TOOLCHAIN}/pager.o
${TOOLCHAIN}/passwd: ${TOOLCHAIN}/passwd.o
${TOOLCHAIN}/rusage: ${TOOLCHAIN}/rusage.o
${TOOLCHAIN}/select: ${TOOLCHAIN}/select.o
${TOOLCHAIN}/semcreate: ${TOOLCHAIN}/semcreate.o
${TOOLCHAIN}/servent: ${TOOLCHAIN}/servent.o
${TOOLCHAIN}/server: ${TOOLCHAIN}/server.o
${TOOLCHAIN}/setlim: ${TOOLCHAIN}/setlim.o
# ${TOOLCHAIN}/setupjc: ${TOOLCHAIN}/setupjc.o
${TOOLCHAIN}/shm-client: ${TOOLCHAIN}/shm-client.o
${TOOLCHAIN}/shm-server: ${TOOLCHAIN}/shm-server.o
${TOOLCHAIN}/sigaction: ${TOOLCHAIN}/sigaction.o
${TOOLCHAIN}/sigblock: ${TOOLCHAIN}/sigblock.o
${TOOLCHAIN}/sigstack: ${TOOLCHAIN}/sigstack.o
${TOOLCHAIN}/snprintf: ${TOOLCHAIN}/snprintf.o
${TOOLCHAIN}/sort: ${TOOLCHAIN}/sort.o
${TOOLCHAIN}/speaker: ${TOOLCHAIN}/speaker.o
${TOOLCHAIN}/stopproc: ${TOOLCHAIN}/stopproc.o
${TOOLCHAIN}/strerror: ${TOOLCHAIN}/strerror.o
${TOOLCHAIN}/strsignal: ${TOOLCHAIN}/strsignal.o
${TOOLCHAIN}/superblock: ${TOOLCHAIN}/superblock.o
${TOOLCHAIN}/time: ${TOOLCHAIN}/time.o
${TOOLCHAIN}/timeout: ${TOOLCHAIN}/timeout.o
${TOOLCHAIN}/timezone: ${TOOLCHAIN}/timezone.o
${TOOLCHAIN}/utmp: ${TOOLCHAIN}/utmp.o
${TOOLCHAIN}/waitfor: ${TOOLCHAIN}/waitfor.o
${TOOLCHAIN}/winsize: ${TOOLCHAIN}/winsize.o

# FORTRAN vs C
${TOOLCHAIN}/hello1: ${TOOLCHAIN}/hello1-for.o ${TOOLCHAIN}/hello1-c.o
${TOOLCHAIN}/hello2: ${TOOLCHAIN}/hello2-for.o ${TOOLCHAIN}/hello2-c.o
${TOOLCHAIN}/mean: ${TOOLCHAIN}/mean-for.o ${TOOLCHAIN}/mean-c.o
${TOOLCHAIN}/norm2: ${TOOLCHAIN}/norm2-for.o ${TOOLCHAIN}/norm2-c.o
${TOOLCHAIN}/fft: ${TOOLCHAIN}/fft-for.o ${TOOLCHAIN}/fft-c.o
${TOOLCHAIN}/ifft: ${TOOLCHAIN}/ifft-for.o ${TOOLCHAIN}/ifft-c.o

# wscons
${TOOLCHAIN}/wsdisplay: ${TOOLCHAIN}/wsdisplay.o
${TOOLCHAIN}/wsdisplay2: ${TOOLCHAIN}/wsdisplay2.o
${TOOLCHAIN}/wsdisplay-colormap: ${TOOLCHAIN}/wsdisplay-colormap.o
${TOOLCHAIN}/wskbd: ${TOOLCHAIN}/wskbd.o
${TOOLCHAIN}/wskbd-leds: ${TOOLCHAIN}/wskbd-leds.o
${TOOLCHAIN}/wskbd-enc: ${TOOLCHAIN}/wskbd-enc.o
${TOOLCHAIN}/wsmux: ${TOOLCHAIN}/wsmux.o

# End of Makefile.
