inits.exe : inits.obj sechhe.obj rassech.obj 
 link /e inits+sechhe+rassech,inits,nul,llibfor7+llibc7 /noe;

inits.obj : inits.for inits.fn write_se.fn
      fl /c /G2 inits.for

sechhe.obj : sechhe.for
      fl /c /G2 sechhe.for

rassech.obj : rassech.for inits.fn
      fl /c /G2 rassech.for

