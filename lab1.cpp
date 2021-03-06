//WHAT IS SYSTEM('CLS')
// clears the command console screen

#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

class Currency {
private:
	string currencyName = "default currency name";
	string fractionalName = "default fractions name";
	int wholeValue = 0;
	int fractionalValue = 0;
public:
        Currency(string wholeName="whole", string partialName="partial"){
                setName(wholeName, partialName);
        }
        virtual ~Currency(){ cout << "hi "; }
	void setName(string wholeName, string partialName) { currencyName = wholeName; fractionalName = partialName; }
	void addWholeValue(int size) { wholeValue += size; }
	void addFractionalValue(int size) { fractionalValue += size; }
	void subtractWholeValue(int size) { wholeValue -= size; }
	void subtractFractionalValue(int size) { fractionalValue -= size; }
	void setFundsToZero() {
		wholeValue = 0;
		fractionalValue = 0;
	}
	double getCurrentFundsValue()
	{
		return (wholeValue + (fractionalValue / 100.0));
	}
	void balanceFraction() {
		// reuduce fractional values
		if (fractionalValue >= 100) {
			wholeValue += static_cast<int>(fractionalValue / 100);
			fractionalValue = fractionalValue % 100;
		}
	}

	//This function takes a single value, i.e. "11.99" and adds to its appropriate collection.
	friend void operator + (Currency &refCurrencyObject, double number)
	{
		refCurrencyObject.wholeValue += static_cast<int>(number);
		double x = number * 100;
		int y = (static_cast<int>(x) % 100);
		refCurrencyObject.fractionalValue += y;
		refCurrencyObject.balanceFraction();
	}

	//This function takes a single value, i.e. "11.99" and takes away from it's appropriate collection.
	friend void operator - (Currency &refCurrencyObject, double number)
	{
		refCurrencyObject.wholeValue -= static_cast<int>(number);
		double x = number * 100;
		int y = (static_cast<int>(x) % 100);
		refCurrencyObject.fractionalValue -= y;
		refCurrencyObject.balanceFraction();
	}

	// output stream overloading
	friend ostream& operator << (ostream &outputStream, Currency &refCurrencyObject)
	{
		cout << setprecision(2) << fixed;
		cout << refCurrencyObject.currencyName << ": " << refCurrencyObject.getCurrentFundsValue();
		return outputStream;
	}

	// make wallet class a friend
	friend class Wallet;
};

class Dollars : public Currency {
public:
        Dollars(string w="Dollars", string p="Cents"):Currency(w,p) {
                //setName("Dollars", "Cents");
        }
        ~Dollars(){ cout << "hey";}
};
class Euros : public Currency {
public:
        Euros(string w="Euros", string p="Cents"):Currency(w,p) {
                //setName("Euro", "Cents");
        }
        ~Euros(){ cout << "hey";}
};
class Rubles : public Currency {
public:
        Rubles(string w="Rubles", string p="Kopek"):Currency(w,p) {
                //setName("Ruble", "Kopek");
        }
        ~Rubles(){ cout << "hey";}
};
class Yuans : public Currency {
public:
        Yuans(string w="Yuans", string p="Fen"):Currency(w,p) {
                //setName("Yuan", "Fen");
        }
        ~Yuans(){ cout << "hey";}
};
class Pesos : public Currency {
public:
        Pesos(string w="Pesos", string p="Centavos"):Currency(w,p) {
                //setName("Peso", "Centavos");
        }
        ~Pesos(){ cout << "hey";}
};

class Wallet
{
private:
	Currency **current_currencies = new Currency*[5];
	double tempValue;
public:
	//Currency **current_currencies = new Currency*[5];
	Wallet(){
		current_currencies[0] = new Dollars();
		current_currencies[1] = new Euros();
		current_currencies[2] = new Rubles();
		current_currencies[3] = new Yuans();
		current_currencies[4] = new Pesos();
	}
	~Wallet(){
	        for(int i=0; i < 5; i++)
	        delete current_currencies[i];
	}
	void listAllCurrencyValues(){
		for (int i = 0; i < 5; i++)
		{
			if (current_currencies[i]->getCurrentFundsValue() >= 0)
				cout << *current_currencies[i] << endl;
		}
	}
	void zeroAllFunds()
	{
		for (int i = 0; i < 5; i++)
		{
			current_currencies[i]->setFundsToZero();
		}
	}
	void addCurrency(int type)
	{
		*(current_currencies[type]) + tempValue;
	}
	void subtractCurrency(int type)
	{
		*(current_currencies[type]) - tempValue;
	}
	
	// input stream overloading
	 friend istream& operator >> (istream &inputStream, Wallet &refCurrencyObject)
	 {
	       inputStream >> refCurrencyObject.tempValue;
	 }
	 friend void requestCurrencyNumberValues(bool isAddition, Wallet &walletReference, int currencyType);
};


int getMenuInput(int);
void requestCurrencyType(bool, Wallet&);
void requestCurrencyNumberValues(bool, Wallet&, int);
//void addCurrency();
//void subtractCurrency();
enum CurrencyType
{
	USDOLLARS, EUROS, RUBLES, YUANS, PESOS
};

int main()
{
	//Currency testCurrency;
	//Currency *currencyPtr = new Dollars;
	//Dollars testDollars;
	Wallet mainWallet;

	//mainWallet.listAllCurrencyValues();

	int choice = 0;
	while (choice != 5) {
		//system("cls");
		cout << "1:  add currency\n";
		cout << "2:  remove currency\n";
		cout << "3:  report current funds\n";
		cout << "4:  remove all currency\n";
		cout << "5:  exit program\n";
		cout << "\ntype your choice and press [ENTER]: ";
		choice = getMenuInput(5);
		switch (choice) {
		case 1: {   // add currency choice
					bool isAddition = true;
					requestCurrencyType(isAddition, mainWallet);
					cout << "press Enter to continue ...\n";
					cin.get();
					break;
		}
		case 2: {  // remove currency choice
					bool isAddition = false;
					requestCurrencyType(isAddition, mainWallet);
					cout << "press Enter to continue ...\n";
					cin.get();
					break;
		}
		case 3: {  // report funds choice
					cout << "\nrequesting currents funds ...\n";
					mainWallet.listAllCurrencyValues();
					cout << "\npress Enter to continue ...\n";
					cin.get();
					break;
		}
		case 4: {  // remove all funds choice
					mainWallet.zeroAllFunds();
					cout << "\npress Enter to continue ...\n";
					cin.get();
					break;
		}
		case 5: {  // exit program choice
					break;
		}
		default: {
					 // this should not get triggered
		}
		}  // end of switch bracket
	}
	cout << "press Enter to exit the program ...";
	cin.get();
	return 0;
}

void requestCurrencyType(bool isAddition, Wallet &walletReference)
{
	int choice = 0;
	cout << "\nchoose the currency type to work with\n";
	cout << "1: Dollars/Cents\n";
	cout << "2: Euro/Cents\n";
	cout << "3: Ruble/Kopek\n";
	cout << "4: Yuan/Fen\n";
	cout << "5: Peso/Centavos\n";
	cout << "6: return to main menu\n";
	cout << "\ntype your choice and press [ENTER]: ";
	choice = getMenuInput(6);

switch (choice) {
        case 1: {
                requestCurrencyNumberValues(isAddition, walletReference, USDOLLARS);
                break;
        }
        case 2: {
                requestCurrencyNumberValues(isAddition, walletReference, EUROS);
                break;
        }
        case 3: {
                requestCurrencyNumberValues(isAddition, walletReference, RUBLES);
                break;
        }
        case 4: {
                requestCurrencyNumberValues(isAddition, walletReference, YUANS);
                break;
        }
        case 5: {
                requestCurrencyNumberValues(isAddition, walletReference, PESOS);
                break;
        }
        case 6: {
                cout << "\npress Enter to continue ...";
                cin.get();
                break;
        }
	default: {

	}
	}  // end of switch bracket
}

void requestCurrencyNumberValues(bool isAddition, Wallet &walletReference, int currencyType)
{
	double value;
	cout << "Enter in the values: ";
	cin >> walletReference;
	if (isAddition) { // if this is an addition request
		walletReference.addCurrency(currencyType);
	}
	else { // else it is a subtraction request
		walletReference.subtractCurrency(currencyType);
	}
	//cout << "press Enter to continue ...";
	cin.get();
}

void addCurrency() {

}

void subtractCurrency() {

}

int getMenuInput(int size) {
	int userInput = 0;
	string tempString;
	getline(cin, tempString);
	while ((tempString[0] < 49 || tempString[0] > (48 + size)) || tempString[1] != '\0') {  // 1 - size
		cout << "1 - " << size << " are the only valid choices, try again: ";
		getline(cin, tempString);
	}
	userInput = stoi(tempString);
	return userInput;
}
