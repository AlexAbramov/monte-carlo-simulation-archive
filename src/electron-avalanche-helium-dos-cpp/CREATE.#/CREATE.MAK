NAME=create
NAME1=mygraph
NAME2=se
NAME3=selas
NAME4=sex
NAME5=sion
CPP=..\cpp
OBJ=..\obj
LIB=c:\bc45\lib;$(OBJ)
INCLUDE=c:\bc45\include\;..\include
TLINK=c:\bc45\bin\tlink
BCC=c:\bc45\bin\bcc
CFG= -c -n$(OBJ) -ml -f87 -I$(INCLUDE) 
# *************************************************************************

$(NAME).exe	:	$(OBJ)\$(NAME).obj\
	  		$(OBJ)\$(NAME1).obj\
	  		$(OBJ)\$(NAME2).obj\
	  		$(OBJ)\$(NAME3).obj\
	  		$(OBJ)\$(NAME4).obj\
	  		$(OBJ)\$(NAME5).obj
  $(TLINK) /v /x /c /L$(LIB) @&&|
c0l+
$(OBJ)\$(NAME)+
$(OBJ)\$(NAME1)+
$(OBJ)\$(NAME2)+
$(OBJ)\$(NAME3)+
$(OBJ)\$(NAME4)+
$(OBJ)\$(NAME5)
$(NAME)
# no map files
fp87+
mathl+
cl+
graphics
|

# *************************************************************************

$(OBJ)\$(NAME).obj :		$(NAME).cpp
  $(BCC)  $(CFG)		$(NAME).cpp

# *************************************************************************

$(OBJ)\$(NAME1).obj :		$(CPP)\$(NAME1).cpp
  $(BCC)  $(CFG)		$(CPP)\$(NAME1).cpp

# *************************************************************************

$(OBJ)\$(NAME2).obj :		$(CPP)\$(NAME2).cpp	..\include\$(NAME2).h
  $(BCC)  $(CFG)		$(CPP)\$(NAME2).cpp	

# *************************************************************************

$(OBJ)\$(NAME3).obj :		$(CPP)\$(NAME3).cpp
  $(BCC)  $(CFG)		$(CPP)\$(NAME3).cpp

# *************************************************************************

$(OBJ)\$(NAME4).obj :		$(CPP)\$(NAME4).cpp
  $(BCC)  $(CFG)		$(CPP)\$(NAME4).cpp

# *************************************************************************

$(OBJ)\$(NAME5).obj :		$(CPP)\$(NAME5).cpp
  $(BCC)  $(CFG)		$(CPP)\$(NAME5).cpp

# *************************************************************************
