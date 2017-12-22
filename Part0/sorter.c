/*notes
	when finding "movie_facebook_likes", it reads it as "\tmovie_facebook_likes" when you compare it to argv[2].  This "\t" is believed to be from tabs in the stdin file.  *ask tjang about this*

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "sorter.h"
#include "mergesort.c"

int main(int argc, char ** argv){
	if(argc<3){  //checks if there are enough parameters in this function
		printf("error: not enough arguments \n");
		return 0;
	}

	char str[1000]; //will be the string with the name of all the column headers separated by comma
	fgets(str, 1000, stdin); //puts the columns headers into a big string file

	//this is for output
	char *string1 = strdup(str);
	string1 = trimWhiteSpace(string1);
	puts(string1);

	char *string = strdup(str);
	char * token = strsep(&string, ",");

	while(token != NULL){ //tokenizes the first columns
		token = trimWhiteSpace(token);
		if(strcmp(token,argv[2])==0){
			//printf("found it!! \n");
			break;
		}
    		token = strsep(&string,",");
   	}
	//printf("We are sorting on column: %s\n", token);
	
	if(token == NULL){
		printf("error: no column exists\n");
		return 0;
	}

	int colnum;
	if(strcmp(argv[2],"color")==0){
		colnum = 0;
	}else if(strcmp(argv[2],"director_name")==0){
		colnum = 1;
	}else if(strcmp(argv[2],"num_critic_for_reviews")==0){
		colnum = 2;
	}else if(strcmp(argv[2],"duration")==0){
		colnum = 3;
	}else if(strcmp(argv[2],"director_facebook_likes")==0){
		colnum = 4;
	}else if(strcmp(argv[2],"actor_3_facebook_likes")==0){
		colnum = 5;
	}else if(strcmp(argv[2],"actor_2_name")==0){
		colnum = 6;
	}else if(strcmp(argv[2],"actor_1_facebook_likes")==0){
		colnum = 7;
	}else if(strcmp(argv[2],"gross")==0){
		colnum = 8;
	}else if(strcmp(argv[2],"genres")==0){
		colnum = 9;
	}else if(strcmp(argv[2],"actor_1_name")==0){
		colnum = 10;
	}else if(strcmp(argv[2],"movie_title")==0){
		colnum = 11;
	}else if(strcmp(argv[2],"num_voted_users")==0){
		colnum = 12;
	}else if(strcmp(argv[2],"cast_total_facebook_likes")==0){
		colnum = 13;
	}else if(strcmp(argv[2],"actor_3_name")==0){
		colnum = 14;
	}else if(strcmp(argv[2],"facenumber_in_poster")==0){
		colnum = 15;
	}else if(strcmp(argv[2],"plot_keywords")==0){
		colnum = 16;
	}else if(strcmp(argv[2],"movie_imdb_link")==0){
		colnum = 17;
	}else if(strcmp(argv[2],"num_user_for_reviews")==0){
		colnum = 18;
	}else if(strcmp(argv[2],"language")==0){
		colnum = 19;
	}else if(strcmp(argv[2],"country")==0){
		colnum = 20;
	}else if(strcmp(argv[2],"content_rating")==0){
		colnum = 21;
	}else if(strcmp(argv[2],"budget")==0){
		colnum = 22;
	}else if(strcmp(argv[2],"title_year")==0){
		colnum = 23;
	}else if(strcmp(argv[2],"actor_2_facebook_likes")==0){
		colnum = 24;
	}else if(strcmp(argv[2],"imdb_score")==0){
		colnum = 25;
	}else if(strcmp(argv[2],"aspect_ratio")==0){
		colnum = 26;
	}else if(strcmp(argv[2],"movie_facebook_likes")==0){
		colnum = 27;
	}

	int n = 5100;
	record * records = malloc(sizeof(record)*n);
	int i=0;
	int j=0;
	char * qm = "\"";
	char * symbol = malloc(sizeof(char)*2);

	while(!feof(stdin)){ //goes through EVERY (5000) lines of the file and prints out EVERYTHING from the line
		fgets(str,1000,stdin); //gets input from standard input
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
				strncpy(symbol,string,1); //char for the first char of the string (used to check if theres a quotation mark("))		
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

		if(strlen(array[k])==0){
			//printf("End of input, breaking\n");
			break;
		}
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
		
		printf("%s,%s,%d,%d,%d,%d,%s,%d,%f,%s,%s,%s,%d,%d,%s,%d,%s,%s,%d,%s,%s,%s,%f,%d,%d,%f,%f,%d\n", records[k].color,records[k].directorName,records[k].numCriticReviews,records[k].duration, records[k].directorFBlikes, records[k].actor3FBlikes, records[k].actor2name,records[k].actor1FBlikes,records[k].gross, records[k].genres, records[k].actor1name, records[k].movieTitle, records[k].numVotedUsers,records[k].castTotalFBlikes, records[k].actor3name,records[k].faceNumberPoster, records[k].plotKeywords, records[k].link, records[k].numUserReviews,records[k].language,records[k].country,records[k].contentRating,records[k].budget,records[k].titleYear,records[k].actor2FBlikes,records[k].imdbScore,records[k].aspectRatio,records[k].movieFBlikes);
	}
	

	free(records);
	free(symbol);
	return 0;
}
