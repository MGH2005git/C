#include <stdio.h>
#define MAX 100

/*======================================================ALPHABETIC FUNCTIONS======================================================*/

int space(int c){
    return (c == ' ' || c == '\t' || c == '\n');
}

int digit(int c){
    return (c >= '0' && c <= '9');
}

int isletter(int c){
    return ((c >= 'A' && c <= 'Z')||(c >= 'a' && c <= 'z'));
}

int isnumber(char s[]){
    int i = 0;
    for(i;s[i]!='\0';i++)
        if(!digit(s[i]))
            return 0;
    return 1;
}

void clearstr(char s[]) {
    s[0] = '\0';
}

int gline(char s[]){
    int i,c;
    for(i=0;i<MAX-1&&((c = getchar())!=EOF)&&c!='\n';i++)
        s[i] = c;
    s[i] = '\0';
    return i;
}

void gline2(char line[]){
    int i = 0,c;
    while(1){
        c = getchar();
        if(c=='\n'||c==EOF){
            line[i] = '\0';
            break;
        }
        if(i<MAX-1)
            line[i++] = c;
        else if(i==MAX-1){
            printf("\tMaximum character reached!\n\n");
            line[i] = '\0';
            while((c = getchar())!='\n'&&c!=EOF);
            break;
        }
    }
}

int getnum(void){
    int c,n = 0;
    while((c = getchar())!='\n'&&c!=EOF)
        if(digit)
            n = 10*n + c - '0';
    return n;
}

void input(char line[MAX][MAX],int index){
    int i = index;
    int c,j = 0;
    while(1){
        while(space(c)&&c!='\n'&&c!=EOF)
            c = getchar();
        if(c==EOF||c=='\n')
            break;
        while(!space(c)&&c!='\n'&&c!=EOF){
            line[i][j++] = c;
            c = getchar();
        }
        line[i][j] = '\0';
        j = 0;
        i++;
    }
    line[i][0] = '\0';
}

void gettoken(const char line[],char token[MAX][MAX]){
    int i = 0,j = 0,k = 0;
    while(line[i]!='\0'){
        while(space(line[i]))
            i++;
        if(line[i]=='\0')
            break;
        while(!space(line[i])&&line[i]!='\0')
            token[j][k++] = line[i++];
        token[j][k] = '\0';
        k = 0;
        j++;
    }
    token[j][0] = '\0';
}

void printstr(const char s[]){
    int i;
    for(i=0;s[i]!='\0';i++)
        putchar(s[i]);
}

int len(const char s[]){
    int i = 0;
    for(i;s[i]!='\0';i++);
    return i;
}

void reverse(char s[]){
    int i,j;
    for(i=0,j=len(s)-1;i<j;i++,j--){
        char t;
        t = s[i];
        s[i] = s[j];
        s[j] = t;
    }
}

void copy(const char from[],char to[],int i1,int i2){
    int i,j=0;
    clearstr(to);
    for(i=i1;i<=i2;i++)
        to[j++]=from[i];
    to[j] = '\0';
}

int strtoint(const char s[]){
    int i = 0,n = 0;
    int sign = 1;
    while(space(s[i]))
        i++;
    if(s[i]=='-'||s[i] == '+'){
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }
    for(i=0;s[i]!='\0';i++)
        if(digit(s[i]))
            n = 10*n + s[i] - '0';
    return sign*n;
}

double strtofloat(const char s[]){
    int i = 0;
    double n = 0.0;
    int sign = 1;
    while(isspace(s[i]))
        i++;
    if(s[i]=='-'||s[i] == '+'){
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }
    for(i;s[i]!='.';i++){
        n = 10*n + s[i] - '0';
    }
    if(s[i]=='.')
        i++;
    double m = 1.0;
    for(i;s[i]!='\0';i++){
        m *= 0.1;
        n += (s[i] - '0')*m;
    }
    return sign*n;
}

void inttostr(int n,char s[]){
    int i = 0;
    if(n == 0){
        s[i++] = '0';
        s[i] = '\0';
        return ;
    }
    int sign = 0;
    if(n<0){
        n = -n;
        sign = -1;
    }
    while(n!=0){
        s[i++] = n % 10 + '0';
        n /= 10;
    }
    if(sign)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int findindex(const char line[],const char s[]){ // THIS ONE IS IMPORTANT
    int i,j = 0;
    int l1 = len(line);
    int l2 = len(s);
    if(l2>l1)
        return -1;
    int flag = 0;
    for(i = 0;i<=l1-l2&&line[i]!='\0';i++){
        if(s[j]==line[i]){
            flag = 1;
            for(j = 0;s[j]!='\0';j++){
                if(s[j]!=line[i+j]){
                    flag = 0;
                    break;
                }
            }
            if(flag) 
                return i;
        }
    }
    return -1;
}

int countchar(const char s[],int c){
    int i;
    int count = 0;
    char t;
    t = c;
    for(i=0;s[i]!='\0';i++)
        if(s[i]==t)
            count++;
    return count;
}

int ispalindrom(const char s[]){
    int i,j;
    for(i=0,j=len(s)-1;i<j;i++,j--){
        if (s[i] != s[j])
            return 0;
    }
    return 1;
}

void Sortstr(char s[]){
    int i,j;
    int l = len(s);
    for(i=0;i<l;i++){
        for(j=0;j<l-1;j++){
            if(s[j]>s[j+1]){
                char t;
                t = s[j];
                s[j] = s[j+1];
                s[j+1] = t;
            }
        }
    }
}

void removespace(char s[]){
    int i,j;
    for(i=0,j=0;s[i]!='\0';i++){
        if(s[i]!='\t'&&s[i]!=' ')
            s[j++] = s[i];
    }
    s[j] = '\0';
}

void cutstring(char s[],int i1,int i2,char t[]){
    int i=0;
    int j = 0;
    while(s[i]!='\0'){
        if(i<i1||i>i2)
            t[j++] = s[i];
        i++;
    }
    t[j] = '\0';
    clearstr(s);
    int k = 0;
    for(k=0;t[k]!='\0';k++)
        s[k] = t[k];
}

void cutstr(char s[],int i1,int i2,char t[]){
    int i,j=0;
    for(i=i1;i<=i2;i++)
        t[j++] = s[i];
    t[j] = '\0';
    clearstr(s);
    for(int i=0;t[i]!='\0';i++)
        s[i] = t[i];
}

int lower(const char c){
    if(c>='A'&&c<='Z')
        return c + 'a' - 'A';
    return c;
}

int checkword(const char s1[],const char s2[]){
    if(len(s1)!=len(s2))
        return 0;
    int i;
    for(i=0;s1[i]!='\0';i++)
        if(lower(s1[i])!=lower(s2[i]))
            return 0;
    return 1;
}

int checkwordCS(const char s1[],const char s2[]){
    if(len(s1)!=len(s2))
        return 0;
    int i;
    for(i=0;s1[i]!='\0';i++)
        if((s1[i])!=(s2[i]))
            return 0;
    return 1;
}

void addstring(const char s1[],const char s2[],char result[]){
    int i = 0;
    for(int j = 0;s1[j]!='\0';j++)
        result[i++] = s1[j];
    for(int k = 0;s2[k]!='\0';k++)
        result[i++] = s2[k];
    result[i] = '\0';
}

/*======================================================NUMERIC FUNCTIONS======================================================*/

int power(long long int a,long long int b){
    long long int p = 1;
    while(b!=0){
        p *= a;
        b--;
    }
    return p;
}

int isprime(int n){
    if(n<=1)
        return 0;
    if(n == 2 || n == 3)
        return 1;
    int t = n % 6;
    int i;
    if(t == 5 || t == 1){
        for(i=3;i*i<=n;i+=2){
            if(n%i==0)
                return 0;
        }
        return 1;
    }
    return 0;
}

int iseven(int n){
    return(n % 2 == 0);
}

void Sort(float s[],int len){
    int i,j;
    for(i=0;i<len;i++){
        for(j=0;j<len-1;j++){
            if(s[j]>s[j+1]){
                float t;
                t = s[j];
                s[j] = s[j+1];
                s[j+1] = t;
            }
        }
    }
}

double dround(double n,int r){
    int sign = 1;
    if(n<0){
        sign = -1;
        n = -n;
    }
    double p = 1;
    while(r!=0){
        p *= 10;
        r--;
    }
    n *= p;
    unsigned int m;
    m = n;
    if(n - m>=0.5)
        m++;
    return sign * (m / p);
}

/*======================================================MAIN FUNCTION======================================================*/

int main(){

    return 0;
}