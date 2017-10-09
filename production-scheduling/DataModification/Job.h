/*
 * Job.h
 *
 *  Created on: 28 kwi 2014
 *      Author: Filson
 */

#ifndef JOB_H_
#define JOB_H_

#include <vector>
#include <iostream>
#include "Task.h"
#include "Machine.h"

using namespace std;
/**
 * Klasa obiektu reprezentuj�cego pojedy�cz� prac� do wykonania.
 */
class Job{
private:
	vector<Task> taskList;	//!< Wektor zada� dla danej pracy.

public:
	/**
	 * Konstruktor klasy.
	 */
	Job();

	/**
	 * Destruktor klasy.
	 */
	~Job();

	/**
	 * Getter waktora zada�.
	 * \return Referencja do wektora zada�.
	 */
	vector<Task>& getTaskList(){
		return taskList;
	}
    const vector<Task>& getConstTaskList()const {
        return taskList;
    }

	/**
	 * Metoda dodaj�ca task do listy.
	 * \param machine Wska�nik do obiektu maszyny u�ytej do danego zadania.
	 * \param startTime Moment rozpocz�cia zadania.
	 * \param duration Czas trwania zadania.
	 */
	void addTask(Machine* machine, int startTime, int duration);

	/**
	 * Metoda dodaj�ca task do listy.
	 * \param newTask Obiekt klasy Task z ustawionymi polami.
	 */
	void addTask(Task newTask);

	/**
	 * Metoda usuwaj�ca z listy task dotycz�cy podanej maszyny.
	 * \param machineId Id maszyny, kt�rej zadanie dotyczy.
	 */
	void deleteTask(int machineId);

	/*
	 * Metoda zmieniaj�ca czas trwania tasku dotycz�cego podanej maszyny.
	 * \param machineId Id maszyny, kt�rej zadanie dotyczy.
	 * \param duration Czas trwania zadania do ustawienia.
	 */
	void changeTaskDuration(int machineId, int duration);

	/**
	 * Metoda zmieniaj�ca czas rozpocz�cia tasku dotycz�cego podanej maszyny.
	 * \param machineId Id maszyny, kt�rej zadanie dotyczy.
	 * \param time Nowy czas rozpocz�cia zadania.
	 */
	void changeTaskStart(int machineId, int time);

	/**
	 * Funkcja sprawdzaj�ca czy podana maszyna zosta�a ju� przypisana do listy zada�.
	 * \param machineId Id maszyny, kt�r� sprawdzamy.
	 * \return True - jesli maszyna zosta�a ju� u�yta; False - w przeciwnym wypadku.
	 */
    bool isMachineUsed(int machineId)const ;

	/**
	 * Metoda zmieniaj�ca kolejnos� task�w
	 * \param currPos Task, kt�rego miejsce wykonania zmieniamy.
	 * \param newPos Miejsce wykonania jakie chcemy ustawi�.
	 */
    void changeTaskPosition(unsigned int currPos,unsigned  int newPos);

	/**
	 * Metoda zeruj�ca czasy rozpocz�cia task�w (Wszystkie taski wykonywane w spos�b ci�g�y.
	 */
	void resetTimetable();
};



#endif /* JOB_H_ */
