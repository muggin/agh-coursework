/*
 * Database.h
 *
 *  Created on: 28 kwi 2014
 *      Author: Filson
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include "Job.h"
#include <QObject>
#include "Machine.h"
#include "../GUI/DataModificationWidgets/DataStructure.h"
#include <iomanip>

using namespace std;
/**
 * Klasa obiektu reprezentuj�cego dane wejsciowe programu.
 */
class Database: public QObject{
    Q_OBJECT

private:
	vector<Job> jobs;			//!< Lista prac, dla kt�rych jest generowany harmonogram.
	vector<Machine*> machines;	//!< Lista wska�nik�w do dost�pnych maszyn.

public:
	/**
	 * Konstruktor klasy.
	 */
	Database();

	/**
	 * Destruktor klasy.
	 */
	~Database();

	/**
	 * Funkcja zwracaj�ca ilos� prac.
	 * \return Ilos� obiekt�w Job w bazie.
	 */
    int getJobsAmount() const;

	/**
	 * Funkcja zwracaj�ca ilos� maszyn.
	 * \return Ilos� obiekt�w Machine w bazie.
	 */
    int getMachinesAmount() const;
	/**
	 * Getter listy prac.
	 * \return Referencja listy prac.
	 */
	vector<Job>& getJobs(){
		return jobs;
	}

    const vector<Job>& getConstJobs() const{
        return jobs;
    }

    int getMaxMachineID();

	/**
	 * Getter listy maszyn.
	 * \return Referencja listy maszyn.
	 */
	vector<Machine*>& getMachines(){
		return machines;
	}

    const vector<Machine*>& getConstMachines()const{
        return machines;
    }

	/**
	 * Funkcja odczytuj�ca plik tekstowy z danymi wejsciowymi do programu.
	 * \param filename Sciezka do pliku.
	 * \return True - jesli odczyt przebiegnie pomyslnie; False - w przeciwnym wypadku.
	 */
	bool readFromFile(const char* filename);

	/**
	 * Funkcja zapisuj�ca podane dane wejsciowe do pliku.
	 * \param filename Sciezka do pliku.
	 * \return True - jesli zapis przebiegnie pomyslnie; False - w przeciwnym wypadku.
	 */
	bool saveToFile(const char* filename);

	/**
	 * Funkcja pobieraj�ca maszyn� z listy wszystkich maszyn w bazie.
	 * \param id Id poszukiwanej maszyny.
	 * \return Wska�nik do szukanej maszyny.
	 */
	Machine* getMachine(int id);

	/**
	 * Funkcja sprawdzaj�ca czy podana maszyna zosta�a ju� wpisana do bazy.
	 * \param id Id szukanej maszyny.
	 * \return True - jesli maszyna jest w bazie; False - w przeciwnym wypadku.
	 */
	bool machineExists(int id);

	/**
	 * Funkcja dodaj�ca wygenerowan� wczesniej prac� do bazy.
	 * \param newJob Obiekt klasy Job.
	 * \return Wska�nik do nowododanej pracy.
	 */
	Job* addJob(Job newJob);

	/**
	 * Funkcja dodaj�ca czyst� (bez dodanych task�w) prac�.
	 * \return Wska�nik do nowododanej pracy.
	 */
	Job* addJob();

	/**
	 * Funkcja dodaj�ca maszyn� do bazy.
	 * \param id Id nowej maszyny.
	 * \return Wska�nik do nowododanej maszyny.
	 */
	Machine* addMachine(int id);

	/**
	 * Metoda usuwaj�ca maszyn� z bazy.
	 * \param id Id usuwanej maszyny.
	 */
	void deleteMachine(int id);

	/**
	 * Metoda usuwaj�ca sekwencj� Joba.
	 * \param num Numer Joba do usuni�cia.
	 */
    void deleteJob(unsigned int num);

	/**
	 * Funkcja generuj�ca losowe dane wejsciowe do programu.
	 * \param jobCount Ilosc prac do wygenerowania.
	 * \param machinesCount Ilosc maszyn do u�ycia.
	 * \return Wska�nik do bie��cego obiektu klasy Database.
	 */
	Database* generateRandomData(int jobCount, int machinesCount);

	/**
	 * Metoda czyszcz�ca obiekt Database (czysci listy prac i maszyn).
	 */
	void clearDatabase();

	/**
	 * Metoda zeruj�ca dane wejsciowe programu (sprowadza dane do formu przed wykonaniem algorytmu).
	 */
	void resetDatabase();

	/**
	 * Metoda prezentuj�ca baz� danych (wypisywanie w konsoli).
	 */
	void presentData();


    /**
     * Funkcja sprawdza czy w sekwencjach wszystkich Job'�w u�ytko wszystkich maszyn w bazie.
     * \return True - jesli wszystko si� zgadza; False - w przeciwnym wypadku.
     */
    bool checkDatabase();

	/**
	 * Funkcja wyznaczaj�ca najd�u�szy czas trwania Joba w ca�ej bazie.
	 * \return Czas wykonania wszystkich task�w w bazie danych.
	 */
	int getLongestJobDuration();

signals:
    void databaseChanged(Database *);
public slots:
    void onNewDataStructure(DataStructure*);

    /**
     * Metoda uzupe�niaj�ca Joby o Taski zawieraj�ce nieu�yte maszyny (z zerowym czasem trwania
     */
    void completeJobs();
};



#endif /* DATABASE_H_ */
