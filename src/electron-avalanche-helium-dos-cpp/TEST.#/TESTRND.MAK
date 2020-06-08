NAME=testrnd
NAME1=rnd
NAME2=mygraph
CPP=..\cpp
OBJ=..\obj
LIB=e:;$(OBJ)
INCLUDE=e:;..\include
TLINK=e:tlink
BCC=e:bcc
CFG= -c -n$(OBJ) -ml -f87 -I$(INCLUDE) 

# *************************************************************************

$(NAME).exe	:	$(OBJ)\$(NAME).obj\
	  		$(OBJ)\$(NAME1).obj\
	  		$(OBJ)\$(NAME2).obj
  TLINK /v /x /c /L$(LIB) c0l+$(OBJ)\$(NAME)+$(OBJ)\$(NAME1)+$(OBJ)\$(NAME2),$(NAME),,fp87+mathl+cl+graphics

# *************************************************************************

$(OBJ)\$(NAME).obj :		$(NAME).cpp
  $(BCC)  $(CFG)		$(NAME).cpp

# *************************************************************************

$(OBJ)\$(NAME1).obj :		$(CPP)\$(NAME1).cpp
  $(BCC)  $(CFG)		$(CPP)\$(NAME1).cpp

# *************************************************************************

$(OBJ)\$(NAME2).obj :		$(CPP)\$(NAME2).cpp
  $(BCC)  $(CFG)		$(CPP)\$(NAME2).cpp

# *************************************************************************
