execute.exe : execute.obj lav.obj nach.obj rand.obj 
 link /e execute+lav+nach+rand,execute,nul,llibfor7+llibc7 /noe;

execute.obj : execute.for sear.fn time.fn read_se.fn read.fn write.fn 
      fl /c /G2 execute.for 

lav.obj : lav.for sear.fn count.fn
      fl /c /G2 lav.for

nach.obj : nach.for
      fl /c /G2 nach.for

rand.obj : rand.for
      fl /c /G2 rand.for

