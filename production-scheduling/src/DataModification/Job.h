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
 * Klasa obiektu reprezentuj¹cego pojedyñcz¹ pracê do wykonania.
 */
class Job{
private:
	vector<Task> taskList;	//!< Wektor zadañ dla danej pracy.

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
	 * Getter waktora zadañ.
	 * \return Referencja do wektora zadañ.
	 */
	vector<Task>& getTaskList(){
		return taskList;
	}
    const vector<Task>& getConstTaskList()const {
        return taskList;
    }

	/**
	 * Metoda dodaj¹ca task do listy.
	 * \param machine WskaŸnik do obiektu maszyny u¿ytej do danego zadania.
	 * \param startTime Moment rozpoczêcia zadania.
	 * \param duration Czas trwania zadania.
	 */
	void addTask(Machine* machine, int startTime, int duration);

	/**
	 * Metoda dodaj¹ca task do listy.
	 * \param newTask Obiekt klasy Task z ustawionymi polami.
	 */
	void addTask(Task newTask);

	/**
	 * Metoda usuwaj¹ca z listy task dotycz¹cy podanej maszyny.
	 * \param machineId Id maszyny, której zadanie dotyczy.
	 */
	void deleteTask(int machineId);

	/*
	 * Metoda zmieniaj¹ca czas trwania tasku dotycz¹cego podanej maszyny.
	 * \param machineId Id maszyny, której zadanie dotyczy.
	 * \param duration Czas trwania zadania do ustawienia.
	 */
	void changeTaskDuration(int machineId, int duration);

	/**
	 * Metoda zmieniaj¹ca czas rozpoczêcia tasku dotycz¹cego podanej maszyny.
	 * \param machineId Id maszyny, której zadanie dotyczy.
	 * \param time Nowy czas rozpoczêcia zadania.
	 */
	void changeTaskStart(int machineId, int time);

	/**
	 * Funkcja sprawdzaj¹ca czy podana maszyna zosta³a ju¿ przypisana do listy zadañ.
	 * \param machineId Id maszyny, któr¹ sprawdzamy.
	 * \return True - jesli maszyna zosta³a ju¿ u¿yta; False - w przeciwnym wypadku.
	 */
    bool isMachineUsed(int machineId)const ;

	/**
	 * Metoda zmieniaj¹ca kolejnosæ tasków
	 * \param currPos Task, którego miejsce wykonania zmieniamy.
	 * \param newPos Miejsce wykonania jakie chcemy ustawiæ.
	 */
    void changeTaskPosition(unsigned int currPos,unsigned  int newPos);

	/**
	 * Metoda zeruj¹ca czasy rozpoczêcia tasków (Wszystkie taski wykonywane w sposób ci¹g³y.
	 */
	void resetTimetable();
};



#endif /* JOB_H_ */
