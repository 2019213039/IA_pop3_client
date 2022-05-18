#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h> 
#include<time.h>

#define SIZE1 6
#define SIZE2 10

int I=0;
clock_t start, stop;// The timer

struct Result
{
	int sCore;
	int utime;
};
	
void idvalidation(char *);//Check the ID format

int operation(int ,int ,int);

int screening(int ,int ,int ,int);
int add(int, int);
int sub(int, int);
int mul(int, int);
int divi(int, int);
int main()
{

	srand(time(NULL));
	int firdigital[SIZE2],secdigital[SIZE2],answdigital[SIZE2],yansw[SIZE2];
	int score=100,choice,t=0;
	int a=0,s=0,m=0,d=0;//Record the number of occurrences of an operation symbol
	char FID[SIZE2],ID[SIZE1],op[SIZE2],oper[SIZE2];
	struct Result r;
	FILE *inFile;

//Strat

	printf("\nWelcome to use my program\n");
	
//First, check the ID format
	
	for(;I!=1;)
	{
		printf("\nPlease input your ID no:");
		scanf("%s",ID);
		idvalidation(ID);
		if(I==0 || strlen(ID)!=6)
		{
			printf("\nThe ID format is incorrect, please re-enter\n");
			I=0;	
		}
	}
	I=0;
	
while(1)
{	
	score=100;// Start all over again
	a=0;
	s=0;
	m=0;
	d=0;
	if ((inFile=fopen("record.txt", "a+"))==NULL)
		{
			printf("Failed to open the file\n");
			exit(1);
		}
	
	t=0; 
	printf("\nPlease choose what you want to do:\n");
	printf("\n(1)   Start a test\n(2)   Check scores\n(3)   Exit\n");
	for(;t==0;)
	{
		scanf("%d",&choice);
		if(choice==1)
		{
			start=clock();
//Then generate the question

	//Generate different operation symbols
	
			for(int i=0;i<10;i++)
			{
				answdigital[i]=0; 
				secdigital[i]=rand()%99+1;
				firdigital[i]=rand()%99+1;	
				op[i]=rand()%4+1;	
				if(i==9)
				{
					if(a==0 || s==0 ||m==0 ||d==0)
					op[i]=screening(a,s,m,d);
					else
					while(op[i]==op[i-1])
					{
						op[i]=rand()%4+1;
					}	
				}
				while(op[i]==op[i-1])
				{
					op[i]=rand()%4+1;
				}
				if(op[i]==1)
				{
					for(;answdigital[i]==0;)
					{
						secdigital[i]=rand()%99+1;
						firdigital[i]=rand()%99+1;
						oper[i]='+';
						answdigital[i]=add(firdigital[i],secdigital[i]);
						if(answdigital[i]!=0)
						a++;
					}
				}
				if(op[i]==2)
				{
					for(;answdigital[i]==0;)
					{
						secdigital[i]=rand()%99+1;
						firdigital[i]=rand()%99+1;
						oper[i]='-';
						answdigital[i]=sub(firdigital[i],secdigital[i]);
						if(answdigital[i]!=0)
						s++;
					}
				}
				if(op[i]==3)
				{
					for(;answdigital[i]==0;)
					{
						secdigital[i]=rand()%99+1;
						firdigital[i]=rand()%99+1;
						oper[i]='*';
						answdigital[i]=mul(firdigital[i],secdigital[i]);
						if(answdigital[i]!=0)
						m++;
					}
				}
				if(op[i]==4)
				{
					firdigital[i]=0;
					for(;firdigital[i]==0;)
					{
						secdigital[i]=rand()%99+1;
						answdigital[i]=rand()%99+1;
						oper[i]='/';
						firdigital[i]=divi(secdigital[i],answdigital[i]);
						if(firdigital[i]!=0)
						d++;
					}
				}
				printf("\n	%d %c %d = ",firdigital[i],oper[i],secdigital[i]);
				scanf("%d",&yansw[i]);
				if(yansw[i]!=answdigital[i])
				score-=10;
			}
	
//Print score 

			stop=clock();
			printf("\nYour score is %d\n",score);
			r.sCore=score;
			r.utime=(int)(stop-start)/CLK_TCK;	
	
//Saves

			fprintf(inFile, "%s		%d		%dseconds\n",ID,r.sCore,r.utime); 
			fclose(inFile);
	
//Print paper information

			printf("\n\n\n	Ques.     | 	Correct Answ.  |  	Ur Answ\n");
			for(int i=0;i<10;i++)
			{
				printf("\n	%d %c %d =  	%d			    	%d\n",firdigital[i],oper[i],secdigital[i],answdigital[i],yansw[i]);
			}
			t=1;
		}
		
		else if(choice==2)
		{
	 		printf("\nYour previous records are:\n");
			while( ! feof(inFile) )
    		{ 
        		char ch,readID[6],second[7];
        		int trash1,trash2; 
        		fscanf(inFile, "%s		%d		%d%s\n", readID, &trash1,&trash2,second);
				for(int i=0;i<6;i++)
				{
					if(readID[i]!=ID[i])
					break;
					if(i==5)
					{
						if(readID[5]==ID[5])
						printf("%s		%d		%d%s\n", readID, trash1,trash2,second);
					}
				}
    		}			
			fclose(inFile);
			t=1;
		}
		else if(choice==3) 
		{
			printf("Thank you for using my program!\n");
			exit(1);	
		}
		else
		printf("\nYour choice is wrong, please choose again\n\n");
	}
	

}
	return 0;
}
////////////////////////////////////////////////////////////////////////

void idvalidation(char *a)
{
	for(int i=0;i<6;i++)
	{
		I=1;
		if(i<=1)
		{
			if(int(*(a+i)) < 65 || int(*(a+i))>90)
			{
				I=0;
				break;
			}
			else
			continue;
		}
		else
		{
			if(int(*(a+i)) < 48 || int(*(a+i)) > 57)
			{
				I=0;
				break;
			}
			else
			continue;	
		}
		
	}	
}

int screening(int X,int Y,int Z,int K)
{
	if(X==0)
	{
		return 1;
	}
	if(Y==0)
	{
		return 2;
	}
	if(Z==0)
	{
		return 3;
	}
	if(K==0)
	{
		return 4;
	}
}

int add(int a, int b)
{
	if(b+a > 0 && b+a < 100)
	return b+a;
	else
	return 0;
}

int sub(int a, int b)
{
	if(a-b >0 && a-b < 100)
	return a-b;
	else
	return 0;
}

int mul(int a, int b)
{
	 if(b*a >0 && b*a < 100)
	return b*a;
	else
	return 0;
}

int divi(int a,int b)
{
	if(a*b >0 && a*b < 100)
	return a*b;
	else
	return 0;
}
