NAME=init
NAME1=param
CPP=..\cpp
OBJ=..\obj
LIB=c:\bc45\lib;$(OBJ)
INCLUDE=c:\bc45\include;..\include
TLINK=c:\bc45\bin\tlink
BCC=c:\bc45\bin\bcc
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
