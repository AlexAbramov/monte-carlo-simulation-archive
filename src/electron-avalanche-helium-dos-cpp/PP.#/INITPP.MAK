NAME=initpp
NAME1=pparam
CPP=..\cpp
OBJ=..\obj
LIB=c:\bc2\lib;$(OBJ)
INCLUDE=c:\bc2\include;..\include
TLINK=c:\bc2\bin\tlink
BCC=c:\bc2\bin\bcc
CFG= -c -n$(OBJ) -ml -f87 -I$(INCLUDE) 

# *************************************************************************

$(NAME).exe	:	$(OBJ)\$(NAME).obj\
	  		$(OBJ)\$(NAME1).obj
  $(TLINK) /v /x /c /L$(LIB) c0l+$(OBJ)\$(NAME)+$(OBJ)\$(NAME1),$(NAME),,fp87+mathl+cl

# *************************************************************************

$(OBJ)\$(NAME).obj :		$(NAME).cpp	..\include\param.h
  $(BCC)  $(CFG)		$(NAME).cpp

# *************************************************************************

$(OBJ)\$(NAME1).obj :		$(CPP)\$(NAME1).cpp	..\include\param.h
  $(BCC)  $(CFG)		$(CPP)\$(NAME1).cpp

# *************************************************************************
