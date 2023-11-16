#include "include/Menu.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
using namespace std;
bool Menu::areEqual(const char *str1, const char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
        {
            return false;
        }
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
}
// Đọc có dấu cách và  stop khi xuống dòng
void Menu::getInput(char *&str, istream &cin, int maxChar)
{
    char temp[maxChar];
    std::cin.ignore();
    char ch = ' ';
    int index = 0;
    while (ch != '\n' && index < maxChar - 1)
    {
        ch = std::cin.get();
        temp[index++] = ch;
    }
    temp[index - 1] = '\0';
    str = new char[index];
    for (int i = 0; i < index; ++i)
    {
        str[i] = temp[i];
    }
}
void Menu::readAttributeTillDelimiter(char *&attribute, std::istream &file)
{
    int MAX_LENGTH = 256;
    int index = 0;
    attribute = new char[MAX_LENGTH];
    char ch;
    bool done = false;

    while (file.get(ch))
    {
        if (ch == ',' || ch == '\n')
        {
            done = true;
            if (ch == '\n')
                file.unget();
            break;
        }
        if (index < MAX_LENGTH - 1)
        {
            attribute[index++] = ch;
        }
        else
        {
            break;
        }
    }
    attribute[index] = '\0';
}

Menu::Menu()
{

    customerManager.GetData(customerManager.lists, "data/input_output/customer.txt");
    employeeManager.GetData(employeeManager.lists, "data/input_output/employee.txt");
    housewareManager.GetData(housewareManager.lists, "data/input_output/houseware.txt");
    foodManager.GetData(foodManager.lists, "data/input_output/food.txt");
    electricalproductManager.GetData(electricalproductManager.lists, "data/input_output/electricalproduct.txt");
}
Menu::~Menu()
{
    // customerManager.SaveData(customerManager.lists, "data/input_output/customer.txt");
    // employeeManager.SaveData(employeeManager.lists, "data/input_output/employee.txt");
}
void Menu::displayCustomerMenu(int customerid, Order& order)
{
    std::cout << "Customer Menu " << endl;
    std::cout << "1. View Personal Information " << endl;
    std::cout << "2. Account Management" << endl;
    std::cout << "3. Browse Products" << endl;
    std::cout << "4. Purchase Orders" << endl;
    std::cout << "5. Statistics" << endl;
    std::cout << "6. View Order History" << endl;
    std::cout << "7. Exit" << endl;
    int choice;
    int vitri;
    std::cin >> choice;
    system("CLS");
    for (size_t i = 0; i < customerManager.lists.getSize(); i++)
    {
        if (customerManager.lists.at(i).GetCustomerID() == customerid)
        {
            vitri = i;
            break;
        }
    }
    
    Customer &cus = customerManager.lists.at(vitri);
    switch (choice)
    {
    case 1:
        cus.Display();
        break;
    case 2:
    {
        std::cout << "Account Management" << endl;
        std::cout << "Account ID" << customerid << endl;
        std::cout << "Please select the information you need to change" << endl;
        std::cout << "1. Full Name." << endl;
        std::cout << "2. Gender." << endl;
        std::cout << "3. Age." << endl;
        std::cout << "4. Day of birth." << endl;
        std::cout << "5. Address." << endl;
        std::cout << "6. Phone number." << endl;
        std::cout << "7. Email." << endl;
        std::cout << "8. Go back" << endl;
        int selection;
        std::cin >> selection;
        system("CLS");
        switch (selection)
        {
        case 1:
        {
            std::cout << "Enter your new full name : ";
            char *fullName;
            getInput(fullName, std::cin);
            cus.SetFullName(fullName);
            break;
        }
        case 2:
        {
            std::cout << "Enter your new gender :";
            char *gender;
            getInput(gender, std::cin);
            cus.SetGender(gender);
            break;
        }
        case 3:
        {
            int age;
            std::cout << "Enter your new age : ";
            std::cin >> age;
            cus.SetAge(age);
            break;
        }
        // ... (other cases)
        case 5:
        {
            std::cout << "Enter your new address";
            char *address;
            getInput(address, std::cin);
            cus.SetAddress(address);
            break; // <-- Add this break statement
        }
        case 6:
        {
            std::cout << "Enter your new phone number : ";
            char *phonenumber;
            getInput(phonenumber, std::cin);
            cus.SetPhoneNumber(phonenumber);
            break;
        }
        case 7:
        {
            std::cout << "Enter your new email : ";
            char *email;
            getInput(email, std::cin);
            cus.SetEmail(email);
            break;
        }
        case 8:
        {
            return;
            break;
        }

        default:
        {
            std::cout << "Invalid selection!";
            break;
        }
        }

        break;
    }
    case 3:
    {
        std::cout << "Browse Products" << endl;
        std::cout << "1. View all products" << endl;
        std::cout << "2. Search for a product" << endl;
        std::cout << "3. Add a product to the cart" << endl;
        std::cout << "4. Go back" << endl;

        int browseChoice;
        std::cin >> browseChoice;

        switch (browseChoice)
        {
        case 1:
        {
            std::cout << "1. View Houseware Products" << endl;
            std::cout << "2. View Food Products" << endl;
            std::cout << "3. View Electrical Products" << endl;
            std::cout << "4. Go back" << endl;

            int viewChoice;
            std::cin >> viewChoice;

            switch (viewChoice)
            {
            case 1:
                housewareManager.Display(housewareManager.lists);
                break;
            case 2:
                foodManager.Display(foodManager.lists);
                break;
            case 3:
                electricalproductManager.Display(electricalproductManager.lists);
                break;
            case 4:
                displayCustomerMenu(customerid,order);
                break;
            default:
                std::cout << "Invalid selection!" << endl;
                break;
                cout << "Enter 0 to return " << endl;
                int is;
                cin >> is;
                if (is == 0)
                    return displayCustomerMenu(customerid,order);
            }
            break;
        }

        case 2:
        {
            std::cout << "Enter product name or product id " << endl;
            std::cout << "1. Product name " << endl;
            std::cout << "2. Product id " << endl;
            int selection;
            char *name;
            int proid;
            bool productFound = false;
            cin >> selection;
            if (selection == 1)
            {
                std::cout << "Enter product name  : ";
                getInput(name, cin);
                for (int i = 0; i < foodManager.lists.getSize(); i++)
                {
                    if (name == foodManager.lists.at(i).getTenSanPham())
                    {
                        foodManager.lists.at(i).Display();
                        productFound = true;
                        break;
                    }
                }
                for (int i = 0; i < electricalproductManager.lists.getSize(); i++)
                {
                    if (name == electricalproductManager.lists.at(i).getTenSanPham())
                    {
                        electricalproductManager.lists.at(i).Display();
                        productFound = true;
                        break;
                    }
                }
                for (int i = 0; i < housewareManager.lists.getSize(); i++)
                {
                    if (name == housewareManager.lists.at(i).getTenSanPham())
                    {
                        housewareManager.lists.at(i).Display();
                        productFound = true;
                        break;
                    }
                }
            }
            else if (selection == 2)
            {
                std::cout << "Enter product id : ";
                cin >> proid;
                for (int i = 0; i < foodManager.lists.getSize(); i++)
                {
                    if (proid == foodManager.lists.at(i).getMaSanPham())
                    {
                        foodManager.lists.at(i).Display();
                        productFound = true;
                        break;
                    }
                }
                for (int i = 0; i < electricalproductManager.lists.getSize(); i++)
                {
                    if (proid == electricalproductManager.lists.at(i).getMaSanPham())
                    {
                        electricalproductManager.lists.at(i).Display();
                        productFound = true;
                        break;
                    }
                }
                for (int i = 0; i < housewareManager.lists.getSize(); i++)
                {
                    if (proid == housewareManager.lists.at(i).getMaSanPham())
                    {
                        housewareManager.lists.at(i).Display();
                        productFound = true;
                        break;
                    }
                }
            }
            cout << "Enter 0 to return " << endl;
            int is;
            cin >> is;
            if (is == 0)
                return displayCustomerMenu(customerid,order);

            break;
        }
        case 3:
        {
            std::cout << "Enter Product name or Product ID to get to cash" << endl;
            std::cout << "1. Product name " << endl;
            std::cout << "2. Product id " << endl;
            int selection;
            char *name;
            int proid;
            bool productFound = false;
            cin >> selection;
            if (selection == 1)
            {
                int sl;
                std::cout << "Enter product name  : ";
                getInput(name, cin);
                for (int i = 0; i < foodManager.lists.getSize(); i++)
                {
                    if (name == foodManager.lists.at(i).getTenSanPham())
                    {
                        std::cout << "Enter quanity =  ";
                        cin >> sl;
                        std::cout << "Do you want to buy " << name << "(Y/N)" << endl;
                        char ch = getch();
                        if (ch == 'Y' || ch == 'y')
                        {
                            // Mua ;
                            cus.BuyProduct(order, foodManager.lists.at(i), sl);
                            cout << "Enter 0 to return " << endl;
                            int is;
                            cin >> is;
                            if (is == 0)
                                return displayCustomerMenu(customerid,order);
                        }
                        productFound = true;
                        break;
                    }
                }
                for (int i = 0; i < electricalproductManager.lists.getSize(); i++)
                {
                    if (name == electricalproductManager.lists.at(i).getTenSanPham())
                    {
                        std::cout << "Enter quanity =  ";
                        cin >> sl;
                        std::cout << "Do you want to buy " << name << "(Y/N)" << endl;
                        char ch = getch();
                        if (ch == 'Y' || ch == 'y')
                        {
                            // Mua ;
                            cus.BuyProduct(order, electricalproductManager.lists.at(i), sl);
                            cout << "Enter 0 to return " << endl;
                            int is;
                            cin >> is;
                            if (is == 0)
                                return displayCustomerMenu(customerid,order);
                        }
                        productFound = true;
                        break;
                    }
                }
                for (int i = 0; i < housewareManager.lists.getSize(); i++)
                {
                    if (name == housewareManager.lists.at(i).getTenSanPham())
                    {
                        std::cout << "Enter quanity =  ";
                        cin >> sl;
                        std::cout << "Do you want to buy " << name << "(Y/N)" << endl;
                        char ch = getch();
                        if (ch == 'Y' || ch == 'y')
                        {
                            // Mua ;
                            cus.BuyProduct(order, housewareManager.lists.at(i), sl);
                            cout << "Enter 0 to return " << endl;
                            int is;
                            cin >> is;
                            if (is == 0)
                                return displayCustomerMenu(customerid,order);
                        }
                        productFound = true;
                        break;
                    }
                }
            }
            else if (selection == 2)
            {
                int sl;
                std::cout << "Enter product id : ";
                cin >> proid;
                for (int i = 0; i < foodManager.lists.getSize(); i++)
                {
                    if (proid == foodManager.lists.at(i).getMaSanPham())
                    {
                        std::cout << "Enter quanity =  ";
                        cin >> sl;
                        std::cout << "Do you want to buy " << foodManager.lists.at(i).getTenSanPham() << "(Y/N)" << endl;
                        char ch = getch();
                        if (ch == 'Y' || ch == 'y')
                        {
                            // Mua ;

                            cus.BuyProduct(order, foodManager.lists.at(i), sl);
                            cout << "Enter 0 to return " << endl;
                            int is;
                            cin >> is;
                            if (is == 0)
                                return displayCustomerMenu(customerid,order);
                        }
                        productFound = true;
                        break;
                    }
                }
                for (int i = 0; i < electricalproductManager.lists.getSize(); i++)
                {
                    if (proid == electricalproductManager.lists.at(i).getMaSanPham())
                    {
                        std::cout << "Enter quanity =  ";
                        cin >> sl;
                        std::cout << "Do you want to buy " << foodManager.lists.at(i).getTenSanPham() << "(Y/N)" << endl;
                        char ch = getch();
                        if (ch == 'Y' || ch == 'y')
                        {
                            // Mua ;
                            cus.BuyProduct(order, electricalproductManager.lists.at(i), sl);
                        }
                        cout << "Enter 0 to return " << endl;
                        int is;
                        cin >> is;
                        if (is == 0)
                            return displayCustomerMenu(customerid,order);
                        productFound = true;
                        break;
                    }
                }
                for (int i = 0; i < housewareManager.lists.getSize(); i++)
                {
                    if (proid == housewareManager.lists.at(i).getMaSanPham())
                    {
                        std::cout << "Enter quanity =  ";
                        cin >> sl;
                        std::cout << "Do you want to buy " << housewareManager.lists.at(i).getTenSanPham() << "(Y/N)" << endl;
                        char ch = getch();
                        if (ch == 'Y' || ch == 'y')
                        {
                            // Mua ;
                            cus.BuyProduct(order, housewareManager.lists.at(i), sl);
                        }
                        cout << "Enter 0 to return " << endl;
                        int is;
                        cin >> is;
                        if (is == 0)
                            return displayCustomerMenu(customerid,order);
                        productFound = true;
                        break;
                    }
                }
            }
            cout << "Enter 0 to return " << endl;
            int is;
            cin >> is;
            if (is == 0)
                return displayCustomerMenu(customerid,order);
            if (productFound == false)
            {
                std::cout << "Can not found!";
            }
            break;
        }

        case 4:
            displayCustomerMenu(customerid,order);
            break;
        default:
            std::cout << "Invalid selection!" << endl;
            break;
        }

        break;
    }
    case 4:
    {
        order.Display(std::cout) ;
        order.HoanThanh = true;
        cus.add_to_orders(order);
        cout << "Enter 0 to return " << endl;
        int is;
        cin >> is;
        if (is == 0)
            return displayCustomerMenu(customerid,order);
        break;
    }

    case 5:
        break;
    case 6:
    {
        cus.Last_Order().Display(std::cout);
        break;
    }
    default:
        std::cout << "Invalid value. Please try again" << endl;

        break;
    }
}
void Menu::displayEmployeeMenu(int employeeid)
{
    std::cout << "Employee Menu" << endl;
    std::cout << "1. View Personal Information" << endl;
    std::cout << "2. Account Management" << endl;
    std::cout << "3. Manage Inventory" << endl;
    std::cout << "4. View Orders" << endl;
    std::cout << "5. Confirm Orders" << endl;
    std::cout << "6. Statistics" << endl;
    std::cout << "7. Exit" << endl;
    int choice;
    std::cin >> choice;
    system("CLS");
    switch (choice)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    default:
        std::cout << "Invalid value. Please try again" << endl;
        break;
    }
}
//!
void Menu::displayManagerMenu()
{
    std::cout << "Manager Menu" << endl;
    std::cout << "1. View lists" << endl;
    std::cout << "2. Edit Information" << endl;
    std::cout << "3. Add object " << endl;
    std::cout << "4. Delete object" << endl;
    std::cout << " 5. Statistics" << endl;
    std::cout << " 6. Save data" << endl;
    std::cout << " 7. View Activity Log" << endl;
    std::cout << " 8. Exit" << endl;

    int choice;
    std::cin >> choice;
    system("CLS");
    switch (choice)
    {
    case 1:
    {
        std::cout << "1. View employee list" << endl;
        std::cout << "2. View customer list" << endl;
        std::cout << "3. View product list" << endl;
        std::cout << "4. View order list" << endl;
        std::cout << "5. Turn back" << endl;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        {
            employeeManager.Display(employeeManager.lists);
            std::cout << "Do you want to export file  (Y/N)" << endl;
            char ch;
            std::cin >> ch;
            if (ch == 'Y' || ch == 'y')
            {
                employeeManager.ShowLists_file(employeeManager.lists, "data/employee_lists.txt");
            }

            break;
        }
        case 2:
        {
            customerManager.Display(customerManager.lists);
            std::cout << "Do you want to export file (Y/N)" << endl;
            char ch;
            std::cin >> ch;
            if (ch == 'Y' || ch == 'y')
            {
                customerManager.ShowLists_file(customerManager.lists, "data/customer_lists.txt");
            }

            break;
        }
        case 3:
        {
            // Show product
            break;
        }
        case 4:
        {
            // Show order
            break;
        }
        case 5:
        {
            return;
            break;
        }
        }
        break;
    }
    case 2:
        // Xử lý Edit Information
        break;
    case 3:
    {
        std::cout << "Select object you want to add" << endl;
        std::cout << "1. Employee" << endl;
        std::cout << "2. Customer" << endl;
        std::cout << "3. Product" << endl;
        std::cout << "4. Discount" << endl;
        std::cout << "5. Delivery" << endl;
        std::cout << "6. Turn back " << endl;
        int choose;
        std::cin >> choose;
        system("CLS");
        switch (choose)
        {
        case 1:
        {
            int numEmployees;
            std::cout << "Enter the number of employees to add: ";
            std::cin >> numEmployees;
            Employee *employees = new Employee[numEmployees];

            for (int i = 0; i < numEmployees; i++)
            {
                employees[i].GetInformation();

                employeeManager.AddToLists(employees[i]);
            }

            delete[] employees;
            break;
        }
        case 2:
        {

            break;
        }
        default:
            break;
        }
        break;
    }
    case 4:
        // Xử lý Delete object
        break;
    case 5:
        // Xử lý Statistics
        break;
    case 6:
        // Xử lý Save data
        break;
    case 7:
        // Thoát
        break;
    default:
        std::cout << "Invalid value. Please try again" << endl;
        break;
    }
}

//!
void Menu::run()
{
    bool exit = false;
    int userType;
    std::cout << "Select the user type : " << std::endl;
    std::cout << "1. Customer" << std::endl;
    std::cout << "2. Manager" << std::endl;
    std::cout << "3. Employee" << std::endl;
    std::cout << "4. Turn back" << std::endl;
    std::cin >> userType;
    system("CLS");
    switch (userType)
    {
    case 1:
    {
        bool validID = false;
        while (true)
        {
            int customerid;
            cout << "Enter your CustomerID: ";
            std::cin >> customerid;
            for (size_t i = 0; i < customerManager.lists.getSize(); i++)
            {
                if (customerid == customerManager.lists.at(i).GetCustomerID())
                {
                    validID = true;
                    Order order ;
                    displayCustomerMenu(customerid,order);
                    int choice;
                    std::cout << "Choose a number to continue or 0 to exit: ";
                    std::cin >> choice;
                    if (choice == 0)
                    {
                        break; // Exit the function if 0 is entered
                    }
                }
            }
            if (validID)
            {
                break; // Break the loop if the ID is valid
            }
            else
            {
                std::cout << "Invalid ID! Do you want to try again? (Y/N): ";
                char tryAgain;
                std::cin >> tryAgain;
                if (tryAgain != 'Y' && tryAgain != 'y')
                {
                    return;
                }
            }
        }
        break;
    }
    case 2:
    {
        int maxChar = 100;
        char temp[maxChar];
        char *password; // assuming a maximum password length
        std::cout << "Enter Manager Password: ";
        getInput(password, std::cin);
        if (areEqual(password, key))
        {
            system("CLS");
            displayManagerMenu();
            int choice;
            std::cout << "Choose a number to continue or 0 to exit: ";
            std::cin >> choice;

            if (choice == 0)
            {
                break;
            }
            break;
        }
        else
        {
            std::cout << "Invalid password!" << endl;
        }
        break;
    }

    case 3:
    {
        while (true)
        {
            int employeeid;
            std::cout << "Enter your Employee ID: ";
            std::cin >> employeeid;
            for (size_t i = 0; i < employeeManager.lists.getSize(); i++)
            {
                if (employeeid == employeeManager.lists.at(i).GetEmployeeID())
                {
                    system("CLS");
                    displayEmployeeMenu(employeeid);
                    int choice;
                    std::cout << "Choose a number to continue or 0 to exit: ";
                    std::cin >> choice;

                    if (choice == 0)
                    {
                        break;
                    }
                }
            }
            std::cout << "Invalid Employee ID! Do you want to try again? (Y/N): ";
            char tryAgain;
            std::cin >> tryAgain;
            if (tryAgain != 'Y' && tryAgain != 'y')
            {
                return;
            }
        }
        break;
    }
    case 4:
        exit = true;
        break;
    default:
        std::cout << "Invalid user type!" << endl;
        break;
    }
}