NAME=mk1
NAME1=param
NAME2=se
NAME3=lav1
NAME4=timer
NAME5=rnd
CPP=..\cpp
OBJ=..\obj
LIB=c:\bc45\lib;$(OBJ)
INCLUDE=c:\bc45\include;..\include
TLINK=c:\bc45\bin\tlink
BCC=c:\bc45\bin\bcc
CFG= -c -f87 -n$(OBJ) -ml -I$(INCLUDE) 

# *************************************************************************

$(NAME).exe	:	$(OBJ)\$(NAME).obj\
	  		$(OBJ)\$(NAME1).obj\
	  		$(OBJ)\$(NAME2).obj\
	  		$(OBJ)\$(NAME3).obj\
	  		$(OBJ)\$(NAME4).obj\
	  		$(OBJ)\$(NAME5).obj
  $(TLINK) /v /x /c /L$(LIB) c0l+$(OBJ)\$(NAME)+$(OBJ)\$(NAME1)+$(OBJ)\$(NAME2)+$(OBJ)\$(NAME3)+$(OBJ)\$(NAME4)+$(OBJ)\$(NAME5),$(NAME),,mathl+cl+fp87

# *************************************************************************

$(OBJ)\$(NAME).obj :		$(NAME).cpp	..\include\param.h
  $(BCC)  $(CFG)		$(NAME).cpp

# *************************************************************************

$(OBJ)\$(NAME1).obj :		$(CPP)\$(NAME1).cpp	..\include\param.h
  $(BCC)  $(CFG)		$(CPP)\$(NAME1).cpp

# *************************************************************************

$(OBJ)\$(NAME2).obj :		$(CPP)\$(NAME2).cpp	..\include\se.h
  $(BCC)  $(CFG)		$(CPP)\$(NAME2).cpp

# *************************************************************************

$(OBJ)\$(NAME3).obj :		$(CPP)\$(NAME3).cpp	..\include\param.h
  $(BCC)  $(CFG)		$(CPP)\$(NAME3).cpp

# *************************************************************************

$(OBJ)\$(NAME4).obj :		$(CPP)\$(NAME4).cpp
  $(BCC)  $(CFG)		$(CPP)\$(NAME4).cpp

# *************************************************************************

$(OBJ)\$(NAME5).obj :		$(CPP)\$(NAME5).cpp
  $(BCC)  $(CFG)		$(CPP)\$(NAME5).cpp

# *************************************************************************
