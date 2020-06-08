NAME=v3
NAME1=mygraph
NAME2=se
CPP=..\cpp
OBJ=..\obj
LIB=c:\bc45\lib\;$(OBJ)
INCLUDE=c:\bc45\include;..\include
TLINK=c:\bc45\bin\tlink
BCC=c:\bc45\bin\bcc
CFG= -c -n$(OBJ) -ml -f87 -I$(INCLUDE) 

# *************************************************************************

$(NAME).exe	:	$(OBJ)\$(NAME).obj\
	  		$(OBJ)\$(NAME1).obj\
	  		$(OBJ)\$(NAME2).obj
  $(TLINK) /v /x /c /L$(LIB) c0l+$(OBJ)\$(NAME)+$(OBJ)\$(NAME1)+$(OBJ)\$(NAME2),$(NAME),,fp87+mathl+cl+graphics

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
