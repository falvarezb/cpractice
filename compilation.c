
#define MYMACRO 1

int main(int argc, char const *argv[])
{
    #ifdef MYMACRO
    int a = MYMACRO;
    #else
    int a = 2;
    #endif
    return 0;
}
