#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 24

#define EMPTY '_'
#define PIXEL '*'
#define MAX_OBJECTS 100

typedef enum {
    LINE = 1,
    RECTANGLE,
    CIRCLE,
    TRIANGLE
} ShapeType;

typedef struct {
    ShapeType type;
    int valid;

    union {
        struct {
            int x1, y1, x2, y2;
        } line;

        struct {
            int x1, y1, x2, y2;
        } rect;

        struct {
            int cx, cy, radius;
        } circle;

        struct {
            int x1, y1, x2, y2, x3, y3;
        } tri;

    } data;

} GraphicObject;

char picture[HEIGHT][WIDTH];
GraphicObject objects[MAX_OBJECTS];

int objectCount = 0;

void clearPicture() {
    int i, j;

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            picture[i][j] = EMPTY;
        }
    }
}

void displayPicture() {
    int i, j;

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            printf("%c", picture[i][j]);
        }
        printf("\n");
    }
}

void setPixel(int x, int y) {

    if (x < 0 || y < 0) {
        return;
    }

    if (x >= WIDTH || y >= HEIGHT) {
        return;
    }

    picture[y][x] = PIXEL;
}

void drawLine(int x1, int y1, int x2, int y2) {

    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps;

    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    } else {
        steps = abs(dy);
    }

    float xincrement = (float)dx / steps;
    float yincrement = (float)dy / steps;

    float x = x1;
    float y = y1;

    int i;

    for (i = 0; i <= steps; i++) {

        setPixel((int)(x + 0.5), (int)(y + 0.5));

        x = x + xincrement;
        y = y + yincrement;
    }
}

void drawRectangle(int x1, int y1, int x2, int y2) {

    drawLine(x1, y1, x2, y1);

    drawLine(x2, y1, x2, y2);

    drawLine(x2, y2, x1, y2);

    drawLine(x1, y2, x1, y1);
}

void drawCircle(int cx, int cy, int radius) {

    int x = 0;
    int y = radius;

    int p = 3 - (2 * radius);

    while (x <= y) {

        setPixel(cx + x, cy + y);
        setPixel(cx - x, cy + y);
        setPixel(cx + x, cy - y);
        setPixel(cx - x, cy - y);

        setPixel(cx + y, cy + x);
        setPixel(cx - y, cy + x);
        setPixel(cx + y, cy - x);
        setPixel(cx - y, cy - x);

        if (p < 0) {
            p = p + (4 * x) + 6;
        }
        else {
            p = p + 4 * (x - y) + 10;
            y--;
        }

        x++;
    }
}

void drawTriangle(int x1, int y1,
                  int x2, int y2,
                  int x3, int y3) {

    drawLine(x1, y1, x2, y2);

    drawLine(x2, y2, x3, y3);

    drawLine(x3, y3, x1, y1);
}

void renderAllObjects() {

    clearPicture();

    int i;

    for (i = 0; i < objectCount; i++) {

        if (objects[i].valid == 0) {
            continue;
        }

        switch (objects[i].type) {

            case LINE:

                drawLine(
                    objects[i].data.line.x1,
                    objects[i].data.line.y1,
                    objects[i].data.line.x2,
                    objects[i].data.line.y2
                );

                break;

            case RECTANGLE:

                drawRectangle(
                    objects[i].data.rect.x1,
                    objects[i].data.rect.y1,
                    objects[i].data.rect.x2,
                    objects[i].data.rect.y2
                );

                break;

            case CIRCLE:

                drawCircle(
                    objects[i].data.circle.cx,
                    objects[i].data.circle.cy,
                    objects[i].data.circle.radius
                );

                break;

            case TRIANGLE:

                drawTriangle(
                    objects[i].data.tri.x1,
                    objects[i].data.tri.y1,
                    objects[i].data.tri.x2,
                    objects[i].data.tri.y2,
                    objects[i].data.tri.x3,
                    objects[i].data.tri.y3
                );

                break;
        }
    }
}

int main() {

    int choice;

    clearPicture();

    while (1) {

        printf("2D Graphics Editor\n");
        printf("Canvas size: %d x %d\n", WIDTH, HEIGHT);

        printf("1. Add object\n");
        printf("2. Delete object\n");
        printf("3. Modify object\n");
        printf("4. Display picture\n");
        printf("5. List objects\n");
        printf("0. Exit\n");

        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            break;
        }

        if (choice == 1) {

            int shapeType;

            printf("Choose shape type:\n");
            printf("1. Line\n");
            printf("2. Rectangle\n");
            printf("3. Circle\n");
            printf("4. Triangle\n");

            printf("Enter shape type: ");

            scanf("%d", &shapeType);

            if (shapeType == 1) {

                printf("Enter x1 y1 x2 y2: ");

                scanf("%d %d %d %d",
                      &objects[objectCount].data.line.x1,
                      &objects[objectCount].data.line.y1,
                      &objects[objectCount].data.line.x2,
                      &objects[objectCount].data.line.y2);

                objects[objectCount].type = LINE;
                objects[objectCount].valid = 1;

                printf("Object added with index %d.\n\n", objectCount);

                objectCount++;
            }

            else if (shapeType == 2) {

                printf("Enter top-left x y and bottom-right x y: ");

                scanf("%d %d %d %d",
                      &objects[objectCount].data.rect.x1,
                      &objects[objectCount].data.rect.y1,
                      &objects[objectCount].data.rect.x2,
                      &objects[objectCount].data.rect.y2);

                objects[objectCount].type = RECTANGLE;
                objects[objectCount].valid = 1;

                printf("Object added with index %d.\n\n", objectCount);

                objectCount++;
            }

            else if (shapeType == 3) {

                printf("Enter center x y and radius: ");

                scanf("%d %d %d",
                      &objects[objectCount].data.circle.cx,
                      &objects[objectCount].data.circle.cy,
                      &objects[objectCount].data.circle.radius);

                objects[objectCount].type = CIRCLE;
                objects[objectCount].valid = 1;

                printf("Object added with index %d.\n\n", objectCount);

                objectCount++;
            }

            else if (shapeType == 4) {

                printf("Enter x1 y1 x2 y2 x3 y3: ");

                scanf("%d %d %d %d %d %d",
                      &objects[objectCount].data.tri.x1,
                      &objects[objectCount].data.tri.y1,
                      &objects[objectCount].data.tri.x2,
                      &objects[objectCount].data.tri.y2,
                      &objects[objectCount].data.tri.x3,
                      &objects[objectCount].data.tri.y3);

                objects[objectCount].type = TRIANGLE;
                objects[objectCount].valid = 1;

                printf("Object added with index %d.\n\n", objectCount);

                objectCount++;
            }
        }

        else if (choice == 2) {

            int index;

            printf("Enter object index to delete: ");

            scanf("%d", &index);

            if (index >= 0 && index < objectCount) {
                objects[index].valid = 0;
            }

            printf("\n");
        }

        else if (choice == 3) {

            printf("\n");
        }

        else if (choice == 4) {

            renderAllObjects();

            displayPicture();

            printf("\n");
        }

        else if (choice == 5) {

            printf("\n");
        }

        else if (choice == 0) {

            printf("Goodbye.\n");

            break;
        }

        else {

            printf("Invalid choice.\n\n");
        }
    }

    return 0;
}
