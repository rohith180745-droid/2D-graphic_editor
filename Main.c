#include <stdio.h>

#define HEIGHT 20
#define WIDTH 40
#define MAX_SHAPES 100

char canvas[HEIGHT][WIDTH];

typedef struct
{
    int id;
    int type;      // 1-Line 2-Rectangle 3-Triangle 4-Circle
    int row;
    int col;
    int p1;
    int p2;
    int active;
} Shape;

Shape shapes[MAX_SHAPES];
int shapeCount=0;
int nextID=1;

void initializeCanvas()
{
    int i, j;

    for(i=0;i<HEIGHT;i++)
    {
        for(j=0;j<WIDTH;j++)
        {
            canvas[i][j]='_';
        }
    }
}

void drawLine(int row, int startCol, int endCol)
{
    int j;

    if(row<0 || row>=HEIGHT)
        return;

    if(startCol>endCol)
    {
        int temp=startCol;
        startCol=endCol;
        endCol=temp;
    }

    for(j=startCol;j<=endCol;j++)
    {
        if(j>=0 && j<WIDTH)
            canvas[row][j]='*';
    }
}

void drawRectangle(int row, int col, int height, int width)
{
    int i, j;

    for(j=col;j<col+width;j++)
    {
        if(row>=0 && row<HEIGHT &&
           j>=0 && j<WIDTH)
            canvas[row][j]='*';

        if(row + height - 1>=0 &&
           row + height - 1<HEIGHT &&
           j>= 0 && j <WIDTH)
            canvas[row + height - 1][j] ='*';
    }

    for(i=row; i<row + height;i++)
    {
        if(i >= 0 && i < HEIGHT &&
           col>= 0 && col<WIDTH)
            canvas[i][col]='*';

        if(i>=0 && i<HEIGHT &&
           col + width - 1>=0 &&
           col + width - 1<WIDTH)
            canvas[i][col + width - 1]='*';
    }
}

void drawTriangle(int row, int col, int height)
{
    int i, j;

    for(i=0; i<height;i++)
    {
        for(j=0; j<=i;j++)
        {
            if(row + i>=0 &&
               row + i<HEIGHT &&
               col + j>=0 &&
               col + j<WIDTH)
            {
                canvas[row + i][col + j]='*';
            }
        }
    }
}

void drawCircle(int centerRow, int centerCol, int radius)
{
    int row, col;

    for(row=0;row<HEIGHT;row++)
    {
        for(col=0;col<WIDTH;col++)
        {
            int dx=row-centerRow;
            int dy=col-centerCol;

            if(dx * dx + dy * dy <= radius * radius)
            {
                canvas[row][col]='*';
            }
        }
    }
}

void redrawCanvas()
{
    int i;

    initializeCanvas();

    for(i=0;i<shapeCount;i++)
    {
        if(shapes[i].active==1)
        {
            switch(shapes[i].type)
            {
                case 1:
                    drawLine(
                        shapes[i].row,
                        shapes[i].col,
                        shapes[i].p1
                    );
                    break;

                case 2:
                    drawRectangle(
                        shapes[i].row,
                        shapes[i].col,
                        shapes[i].p1,
                        shapes[i].p2
                    );
                    break;

                case 3:
                    drawTriangle(
                        shapes[i].row,
                        shapes[i].col,
                        shapes[i].p1
                    );
                    break;

                case 4:
                    drawCircle(
                        shapes[i].row,
                        shapes[i].col,
                        shapes[i].p1
                    );
                    break;
            }
        }
    }
}

void displayCanvas()
{
    int i, j;

    printf("\n");

    for(i=0;i<HEIGHT;i++)
    {
        for(j=0;j<WIDTH;j++)
        {
            printf("%c",canvas[i][j]);
        }
        printf("\n");
    }
}

void addShape()
{
    Shape s;

    int choice;

    printf("\n");
    printf("1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Triangle\n");
    printf("4. Circle\n");

    printf("Enter Shape Type: ");
    scanf("%d", &choice);

    s.id=nextID++;
    s.type=choice;
    s.active=1;

    switch(choice)
    {
        case 1:
            printf("Enter Row StartCol EndCol: ");
            scanf("%d %d %d",
                  &s.row,
                  &s.col,
                  &s.p1);
            s.p2=0;
            break;

        case 2:
            printf("Enter Row Col Height Width: ");
            scanf("%d %d %d %d",
                  &s.row,
                  &s.col,
                  &s.p1,
                  &s.p2);
            break;

        case 3:
            printf("Enter Row Col Height: ");
            scanf("%d %d %d",
                  &s.row,
                  &s.col,
                  &s.p1);
            s.p2=0;
            break;

        case 4:
            printf("Enter CenterRow CenterCol Radius: ");
            scanf("%d %d %d",
                  &s.row,
                  &s.col,
                  &s.p1);
            s.p2=0;
            break;

        default:
            printf("Invalid Shape!\n");
            return;
    }

    shapes[shapeCount++]=s;

    redrawCanvas();

    printf("Shape Added! ID = %d\n",s.id);
}

void deleteShape()
{
    int id;
    int i;
    int found=0;

    printf("Enter Shape ID to Delete: ");
    scanf("%d",&id);

    for(i=0;i<shapeCount;i++)
    {
        if(shapes[i].id==id &&
           shapes[i].active==1)
        {
            shapes[i].active=0;
            found=1;
            break;
        }
    }

    if(found)
    {
        redrawCanvas();
        printf("Shape Deleted!\n");
    }
    else
    {
        printf("Shape ID Not Found!\n");
    }
}

void modifyShape()
{
    int id;
    int i;
    int found=0;

    printf("Enter Shape ID to Modify: ");
    scanf("%d",&id);

    for(i=0;i<shapeCount;i++)
    {
        if(shapes[i].id==id &&
           shapes[i].active==1)
        {
            found=1;

            switch(shapes[i].type)
            {
                case 1:
                    printf("Enter New Row StartCol EndCol: ");
                    scanf("%d %d %d",
                          &shapes[i].row,
                          &shapes[i].col,
                          &shapes[i].p1);
                    break;

                case 2:
                    printf("Enter New Row Col Height Width: ");
                    scanf("%d %d %d %d",
                          &shapes[i].row,
                          &shapes[i].col,
                          &shapes[i].p1,
                          &shapes[i].p2);
                    break;

                case 3:
                    printf("Enter New Row Col Height: ");
                    scanf("%d %d %d",
                          &shapes[i].row,
                          &shapes[i].col,
                          &shapes[i].p1);
                    break;

                case 4:
                    printf("Enter New CenterRow CenterCol Radius: ");
                    scanf("%d %d %d",
                          &shapes[i].row,
                          &shapes[i].col,
                          &shapes[i].p1);
                    break;
            }

            redrawCanvas();

            printf("Shape Modified!\n");
            break;
        }
    }

    if(!found)
    {
        printf("Shape ID Not Found!\n");
    }
}

void listShapes()
{
    int i;

    printf("\nStored Shapes:\n");

    for(i=0;i<shapeCount;i++)
    {
        if(shapes[i].active)
        {
            printf("ID: %d  Type: %d\n",
                   shapes[i].id,
                   shapes[i].type);
        }
    }
}

int main()
{
    int choice;

    initializeCanvas();

    do
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Add Shape\n");
        printf("2. Display Canvas\n");
        printf("3. Delete Shape\n");
        printf("4. Modify Shape\n");
        printf("5. List Shapes\n");
        printf("6. Clear Canvas\n");
        printf("7. Exit\n");

        printf("Enter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addShape();
                break;

            case 2:
                displayCanvas();
                break;

            case 3:
                deleteShape();
                break;

            case 4:
                modifyShape();
                break;

            case 5:
                listShapes();
                break;

            case 6:
                shapeCount=0;
                initializeCanvas();
                printf("Canvas Cleared!\n");
                break;

            case 7:
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice!=7);

    return 0;
}
