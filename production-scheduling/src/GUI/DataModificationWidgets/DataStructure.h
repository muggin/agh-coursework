#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#include <string>

struct DataStructure
{
    enum OperationType
    {
        DB_FILE_LOAD,DB_FILE_SAVE,DB_JOB_ADD,DB_MACHINE_ADD,DB_TASK_ADD,
        DB_GEN_RND,DB_RESET, DB_CLEAR,DB_DELETE_JOB,DB_DELETE_MACHINE
        ,DB_DELETE_TASK,DB_EDIT
    };
    OperationType opType;
    std::string dtfile;
    int jobID;
    int oldpos;
    int newpos;
    int tasktime;
    int taskID;
    int machineID;
};


#endif // DATASTRUCTURE_H
