/*
 * Task.h
 *
 *  Created on: 28 kwi 2014
 *      Author: Filson
 */

#ifndef TASK_H_
#define TASK_H_

#include "Machine.h"

using namespace std;

/**
 * Klasa obiektu reprezentuj�cego pojedyncze zadanie w ramach danej pracy.
 */
class Task{
private:
	Machine* machine;	//!< Wska�nik do maszyny u�ytej w zadaniu.
	int start;		//!< Czas rozpocz�cia zadania.
	int time;		//!< Czas trwania zadania.

public:
	/**
	 * Konstruktor klasy.
	 * \param machine Wska�nik do maszyny u�ytej przy zadaniu.
	 * \param startTimr Czas rozpocz�cia zadania.
	 * \param duration Czas trwania zadania.
	 */
	Task(Machine* machine, int startTime, int duration);

	/**
	 * Destruktor klasy.
	 */
	~Task();

	/**
	 * Getter maszyny.
	 * \return Wska�nik do maszyny.
	 */
    Machine* getMachine() const {
	  	return machine;
	}

	/**
	 * Setter maszyny.
	 * \param machine Wska�nik do maszyny.
	 */
	void setMachine(Machine* machine) {
	  	this->machine = machine;
	}

	/**
	 * Getter czasu pocz�tkowego zadania.
	 * \return Czas rozpocz�cia zadania
	 */
	int getStart() const {
		return start;
	}

	/**
	 * Setter czasu pocz�tkowego zadania.
	 * \param start Czas rozpocz�cia zadania.
	 */
	void setStart(int start) {
		this->start = start;
	}

	/**
	 * Getter czasu trwania zadania.
	 * \return Czas trwania zadania
	*/
	int getTime() const {
		return time;
	}

	/**
	 * Setter czasu trwania zadania.
	 * \param time Czas trwania zadania.
	 */
	void setTime(int time) {
		this->time = time;
	}
};
#endif /* TASK_H_ */
