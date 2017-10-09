/*
 * Chromosom.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: Wojtek
 */
#include "Chromosom.h"
#include <ctime>
#include <limits>
#include <cstdlib>

Chromosom::Chromosom() {
    fitness=std::numeric_limits<int>::max();

}

Chromosom::Chromosom(vector<int> genotype) {
	this->genotype=genotype;
	fitness=std::numeric_limits<int>::max();
}

Chromosom::~Chromosom() {
	// TODO Auto-generated destructor stub
}


void Chromosom::setJobDatabase(Database* jobDatabase)
{
    Chromosom::jobDatabase=jobDatabase;
}

int Chromosom::getFitness() const {
	return this->fitness;
}

const vector<int>& Chromosom::getGenotype() const{
	return this->genotype;
}

Database& Chromosom::getJobDatabase()  {
    return *(Chromosom::jobDatabase);
}


void Chromosom::setGenotype(vector<int>& genotype) {
	this->genotype=genotype;
}

void Chromosom::generateRandomGenotype() {
    if(jobDatabase==NULL)
        return;
    int machineCount=jobDatabase->getMachinesAmount();
    int jobCount=jobDatabase->getJobsAmount();
    this->genotype=vector <int> (machineCount*jobCount,0);
    vector <int> taskScheduled (jobCount,0);
	int jobID;
	for(vector<int>::iterator it=genotype.begin();it!=genotype.end();it++)
	{
	    do
	    {
	        jobID=rand()%jobCount;
	    }
	    while(taskScheduled[jobID]>=machineCount);
	    taskScheduled[jobID]++;
	    *it=jobID;
	}

}

int Chromosom::countFitness() { //dzia��a przy numeracji maszyn i job��w od 0 - do ustalenia
    int machineCount=jobDatabase->getMaxMachineID()+1;
    int jobCount=jobDatabase->getJobsAmount();
    if(!isValid())
        return fitness;
    vector<int> machineSchedule(machineCount,0);	//!< Informacje o zajetosci maszyn.
	vector<int> jobSchedule(jobCount,0);	//!< Informacje o postepach prac.
	vector<int> currentTaskCount(jobCount,0);
	int startingfit=0;
	int currentTasknum;
	int currentMachineId;
    int jobstarttime;
	for(vector<int>::iterator it=genotype.begin();it!=genotype.end();it++)
	{
	    currentTasknum=currentTaskCount[*it];
       // cout<<"Przed current get machine ID cuurent task num: "<<currentTasknum<<" a job"<<*it<<endl;
        //cout<<flush;
        currentMachineId=jobDatabase->getJobs()[*it].getTaskList()[currentTasknum].getMachine()->getId();
	   // cout<<"Current job num: "<<(*it)<<" current machined ID: "<<currentMachineId<<"task of the job: "<<currentTasknum<<"time of the task"<<jobDatabase.getJobs()[*it].getTaskList()[currentTasknum].getTime()<<endl;
	    currentTaskCount[*it]++;

	    if(machineSchedule[currentMachineId]>jobSchedule[*it])
        {
            jobstarttime=machineSchedule[currentMachineId];
            jobSchedule[*it]=machineSchedule[currentMachineId]+jobDatabase->getJobs()[*it].getTaskList()[currentTasknum].getTime();
        }
        else
        {
             jobstarttime=jobSchedule[*it];
             jobSchedule[*it]+=jobDatabase->getJobs()[*it].getTaskList()[currentTasknum].getTime();
        }

        machineSchedule[currentMachineId]=jobstarttime+jobDatabase->getJobs()[*it].getTaskList()[currentTasknum].getTime();
	}
	for(vector<int>::iterator it=jobSchedule.begin();it!=jobSchedule.end();it++)
	    if(*it>startingfit)
            startingfit=*it;

    this->fitness=startingfit;
    machineSchedule.clear();
    jobSchedule.clear();
    currentTaskCount.clear();
    return this->fitness;
}

void Chromosom::printGenotype() const
{
    for(vector<int>::const_iterator it=genotype.begin();it!=genotype.end();it++)
        cout<<*it<<" ";
    cout<<endl;
}

void Chromosom::printChromosom() const
{
    cout<<"Fitness:"<<setw(4)<<fitness<<" |";
    cout<<" Genotype: ";
    for(vector<int>::const_iterator it=genotype.begin();it!=genotype.end();it++)
        cout<<setw(2)<<*it<<" ";
    cout<<endl;
}

void Chromosom::updateDatabaseWithStartTimes()
{
    if(jobDatabase==NULL)
        return;
    int machineCount=jobDatabase->getMaxMachineID()+1;
    int jobCount=jobDatabase->getJobsAmount();
    vector<int> machineSchedule(machineCount,0);	//!< Informacje o zajetosci maszyn.
	vector<int> jobSchedule(jobCount,0);	//!< Informacje o postepach prac.
	vector<int> currentTaskCount(jobCount,0);
	int currentTasknum;
	int currentMachineId;
    int jobstarttime;
	for(vector<int>::iterator it=genotype.begin();it!=genotype.end();it++)
	{
	    currentTasknum=currentTaskCount[*it];
        currentMachineId=jobDatabase->getJobs()[*it].getTaskList()[currentTasknum].getMachine()->getId();
	    currentTaskCount[*it]++;

	    if(machineSchedule[currentMachineId]>jobSchedule[*it])
	    {
            jobstarttime=machineSchedule[currentMachineId];
            jobDatabase->getJobs()[*it].changeTaskStart(currentMachineId,machineSchedule[currentMachineId]);
            jobSchedule[*it]=machineSchedule[currentMachineId]+jobDatabase->getJobs()[*it].getTaskList()[currentTasknum].getTime();
	    }
	    else
	    {
            jobstarttime=jobSchedule[*it];
            jobDatabase->getJobs()[*it].changeTaskStart(currentMachineId,jobSchedule[*it]);
            jobSchedule[*it]+=jobDatabase->getJobs()[*it].getTaskList()[currentTasknum].getTime();
	    }
        machineSchedule[currentMachineId]=jobstarttime+jobDatabase->getJobs()[*it].getTaskList()[currentTasknum].getTime();
	}

}

void Chromosom::setRandomFitness()
{
    this->fitness=rand()%1000;
}


bool Chromosom::isValid()
{
    if(jobDatabase==NULL)
        return false;
    int machineCount=jobDatabase->getMachinesAmount();
    int jobCount=jobDatabase->getJobsAmount();
    vector<int> taskCount(jobCount,0);
    for(vector<int>::iterator it=genotype.begin();it!=genotype.end();it++)
    {
        taskCount[*it]++;
    }
    for(vector<int>::iterator it=taskCount.begin();it!=taskCount.end();it++)
    {
        if(*it!=machineCount)
            return false;
    }
    return true;


}

bool Chromosom::repairChromosom()
{
    if(jobDatabase==NULL)
        return false;
    int jobCount=jobDatabase->getJobsAmount();
    if (isValid())
        return false;

    vector<int> taskCount(jobCount,0);
    vector<int> jobsleft;
    int rand1,rand2;

    for(vector<int>::iterator it=genotype.begin();it!=genotype.end();it++)
    {
        taskCount[*it]++;
    }


    for(vector<int>::iterator it=taskCount.begin();it!=taskCount.end();it++)
    {

        for(int i=*it;i<jobCount;i++)
            jobsleft.push_back(it-taskCount.begin());
    }

    for(int i=0;i<RANDOMREPAIR;i++)
    {
        rand1=rand()%jobsleft.size();
        rand2=rand()%jobsleft.size();
        swap(jobsleft[rand1],jobsleft[rand2]);

    }

    taskCount=vector<int>(jobCount,0);

    for(vector<int>::iterator it=genotype.begin();it!=genotype.end();it++)
    {
        taskCount[*it]++;
        if(taskCount[*it]>jobCount)
        {
            *it=jobsleft.back();
            jobsleft.pop_back();
        }
    }
    return true;

}

Database* Chromosom::jobDatabase=NULL;
