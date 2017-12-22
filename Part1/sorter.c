/*notes
    when finding "movie_facebook_likes", it reads it as "\tmovie_facebook_likes" when you compare it to argv[2].  This "\t" is believed to be from tabs in the stdin file.  *ask tjang about this*
 
*/
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include "sorter.h"
#include "mergesort.c"
 
int counter = 0;
int numProcessesMade;
 
int numColumns(char * csvname){
    int numcolumns = 0;
    FILE * fp;
    fp = fopen(csvname,"r");
    char str[1000];
    fgets(str, 1000, fp);  //fgets the stream from file pointer    <--------------some issue here Address sanitizer
   
    //this is for output
    char *string1 = strdup(str);
    string1 = trimWhiteSpace(string1);
   
    int i;
    for(i=0;i< (strlen(string1));i++){
        if(string1[i] == ','){
            numcolumns++;
        }
    }
    numcolumns++; //to get the true # of columns since i basically counted the commas between them.
    return numcolumns;
}
 
int isCSV(char * string){
    int length = strlen(string);
    if(length<4){
        //printf("String is too short to be a CSV file!\n");
        return 0;
    }
    char * ending = malloc(sizeof(char)*length);
    strncpy(ending, string+length-4, 4);
 
    if(strcmp(ending,".csv") == 0){ //0 means that this is a CSV file.
        free(ending);
        return 1;
    }else{              //1 means that this is not a CSV file.
        free(ending);
        return 0;
    }
 
    free(ending);
    return 0;
}
 
char * actualName(char * csvname){  //e.g. *csvname = movie_metadata.csv
    int length = (strlen(csvname)-4);
    char nombre[100];
    strncpy(nombre, csvname, length);
    char *actualName = strdup(nombre);
   
    return actualName; //e.g. *actualname should now be movie_metadata
}
 
void sortFile(char * csvname, char * colname, char * actualname, char * outputDirectory){ //IF OUTPUT DIRECTORY IS NULL
    //printf("csvname: %s\n", csvname);
    FILE * fp;
    fp = fopen(csvname,"r");
    char str[1000];
    fgets(str, 1000, fp);  //fgets the stream from file pointer    <--------------some issue here Address sanitizer
 
    //this is for output
    char *string1 = strdup(str);
    string1 = trimWhiteSpace(string1);  //string1 is the column headers
    //puts(string1);
 
    char *string = strdup(str);
    char * token = strsep(&string, ",");
 
    while(token != NULL){ //tokenizes the first columns
        token = trimWhiteSpace(token);
        if(strcmp(token,colname)==0){
            //printf("found it!! \n");
            break;
        }
        token = strsep(&string,",");
    }
       
    if(token == NULL){
        printf("\n");
        printf("error: no column exists, sorting failed on: %s\n",csvname);
        return;
    }
 
    char * newcsvname = malloc(sizeof(char)* 150);
    int size = strlen(csvname); // size = 34
    int q = (strlen(actualname) + 4); //q = 18
    size = size-q; //size is now 34-18 = 16
    strncpy(newcsvname, csvname, size); //at this point csvname = Part1/csv_files/movie_metadata-sorted-movie_title.csv
    int len = (     strlen(csvname) + strlen(actualname) + strlen(colname) + 40   );
    char * outputFile = malloc(sizeof(char)*len);
    strcpy(outputFile, newcsvname);
    strcat(outputFile, actualname);
    strcat(outputFile, "-sorted-");
    strcat(outputFile, colname);
    strcat(outputFile, ".csv");
    char * name = outputFile;
 
    FILE * ds = fopen(name,"ab+"); //outputFile = csv_files/movie_metadata-sorted-movie_title.csv  
    fprintf(ds,"%s\n", string1);
 
    int colnum;
    if(strcmp(colname,"color")==0){
        colnum = 0;
    }else if(strcmp(colname,"director_name")==0){
        colnum = 1;
    }else if(strcmp(colname,"num_critic_for_reviews")==0){
        colnum = 2;
    }else if(strcmp(colname,"duration")==0){
        colnum = 3;
    }else if(strcmp(colname,"director_facebook_likes")==0){
        colnum = 4;
    }else if(strcmp(colname,"actor_3_facebook_likes")==0){
        colnum = 5;
    }else if(strcmp(colname,"actor_2_name")==0){
        colnum = 6;
    }else if(strcmp(colname,"actor_1_facebook_likes")==0){
        colnum = 7;
    }else if(strcmp(colname,"gross")==0){
        colnum = 8;
    }else if(strcmp(colname,"genres")==0){
        colnum = 9;
    }else if(strcmp(colname,"actor_1_name")==0){
        colnum = 10;
    }else if(strcmp(colname,"movie_title")==0){
        colnum = 11;
    }else if(strcmp(colname,"num_voted_users")==0){
        colnum = 12;
    }else if(strcmp(colname,"cast_total_facebook_likes")==0){
        colnum = 13;
    }else if(strcmp(colname,"actor_3_name")==0){
        colnum = 14;
    }else if(strcmp(colname,"facenumber_in_poster")==0){
        colnum = 15;
    }else if(strcmp(colname,"plot_keywords")==0){
        colnum = 16;
    }else if(strcmp(colname,"movie_imdb_link")==0){
        colnum = 17;
    }else if(strcmp(colname,"num_user_for_reviews")==0){
        colnum = 18;
    }else if(strcmp(colname,"language")==0){
        colnum = 19;
    }else if(strcmp(colname,"country")==0){
        colnum = 20;
    }else if(strcmp(colname,"content_rating")==0){
        colnum = 21;
    }else if(strcmp(colname,"budget")==0){
        colnum = 22;
    }else if(strcmp(colname,"title_year")==0){
        colnum = 23;
    }else if(strcmp(colname,"actor_2_facebook_likes")==0){
        colnum = 24;
    }else if(strcmp(colname,"imdb_score")==0){
        colnum = 25;
    }else if(strcmp(colname,"aspect_ratio")==0){
        colnum = 26;
    }else if(strcmp(colname,"movie_facebook_likes")==0){
        colnum = 27;
    }
 
    int n = 5100;
    record * records = malloc(sizeof(record)*n);
    int i=0;
    int j=0;
    char * qm = "\"";
    char * symbol = malloc(sizeof(char)*2);
 
    while(!feof(fp)){ //goes through EVERY (5000) lines of the file and prints out EVERYTHING from the line
        fgets(str,1000,fp); //gets input from standard input
        string = strdup(str);
        token = strsep(&string,","); //an entry of a line
 
        if(j+1>n){ //reallocates more more entries into the array of structs
            n = n*2;
            records = realloc(records, n*sizeof(record));
        }
 
        while(token != NULL){ //tokenizes EACH line of the file
            token = trimWhiteSpace(token);
            switch(i){
                case 0:
                    records[j].color = token;
                    break;                 
                case 1:
                    records[j].directorName = token;
                    break;                 
                case 2:
                    records[j].numCriticReviews = atoi(token);
                    break;                 
                case 3:
                    records[j].duration = atoi(token);
                    break;
                case 4:
                    records[j].directorFBlikes = atoi(token);
                    break;                 
                case 5:
                    records[j].actor3FBlikes = atoi(token);
                    break;                 
                case 6:
                    records[j].actor2name = token;
                    break;                 
                case 7:
                    records[j].actor1FBlstringikes = atoi(token);
                    break;                 
                case 8:
                    records[j].gross = atof(token);
                    break;
                case 9:
                    records[j].genres = token;
                    break;                 
                case 10:
                    records[j].actor1name = token;
                    break;
                case 11:
                    records[j].movieTitle = token;
                    break;
                case 12:
                    records[j].numVotedUsers = atoi(token);
                    break;
                case 13:
                    records[j].castTotalFBlikes = atoi(token);
                    break;
                case 14:
                    records[j].actor3name = token;
                    break;
                case 15:
                    records[j].faceNumberPoster = atoi(token);
                    break;
                case 16:
                    records[j].plotKeywords = token;
                    break;
                case 17:
                    records[j].link = token;
                    break;
                case 18:
                    records[j].numUserReviews = atoi(token);
                    break;
                case 19:
                    records[j].language = token;
                    break;
                case 20:
                    records[j].country = token;
                    break;
                case 21:
                    records[j].contentRating = token;
                    break;
                case 22:
                    records[j].budget = atof(token);
                    break;
                case 23:
                    records[j].titleYear = atoi(token);
                    break;
                case 24:
                    records[j].actor2FBlikes = atoi(token);
                    break;
                case 25:
                    records[j].imdbScore = atof(token);
                    break;
                case 26:
                    records[j].aspectRatio = atof(token);
                    break;
                case 27:
                    records[j].movieFBlikes = atoi(token);
                    break;
            }          
            if(string != NULL){  //FIXED
                strncpy(symbol,string,1); //char for the first char of the string (used to check if theres a quotation mark"))         
            }
            if(strcmp(symbol,qm)==0){
                string = string + 1; //delete the string[0] which is currently a "
                token = strsep(&string,qm);
                string = string + 1; //delete the , after "
            }else{
                token = strsep(&string,",");
            }
           
            //token = strsep(&string,",");
            if(i == 28){ //after i has hit 28, we reset it back to 0.  
                i = 0;
            }
            i++;
        }
        j++;
        i=0;
    }
    //printf("%d \n",j); //j is the number of movies (AKA the "array size" when used for mergesort)
 
    mergesort(records, colnum, j-1);  //j-1 because the last entry is a repeat for some reason....
    int k;
    for(k=0;k<j-1;k++){
           
        //this if statement takes each title with a "," and puts quotations around it
        if(strchr(records[k].movieTitle,',')){ //detection works fine
            char qm1[100] = "";
            char qm2[100] = "";
            qm1[0] = '\"';
            qm2[0] = '\"';
            strcat(qm1,records[k].movieTitle);
            strcat(qm1,qm2);
            records[k].movieTitle = qm1;
        }
        fprintf(ds,"%s,%s,%d,%d,%d,%d,%s,%d,%f,%s,%s,%s,%d,%d,%s,%d,%s,%s,%d,%s,%s,%s,%f,%d,%d,%f,%f,%d\n", records[k].color,records[k].directorName,records[k].numCriticReviews,records[k].duration, records[k].directorFBlikes, records[k].actor3FBlikes, records[k].actor2name,records[k].actor1FBlikes,records[k].gross, records[k].genres, records[k].actor1name, records[k].movieTitle, records[k].numVotedUsers,records[k].castTotalFBlikes, records[k].actor3name,records[k].faceNumberPoster, records[k].plotKeywords, records[k].link, records[k].numUserReviews,records[k].language,records[k].country,records[k].contentRating,records[k].budget,records[k].titleYear,records[k].actor2FBlikes,records[k].imdbScore,records[k].aspectRatio,records[k].movieFBlikes);
    }
    //printf("SORTEDDDDDDDDDDDDDDDDDDDDDDDDDDD\n");
    free(newcsvname);
    free(outputFile);
    free(records);
    free(symbol);
}
 
void sortFile2(char * csvname, char * colname, char * actualname, char * outputDirectory){ //IF OUTPUT DIRECTORY IS NOT NULL
    FILE * fp;
    fp = fopen(csvname,"r");
    char str[1000];
    fgets(str, 1000, fp);  //fgets the stream from file pointer    <--------------some issue here Address sanitizer
 
    //this is for output
    char *string1 = strdup(str);
    string1 = trimWhiteSpace(string1);  //string1 is the column headers
    //puts(string1);
 
    char *string = strdup(str);
    char * token = strsep(&string, ",");
 
    while(token != NULL){ //tokenizes the first columns
        token = trimWhiteSpace(token);
        if(strcmp(token,colname)==0){
            //printf("found it!! \n");
            break;
        }
        token = strsep(&string,",");
    }
       
    if(token == NULL){
        printf("\n");
        printf("error: no column exists, sorting failed on: %s\n",csvname);
        return;
    }
   
    int len = (     strlen(outputDirectory) + strlen(actualname) + strlen(colname) + 40   );
    char * outputFile = malloc(sizeof(char)*len);
    strcpy(outputFile, outputDirectory);
    strcat(outputFile, "/");
    strcat(outputFile, actualname);
    strcat(outputFile, "-sorted-");
    strcat(outputFile, colname);
    strcat(outputFile, ".csv");
    //printf("outputFile is: %s\n", outputFile);
    char * name = outputFile;
 
 
    FILE * ds = fopen(name,"ab+"); //outputFile = csv_files/movie_metadata-sorted-movie_title.csv  
    fprintf(ds,"%s\n", string1);
 
    int colnum;
    if(strcmp(colname,"color")==0){
        colnum = 0;
    }else if(strcmp(colname,"director_name")==0){
        colnum = 1;
    }else if(strcmp(colname,"num_critic_for_reviews")==0){
        colnum = 2;
    }else if(strcmp(colname,"duration")==0){
        colnum = 3;
    }else if(strcmp(colname,"director_facebook_likes")==0){
        colnum = 4;
    }else if(strcmp(colname,"actor_3_facebook_likes")==0){
        colnum = 5;
    }else if(strcmp(colname,"actor_2_name")==0){
        colnum = 6;
    }else if(strcmp(colname,"actor_1_facebook_likes")==0){
        colnum = 7;
    }else if(strcmp(colname,"gross")==0){
        colnum = 8;
    }else if(strcmp(colname,"genres")==0){
        colnum = 9;
    }else if(strcmp(colname,"actor_1_name")==0){
        colnum = 10;
    }else if(strcmp(colname,"movie_title")==0){
        colnum = 11;
    }else if(strcmp(colname,"num_voted_users")==0){
        colnum = 12;
    }else if(strcmp(colname,"cast_total_facebook_likes")==0){
        colnum = 13;
    }else if(strcmp(colname,"actor_3_name")==0){
        colnum = 14;
    }else if(strcmp(colname,"facenumber_in_poster")==0){
        colnum = 15;
    }else if(strcmp(colname,"plot_keywords")==0){
        colnum = 16;
    }else if(strcmp(colname,"movie_imdb_link")==0){
        colnum = 17;
    }else if(strcmp(colname,"num_user_for_reviews")==0){
        colnum = 18;
    }else if(strcmp(colname,"language")==0){
        colnum = 19;
    }else if(strcmp(colname,"country")==0){
        colnum = 20;
    }else if(strcmp(colname,"content_rating")==0){
        colnum = 21;
    }else if(strcmp(colname,"budget")==0){
        colnum = 22;
    }else if(strcmp(colname,"title_year")==0){
        colnum = 23;
    }else if(strcmp(colname,"actor_2_facebook_likes")==0){
        colnum = 24;
    }else if(strcmp(colname,"imdb_score")==0){
        colnum = 25;
    }else if(strcmp(colname,"aspect_ratio")==0){
        colnum = 26;
    }else if(strcmp(colname,"movie_facebook_likes")==0){
        colnum = 27;
    }
 
    int n = 5100;
    record * records = malloc(sizeof(record)*n);
    int i=0;
    int j=0;
    char * qm = "\"";
    char * symbol = malloc(sizeof(char)*2);
 
    while(!feof(fp)){ //goes through EVERY (5000) lines of the file and prints out EVERYTHING from the line
        fgets(str,1000,fp); //gets input from standard input
        string = strdup(str);
        token = strsep(&string,","); //an entry of a line
 
        if(j+1>n){ //reallocates more more entries into the array of structs
            n = n*2;
            records = realloc(records, n*sizeof(record));
        }
 
        while(token != NULL){ //tokenizes EACH line of the file
            token = trimWhiteSpace(token);
            switch(i){
                case 0:
                    records[j].color = token;
                    break;                 
                case 1:
                    records[j].directorName = token;
                    break;                 
                case 2:
                    records[j].numCriticReviews = atoi(token);
                    break;                 
                case 3:
                    records[j].duration = atoi(token);
                    break;
                case 4:
                    records[j].directorFBlikes = atoi(token);
                    break;                 
                case 5:
                    records[j].actor3FBlikes = atoi(token);
                    break;                 
                case 6:
                    records[j].actor2name = token;
                    break;                 
                case 7:
                    records[j].actor1FBlikes = atoi(token);
                    break;                 
                case 8:
                    records[j].gross = atof(token);
                    break;
                case 9:
                    records[j].genres = token;
                    break;                 
                case 10:
                    records[j].actor1name = token;
                    break;
                case 11:
                    records[j].movieTitle = token;
                    break;
                case 12:
                    records[j].numVotedUsers = atoi(token);
                    break;
                case 13:
                    records[j].castTotalFBlikes = atoi(token);
                    break;
                case 14:
                    records[j].actor3name = token;
                    break;
                case 15:
                    records[j].faceNumberPoster = atoi(token);
                    break;
                case 16:
                    records[j].plotKeywords = token;
                    break;
                case 17:
                    records[j].link = token;
                    break;
                case 18:
                    records[j].numUserReviews = atoi(token);
                    break;
                case 19:
                    records[j].language = token;
                    break;
                case 20:
                    records[j].country = token;
                    break;
                case 21:
                    records[j].contentRating = token;
                    break;
                case 22:
                    records[j].budget = atof(token);
                    break;
                case 23:
                    records[j].titleYear = atoi(token);
                    break;
                case 24:
                    records[j].actor2FBlikes = atoi(token);
                    break;
                case 25:
                    records[j].imdbScore = atof(token);
                    break;
                case 26:
                    records[j].aspectRatio = atof(token);
                    break;
                case 27:
                    records[j].movieFBlikes = atoi(token);
                    break;
            }          
            if(string != NULL){  //FIXED
                strncpy(symbol,string,1); //char for the first char of the string (used to check if theres a quotation mark"))         
            }
            if(strcmp(symbol,qm)==0){
                string = string + 1; //delete the string[0] which is currently a "
                token = strsep(&string,qm);
                string = string + 1; //delete the , after "
            }else{
                token = strsep(&string,",");
            }
           
            //token = strsep(&string,",");
            if(i == 28){ //after i has hit 28, we reset it back to 0.  
                i = 0;
            }
            i++;
        }
        j++;
        i=0;
    }
    //printf("%d \n",j); //j is the number of movies (AKA the "array size" when used for mergesort)
 
    mergesort(records, colnum, j-1);  //j-1 because the last entry is a repeat for some reason....
    int k;
    for(k=0;k<j-1;k++){
           
        //this if statement takes each title with a "," and puts quotations around it
        if(strchr(records[k].movieTitle,',')){ //detection works fine
            char qm1[100] = "";
            char qm2[100] = "";
            qm1[0] = '\"';
            qm2[0] = '\"';
            strcat(qm1,records[k].movieTitle);
            strcat(qm1,qm2);
            records[k].movieTitle = qm1;
        }
        fprintf(ds,"%s,%s,%d,%d,%d,%d,%s,%d,%f,%s,%s,%s,%d,%d,%s,%d,%s,%s,%d,%s,%s,%s,%f,%d,%d,%f,%f,%d\n", records[k].color,records[k].directorName,records[k].numCriticReviews,records[k].duration, records[k].directorFBlikes, records[k].actor3FBlikes, records[k].actor2name,records[k].actor1FBlikes,records[k].gross, records[k].genres, records[k].actor1name, records[k].movieTitle, records[k].numVotedUsers,records[k].castTotalFBlikes, records[k].actor3name,records[k].faceNumberPoster, records[k].plotKeywords, records[k].link, records[k].numUserReviews,records[k].language,records[k].country,records[k].contentRating,records[k].budget,records[k].titleYear,records[k].actor2FBlikes,records[k].imdbScore,records[k].aspectRatio,records[k].movieFBlikes);
    }
    //printf("SORTEDDDDDDDDDDDDDDDDDDDDDDDDDDD\n");
    free(outputFile);
    free(records);
    free(symbol);
}
 
void getFile(char * path, char * colname, char * outputDirectory){  
    int pathlen = strlen(path) + 5;
    char * newpath = malloc(sizeof(char) * pathlen);
    sprintf(newpath, "%s", path);
    DIR * dir;
    dir = opendir(path);
    struct dirent * string;
    while(dir){ //traverses through contents of directory
        if((string = readdir(dir)) != NULL){  //checks to see if we've checked everything in the directory
	    //printf("string->d_name: %s\n", string->d_name);
            if(string->d_type == DT_DIR){  //If directory  <--some error is happening here
                if( (strcmp(string->d_name,".") !=0) && (strcmp(string->d_name, "..") !=0) ){ //Makes sure its not a hidden directory
                    //printf("found a DIRECTORY <%s>, <------- fork here\n", string->d_name);  
                    if(!fork()){ //If this is a child
                        printf("%d, ", getpid()); //print pid
                        fflush(stdout);
                        int newsize = (strlen(newpath) + strlen(string->d_name) + 1);
                        char * fullpath = malloc(sizeof(char)*(newsize + 1));
                            strcpy(fullpath, newpath);
                            strcat(fullpath, "/");
                        strcat(fullpath, string->d_name);  
                       
                        closedir(dir); //closes the old path  **IMPORTANT SO NO DOUBLING OCCURS**
                        dir = opendir(fullpath);  //creates new path for the child process
                        //printf("=======================%s\n", newpath);
                        free(newpath);
                        newpath = malloc(sizeof(char) * (strlen(fullpath) + 10));  //resets newpath with new size
                        strcpy(newpath, fullpath);
                        free(fullpath);
                        //printf("=======================%s\n", newpath);
                       
                        counter = 0;  //reset counter
                    }
                    else{  //else still in parent
                        counter++;
                    }
                }
            }else{  //Not a directory, but could be a csv file
                //printf("---->is %s a csv file?\n", string->d_name);
                int c = isCSV(string->d_name);
                if(c==1){
                    //printf("Found CSV FILE: <---- fork here %s\n", string->d_name);
                    //printf("file path at %s, is %s\n", string->d_name, path);
                    if(!fork()){   //If this is a child
                        int newsize = (strlen(newpath) + strlen(string->d_name) + 1);
                        char * fullpath = malloc(sizeof(char)* (newsize+1));                   
                        strcpy(fullpath, newpath);
                        strcat(fullpath, "/");
                        strcat(fullpath, string->d_name);
                       
                        //printf("file path for %s --->>> %s\n", string->d_name,fullpath);
                        //printf("Sorting file: %s\n", string->d_name);
 
                        //SORTS on file here
 
                        int colnums = 0;
                        colnums = numColumns(fullpath);
                        //printf("number of columns in csv file is: %d\n", colnums);
                                               
                        if(colnums != 28){
                            //printf("ERROR: different number of columns\n");
                            //printf("failed to sort on file: %s\n", string->d_name);
                            return;
                        }
 
                        printf("%d, ", getpid());  //print pid
                        fflush(stdout);
                        char * nombre = actualName(string->d_name);
                        //printf("actual name is: %s\n", nombre);
                        if(outputDirectory != NULL){
                            sortFile2(fullpath, colname, nombre, outputDirectory);
                        }else{
                            sortFile(fullpath, colname, nombre,outputDirectory);
                        }
                       
                        free(fullpath);
                        return;   //signals that the sorting process is done
                    }else{    //else still in parent
                        counter++;
                    }
                }
            }
        }else{ //if theres nothing else to see in the directory, stop looping through directory
            break;
        }
    }
   
    while(counter != 0){   //all files in the immediate folder have been forked if directory or csv file, now waits for #counter of processes to return
        //printf("process completed\n");       
        int status;    
        wait(&status);
        counter--;
    }
   
    free(newpath);
    return; //signals that directory fork is done
}
 
//finds the number of processes made in the directory
void numProcess(char * stream){  
    DIR * dir;
    dir = opendir(stream);
    struct dirent * string;
    while(dir){
        if((string = readdir(dir)) != NULL){
            if (string->d_type == DT_DIR){
                if(     (strcmp(string->d_name, ".") != 0) && (strcmp(string->d_name, "..") != 0)      ){
                    numProcessesMade++;
 
                    if ((strlen(stream) + strlen(string->d_name) + 1) > PATH_MAX){  //path is say "/ilab/users/CS214/Part1" here
                            //return 0;
                        }
                    char fullpath[PATH_MAX + 1];
 
                        strcpy(fullpath, stream);
                        strcat(fullpath, "/");
                        strcat(fullpath, string->d_name);  
 
                        numProcess(fullpath); //new path is say "/ilab/users/CS214/Part1/csv_files" here
                }else{
 
                }
            }else{
               
            }
            //printf("path is: %s\n", stream);
            int c = isCSV(string->d_name);
            if(c == 1){
                if ((strlen(stream) + strlen(string->d_name) + 1) > PATH_MAX){  //path is say "/ilab/users/CS214/Part1" here
                        //return 0;
                    }
                char fullpath[PATH_MAX + 1];
 
                    strcpy(fullpath, stream);
                    strcat(fullpath, "/");
                    strcat(fullpath, string->d_name);
 
                int colnums = 0;
                colnums = numColumns(fullpath);  //checks if the number of columns in the file is correct
                if(colnums == 28){
                    numProcessesMade++;
                }
            }else{
 
            }
 
        }else{
            closedir(dir);
            return;
        }
    }
    closedir(dir);
}

int main(int argc, char ** argv){
 
    int pid = getpid();
    printf("Initial PID: %d \n", pid);
    printf("PIDS of all child processes: ");
    fflush(stdout);
   
    char cwd[1024];

    int isthere = 0;
    int isthere2 = 0;
 
    DIR * dip;
    if((dip = opendir(argv[6])) != NULL){
	isthere = 1;
    }
    DIR * dip2;
    if((dip2 = opendir(argv[4])) != NULL){
        isthere2 = 1;
    }

    if(argv[5] != NULL){
	    if(strcmp(argv[5],"-o") == 0){
		//printf("true\n");
		if(isthere == 0){
		    printf("\n");
		    printf("error: not a valid output directory\n");
		    return 0;
		}
	    }
    }else{
	    if(strcmp(argv[3],"-o") == 0){
		//printf("true\n");
		if(isthere2 == 0){
		    printf("\n");
		    printf("error: not a valid output directory\n");
		    return 0;
		}
	    }
    }

    if(isthere == 0 && isthere2 == 0){
        //./sorter -c <column_type>
        if(getcwd(cwd, sizeof(cwd)) != NULL){
            //fprintf(stdout, "Current working dir: %s \n", cwd);
        }else{
            perror("getcwd() error");
            return 0;
        }
        numProcess(cwd);
        getFile(cwd,argv[2],NULL);
    }else{
        if(strcmp(argv[3], "-o") == 0 ){
            //./sorter -c <column_type> -o <output_directory
            if(getcwd(cwd, sizeof(cwd)) != NULL){
                //fprintf(stdout, "Current working dir: %s \n", cwd);
            }else{
                perror("getcwd() error");
                return 0;
            }
            numProcess(cwd);
            getFile(cwd,argv[2],argv[4]);
        }else{
            if(isthere == 1){
                if(argv[4] != NULL){
                    //./sorter -c <column_type> -d <input_directory> -o <output_directory
                    numProcess(argv[4]);
                    getFile(argv[4],argv[2],argv[6]);
                }else{
                    if(getcwd(cwd, sizeof(cwd)) != NULL){
                        //fprintf(stdout, "Current working dir: %s \n", cwd);
                    }else{
                        perror("getcwd() error");
                        return 0;
                    }
                    numProcess(cwd);
                    getFile(cwd,argv[2],argv[6]);
                }
            }else if(isthere == 0){ //argv[6] IS NULL
                if(isthere2 == 1){
                    //./sorter -c <column_type> -d <input_directory>
                    numProcess(argv[4]);
                    getFile(argv[4],argv[2],NULL);
                }else if(isthere2 == 0){
                    //./sorter -c <column_type>
                    if(getcwd(cwd, sizeof(cwd)) != NULL){
                        //fprintf(stdout, "Current working dir: %s \n", cwd);
                    }else{
                        perror("getcwd() error");
                        return 0;
                    }
                    numProcess(cwd);
                    getFile(cwd,argv[2],NULL);
                }
            }
        }
    }

    int status;
    wait(&status);
    if(pid == getpid()){
        printf("\n");
        numProcessesMade = numProcessesMade + 1;
        printf("Total Number of Processes Made: %d \n", numProcessesMade);
    }
 
    return 0;
}
