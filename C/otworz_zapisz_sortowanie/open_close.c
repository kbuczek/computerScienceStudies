#include<stdio.h>

FILE *fin, *fout;
fin = fopen("dane.txt","r"); //read file
fout = fopen("out.dat","w"); //write file
scanf(argumenty) -> fscanf(fin,argumenty)	
printf(argumenty) -> fprintf(fout, argumenty)	
fclose(fin);
fclose(fout);
