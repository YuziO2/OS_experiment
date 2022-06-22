struct Process
{
    int name;
    struct Process *next;
    int arrival;
    int runTime;
    int status;
};