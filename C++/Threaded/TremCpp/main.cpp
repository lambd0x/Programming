#include <vector>
#include <string>
#include <thread>
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

void train1Logic()
{
	MapaTrem train;
	train.SetTrain1Pos(1, 1);
	train.Trem1Txt("Estacao de Lucerne");
	train.Gate(1);
	string master1 = "1proceeding";

	// Main loop of the Train 1 (System's logic)
	while (1)
	{
		// Captures current key stroke for Train logic
		int key1 = train.GetLastKeyAndEmpty();
		// Key debugger
		//cout << "Pressionado: " << key1 << endl;

		// Get hold of train 1 positional details
		auto PresentTrain1Pos = train.GetTrain1Pos();
		float pt1p = get<0>(PresentTrain1Pos);
		int   tt1p = get<1>(PresentTrain1Pos);

		// Get hold of train 2 positional details
		auto PresentTrain2Pos = train.GetTrain2Pos();
		float pt2p = get<0>(PresentTrain2Pos);
		int   tt2p = get<1>(PresentTrain2Pos);

		// 1)Train 1 is on Lucerne's train station and Train 2 is on Sarnen's train station
		if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		/** Combinations of Train 1 and Train 2 **/
		// Combos from Train 1:
		// 13)Train 2 is on Sarnen's train rail and Train 1 is on Lucerne's train station
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		else if ((key1 == UPlockNO || key1 == UPlockYE || key1 == UPlockNO2)
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
		// 33) Exit cases
		else if (key1 == ESClockNO || key1 == ESClockYE)
		{
			break;
		}

		// 10ms
		Thread::SleepMS(10);
	}//while
}

void train2Logic()
{
	// Initial defs
	MapaTrem train;
	train.SetTrain2Pos(1, 2);
	train.Trem2Txt("Estacao de Sarnen");
	train.Gate(1);
	string master2 = "2proceeding";

	// Main loop of the Train 2 (System's logic)
	while (1)
	{
		// Captures current key stroke for Train 2 logic
		int key2 = train.GetLastKeyAndEmpty();

		// Key debugger
		//cout << "Pressionado: " << key2 << endl;

		// Get hold of train2 positional details
		auto PresentTrain2Pos = train.GetTrain1Pos();
		float pt1p = get<0>(PresentTrain1Pos);
		int   tt1p = get<1>(PresentTrain1Pos);

		// Get hold of train2 positional details
		auto PresentTrain2Pos = train.GetTrain2Pos();
		float pt2p = get<0>(PresentTrain2Pos);
		int   tt2p = get<1>(PresentTrain2Pos);

		// 7)Train 2 is on Sarnen's train station and Train 1 is on Lucerne's train station
		if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		/** Combinations of Train 1 and Train 2 **/
		// Combos from Train 2:
		// 23)Train 1 is on Lucerne's train rail and Train 2 is on Sarnen's train station
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if ((key2 == DOWNlockNO || key2 == DOWNlockYE || key2 == DOWNlockNO2)
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
		else if (key2 == ESClockNO || key2 == ESClockYE)
		{
			break;
		}

		// 10ms
		Thread::SleepMS(10);
	}//while
}

int main(int argc, char **argv)
{
	// To have this odd setup compiled: cmake .. (just for the first time over current architecture)
	// Then: make

	// Init threads
	for(int i=0; i < 2; i++)
	{
		if(i == 0)
			// Thread for Train 1
			thread t1(train1Logic);
		else
			// Thread for Train 2
			thread t2(train2Logic)
	}

	// Wait for the end of the system to start the pogrom
	for(int i=0; i < 2; i++)
	{
		if(i == 0)
			// Train 1's Thread is stabbed to death
			t1.join();
		else
			// Train 1's Thread is stabbed to death
	}

	return 0;
}