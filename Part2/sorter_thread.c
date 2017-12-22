#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include "sorter_thread.h"
#include "mergesort.c"
#include<pthread.h>

#define MAX_FILES 4000

//pthread_t tid[MAX_FILES]; //creates all of the pthread_t pointers to each thread

int k = 0;

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
	}else{ 				//1 means that this is not a CSV file.
		free(ending);
		return 0;
	}

	free(ending);
	return 0;
}

//global variables
//pthread_t tid[MAX_FILES];
//int tcounter = 1; 	//starts at 1 b/c tid[0] is created in the main
int threadcount = 0;
char * colname;
char * outputDirectory;
char * titles;
int globalColnum;
int v = 12000;
int recordsSize = 0;
record * allrecords;
//char * actualname;  //we might actually not need actualname since we are putting everything into a big csv file

//initialize locks
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* sortFile(void * csvname){
	char * csvname_ptr = (char*) csvname;
	//char * colname_ptr = (char*) colname;
	
	//printf("colname_ptr: %s\n", colname_ptr);

	//IMPLEMENT LOCK HERE, so only one thread can actually SORT at a time
	pthread_mutex_lock(&m);
	//printf("**********sorting file: %s\n", csvname_ptr);
	//printf("RUNNING SORT\n");

	FILE * fp;
	fp = fopen(csvname_ptr,"r");
	char str[1000];
	fgets(str, 1000, fp);  //fgets the stream from file pointer    <--------------some issue here Address sanitizer
	 
	//this is for output
	char *string1 = strdup(str);
	string1 = trimWhiteSpace(string1);  //string1 is the column headers
	//puts(string1);
	//printf("string1: %s\n", string1);
	 
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
		printf("error: no column exists, sorting failed on: %s\n",csvname_ptr);
		return NULL;
	}
	/*
	char * name = "AllFiles-sorted-";
	char * outputFile = malloc(sizeof(char) * 200);
	if(outputDirectory != NULL){
		strcpy(outputFile, outputDirectory);
		strcat(outputFile, "/");
		strcat(outputFile, name);
		strcat(outputFile, colname);
		strcat(outputFile, ".csv");
		printf("outputFile: %s\n", outputFile);

	}else{
		strcpy(outputFile, name);
		strcat(outputFile, colname);
		strcat(outputFile, ".csv");
		printf("outputFile: %s\n", outputFile);
	}

	FILE * ds = fopen(outputFile,"ab+"); //outputFile = csv_files/movie_metadata-sorted-movie_title.csv
	fprintf(ds,"%s\n", string1); 
	*/
	titles = string1;

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
	 
	while(!feof(fp)){ 	//goes through EVERY (5000) lines of the file and prints out EVERYTHING from the line
		fgets(str,1000,fp); 	//gets input from standard input
		string = strdup(str);
		token = strsep(&string,","); 	//an entry of a line
	 
		if(j+1>n){ 	//reallocates more more entries into the array of structs
		    n = n*2;
		    records = realloc(records, n*sizeof(record));
		}
	 
		while(token != NULL){ 	//tokenizes EACH line of the file
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
	    globalColnum = colnum;
	    mergesort(records, colnum, j-1);  //j-1 because the last entry is a repeat for some reason....
	    //EVERYTHING in records should now be SORTED!

	    //put everything into the global ARRAY
	    //printf("recordsSize: %d, j: %d \n", recordsSize, j);
	    //printf("v: %d \n", v);
	    if( (recordsSize + j) > v){
		v = v*2;
		//printf("realloced!!\n");
		allrecords = realloc(allrecords, v*sizeof(record));
	    }
	    int p;
	    for(p=0;p<j;p++){
		allrecords[recordsSize] = records[p]; 
		recordsSize++;
	    }
/*	    
	    int k;
	    for(k=0;k<j-1;k++){
			//printf("%d",k);
		   
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

*/	
	//printf("SORTEDDDDDDDDDDDDDDDDDDDDDDDDDDD\n");
	//free(newcsvname);
	//free(outputFile);
	free(records);
	free(symbol);

	pthread_mutex_unlock(&m);

	pthread_exit(0);
}

void* getFile(void * path){
	//int pathlen = strlen(path) + 5;
	//char * newpath = malloc(sizeof(char) * pathlen);
	//sprintf(newpath, "%s", path);

	pthread_t tid[MAX_FILES];
	int tcounter = 0;

	char * path_ptr = (char*) path;
	//printf("path is: %s\n", path_ptr);

	DIR * dir;
	dir = opendir(path_ptr);
	//struct dirent * string;
	struct dirent * string2 = malloc(5000);
	//int tnum;
	while(dir){  //traverses through contents of directory
		readdir_r(dir, string2, &string2);
		if(string2 != NULL){  //checks to see if we've checked everything in the directory
			if(string2->d_type == DT_DIR){  //If directory
				if( (strcmp(string2->d_name,".") !=0) && (strcmp(string2->d_name, "..") !=0) ){ //no hidden directory
					//printf("found a DIRECTORY <%s>, <------- thread here\n", string2->d_name);
					//spawn a thread to traverse through sub directory
					//pthread_t id;
					pthread_attr_t attr;
					pthread_attr_init(&attr);
					
					int newsize = (strlen(path_ptr) + strlen(string2->d_name) + 1);
					char * fullpath = malloc(sizeof(char)*(newsize + 1));
	    				strcpy(fullpath, path_ptr);
	    				strcat(fullpath, "/");
					strcat(fullpath, string2->d_name);
					
					//tid[tcounter];
					//printf("fullpath: %s\n", fullpath);
					//tnum = tcounter;
            				pthread_create(&tid[tcounter], NULL, getFile, fullpath); //fullpath should be a pointer
					threadcount++;
					tcounter++;
			
					//print out tid
					//tid[tcounter] = pthread_self();
					//printf("tid is: %lu\n", tid[tcounter]);

				}
			}else{  //Not a directory, but could be a csv file
				int c = isCSV(string2->d_name);
				if(c==1){
					//printf("Found CSV FILE: <---- thread here %s\n", string2->d_name);
					//spawn a thread to sort the csv file
					pthread_attr_t attr;
					pthread_attr_init(&attr);
					
					int newsize = (strlen(path_ptr) + strlen(string2->d_name) + 1);
					char * fullpath = malloc(sizeof(char)*(newsize + 1));
	    				strcpy(fullpath, path_ptr);
	    				strcat(fullpath, "/");
					strcat(fullpath, string2->d_name);

					//int tnum2 = tcounter;
					pthread_create(&tid[tcounter], NULL, sortFile, fullpath);
					threadcount++;
					tcounter++;
									
					//tid[tcounter] = pthread_self();
					//printf("tid is: %lu\n", tid[tcounter]);
				}
			}
		}else{ //if theres nothing else to see in the directory, stop looping through directory
			break;
		}
	}
	//sleep(1);
	int j;
	for(j=0; j<tcounter; j++){
		pthread_join(tid[j], NULL);
		//tid[j] = pthread_self();
		printf("%lu, ", tid[j]);
	}
	//tid[tnum] = pthread_self();
	//printf("tid is: %lu\n", tid[tnum]);
	//pthread_join(tid[tnum],NULL);

	pthread_exit(0);
}


int main(int argc, char ** argv){
	
	char cwd[1024];
	//numProcessesMade = 0;
	allrecords = malloc(sizeof(record) * v);
	char * inputDirectory;

	int i = 0;
	while(argv[i]){
		if(strcmp(argv[i],"-c") == 0){
			colname = argv[i+1];
		}
		if(strcmp(argv[i],"-o") == 0){
			outputDirectory = argv[i+1];
		}
		if(strcmp(argv[i], "-d") == 0){
			inputDirectory = argv[i+1];
		}
		i++;
	}
	if(inputDirectory == NULL){
		inputDirectory = getcwd(cwd, sizeof(cwd));
	}
	//printf("colname: %s\n", colname);
	//printf("outputDirectory: %s\n", outputDirectory);
	//printf("inputDirectory is: %s\n", inputDirectory);
	
	//makes the thread id
	pthread_t tid;

	//attributes of the thread
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	//creates thread.
	pthread_create(&tid, NULL, getFile, inputDirectory);
	printf("initial TID: %lu \n", tid);
	printf("TIDS of all child threads: ");
	threadcount++;	

	//waits for thread to end
	pthread_join(tid, NULL);
	
	//tid = pthread_self();
	//printf("tid is: %lu\n", tid);
	
	//printf("records size: %d\n", recordsSize);
/*
	for(k=0; k<recordsSize; k++){
		printf("%s,%s,%d,%d,%d,%d,%s,%d,%f,%s,%s,%s,%d,%d,%s,%d,%s,%s,%d,%s,%s,%s,%f,%d,%d,%f,%f,%d\n\n", allrecords[k].color,allrecords[k].directorName,allrecords[k].numCriticReviews,allrecords[k].duration, allrecords[k].directorFBlikes, allrecords[k].actor3FBlikes, allrecords[k].actor2name,allrecords[k].actor1FBlikes,allrecords[k].gross, allrecords[k].genres, allrecords[k].actor1name, allrecords[k].movieTitle, allrecords[k].numVotedUsers,allrecords[k].castTotalFBlikes, allrecords[k].actor3name,allrecords[k].faceNumberPoster, allrecords[k].plotKeywords, allrecords[k].link, allrecords[k].numUserReviews,allrecords[k].language,allrecords[k].country,allrecords[k].contentRating,allrecords[k].budget,allrecords[k].titleYear,allrecords[k].actor2FBlikes,allrecords[k].imdbScore,allrecords[k].aspectRatio,allrecords[k].movieFBlikes);
	}
*/

	char * name = "AllFiles-sorted-";
	char * outputFile = malloc(sizeof(char) * 200);
	if(outputDirectory != NULL){
		strcpy(outputFile, outputDirectory);
		strcat(outputFile, "/");
		strcat(outputFile, name);
		strcat(outputFile, colname);
		strcat(outputFile, ".csv");
		//printf("outputFile: %s\n", outputFile);

	}else{
		strcpy(outputFile, name);
		strcat(outputFile, colname);
		strcat(outputFile, ".csv");
		//printf("outputFile: %s\n", outputFile);
	}

	FILE * ds = fopen(outputFile,"ab+"); //outputFile = csv_files/movie_metadata-sorted-movie_title.csv
	fprintf(ds,"%s\n", titles); 

	//NOW I CAN CONFIRM THAT EVERYTHING IS IN the variable allrecords, now i must mergesort on allrecords
	mergesort(allrecords, globalColnum, recordsSize);
/*
	int k;
	for(k=0; k<recordsSize; k++){
		printf("%s,%s,%d,%d,%d,%d,%s,%d,%f,%s,%s,%s,%d,%d,%s,%d,%s,%s,%d,%s,%s,%s,%f,%d,%d,%f,%f,%d\n", allrecords[k].color,allrecords[k].directorName,allrecords[k].numCriticReviews,allrecords[k].duration, allrecords[k].directorFBlikes, allrecords[k].actor3FBlikes, allrecords[k].actor2name,allrecords[k].actor1FBlikes,allrecords[k].gross, allrecords[k].genres, allrecords[k].actor1name, allrecords[k].movieTitle, allrecords[k].numVotedUsers,allrecords[k].castTotalFBlikes, allrecords[k].actor3name,allrecords[k].faceNumberPoster, allrecords[k].plotKeywords, allrecords[k].link, allrecords[k].numUserReviews,allrecords[k].language,allrecords[k].country,allrecords[k].contentRating,allrecords[k].budget,allrecords[k].titleYear,allrecords[k].actor2FBlikes,allrecords[k].imdbScore,allrecords[k].aspectRatio,allrecords[k].movieFBlikes);
	}
*/

	int k;
	for(k=0;k<recordsSize;k++){
		//this if statement takes each title with a "," and puts quotations around it
		if(strchr(allrecords[k].movieTitle,',')){ //detection works fine
		    	char qm1[100] = "";
		    	char qm2[100] = "";
		    	qm1[0] = '\"';
		    	qm2[0] = '\"';
		    	strcat(qm1,allrecords[k].movieTitle);
		    	strcat(qm1,qm2);
		    	allrecords[k].movieTitle = qm1;
		}
	   	fprintf(ds,"%s,%s,%d,%d,%d,%d,%s,%d,%f,%s,%s,%s,%d,%d,%s,%d,%s,%s,%d,%s,%s,%s,%f,%d,%d,%f,%f,%d\n", allrecords[k].color,allrecords[k].directorName,allrecords[k].numCriticReviews,allrecords[k].duration, allrecords[k].directorFBlikes, allrecords[k].actor3FBlikes, allrecords[k].actor2name,allrecords[k].actor1FBlikes,allrecords[k].gross, allrecords[k].genres, allrecords[k].actor1name, allrecords[k].movieTitle, allrecords[k].numVotedUsers,allrecords[k].castTotalFBlikes, allrecords[k].actor3name,allrecords[k].faceNumberPoster, allrecords[k].plotKeywords, allrecords[k].link, allrecords[k].numUserReviews,allrecords[k].language,allrecords[k].country,allrecords[k].contentRating,allrecords[k].budget,allrecords[k].titleYear,allrecords[k].actor2FBlikes,allrecords[k].imdbScore,allrecords[k].aspectRatio,allrecords[k].movieFBlikes);
	}

	printf("\n");
	printf("Total number of threads: %d \n", threadcount);
	
	return 0;
}
