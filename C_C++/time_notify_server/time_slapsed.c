#include <time.h>
#include <stdio.h>
// 1h = 60min = 3.600.000ms = 3600s
//const int Totaltime = 3600;
// 5min = 300.000ms = 300s
const int Totaltime = 300;

// Default is 0, only for testing
int NotifyServer = 1;

time_t Start;

void otherStuff()
{

}

void connection()
{

}

int main(void)
{
	// Sets a timer and counts 1h
	// to exchange a message to the server
	// notifying it about the preset time
	if (NotifyServer)
	{
		time (&Start);

		double diff = 0;
		while (diff < Totaltime)
		{
			// This routine must go on counting as soon as a card is read,
			// but during this period of time the code should not be unable to respond
			time_t current;
			time (&current);
			diff = difftime (current, Start);

			// Read card ...
			otherStuff();

			// Connect and authenticate with the server
			connection();

		}

		// Notify the server once the time is reached
		printf("... + MachineID + / + ReachedTimeLimit");

		// Done with the server
		NotifyServer = 0;
	}
	// Flow until a card is read
	else
	{
		// Read card ...
		otherStuff();

		// Connect and authenticate with the server
		connection();

		// Has to notify the server
		NotifyServer = 1;
	}

	return 0;
}
