#include "Database.h"

Database::Database(){

}

Database::~Database(){
	this->clearDatabase();
}

int Database::getJobsAmount()const{
	return jobs.size();
}

int Database::getMachinesAmount()const{
	return machines.size();
}

bool Database::readFromFile(const char* filename){
	clearDatabase();
	bool result = false;
	ifstream inputFile;
	int jobCount, machinesCount, tmp, flag=0;
	string data;
	vector<string> fields;
	vector<int> newMachines, times;

	inputFile.open(filename, ios::in);
	if(inputFile.good()){
		int pos = 0;
		getline(inputFile, data);

		while(data[pos] != 'x'){
			pos++;
		}
		istringstream(data.substr(0,pos)) >> jobCount;
		istringstream(data.substr(pos+1,data.length()-pos-1)) >> machinesCount;

		pos = 0;
		flag = 0;
		int lineCounter = 0;
		while(getline(inputFile,data)){
			pos = 0;
            for(unsigned int i=0; i<data.length(); i++){
				if(data[i] == ' '){
					istringstream(data.substr(pos, i-pos)) >> tmp;
					pos = i+1;
					if(flag == 0){
						newMachines.push_back(tmp);
						flag = 1;
					}else if(flag == 1){
						times.push_back(tmp);
						flag = 0;
					}
				}
			}
			istringstream(data.substr(pos, data.length()-pos)) >> tmp;
			if(flag == 0){
				newMachines.push_back(tmp);
				flag = 1;
			}else{
				times.push_back(tmp);
				flag = 0;
			}
			lineCounter++;
		}
		if(lineCounter == jobCount && newMachines.size() == jobCount*machinesCount && times.size() == jobCount*machinesCount){
			for(int i=0; i<jobCount; i++){
				this->addJob();
				int timeSummary=0;
				for(int j=0; j<machinesCount; j++){
					int number = i*machinesCount+j;
					if(machineExists(newMachines[number])){
						jobs.back().addTask(this->getMachine(newMachines[number]), timeSummary, times[number]);
					}else{
						jobs.back().addTask(this->addMachine(newMachines[number]), timeSummary, times[number]);
					}
					timeSummary += times[number];
				}
			}
			result = true;
		}else{
			cout << "Nieprawid³owa forma pliku." << endl;
		}
	}else{
		cout << "Wyst¹pi³ b³¹d podczas odczytu pliku." << endl;
	}

	inputFile.close();
	return result;
}

bool Database::saveToFile(const char* filename){
	bool result = false;
	ofstream outputFile;
	outputFile.open(filename, ios::out | ios::trunc);
	if(outputFile.is_open()){
		outputFile << jobs.size() << "x" << machines.size();
        for(unsigned int i=0; i<jobs.size(); i++){
			outputFile << endl;
			vector<Task> tasks = jobs[i].getTaskList();
            for(unsigned int j=0; j<tasks.size(); j++){
				if(j != 0)
					outputFile << " ";
				outputFile << tasks[j].getMachine()->getId() << " ";
				outputFile << tasks[j].getTime();
			}
		}
	}else{
		cout << "Nie uda³o siê otworzyæ pliku." << endl;
	}
	outputFile.close();
	return result;
}

Machine* Database::getMachine(int id){
	Machine *result = NULL;
    for(unsigned int i=0; i<machines.size(); i++){
		if(machines[i]->getId() == id){
			result = machines[i];
			break;
		}
	}
	return result;
}

bool Database::machineExists(int id){
	bool result = false;
	if(getMachine(id) != 0)
		result = true;
	return result;
}

Machine* Database::addMachine(int id){
	Machine *newMachine = new Machine(id);
	this->machines.push_back(newMachine);
	return newMachine;
}

Job* Database::addJob(Job newJob){
	this->jobs.push_back(newJob);
	return &(jobs.back());
}

Job* Database::addJob(){
	Job newJob;
	this->jobs.push_back(newJob);
	return &(jobs.back());
}

void Database::deleteMachine(int id){
    unsigned int i = 0;
	if(machineExists(id)){
		for(i=0; i<jobs.size(); i++){
			jobs[i].deleteTask(id);
		}
		i = 0;
		while(machines[i]->getId() != id)
			i++;
		if(i < machines.size()){
			delete machines[i];
			machines.erase(machines.begin()+i);
		}
	}else{
		cout << "Podana maszyna nie istnieje." << endl;;
	}
}

void Database::deleteJob(unsigned int num){
	if(jobs.size()>0 && num < jobs.size()){
		jobs.erase(jobs.begin()+num);
	}
}

Database* Database::generateRandomData(int jobCount, int machinesCount){
    int randMachine,timeSummary, randTime;
	vector<int> tempVector;
	if(jobCount>0 && machinesCount>0){
		clearDatabase();
		for(int i=0; i<machinesCount; i++){
			this->addMachine(i);
			tempVector.push_back(i);
		}

		for(int i=0; i<jobCount; i++){
			this->addJob();
			timeSummary = 0;

			for(int j=0; j<machinesCount; j++){
				randMachine = rand() % machinesCount;
				while(jobs.back().isMachineUsed(randMachine))
					randMachine = rand() % machinesCount;
				randTime = rand() % 20;
				jobs.back().addTask(this->getMachine(randMachine), timeSummary, randTime);
				timeSummary += randTime;
			}
		}
	}

	return this;
}

void Database::clearDatabase(){
	jobs.clear();
    for(unsigned int i=0; i<machines.size(); i++)
		delete machines[i];
	machines.clear();
}

void Database::resetDatabase(){
    for(unsigned int i=0; i<jobs.size(); i++){
		jobs[i].resetTimetable();
	}
}

void Database::presentData(){
	cout << endl << "Prezentujê dane:" << endl;
	cout <<  "<maszyna>(<d³ugosc>/<start>)" << endl << endl;
    for(unsigned int i=0; i<jobs.size(); i++){
		vector<Task> tasks = jobs[i].getTaskList();
        for(unsigned int j=0; j<tasks.size(); j++){
			cout << jobs[i].getTaskList()[j].getMachine()->getId() << "(";
			cout << jobs[i].getTaskList()[j].getTime() << "/";
			cout << jobs[i].getTaskList()[j].getStart() << ")  ";
		}
		cout << endl;
	}
	cout << endl;
}

bool Database::checkDatabase(){
	bool result = true;
	int machinesCount = machines.size();
    for(unsigned int i=0; i<jobs.size(); i++){
		if( jobs[i].getTaskList().size() != machinesCount )
			result = false;
	}
	return result;
}

int Database::getLongestJobDuration(){
	int maxDuration = 0;
	int jobDuration = 0;
    for(unsigned int i=0; i<jobs.size(); i++){
		vector <Task> &tasks = jobs[i].getTaskList();
		if(tasks.size() > 0){
			jobDuration = tasks[tasks.size()-1].getStart() + tasks[tasks.size()-1].getTime();
			if(jobDuration > maxDuration)
				maxDuration = jobDuration;
		}
	}
	return maxDuration;
}

int Database::getMaxMachineID()
{
    int maxid=-1;
    for(vector<Machine*>::iterator it=machines.begin();it!=machines.end();it++)
    {
        if((*it)->getId()>maxid)
            maxid=(*it)->getId();
    }
    return maxid;
}

void Database::onNewDataStructure(DataStructure* dtStructure)
{
    switch(dtStructure->opType)
    {
    case DataStructure::DB_FILE_LOAD:
        this->readFromFile((dtStructure->dtfile).c_str());  //TODO kontrola bledu
        emit databaseChanged(this);
        break;
    case DataStructure::DB_FILE_SAVE:
        this->saveToFile((dtStructure->dtfile).c_str());  //TODO kontrola bledu
        break;
    case DataStructure::DB_GEN_RND:
        this->generateRandomData((rand()%50+1), (rand()%50+1));
        emit databaseChanged(this);
        break;
    case DataStructure::DB_RESET:
        this->resetDatabase();
        emit databaseChanged(this);
        break;
    case DataStructure::DB_CLEAR:
        this->clearDatabase();
        emit databaseChanged(this);
        break;
    case DataStructure::DB_JOB_ADD:
        this->addJob();
        emit databaseChanged(this);
        break;
    case DataStructure::DB_MACHINE_ADD:
    {
        vector <Machine*> machines = this->getMachines();
        unsigned int i= 0;
        while(i<machines.size() && this->machineExists(i))
            i++;
        this->addMachine(i);
        emit databaseChanged(this);
    }
        break;
    case DataStructure::DB_TASK_ADD:
    {
        Job &selectedJob = this->getJobs()[dtStructure->jobID];
        Machine* selectedMachine = this->getMachine(dtStructure->machineID);
        selectedJob.addTask(selectedMachine,0,dtStructure->tasktime);
        emit databaseChanged(this);
    }
        break;
    case DataStructure::DB_DELETE_JOB:
        this->deleteJob(dtStructure->jobID);
        emit databaseChanged(this);
        break;
    case DataStructure::DB_DELETE_MACHINE:
        this->deleteMachine(dtStructure->machineID);
        emit databaseChanged(this);
        break;
    case DataStructure::DB_DELETE_TASK:
        this->getJobs()[dtStructure->jobID].deleteTask(dtStructure->machineID);
        emit databaseChanged(this);
        break;
    case DataStructure::DB_EDIT:
    {
        Job &selectedJob = this->getJobs()[dtStructure->jobID];
        Task &selectedTask = selectedJob.getTaskList()[dtStructure->taskID];
        if((dtStructure->machineID)!=-1)
        selectedTask.setMachine(this->getMachine(dtStructure->machineID));
        selectedTask.setTime(dtStructure->tasktime);
        if(dtStructure->oldpos!=dtStructure->newpos)
        {
            selectedJob.changeTaskPosition(dtStructure->oldpos, dtStructure->newpos);
        }
        emit databaseChanged(this);
    }
        break;
    }
    delete dtStructure;
}

void Database::completeJobs(){
    for(int i=0; i<jobs.size(); i++){
        Job &currJob = jobs[i];
        for(int j=0; j<machines.size(); j++){
            Machine *checkMachine = machines[j];
            if(!currJob.isMachineUsed(checkMachine->getId())){
                currJob.addTask(checkMachine, 0, 0);
            }
        }
    }
}
