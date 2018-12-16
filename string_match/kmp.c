#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int validInput( char *str, char *patt);
char * substring ( char * str, int beg , int end);

int * computeLPS( char * patt);
void KMPMatch( char *txt, char *patt, int * LPS);


int main(){
	int i,j,txtSize,pattSize,nextStateV=0;
	int *LPS;
	char * str1="aababbabaababb", *str2="abcabcabab";
	
	
	txtSize=strlen(str1);
	pattSize=strlen(str2);
	
	LPS=computeLPS(str2);
	printf("\n Patt:%s LPS:", str2);
	for(i=0;i<pattSize;i++)
	{
		printf(" %d", LPS[i]);
	}
	
	KMPMatch(str1,str2, LPS);

	free(LPS);
	
	return 0;
	
}
void KMPMatch( char *txt, char *patt, int* LPS){
	int i=0,j=0,p,t;
	p=strlen(patt);
	t=strlen(txt);
	while(i<t){
		if(txt[i]== patt[j]){
				j++;
				i++;
		}
		else{
			if(j!=0)
				j=LPS[j-1];
			else
				i++;
			} 
		if(j==p){
			printf("\n Match Found %d", i-j+1);
			j=LPS[j-1];
		}
			
		printf("\n NExti:%d Nextj:%d",i,j);
	}
}

int * computeLPS( char * patt){
	int i=1,j=0 , x=0;
	int pSize=strlen(patt);
	int *LPS=(int*)malloc(pSize*(sizeof(int)));
	LPS[0]=0;
	
	for(i=1;i<pSize;i++){
		
		printf("\n CURSTR(%d):",i);
		for(x=0;x<=i;x++){
			printf("%c", patt[x]);
		}
		printf(" LPS(%d):" ,j);
		for(x=0;x<=j;x++){
			printf("%c", patt[x]);
		}
		
		printf(" J: ");
		while( (patt[i]!= patt[j]) && j>0){
				j=LPS[j-1];
				printf("%d ", j);
		}
		if(patt[i]==patt[j]){
			j++;
			LPS[i]=j;
			printf("%d ", j);
		}
		
		if(j==0){
			LPS[i]=j;
			printf("%d ", j);
		}
		
		
		
	}
	return LPS;
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

