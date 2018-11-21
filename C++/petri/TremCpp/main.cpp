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

using namespace std;

// Identify the number of tokens required per each petri net transition
vector<int> GetTokensPerTransitions(vector<vector<int>> PRE)
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
vector<int> GetActiveTransitions(vector<int> M0, vector<int> tokensPerTrans, vector<vector<int>> PRE)
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

// Moves the train in accordance to the transition executed
bool TrainMovesBaby(unsigned int id_trans)
{
	if (id_trans == 1)
	{
		// Loads train 1 with people

		// Fakes the time (1s)
		Thread::SleepMS(60);
	}

	/*
	    // 1)Train 1 is on Lucerne's train station and Train 2 is on Sarnen's train station
	    if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	            && (pt1p == 1.0f && tt1p == 1) && (pt2p == 1.0f && tt2p == 2)
	            && (master1 == "1proceeding"))
	    {
	        // Train 1 advances up until the end of Lucerne's train rail
	        for (float p = -1.0f; p <= -0.5f; p += 0.01f)
	        {
	            train.SetTrain1Pos((-1) * p, 1);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(0.5f, 1);
	        train.Trem1Txt("Trilhos de Lucerne");
	    }
	    // 2)Train 1 is on Lucerne's train rail and Train 2 is on Sarnen's train station
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 0.5f && tt1p == 1) && (pt2p == 1.0f && tt2p == 2)
	             && (master1 == "1proceeding"))
	    {
	        train.Gate(1);
	        // Train 1 advances to Stans' train rail (critical area)
	        for (float p = -0.5f; p <= 0.0f; p += 0.01f)
	        {
	            train.SetTrain1Pos((-1) * p, 1);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(0.0f, 0);
	        train.Trem1Txt("Trilhos de Stans");
	    }
	    // 3)Train 1 is on Stan's train rail (critical area) and Train 2 is on Sarnen's train station
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 0.0f && tt1p == 0) && (pt2p == 1.0f && tt2p == 2)
	             && (master1 == "1proceeding"))
	    {
	        // Train 1 advances to Engelberg's train station (critical area)
	        for (float p = 0.0f; p <= 1.0f; p += 0.01f)
	        {
	            train.SetTrain1Pos(p, 0);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(1.0f, 0);
	        master1 = "1returning";
	        train.Trem1Txt("Estacao de Engelberg");
	    }
	    // 4)Train 1 is on Engelberg's train station (critical area) and Train 2 is on Sarnen's train station
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 1.0f && tt1p == 0) && (pt2p == 1.0f && tt2p == 2)
	             && (master1 == "1returning"))
	    {
	        // Train 1 advances from Engelberg's train station goes back to Stans' train rail
	        for (float p = 1.0f; p >= 0.0; p -= 0.01)
	        {
	            train.SetTrain1Pos(p, 0);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(0.0f, 0);
	        train.Trem1Txt("Trilhos de Stans");
	    }
	    // 5)Train 1 is on Stans' train rail (critical area) [returning] and Train 2 is on Sarnen's train station
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 0.0f && tt1p == 0) && (pt2p == 1.0f && tt2p == 2)
	             && (master1 == "1returning"))
	    {
	        // Train 1 advances from Stans' train rail back to Lucerne's train rail
	        for (float p = 0.0f; p >= -0.5; p -= 0.01)
	        {
	            train.SetTrain1Pos((-1) * p, 1);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(0.5f, 1);
	        train.Trem1Txt("Trilhos de Lucerne");
	    }
	    // 6)Train 1 is on Lucerne's train rail [returning] and Train 2 is on Sarnen's train station
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 0.5f && tt1p == 1) && (pt2p == 1.0f && tt2p == 2)
	             && (master1 == "1returning"))
	    {
	        // Train 1 advances from Lucerne's train rail back to Lucerne's train station
	        for (float p = -0.5f; p >= -1.0f; p -= 0.01)
	        {
	            train.SetTrain1Pos((-1) * p, 1);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(1.0f, 1);
	        master1 = "1proceeding";
	        train.Trem1Txt("Estacao de Lucerne");
	    }
	    // 7)Train 2 is on Sarnen's train station and Train 1 is on Lucerne's train station
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 1.0f && tt1p == 1) && (pt2p == 1.0f && tt2p == 2)
	             && (master2 == "2proceeding"))
	    {
	        // Train 2 advances up until the end of Sarnen's train rail
	        for (float p = -1.0f; p <= -0.5f; p += 0.01f)
	        {
	            train.SetTrain2Pos((-1) * p, 2);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(0.5f, 2);
	        train.Trem2Txt("Trilhos de Sarnen");
	    }
	    // 8)Train 2 is on Sarnen's train rail and Train 1 is on Lucerne's train station
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 1.0f && tt1p == 1) && (pt2p == 0.5f && tt2p == 2)
	             && (master2 == "2proceeding"))
	    {
	        train.Gate(0);
	        // Train 2 advances to Stans' train rail (critical area)
	        for (float p = -0.5f; p <= 0.0f; p += 0.01f)
	        {
	            train.SetTrain2Pos((-1) * p, 2);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(0.0f, 0);
	        train.Trem2Txt("Trilhos de Stans");
	    }
	    // 9)Train 2 is on Stans' train rail (critical area) and Train 1 is on Lucerne's train station
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 1.0f && tt1p == 1) && (pt2p == 0.0f && tt2p == 0)
	             && (master2 == "2proceeding"))
	    {
	        // Train 2 advances to Engelberg's train station (critical area)
	        for (float p = 0.0f; p <= 1.0f; p += 0.01f)
	        {
	            train.SetTrain2Pos(p, 0);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(1.0f, 0);
	        master2 = "2returning";
	        train.Trem2Txt("Estacao de Engelberg");
	    }
	    // 10)Train 2 is on Engelberg's train station (critical area) and Train 1 is on Lucerne's train station
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 1.0f && tt1p == 1) && (pt2p == 1.0f && tt2p == 0)
	             && (master2 == "2returning"))
	    {
	        // Train 2 advances from Engelberg's train station goes back to Stans' train rail
	        for (float p = 1.0f; p >= 0.0; p -= 0.01)
	        {
	            train.SetTrain2Pos(p, 0);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(0.0f, 0);
	        train.Trem2Txt("Trilhos de Stans");
	    }
	    // 11)Train 2 is on Stans's train rail (critical area) [returning] and Train 1 is on Lucerne's train station
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 1.0f && tt1p == 1) && (pt2p == 0.0f && tt2p == 0)
	             && (master2 == "2returning"))
	    {
	        // Train 2 advances from Stans's train rail back to Sarnen's train rail
	        for (float p = 0.0f; p >= -0.5; p -= 0.01)
	        {
	            train.SetTrain2Pos((-1) * p, 2);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(0.5f, 2);
	        train.Trem2Txt("Trilhos de Sarnen");
	    }
	    // 12)Train 2 is on Sarnen's train rail [returning] and Train 1 is on Lucerne's train station
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 1.0f && tt1p == 1) && (pt2p == 0.5f && tt2p == 2)
	             && (master2 == "2returning"))
	    {
	        // Train 2 advances from Sarnen's train rail back to Sarnen's train station
	        for (float p = -0.5f; p >= -1.0f; p -= 0.01)
	        {
	            train.SetTrain2Pos((-1) * p, 2);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(1.0f, 2);
	        master2 = "2proceeding";
	        train.Trem2Txt("Estacao de Sarnen");
	    }
	    // Combinations of Train 1 and Train 2
	    // Combos from Train 1:
	    // 13)Train 2 is on Sarnen's train rail and Train 1 is on Lucerne's train station
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 1.0f && tt1p == 1) && (pt2p == 0.5f && tt2p == 2)
	             && (master1 == "1proceeding"))
	    {
	        // Train 1 advances to Lucerne's train rail
	        for (float p = -1.0f; p <= -0.5f; p += 0.01f)
	        {
	            train.SetTrain1Pos((-1) * p, 1);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(0.5f, 1);
	        train.Trem1Txt("Trilhos de Lucerne");
	    }
	    // 14)Train 2 is on Sarnen's train rail and Train 1 is on Lucerne's train rail
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 0.5f && tt1p == 1) && (pt2p == 0.5f && tt2p == 2)
	             && (master1 == "1proceeding"))
	    {
	        train.Gate(1);
	        // Train 1 advances to Stans' train rail
	        for (float p = -0.5f; p <= 0.0f; p += 0.01f)
	        {
	            train.SetTrain1Pos((-1) * p, 1);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(0.0f, 0);
	        train.Trem1Txt("Trilhos de Stans");
	    }
	    // 15)Train 2 is on Sarnen's train rail and Train 1 is on Stans' train rail
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 0.0f && tt1p == 0) && (pt2p == 0.5f && tt2p == 2)
	             && (master1 == "1proceeding"))
	    {
	        // Train 1 advances to Engelberg's train station
	        for (float p = 0.0f; p <= 1.0f; p += 0.01f)
	        {
	            train.SetTrain1Pos(p, 0);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(1.0f, 0);
	        master1 = "1returning";
	        train.Trem1Txt("Estacao de Engelberg");
	    }
	    // 16)Train 2 is on Sarnen's train rail and Train 1 is on Engelberg's train station [returning]
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 1.0f && tt1p == 0) && (pt2p == 0.5f && tt2p == 2)
	             && (master1 == "1returning"))
	    {
	        // Train 1 advances to Stans' train rail
	        for (float p = 1.0f; p >= 0.0f; p -= 0.01f)
	        {
	            train.SetTrain1Pos(p, 0);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(0.0f, 0);
	        train.Trem1Txt("Trilhos de Stans");
	    }
	    // 17)Train 2 is on Sarnen's train rail and Train 1 is on Stans' train rail [returning]
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 0.0f && tt1p == 0) && (pt2p == 0.5f && tt2p == 2)
	             && (master1 == "1returning"))
	    {
	        // Train 1 advances to Lucerne's train rail
	        for (float p = 0.0f; p <= 0.5f; p += 0.01f)
	        {
	            train.SetTrain1Pos(p, 1);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(0.5f, 1);
	        train.Trem1Txt("Trilhos de Lucerne");
	    }
	    // 18)Train 2 is on Sarnen's train rail and Train 1 is on Lucerne's train rail [returning]
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 0.5f && tt1p == 1) && (pt2p == 0.5f && tt2p == 2)
	             && (master1 == "1returning"))
	    {
	        // Train 1 advances to Lucerne's train station
	        for (float p = 0.5f; p <= 1.0f; p += 0.01f)
	        {
	            train.SetTrain1Pos(p, 1);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(1.0f, 1);
	        master1 = "1proceeding";
	        train.Trem1Txt("Estacao de Lucerne");
	    }
	    // 19)Train 2 is on Stans' trail rail and Train 1 is on Lucerne's train station
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 1.0f && tt1p == 1) && (pt2p == 0.0f && tt2p == 0)
	             && (master1 == "1proceeding"))
	    {
	        // Train 1 advances to Lucerne's train rail
	        for (float p = 1.0f; p >= 0.5f; p -= 0.01f)
	        {
	            train.SetTrain1Pos(p, 1);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(0.5f, 1);
	        train.Trem1Txt("Trilhos de Lucerne");
	    }
	    // 20)Train 2 is on Engelberg's trail station and Train 1 is on Lucerne's train station
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 1.0f && tt1p == 1) && (pt2p == 1.0f && tt2p == 0)
	             && (master1 == "1proceeding"))
	    {
	        // Train 1 advances to Lucerne's train rail
	        for (float p = 1.0f; p >= 0.5f; p -= 0.01f)
	        {
	            train.SetTrain1Pos(p, 1);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(0.5f, 1);
	        train.Trem1Txt("Trilhos de Lucerne");
	    }
	    // 21)Train 2 is on Stans' train rail and Train 1 is on Lucerne's train rail
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 0.5f && tt1p == 1) && (pt2p == 0.0f && tt2p == 0)
	             && (master1 == "1returning"))
	    {
	        // Train 1 advances to Lucerne's train station
	        for (float p = 0.5f; p <= 1.0f; p += 0.01f)
	        {
	            train.SetTrain1Pos(p, 1);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(1.0f, 1);
	        train.Trem1Txt("Estacao de Lucerne");
	        master1 = "1proceeding";
	    }
	    // 22)Train 2 is on Engelberg's train station and Train 1 is on Lucerne's train rail
	    else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
	             && (pt1p == 0.5f && tt1p == 1) && (pt2p == 1.0f && tt2p == 0)
	             && (master1 == "1returning"))
	    {
	        // Train 1 advances to Lucerne's train station
	        for (float p = 0.5f; p <= 1.0f; p += 0.01f)
	        {
	            train.SetTrain1Pos(p, 1);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain1Pos(1.0f, 1);
	        train.Trem1Txt("Estacao de Lucerne");
	        master1 = "1proceeding";
	    }
	    // Combos from Train 2:
	    // 23)Train 1 is on Lucerne's train rail and Train 2 is on Sarnen's train station
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 0.5f && tt1p == 1) && (pt2p == 1.0f && tt2p == 2)
	             && (master2 == "2proceeding"))
	    {
	        // Train 2 advances to Sarnen's train rail
	        for (float p = -1.0f; p <= -0.5f; p += 0.01f)
	        {
	            train.SetTrain2Pos((-1) * p, 2);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(0.5f, 2);
	        train.Trem2Txt("Trilhos de Sarnen");
	    }
	    // 24)Train 1 is on Lucerne's train rail and Train 2 is on Sarnen's train rail
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 0.5f && tt1p == 1) && (pt2p == 0.5f && tt2p == 2)
	             && (master2 == "2proceeding"))
	    {
	        train.Gate(0);
	        // Train 2 advances to Stans' train rail
	        for (float p = -0.5f; p <= 0.0f; p += 0.01f)
	        {
	            train.SetTrain2Pos((-1) * p, 2);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(0.0f, 0);
	        train.Trem2Txt("Trilhos de Stans");
	    }
	    // 25)Train 1 is on Lucerne's train rail and Train 2 is on Stans' train rail
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 0.5f && tt1p == 1) && (pt2p == 0.0f && tt2p == 0)
	             && (master2 == "2proceeding"))
	    {
	        // Train 2 advances to Engelberg's train station
	        for (float p = 0.0f; p <= 1.0f; p += 0.01f)
	        {
	            train.SetTrain2Pos(p, 0);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(1.0f, 0);
	        master2 = "2returning";
	        train.Trem2Txt("Estacao de Engelberg");
	    }
	    // 26)Train 1 is on Lucerne's train rail and Train 2 is on Engelberg's train station [returning]
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 0.5f && tt1p == 1) && (pt2p == 1.0f && tt2p == 0)
	             && (master2 == "2returning"))
	    {
	        // Train 2 advances to Stans' train rail
	        for (float p = 1.0f; p >= 0.0f; p -= 0.01f)
	        {
	            train.SetTrain2Pos(p, 0);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(0.0f, 0);
	        train.Trem2Txt("Trilhos de Stans");
	    }
	    // 27)Train 1 is on Lucerne's train rail and Train 2 is on Stans' train rail [returning]
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 0.5f && tt1p == 1) && (pt2p == 0.0f && tt2p == 0)
	             && (master2 == "2returning"))
	    {
	        // Train 2 advances to Sarnen's train rail
	        for (float p = 0.0f; p <= 0.5f; p += 0.01f)
	        {
	            train.SetTrain2Pos(p, 2);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(0.5f, 2);
	        train.Trem2Txt("Trilhos de Sarnen");
	    }
	    // 28)Train 1 is on Lucerne's train rail and Train 2 is on Stans's train rail [returning]
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 0.5f && tt1p == 1) && (pt2p == 0.5f && tt2p == 2)
	             && (master2 == "2returning"))
	    {
	        // Train 2 advances to Sarnen's train station
	        for (float p = 0.5f; p <= 1.0f; p += 0.01f)
	        {
	            train.SetTrain2Pos(p, 2);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(1.0f, 2);
	        master2 = "2proceeding";
	        train.Trem2Txt("Estacao de Sarnen");
	    }
	    // 29)Train 1 is on Stans' trail rail and Train 2 is on Sarnen's train station
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 0.0f && tt1p == 0) && (pt2p == 1.0f && tt2p == 2)
	             && (master2 == "2proceeding"))
	    {
	        // Train 2 advances to Sarnen's train rail
	        for (float p = 1.0f; p >= 0.5f; p -= 0.01f)
	        {
	            train.SetTrain2Pos(p, 2);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(0.5f, 2);
	        train.Trem2Txt("Trilhos de Sarnen");
	    }
	    // 30)Train 1 is on Engelberg's trail station and Train 2 is on Sarnen's train station
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 1.0f && tt1p == 0) && (pt2p == 1.0f && tt2p == 2)
	             && (master2 == "2proceeding"))
	    {
	        // Train 2 advances to Sarnen's train rail
	        for (float p = 1.0f; p >= 0.5f; p -= 0.01f)
	        {
	            train.SetTrain2Pos(p, 2);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(0.5f, 2);
	        train.Trem2Txt("Trilhos de Sarnen");
	    }
	    // 31)Train 1 is on Stans's train rail and Train 2 is on Sarnen's train station
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 0.0f && tt1p == 0) && (pt2p == 0.5f && tt2p == 2)
	             && (master2 == "2returning"))
	    {
	        // Train 2 advances to Sarnen's train station
	        for (float p = 0.5f; p <= 1.0f; p += 0.01f)
	        {
	            train.SetTrain2Pos(p, 2);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(1.0f, 2);
	        train.Trem2Txt("Estacao de Sarnen");
	        master2 = "2proceeding";
	    }
	    // 32)Train 1 is on Engelberg's train station and Train 2 is on Sarnen's train station
	    else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
	             && (pt1p == 1.0f && tt1p == 0) && (pt2p == 0.5f && tt2p == 2)
	             && (master2 == "2returning"))
	    {
	        // Train 2 advances to Sarnen's train rail
	        for (float p = 0.5f; p <= 1.0f; p += 0.01f)
	        {
	            train.SetTrain2Pos(p, 2);
	            Thread::SleepMS(10);
	        }
	        //Fix annoying decimal rep of mantissa
	        train.SetTrain2Pos(1.0f, 2);
	        train.Trem2Txt("Estacao de Sarnen");
	        master2 = "2proceeding";
	    }
	    // 33) Exit cases
	    else if (key == ESClockNO || key == ESClockYE)
	    {
	        break;
	    }
	    */
}

// Effectively execute the petri transition
bool ExecuteTrans(unsigned int id_trans, vector<int> M0, vector<vector<int>> PRE, vector<vector<int>> POS)
{
	// Consume the PRE tokens from M0
	for (unsigned int i = 0; i < PRE.size(); i++)
	{
		if (PRE[i][id_trans] != 0 && M0[i] == PRE[i][id_trans])
		{
			M0[i] = 0;
		}
	}
	for (unsigned int i = 0; i < M0.size(); i++)
		cout << "M0 content " << i << ": " << M0[i] << endl;

	// Move train
	TrainMovesBaby(id_trans);

	// Set POS tokens into M0
}

int main(int argc, char **argv)
{
	// To have this odd setup compiled: cmake .. (just for the first time over current architecture)
	// Then: make

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
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0}, //nro13
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0}, //nro14
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1}, //nro15
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1}, //nro16
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //nro17
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0}, //nro18
	};                                                                //total: 19
	// A list with the amount of tokens required to trigger each transition
	vector<int> tokensPerTrans = GetTokensPerTransitions(PRE);
	for (unsigned int i = 0; i < tokensPerTrans.size(); i++)
		cout << "To trigger transition " << i << ": " << tokensPerTrans[i] << endl;

	vector<int> activeTrans = GetActiveTransitions(M0, tokensPerTrans, PRE);
	for (unsigned int i = 0; i < activeTrans.size(); i++)
		cout << "Triggerable transition " << i << ": " << activeTrans[i] << endl;

	// Initial defs
	MapaTrem train;
	train.SetTrain1Pos(0.9f, 1);
	train.Trem1Txt("Estacao de Lucerne");
	train.SetTrain2Pos(0.9f, 2);
	train.Trem2Txt("Estacao de Sarnen");
	train.Gate(1);

	// The id of the transition which will be executed currently
	int id = -1;

	// Main loop of the system
	while (1)
	{
		// Captures current key stroke
		int key = train.GetLastKeyAndEmpty();
		// Key debugger
		//cout << "Pressionado: " << key << endl;

		// Checks if M1 has been pressed
		if (key == UPlockNO || key == UPlockYE || key == UPlockNO2)
		{
			id = 1;
		}
		// Checks if M2 has been pressed
		else if (key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
		{
			id = 10;
		}

		// Prevents the initial -1 id from getting checked
		if (id != -1)
		{
			ExecuteTrans(id, M0, PRE, POS);
		}

		// Quits the application
		if (key == ESClockNO || key == ESClockYE)
		{
			break;
		}
		// 10ms
		Thread::SleepMS(10);
	}//end while

	return 0;
}
