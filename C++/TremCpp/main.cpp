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

int main(int argc, char **argv)
{
	// To have this odd setup compiled: cmake .. (just for the first time over current architecture)
	// Then: make

	MapaTrem train;
	train.SetTrain1Pos(1, 1);
//	trens.Trem1Txt("Mensagem trem 1.");
	train.SetTrain2Pos(1, 2);
//	trens.Trem2Txt("Mensagem trem 2.");
	train.Gate(1);
	string master1 = "1proceeding";
	string master2 = "2proceeding";

	// Main loop of the system
	while (1)
	{
		// Captures current key stroke
		int key = train.GetLastKeyAndEmpty();
		// Key debugger
		//cout << "Pressionado: " << key << endl;

		// Get hold of train1 positional details
		auto PresentTrain1Pos = train.GetTrain1Pos();
		float pt1p = get<0>(PresentTrain1Pos);
		int   tt1p = get<1>(PresentTrain1Pos);
		cout << "Trem1pos: " << pt1p << " " << tt1p << " ";

		// Get hold of train2 positional details
		auto PresentTrain2Pos = train.GetTrain2Pos();
		float pt2p = get<0>(PresentTrain2Pos);
		int   tt2p = get<1>(PresentTrain2Pos);
		cout << "Trem2pos: " << pt2p << " " << tt2p << endl;

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
		}
		// 2)Train 1 is on Lucerne's train rail and Train 2 is on Sarnen's train station
		else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
		         && (pt1p == 0.5f && tt1p == 1) && (pt2p == 1.0f && tt2p == 2)
		         && (master1 == "1proceeding"))
		{
			// Train 1 advances to Stans' train rail (critical area)
			for (float p = -0.5f; p <= 0.0f; p += 0.01f)
			{
				train.SetTrain1Pos((-1) * p, 1);
				Thread::SleepMS(10);
			}
			//Fix annoying decimal rep of mantissa
			train.SetTrain1Pos(0.0f, 0);
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
		}
		// 4)Train 1 is on Engelberg's train station (critical area) and Train 2 is on Sarnen's train station
		else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
		         && (pt1p == 1.0f && tt1p == 0) && (pt2p == 1.0f && tt2p == 2)
		         && (master1 == "1proceeding"))
		{
			// Train 1 advances from Engelberg's train station goes back to Stans' train rail
			for (float p = 1.0f; p >= 0.0; p -= 0.01)
			{
				train.SetTrain1Pos(p, 0);
				Thread::SleepMS(10);
			}
			//Fix annoying decimal rep of mantissa
			train.SetTrain1Pos(0.0f, 0);
			master1 = "1returning";
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
		}
		// 10)Train 2 is on Engelberg's train station (critical area) and Train 1 is on Lucerne's train station
		else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
		         && (pt1p == 1.0f && tt1p == 1) && (pt2p == 1.0f && tt2p == 0)
		         && (master2 == "2proceeding"))
		{
			// Train 2 advances from Engelberg's train station goes back to Stans' train rail
			for (float p = 1.0f; p >= 0.0; p -= 0.01)
			{
				train.SetTrain2Pos(p, 0);
				Thread::SleepMS(10);
			}
			//Fix annoying decimal rep of mantissa
			train.SetTrain2Pos(0.0f, 0);
			master2 = "2returning";
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
		}
		/** Combinations of Train 1 and Train 2 **/
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
		}
		// 14)Train 2 is on Sarnen's train rail and Train 1 is on Lucerne's train rail
		else if ((key == UPlockNO || key == UPlockYE || key == UPlockNO2)
		         && (pt1p == 0.5f && tt1p == 1) && (pt2p == 0.5f && tt2p == 2)
		         && (master1 == "1proceeding"))
		{
			train.Gate(0);
			// Train 1 advances to Stans' train rail
			for (float p = -0.5f; p <= 0.0f; p += 0.01f)
			{
				train.SetTrain1Pos((-1) * p, 1);
				Thread::SleepMS(10);
			}
			//Fix annoying decimal rep of mantissa
			train.SetTrain1Pos(0.0f, 0);
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
		}
		// Combos from Train 2:
		// 19)Train 1 is on Lucerne's train rail and Train 2 is on Sarnen's train station
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
		}
		// 20)Train 1 is on Lucerne's train rail and Train 2 is on Sarnen's train rail
		else if ((key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
		         && (pt1p == 0.5f && tt1p == 1) && (pt2p == 0.5f && tt2p == 2)
		         && (master2 == "2proceeding"))
		{
			train.Gate(1);
			// Train 2 advances to Stans' train rail
			for (float p = -0.5f; p <= 0.0f; p += 0.01f)
			{
				train.SetTrain2Pos((-1) * p, 2);
				Thread::SleepMS(10);
			}
			//Fix annoying decimal rep of mantissa
			train.SetTrain2Pos(0.0f, 0);
		}
		// 21)Train 1 is on Lucerne's train rail and Train 2 is on Stans' train rail
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
		}
		// 22)Train 1 is on Lucerne's train rail and Train 2 is on Engelberg's train station [returning]
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
		}
		// 23)Train 1 is on Lucerne's train rail and Train 2 is on Stans' train rail [returning]
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
		}
		// 24)Train 1 is on Lucerne's train rail and Train 2 is on Stans's train rail [returning]
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
		}
		/*
		        else if (key == DOWNlockNO || key == DOWNlockYE || key == DOWNlockNO2)
		        {
		            // Trem 2 de Sarnen para Engelberg com avanço direto por Stans
		            train.Gate(0);
		            for (float p = -1; p <= 1; p += 0.01)
		            {
		                if (p < 0)
		                    train.SetTrain2Pos((-1) * p, 2);
		                else
		                    train.SetTrain2Pos(p, 0);
		                //trens.Trem1Pos(p.x,p.y);
		                Thread::SleepMS(10);

		                trens.Trem2Txt("a1=" + to_string((int) trens.A1()) +
		                               " a2=" + to_string((int) trens.A2()) +
		                               " b1=" + to_string((int) trens.B1()) +
		                               " b2=" + to_string((int) trens.B2()) +
		                               " c=" + to_string((int) trens.C()));

		            }
		            //trens.Trem2Txt("Mensagem trem 2.");

		            // Trem 2 de Engelberg para Sarnen com avanço direto por Stans
		            for (float p = 1; p >= -1; p -= 0.01)
		            {
		                if (p > 0)
		                    train.SetTrain2Pos(p, 0);
		                else
		                    train.SetTrain2Pos((-1) * p, 2);
		                //trens.Trem1Pos(p.x,p.y);
		                Thread::SleepMS(10);

		                trens.Trem2Txt("a1=" + to_string((int) trens.A1()) +
		                               " a2=" + to_string((int) trens.A2()) +
		                               " b1=" + to_string((int) trens.B1()) +
		                               " b2=" + to_string((int) trens.B2()) +
		                               " c=" + to_string((int) trens.C()));

		            }
		            //  trens.Trem2Txt("Mensagem trem 2.");
		*/
		else if (key == ESClockNO || key == ESClockYE)
		{
			break;
		}

		// 10ms
		Thread::SleepMS(10);
	}//while

	return 0;
}
