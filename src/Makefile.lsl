# File: Makefile.lsl

# Purpose: Makefile for Linux + SVGA library

SRCS = \
  z-util.c z-virt.c z-form.c z-rand.c z-term.c \
  variable.c tables.c util.c cave.c \
  object1.c object2.c monster1.c monster2.c \
  xtra1.c xtra2.c spells1.c spells2.c \
  melee1.c melee2.c save.c files.c \
  cmd1.c cmd2.c cmd3.c cmd4.c cmd5.c cmd6.c \
  store.c birth.c load.c \
  wizard1.c wizard2.c obj-info.c \
  generate.c dungeon.c init1.c init2.c randart.c \
  main-lsl.c main.c

LUAOBJS = \
  lua/lapi.o lua/ldebug.o lua/lmem.o lua/lstrlib.o lua/lvm.o \
  lua/lauxlib.o lua/ldo.o lua/lobject.o lua/ltable.o lua/lzio.o \
  lua/lbaselib.o lua/lfunc.o lua/lparser.o lua/lcode.o lua/lgc.o \
  lua/lopcodes.o lua/lstate.o lua/ltm.o  lua/ldblib.o lua/llex.o \
  lua/lstring.o lua/ldump.o lua/lundump.o lua/ltablib.o \
  lua/tolua_map.o lua/tolua_is.o lua/tolua_to.o lua/tolua_push.o \
  lua/tolua_event.o

TOLUAOBJS = \
  lua/tolua.o lua/toluabind.o lua/liolib.o \
  $(LUAOBJS)

OBJS = \
  z-util.o z-virt.o z-form.o z-rand.o z-term.o \
  variable.o tables.o util.o cave.o \
  object1.o object2.o monster1.o monster2.o \
  xtra1.o xtra2.o spells1.o spells2.o \
  melee1.o melee2.o save.o files.o \
  cmd1.o cmd2.o cmd3.o cmd4.o cmd5.o cmd6.o \
  store.o birth.o load.o \
  wizard1.o wizard2.o obj-info.o \
  generate.o dungeon.o init1.o init2.o randart.o \
  main-lsl.o main.o \
  script.o use-obj.o x-spell.o \
  l-monst.o l-object.o l-player.o l-random.o l-ui.o \
  l-misc.o l-spell.o \
  $(LUAOBJS)


CC = gcc

CFLAGS = -O2 -fno-strength-reduce -Wall -D"USE_LSL"

LIBS = -lz -lvgagl -lvga



# 
# Build the "Angband" program 
# 
angband: $(OBJS) 
	$(CC) $(CFLAGS) -o angband $(OBJS) $(LDFLAGS) $(LIBS) 


#
# install Angband
#
install: angband
	cp angband ..

#
# Clean up old junk
#
clean:
	-rm -f *.o angband
	-rm -f ./lua/*.o ./lua/tolua


#
# Generate dependencies automatically
#
depend:
	makedepend -D__MAKEDEPEND__ $(SRCS)

#
# Lua stuff
#

lua/tolua: $(TOLUAOBJS)
	$(CC) -o lua/tolua $(TOLUAOBJS) $(LDFLAGS) $(LIBS)


#
# Hack -- some file dependencies
#
HDRS = \
  h-basic.h \
  h-define.h h-type.h h-system.h h-config.h

INCS = \
  angband.h \
  config.h defines.h types.h externs.h \
  z-term.h z-rand.h z-util.h z-virt.h z-form.h $(HDRS)


birth.o: birth.c $(INCS)
cave.o: cave.c $(INCS)
cmd1.o: cmd1.c $(INCS)
cmd2.o: cmd2.c $(INCS)
cmd3.o: cmd3.c $(INCS)
cmd4.o: cmd4.c $(INCS)
cmd5.o: cmd5.c $(INCS) script.h
cmd6.o: cmd6.c $(INCS) script.h
dungeon.o: dungeon.c $(INCS)
files.o: files.c $(INCS)
generate.o: generate.c $(INCS)
init1.o: init1.c $(INCS) init.h
init2.o: init2.c $(INCS) init.h script.h
l-misc.o: l-misc.c $(INCS) lua/tolua.h
l-monst.o: l-monst.c $(INCS) lua/tolua.h
l-object.o: l-object.c $(INCS) lua/tolua.h
l-player.o: l-player.c $(INCS) lua/tolua.h
l-random.o: l-random.c $(INCS) lua/tolua.h
l-spell.o: l-spell.c $(INCS) lua/tolua.h
l-ui.o: l-ui.c $(INCS) lua/tolua.h
randart.o: randart.c $(INCS) init.h
load.o: load.c $(INCS)
main-cap.o: main-cap.c $(INCS) main.h
main-gcu.o: main-gcu.c $(INCS) main.h
main-lsl.o: main-lsl.c $(INCS) main.h
main-x11.o: main-x11.c $(INCS) main.h
main-xaw.o: main-xaw.c $(INCS) main.h
main.o: main.c $(INCS) main.h
melee1.o: melee1.c $(INCS)
melee2.o: melee2.c $(INCS)
monster1.o: monster1.c $(INCS)
monster2.o: monster2.c $(INCS)
obj-info.o: obj-info.c $(INCS)
object1.o: object1.c $(INCS)
object2.o: object2.c $(INCS)
save.o: save.c $(INCS)
script.o: script.c $(INCS) script.h \
		lua/lauxlib.h lua/lua.h lua/lualib.h lua/tolua.h
spells1.o: spells1.c $(INCS)
spells2.o: spells2.c $(INCS)
store.o: store.c $(INCS)
tables.o: tables.c $(INCS)
use-obj.o: use-obj.c $(INCS)
util.o: util.c $(INCS)
variable.o: variable.c $(INCS)
wizard1.o: wizard1.c $(INCS)
wizard2.o: wizard2.c $(INCS) script.h
x-spell.o: x-spell.c $(INCS)
xtra1.o: xtra1.c $(INCS) script.h
xtra2.o: xtra2.c $(INCS)
z-form.o: z-form.c $(HDRS) z-form.h z-util.h z-virt.h
z-rand.o: z-rand.c $(HDRS) z-rand.h
z-term.o: z-term.c $(HDRS) z-term.h z-virt.h
z-util.o: z-util.c $(HDRS) z-util.h
z-virt.o: z-virt.c $(HDRS) z-virt.h z-util.h

#
# Build wrappers
#

l-monst.c: lua/tolua l-monst.pkg
	lua/tolua -n monster -o l-monst.c l-monst.pkg

l-object.c: lua/tolua l-object.pkg
	lua/tolua -n object -o l-object.c l-object.pkg

l-player.c: lua/tolua l-player.pkg
	lua/tolua -n player -o l-player.c l-player.pkg

l-random.c: lua/tolua l-random.pkg
	lua/tolua -n random -o l-random.c l-random.pkg

l-ui.c: lua/tolua l-ui.pkg
	lua/tolua -n ui -o l-ui.c l-ui.pkg

l-misc.c: lua/tolua l-misc.pkg
	lua/tolua -n misc -o l-misc.c l-misc.pkg

l-spell.c: lua/tolua l-spell.pkg
	lua/tolua -n spell -o l-spell.c l-spell.pkg
