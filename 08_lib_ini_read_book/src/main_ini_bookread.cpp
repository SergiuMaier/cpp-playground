// Includes
//#define val_max 10; 

// C++ system headers
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// 3rd party libs headers
#include <SimpleIni.h>

/**
	Define a simple book.
*/
class Book
{
public:
	int contor;
	std::string count; 
	std::string name;
	std::string authors;

	void printFirst() {          //first section
		std::cout << "[books]\n";
		std::cout << "count=" << this->count << std::endl << "\n";;
	}
	void print()
	{
		std::cout << "[book." << this->contor <<"]\n";
		std::cout << "name=" << this->name << std::endl;
		std::cout << "author=" << this->authors << std::endl << "\n";
	}
};

/**
	Reads a vector of books from an INI file.
	Note: the INI file shall contain a general books section with the number of books contained,
	and another INI section for each book, named [book.N], where N is a number/counter

	[books]
	count = 2;

	[book.1]
	name=The origin of truth
	author=Gusti
	[book.2]
	name  = Arhanghelul Raul
	author=Ovidiu Eftimie

	@param file_name The name of the file to read from (must include path).
	@return Vector of books.
*/
std::vector<Book> readBooksFromIniFile(const std::string& file_name)
{	
	// TODO: BEGIN read the file -------------------------------------

	// E.g. Book myBook;
	//		// build the section name (E.g. book.1)
	//		std::stringstream ss;
	//		ss << "book." << (i + 1);
	//		// Copy the stream to a string you can use
	//		std::string section_name(ss.str());

	//		...
	//		results.emplace_back(myBook);
	
	std::vector<Book> results;
	Book myBook;

	CSimpleIniA ini_file;
	ini_file.SetUnicode();
	if (ini_file.LoadFile("../../data/ermahgerd_berks.ini") < 0)
		std::cout << "Could not open the file!\n";

	// So far this is the only way I have managed to solve this
    // Probably it could have been done easier

	const char* str= "books";  //the name given in the e.g.;
	myBook.count = ini_file.GetValue(str, "count", "def"); //getting the number of books writen in the file
	myBook.printFirst();     //printing the first section but not where I want it

	int countInt = stoi(myBook.count); //converting to integer to use the value below, in the loop
	
	std::stringstream ss[10];  //I tried std::stringstream ss[val_max] or ss[countInt] => error 	
	
	for (int i = 0; i < countInt; i++) {

		ss[i] << "book." << (i + 1);
		std::string& section_name = ss[i].str();
		const char* css = section_name.c_str();

		myBook.contor = i + 1;  //[book.i]
		myBook.name = ini_file.GetValue(css, "name", "def");
		myBook.authors = ini_file.GetValue(css, "author", "def");
		
		results.emplace_back(myBook);
	}

	// TODO: END read file and add to results vector ------------------
	return results;
}

int main()
{
	// Read a collection of books from an INI file.
	// Using the SimpleINI C++ Lib: https://github.com/brofield/simpleini

	// Read the data
	std::string input_data("../../data/ermahgerd_berks.ini");
	std::cout << "Reading the data from " << input_data << std::endl;
	std::vector<Book> books_from_file = readBooksFromIniFile(input_data);

	// Print the data
	std::cout << "Here are all the books found in the data file...\n" << std::endl;
	
	//Book book;
	//book.printFirst(); //not ok, something is missing 

	for (auto book : books_from_file)
	{
		book.print();
	}

	return 0;
}