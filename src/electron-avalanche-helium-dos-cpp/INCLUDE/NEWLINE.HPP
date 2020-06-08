static void newline(FILE* fp)
{ 
  while(1){ int k=fgetc(fp); if(k==10 || k==-1)break; }
}
