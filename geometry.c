#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SKIP while(i<strlen(a) && a[i]==' ') i++
typedef struct {
	double x;
	double y;
} Point;
typedef struct
{
	Point p;
	double R;
} Circle;

void print_crc(Circle c)
{
   printf("circle(%lf %lf, %lf)\n", c.p.x, c.p.y, c.R);
}
int is_circle(char a[], int comments)
{
    char c[] = "circle(";
    for(int i = 0; i<strlen(a); i++)
    {
       a[i] = tolower(a[i]);
       if(i<7 && c[i]!=a[i])
          {
              if(comments)
              {
                 printf("%s\n",a);
                 printf(" ^ \nNot a circle\n");
              }
              return 0;
          }
    }
    int i = 7, dot = 1;   
    SKIP;
    if(a[i]=='-')
       i++;  
    while(i<strlen(a))
    {
        if(!(isdigit(a[i]) || (dot && a[i] == '.')))
        {
           if(a[i]!=' ')
           {
              if(comments)
              {
                 printf("%s\n",a);
                 for(int j = 0; j<i; j++)
                 printf(" ");
                 printf("^\nwrong symbol\n");
              }
              return 0;
           }
           break;
        }else if(a[i]=='.') dot = 0;        
        i++;   
    }
    dot =1;
    SKIP;

    if(a[i]=='-')
      i++;
    while(i<strlen(a))
    {
        if(!(isdigit(a[i]) || (dot && a[i] == '.')))
        {
           if(a[i]!=' ' && a[i]!=',')
           {
              if(comments)
              {
                 printf("%s\n",a);
                 for(int j = 0; j<i; j++)
                    printf(" ");
                 printf("^\nwrong symbol\n");
              }
              return 0;
           }
           break;
        }else if(a[i]=='.') dot = 0;
        i++;   
    }
    dot =1;
    SKIP;
    if(a[i++]!=',')
    {
       if(comments)
       {
       printf("Have no \',\'\n");
       }
       return 0;
    }
    SKIP;
    if(a[i]=='-')
       i++;
    while(i<strlen(a))
    {
        if(!(isdigit(a[i]) || (dot && a[i] == '.')))
        {
           if(a[i]!=' ' && a[i]!=')')
           {
              if(comments)
              {
                 printf("%s\n",a);
                 for(int j = 0; j<i; j++)
                 printf(" ");
                 printf("^\nwrong symbol\n");
              }
              return 0;
           }
           break;
        }else if(a[i]=='.') dot = 0;
        i++;   
    }
    SKIP;
    if(a[i++]!=')')
    {
       if(comments)
       {
          printf("%s\nHave no ended \')\'\n",a);
       }
       return 0;
    }
    return 1;
}
Circle get_circle(char a[])
{
    Point p1 = {0,0};
    Circle circle = {p1,0};
    int i = 7, k = 0, dot = 1;
    char fl1[255], fl2[255], fl3[255];
    
    SKIP;
    
    if(a[i]=='-')
       fl1[k++]=a[i++];
       
    while(i<strlen(a))
    {
        if(isdigit(a[i]) || (dot && a[i] == '.'))
        {
           fl1[k++]=a[i];
           if(a[i] == '.') dot=0;
        }   
        else
        {
           if(a[i]!=' ')
           {
              return circle;
           }
           break;
        }
        i++;   
    }
    fl1[k]='\0'; k = 0; dot =1;
    SKIP;

    if(a[i]=='-')
       fl2[k++]=a[i++];
    while(i<strlen(a))
    {
        if(isdigit(a[i]) || (dot && a[i] == '.'))
        {
           fl2[k++]=a[i];
           if(a[i] == '.') dot=0;
        }
        else
        {
           if(a[i]!=' ' && a[i]!=',')
           {
              return circle;
           }
           break;
        }
        i++;   
    }
    SKIP;
    if(a[i++]!=',')
    {
       return circle;
    }
    while(i<strlen(a) && a[i]==' ')
    {
       i++;
    }
    fl2[k]='\0'; k=0; dot = 1;
    if(a[i]=='-')
       fl3[k++]=a[i++];
    while(i<strlen(a))
    {
        if(isdigit(a[i]) || (dot && a[i] == '.'))
        {
           fl3[k++]=a[i];
           if(a[i] == '.') dot=0;
        }
        else
        {
           if(a[i]!=' ' && a[i]!=')')
           {
              return circle;
           }
           break;
        }
        i++;   
    }
    SKIP;
    if(a[i++]!=')')
    {
       return circle;
    }
    fl3[k]='\0';
    
    circle.p.x = atof(fl1);
    circle.p.y = atof(fl2);
    circle.R = atof(fl3);
    return circle;
}
int main(int argc, char *argv[]) 
{
        FILE *fp;
  	if(argc!=1)   
  	{
  	   if((fp=freopen(argv[1],"r",stdin))==NULL)
  	      printf("No such file or directory");
  	}
  	else 
  	   printf("введите количество фигур:\n");	
  	char num[255];
  	gets(num);
  	int size = atoi(num);
  	char str[size][255];
  	int count_with_no_errors = 0;
  	for(int i = 0; i<size; i++)
  	{
  	   gets(str[i]);
  	   count_with_no_errors+=is_circle(str[i],1);
  	}
  	Circle masc[count_with_no_errors];
  	printf("\n");
  	int da = 0;
  	for(int i = 0; i<size; i++)
  	{
  	  if(is_circle(str[i],0))
  	      masc[da++]=get_circle(str[i]);
  	}
  	for(int i = 0; i<count_with_no_errors; i++)
  	{
  	   print_crc(masc[i]);
  	}
  	if(fp)
  	{
  	   fclose(fp);
  	}
        return 0;
}
