#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void stripzeros(char *result);
static void merge_sort(char **arr,int beg,int end);
static void merge(char **arr,int beg,int mid,int end);


int intal_compare( const char* intal1, const char* intal2)
{
  int a=strlen(intal1);
  int b=strlen(intal2);
  //Check based on length
  if(a>b)
    return 1;
  else if(a<b)
    return -1;
  else
  {
    int n1,n2;
    int flag=1;
    for(int i=0;i<a;i ++)
    {
      n1=intal1[i]-'0';
      n2=intal2[i]-'0';
      if(n1!=n2)
      {
        flag=0;
        break;
      }
    }
    if(!flag)
    {
      if(n1>n2)
      {
        return 1;
      }
      if(n1<n2)
      {
        return -1;
      }
    }
    else
      return 0;
  }
}

char* intal_add(const char* intal1, const char* intal2)
{
  char *result=(char *)malloc(1001*sizeof(char));
  int c=0;
  char *greater=(char *)malloc(1001*sizeof(char));
  strcpy(greater,intal1);
  char *lesser=(char *)malloc(1001*sizeof(char));;
  strcpy(lesser,intal2);
  int a=strlen(greater);
  int b=strlen(lesser);
  if(a<b)
  {
    strcpy(greater,intal2);
    strcpy(lesser,intal1);
    a=strlen(greater);
    b=strlen(lesser);
  }
  int j=a-1;
  for(int i=b-1;i>=0;i--)
  {
    int n1=greater[j]-'0';
    int n2=lesser[i]-'0';
    int sum=n1+n2+c;
    c=sum/10;
    sum=sum%10;
    result[j]=sum+'0';
    j--;
  }
  while(j!=-1)
  {
    int n1=greater[j]-'0';
    int sum=n1+c;
    c=sum/10;
    sum=sum%10;
    result[j]=sum+'0';
    j--;
  }
  if(c)//if carry is still left over after all the digits are added
  {
    for(int i=a;i>=1;i--)
    {
      result[i]=result[i-1];
    }
    result[0]=c+'0';
    result[a+1]='\0';
  }
  else
  {
    result[a]='\0';
  }
  free(greater);
  free(lesser);
  return result;
}


char* intal_diff(const char* intal1, const char* intal2)
{
  char *result=(char *)malloc(1001*sizeof(char));
  char *greater=(char *)malloc(1001*sizeof(char));
  strcpy(greater,intal1);
  char *lesser=(char *)malloc(1001*sizeof(char));
  strcpy(lesser,intal2);
  int a=strlen(greater);
  int b=strlen(lesser);
  int index=intal_compare(intal1,intal2);
  if(index==0)
  {
    strcpy(result,"0");
    free(greater);
    free(lesser);
    return result;
  }
  if(index==-1)
  {
    strcpy(greater,intal2);
    strcpy(lesser,intal1);
    a=strlen(greater);
    b=strlen(lesser);
  }
  int j=a-1;
  int flag=0;//used to check if the previous subtraction had a borrow or not
  for(int i=b-1;i>=0;i--)
  {
    int n1=greater[j]-'0';
    int n2=lesser[i]-'0';
    if(flag)
      n2++;
    if(n1<n2)
    {
      int diff=n1+10-n2;
      result[j]=diff+'0';
      flag=1;
    }
    else if(n1>=n2)
    {
      int diff=n1-n2;
      result[j]=diff+'0';
      flag=0;
    }
    j--;
  }
  while(j!=-1)
  {
    int n1=greater[j]-'0';
    if(n1==0 && flag)
    {
      n1=9;
    }
    else if(flag)
    {
      n1--;
      flag=0;
    }
    result[j]=n1+'0';
    j--;
  }
  result[a]='\0';
  stripzeros(result);
  free(greater);
  free(lesser);
  return result;
}

void stripzeros(char* result)
{
  int count=0;
  for(int i=0;i<strlen(result);i++)
  {
    if(result[i]-'0'!=0)
      break;
    else
      count++;
  }
  if(count!=0)
  {
    int j=0;
    for(int i=count;i<strlen(result);i++)
    {
      result[j]=result[i];
      j++;
    }
    result[j]='\0';
  }
}

char* intal_multiply(const char* intal1, const char* intal2)
{
  char *result=(char *)malloc(1001*sizeof(char));
  strcpy(result,"0");
  char *greater=(char *)malloc(1001*sizeof(char));
  strcpy(greater,intal1);
  char *lesser=(char *)malloc(1001*sizeof(char));
  strcpy(lesser,intal2);
  int a=strlen(greater);
  int b=strlen(lesser);
  int index=intal_compare(intal1,intal2);
  if(index==-1)
  {
    strcpy(greater,intal2);
    strcpy(lesser,intal1);
    a=strlen(greater);
    b=strlen(lesser);
  }
  for(int i=b-1;i>=0;i--)
  {
    int n2=lesser[i]-'0';
    char *temp=(char *)malloc(1001*sizeof(char));
    int a1=a;
    int c=0;
    for(int j=a-1;j>=0;j--)
    {
      int n1=greater[j]-'0';
      int sum=n1*n2+c;
      c=sum/10;
      sum=sum%10;
      temp[j]=sum+'0';
    }
    for(int k=b-1-i;k>0;k--)//adds zeros to the right side
    {
      temp[a1]=0+'0';
      a1++;
    }
    if(c)
    {
      for(int i=a1;i>=1;i--)
      {
        temp[i]=temp[i-1];
      }
      temp[0]=c+'0';
      temp[a1+1]='\0';
    }
    else
    {
      temp[a1]='\0';
    }
    char *temp2=intal_add(result,temp);
    strcpy(result,temp2);
    free(temp);
    free(temp2);
  }
  free(greater);
  free(lesser);
  return result;
}

char* intal_factorial(unsigned int n)
{
  char *result=(char *)malloc(1001*sizeof(char));
  strcpy(result,"1");
  char *one=(char *)malloc(1*sizeof(char));
  strcpy(one,"1");
  if(n==0)
    return "1";
  char *check=(char *)malloc(1001*sizeof(char));
  strcpy(check,"2");
  for(int i=2;i<=n;i++)
  {
    char *temp=intal_multiply(result,check);
    strcpy(result,temp);
    free(temp);
    char *temp2=intal_add(check,one);
    strcpy(check,temp2);
    free(temp2);
  }
  free(one);
  free(check);
  return result;
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{
  char **C = (char**) malloc((k+1)* sizeof(char*));
	for(int i=0;i<=k;i++)
  {
		C[i] = (char*) malloc(1001 * sizeof(char));
    strcpy(C[i],"0");
	}
  strcpy(C[0],"1");
  for(int i=1;i<=n;i++)
  {
    int min=k;
    if(i<k)
    {
      min=i;
    }
    for(int j=min;j>0;j--)
    {
      char *temp=intal_add(C[j],C[j-1]);
      strcpy(C[j],temp);
      free(temp);
    }
  }
  char *result=(char*) malloc(1001 * sizeof(char));
  strcpy(result,C[k]);
  free(C);
  return result;
}

char* intal_pow(const char* intal1, unsigned int n)
{
  if(n==0)
    return "1";
  char *temp=intal_pow(intal1,n/2);
  if(n%2==0)
  {
    char *mul=intal_multiply(temp,temp);
    return mul;
  }
  else
  {
    char *mul1=intal_multiply(intal1,temp);
    char *mul2=intal_multiply(mul1,temp);
    free(mul1);
    return(mul2);
  }
}

void intal_sort(char **arr,int n)
{
  int a=0;
  merge_sort(arr,a,n-1);
}

void merge_sort(char **arr,int beg,int end)
{
  if(beg<end)
  {
    int mid=beg+(end-beg)/2;
    merge_sort(arr,beg,mid);
    merge_sort(arr,mid+1,end);
    merge(arr,beg,mid,end);
  }
}

void merge(char **arr,int beg,int mid,int end)
{
  int n1=mid-beg+1;
  int n2=end-mid;
  char *L[n1];
  char *R[n2];
  for(int i=0;i<n1;i++)
  {
    L[i]=arr[beg+i];
  }
  for(int i=0;i<n2;i++)
  {
    R[i]=arr[mid+1+i];
  }
  int i=0;
  int j=0;
  int k=beg;
  while(i<n1 && j<n2)
  {
    int c=intal_compare(L[i],R[j]);
    if(c==-1||c==0)
    {
      arr[k]=L[i];
      i++;
    }
    else
    {
      arr[k]=R[j];
      j++;
    }
    k++;
  }
  while(i<n1)
  {
    arr[k]=L[i];
    i++;
    k++;
  }
  while(j<n2)
  {
    arr[k]=R[j];
    j++;
    k++;
  }
}

int intal_search(char **arr, int n, const char* key)
{
  int i;
  for(i=0;i<n;i++)
  {
    int c=intal_compare(arr[i],key);
    if(c==0)
      return i;
  }
  return -1;
}

int intal_binsearch(char **arr, int n, const char* key)
{
  int beg=0;
  int end=n-1;
  while (beg<=end)
  {
    int mid = beg+(end-beg)/2;
    if (intal_compare(arr[mid],key)==0)
      return mid;
    if (intal_compare(arr[mid],key)==-1)
      beg=mid+1;
    else
      end=mid-1;
  }
  return -1;
}

char* intal_fibonacci(unsigned int n)
{
  char **fib = (char**) malloc((n+1) * sizeof(char*));
	for(int i = 0; i <= n; i++)
  {
		fib[i] = (char*) malloc(1001 * sizeof(char));
	}
  strcpy(fib[0],"0");
  strcpy(fib[1],"1");
  int j=2;
  while(j<=n)
  {
    fib[j]=intal_add(fib[j-1],fib[j-2]);
    j++;
  }
  char *result=(char*) malloc(1001 * sizeof(char));
  strcpy(result,fib[n]);
  free(fib);
  return result;
}

int intal_max(char **arr, int n)
{
  int i;
  int m=0;
  for(i=1;i<n;i++)
  {
    int c=intal_compare(arr[i],arr[m]);
    if(c==1)
    {
      m=i;
    }
  }
  return m;
}

int intal_min(char **arr, int n)
{
  int i;
  int m=0;
  for(i=1;i<n;i++)
  {
    int c=intal_compare(arr[i],arr[m]);
    if(c==-1)
    {
      m=i;
    }
  }
  return m;
}

char* coin_row_problem(char **arr, int n)
{
  char **a = (char**) malloc((n+1) * sizeof(char*));
	for(int i=0;i<=n;i++)
  {
		a[i] = (char*) malloc(1001 * sizeof(char));
	}
  strcpy(a[0],"0");
  strcpy(a[1],arr[0]);
  for(int i=1;i<n;i++)
  {
    char *temp=intal_add(arr[i],a[i-1]);
    int c=intal_compare(temp,a[i]);
    if(c==1||c==0)
    {
      strcpy(a[i+1],temp);
    }
    else
    {
      strcpy(a[i+1],a[i]);
    }
    free(temp);
  }
  char *result=(char*) malloc(1001 * sizeof(char));
  strcpy(result,a[n]);
  free(a);
  return result;
}

char* intal_mod(const char* intal1, const char* intal2)
{
  char *greater=(char *)malloc(1001*sizeof(char));
  strcpy(greater,intal1);
  char *lesser=(char *)malloc(1001*sizeof(char));
  strcpy(lesser,intal2);
  int a=strlen(greater);
  int b=strlen(lesser);
  for(int i=b;i<a;i++)
  {
    lesser[i]='0';
  }
  lesser[a]='\0';
  while(intal_compare(greater,intal2)!=-1)
  {
    while(intal_compare(greater,lesser)!=-1)
    {
      char *temp=intal_diff(greater,lesser);
      strcpy(greater,temp);
      free(temp);
    }
    int c=strlen(lesser);
    lesser[c-1]='\0';
  }
  char *result=(char *)malloc(1001*sizeof(char));
  strcpy(result,greater);
  free(lesser);
  free(greater);
  return result;
}


char* intal_gcd(const char* intal1, const char* intal2)
{
  char *greater=(char *)malloc(1001*sizeof(char));
  strcpy(greater,intal1);
  char *lesser=(char *)malloc(1001*sizeof(char));;
  strcpy(lesser,intal2);
  if(intal_compare(greater,"0")==0 && intal_compare(lesser,"0")==0)
  {
    return "0";
  }
  if(intal_compare(greater,"0")==0)
  {
    free(greater);
    return lesser;
  }
  if(intal_compare(lesser,"0")==0)
  {
    free(lesser);
    return greater;
  }
  while(intal_compare(lesser,"0")!=0)
  {
    char *remainder=intal_mod(greater,lesser);
    strcpy(greater,lesser);
    strcpy(lesser,remainder);
    free(remainder);
  }
  free(lesser);
  return greater;
}

//extra functionality for division
char* intal_division(const char* intal1, const char* intal2)
{
  char *greater=(char *)malloc(1001*sizeof(char));
  strcpy(greater,intal1);
  char *lesser=(char *)malloc(1001*sizeof(char));;
  strcpy(lesser,intal2);
  int a=strlen(greater);
  int b=strlen(lesser);
  for(int i=b;i<a;i++)
  {
    lesser[i]='0';
  }
  lesser[a]='\0';
  char *result=(char *)malloc(1001*sizeof(char));
  int j=0;
  while(intal_compare(greater,intal2)!=-1)
  {
    int i=0;
    while(intal_compare(greater,lesser)!=-1)
    {
      char *temp=intal_diff(greater,lesser);
      strcpy(greater,temp);
      free(temp);
      i++;
    }
    result[j]=i+'0';
    j++;
    int c=strlen(lesser);
    lesser[c-1]='\0';
  }
  result[j]='\0';
  free(lesser);
  free(greater);
  return result;
}
