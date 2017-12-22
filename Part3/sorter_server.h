/*
enum column{
	color,
	director_name,
	num_critic_for_reviews,
	duration,
	director_facebook_likes,
	actor_3_facebook_likes,
	actor_2_name,
	actor_1_facebook_likes,
	gross,
	genres,
	actor_1_name,
	movie_title
};
*/


typedef struct record{
	char * color;
	char * directorName;
	int numCriticReviews;
	int duration;
	int directorFBlikes;
	int actor3FBlikes;
	char * actor2name;
	int actor1FBlikes;
	int gross;
	char * genres;
	char * actor1name;
	char * movieTitle;
	int numVotedUsers;
	int castTotalFBlikes;
	char * actor3name;
	int faceNumberPoster;
	char * plotKeywords;
	char * link;
	int numUserReviews;
	char * language;
	char * country;
	char * contentRating;
	int budget;
	int titleYear;
	int actor2FBlikes;
	double imdbScore;
	double aspectRatio;
	int movieFBlikes;
}record;


char *trimWhiteSpace(char *str){ //gets rid of white space (including /r and /t as a bonus)
  	char *end;

  	// Trim leading space
  	while(isspace((unsigned char)*str)) str++;

  	if(*str == 0)  // All spaces?
    		return str;

  	// Trim trailing space
  	end = str + strlen(str) - 1;
  	while(end > str && isspace((unsigned char)*end)) end--;

  	// Write new null terminator
  	*(end+1) = 0;

  	return str;
}

void trim(char* token) {
   
    if(token[0] == ' '){ //leading white spaces
       
        int i, j;
        for(i = 0; token[i] == ' '; i++);
       
        for(j = 0; token[i+j] != '\0'; j++){
            token[j] = token[i+j];
        }
       
        token[j] = '\0';
       
    }
   
    if(token[strlen(token)] == ' ' || token[strlen(token)] == '\0'){ //trailing white spaces
       
        int i = strlen(token);
       
        while(token[i] == ' ' || token[i] == '\0'){
            i--;
        }
       
        token[i + 1] = '\0';
       
    }
   
} //end of 'trim' function
