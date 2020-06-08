NAME =perenorm
CC = e:bcc.exe +$(NAME).CFG
TLIB = e:tlib.exe
TLINK = e:tlink.exe
LIBPATH = e:
INCLUDEPATH = e:


#               *Implicit Rules*

.cpp.obj:
  $(CC) -c $*

#               *List Macros*


EXE_dependencies =  \
 $(NAME).obj

#               *Explicit Rules*
$(NAME).exe: $(NAME).cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/L$(LIBPATH) @&&|
c0l.obj+
$(NAME).obj
$(NAME)
                # no map file
fp87.lib+
graphics.lib+
mathl.lib+
cl.lib
|

#               *Individual File Dependencies*
$(NAME).obj: $(NAME).cfg $(NAME).cpp

#               *Compiler Configuration File*
$(NAME).cfg: $(NAME).mak
  copy &&|
-f87
-ml
-I$(INCLUDEPATH)
-L$(LIBPATH)
-h
-H=e:\$(NAME).sym
| $(NAME).cfg


