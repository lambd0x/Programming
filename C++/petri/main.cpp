#include <vector>
#include <string>
#include <iostream>
#include "class/mapatrem.h"
#include "class/threadtest.h"
#include "class/threads/thread.h"

#define DOWNlockNO 65364
#define DOWNlockNO2 84
#define DOWNlockYE 1113940

#define UPlockNO 65362
#define UPlockNO2 82
#define UPlockYE 1113938

#define ESClockNO 27
#define ESClockYE 1048603

//Terminal colors
#define RED         "\x1b[31m"
#define BLUE        "\x1b[34m"
#define WHITE       "\x1b[37m"
#define COLOR_RESET "\x1b[0m"

MapaTrem train;

using namespace std;

Mat trem1_vazio;
Mat trem1_cheio;

Mat trem2_vazio;
Mat trem2_cheio;

// Identified button pressed
int pressed = -1;
// Transfers the exec control between Train 1 and Train 2
int controlBack = -1;
// Informs each train that the other train is waiting
int waits = -1;

// Identify the number of tokens required per each petri net transition
vector<int> GetTokensPerTransitions(vector<vector<int>> &PRE)
{
	vector<int> l(20);
	int count = 0;
	for (unsigned int j = 0; j < PRE[0].size(); j++)
	{
		for (unsigned int i = 0; i < PRE.size(); i++)
		{
			count++;
			if (PRE[i][j] != 0)
			{
				l[j]++;
			}
		}
		count = 0;
	}
	return l;
}

// Get hold of the currently triggerable transitions
vector<int> GetActiveTransitions(vector<int> &M0, vector<int> &tokensPerTrans, vector<vector<int>> &PRE)
{
	vector<int> l{};
	for (unsigned int j = 0; j < PRE[0].size(); j++)
	{
		// Total of tokens required to trigger current transition
		int tTokens = tokensPerTrans[j];
		// Current amount of tokens meet
		int aTokens = 0;
		for (unsigned int i = 0; i < PRE.size(); i++)
		{
			if (PRE[i][j] != 0 && M0[i] == 1)
			{
				aTokens++;
			}
		}
		if (aTokens == tTokens)
		{
			//Add current transition to the list of triggerable transitions
			l.insert(l.end(), j);
		}
	}
	return l;
}

// Determines the transition to be executed in regard to train1 or train2 (pressed key)
int GetTransExec(unsigned int pressed, vector<int> &activeTrans, vector<int> &listTrain1, vector<int> &listTrain2)
{
	int transition = -1;
	// Transitions of train1
	if (pressed == 0)
	{
		for (auto trans : activeTrans)
			for (auto trans2 : listTrain1)
				if (trans == trans2)
					transition = trans;
	}
	// Transitions of train2
	else if (pressed == 1)
	{
		for (auto trans : activeTrans)
			for (auto trans2 : listTrain2)
				if (trans == trans2)
					transition = trans;
	}
	return transition;
}

// Moves the train in accordance to the transition executed
bool TrainMovesBaby(unsigned int id_trans)
{
	bool ok = false;
	// Train 1: transitions
	if (id_trans == 1)
	{
		train.Trem1Txt("Carregando trem 1 em Lucerne");
		// Loads train 1 with people
		train.SetMatTrain1(trem1_cheio);
		// Fakes the loading time
		Thread::SleepMS(3000);
		train.Trem1Txt("Estacao de Lucerne");
		//Transition finished
		ok = true;
	}
	else if (id_trans == 2)
	{
		bool B1Sensor = false;
		// Train 1 goes to Lucerne's rail
		// Starts slowly
		train.Trem1Txt("Estacao de Lucerne");
		for (float p = -train.GetTrain1Pos(); p <= -0.85f; p += 0.0005f)
		{
			train.SetTrain1Pos((-1) * p, train.GetTrain1Traj());
			Thread::SleepMS(10);
		}
		train.Trem1Txt("Trilhos de Lucerne");
		for (float p = -train.GetTrain1Pos(); ; p += 0.005f)
		{
			//Stops the train
			if (B1Sensor)
				break;
			train.SetTrain1Pos((-1) * p, train.GetTrain1Traj());
			Thread::SleepMS(10);
			if (train.B1())
				B1Sensor = true;
		}
		//Fix annoying decimal rep of mantissa
		train.SetTrain1Pos(0.5f, train.GetTrain1Traj());
		//Transition finished
		ok = true;
	}
	else if (id_trans == 3)
	{
		// Train 1 goes to Stans's rail (this very transition does nothing because its action is joined with transition 4)
		//Transition finished
		ok = true;
	}
	else if (id_trans == 4)
	{
		train.Trem1Txt("Trilhos de Stans");
		bool CSensor = false;
		// Train 1 goes from Lucerne's rail up to Engelberg's station
		train.Gate(1);
		// Train 1 goes from Lucerne's rail up to Stans' rail
		for (float p = -train.GetTrain1Pos(); p <= 0.0f; p += 0.005f)
		{
			train.SetTrain1Pos((-1) * p, train.GetTrain1Traj());
			Thread::SleepMS(10);
		}
		//Fix annoying decimal rep of mantissa
		train.SetTrain1Pos(0.0f, 0);
		// Train 1 goes from Stans' rail up to Engelberg's station
		for (float p = train.GetTrain1Pos(); p <= 0.8; p += 0.005f)
		{
			//Stops the train
			if (CSensor)
				break;
			//Stops the train
			train.SetTrain1Pos(p, train.GetTrain1Traj());
			Thread::SleepMS(10);
			if (train.C())
				CSensor = true;
		}
		// Decreases Train 1 speed
		train.Trem1Txt("Estacao de Engelberg");
		for (float p = train.GetTrain1Pos(); p <= 0.85; p += 0.0005f)
		{
			train.SetTrain1Pos(p, train.GetTrain1Traj());
			Thread::SleepMS(10);
		}
		//Fix annoying decimal rep of mantissa
		train.SetTrain1Pos(0.85f, train.GetTrain1Traj());
		// Transition finished
		ok = true;
	}
	else if (id_trans == 5)
	{
		train.Trem1Txt("Descarregando trem 1 em Engelberg");
		// Fakes the unloading time
		Thread::SleepMS(3000);
		// Train 1 goes to Lucerne's rail
		// Loads train 1 with people
		train.SetMatTrain1(trem1_vazio);
		//Transition finished
		ok = true;
	}
	else if (id_trans == 6)
	{
		// Train 1 goes to Stans's rail (this very transition does nothing because its action is joined with transition 7)
		//Transition finished
		ok = true;
	}
	else if (id_trans == 7)
	{
		bool B1Sensor = false;
		// Train 1 goes from Lucerne's rail up to Engelberg's station
		train.Gate(1);
		train.Trem1Txt("Estacao de Engelberg");
		// Train 1 goes Engelberg's station up to Stans' rail
		// Slowly starts
		for (float p = train.GetTrain1Pos(); p >= 0.8; p -= 0.0005f)
		{
			train.SetTrain1Pos(p, train.GetTrain1Traj());
			Thread::SleepMS(10);
		}
		train.Trem1Txt("Trilhos de Stans");
		// Max speed
		for (float p = train.GetTrain1Pos(); p >= 0.0; p -= 0.005f)
		{
			train.SetTrain1Pos(p, train.GetTrain1Traj());
			Thread::SleepMS(10);
		}
		//Fix annoying decimal rep of mantissa
		train.SetTrain1Pos(0.0f, 1);
		// Train 1 goes from Stans' rail up to Lucerne's rail
		for (float p = train.GetTrain1Pos(); ; p += 0.005f)
		{
			if (B1Sensor)
				break;
			train.SetTrain1Pos(p, train.GetTrain1Traj());
			Thread::SleepMS(10);
			if (train.B1())
				B1Sensor = true;
		}
		train.Trem1Txt("Trilhos de Lucerne");

		//Fix annoying decimal rep of mantissa
		train.SetTrain1Pos(0.5f, train.GetTrain1Traj());
		// Transition finished
		ok = true;
	}
	else if (id_trans == 0)
	{
		// Train 1 goes back to Lucerne's station
		bool A1Sensor = false;
		// Train 1 goes to Lucerne's rail
		for (float p = train.GetTrain1Pos(); ; p += 0.005f)
		{
			//Stops the train
			if (A1Sensor)
				break;
			train.SetTrain1Pos(p, train.GetTrain1Traj());
			Thread::SleepMS(10);
			if (train.A1())
				A1Sensor = true;
		}
		// Arrives slowly
		train.Trem1Txt("Estacao de Lucerne");
		for (float p = train.GetTrain1Pos(); p <= 0.9; p += 0.0005f)
		{
			train.SetTrain1Pos(p, train.GetTrain1Traj());
			Thread::SleepMS(10);
		}
		//Fix annoying decimal rep of mantissa
		train.SetTrain1Pos(0.9f, train.GetTrain1Traj());
		//Transition finished
		ok = true;
	}
	else if (id_trans == 8)
	{
		// Train 1 waits for switch G
		// Stops slowly
		train.Trem1Txt("Trilhos de Lucerne");
		for (float p = -train.GetTrain1Pos(); p <= -0.4f; p += 0.0005f)
		{
			train.SetTrain1Pos((-1) *p, train.GetTrain1Traj());
			Thread::SleepMS(10);
		}
		// Informs Train 2
		waits = 0;
		// Transfer to Train 2
		controlBack = 1;
		// Transition finished
		ok = true;
	}
	else if (id_trans == 18)
	{
		// Train 1 takes over switch G
		// Transition left empty because it is completed by transition 4
		// Transition finished
		ok = true;
	}

	// Train 2: transitions
	if (id_trans == 10)
	{
		train.Trem2Txt("Carregando trem 2 em Sarnen");
		// Loads train 2 with people
		train.SetMatTrain2(trem2_cheio);
		// Fakes the loading time
		Thread::SleepMS(3000);
		train.Trem2Txt("Estacao de Sarnen");
		// Transition finished
		ok = true;
	}
	else if (id_trans == 12)
	{
		bool B2Sensor = false;
		// Train 2 goes to Sarnen's rail
		// Starts slowly
		train.Trem2Txt("Estacao de Sarnen");
		for (float p = -train.GetTrain2Pos(); p <= -0.85f; p += 0.0005f)
		{
			train.SetTrain2Pos((-1) * p, train.GetTrain2Traj());
			Thread::SleepMS(10);
		}
		train.Trem2Txt("Trilhos de Sarnen");
		for (float p = -train.GetTrain2Pos(); ; p += 0.005f)
		{
			//Stops the train
			if (B2Sensor)
				break;
			train.SetTrain2Pos((-1) * p, train.GetTrain2Traj());
			Thread::SleepMS(10);
			if (train.B2())
				B2Sensor = true;
		}
		//Fix annoying decimal rep of mantissa
		train.SetTrain2Pos(0.5f, train.GetTrain2Traj());
		//Transition finished
		ok = true;
	}
	else if (id_trans == 9)
	{
		// Train 2 goes to Stans's rail (this very transition does nothing because its action is joined with transition 14)
		//Transition finished
		ok = true;
	}
	else if (id_trans == 14)
	{
		train.Trem2Txt("Trilhos de Stans");
		bool CSensor = false;
		// Train 2 goes from Lucerne's rail up to Engelberg's station
		train.Gate(0);
		// Train 2 goes from Lucerne's rail up to Stans' rail
		for (float p = -train.GetTrain2Pos(); p <= 0.0f; p += 0.005f)
		{
			train.SetTrain2Pos((-1) * p, train.GetTrain2Traj());
			Thread::SleepMS(10);
		}
		//Fix annoying decimal rep of mantissa
		train.SetTrain2Pos(0.0f, 0);
		// Train 2 goes from Stans' rail up to Engelberg's station
		for (float p = train.GetTrain2Pos(); p <= 0.8; p += 0.005f)
		{
			//Stops the train
			if (CSensor)
				break;
			//Stops the train
			train.SetTrain2Pos(p, train.GetTrain2Traj());
			Thread::SleepMS(10);
			if (train.C())
				CSensor = true;
		}
		// Decreases Train 2 speed
		train.Trem2Txt("Estacao de Engelberg");
		for (float p = train.GetTrain2Pos(); p <= 0.85; p += 0.0005f)
		{
			train.SetTrain2Pos(p, train.GetTrain2Traj());
			Thread::SleepMS(10);
		}
		//Fix annoying decimal rep of mantissa
		train.SetTrain2Pos(0.85f, train.GetTrain2Traj());
		// Transition finished
		ok = true;
	}
	else if (id_trans == 15)
	{
		train.Trem2Txt("Descarregando trem 2 em Engelberg");
		// Fakes the unloading time
		Thread::SleepMS(3000);
		// Train 2 goes to Lucerne's rail
		// Loads train 2 with people
		train.SetMatTrain2(trem2_vazio);
		//Transition finished
		ok = true;
	}
	else if (id_trans == 16)
	{
		// Train 2 goes to Stans's rail (this very transition does nothing because its action is joined with transition 17)
		//Transition finished
		ok = true;
	}
	else if (id_trans == 17)
	{
		bool B2Sensor = false;
		// Train 2 goes from Sarnen's rail up to Engelberg's station
		train.Gate(0);
		train.Trem2Txt("Estacao de Engelberg");
		// Train 2 goes Engelberg's station up to Stans' rail
		// Slowly starts
		for (float p = train.GetTrain2Pos(); p >= 0.8; p -= 0.0005f)
		{
			train.SetTrain2Pos(p, train.GetTrain2Traj());
			Thread::SleepMS(10);
		}
		train.Trem2Txt("Trilhos de Stans");
		// Max speed
		for (float p = train.GetTrain2Pos(); p >= 0.0; p -= 0.005f)
		{
			train.SetTrain2Pos(p, train.GetTrain2Traj());
			Thread::SleepMS(10);
		}
		//Fix annoying decimal rep of mantissa
		train.SetTrain2Pos(0.0f, 2);
		// Train 2 goes from Stans' rail up to Lucerne's rail
		for (float p = train.GetTrain2Pos(); ; p += 0.005f)
		{
			if (B2Sensor)
				break;
			train.SetTrain2Pos(p, train.GetTrain2Traj());
			Thread::SleepMS(10);
			if (train.B2())
				B2Sensor = true;
		}
		train.Trem2Txt("Trilhos de Sarnen");

		//Fix annoying decimal rep of mantissa
		train.SetTrain2Pos(0.5f, train.GetTrain2Traj());

		// Transition finished
		ok = true;
	}
	else if (id_trans == 11)
	{
		// Train 2 goes back to Sarnen's station
		bool A2Sensor = false;
		// Train 2 goes to Sarnen's rail
		for (float p = train.GetTrain2Pos(); ; p += 0.005f)
		{
			//Stops the train
			if (A2Sensor)
				break;
			train.SetTrain2Pos(p, train.GetTrain2Traj());
			Thread::SleepMS(10);
			if (train.A2())
				A2Sensor = true;
		}
		// Arrives slowly
		train.Trem2Txt("Estacao de Sarnen");
		for (float p = train.GetTrain2Pos(); p <= 0.9; p += 0.0005f)
		{
			train.SetTrain2Pos(p, train.GetTrain2Traj());
			Thread::SleepMS(10);
		}
		//Fix annoying decimal rep of mantissa
		train.SetTrain2Pos(0.9f, train.GetTrain2Traj());
		//Transition finished
		ok = true;
	}
	else if (id_trans == 13)
	{
		// Train 2 waits for switch G
		// Stop slowly
		train.Trem2Txt("Trilhos de Sarnen");
		for (float p = -train.GetTrain2Pos(); p <= -0.4f; p += 0.0005f)
		{
			train.SetTrain2Pos((-1) *p, train.GetTrain2Traj());
			Thread::SleepMS(10);
		}
		// Informs Train 1
		waits = 1;
		// Transfer to Train 1
		controlBack = 0;
		// Transition finished
		ok = true;

		// Transition finished
		ok = true;
	}
	else if (id_trans == 19)
	{
		// Train 2 takes over switch G
		// Transition left empty because it is completed by transition 19
		// Transition finished
		ok = true;
	}

	return ok;
}

// Effectively execute the petri transition
bool ExecuteTrans(unsigned int id_trans, vector<int> &M0, vector<vector<int>> &PRE, vector<vector<int>> &POS)
{
	bool ok = false;

	// Consume the PRE tokens from M0
	for (unsigned int i = 0; i < PRE.size(); i++)
	{
		if (PRE[i][id_trans] != 0 && M0[i] >= PRE[i][id_trans])
		{
			M0[i] -= PRE[i][id_trans];
		}
	}
//	for (unsigned int i = 0; i < M0.size(); i++)
//		cout << "M0 content " << i << ": " << M0[i] << endl;

	cout << BLUE " Transition " << id_trans << " has started " COLOR_RESET;
	// Move train
	if (TrainMovesBaby(id_trans))
	{
		cout << BLUE " Transition " << id_trans << " has finished\n" COLOR_RESET << endl;

		// Set POS tokens into M0
		for (unsigned int i = 0; i < POS.size(); i++)
		{
			M0[i] += POS[i][id_trans];
		}
		ok = true;
	}
	return ok;
}

int main(int argc, char **argv)
{
	// To have this odd setup compiled: cmake .. (just for the first time over current architecture)
	// Then: make

	// Define imgs for train1
	trem1_vazio = imread("img/train1_vazio.png", CV_LOAD_IMAGE_COLOR);
	trem1_cheio = imread("img/train1_cheio.png", CV_LOAD_IMAGE_COLOR);

	// Define imgs for train2
	trem2_vazio = imread("img/train2_vazio.png", CV_LOAD_IMAGE_COLOR);
	trem2_cheio = imread("img/train2_cheio.png", CV_LOAD_IMAGE_COLOR);

	train.SetMatTrain1(trem1_vazio);
	train.SetMatTrain2(trem2_vazio);

	// M0 of the petri net
	vector<int> M0
	{
		1,// Est Lucerne           /nro0
		1,// Trem1 vazio           /nro1
		0,// Trem1 cheio           /nro2
		0,// Trem1 esquerda        /nro3
		1,// Trem1 parado          /nro4
		0,// Trem1 direita         /nro5
		0,// Trilhos de Lucerne    /nro6
		1,// Uso do switch G       /nro7
		0,// Trilhos de Stans      /nro8
		0,// Switch G para Lucerne /nro9
		0,// Est. de Engelberg     /nro10
		1,// Trem2 vazio           /nro11
		0,// Trem2 cheio           /nro12
		0,// Trem2 esquerda        /nro13
		1,// Trem2 parado          /nro14
		0,// Trem2 direita         /nro15
		0, // Switch G para Sarnen /nro16
		1,// Estacao Sarnen        /nro17
		0,// Trilhos de Sarnen     /nro18
	};                             //total: 19

	// Pre of the petri net
	vector<vector<int>> PRE
	{
		//0,1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19 /nro transitions (total: 20)
		{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //nro0
		{1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //nro1
		{0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //nro2
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //nro3
		{0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //nro4
		{0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //nro5
		{1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //nro6
		{0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}, //nro7
		{0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0}, //nro8
		{0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, //nro9
		{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0}, //nro10
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0}, //nro11
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0}, //nro12
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //nro13
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1}, //nro14
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, //nro15
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0}, //nro16
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0}, //nro17
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1}, //nro18
	};                                                                //total: 19

	// Pos of the petri net
	vector<vector<int>> POS
	{
		//0,1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19 /nro transitions (total: 20)
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //nro0
		{1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //nro1
		{0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //nro2
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //nro3
		{1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //nro4
		{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //nro5
		{0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //nro6
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, //nro7
		{0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1}, //nro8
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0}, //nro9
		{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}, //nro10
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0}, //nro11
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0}, //nro12
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, //nro13
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0}, //nro14
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1}, //nro15
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1}, //nro16
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //nro17
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0}, //nro18
	};                                                                //total: 19
	// A list with the amount of tokens required to trigger each transition
	vector<int> tokensPerTrans = GetTokensPerTransitions(PRE);

	vector<int> listTrain1{0, 1, 2, 3, 4, 5, 6, 7, 8, 18};
	vector<int> listTrain2{9, 10, 11, 12, 13, 14, 15, 16, 17, 19};

	// Initial defs
	train.SetTrain1Pos(0.9f, 1);
	train.Trem1Txt("Estacao de Lucerne");
	train.SetTrain2Pos(0.9f, 2);
	train.Trem2Txt("Estacao de Sarnen");
	train.Gate(1);

	// Vector of current triggerable transitions
	vector<int> activeTrans;
	// The id of the transition which will be executed currently
	int id_trans = -1;
	// Current key stroke
	int key = -1;
	// Operator has pressed the key
	pressed = -1;

	// Main loop of the system
	while (1)
	{
		// Captures current key stroke
		if (key == -1)
			key = train.GetLastKeyAndEmpty();

		// Checks if M1 has been pressed
		if (key == UPlockNO || key == UPlockYE || key == UPlockNO2)
		{
			// Denotes M1 (train 1)
			pressed = 0;
		}
		// Checks if M2 has been pressed
		else if (key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
		{
			// Denotes M2 (train 2)
			pressed = 1;
		}

		// Prevents the initial -1 id from getting checked
		if (pressed != -1)
		{
			// Displays the current triggerable transitions
			vector<int> activeTrans = GetActiveTransitions(M0, tokensPerTrans, PRE);
			cout << WHITE "Triggerable transitions: " COLOR_RESET;
			for (unsigned int i = 0; i < activeTrans.size(); i++)
				cout << activeTrans[i] << " ";

			// Gets the executable transition in accordance to the train
			id_trans = GetTransExec(pressed, activeTrans, listTrain1, listTrain2);
			cout << WHITE "Petri net executes transition: " COLOR_RESET << id_trans << endl;

			if (!ExecuteTrans(id_trans, M0, PRE, POS))
			{
				cout << RED "Something went wrong with transition: " COLOR_RESET << id_trans << endl;
				exit(-1);
				// Prevents train 1 from leaving Lucerne's station without a further M1 press
			}
			else if (id_trans == 0 && controlBack == -1 && waits == -1)
				pressed = -1;
			else if (id_trans == 11 && controlBack == -1 && waits == -1)
				pressed = -1;
			else if (controlBack == 1)
			{
				controlBack = -1;
				pressed = 1;
			}
			else if (controlBack == 0)
			{
				controlBack = -1;
				pressed = 0;
			}
			else if (id_trans == 11 && waits == 0)
			{
				waits = -1;
				pressed = 0;
			}
			else if (id_trans == 0 && waits == 1)
			{
				waits = -1;
				pressed = 1;
			}
		}

		// Quits the application
		if (key == ESClockNO || key == ESClockYE)
		{
			break;
		}
		// 10ms
		Thread::SleepMS(10);
		// No new key stroke
		key = -1;
	}//end while

	return 0;
}
