#include <stdio.h>
#include <stdlib.h>

#define R 20
#define C 40

char a[R][C];

void clear()
{
    int i,j;

    for(i=0;i<R;i++)
        for(j=0;j<C;j++)
            a[i][j]='_';
}

void show()
{
    int i,j;

    for(i=0;i<R;i++)
    {
        for(j=0;j<C;j++)
            printf("%c",a[i][j]);
        printf("\n");
    }
}

void rect(int r,int c,int h,int w)
{
    int i;

    for(i=c;i<c+w;i++)
    {
        a[r][i]='*';
        a[r+h-1][i]='*';
    }

    for(i=r;i<r+h;i++)
    {
        a[i][c]='*';
        a[i][c+w-1]='*';
    }
}

void line(int r1,int c1,int r2,int c2)
{
    int i;

    if(r1==r2)
    {
        for(i=c1;i<=c2;i++)
            a[r1][i]='*';
    }
    else if(c1==c2)
    {
        for(i=r1;i<=r2;i++)
            a[i][c1]='*';
    }
}

void tri(int r,int c,int h)
{
    int i;

    for(i=0;i<h;i++)
    {
        a[r+i][c-i]='*';
        a[r+i][c+i]='*';
    }

    for(i=c-h+1;i<=c+h-1;i++)
        a[r+h-1][i]='*';
}

void circle(int xc,int yc,int rad)
{
    int x,y,d;

    for(x=0;x<R;x++)
    {
        for(y=0;y<C;y++)
        {
            d=(x-xc)*(x-xc)+(y-yc)*(y-yc);

            if(abs(d-rad*rad)<=rad)
                a[x][y]='*';
        }
    }
}

int main()
{
    int ch;
    int r,c,h,w,rad;
    int r1,c1,r2,c2;

    clear();

    do
    {
        printf("\n1.Rectangle");
        printf("\n2.Line");
        printf("\n3.Triangle");
        printf("\n4.Circle");
        printf("\n5.Display");
        printf("\n6.Clear");
        printf("\n0.Exit");
        printf("\nEnter choice: ");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
                printf("Row Col Height Width: ");
                scanf("%d%d%d%d",&r,&c,&h,&w);
                rect(r,c,h,w);
                break;

            case 2:
                printf("r1 c1 r2 c2: ");
                scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
                line(r1,c1,r2,c2);
                break;

            case 3:
                printf("Row Col Height: ");
                scanf("%d%d%d",&r,&c,&h);
                tri(r,c,h);
                break;

            case 4:
                printf("CenterRow CenterCol Radius: ");
                scanf("%d%d%d",&r,&c,&rad);
                circle(r,c,rad);
                break;

            case 5:
                show();
                break;

            case 6:
                clear();
                printf("Picture Cleared\n");
                break;

            case 0:
                printf("Program Ended\n");
                break;

            default:
                printf("Invalid Choice\n");
        }
    
    }while(ch!=0);

    return 0;
}
