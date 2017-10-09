#include "Task.h"

Task::Task(Machine* machine, int startTime, int duration){
	this->machine = machine;
	this->start = startTime;
	this->time = duration;
}

Task::~Task(){

}
