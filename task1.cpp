#include "task1.h"

int executeTask()
{
	int P, T, M;
	ifstream fin(T1_DATA_FILE);
	fin >> P >> T >> M;

	// fill vectors with max values
	vector<int>* arrKnownTasksVectors = new vector<int>[T];
	for (int i = 0; i < T; i++)
		for (int j = 1; j <= P; j++)
			arrKnownTasksVectors[i].push_back(j);

	// read partisipant-task data
	for (int i = 0; i < M; i++) {
		int participant, taskNum;
		fin >> participant >> taskNum;
		taskNum--; // to start from zero
		for (auto iter = arrKnownTasksVectors[taskNum].begin();
			iter != arrKnownTasksVectors[taskNum].end();
			iter++)
				if (*iter == participant) {
					arrKnownTasksVectors[taskNum].erase(iter);
					break;
			}
	}

	vector<int> vecOfMostPopularTasks; // most unpopular :)
	int maxlen = -1;
	for (int tasknum = 0; tasknum < T; tasknum++) {

		//cout << arrKnownTasksVectors[tasknum].size()  << endl;
		int participantAmount = arrKnownTasksVectors[tasknum].size();
		if (participantAmount > maxlen) {
			vecOfMostPopularTasks.clear();
			vecOfMostPopularTasks.push_back(tasknum);
			maxlen = participantAmount;
			//continue;
		}
		else if (participantAmount == maxlen) {
			vecOfMostPopularTasks.push_back(tasknum);
		}
	}

	vector<int> vecOfCounters;
	int counter = 0;

	// find equal sets of participants
	for (int setnum = 0; setnum < vecOfMostPopularTasks.size(); setnum++) {
		counter = 0;
		for (int setnum2 = 0; setnum2 < vecOfMostPopularTasks.size(); setnum2++) {
			if (setnum == setnum2)
				continue;
			int task1num = vecOfMostPopularTasks[setnum];
			int task2num = vecOfMostPopularTasks[setnum2];
			if (arrKnownTasksVectors[task1num] == arrKnownTasksVectors[task2num]) {
				counter++;
			}
		}
		vecOfCounters.push_back(counter);
	}

	// find max from counters

	int maxCounter = -1;
	int maxCounterIdx = 0; // for vecOfMostPopularTasks
	for (int i = 0; i < vecOfCounters.size(); i++) {
		if (vecOfCounters[i] > maxCounter) {
			maxCounter = vecOfCounters[i];
			maxCounterIdx = i;
		}		
	}

	// print
	cout << arrKnownTasksVectors[vecOfMostPopularTasks[maxCounterIdx]].size() << " " << maxCounter + 1 << endl;

	auto vecParticipants = arrKnownTasksVectors[vecOfMostPopularTasks[maxCounterIdx]];
	for (int i = 0; i < T; i++)
		if (arrKnownTasksVectors[i] == vecParticipants)
			cout << i + 1 << " ";
		

	delete[] arrKnownTasksVectors;
	return 0;
}
