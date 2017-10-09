#include "Job.h"

Job::Job(){

}

Job::~Job(){
	this->taskList.clear();
}

void Job::addTask(Machine* machine, int startTime, int duration){
	if( !isMachineUsed(machine->getId()) ){
		int minStartTime = 0;
		if(taskList.size()!=0)
			minStartTime = taskList.back().getStart() + taskList.back().getTime();
		if( startTime < minStartTime )
			startTime = minStartTime;
		Task newTask(machine, startTime, duration);
		this->taskList.push_back(newTask);
	}
}

void Job::addTask(Task newTask){
	if( !isMachineUsed(newTask.getMachine()->getId()) ){
		int minStartTime = taskList.back().getStart() + taskList.back().getTime();
		if( newTask.getStart() < minStartTime )
			newTask.setStart(minStartTime);
		taskList.push_back(newTask);
	}
}

void Job::deleteTask(int machineId){
    unsigned int i=0;
	while(i<=taskList.size()-1 && taskList[i].getMachine()->getId()!=machineId){
		i++;
	}
	if(i < taskList.size()){
		taskList.erase(taskList.begin()+i);
		resetTimetable();
	}
}

void Job::changeTaskDuration(int machineId, int duration){
    unsigned int i=0;
	if(duration >= 0){
		while(i<=taskList.size()-1 && taskList[i].getMachine()->getId()!=machineId){
			i++;
		}
		if(i < taskList.size()){
			taskList[i].setTime(duration);
			resetTimetable();
		}
	}
}

void Job::changeTaskStart(int machineId, int time){
    unsigned int i=0;
	if(time >= 0){
		while(i<=taskList.size()-1 && taskList[i].getMachine()->getId()!=machineId){
			i++;
		}
		if(i<taskList.size())
			taskList[i].setStart(time);
	}
}

bool Job::isMachineUsed(int machineId)const {
	bool result = false;
    for(unsigned int i=0; i<taskList.size(); i++){
		if(taskList[i].getMachine()->getId()==machineId){
			result = true;
			break;
		}
	}
	return result;
}

void Job::changeTaskPosition(unsigned int currPos,unsigned int newPos){
	if( (currPos < taskList.size()) && (newPos < taskList.size()) && (currPos != newPos) ){
		Task temp = taskList[currPos];
		taskList.erase(taskList.begin() + currPos);
		taskList.insert(taskList.begin() + newPos, temp);
		resetTimetable();
	}
}

void Job::resetTimetable(){
	int timeSummary = 0;
    for(unsigned int i=0; i<taskList.size(); i++){
		taskList[i].setStart(timeSummary);
		timeSummary += taskList[i].getTime();
	}
}
