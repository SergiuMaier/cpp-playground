#include <iostream>
#include <string>
#include <vector>

#define ALIVE_CELL '*'
#define DEAD_CELL '-'

enum Pattern
{
	Block = 1, Boat = 2, Blinker = 3, Beacon = 4, Pentadecathlon = 5, Glider = 6, Pulsar = 7
};

void getUserInput(size_t &lines, size_t& columns);
void initMatrix(std::vector<std::string>& matrixToInit, size_t lines, size_t columns);
void printMatrix(std::vector<std::string>& matrix);
int getNumberOfAliveNeighbours(std::vector<std::string>& matrix, size_t x, size_t y);
void createNextGeneration(std::vector<std::string>& matrix);
void drawPattern(Pattern desired_pattern, int x, int y, std::vector<std::string>& matrix);
int getTick();
Pattern getPattern(int &x, int &y);
void game(std::vector<std::string>& matrix);

int main()
{
	std::vector<std::string> matrix;
	size_t lines;
	size_t columns;

	getUserInput(lines, columns);
	initMatrix(matrix, lines, columns);
	
	//printMatrix(matrix);
	
	game(matrix);

	return 0;
}

void getUserInput(size_t& columns,size_t& lines)
{
	while (true)
	{
		int x = 0;
		int y = 0;

		std::cout << "Enter the dimensions of the matrix: (val1 val2)" << std::endl;
		if (std::cin.peek() == '\n') //if there is no input => then default val
		{
			lines = 20;
			columns = 20;
			return; //skipping the rest 
		}
		std::cin >> x >> y;

		if (std::cin.good())
		{
			if (x < 20 || y < 20)
			{
				std::cout << "The matrix is too small!\n" << std::endl;
			}
			else
			{
				columns = x;
				lines = y;
				return;
			}
		}
		else 
		{
			std::cout << "Invalid input!" << std::endl;
		}
	}
}

void initMatrix(std::vector<std::string>& matrixToInit, size_t lines, size_t columns) {

	std::string defaultValue = "-"; //dead

	for (size_t lineIndex = 0; lineIndex < (lines + 2); lineIndex++) //adding an extra border I can treat the cells form the initial border
	{
		matrixToInit.push_back(defaultValue);
		for(size_t colIndex = 1; colIndex < (columns+2); colIndex++)//I already have index 0 from the lines
		{
			matrixToInit[lineIndex].append(defaultValue);
		}
	}
	std::cout << std::endl;
}

void printMatrix(std::vector<std::string>& matrix) {

	for (size_t lineIndex = 1; lineIndex < (matrix.size() - 1); lineIndex++)//now I don't want to print the extra border of dead cells 
	{
		for (size_t colIndex = 1; colIndex < (matrix[lineIndex].size() - 1); colIndex++)
		{
			std::cout << matrix[lineIndex][colIndex] << " ";
		}
		std::cout << std::endl;
	} 
	std::cout << std::endl;
}

int getNumberOfAliveNeighbours(std::vector<std::string>& matrix, size_t x, size_t y) { //x,y = coordinates of the cell

	int aliveNeighbours = 0;
	
	//checking clockwise:

	for (size_t current_x = x; current_x < (x + 3); current_x++)//the top neighbouring cells
	{
		if (matrix[y - 1][current_x - 1] == ALIVE_CELL) //it starts from the top left corner of the cell to the top right corner
		{
			aliveNeighbours++;
		}
	}

	if (matrix[y][x + 1] == ALIVE_CELL) //the right cell left for checking
	{
		aliveNeighbours++;
	}

	for (size_t current_x = x; current_x < (x + 3); current_x++) //the bottom neighbouring cells
	{
		if (matrix[y + 1][current_x - 1] == ALIVE_CELL)
		{
			aliveNeighbours++;
		}
	}

	if (matrix[y][x - 1] == ALIVE_CELL) //the left cell
	{
		aliveNeighbours++;
	}

	return aliveNeighbours;
}

void createNextGeneration(std::vector<std::string>& matrix) {

	std::vector<std::string> nextGenMatrix = matrix;

	int aliveNeighbours = 0;

	for (size_t lineIndex = 1; lineIndex < (matrix.size() - 1); lineIndex++)
	{
		for (size_t colIndex = 1; colIndex < (matrix[lineIndex].size() - 1); colIndex++)
		{
			aliveNeighbours = getNumberOfAliveNeighbours(matrix, colIndex, lineIndex);
			//std::cout << aliveNeighbours << std::endl;

			//implementing the rules:
			if (matrix[lineIndex][colIndex] == DEAD_CELL && aliveNeighbours == 3)
			{
				nextGenMatrix[lineIndex][colIndex] = ALIVE_CELL;
			}
			else if (matrix[lineIndex][colIndex] == ALIVE_CELL && aliveNeighbours < 2)
			{
				nextGenMatrix[lineIndex][colIndex] = DEAD_CELL;
			}
			else if (matrix[lineIndex][colIndex] == ALIVE_CELL && (aliveNeighbours == 2 || aliveNeighbours == 3))
			{
				nextGenMatrix[lineIndex][colIndex] = ALIVE_CELL;
			}
			else if (matrix[lineIndex][colIndex] == ALIVE_CELL && aliveNeighbours > 3)
			{
				nextGenMatrix[lineIndex][colIndex] = DEAD_CELL;
			}
		}
	}

	matrix = nextGenMatrix;
}

int getTick() {

	int ticks = 0;

	while (true)
	{
		std::cout << "Enter the number of generations: " << std::endl;
		std::cin >> ticks;

		if (std::cin.good())
		{
			return ticks;
		}
		else
		{
			std::cout << "\nInvalid input!" << std::endl;
		}
	}
}

Pattern getPattern(int &x, int &y) {
	
	int pattern;

	while (true) 
	{
		std::cout << "\nPatterns:" << std::endl;
		std::cout << "1. Block" << std::endl;
		std::cout << "2. Boat" << std::endl;
		std::cout << "3. Blinker" << std::endl;
		std::cout << "4. Beacon" << std::endl;
		std::cout << "5. Pentadecathlon" << std::endl;
		std::cout << "6. Glider" << std::endl;
		std::cout << "7. Pulser" << std::endl;
		std::cout << "\nEnter the number of the pattern and the coordinates: (nr x y) " << std::endl;
		std::cin >> pattern >> x >> y;

		if (std::cin.good())
		{
			switch (pattern)
			{
			case Pattern::Beacon:
						return Beacon;
						break;
			case Pattern::Blinker:
						return Blinker;
						break;
			case Pattern::Block:
						return Block;
						break;
			case Pattern::Boat:
						return Boat;
						break;
			case Pattern::Pentadecathlon:
						return Pentadecathlon;
						break;
			case Pattern::Glider:
						return Glider;
						break;
			case Pattern::Pulsar:
						return Pulsar;
						break;
			default:
					break;
			}
		}
		else
		{
			std::cout << "\nInvalid input!" << std::endl;
		}
	}
}

std::vector<std::string> drawBlock()
{
	std::vector<std::string> patternBeacon;
	std::string aliveCell = "*";

	patternBeacon.push_back(aliveCell);
	patternBeacon.push_back(aliveCell);
	patternBeacon[0].append(aliveCell);
	patternBeacon[1].append(aliveCell);

	return patternBeacon;
}

std::vector<std::string> drawBoat()
{
	std::vector<std::string> patternBoat;
	std::string firstLine = "**-";
	std::string secondLine ="*-*";
	std::string thirdLine = "-*-";

	patternBoat.push_back(firstLine);
	patternBoat.push_back(secondLine);
	patternBoat.push_back(thirdLine);

	return patternBoat;
}

std::vector<std::string> drawBlinker()
{
	std::vector<std::string> patternBlinker;
	std::string blinker = "***";
	patternBlinker.push_back(blinker);

	return patternBlinker;
}

std::vector<std::string> drawBeacon()
{
	std::vector<std::string> patternBeacon;
	std::string firstLine = "**--";
	std::string secondLine ="*---";
	std::string thirdLine = "---*";
	std::string fourthLine ="--**";

	patternBeacon.push_back(firstLine);
	patternBeacon.push_back(secondLine);
	patternBeacon.push_back(thirdLine);
	patternBeacon.push_back(fourthLine);

	return patternBeacon;
}

std::vector<std::string> drawPentadecathlon()
{
	std::vector<std::string> patternPentad;
	std::string firstLine = "--*----*--"; //first line is also the third one
	std::string secondLine ="**-****-**";

	patternPentad.push_back(firstLine);
	patternPentad.push_back(secondLine);
	patternPentad.push_back(firstLine);

	return patternPentad;
}

std::vector<std::string> drawGlider()
{
	std::vector<std::string> patternGlider;
	std::string first_line = "-*-";
	std::string second_line ="--*";
	std::string third_line = "***";

	patternGlider.push_back(first_line);
	patternGlider.push_back(second_line);
	patternGlider.push_back(third_line);

	return patternGlider;
}

std::vector<std::string> drawPulsar()
{
	std::vector<std::string> patternPulsar;
	std::string firstLine =  "-----*-----*-----"; //this line is the same as 2, 14 and 15
	std::string thirdLine =  "-----**---**-----";
	std::string fourthLine = "-----------------"; //the same as 8 and 12
	std::string fifthLine =  "-***--**-**--***-";
	std::string sixthLine =  "---*-*-*-*-*-*---";
	std::string seventhLine ="-----**---**-----";
	std::string ninethLine = "-----**---**-----";
	std::string tenthLine =  "---*-*-*-*-*-*---";
	std::string eleventhLine="-***--**-**--***-";
	std::string thirteenthLine ="-----**---**-----";
	std::string fourteenthLine ="-----**---**-----";

	patternPulsar.push_back(firstLine);
	patternPulsar.push_back(firstLine);
	patternPulsar.push_back(thirdLine);
	patternPulsar.push_back(fourthLine);
	patternPulsar.push_back(fifthLine);
	patternPulsar.push_back(sixthLine);
	patternPulsar.push_back(seventhLine);
	patternPulsar.push_back(fourthLine);
	patternPulsar.push_back(ninethLine);
	patternPulsar.push_back(tenthLine);
	patternPulsar.push_back(eleventhLine);
	patternPulsar.push_back(fourthLine);
	patternPulsar.push_back(thirteenthLine);
	patternPulsar.push_back(firstLine);
	patternPulsar.push_back(firstLine);

	return patternPulsar;
}

void drawPattern(Pattern desiredPattern, int x, int y, std::vector<std::string>& matrix) {

	std::vector<std::string> pattern;

	if (desiredPattern == Pattern::Block)
	{
		pattern = drawBlock();
	}
	else if (desiredPattern == Pattern::Boat)
	{
		pattern = drawBoat();
	}
	else if (desiredPattern == Pattern::Blinker)
	{
		pattern = drawBlinker();
	}
	else if (desiredPattern == Pattern::Beacon)
	{
		pattern = drawBeacon();
	}
	else if (desiredPattern == Pattern::Pentadecathlon)
	{
		pattern = drawPentadecathlon();
	}
	else if (desiredPattern == Pattern::Glider)
	{
		pattern = drawGlider();
	}
	else if (desiredPattern == Pattern::Pulsar)
	{
		pattern = drawPulsar();
	}

	int current_x = x;

	for (size_t lineIndex = 0; lineIndex < pattern.size(); lineIndex++) //shape of the matrix
	{
		for (size_t colIndex = 0; colIndex < pattern[0].size(); colIndex++)
		{
			matrix[y][current_x] = pattern[lineIndex][colIndex];

			if ((matrix[1].size() - 2) > current_x)
			{
				current_x++;
			}
		}

		current_x = x; //reset the coordinate

		if ((matrix.size() - 2) > y)
		{
			y++; //next line	
		}
	}
}

void game(std::vector<std::string>& matrix) {

	int ticks = getTick();
	int currentTick = 0;
	int x, y; //pattern's coordinates
	Pattern inputPattern = getPattern(x, y);
	
	drawPattern(inputPattern, x, y, matrix);
	
	//checking the coordinates of the pattern
	while (x == 0 || y == 0 || x > (matrix[1].size() - 2) || y > (matrix.size() - 2))
	{
		std::cout << "Invalid coordinates" << std::endl;
		Pattern inputPattern = getPattern(x, y);
	}
	
	//printMatrix(matrix);

	while (currentTick < ticks)
	{
		std::cout << std::endl << "Generation: " << currentTick << std::endl;
		printMatrix(matrix);
		createNextGeneration(matrix);
		currentTick++;
	}
}