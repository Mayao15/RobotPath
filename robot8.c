#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Max 100
#define MIN(x,y) ((x)<(y)?(x):(y))
char a[10][10]={};//a[y][x]
int oriY=3,oriX=3,finY=9,finX=9;
float openlist[Max][6]={0};
float closelist[Max][6]={0};
int countCl=0;
//struct  list {
//    int x;
//    int y;
//    int depth;
//    float f;
//    int parent_x;
//    int parent_y;
//};

float F(int depth,int x,int y);
void Print( );
void InsertSort();
void Astar();
void PrintPath();
void DrawTree(float i,float j);

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
//    scanf("起始位置：%d,%d"，&oriY,&oriX);
//    scanf("结束位置：%d,%d"，&finY,&finX);
    oriY-=1;oriX-=1;finY-=1;finX-=1;
    if(oriY==finY&&oriX==finX){
        printf("机器人已在终点");
        return 0;
    }

    openlist[0][0]=oriY;
    openlist[0][1]=oriX;
    openlist[0][2]=0;
    openlist[0][3]=F(0,oriY,oriX);
    a[oriY][oriX]='1';
    Print();

    Astar();

    PrintPath();

    printf("---------------------\n搜索图:\n(%d,%d)\n",oriX+1,oriY+1);
    DrawTree(oriX,oriY);
    return 0;
}
void DrawTree(float i,float j){
    int k,m,n;

    for(k=0;k<Max&&i!=0&&j!=0;k++){
        if(openlist[k][5]==(float)j&&openlist[k][4]==(float)i){
            for(n=0;n<openlist[k][2];n++){
                printf("|      ");
            }
            printf("(%.0f,%.0f)\n",openlist[k][1]+1,openlist[k][0]+1);
        }
    }

    for(m=0;m<Max&&i!=0&&j!=0;m++){
        if(closelist[m][5]==(float)j&&closelist[m][4]==(float)i){
            for(n=0;n<closelist[m][2];n++){
                printf("|      ");
            }
            printf("(%.0f,%.0f)\n",closelist[m][1]+1,closelist[m][0]+1);
            DrawTree(closelist[m][1],closelist[m][0]);
        }
    }
}

int Search(int x,int y,int d,int f,int i,int j){
//    int k=0;
//    for(k=0;k<Max;k++){
//        if(openlist[k][1]==x&&openlist[k][0]==y){
//            if(openlist[k][3]>f){
//                openlist[k][0]=y;
//                openlist[k][1]=x;
//                openlist[k][2]=d;
//                openlist[k][3]=f;
//                openlist[k][4]=j;
//                openlist[k][5]=i;
//            }
//            return 1;
//        }
//        if(closelist[k][1]==x&&closelist[k][0]==y){
//            if(closelist[k][3]>f){
//                for(;closelist[k][2]!=0||closelist[k][3]!=0;k++){
//                    closelist[k][0]=closelist[k+1][0];
//                    closelist[k][1]=closelist[k+1][1];
//                    closelist[k][2]=closelist[k+1][2];
//                    closelist[k][3]=closelist[k+1][3];
//                    closelist[k][4]=closelist[k+1][4];
//                    closelist[k][5]=closelist[k+1][5];
//                }
//                countCl--;
//                return 0;
//            }
//            return 1;
//        }
//    }
    for(i=0;i<Max;i++)
        if(openlist[i][0]==x&&openlist[i][1]==y||closelist[i][0]==x&&closelist[i][1]==y)
            return 1;

    return 0;
}


float F(int depth,int y,int x){
    float W,ans;
//    W=abs(y-finY)+abs(x-finX)-MIN(abs(y-finY),abs(x-finX));
    W=sqrt(((float)y-(float)finY)*((float)y-(float)finY)+((float)x-(float)finX)*((float)x-(float)finX));
    ans=W+(float)depth;
    return ans;
}

void Print( ){
    int i,j,k;
    printf("---------------------\n第%d次搜索前的open表\n",countCl+1);
    for(i=0;openlist[i][2]!=0||openlist[i][3]!=0;i++){
            printf("(%.0f,%.0f) (%.0f,%.0f),d=%.0f,f=%.3f\n",openlist[i][1]+1,openlist[i][0]+1,openlist[i][5]+1,openlist[i][4]+1,openlist[i][2],openlist[i][3]);
    }
    if(i==0){
        printf("搜索失败\n");
        return 0;
    }
    printf("第%d次搜索前的close表:\n",countCl+1);
    for(k=0;closelist[k][2]!=0||closelist[k][3]!=0;k++){
        printf("(%.0f,%.0f) (%.0f,%.0f),d=%.0f,f=%.3f\n",closelist[k][1]+1,closelist[k][0]+1,closelist[k][5]+1,closelist[k][4]+1,closelist[k][2],closelist[k][3]);
    }
    if(k==0){
        printf("close表为空\n");
    }
    printf("第%d次搜索后搜索过的节点（1）:\n",countCl+1);
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

void InsertSort(){
    int i, j;
    float temp0,temp1,temp2,temp3,temp4,temp5;
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
    int i=oriY,j=oriX,countOp=0,depth=0,k=0;
    while(i!=finY||j!=finX){
        //把经历过的Open表节点放入Close表，然后删除该节点
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
        //8点搜索，把节点放入Open表
        if(i-1>=0&&a[i-1][j]!='*'){//上
            if(Search(i-1,j,depth+1,F(depth+1,i-1,j),i,j)==0){
                countOp++;
                openlist[countOp][0]=i-1;
                openlist[countOp][1]=j;
                openlist[countOp][2]=depth+1;
                openlist[countOp][3]=F(depth+1,i-1,j);
                openlist[countOp][4]=i;
                openlist[countOp][5]=j;
            }
        }
        if(i-1>=0&&a[i-1][j-1]!='*'){//左上
            if(Search(i-1,j-1,depth+1,F(depth+1,i-1,j-1),i,j)==0){
                countOp++;
                openlist[countOp][0]=i-1;
                openlist[countOp][1]=j-1;
                openlist[countOp][2]=depth+1;
                openlist[countOp][3]=F(depth+1,i-1,j-1);
                openlist[countOp][4]=i;
                openlist[countOp][5]=j;
            }
        }
        if(j-1>=0&&a[i][j-1]!='*'){//左
            if(Search(i,j-1,depth+1,F(depth+1,i,j-1),i,j)==0){
                countOp++;
                openlist[countOp][0]=i;
                openlist[countOp][1]=j-1;
                openlist[countOp][2]=depth+1;
                openlist[countOp][3]=F(depth+1,i,j-1);
                openlist[countOp][4]=i;
                openlist[countOp][5]=j;
            }
        }
        if(i-1>=0&&a[i+1][j-1]!='*'){//左下
            if(Search(i+1,j-1,depth+1,F(depth+1,i,j-1),i,j)==0){
                countOp++;
                openlist[countOp][0]=i+1;
                openlist[countOp][1]=j-1;
                openlist[countOp][2]=depth+1;
                openlist[countOp][3]=F(depth+1,i+1,j-1);
                openlist[countOp][4]=i;
                openlist[countOp][5]=j;
            }
        }
        if(i+1<=9&&a[i+1][j]!='*'){//下
            if(Search(i+1,j,depth+1,F(depth+1,i,j-1),i,j)==0){
                countOp++;
                openlist[countOp][0]=i+1;
                openlist[countOp][1]=j;
                openlist[countOp][2]=depth+1;
                openlist[countOp][3]=F(depth+1,i+1,j);
                openlist[countOp][4]=i;
                openlist[countOp][5]=j;
            }
        }
        if(i-1>=0&&a[i+1][j-1]!='*'){//右下
            if(Search(i+1,j+1,depth+1,F(depth+1,i,j-1),i,j)==0){
                countOp++;
                openlist[countOp][0]=i+1;
                openlist[countOp][1]=j+1;
                openlist[countOp][2]=depth+1;
                openlist[countOp][3]=F(depth+1,i+1,j+1);
                openlist[countOp][4]=i;
                openlist[countOp][5]=j;
            }
        }
        if(j+1<=9&&a[i][j+1]!='*'){//右
            if(Search(i,j+1,depth,F(depth+1,i,j+1),i,j)==0){
                countOp++;
                openlist[countOp][0]=i;
                openlist[countOp][1]=j+1;
                openlist[countOp][2]=depth+1;
                openlist[countOp][3]=F(depth+1,i,j+1);
                openlist[countOp][4]=i;
                openlist[countOp][5]=j;
            }
        }
        if(i-1>=0&&a[i-1][j-1]!='*'){//右上
            if(Search(i-1,j+1,depth,F(depth+1,i,j-1),i,j)==0){
                countOp++;
                openlist[countOp][0]=i-1;
                openlist[countOp][1]=j+1;
                openlist[countOp][2]=depth+1;
                openlist[countOp][3]=F(depth+1,i-1,j+1);
                openlist[countOp][4]=i;
                openlist[countOp][5]=j;
            }
        }

        //对Open表按F从小到大排序
        InsertSort();
        //从Open表中F最小的开始
        i=openlist[0][0];
        j=openlist[0][1];
        depth=openlist[0][2];
        a[i][j]='1';
        Print();
    }
    printf("机器人已在终点\n");

    closelist[countCl][0]=openlist[0][0];
    closelist[countCl][1]=openlist[0][1];
    closelist[countCl][2]=openlist[0][2];
    closelist[countCl][3]=openlist[0][3];
    closelist[countCl][4]=openlist[0][4];
    closelist[countCl][5]=openlist[0][5];
    for(k=0;openlist[k][2]!=0||openlist[k][3]!=0;k++){
            openlist[k][0]=openlist[k+1][0];
            openlist[k][1]=openlist[k+1][1];
            openlist[k][2]=openlist[k+1][2];
            openlist[k][3]=openlist[k+1][3];
            openlist[k][4]=openlist[k+1][4];
            openlist[k][5]=openlist[k+1][5];
        }
    countOp--;

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
        b[i][j]=1;
        childY=i;
        childX=j;
        i=parentY;
        j=parentX;
    }
    b[i][j]=12;
    printf("---------------------\n最佳路径：\n");
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
//            printf("%d ",b[i][j]);
            switch (b[i][j]){
                case 0: printf("■"); break;
                case 1: printf("◆"); break;
                case 9: printf("×"); break;
                case 11:printf("▲"); break;
                case 12:printf("△"); break;
            }
        }
        printf("\n");
    }
}
