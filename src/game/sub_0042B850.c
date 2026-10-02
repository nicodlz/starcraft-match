/* Signed two-WORD comparison; trailing bytes in the sorted records are unobserved. */
typedef struct Sub0042B850Point {
    short x;
    short y;
} Sub0042B850Point;
typedef char Sub0042B850PointSize[(sizeof(Sub0042B850Point) == 4) ? 1 : -1];

int sub_0042B850(const Sub0042B850Point *first,
                 const Sub0042B850Point *second)
{
    if (first->x < second->x)
        return -1;
    if (first->x > second->x)
        return 1;
    if (first->y < second->y)
        return -1;
    return first->y > second->y;
}
