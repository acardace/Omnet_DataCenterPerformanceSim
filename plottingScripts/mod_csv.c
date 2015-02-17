#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//argv[1] csv file
//argv[2] run replications
//argv[3] start x value
//argv[4] step x value
//argv[5] x label
//argv[6] y label
//argv[7] plot Title

int main(int argc, char *argv[]){
   if( argc != 8 ){
      printf("./csv_mod <csv file> <replications> <start x value> <x step> <x label> <y label> <plot title>\n");
      exit(EXIT_SUCCESS);
   }

   FILE *in_csv = fopen(argv[1], "r");
   FILE *out_csv = fopen(".tmp_csv","w+");
   int rep = (int) strtol(argv[2], NULL, 10);
   int counter = rep;
   int x_start = (int) strtol(argv[3], NULL, 10);
   int x_step = (int) strtol(argv[4], NULL, 10);
   int x = x_start;
   double acc = 0.;
   double scanned;
   char path[128];
   char outfile[128];
   char *last_occ;

   last_occ = strrchr(argv[1],'/');
   if( last_occ )
      memcpy( outfile, last_occ+1, strlen(last_occ+1)-3);
   else
      memcpy( outfile, argv[1], strlen(argv[1])-3);
   outfile[strlen(argv[1])-2] = '\0';
   strcat( outfile, "svg");

   fprintf(out_csv,"X,Y\n");

   while( fscanf(in_csv,"%lf,",&scanned) != EOF ){
      counter--;
      //acc += scanned;
      if( counter==0 ){
         //acc = acc/rep;
         //fprintf(out_csv,"%d,%lf\n",x,acc);
         //acc = 0.;
         counter = rep;
         x += x_step;
      }
      fprintf(out_csv,"%d,%lf\n",x,scanned);
   }

   fclose(in_csv);
   fclose(out_csv);
   rename(".tmp_csv",argv[1]);

   sprintf(path,"Rscript plotter.R %s %s %s %s %s",argv[1],outfile, argv[5], argv[6], argv[7]);
   printf("OK -> %s modified correctly\n",argv[1]);
   printf("output will be saved in -> %s\n",outfile);
   printf("Executing -> %s\n",path);
   if( execlp("Rscript",path,"plotter.R",argv[1],outfile, argv[5], argv[6], argv[7],(char*) NULL) == -1)
      perror("execlp()");

   return 0;
}
