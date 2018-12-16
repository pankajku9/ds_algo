#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int validInput( char *str, char *patt);
char * substring ( char * str, int beg , int end);
int getNextState( char *patt, int currState , char x);
int isSuffix( char * str1 , char * str2 );
char charSet[]={'a', 'b', 'c', 'd'};
int ** tarnsTable( char * patt );
void printTransTable( int **sTable, int NumState , int NumChar);
int getIndex(char *charArray, char ch);
int nextState( int ** stable, int cstate, char ch);


int main(){
	int i,j,txtSize,pattSize,nextStateV=0;
	int **tab;
	char * str1="aababacaaababacaasdababaca", *str2="ababaca";
	
	//printf(" Txt:%s patt: %s match at index:%d", str1, str2, index );
	
	printf("\n Substring of  %s for beg: %d , End: %d --> %s ", str2, 2, 4, substring( str2, 2, 4));
	//printf(" IS Suffix aaaaba  aba %d", isSuffix("aaaaba", "abab") );
	txtSize=strlen(str1);
	pattSize=strlen(str2);
	
	tab=tarnsTable(str2);
	printTransTable(tab, 7,4);
	
	for(i=0;i<txtSize;i++){
		nextStateV=nextState(tab,nextStateV,str1[i]);
		if(nextStateV==pattSize)
			printf("\n Str1:%s Str2:%s Match Found at %d", str1,str2, i-pattSize+1);
	}
	return 0;
	
}

int nextState( int ** stable, int cstate, char ch){
	return stable[cstate][getIndex(charSet,ch)];
}

int getIndex(char *charArray, char ch){
	int i;
	for(i=0;i<strlen(charArray);i++){
	if(charArray[i]==ch){
		return i;
	}
	}
}

void printTransTable( int **sTable, int NumState , int NumChar){
	int i,j;
	
	printf(" \n The state \n [  ] ", i);
		
	for(j=0;j<NumChar;j++){
	printf(" %c", charSet[j]);
	}
	for(i=0;i< NumState;i++){
		printf(" \n [%d:] ", i);
		for(j=0;j<NumChar;j++){
			printf(" %d", sTable[i][j]);
		}
	}
}

int ** tarnsTable( char * patt ){
	int ** sTable;
	int i,j,NumState;
	int NumChar=4;
	NumState=strlen(patt)+1;
	sTable=(int**)malloc(NumState*sizeof(int*));
	for(i=0;i<NumState;i++){
	sTable[i]=(int*)malloc(NumChar*sizeof(int));
	}
	
	for(i=0;i<NumState;i++){
		for(j=0;j<NumChar;j++){
			sTable[i][j]=0;
		}
	}
	for(i=0;i<NumState;i++){
		for(j=0;j<NumChar;j++){
			sTable[i][j]=getNextState(patt, i, charSet[j]);
		}
	}
	
	return sTable;
}




 int getNextState( char *patt, int currState , char x){
	int i,k;
	//char probStr[currState+1], prefix[currState+1];
	char *probStr, *prefix;
	probStr=(char*)malloc(sizeof(char)*(currState+2));
	prefix=(char*)malloc(sizeof(char)*(currState+2));
	if(currState!=0)
	strncpy(probStr, patt, currState);
	probStr[currState]=x;
	probStr[currState+1]='\0';
	
	
	
	
	if(strlen(patt)+1 < currState+1 )
		k=strlen(patt)+1;
	else
		k=currState+1;
	
	for(i=k;k>0;k--){
		if(k==0)
		break;
		
		strncpy(prefix, patt, k);
		prefix[k]='\0';
		//printf("\n probStr:%s  prefix:%s K: %d  isSuffix(prefix, probStr): %d" , probStr, prefix , k , isSuffix(prefix, probStr));
		if(isSuffix(prefix, probStr))
		break;
	}
	
	free(probStr);
	free(prefix);
	return k;
	
 }

int isSuffix( char * str1 , char * str2 ) {
	int i,j,s1, s2,suffix=1;
	s1=strlen(str1);
	s2=strlen(str2);
	
	for(i=0,j=s2-s1;i<s1 && j<s2;i++,j++){
		if(str1[i]!= str2[j]){
			suffix=0;
			break;
		}
	}
	
	//printf("\n In IsSuffix str1:%s str2:%s isSuffix:%d", str1, str2, suffix);
	
	return suffix;
	
}


char * substring ( char * str, int beg , int end){
	
	int i, sizeofSubstring=end-beg+2;
	if(end<beg)
		return NULL;
	char *sstr=(char*)malloc((sizeofSubstring+1)*sizeof(char));
	memset(sstr, '\0', sizeofSubstring+1);
	for(i=beg; i<=end; i++)
		sstr[i-beg]=str[i];
	//memcpy(sstr, str, sizeofSubstring);
	return sstr;
}

int validInput( char *txt, char *patt){
	
	int invalid=0;
	
	char * emptystr="";
	
	// NULL String
	if( txt==NULL || patt==NULL)
		invalid=1;
	
	// Empty string
		if( !strcmp(txt,emptystr) || !strcmp(patt,emptystr))
		invalid=1;
	// unintialized string
	
	//inavalid string
	
	//pattern greater than text
	if(strlen(patt)>strlen(txt))
		invalid=1;
	
	if(invalid){
	printf("\n:invalid Input");
	return 0;	
	}
	else
	return 1;
}

