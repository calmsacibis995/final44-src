h24192
s 00016/00000/00000
d D 5.1 90/06/25 14:58:07 bostic 1 0
c date and time created 90/06/25 14:58:07 by bostic
e
u
U
t
T
I 1

double
t(a, i)
        double a;
{
        fortran float sin(), cos();

        switch(i) {
        case 0:
                return (cos(a*(3.141592/180.)));
        case 1:
                return (sin(a*(3.141592/180.)));
        }
}

main() { printf("%g\n", t(90.,0)); }
E 1
