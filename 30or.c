
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define N 20
#define M 20

int findTerm(float a[N][M],float b[],int minindex);
void show (float c[],float b[],float a[][M]);
void show2(float c[M]);

int terms;
int constraint;
int i,j;
int main(){
  float c[M];
  //coeff of the objective function
  float a[N][M];//co-efficent of the constraints
  float b[N];// RMS of constraints

  float z=0;
  int flag=0;
  int flag1=0;
  int flag2=0;
  int minindex=-1;
  float minrow;
  float divid;
  float multi;
  float multi1;
  int temp1;
  //////////////////////////
  for(i=0;i<M;i++)
    c[i]=0;
  for(i=0;i<N;i++)
    for(j=0;j<M;j++)
      a[i][j]=0;
  //////////////////////////
  printf("\nHiiiii\nThis is Simplex algorithm program\n");
  printf("\nEnter number of terms in Z function\n");
  scanf("%d",&terms);
  //////////////////////////////////////////////////////////
  printf("\nEnter the coeff of objective function\n");
  for(i=0;i<terms;i++)
    scanf("%f",&c[i]);
  printf("\nObjective function :\n");
  printf("\nMax z = ");
  for(i=0;i<terms;i++)//for  2x1+4x2+.....
  {
    if(i==0)
      printf("%g*x%d",c[i],i+1);
    else
      printf(" + %g*x%d",c[i],i+1);
  }
  /////////////////////////////////////////////////////
  for(i=0;i<terms;i++)
	  c[i]=(-1)*c[i];

  /////////////////////////////////////////////////////

  printf("\nEnter number of constraint\n");
  scanf("%d",&constraint);
  printf("\nEnter the coeff of constraints\n");
  for(i=0;i<constraint;i++)
    for(j=0;j<terms;j++)
      scanf("%f",&a[i][j]);
  for(i=0;i<constraint;i++)// 1 baraye zaribe x haye ezafi dar a
    a[i][j++]=1;


  printf("\nEnter RMS of constraints\n");
  for(i=0;i<constraint;i++)
    scanf("%f",&b[i]);

  printf("\nConstraints:\n");
  for(i=0;i<constraint;i++)
  {
    for(j=0;j<terms;j++)
    {
      if(j==0)
        printf(" %g*x%d ",a[i][j],j+1);
      else
        printf(" + %g*x%d ",a[i][j],j+1);
    }
    printf(" <= %g\n",b[i]);
  }
  printf("\n\n");
    //return 0;
  ////////////////////////////////////////baraye gozashtane bi va z sare jashun tu jadval
  c[constraint+terms]=z;
  for(i=0;i<constraint;i++){
	  a[i][constraint+terms]=b[i];
  }

  show(c,b,a);
  getch();

  //////////////////////////////////////////
  while(1){//akharesh inja ro bayad 1 ya true konam
      flag2=0;
	  minrow=c[0];
	  minindex=0;
	  //sharte payan
	  for(i=0;i<(constraint+terms);i++){//be tedade moteghayeramun va mohasebeye mine satre aval
		  if( c[i]<0 ){
			  flag2=1;
			  //minindex=i;
			  if(minrow>c[i]){
				  minrow=c[i];
				  minindex=i;
			  }
		  }
	  }
	  //printf("min = %0.2g\n",minrow);
	  //printf("minrow = %0.2f\n",minrow);
	  if( flag2==0 )//yani dar satre aval manfi nadashtim
		  break;

	  temp1=findTerm(a,b,minindex);
	  if( temp1==-1 ){// pas noghteye (temp,minindex) bayad 1 shavad
		  printf(" the coeff of constrant is negativ or zero ");
		  break;
	  }// inja chun motmaenin sefr nist pas dige un sharto chek nemikonam vase baadesh

	  divid=a[temp1][minindex];
	  for(i=0;i<(constraint+terms+1);i++){//vase khate minindex row ...1 vase RHT
		  a[temp1][i] = (a[temp1][i])/divid;
	  }
////////////////////////////////////////////////////virayesh shod +1 ----->> hazf shod
	  for(j=0;j<constraint;j++){//vase khat haye dige ke be forme canonical darare
		  if(j!=temp1){
			  if(a[j][minindex]!=0){//bejaye o bayad j bashe
			      multi1=(-1)*(a[j][minindex]);
				  for(i=0;i<(constraint+terms+1);i++){
					  a[j][i]=((a[temp1][i])*(multi1))+a[j][i]; //bejaye 0 hamun j
				  }
			  }
		  }
	  }

	  for(i=0;i<constraint;i++){// for update b[]
	      b[i]=a[i][constraint+terms];
	  }

	  if(c[minindex]!=0){//vase khate aval ke c[] hast
	      multi=(-1)*(c[minindex]);
		  for(i=0;i<(constraint+terms+1);i++){
			  c[i]=((a[temp1][i])*(multi))+c[i]; //bejaye 0 hamun j
		  }
	  }
	  printf("Max z=%.2f\n\n\n",c[constraint+terms]);
      show(c,b,a);
  }
  //printf("Max z=%0.2g\n",c[constraint+terms]);
  //printf("Max z=%.2f\n\n",c[constraint+terms]);
  //show(c,b,a);
  getch();
  while(1)
	  getch();
  return 0;
}

int findTerm(float a[N][M],float b[],int minindex){
	int itemp=-1;
	float ftemp=1000;
	for(i=0;i<constraint;i++){
		if(a[i][minindex]>0){
			if( ( (b[i])/(a[i][minindex]) ) < ftemp  ){
				ftemp=(b[i])/(a[i][minindex]);
				itemp=i;
			}
		}

	}
	/*
	int ntemp=0;
	for(i=0;i<constraint;i++){
        if(a[i][minindex]<0){
            ;
        }
        else if(a[i][minindex]==0){
            ntemp++;
        }

		else if(a[i][minindex]>0){
			if( ( (b[i])/(a[i][minindex]) ) < ftemp  ){
				ftemp=(b[i])/(a[i][minindex]);
				itemp=i;
			}
		}

	}

	*/
	return itemp;

}

void show (float c[N],float b[N],float a[N][M])
{
  int i,j;
  show2(c);
  for(i=0;i<constraint;i++)
  {
    for(j=0;j<(constraint+terms+1);j++)
      printf("%0.3g\t",a[i][j]);
    printf("\n");
  }
}
void show2(float c[M])
{
  int i;
  for(i=0;i<(constraint+terms);i++)
    printf("x[%d]\t",i+1);
  printf("RMS\n");
  for(i=0;i<(constraint+terms+1);i++)
    printf("%0.2g\t",c[i]);
  printf("\n");

}
