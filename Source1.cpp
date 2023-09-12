
#include<iostream>
#include<conio.h>
#include <fstream>
#include<string>

using namespace std;

struct Manager
{
    string name;
    string position;
    int choice;
};
struct Carpets
{
    string name;
    int id = 0;
    int SalePrice = 0;
};
struct Supplier
{
    string name;
    int id = 0;
    string phoneno ;
};
struct Customer
{
    string name;
    int id = 0;
    string phoneno;
};
struct Bank
{
    string name;
    int id = 0;
    string phoneno;
};
struct Expense
{
    string name;
    int id = 0;
    
};
struct productsData
{
    string partyname;
    int proid;
    int rate;
    int debit;
    int credit;
    int balance;
    int supplierid;
    int customerid;
};
struct AccountData 
{
    string partyname;
    int id;
    string acc_type;
    int debit;
    int credit;
    int balance;
    int cash_in_hand;
    string tran_type;
};

void productarray(Carpets* carpets, int size);

//pure virtual functions
class MyLib
{
public:
    virtual int countRecords(string filename, int struct_size, int nxt_id = 0) = 0;
    virtual void storeDataInArray(Carpets* carpets, int record) = 0;
    virtual void storeDataInExpenseArray(Expense* expense, int record) = 0;
};
class MyLibImpl : public MyLib
{
public:

    //fuction overriding
    int countRecords(string filename, int struct_size, int nxt_id = 0) override
    {
        ifstream MyFile(filename);
        if (!MyFile)
        {
            cout << "Error: Unable to open file!";
            return 0;
        }
        else
        {
            int count = 0;
            string line;
            while (getline(MyFile, line))
            {
                ++count;
            }
            MyFile.close();

            return ((count / struct_size) + nxt_id);
        }
    }

    void storeDataInArray(Carpets* carpets, int record) override
    {
        try
        {
            ifstream MyFile2("products.txt");
            if (!MyFile2)
            {
                throw 0;
            }

            string line;
            int count = 0;
            while (count < record)
            {
                getline(MyFile2, line);
                carpets[count].name = line;
                getline(MyFile2, line);
                carpets[count].id = stoi(line);
                getline(MyFile2, line);
                carpets[count].SalePrice = stoi(line);
                ++count;
            }
            MyFile2.close();
        }
        catch (bool check)
        {
            cout << "Error: Unable to open file!";
            return;
        }
    }

    void storeDataInExpenseArray(Expense* expense, int record)
    {
        string filename = "expense.txt";
        try
        {
            ifstream MyFile2(filename);
            if (!MyFile2)
            {
                throw 0;
            }

            string line;
            int count = 0;
            while (count < record)
            {
                getline(MyFile2, line);
                expense[count].name = line;
                getline(MyFile2, line);
                expense[count].id = stoi(line);
                getline(MyFile2, line);
                ++count;
            }
            MyFile2.close();
        }
        catch (bool check)
        {
            cout << "Error: Unable to open file!";
            return;
        }

    }
};
class AddNew : public MyLibImpl
{
public:
    
    void add_new_carpet()
    {
        string filename = "products.txt";
        int n;
        cout << "How many items do you want to feed? : ";
        cin >> n;

        Carpets* carpets = new Carpets[n];
        int new_id = countRecords(filename, 3, 1);
        for (int i = 0; i < n; i++)
        {
            cout << "Enter Carpet Name: ";
            cin >> carpets[i].name;
            cout << "ID: " << new_id << endl;
            cout << "Enter Carpet Sale Price: ";
            cin >> carpets[i].SalePrice;
            new_id++;
        }

        try
        {
            ofstream MyFile(filename, ios::app);
            if (!MyFile)
            {
                throw 1;
            }
            else
            {
                int nextId = countRecords(filename, 3, 1) ;
                for (int i = 0; i < n; i++)
                {
                    carpets[i].id = nextId++;
                    MyFile << carpets[i].name << endl;
                    MyFile << carpets[i].id << endl;
                    MyFile << carpets[i].SalePrice << endl;
                }
                cout << "Data entered in names file.\n";
            }
            MyFile.close();
            delete[] carpets;
        }
        catch (bool check)
        {
            cout << "Error: Unable to open file!";
            return;
        }

        int record = countRecords(filename, 3, 0);
        cout << "Total records entered: " << record << endl;

        carpets = new Carpets[record];
        storeDataInArray(carpets, record);

        cout << endl << "\tList of Products:\n";
        for (int i = 0; i < record; i++)
        {
            cout << "Carpet Name         : " << carpets[i].name << endl;
            cout << "Carpet ID           : " << carpets[i].id << endl;
            cout << "Carpet Sale Price   : " << carpets[i].SalePrice << endl;
        }
        delete[] carpets;
        _getch();
    }
    void add_new_Expense()
    {
        string filename = "expense.txt";

        int n;
        cout << "how many Expense data do you want to feed? : ";
        cin >> n;

        Expense* expense = new Expense[n];
        int new_id = countRecords(filename, 2, 1);
        for (int i = 0; i < n; i++)
        {
            cout << " Enter Expense Name         : ";
            cin >> expense[i].name;
            cout << endl;
            cout << " Expense ID: " << new_id << endl;
            cout << endl;
            new_id++;
        }
        try
        {
            ofstream MyFile(filename, ios::app);
            if (!MyFile)
            {
                throw 1;
            }
            else
            {
                int nextId = countRecords(filename, 2, 1);
                for (int i = 0; i < n; i++)
                {
                    expense[i].id = nextId++;
                    MyFile << expense[i].name << endl;
                    MyFile << expense[i].id << endl;

                }
                cout << "Data entered in banks file \n";
            }
            MyFile.close();
            delete[] expense;
        }
        catch (bool check)
        {
            cout << "Error: Unable to open file!";
            return;
        }

        int record = countRecords("expense.txt", 2, 0);
        cout << "Total record Entered :  " << record << endl;

        expense = new Expense[record];
        storeDataInExpenseArray(expense, record);

        cout << endl << "\tList of Expenses : \n";
        for (int i = 0; i < record; i++)
        {
            cout << " Expense Name         : " << expense[i].name << endl;
            cout << " Expense ID           : " << expense[i].id << endl;

        }
        delete[] expense;
        _getch();
        return;



    }

};
//Friend class
class FriendClass
{
public:
    void friendAccess(AddNew& obj)
    {
        obj.add_new_carpet();
        obj.add_new_Expense();
    }


};

//Functions to access class
void add_new_carpet()
{
    MyLibImpl obj;
    AddNew addNewObj;
    MyLib* basePtr = &addNewObj;
    basePtr->countRecords("products.txt", 3, 0);
    basePtr->storeDataInArray(nullptr, 0);
    addNewObj.add_new_carpet();
}
void add_new_Expense()
{
    MyLibImpl obj;
    AddNew addNewObj;
    MyLib* basePtr = &addNewObj;
    basePtr->countRecords("expense.txt", 2, 0);
    basePtr->storeDataInArray(nullptr, 0);
    addNewObj.add_new_carpet();
}



class mylib
{
    int next_id = 0;
public:

    // Function to count the number of records in the file
    int countRecords(string filename, int struct_size, int nxt_id = 0)
    {
        try {
            ifstream MyFile(filename);
            if (!MyFile)
            {
                throw "Error: Unable to open file!";
            }
            else
            {
                int count = 0;
                string line;
                while (getline(MyFile, line))
                {
                    ++count;

                }
                MyFile.close();

                return ((count / struct_size) + nxt_id);
            }
        }
        catch (const char* errorMsg)
        {
            cout << errorMsg << endl;
            return 0;
        }

    }

};
class add_new : public mylib
{
public:
    
    void storeDataInBankArray(Bank* bank, int record)
    {
        string filename = "banks.txt";
        try
        {
            ifstream MyFile2(filename);
            if (!MyFile2)
            {
                throw 0;
            }

            string line;
            int count = 0;
            while (count < record)
            {
                getline(MyFile2, line);
                bank[count].name = line;
                getline(MyFile2, line);
                bank[count].id = stoi(line);
                getline(MyFile2, line);
                bank[count].phoneno = stoi(line);
                ++count;
            }
            MyFile2.close();
        }
        catch (bool check)
        {
            cout << "Error: Unable to open file!";
            return;
        }

    }
    template<typename T>
    void storeDataInArray(T* data, int record, const string& filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cout << "Error: Unable to open file!" << endl;
            return;

        }
        else
        {
            string line;
            int count = 0;
            while (count < record)
            {
                getline(file, line);
                data[count].name = line;
                getline(file, line);
                data[count].id = stoi(line);
                getline(file, line);
                data[count].phoneno = stoi(line);
                ++count;
            }
            file.close();
        }
    }


  
    void add_new_customer()
    {
        
        string filename = "customers.txt";
        int n;
        cout << "how many Customers Data do yoy want to feed? : ";
        cin >> n;

        Customer* customer = new Customer[n];
        int new_id = countRecords(filename, 3, 1);
        for (int i = 0; i < n; i++)
        {
            cout << " Enter CUSTOMER Name         : ";
            cin >> customer[i].name;
            cout << endl;
            cout << "ID: " << new_id << endl;
            cout << "Enter Customers Phone Number : ";
            cin >> customer[i].phoneno;
            cout << endl;
            new_id++;
        }
        try
        {
            ofstream MyFile(filename, ios::app);
            if (!MyFile)
            {
                throw 0;
            }
            else
            {
                int nextId = countRecords(filename, 3, 1);
                for (int i = 0; i < n; i++)
                {
                    customer[i].id = nextId++;
                    MyFile << customer[i].name << endl;
                    MyFile << customer[i].id << endl;
                    MyFile << customer[i].phoneno << endl;
                }
                cout << "Data entered in Customers file \n";
            }
            MyFile.close();
            delete[] customer;
        }
        catch (bool check)
        {
            cout << "Error: Unable to open file!";
            return;
        }

        int record = countRecords("customers.txt", 3, 0);
        cout << "Total record Entered :  " << record << endl;

        customer = new Customer[record];
        storeDataInArray(customer, record,"customers.txt");

        cout << endl << "\tList of Customers : \n";
        for (int i = 0; i < record; i++)
        {
            cout << " Customers Name         : " << customer[i].name << endl;
            cout << " Customers ID           : " << customer[i].id << endl;
            cout << " Customer Phone No. : " << customer[i].phoneno << endl;

        }
        delete[] customer;
        _getch();
        return;


    }
    void add_new_supplier()
    {
        string filename = "supplier.txt";
        int n;
        cout << "how many Suppliers Data do yoy want to feed? : ";
        cin >> n;

        Supplier* supplier = new Supplier[n];
        int new_id = countRecords(filename, 3, 1);
        for (int i = 0; i < n; i++)
        {
            cout << " Enter Supplier Name         : ";
            cin >> supplier[i].name;
            cout << endl;
            cout << "ID: " << new_id << endl;
            cout << "Enter Supplier Phone Number : ";
            cin >> supplier[i].phoneno;
            cout << endl;
            new_id++;
        }
        try
        {
            ofstream MyFile(filename, ios::app);
            if (!MyFile)
            {
                throw 1;
            }
            else
            {
                int nextId = countRecords(filename, 3, 1);
                for (int i = 0; i < n; i++)
                {
                    supplier[i].id = nextId++;
                    MyFile << supplier[i].name << endl;
                    MyFile << supplier[i].id << endl;
                    MyFile << supplier[i].phoneno << endl;
                }
                cout << "Data entered in Supplier file \n";
            }
            MyFile.close();
            delete[] supplier;
        }
        catch (bool check)
        {
            cout << "Error: Unable to open file!";
            return;
        }

        int record = countRecords("supplier.txt", 3, 0);
        cout << "Total record Entered :  " << record << endl;

        supplier = new Supplier[record];
        storeDataInArray(supplier, record,"supplier.txt");

        cout << endl << "\tList of Suppliers : \n";
        for (int i = 0; i < record; i++)
        {
            cout << " Suppliers Name         : " << supplier[i].name << endl;
            cout << " Supplier ID           : " << supplier[i].id << endl;
            cout << " Supplier Phone No. : " << supplier[i].phoneno << endl;

        }
        delete[] supplier;
        return;


    }
    void add_new_Bank()
    {
        string filename = "banks.txt";

        int n;
        cout << "how many Banks data do you want to feed? : ";
        cin >> n;

        Bank* bank = new Bank[n];
        int new_id = countRecords(filename, 3, 1);
        for (int i = 0; i < n; i++)
        {
            cout << " Enter Bank Name         : ";
            cin >> bank[i].name;
            cout << endl;
            cout << "ID: " << new_id << endl;
            cout << "Enter Bank Phone Number : ";
            cin >> bank[i].phoneno;
            cout << endl;
            new_id++;
        }
        try
        {
            ofstream MyFile(filename, ios::app);
            if (!MyFile)
            {
                throw 1;
            }
            else
            {
                int nextId = countRecords(filename, 3, 1) ;
                for (int i = 0; i < n; i++)
                {
                    bank[i].id = nextId++;
                    MyFile << bank[i].name << endl;
                    MyFile << bank[i].id << endl;
                    MyFile << bank[i].phoneno << endl;
                }
                cout << "Data entered in banks file \n";
            }
            MyFile.close();
            delete[] bank;
        }
        catch (bool check)
        {
            cout << "Error: Unable to open file!";
            return;
        }

        int record = countRecords("banks.txt", 3, 0);
        cout << "Total records entered: " << record << endl;

        bank = new Bank[record];
        storeDataInBankArray(bank, record);

        cout << endl << "\tList of Banks:\n";
        for (int i = 0; i < record; i++)
        {
            cout << " Bank Name         : " << bank[i].name << endl;
            cout << " Bank ID           : " << bank[i].id << endl;
            cout << " Bank Phone Number : " << bank[i].phoneno << endl;
        }

        delete[] bank;
        _getch();
        return;

    }
  

};

ostream& operator<<(ostream& os, const Bank& bank)
{
    os << "Bank Name         : " << bank.name << endl;
    os << "Bank ID           : " << bank.id << endl;
    os << "Bank Phone Number : " << bank.phoneno << endl;
    return os;
}



class Transactions : public mylib
{
    int supplier_code;
    int customer_code;
    int pro_id; 
    int quantity; 
    int Rate;
    friend void productarray(Carpets* carpets, int size);

public:
    
   void purchase()
    {
        //create supplier array

        mylib obj, obj2;
        int array_Size = obj.countRecords("supplier.txt", 3,0);
        Supplier* supplier = new Supplier[array_Size];
        ifstream Myfile("supplier.txt");
        string id;
        for (int i = 0; i < array_Size; i++)
        {
            getline(Myfile, supplier[i].name);

            getline(Myfile, id);
            supplier[i].id = stoi(id);

            getline(Myfile, supplier[i].phoneno);
        }
        Myfile.close();

        int array2_Size = countRecords("products.txt", 3,0);
        Carpets* carpets = new Carpets[array2_Size];
        productarray(carpets, array2_Size);

    cout << "\t\t\t\t-------------------------------------------------" << endl;
    cout << "\t\t\t\t\tID " << "\t\tSuppliers Name\t\t"  << endl;
    cout << "\t\t\t\t-------------------------------------------------" << endl;

    string name,phone_no;

    for (int i = 0; i < array_Size; i++)
    {
        cout <<"\t\t\t\t\t" << supplier[i].id << "\t\t" << supplier[i].name << endl;
    }

    cout << "Enter Id of supplier from which you purchase : ";
    cin >> supplier_code;

    cout << "\t\t\t\t-------------------------------------------------"  << endl;
    cout << "\t\t\t\t\tID " << "\t\t Carpet_Name\t\t" << "Rate\t\t" << endl;
    cout << "\t\t\t\t-------------------------------------------------"  << endl;

    for (int i = 0; i < array2_Size ; i++)
    {
        cout << "\t\t\t\t\t" << carpets[i].id << "\t\t" << carpets[i].name<<"\t\t\t"<<carpets[i].SalePrice << endl;
    }
    

    cout << "Enter Id of Item you Prchase : ";
    cin >> pro_id;
    cout << "Enter quantity of carpet you Purhased : ";
    cin >> quantity;

    int prev_stock = stock(pro_id);
   
   

    ofstream MyFile("productdata.txt",ios::app);
    MyFile << supplier[supplier_code - 1].name << endl;
    MyFile << pro_id << endl;
    MyFile << carpets[pro_id-1].SalePrice << endl;
    MyFile << quantity << endl;
    MyFile << 0 << endl;
    MyFile <<(prev_stock+quantity) << endl;
    MyFile << supplier_code << endl;
    MyFile << 0 << endl;
   
    MyFile.close();

    cout << "\n\n-------------------------------------------------------------\n\n";
    cout << "\n\nPrevious stock :\t " << prev_stock;
    cout << "\nPurchase stock :\t" << quantity;
    cout << "\nTotal stock : \t" << (prev_stock + quantity);


    string partyname = supplier[supplier_code - 1].name;
    string acc_type;
    int debit = (quantity* carpets[pro_id - 1].SalePrice);
    int credit=0;
    
    int supplier_prev_balance = account_balance(supplier_code,"supplier");  //find supplier previous balance
    
    int balance = supplier_prev_balance + debit;
    int cash_in_hand = 0;
    string tran_type = "purchase"; 


    ofstream MyFile3("accountdata.txt", ios::app);
    MyFile3 << partyname << endl;
    MyFile3 << supplier_code << endl;
    MyFile3 << "supplier" << endl;
    MyFile3 << debit << endl;
    MyFile3 << credit << endl;
    MyFile3 << balance << endl;
    MyFile3 << cash_in_hand << endl;
    MyFile3 << tran_type << endl;

    MyFile3.close();


    _getch();

    }
   int stock(int filter_id)
    {
       try
       {
           ifstream MyFile2("productdata.txt");
           if (!MyFile2)
           {
              throw 1;
           }

           string line;
           int count = 0;
           int file_size = countRecords("productdata.txt", 8, 0);

           productsData* productdata = new productsData[file_size];

           int last_found = 0;



           while (count < file_size)
           {

               getline(MyFile2, line);
               productdata[count].partyname = line;
               getline(MyFile2, line);
               productdata[count].proid = stoi(line);
               getline(MyFile2, line);
               productdata[count].rate = stoi(line);
               getline(MyFile2, line);
               productdata[count].debit = stoi(line);
               getline(MyFile2, line);
               productdata[count].credit = stoi(line);
               getline(MyFile2, line);
               productdata[count].balance = stoi(line);
               getline(MyFile2, line);
               productdata[count].supplierid = stoi(line);
               getline(MyFile2, line);
               productdata[count].customerid = stoi(line);

               if (productdata[count].proid == filter_id)
               {
                   last_found = productdata[count].balance;
               }

               ++count;
           }
           MyFile2.close();
          return last_found;
       }
       catch (bool check)
       {
           cout << "Error: Unable to open file!";
           return 0;
       }
        
    }
   int account_balance(int filter_id ,string acc_type )
   {

       ifstream MyFile2("accountdata.txt");
       if (!MyFile2)
       {
           cout << "Error: Unable to open file!" << endl;
           return 0;
       }

       string line;
       int count = 0;
       int file_size = countRecords("accountdata.txt", 8, 0);

       AccountData* accountdata = new AccountData[file_size];

       int last_found = 0;

       while (count < file_size)
       {

           getline(MyFile2, line);
           accountdata[count].partyname = line;
           getline(MyFile2, line);
           accountdata[count].id = stoi(line);
           getline(MyFile2, line);
           accountdata[count].acc_type = line;
           getline(MyFile2, line);
           accountdata[count].debit = stoi(line);
           getline(MyFile2, line);
           accountdata[count].credit = stoi(line);
           getline(MyFile2, line);
           accountdata[count].balance = stoi(line);
           getline(MyFile2, line);
           accountdata[count].cash_in_hand = stoi(line);
           getline(MyFile2, line);
           accountdata[count].tran_type = line;


           if (accountdata[count].id == filter_id && accountdata[count].acc_type == acc_type)
           {
               last_found = accountdata[count].balance;
           }

           ++count;
       }
       MyFile2.close();

       return last_found;
   }
   void sales( )
   {
       //create supplier array

       mylib obj, obj2;
       int array_Size = obj.countRecords("customers.txt", 3,0);
       Customer* customer = new Customer[array_Size];
       
       ifstream Myfile("customers.txt");
       string id;
       for (int i = 0; i < array_Size; i++)
       {
           getline(Myfile, customer[i].name);

           getline(Myfile, id);
           customer[i].id = stoi(id);

           getline(Myfile, customer[i].phoneno);
       }
       Myfile.close();


       int array2_Size = countRecords("products.txt", 3,0);
       Carpets* carpets = new Carpets[array2_Size];
       productarray(carpets, array2_Size);

       
       
       cout << "\t\t\t\t-------------------------------------------------" << endl;
       cout << "\t\t\t\t\tID " << "\t\tCustomer Name\t\t" << endl;
       cout << "\t\t\t\t-------------------------------------------------" << endl;

       string name, phone_no;

       for (int i = 0; i < array_Size; i++)
       {
           cout << "\t\t\t\t\t" << customer[i].id << "\t\t" << customer[i].name << endl;
       }

       cout << "Enter Id of customer to which you sell : ";
       cin >> customer_code;

       cout << "\t\t\t\t-------------------------------------------------" << endl;
       cout << "\t\t\t\t\tID " << "\t\t Carpet_Name\t\t" << endl;
       cout << "\t\t\t\t-------------------------------------------------" << endl;
       
       for (int i = 0; i < array2_Size; i++)
       {
           cout << "\t\t\t\t\t" << carpets[i].id << "\t\t" << carpets[i].name  << endl;
       }


       cout << "Enter Id of Item you sell : ";
       cin >> pro_id;
       int prev_stock = stock(pro_id);
       cout << "\n\nPrevious stock :\t " << prev_stock;
       while (prev_stock < quantity)
       {
           cout << "out of stock try again";
           cout << "\n\nPrevious stock :\t " << prev_stock;
           cout << "\nEnter Sold stock again :\t"; cin >> quantity;
       }

       cout << "\nEnter quantity of carpet you sell : ";
       cin >> quantity;
       int rate;
       cout << "Enter price you want to sell : ";
       cin >> rate;
       
       
       ofstream MyFile("productdata.txt", ios::app);
       
       MyFile << customer[customer_code - 1].name << endl;
       MyFile << pro_id << endl;
       MyFile << rate << endl;
       MyFile << 0 << endl;
       MyFile << quantity << endl;
       MyFile << (prev_stock - quantity) << endl;
       MyFile << 0 << endl;
       MyFile << customer_code << endl;

       MyFile.close();
       cout << "\n\n-------------------------------------------------------------\n\n";
      
       cout << "\nSold stock :\t" << quantity;       
       cout << "\nTotal stock : \t" << (prev_stock - quantity);
      
       
      string partyname = customer[customer_code - 1].name;
      string acc_type;
      int debit_amount = 0;
      int credit_amount = quantity *rate;

       int customer_prev_balance = account_balance(customer_code, "customer");  //find customer previous balance
       int balance = customer_prev_balance + credit_amount;
       int cash_in_hand = 0;
       string tran_type = "sale";

       ofstream MyFile3("accountdata.txt", ios::app);
       MyFile3 << partyname << endl;
       MyFile3 << customer_code << endl;
       MyFile3 << "customer" << endl;
       MyFile3 << debit_amount << endl;
       MyFile3 << credit_amount << endl;
       MyFile3 << balance << endl;
       MyFile3 << cash_in_hand << endl;
       MyFile3 << tran_type << endl;

       MyFile3.close();

       _getch();

   }
   
   void cash_from_customer()
   {

       //create supplier array
       mylib obj, obj2;
       int array_Size = obj.countRecords("customers.txt", 3, 0);
       Customer* customer = new Customer[array_Size];
       ifstream Myfile("customers.txt");
       string id;
       for (int i = 0; i < array_Size; i++)
       {
           getline(Myfile, customer[i].name);

           getline(Myfile, id);
           customer[i].id = stoi(id);

           getline(Myfile, customer[i].phoneno);
       }
       Myfile.close();

       int array2_Size = countRecords("customers.txt", 3, 0);
       Carpets* carpets = new Carpets[array2_Size];
       productarray(carpets, array2_Size);

       cout << "\t\t\t\t-------------------------------------------------" << endl;
       cout << "\t\t\t\t\tID " << "\t\tCustomer Name\t\t" << endl;
       cout << "\t\t\t\t-------------------------------------------------" << endl;

       string name, phone_no;

       for (int i = 0; i < array_Size; i++)
       {
           cout << "\t\t\t\t\t" << customer[i].id << "\t\t" << customer[i].name << endl;
       }

       cout << "Enter Id of Customer from which you purchase : ";
       cin >> customer_code;



       string partyname = customer[customer_code - 1].name;
       string acc_type;
       int debit = 0;
       int credit = 0;

       int customer_prev_balance = account_balance(customer_code, "customer");  //find customer previous balance


       int cash_in_hand = 0;
       string tran_type = "cash";

       cout << "\n\t Enter Cash take from customer :\t";
       cin >> debit;
       int balance = customer_prev_balance + debit;

       ofstream MyFile3("accountdata.txt", ios::app);
       MyFile3 << partyname << endl;
       MyFile3 << customer_code << endl;
       MyFile3 << "customer" << endl;
       MyFile3 << debit << endl;
       MyFile3 << credit << endl;
       MyFile3 << balance << endl;
       MyFile3 << cash_in_hand << endl;
       MyFile3 << tran_type << endl;

       MyFile3.close();


       _getch();



   }
   void cash_to_supplier()
   {

       //create supplier array
       mylib obj, obj2;
       int array_Size = obj.countRecords("supplier.txt", 3, 0);
       Supplier* supplier = new Supplier[array_Size];
       ifstream Myfile("supplier.txt");
       string id;
       for (int i = 0; i < array_Size; i++)
       {
           getline(Myfile, supplier[i].name);

           getline(Myfile, id);
           supplier[i].id = stoi(id);

           getline(Myfile, supplier[i].phoneno);
       }
       Myfile.close();

       int array2_Size = countRecords("products.txt", 3, 0);
       Carpets* carpets = new Carpets[array2_Size];
       productarray(carpets, array2_Size);

       cout << "\t\t\t\t-------------------------------------------------" << endl;
       cout << "\t\t\t\t\tID " << "\t\tSuppliers Name\t\t" << endl;
       cout << "\t\t\t\t-------------------------------------------------" << endl;

       string name, phone_no;

       for (int i = 0; i < array_Size; i++)
       {
           cout << "\t\t\t\t\t" << supplier[i].id << "\t\t" << supplier[i].name << endl;
       }

       cout << "Enter Id of supplier from which you purchase : ";
       cin >> supplier_code;



       string partyname = supplier[supplier_code - 1].name;
       string acc_type;
       int debit = 0;
       int credit = 0;

       int supplier_prev_balance = account_balance(supplier_code, "supplier");  //find supplier previous balance

      
       int cash_in_hand = 0;
       string tran_type = "cash";

       cout << "\n\t Enter Cash of Carpet :\t";
       cin >> credit;
       int balance = supplier_prev_balance - credit;

       ofstream MyFile3("accountdata.txt", ios::app);
       MyFile3 << partyname << endl;
       MyFile3 << supplier_code << endl;
       MyFile3 << "supplier" << endl;
       MyFile3 << debit << endl;
       MyFile3 << credit << endl;
       MyFile3 << balance << endl;
       MyFile3 << cash_in_hand << endl;
       MyFile3 << tran_type << endl;

       MyFile3.close();


       _getch();

   }
   void cash_from_Bank()
   {
       //create supplier array
      mylib obj, obj2;
      int array_Size = obj.countRecords("banks.txt", 3, 0);
      Bank* bank = new Bank[array_Size];
           ifstream Myfile("customers.txt");
           string id;
           for (int i = 0; i < array_Size; i++)
           {
               getline(Myfile, bank[i].name);

               getline(Myfile, id);
               bank[i].id = stoi(id);

               getline(Myfile, bank[i].phoneno);
           }
           Myfile.close();

           int array2_Size = countRecords("banks.txt", 3, 0);
           Carpets* carpets = new Carpets[array2_Size];
           productarray(carpets, array2_Size);

           cout << "\t\t\t\t-------------------------------------------------" << endl;
           cout << "\t\t\t\t\tID " << "\t\tBank Name\t\t" << endl;
           cout << "\t\t\t\t-------------------------------------------------" << endl;

           string name, phone_no;

           for (int i = 0; i < array_Size; i++)
           {
               cout << "\t\t\t\t\t" << bank[i].id << "\t\t" << bank[i].name << endl;
           }
           int bank_code;
           cout << "Enter Bank ID : ";
           cin >> bank_code;



           string partyname = bank[bank_code - 1].name;
           string acc_type;
           int debit = 0;
           int credit = 0;

          int bank_prev_balance = account_balance(bank_code, "bank");  //find customer previous balance


           int cash_in_hand = 0;
           string tran_type = "cash";

           cout << "\n\t Enter Cash take from Bank :\t";
           cin >> debit;
          int balance = bank_prev_balance + debit;

          ofstream MyFile3("accountdata.txt", ios::app);
           MyFile3 << partyname << endl;
           MyFile3 << bank_code << endl;
           MyFile3 << "bank" << endl;
           MyFile3 << debit << endl;
           MyFile3 << credit << endl;
           MyFile3 << balance << endl;
           MyFile3 << cash_in_hand << endl;
           MyFile3 << tran_type << endl;

           MyFile3.close();


           _getch();




   }
   void cash_to_Bank()
   {
       //create supplier array
       mylib obj, obj2;
       int array_Size = obj.countRecords("banks.txt", 3, 0);
       Bank* bank = new Bank[array_Size];
       ifstream Myfile("banks.txt");
       string id;
       for (int i = 0; i < array_Size; i++)
       {
           getline(Myfile, bank[i].name);

           getline(Myfile, id);
           bank[i].id = stoi(id);

           getline(Myfile, bank[i].phoneno);
       }
       Myfile.close();

       int array2_Size = countRecords("banks.txt", 3, 0);
       Carpets* carpets = new Carpets[array2_Size];
       productarray(carpets, array2_Size);

       cout << "\t\t\t\t-------------------------------------------------" << endl;
       cout << "\t\t\t\t\tID " << "\t\tBank Name\t\t" << endl;
       cout << "\t\t\t\t-------------------------------------------------" << endl;

       string name, phone_no;

       for (int i = 0; i < array_Size; i++)
       {
           cout << "\t\t\t\t\t" << bank[i].id << "\t\t" << bank[i].name << endl;
       }

       int bank_code;
       cout << "Enter Bank: ";
       cin >> bank_code;



       string partyname = bank[bank_code - 1].name;
       string acc_type;
       int debit = 0;
       int credit = 0;

       int bank_prev_balance = account_balance(bank_code, "bank");  //find supplier previous balance


       int cash_in_hand = 0;
       string tran_type = "cash";

       cout << "\n\t Enter Cash :\t";
       cin >> credit;
       int balance = bank_prev_balance - credit;

       ofstream MyFile3("accountdata.txt", ios::app);
       MyFile3 << partyname << endl;
       MyFile3 << bank_code << endl;
       MyFile3 << "supplier" << endl;
       MyFile3 << debit << endl;
       MyFile3 << credit << endl;
       MyFile3 << balance << endl;
       MyFile3 << cash_in_hand << endl;
       MyFile3 << tran_type << endl;

       MyFile3.close();


       _getch();
   }
   

};
class reports : public mylib
{
    friend void productarray(Carpets* carpets, int size);
public:
    
    struct salesstock
    {
        string product_name;
        int id;
        int purchase=0;
        int sale=0;
        int stock=0;
    };
    
    
    void sales_stock_report()
    {
        int size_ssr = countRecords("products.txt", 3,0);
        salesstock* ssr = new salesstock[size_ssr];
        
        string ignored_line, id, purchase ,sale ,balance;
        
        ifstream Myfile2("products.txt");
        for (int i = 0; i < size_ssr; i++)
        {
            getline(Myfile2, ssr[i].product_name);
            getline(Myfile2, id);
            ssr[i].id = stoi(id);
            getline(Myfile2, ignored_line);
        }
        Myfile2.close();

        int size = countRecords("productdata.txt", 8,0);
        int index;
        ifstream Myfile("productdata.txt");
        for (int i = 0; i < size; i++)
        {
            getline(Myfile, ignored_line);
            
            getline(Myfile,id);
            index = stoi(id) -1;

            getline(Myfile, ignored_line);
            
            getline(Myfile, purchase);
            ssr[index].purchase = stoi(purchase)+ ssr[index].purchase;

            getline(Myfile, sale);
            ssr[index].sale = stoi(sale) + ssr[index].sale;

            getline(Myfile, balance);
            ssr[index].stock = stoi(balance);

            getline(Myfile, ignored_line);
            getline(Myfile, ignored_line);


        }
        Myfile2.close();



        cout << "\t\t\t\t-------------------------------------------------" << endl;
        cout << "\t\t\tItemName " << "\tSales\t" << "\tPurchase\t" << "\tStock\t" << endl;
        cout << "\t\t\t\t-------------------------------------------------" << endl;

        string name, phone_no;
        for (int i = 0; i < size_ssr; i++)
        {
            cout << "\t\t" << ssr[i].product_name;
            cout << "\t\t" << ssr[i].sale;
            cout << "\t" << ssr[i].purchase;
            cout << "\t" << ssr[i].stock << endl;
        }


       
    }
    void one_product_detail()
    {
        int array2_Size = countRecords("products.txt", 3,0);
        Carpets* carpets = new Carpets[array2_Size];
        productarray(carpets, array2_Size);

        cout << "\t\t\t\t-------------------------------------------------" << endl;
        cout << "\t\t\t\tID" << "\t\t Carpet_Name\t\t" << "Rate\t\t" << endl;
        cout << "\t\t\t\t-------------------------------------------------" << endl;

        for (int i = 0; i < array2_Size; i++)
        {
            cout << "\t\t\t\t\t" << carpets[i].id << "\t\t" << carpets[i].name << "\t\t\t" << carpets[i].SalePrice << endl;
        }

        int pro_id;
        cout << "Enter Id of Item you want to check Report : ";
        cin >> pro_id;



        string partyname,proid,rate,debit,credit, balance, supplierid, customerid;
        
        array2_Size = countRecords("productdata.txt", 8,0);

        ifstream Myfile("productdata.txt");
        
        cout << "-------------------------------------------------------------------------------------------" << endl;
        cout << "\tProduct_ID" << "\tRate\t" << "\tDebit\t" << "\tCredit\t" << "\tBalance\t" << "\tPartyName" << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;

        
        for (int i = 0; i < array2_Size; i++)
        {
            getline(Myfile, partyname);
            getline(Myfile, proid);
            getline(Myfile, rate);
            getline(Myfile, debit);
            getline(Myfile, credit);
            getline(Myfile, balance);
            getline(Myfile, supplierid);
            getline(Myfile, customerid);

            if (pro_id == stoi(proid))
            {
                cout  << proid << "\t\t" << rate << "\t\t";
                cout << debit << "\t\t" << credit << "\t\t" << balance << "\t\t";
                cout << partyname  << endl;
            }
        }
        Myfile.close();

       
    }
    void one_supplier_detail()
    {
        mylib obj, obj2;
        int array_Size = obj.countRecords("supplier.txt", 3, 0);
        Supplier* supplier = new Supplier[array_Size];
        ifstream Myfile("supplier.txt");
        string id;
        for (int i = 0; i < array_Size; i++)
        {
            getline(Myfile, supplier[i].name);

            getline(Myfile, id);
            supplier[i].id = stoi(id);

            getline(Myfile, supplier[i].phoneno);
        }
        Myfile.close();

        int array2_Size = countRecords("products.txt", 3, 0);
        Carpets* carpets = new Carpets[array2_Size];
        productarray(carpets, array2_Size);

        cout << "\t\t\t\t-------------------------------------------------" << endl;
        cout << "\t\t\t\t\tID " << "\t\tSuppliers Name\t\t" << endl;
        cout << "\t\t\t\t-------------------------------------------------" << endl;

        string name, phone_no;

        for (int i = 0; i < array_Size; i++)
        {
            cout << "\t\t\t\t\t" << supplier[i].id << "\t\t" << supplier[i].name << endl;
        }

        
        int supplier_id;
        cout << "Enter Supplier Id you want to check Report : ";
        cin >> supplier_id;
        
        
 
        array2_Size = countRecords("accountdata.txt", 8, 0);

        ifstream Myfile2("accountdata.txt");

        cout << "-------------------------------------------------------------------------------------------" << endl;
        cout << "\tsupplier_ID" << "\tDebit\t" << "\tCredit\t" << "\tBalance\t" << "\t Transaction Type" << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
        

   string partyname, acc_type, debit, credit, balance, cash_in_hand, tran_type;

       
        for (int i = 0; i < array2_Size; i++)
        {
            getline(Myfile2, partyname);
            getline(Myfile2, id);
            getline(Myfile2, acc_type);
            getline(Myfile2, debit);
            getline(Myfile2, credit);
            getline(Myfile2, balance);
            getline(Myfile2, cash_in_hand);
            getline(Myfile2, tran_type);

            if (supplier_id == stoi(id) && acc_type == "supplier")
            {
                cout << id << "\t\t";
                cout << debit << "\t\t" << credit << "\t\t" << balance << "\t\t";
                cout << tran_type<< endl;
            }
        }
        Myfile2.close();


    }
    void one_customer_detail()
    {

        //create supplier array
        mylib obj, obj2;
        int array_Size = obj.countRecords("customers.txt", 3, 0);
        Customer* customer = new Customer[array_Size];
        ifstream Myfile("customers.txt");
        string id;
        for (int i = 0; i < array_Size; i++)
        {
            getline(Myfile, customer[i].name);

            getline(Myfile, id);
            customer[i].id = stoi(id);

            getline(Myfile, customer[i].phoneno);
        }
        Myfile.close();

        int array2_Size = countRecords("customers.txt", 3, 0);
        Carpets* carpets = new Carpets[array2_Size];
        productarray(carpets, array2_Size);

        cout << "\t\t\t\t-------------------------------------------------" << endl;
        cout << "\t\t\t\t\tID " << "\t\tCustomer Name\t\t" << endl;
        cout << "\t\t\t\t-------------------------------------------------" << endl;

        int customer_id;
        string name, phone_no;

        for (int i = 0; i < array_Size; i++)
        {
            cout << "\t\t\t\t\t" << customer[i].id << "\t\t" << customer[i].name << endl;
        }
        cout << "\t\n Enter Customer id :\t";
        cin >> customer_id;

        array2_Size = countRecords("accountdata.txt", 8, 0);

        ifstream Myfile2("accountdata.txt");

        cout << "-------------------------------------------------------------------------------------------" << endl;
        cout << "\tCustomee_ID" << "\tDebit\t" << "\tCredit\t" << "\tBalance\t" << "\t Transaction Type" << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;


        string partyname, acc_type, debit, credit, balance, cash_in_hand, tran_type;


        for (int i = 0; i < array2_Size; i++)
        {
            getline(Myfile2, partyname);
            getline(Myfile2, id);
            getline(Myfile2, acc_type);
            getline(Myfile2, debit);
            getline(Myfile2, credit);
            getline(Myfile2, balance);
            getline(Myfile2, cash_in_hand);
            getline(Myfile2, tran_type);

            if (customer_id == stoi(id) && acc_type == "customer")
            {
                cout << id << "\t\t";
                cout << debit << "\t\t" << credit << "\t\t" << balance << "\t\t";
                cout << tran_type << endl;
            }
        }
        Myfile2.close();


    }
    void bank_account_report()
    {
        //create supplier array
        mylib obj, obj2;
        int array_Size = obj.countRecords("banks.txt", 3, 0);
        Bank* bank = new Bank[array_Size];
        ifstream Myfile("banks.txt");
        string id;
        for (int i = 0; i < array_Size; i++)
        {
            getline(Myfile, bank[i].name);

            getline(Myfile, id);
            bank[i].id = stoi(id);

            getline(Myfile, bank[i].phoneno);
        }
        Myfile.close();

        int array2_Size = countRecords("customers.txt", 3, 0);
        Carpets* carpets = new Carpets[array2_Size];
        productarray(carpets, array2_Size);

        cout << "\t\t\t\t-------------------------------------------------" << endl;
        cout << "\t\t\t\t\tID " << "\t\tBank Name\t\t" << endl;
        cout << "\t\t\t\t-------------------------------------------------" << endl;

        int bank_id;
        string name, phone_no;

        for (int i = 0; i < array_Size; i++)
        {
            cout << "\t\t\t\t\t" << bank[i].id << "\t\t" << bank[i].name << endl;
        }
        cout << "\t\n Enter Bank id :\t";
        cin >> bank_id;

        array2_Size = countRecords("accountdata.txt", 8, 0);

        ifstream Myfile2("accountdata.txt");

        cout << "-------------------------------------------------------------------------------------------" << endl;
        cout << "\tBank_ID" << "\tDebit\t" << "\tCredit\t" << "\tBalance\t" << "\t Transaction Type" << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;


        string partyname, acc_type, debit, credit, balance, cash_in_hand, tran_type;


        for (int i = 0; i < array2_Size; i++)
        {
            getline(Myfile2, partyname);
            getline(Myfile2, id);
            getline(Myfile2, acc_type);
            getline(Myfile2, debit);
            getline(Myfile2, credit);
            getline(Myfile2, balance);
            getline(Myfile2, cash_in_hand);
            getline(Myfile2, tran_type);

            if (bank_id == stoi(id) && acc_type == "bank")
            {
                cout << id << "\t\t";
                cout << debit << "\t\t" << credit << "\t\t" << balance << "\t\t";
                cout << tran_type << endl;
            }
        }
        Myfile2.close();
    }

};


//Freind Function
void productarray(Carpets* carpets, int size)
{
    //creating items array
    string rate;
    string id;
    ifstream Myfile2("products.txt");
    for (int i = 0; i < size; i++)
    {
        getline(Myfile2, carpets[i].name);

        getline(Myfile2, id);

        carpets[i].id = stoi(id);

        getline(Myfile2, rate);
        carpets[i].SalePrice = stoi(rate);
    }
    Myfile2.close();
}  

void handleUserInput(Manager* managers)
{
    int choice, subChoice,new_choice , new_sub_choice, FurtherChoice;

    cout << "Enter your choice:\n";
    for (int i = 0; i < 8; i++)
    {
        cout << "Press " << i + 1 << " for " << managers[i].name << " " << managers[i].position << endl;
    }
    cin >> choice;

    while (choice < 1 || choice > 8)
    {
        cout << "Invalid choice. Please try again.\n";
        for (int i = 0; i < 8; i++)
        {
            cout << "Press " << i + 1 << " for " << managers[i].name << " " << managers[i].position << endl;
        }
        cin >> choice;
    }

    system("CLS");
    cout << "\nYou have selected " << managers[choice - 1].name << ", " << managers[choice - 1].position << endl;

    cout << "\nPress 1 to feed New Record\n";
    cout << "Press 2 for Transactions \n";
    cout << "Press 3 for Reports\n";
    cout << "Press 4 to exit\n";

    cout << "Enter your choice: ";
    cin >> subChoice;

    while (subChoice != 4)
    {
        system("CLS");
        if (subChoice == 1)
        {
            system("CLS");
            cout << "You have selected feeding New Record\n";
            cout << "Press 1 to feed New Product (Carpet)" << endl;
            cout << "Press 2 to feed New Customer" << endl;
            cout << "Press 3 to feed New Supplier" << endl;
            cout << "Press 4 to feed New Expenses" << endl;
            cout << "Press 5 to feed New Banks" << endl;
            cout << "Press 6 to Go Back" << endl;

            cin >> FurtherChoice;
            while (FurtherChoice != 6)
            {
                if (FurtherChoice == 1)
                {
                    system("CLS");
                    system("Color E1");
                    add_new obj;
                    add_new_carpet();
                }
                else if (FurtherChoice == 2)
                {
                    system("CLS");
                    system("Color E1");
                    add_new obj;
                    obj.add_new_customer();
                }
                else if (FurtherChoice == 3)
                {
                    system("CLS");
                    system("Color E1");
                    add_new obj;
                    obj.add_new_supplier();
                }
                else if (FurtherChoice == 4)
                {
                    system("CLS");
                    system("Color E1");
                    add_new obj;
                    add_new_Expense();
                }
                else if (FurtherChoice == 5)
                {
                    system("CLS");
                    system("Color E1");
                    add_new obj;
                    obj.add_new_Bank();
                }
                else if (FurtherChoice == 6)
                {
                    system("CLS");
                    system("Color E1");
                    cout << "Back.....\n";
                }
                else
                {
                    system("CLS");
                    system("Color E1");
                    cout << "Invalid choice. Please try again.\n";
                }
                system("CLS");
                cout << "You have selected feeding New Record\n";
                cout << "Press 1 to feed New Product (Carpet)" << endl;
                cout << "Press 2 to feed New Customer" << endl;
                cout << "Press 3 to feed New Supplier" << endl;
                cout << "Press 4 to feed New Expenses" << endl;
                cout << "Press 5 to feed New Banks" << endl;
                cout << "Press 6 to Go Back" << endl;

                cin >> FurtherChoice;

            }
        }
        else if (subChoice == 2)
        {
            system("CLS");
            system("Color B1");
            cout << "You have selected Transactions \n";

            cout << "Press 1 for PURCHASE \n";
            cout << "Press 2 for SALES \n";
            cout << "Press 3 for Cash Transaction \n";
            cout << "Press 4 to Go Back \n";

            cin >> new_choice;
            while (new_choice != 4)
            {
                if (new_choice == 1)
                {
                    system("CLS");
                    system("Color E1");
                    cout << "You have selected PURCHASE \n";

                    Transactions obj3;
                    obj3.purchase();
                    cout << endl << endl;
                }
                else if (new_choice == 2)
                {
                    system("CLS");
                    system("Color E1");
                    cout << "You have selected SALES.\n";

                    Transactions obj3;
                    obj3.sales();
                    cout << endl << endl;
                }
                else if (new_choice == 3)
                {
                    system("CLS");
                    system("Color E1");
                    cout << "You have selected Cash Transactions\n";
                    cout << " \n  Press 1-for Cash from customer\n";
                    cout << " \n  Press 2-for Cash to Spplier\n";
                    cout << " \n  Press 3 to go back\n";
                    cin >> new_sub_choice;

                    while (new_sub_choice != 3)
                    {

                        if (new_sub_choice == 1)
                        {
                            cout << " \n You have selected cash from customer\n";
                            Transactions obj;
                            obj.cash_from_customer();
                        }
                        else if (new_sub_choice == 2)
                        {
                            cout << " \n  You have selected Cash to Supplier \n";
                            Transactions obj;
                            obj.cash_to_supplier();
                        }
                        else if (new_choice == 4)
                        {
                            system("CLS");
                            system("Color E1");
                            cout << "Back.....\n";

                        }
                        else
                        {
                            system("CLS");
                            system("Color E1");
                            cout << "Invalid choice. Please try again.\n";
                        }

                        system("CLS");
                        system("Color E1");
                        cout << "You have selected Cash Transactions\n";
                        cout << " \n  Press 1-for Cash from customer\n";
                        cout << " \n  Press 2-for Cash to Spplier\n";
                        cout << " \n  Press 3 to go back\n";

                        cin >> new_sub_choice;

                    }
                }

                else if (new_choice == 4)
                {
                    system("CLS");
                    system("Color E1");
                    cout << "Back.....\n";

                }

                else
                {
                    system("CLS");
                    system("Color E1");
                    cout << "Invalid choice. Please try again.\n";
                }
                system("CLS");
                system("Color E1");
                cout << "You have selected Transactions \n";

                cout << "Press 1 for PURCHASE \n";
                cout << "Press 2 for SALES \n";
                cout << "Press 3 for Cash Transaction \n";
                cout << "Press 4 to Go Back \n";

                cin >> new_choice;


            }
        }
        else if (subChoice == 3)
        {
            system("CLS");
            system("Color E1");
            cout << "You have selected Reports.\n";

            cout << "\nPress 1 to see sales stock report \n";
            cout << "Press 2 for one product Account report \n";
            cout << "Press 3 for Supplier Account report \n";
            cout << "Press 4 for Customer Account report\n";
            cout << "Press 5 for  Bank  Account report\n";
            cout << "Press 6 to go back\n";

            cout << "Enter your choice: ";
            cin >> FurtherChoice;
            reports obj;
            while (FurtherChoice != 6)
            {


                if (FurtherChoice == 1)
                {
                    system("CLS");
                    system("Color E1");
                    cout << "\n\nYou have selected sales stock report \n\n";
                    obj.sales_stock_report();
                }
                else if (FurtherChoice == 2)
                {
                    system("CLS");
                    system("Color E1");
                    cout << "\n\nYou have selected Prodct Account Report \n\n";
                    obj.one_product_detail();
                }
                else if (FurtherChoice == 3)
                {
                    system("CLS");
                    system("Color D1");
                    cout << "\n\nYou have Suppliers Account Report \n\n";
                    obj.one_supplier_detail();
                }
                else if (FurtherChoice == 4)
                {
                    system("CLS");
                    system("Color E1");
                    cout << "\n\nYou have selected Customers Account Report \n\n";
                    obj.one_customer_detail();
                }
                else if (FurtherChoice == 5)
                {
                    system("CLS");
                    system("Color E1");
                    cout << "\n\nYou have selected Bank Account Report \n\n";
                    obj.bank_account_report();
                }
                
                else if( FurtherChoice==6)
                {
                    system("CLS");
                    system("Color E1");
                    cout << "Back.....\n";
                }
                else
                {
                    system("CLS");
                    system("Color E1");
                    cout << "Invalid choice. Please try again.\n";
                }
                system("Color E1");
               cout << "\nPress 1 to see sales stock report \n";
               cout << "Press 2 for one product Account report \n";
               cout << "Press 3 for Supplier Account report \n";
               cout << "Press 4 for Customer Account report\n";
               cout << "Press 5 for  Bank  Account report\n";
               cout << "Press 6 to go back\n";

                cout << "Enter your choice: ";
                cin >> FurtherChoice;
            }

        }

        else if (subChoice == 4)
        {
        system("CLS");
        system("Color E1");
            cout << "exit.....\n";
        }
        else
        {
        system("CLS");
        system("Color E1");
        cout << "Invalid choice. Please try again.\n";
        }
        cout << "\nPress 1 to feed New Record \n";
        cout << "Press 2 for Transactions \n";
        cout << "Press 3 for Reports\n";
        cout << "Press 4 to exit\n";


        cout << "Enter your choice: ";
        cin >> subChoice;

    }
}

int main()
{
    system("CLS");
    system("Color E1");
 

    cout << "\t\t\t\t-------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\tTHE CARPET WORLD" << endl;
    cout << "\t\t\t\t-------------------------------------------------" << endl;

    Manager managers[8] =
    {
        {"Admin", "Administrator", 1},{"SM", "Sales Manager", 2},
        {"FM", "Financial Manager", 3},{"IM", "Inventory Manager", 4},
        {"CP", "Company Representative", 5},{"AS", "Assistant Supervisor", 6},
        {"PM", "Purchase Manager", 7},{"BR", "Bank Representative", 8}
    };

    handleUserInput(managers);





    system("CLS");
    cout << "\nExiting...\n";
    return 0;
}
