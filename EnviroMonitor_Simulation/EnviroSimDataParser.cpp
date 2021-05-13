// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS FILE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //


//----------------------------------------- PREPROCESSOR -----------------------------------//
#define _CRT_SECURE_NO_WARNINGS
//----------------------------------------- PREPROCESSOR -----------------------------------//



// ---------------------------------------- INCLUDE AREA ---------------------------------- //
// Class header file
#include "EnviroSimDataParser.h"
// -------------------------------------- END INCLUDE AREA -------------------------------- //

// ----------------------------------------- NAMESPACE ------------------------------------ //
using namespace std;
// ----------------------------------------- NAMESPACE ------------------------------------ //

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ MEMBER FUNCTIONS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ //

//------------------------------------------------
// Default constructor
//------------------------------------------------
EnviroSimDataParser::EnviroSimDataParser(const char *fileName)
{
	char line[128];

	strcpy(m_sFileName, fileName);
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in); // Open the data file
	m_iNumSensors = 0;  // Number of sensors in the file
	m_iNumDisplays = 0; // Number of display devices in the file
	m_iNextSensor = 0;  // Next sensor number to read
	m_iNextDisplay = 0; // Next display number to read

	if (inFile->is_open())
	{
		// Count the number of sensors
		while (getNextLine(line, 127))
		{
			if (strcmp(line, "<SENSOR>") == 0)
				m_iNumSensors++;
			if (strcmp(line, "<DISPLAY_DEVICE>") == 0)
				m_iNumDisplays++;
		}
		inFile->close();
	}
	else
	{
		cout << "Failed to open file. Application terminated...\n";
		exit(0);
	}
}
//------------------------------------------------
// Destructor
//------------------------------------------------
EnviroSimDataParser::~EnviroSimDataParser()
{
}

//------------------------------------------------
// Return number of sensors in the data file.
//------------------------------------------------
int EnviroSimDataParser::getSensorCount()
{
	return m_iNumSensors;
}

//------------------------------------------------
// Return number of displays in the data file.
//------------------------------------------------
int EnviroSimDataParser::getDisplayCount()
{
	return m_iNumDisplays;
}

//------------------------------------------------------------------
// Gets all data on one sensor
// Args:
//		type - pointer to a char array to hold sensor type string
//		material - pointer to a char array to hold material string
//		ID - pointer to int variable to hold sensor ID
//		units - pointer to char array to hold units string
//		minVal - pointer to double variable to hold minimum reading
//		maxVal - pointer to double variable to hold maximum reading
//		
//------------------------------------------------------------------
bool EnviroSimDataParser::getSensorData(char *type, char *material, int *ID,
	char *units, double *minVal, double *maxVal)
{
	int sNum = 0;
	char line[128];

	// See if we have read all sensors
	if (m_iNextSensor >= m_iNumSensors) return false;

	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);
	if (inFile->is_open())
	{
		// Read to the the current sensor count
		while (getNextLine(line, 127))
		{
			if (strcmp(line, "<SENSOR>") == 0) // Got one
			{
				if (sNum == m_iNextSensor)
				{
					// Get data on this one
					while (getNextLine(line, 127))
					{
						// Get the type
						if (strcmp(line, "<TYPE>") == 0)
						{
							if (getNextLine(line, 127))
							{
								strcpy(type, line); // Set the type
							}
							else
								return false; // Oops!
						}
						else if (strcmp(line, "<MATERIAL>") == 0)
						{
							if (getNextLine(line, 127))
							{
								strcpy(material, line); // Set the material
							}
							else
								return false; // Oops!
						}
						else if (strcmp(line, "<ID>") == 0)
						{
							if (getNextLine(line, 127))
							{
								*ID = atoi(line); // Set the ID
							}
							else
								return false; // Oops!
						}
						else if (strcmp(line, "<UNITS>") == 0)
						{
							if (getNextLine(line, 127))
							{
								strcpy(units, line); // Set the units
							}
							else
								return false; // Oops!
						}
						else if (strcmp(line, "<MINIMUM_VALUE>") == 0)
						{
							if (getNextLine(line, 127))
							{
								*minVal = atof(line); // Set the minimum value
							}
							else
								return false; // Oops!
						}
						else if (strcmp(line, "<MAXIMUM_VALUE>") == 0)
						{
							if (getNextLine(line, 127))
							{
								*maxVal = atof(line); // Set the minimum value
							}
							else
								return false; // Oops!
						}
						else if (strcmp(line, "</SENSOR>") == 0)
						{
							m_iNextSensor++; // Increment for next sensor
							return true; // Got it
						}
					} // end while
				} // end if(sNum == m_iNextSensor)
				else
				{
					sNum++; // Check the next one
				}
			}
		}
		inFile->close();
	} // end if file open
	return false; // If we get here we have got all the sensors
}

//------------------------------------------------------------------
// Gets all data on one sensor
// Args:
//		type - pointer to a char array to hold display type string
//		IDs - pointer to a int array (max 8) into which to write
//				sensor IDs
//		IDcount - pointer to int variable to hold ID count
//		
//------------------------------------------------------------------
bool EnviroSimDataParser::getDisplayData(char *type, int *IDs, int *IDCount)
{
	int dNum = 0;
	int iNum = 0;
	char line[128];

	// See if we have read all display devices
	if (m_iNextDisplay >= m_iNumDisplays) return false;

	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);
	if (inFile->is_open())
	{
		// Read to the the current display device count
		while (getNextLine(line, 127))
		{
			if (strcmp(line, "<DISPLAY_DEVICE>") == 0) // Got one
			{
				if (dNum == m_iNextDisplay)
				{
					// Get data on this one
					iNum = 0;
					while (getNextLine(line, 127))
					{
						// Get the type
						if (strcmp(line, "<TYPE>") == 0)
						{
							if (getNextLine(line, 127))
							{
								strcpy(type, line); // Set the type
							}
							else
								return false; // Oops!
						}
						else if (strcmp(line, "<SENSOR_ID>") == 0)
						{
							if (getNextLine(line, 127))
							{
								IDs[iNum] = atoi(line); // Set the ID
								iNum++;
							}
							else
								return false; // Oops!
						}
						else if (strcmp(line, "</DISPLAY_DEVICE>") == 0)
						{
							m_iNextDisplay++; // Increment for next sensor
							*IDCount = iNum;
							return true; // Got it
						}
					} // end while
				} // end if(sNum == m_iNextSensor)
				else
				{
					dNum++; // Check the next one
				}
			}
		}
		inFile->close();
	} // end if file open
	return false; // If we get here we have got all the display devices
}

//------------------------------------------------
// Function: getNextLine()
// Purpose: Reads lines from a file and places
//   them in buffer, removing any leading white
//   space.  Skips blank lines. Ignors comment
//   lines starting with <!-- and ending with -->
//   
// Args:  inF -- valid ifstream object of the open
//               file to read from.
//        buffer -- char array to read line into.
//        n -- length of buffer.
// Returns: True if a line was successfully read,
//    false if the end of file was encountered.
// Notes: Function provided by instructor.
//------------------------------------------------
bool EnviroSimDataParser::getNextLine(char *buffer, int n)
{
	bool    done = false;
	char    tempBuf[128];
	char	*temp;
	while (!done)
	{
		inFile->getline(tempBuf, n); // Read a line from the file

		if (inFile->good())          // If a line was successfully read check it
		{
			if (strlen(tempBuf) == 0)     // Skip any blank lines
				continue;
			else if (strncmp(tempBuf, "<!--", 4) == 0) // Skip comment lines
				continue;
			else done = true;    // Got a valid data line so return with this line
		}
		else
		{
			strcpy(buffer, "");  // Clear the buffer array
			return false;        // Flag end of file
		}
	} // end while
	// Remove white space from end of string
	temp = &tempBuf[strlen(tempBuf)]; // point to closing \0
	temp--; // back up 1 space
	while (isspace(*temp))
	{
		*temp = '\0'; // Make it another NULL terminator
		temp--;  // Back up 1 char
	}
	// Remove white space from front of string
	temp = tempBuf;
	while (isspace(*temp)) temp++; // Skip leading white space
	// Copy remainder of string into the buffer
	strcpy(buffer, temp);
	return true;  // Flag a successful read
}
