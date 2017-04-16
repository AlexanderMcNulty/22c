//WHAT IS SYSTEM('CLS')

#include<iostream>
#include<string>

using namespace std;

class Currency{
private:
    string currencyName = "default currency name";
    string fractionalName = "default fractions name";
    int wholeValue = 0;
    int fractionalValue = 0;
public:
    void setName(string wholeName, string partialName){currencyName = wholeName; fractionalName = partialName;}
    void addWholeValue(int size){wholeValue += size;}
    void addFractionalValue(int size){fractionalValue += size;}
    void subtractWholeValue(int size){wholeValue -= size;}
    void subtractFractionalValue(int size){fractionalValue -= size;}
    void setFundsToZero(){
            wholeValue = 0;
            fractionalValue = 0;
    }
    void getCurrentFundsValue(){
            cout << wholeValue << "." << fractionalValue << endl;
    }
    void balanceFraction(){
            // reuduce fractional values
            if (fractionalValue >= 100){
                    wholeValue += static_cast<int>(fractionalValue / 100);
                    fractionalValue = fractionalValue % 100;
            }
    }

    //This function takes a single value, i.e. "11.99" and adds to its appropriate collection.
    friend void operator + (Currency &refCurrencyObject, double number){
            refCurrencyObject.wholeValue += static_cast<int>(number);
            double x = number * 100;
            int y = (static_cast<int>(x) % 100);
            refCurrencyObject.fractionalValue += y;
            refCurrencyObject.balanceFraction();
    }
    
    //This function takes a single value, i.e. "11.99" and takes away from it's appropriate collection.
    friend void operator - (Currency &refCurrencyObject, double number){
            refCurrencyObject.wholeValue -= static_cast<int>(number);
            double x = number * 100;
            int y = (static_cast<int>(x) % 100);
            refCurrencyObject.fractionalValue -= y;
            refCurrencyObject.balanceFraction();
    }

    // input stream overloading
    // friend istream& operator >> (istream &inputStream, Currency &refCurrencyObject)
    // {
    //         //refCurrencyObject.addWholeValue += inputStream;
    // }
    
    // output stream overloading
    friend ostream& operator << (ostream &outputStream, Currency &refCurrencyObject)
    {
        cout << refCurrencyObject.currencyName << ": " << refCurrencyObject.wholeValue << ".";
        if (refCurrencyObject.fractionalValue <= 9)  { // needed to format output
                cout << "0" << refCurrencyObject.fractionalValue;
        } else {
                cout << refCurrencyObject.fractionalValue;
        }
        return outputStream;
    }
};

class Dollars : public Currency {
public:
    Dollars(){
            setName("Dollars", "Cents");
    }
};
class Euros : public Currency {
public:
    Euros(){
            setName("Euro", "Cents");
    }
};
class Rubles : public Currency {
public:
    Rubles(){
            setName("Ruble", "Kopek");
    }
};
class Yuans : public Currency {
public:
    Yuans(){
            setName("Yuan", "Fen");
    }
};
class Pesos : public Currency {
public:
    Pesos(){
            setName("Peso", "Centavos");
    }
};

class Wallet {
private:
    Currency **current_currencies = new Currency*[5];
public:
    Wallet(){
        current_currencies[0] = new Dollars();
        current_currencies[1] = new Euros();
        current_currencies[2] = new Rubles();
        current_currencies[3] = new Yuans();
        current_currencies[4] = new Pesos();
    }
    void listAllCurrencyValues(){
        for(int i = 0; i < 5; i++){
            current_currencies[i]->getCurrentFundsValue();
            
        }
    }
};


int getMenuInput(int);
void requestCurrencyType(bool, Currency&, Dollars&);
void requestCurrencyNumberValues(bool, Currency&, Dollars&);
void addCurrency();
void subtractCurrency();


int main() {
    Currency testCurrency;
    Currency *currencyPtr = new Dollars;
    Dollars testDollars;
    
    Wallet mainWallet;
    
    mainWallet.listAllCurrencyValues();
    
    int choice = 0;
    while (choice != 5){
        system("cls");
        cout << "1:  add currency\n";
        cout << "2:  remove currency\n";
        cout << "3:  report current funds\n";
        cout << "4:  remove all currency\n";
        cout << "5:  exit program\n";
        cout << "\ntype your choice and press [ENTER]: ";
        choice = getMenuInput(5);
        switch (choice){
            case 1: {   // add currency choice
                bool isAddition = true;
                requestCurrencyType(isAddition, testCurrency, testDollars);
                cout << "press Enter to continue ...\n";
                cin.get();
                break;
            }
            case 2:  {  // remove currency choice
                bool isAddition = false;
                requestCurrencyType(isAddition, testCurrency, testDollars);
                cout << "press Enter to continue ...";
                cin.get();
                break;
            }
            case 3:  {  // report funds choice
                cout << "\nrequesting currents funds ...\n";
                cout << testCurrency << endl;
                cout << testDollars << endl;
                cout << "\npress Enter to continue ...";
                cin.get();
                break;
            }
            case 4:  {  // remove all funds choice
                testCurrency.setFundsToZero();
                testDollars.setFundsToZero();
                cout << "\npress Enter to continue ...";
                cin.get();
                break;
            }
            case 5:  {  // exit program choice
                break;
            }
            default:  {
                    // this should not get triggered
            }
        }  // end of switch bracket
    }

    cout << "press Enter to exit the program ...";
    cin.get();
    return 0;
}

void requestCurrencyType(bool isAddition, Currency &pointer, Dollars &dollarsPtr){
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
            requestCurrencyNumberValues(isAddition, pointer, dollarsPtr);
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            break;
        }
        case 4: {
            break;
        }
        case 5: {
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

void requestCurrencyNumberValues(bool isAddition, Currency &pointer, Dollars &dollarsPtr) {
    double value;
    cout << "Enter in the values: ";
    cin >> value;
    if (isAddition) { // if this is an addition request
            //pointer
            dollarsPtr + value;
    } else { // else it is a subtraction request
            dollarsPtr - value;
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
