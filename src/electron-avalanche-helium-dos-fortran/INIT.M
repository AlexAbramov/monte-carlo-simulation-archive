init.exe : init.obj 
 link /e init,,nul,llibfor7+llibc7 /noe;

init.obj : init.for sear.fn 
 fl /c /G2 init.for sear.fn
