#include <stdio.h>
#include <stdlib.h>
#define Max 100
char a[10][10]={};//a[y][x]
int oriY=3,oriX=3,finY=9,finX=9;
int openlist[Max][6]={0};
int closelist[Max][6]={0};
int countCl=0;
//struct  list {
//    int x;
//    int y;
//    int depth;
//    int f;
//    int parent_x;
//    int parent_y;
//};

int F(int depth,int x,int y);
void Print( );
void insertSort();
void Astar();
void PrintPath();
int main()
{

    a[1][0]='*';
    a[1][3]='*';
    a[1][8]='*';
    a[2][5]='*';
    a[3][2]='*';
    a[3][6]='*';
    a[3][8]='*';
    a[5][4]='*';
    a[7][2]='*';
    a[7][6]='*';
    a[9][0]='*';
    a[9][2]='*';
    a[9][8]='*';

//    int oriY,oriX,finY,finX;
//    scanf("��ʼλ�ã�%d,%d"��&oriY,&oriX);
//    scanf("����λ�ã�%d,%d"��&finY,&finX);
    oriY-=1;oriX-=1;finY-=1;finX-=1;



    openlist[0][0]=oriY;
    openlist[0][1]=oriX;
    openlist[0][2]=0;
    openlist[0][3]=F(0,oriY,oriX);
    a[oriY][oriX]='1';
    Print();

    Astar();

    PrintPath();
    return 0;
}
int Search(int x,int y){
    int i=0;
    for(i=0;i<Max;i++)
        if(openlist[i][0]==x&&openlist[i][1]==y||closelist[i][0]==x&&closelist[i][1]==y)
            return 1;
    return 0;
}


int F(int depth,int x,int y){
    int W,ans;
    W=abs(x-finY)+abs(y-finX);
    ans=W+depth;
    return ans;
}

void Print( ){
    int i,j,k;
    printf("---------------------\n��%d������ǰ��open��\n",countCl+1);
    for(i=0;openlist[i][2]!=0||openlist[i][3]!=0;i++){
            printf("(%d,%d),d=%d,f=%d\n",openlist[i][1]+1,openlist[i][0]+1,openlist[i][2],openlist[i][3]);
    }
    if(i==0){
        printf("����ʧ��\n");
        return 0;
    }
    printf("��%d������ǰ��close��:\n",countCl+1);
    for(k=0;closelist[k][2]!=0||closelist[k][3]!=0;k++){
        printf("(%d,%d),d=%d,f=%d\n",closelist[k][1]+1,closelist[k][0]+1,closelist[k][2],closelist[k][3]);
    }
    if(k==0){
        printf("close��Ϊ��\n");
    }
    printf("��%d���������������Ľڵ㣨1��:\n",countCl+1);
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            if(a[i][j]==0){
                printf("0 ");
            }
            else{
                printf("%c ",a[i][j] );
            }
        }
        printf("\n");
    }

}

void insertSort(){
    int i, j;
    int temp0,temp1,temp2,temp3,temp4,temp5;
    for(i=1;openlist[i][2]!=0||openlist[i][3]!=0;i++){
        temp0=openlist[i][0];
        temp1=openlist[i][1];
        temp2=openlist[i][2];
        temp3=openlist[i][3];
        temp4=openlist[i][4];
        temp5=openlist[i][5];
        for(j=i-1; j>=0 && temp3<=openlist[j][3]; j--){
            openlist[j+1][0]=openlist[j][0];
            openlist[j+1][1]=openlist[j][1];
            openlist[j+1][2]=openlist[j][2];
            openlist[j+1][3]=openlist[j][3];
            openlist[j+1][4]=openlist[j][4];
            openlist[j+1][5]=openlist[j][5];
        }
        openlist[j+1][0]=temp0;
        openlist[j+1][1]=temp1;
        openlist[j+1][2]=temp2;
        openlist[j+1][3]=temp3;
        openlist[j+1][4]=temp4;
        openlist[j+1][5]=temp5;
       }
}


void Astar(){
    int i=oriY,j=oriX,countOp=0,depth=0,k=0,temp;
    while(i!=finY||j!=finX){
        //4���������ѽڵ����Open��
        if(i-1>=0&&a[i-1][j]!='*'){//��
            temp=i-1;
            if(Search(temp,j)==0){
                countOp++;
                openlist[countOp][0]=temp;
                openlist[countOp][1]=j;
                openlist[countOp][2]=depth+1;
                openlist[countOp][3]=F(depth+1,temp,j);
                openlist[countOp][4]=i;
                openlist[countOp][5]=j;
            }
        }
        if(j-1>=0&&a[i][j-1]!='*'){//��
            temp=j-1;
            if(Search(i,temp)==0){
                countOp++;
                openlist[countOp][0]=i;
                openlist[countOp][1]=temp;
                openlist[countOp][2]=depth+1;
                openlist[countOp][3]=F(depth+1,i,temp);
                openlist[countOp][4]=i;
                openlist[countOp][5]=j;
            }
        }
        if(i+1<=9&&a[i+1][j]!='*'){//��
            temp=i+1;
            if(Search(temp,j)==0){
                countOp++;
                openlist[countOp][0]=temp;
                openlist[countOp][1]=j;
                openlist[countOp][2]=depth+1;
                openlist[countOp][3]=F(depth+1,temp,j);
                openlist[countOp][4]=i;
                openlist[countOp][5]=j;
            }
        }
        if(j+1<=9&&a[i][j+1]!='*'){//��
            temp=j+1;
            if(Search(i,temp)==0){
                countOp++;
                openlist[countOp][0]=i;
                openlist[countOp][1]=temp;
                openlist[countOp][2]=depth+1;
                openlist[countOp][3]=F(depth+1,i,temp);
                openlist[countOp][4]=i;
                openlist[countOp][5]=j;
            }
        }
        //�Ѿ�������Open��ڵ����Close��Ȼ��ɾ���ýڵ�
        closelist[countCl][0]=openlist[0][0];
        closelist[countCl][1]=openlist[0][1];
        closelist[countCl][2]=openlist[0][2];
        closelist[countCl][3]=openlist[0][3];
        closelist[countCl][4]=openlist[0][4];
        closelist[countCl][5]=openlist[0][5];
        countCl++;
        for(k=0;openlist[k][2]!=0||openlist[k][3]!=0;k++){
            openlist[k][0]=openlist[k+1][0];
            openlist[k][1]=openlist[k+1][1];
            openlist[k][2]=openlist[k+1][2];
            openlist[k][3]=openlist[k+1][3];
            openlist[k][4]=openlist[k+1][4];
            openlist[k][5]=openlist[k+1][5];
        }
        countOp--;
        //��Open��F��С��������
        insertSort();
        //��Open����F��С�Ŀ�ʼ
        i=openlist[0][0];
        j=openlist[0][1];
        depth=openlist[0][2];
        a[i][j]='1';
        Print();
    }
    closelist[countCl][0]=openlist[0][0];
    closelist[countCl][1]=openlist[0][1];
    closelist[countCl][2]=openlist[0][2];
    closelist[countCl][3]=openlist[0][3];
    closelist[countCl][4]=openlist[0][4];
    closelist[countCl][5]=openlist[0][5];

}

void PrintPath(){
    int b[10][10]={0};
    b[1][0]=9;
    b[1][3]=9;
    b[1][8]=9;
    b[2][5]=9;
    b[3][2]=9;
    b[3][6]=9;
    b[3][8]=9;
    b[5][4]=9;
    b[7][2]=9;
    b[7][6]=9;
    b[9][0]=9;
    b[9][2]=9;
    b[9][8]=9;
    int i=finY,j=finX,k=0,childX,childY,parentX,parentY;
    b[i][j]=11;
    for(k=countCl;closelist[k][2]!=0||closelist[k][3]!=0;k--){
        if(closelist[k][0]==i&&closelist[k][1]==j){
            childX=j;
            childY=i;
            i=closelist[k][4];
            j=closelist[k][5];
            break;
        }
    }
    countCl--;

    while(i!=oriY||j!=oriX){
        for(k=countCl;closelist[k][2]!=0||closelist[k][3]!=0;k--){
            if(closelist[k][0]==i&&closelist[k][1]==j){
                parentY=closelist[k][4];
                parentX=closelist[k][5];
                break;
            }
        }
//        printf("%d %d,%d %d,%d %d\n",parentX,parentY,j,i,childX,childY);
        if(abs(childX-parentX)==2){
            b[i][j]=1;//��
        }
        if(abs(childY-parentY)==2){
            b[i][j]=2;//��
        }
        if(j-parentX==1&&i-childY==-1||j-childX==1&&i-parentY==-1){
            b[i][j]=3;//��
        }
        if(j-childX==-1&&i-parentY==1||j-parentX==-1&&i-childY==1){
            b[i][j]=4;//��
        }
        if(j-childX==1&&i-parentY==1||j-parentX==1&&i-childY==1){
            b[i][j]=5;//��
        }
        if(j-parentX==-1&&i-childY==-1||j-childX==-1&&i-parentY==-1){
            b[i][j]=6;//��
        }
        childY=i;
        childX=j;
        i=parentY;
        j=parentX;
    }
    b[i][j]=12;
    printf("---------------------\n���·����\n");
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
//            printf("%d ",b[i][j]);
            switch (b[i][j]){
                case 0: printf("��"); break;
                case 1: printf("�� "); break;
                case 2: printf("�� "); break;
                case 3: printf("�� "); break;
                case 4: printf("�� "); break;
                case 5: printf("�� "); break;
                case 6: printf("�� "); break;
                case 9: printf("��"); break;
                case 11:printf("��"); break;
                case 12:printf("��"); break;
            }
        }
        printf("\n");
    }
}
