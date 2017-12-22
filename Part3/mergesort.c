/*
	more switch statements to figure out which column to sort by?
*/


int firstString(char * s1, char * s2){ //compares to strings alphabetically and returns the alphabetically first string
	
	if(strcmp(s1,s2)>0){	//this means s1 is alphabetically first
		return 0;	
	}else{			//this means that s2 was alphabetically first;
		return 1;
	}
}

/*
int firstString(char * string1, char * string2){

   	// temporary strings

	int n1 = strlen(string1);
	int n2 = strlen(string2);
	char* temp1 = malloc(sizeof(char)*n1);
	char* temp2 = malloc(sizeof(char)*n2);
	
	int i;
	for(i = 0; i < strlen(string1); i++){ //converts string 1 into lowercase
		temp1[i] = tolower(string1[i]);
	}
	
	for(i = 0; i < strlen(string2); i++){ //converts string 2 into lowercase
		temp2[i] = tolower(string2[i]);
	}
	
	if(strcmp(temp1,temp2)<0 || strcmp(temp1,temp2) == 0){	//this means temp1 is alphabetically first
		return 1;	
	}else{			//this means that temp2 was alphabetically first;
		return 0;
	}
}
*/

void NUMmerge(record * arr, int l, int m, int r, int colnum){
    	int i, j, k;
    	int n1 = m - l + 1; 	//size of left array
    	int n2 =  r - m;	//size of right array
 
    	record * tempL = malloc(sizeof(record)*n1); 		//temp arrays
	record * tempR = malloc(sizeof(record)*n2);	

    	for (i = 0; i < n1; i++){	//copy data to temp arrays
        	tempL[i] = arr[l+i];
	}
    	for (j = 0; j < n2; j++){
        	tempR[j] = arr[m+1+j];
	}
	
    	/* merge back into temp array*/
    	i = 0; // first index of first subarray
    	j = 0; // first index of second subarray
    	k = l; // first index of merged subarray

	switch(colnum){
		case(0):
			//CHAR
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
				int result = firstString(tempL[i].color,tempR[j].color);
        			if (result == 1){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(1):
			//CHAR
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
				int result = firstString(tempL[i].directorName,tempR[j].directorName);
        			if (result == 1){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(2): //INT
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].numCriticReviews <= tempR[j].numCriticReviews){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(3)://INT
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].duration <= tempR[j].duration){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(4): //INT
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].directorFBlikes <= tempR[j].directorFBlikes){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(5): //INT
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].actor3FBlikes <= tempR[j].actor3FBlikes){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(6):
			//CHAR
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
				int result = firstString(tempL[i].actor2name,tempR[j].actor2name);
        			if (result == 1){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(7): //INT
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].actor1FBlikes <= tempR[j].actor1FBlikes){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(8): //FLOAT/DOUBLE
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].gross <= tempR[j].gross){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(9):
			//CHAR
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
				int result = firstString(tempL[i].genres,tempR[j].genres);
        			if (result == 1){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(10):
			//CHAR
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
				int result = firstString(tempL[i].actor1name,tempR[j].actor1name);
        			if (result == 1){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(11): //CHAR
			//printf("working \n");
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
				int result = firstString(tempL[i].movieTitle,tempR[j].movieTitle);
        			if (result == 1){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(12): //INT
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].numVotedUsers <= tempR[j].numVotedUsers){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;		
		case(13): //INT
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].castTotalFBlikes <= tempR[j].castTotalFBlikes){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(14):
			//CHAR
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
				int result = firstString(tempL[i].actor3name,tempR[j].actor3name);
        			if (result == 1){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;	
		case(15): //INT
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].faceNumberPoster <= tempR[j].faceNumberPoster){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(16):
			//CHAR
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
				int result = firstString(tempL[i].plotKeywords,tempR[j].plotKeywords);
        			if (result == 1){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;	
		case(17):
			//CHAR
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
				int result = firstString(tempL[i].link,tempR[j].link);
        			if (result == 1){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;		
		case(18): //INT
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].numUserReviews <= tempR[j].numUserReviews){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;	
		case(19):
			//CHAR
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
				int result = firstString(tempL[i].language,tempR[j].language);
        			if (result == 1){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;		
		case(20):
			//CHAR
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
				int result = firstString(tempL[i].country,tempR[j].country);
        			if (result == 1){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(21):
			//CHAR
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
				int result = firstString(tempL[i].contentRating,tempR[j].contentRating);
        			if (result == 1){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(22): //FLOAT/DOUBLE
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].budget <= tempR[j].budget){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(23): //INT
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].titleYear <= tempR[j].titleYear){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(24): //INT
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].actor2FBlikes <= tempR[j].actor2FBlikes){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(25): //FLOAT/DOUBLE
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].imdbScore <= tempR[j].imdbScore){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(26): //FLOAT/DOUBLE
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].aspectRatio <= tempR[j].aspectRatio){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
		case(27): //INT
			while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        			if (tempL[i].movieFBlikes <= tempR[j].movieFBlikes){
            				arr[k] = tempL[i];	
            				i++;
        			}else{
            				arr[k] = tempR[j];
            				j++;
        			}
        			k++;
    			}
			break;
	}

	/*
	//original white loop just here in case errors
    	while (i < n1 && j < n2){ //sees if i or j is larger and puts the smallest one into temp
        	if (tempL[i].movieFBlikes <= tempR[j].movieFBlikes){
            		arr[k] = tempL[i];	
            		i++;
        	}else{
            		arr[k] = tempR[j];
            		j++;
        	}
        	k++;
    	}
	*/ 

    	//copy remaining elements of tempL[], if there are any
    	while (i < n1){
        	arr[k] = tempL[i];
        	i++;
        	k++;
    	}
 	//same thing but with tempR[]
    	while (j < n2){
        	arr[k] = tempR[j];
        	j++;
        	k++;
    	}
	free(tempL);
	free(tempR);
}

void NUMmergeSorter(record * arr, int l, int r , int colnum ){
    	if (l < r){
    		int m = l+(r-l)/2; //round down if m is a decimal (i.e 4.5 -> 4)
    		// sort first and second halves
    		NUMmergeSorter(arr, l, m,colnum);		//split the left sub arrays
    		NUMmergeSorter(arr, m+1, r,colnum);		//split the right sub arrays
    		NUMmerge(arr, l, m, r, colnum);			//compares two sub-arrays and sorts them in arr
    	}
}

record * mergesort(record * records, int colnum, int size){ //splits array into arrays of one
	
	switch(colnum){
		case(0):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(1):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(2):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(3):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(4):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(5):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(6):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(7):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(8):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(9):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(10):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(11):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(12):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;		
		case(13):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(14):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;	
		case(15):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(16):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;	
		case(17):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;		
		case(18):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;	
		case(19):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;		
		case(20):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(21):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(22):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(23):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(24):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(25):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(26):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
		case(27):
			NUMmergeSorter(records,0,size-1 ,colnum);
			break;
	}
	return records;
}
