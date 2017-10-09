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
 * Klasa obiektu reprezentuj¹cego dane wejsciowe programu.
 */
class Database: public QObject{
    Q_OBJECT

private:
	vector<Job> jobs;			//!< Lista prac, dla których jest generowany harmonogram.
	vector<Machine*> machines;	//!< Lista wskaŸników do dostêpnych maszyn.

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
	 * Funkcja zwracaj¹ca ilosæ prac.
	 * \return Ilosæ obiektów Job w bazie.
	 */
    int getJobsAmount() const;

	/**
	 * Funkcja zwracaj¹ca ilosæ maszyn.
	 * \return Ilosæ obiektów Machine w bazie.
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
	 * Funkcja odczytuj¹ca plik tekstowy z danymi wejsciowymi do programu.
	 * \param filename Sciezka do pliku.
	 * \return True - jesli odczyt przebiegnie pomyslnie; False - w przeciwnym wypadku.
	 */
	bool readFromFile(const char* filename);

	/**
	 * Funkcja zapisuj¹ca podane dane wejsciowe do pliku.
	 * \param filename Sciezka do pliku.
	 * \return True - jesli zapis przebiegnie pomyslnie; False - w przeciwnym wypadku.
	 */
	bool saveToFile(const char* filename);

	/**
	 * Funkcja pobieraj¹ca maszynê z listy wszystkich maszyn w bazie.
	 * \param id Id poszukiwanej maszyny.
	 * \return WskaŸnik do szukanej maszyny.
	 */
	Machine* getMachine(int id);

	/**
	 * Funkcja sprawdzaj¹ca czy podana maszyna zosta³a ju¿ wpisana do bazy.
	 * \param id Id szukanej maszyny.
	 * \return True - jesli maszyna jest w bazie; False - w przeciwnym wypadku.
	 */
	bool machineExists(int id);

	/**
	 * Funkcja dodaj¹ca wygenerowan¹ wczesniej pracê do bazy.
	 * \param newJob Obiekt klasy Job.
	 * \return WskaŸnik do nowododanej pracy.
	 */
	Job* addJob(Job newJob);

	/**
	 * Funkcja dodaj¹ca czyst¹ (bez dodanych tasków) pracê.
	 * \return WskaŸnik do nowododanej pracy.
	 */
	Job* addJob();

	/**
	 * Funkcja dodaj¹ca maszynê do bazy.
	 * \param id Id nowej maszyny.
	 * \return WskaŸnik do nowododanej maszyny.
	 */
	Machine* addMachine(int id);

	/**
	 * Metoda usuwaj¹ca maszynê z bazy.
	 * \param id Id usuwanej maszyny.
	 */
	void deleteMachine(int id);

	/**
	 * Metoda usuwaj¹ca sekwencjê Joba.
	 * \param num Numer Joba do usuniêcia.
	 */
    void deleteJob(unsigned int num);

	/**
	 * Funkcja generuj¹ca losowe dane wejsciowe do programu.
	 * \param jobCount Ilosc prac do wygenerowania.
	 * \param machinesCount Ilosc maszyn do u¿ycia.
	 * \return WskaŸnik do bie¿¹cego obiektu klasy Database.
	 */
	Database* generateRandomData(int jobCount, int machinesCount);

	/**
	 * Metoda czyszcz¹ca obiekt Database (czysci listy prac i maszyn).
	 */
	void clearDatabase();

	/**
	 * Metoda zeruj¹ca dane wejsciowe programu (sprowadza dane do formu przed wykonaniem algorytmu).
	 */
	void resetDatabase();

	/**
	 * Metoda prezentuj¹ca bazê danych (wypisywanie w konsoli).
	 */
	void presentData();


    /**
     * Funkcja sprawdza czy w sekwencjach wszystkich Job'ów u¿ytko wszystkich maszyn w bazie.
     * \return True - jesli wszystko siê zgadza; False - w przeciwnym wypadku.
     */
    bool checkDatabase();

	/**
	 * Funkcja wyznaczaj¹ca najd³u¿szy czas trwania Joba w ca³ej bazie.
	 * \return Czas wykonania wszystkich tasków w bazie danych.
	 */
	int getLongestJobDuration();

signals:
    void databaseChanged(Database *);
public slots:
    void onNewDataStructure(DataStructure*);

    /**
     * Metoda uzupe³niaj±ca Joby o Taski zawieraj±ce nieu¿yte maszyny (z zerowym czasem trwania
     */
    void completeJobs();
};



#endif /* DATABASE_H_ */
