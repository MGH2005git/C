#include <stdio.h>
#define MAX 50

/*======================================================================NOTE======================================================================*/
//  hexadecimal are signed by 0x at the begining and the letters inside must be captal : 0xA00192F;
//  binary numbers are sorted in string in correct order e.g 01011 is 10 ;
// ONLY SIGNED BINARIES // first bit is zero --> positive : 01011 is +11 ; first bit is 1 --> negative : 1111 is -7
// VERY IMPORTANT NOTE : bin[len] = '\0';
/*================================================================================================================================================*/

int len(char s[]){
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

int digit(int c){
    return (c>='0'&&c<='9');
}

int isletter(int c){
    return ((c>='A'&&c<='Z')||(c>='a'&&c<='z'));
}

void clearstr(char s[]){
    s[0] = '\0';
}

void copy(char from[],char to[]){
    int i,j = 0;
    clearstr(to);
    for(i=0;from[i]!='\0';i++)
        to[j++] = from[i];
    to[j] = '\0';
}

int gline(char line[]){
    int i,c;
    for(i=0;((c = getchar())!='\n')&&c!=EOF;i++){
        line[i] = c;
    }
    line[i] = '\0';
}

/*=====================================================================UNSIGED====================================================================*/

void unsigeddecimaltobin(char bin[],int n){
    clearstr(bin);
    if(n==0){
        bin[0] = '0';
        bin[1] = '\0';
        return;
    }
    int i = 0;
    while(n!=0){
        bin[i++] = n%2 + '0';
        n /= 2;
    }
    bin[i] = '\0';
    reverse(bin);
}

/*================================================================================================================================================*/

void padzero(char bin[],int maxlen){ // T
    int i = len(bin);
    reverse(bin);
    for(i;i<maxlen;i++)
        bin[i] = '0';
    bin[i] = '\0';
    reverse(bin);
}

int findmsb(char bin[]){ // find most significant bit
    int i = 0;
    for(i;i<len(bin);i++)
        if(bin[i]=='1')
            return i;
    return -1;
}

void unpadzero(char bin[],int maxlen){ // T
    int i = len(bin)-1;
    int j = 0;
    char temp[MAX];
    clearstr(temp);
    for(j;j<maxlen;j++){
        temp[j] = bin[i--];
    }
    temp[j] = '\0';
    reverse(temp);
    copy(temp,bin);
}

void onescomplement(char bin[]){ // T
    int i;
    for(i=0;i<len(bin);i++){
        if(bin[i]=='1')
            bin[i] = '0';
        else
            bin[i] = '1';
    }
}

void addbinary(char bin1[],char bin2[],char bin[MAX],int maxlen){ // the bin1 and bin2 remain unchanged
    int l1 = len(bin1);
    int l2 = len(bin2);
    clearstr(bin);
    padzero(bin1,maxlen);
    padzero(bin2,maxlen);
    padzero(bin,maxlen);
    bin[maxlen] = '\0';

    int i;
    int carry = 0;
    for(i=maxlen-1;i>=0;i--){
        bin[i] = bin1[i] + bin2[i] - '0' + carry;
        if(bin[i]=='3'){
            bin[i] ='1';
            carry = 1;
        }
        else if(bin[i]=='2'){
            bin[i] ='0';
            carry = 1;
        }
        else
            carry = 0;
    }
    unpadzero(bin1,l1);
    unpadzero(bin2,l2);
}

int bintodecimal(char bin[]){ // sigend bin (UNPAD FIRST!)
    int i;
    int n = 0;
    int sign = 1;
    int b = 1;
    if(bin[0]=='1')
        sign = -1;
    for(i=len(bin)-1;i>=1;i--){
        if(bin[i]=='1')
            n += b;
        b *= 2;
    }
    return sign*n;
}

void decimaltobin(int n,char bin[]){ // signed bin // T
    clearstr(bin);
    int sign = 0;
    if(n<0){
        sign = 1;
        n = -n;
    }
    int i = 0,j;
    char temp[MAX];
    clearstr(temp);
    while(n!=0){
        temp[i++] = n%2 + '0';
        n /= 2;
    }
    temp[i] = '\0';
    if(sign)
        bin[0] = '1';
    else
        bin[0] = '0';
    for(j=0;j<len(temp);j++)
        bin[j+1] = temp[j];
    bin[j+1] = '\0';
    reverse(bin);
}

int hxdtodecimal(char hxd[]){ // unsigned hexadecimal // e.g. 0x10EA // T
    int n = 0;
    int t = 1;
    int i;
    for(i=len(hxd)-1;i>=2;i--){
        if(hxd[i]>='A'&&hxd[i]<='F')
            n += (hxd[i] - 'A' + 10)*t;
        else if(hxd[i]>='0'&&hxd[i]<='9')
            n += (hxd[i] - '0')*t;
        t *= 16;
    }
    return n;
}

void decimaltohxd(char hxd[],int n){ // unsiged hexadecimal
    if(n==0){
        hxd[0] = '0';
        hxd[1] = 'x';
        hxd[2] = '0';
        hxd[3] = '\0';
        return;
    }
    int t;
    char temp[MAX];
    clearstr(temp);
    int i = 0;
    while(n!=0){
        t = n%16;
        if(t<9)
            temp[i++] = t + '0';
        else
            temp[i++] = t - 10 + 'A';
        n/=16;
    }
    reverse(temp);
    int j = 0;
    hxd[0] = '0';
    hxd[1] = 'x';
    for(j;j<len(temp);j++)
        hxd[j+2] = temp[j];
    hxd[j+2] = '\0';
}

void hxdtobinary(char hxd[],char bin[]){ // unsigned hexadecimal // singed binary
    int i,k;
    int j = 1;
    char temp[MAX];
    clearstr(temp);
    clearstr(bin);

    for(i=2;i<len(hxd);i++){
        int t;
        if(hxd[i]>='A'&&hxd[i]<='F')
            t = hxd[i] - 'A' + 10;
        else
            t = hxd[i] - '0';
        unsigeddecimaltobin(temp,t);
        padzero(temp,4);
        for(k=0;k<4;k++)
            bin[j+k] = temp[k];
        j += 4;
        clearstr(temp);
    }
    bin[0] = '0';
    bin[j] = '\0';
}


/*==================================================================MAIN FUNCIONS=================================================================*/

void ONESCOMPLEMENT(char bin[]){ // T
    int i;
    for(i=0;i<len(bin);i++){
        if(bin[i]=='1')
            bin[i] = '0';
        else
            bin[i] = '1';
    }
}

void TWOSCOMPLEMENT(char bin[]){ // sigend bin
    onescomplement(bin);
    int l = len(bin);
    char one[MAX] = "1";
    padzero(one,l);
    char temp[MAX];
    clearstr(temp);
    padzero(temp,l);
    addbinary(bin,one,temp,l);
    copy(temp,bin);
}

void NOT(char bin[]){
    int i = 0;
    for(i;i<len(bin)-1;i++){
        if(bin[i]=='1')
            bin[i] = '0';
        else
            bin[i] = '1';
    }
}

void AND(char bin1[],char bin2[],char bin[]){
    clearstr(bin);
    int l1 = len(bin1);
    int l2 = len(bin2);
    int l = (l1>l2) ? l1 : l2;
    padzero(bin1,l);
    padzero(bin2,l);
    padzero(bin,l);
    bin[l] = '\0';
    int i;
    for(i=0;i<l;i++){
        if(bin1[i]=='1'&&bin2[i]=='1')
            bin[i] = '1';
        else
            bin[i] = '0';
    }
    unpadzero(bin1,l1);
    unpadzero(bin2,l2);
}

void XOR(char bin1[],char bin2[],char bin[]){
    clearstr(bin);
    int l1 = len(bin1);
    int l2 = len(bin2);
    int l = (l1>l2) ? l1 : l2;
    padzero(bin1,l);
    padzero(bin2,l);
    padzero(bin,l);
    bin[l] = '\0';
    int i;
    for(i=0;i<l;i++){
        if(bin1[i]!=bin2[i])
            bin[i] = '1';
        else
            bin[i] = '0';
    }
    unpadzero(bin1,l1);
    unpadzero(bin2,l2);
}

void OR(char bin1[],char bin2[],char bin[]){
    clearstr(bin);
    int l1 = len(bin1);
    int l2 = len(bin2);
    int l = (l1>l2) ? l1 : l2;
    padzero(bin1,l);
    padzero(bin2,l);
    padzero(bin,l);
    bin[l] = '\0';
    int i;
    for(i=0;i<l;i++){
        if(bin1[i]=='1'||bin2[i]=='1')
            bin[i] = '1';
        else
            bin[i] = '0';
    }
    unpadzero(bin1,l1);
    unpadzero(bin2,l2);
}

void NOR(char bin1[],char bin2[],char bin[]){
    OR(bin1,bin2,bin);
    NOT(bin);
}

void XNOR(char bin1[],char bin2[],char bin[]){
    XOR(bin1,bin2,bin);
    NOT(bin);
}

void NAND(char bin1[],char bin2[],char bin[]){
    AND(bin1,bin2,bin);
    NOT(bin);
}


/*================================================================================================================================================*/



int main(){


    return 0;
}