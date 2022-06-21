struct Process
{
    int name;
    struct Process *next;
    struct Process *prev;
    int arrival;
    int runTime;
    int status;
};