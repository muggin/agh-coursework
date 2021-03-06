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
 * Klasa obiektu reprezentującego pojedyncze zadanie w ramach danej pracy.
 */
class Task{
private:
	Machine* machine;	//!< Wskaźnik do maszyny użytej w zadaniu.
	int start;		//!< Czas rozpoczęcia zadania.
	int time;		//!< Czas trwania zadania.

public:
	/**
	 * Konstruktor klasy.
	 * \param machine Wskaźnik do maszyny użytej przy zadaniu.
	 * \param startTimr Czas rozpoczęcia zadania.
	 * \param duration Czas trwania zadania.
	 */
	Task(Machine* machine, int startTime, int duration);

	/**
	 * Destruktor klasy.
	 */
	~Task();

	/**
	 * Getter maszyny.
	 * \return Wskaźnik do maszyny.
	 */
    Machine* getMachine() const {
	  	return machine;
	}

	/**
	 * Setter maszyny.
	 * \param machine Wskaźnik do maszyny.
	 */
	void setMachine(Machine* machine) {
	  	this->machine = machine;
	}

	/**
	 * Getter czasu początkowego zadania.
	 * \return Czas rozpoczęcia zadania
	 */
	int getStart() const {
		return start;
	}

	/**
	 * Setter czasu początkowego zadania.
	 * \param start Czas rozpoczęcia zadania.
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
