#include "include/Menu.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <cstring>
using namespace std;
bool Menu::areEqual(const char *str1, const char *str2)
{
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
void Menu::getInput(char *&str, istream &cin, int maxChar )
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
void Menu::UpdateStatistics(){
    statistics.SetTotalOrders(orderManager.lists.getSize()); 
    double revenue = 0 ;
    for (int i = 0 ; i < orderManager.lists.getSize();i++)
    {
        revenue += orderManager.lists.at(i).getTotalAfterDiscount();
    }

    statistics.SetTotalRevenue(revenue);
    // Tính chi phí
    double tAmountOut = 0 ;
    double tSalary= 0 ;
    // Tiền nhập sản phẩm , tiền lương , tiền mặt bằng 
    for (size_t i = 0; i < employeeManager.lists.getSize(); i++)
    {
        tAmountOut += employeeManager.lists.at(i).GetSalary(); 
        tSalary += employeeManager.lists.at(i).GetSalary(); 
    }
    // thiếu tiền nhập hàng 

    statistics.SetTotalAmountOut(tAmountOut) ;
    double tAmountIn = 0 ; 
    int numOrds = 0 ; 
    for (size_t i = 0; i < customerManager.lists.getSize(); i++)
    {
        for (size_t j = 0; j < customerManager.lists.at(i).getOrderHistory().getSize(); j++)
        {
            tAmountIn += customerManager.lists.at(i).getOrderHistory().at(j).getTotalAfterDiscount() ; 
            numOrds += 1 ;
        }
    }
    statistics.SetTotalAmountIn(tAmountIn) ; 
    statistics.SetNumberOfCustomers(customerManager.lists.getSize()) ;
    statistics.SetNumberOfSalesInvoices(numOrds); 
    statistics.SetNumberOfEmployees(employeeManager.lists.getSize()) ; 
    statistics.SetTotalPaymentsToEmployees(tSalary) ; 
    int tQuanitySold; 
    for (size_t i = 0; i < orderManager.lists.getSize(); i++)
    {
        tQuanitySold += orderManager.lists.at(i).getQuanityProduct(); 
    }
    statistics.SetTotalUnitsSold(tQuanitySold) ;
}
Menu::Menu()
{

    customerManager.GetData(customerManager.lists, "data/input_output/customer.txt");
    employeeManager.GetData(employeeManager.lists, "data/input_output/employee.txt");
    housewareManager.GetData(housewareManager.lists, "data/input_output/houseware.txt");
    foodManager.GetData(foodManager.lists, "data/input_output/food.txt");
    electricalproductManager.GetData(electricalproductManager.lists, "data/input_output/electricalproduct.txt");
    orderManager.GetData(orderManager.lists, "data/input_output/order.txt");
    for (size_t i = 0; i < customerManager.lists.getSize(); i++)
    {
        for (size_t j = 0; j < orderManager.lists.getSize(); j++)
        {
            if (customerManager.lists.at(i).GetCustomerID() == orderManager.lists.at(j).getCustomerID())
            {
                customerManager.lists.at(i).getOrderHistory().pushBack(orderManager.lists.at(j));
            }
        }
    }
    discountManager.GetData(discountManager.lists, "data/input_output/discount.txt");
}

Menu::~Menu()
{
    customerManager.SaveData(customerManager.lists, "data/input_output/customer.txt");
    // employeeManager.SaveData(employeeManager.lists, "data/input_output/employee.txt");
    orderManager.SaveData(orderManager.lists, "data/input_output/order.txt");
    // foodManager.SaveData(foodManager.lists, "data/input_output/food.txt");
    // electricalproductManager.SaveData(electricalproductManager.lists, "data/input_output/electricalproduct.txt");
    // housewareManager.SaveData(housewareManager.lists, "data/input_output/houseware.txt");
}
void Menu::displayCustomerMenu(Customer &cus, Order &order)
{
    std::cout  << BLUE << std::setfill('=') << std::setw(41)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout  <<BLUE <<"| |"<< BRIGHT_MAGENTA <<"          Customer Menu:           "<<BLUE<<"| |"<<std::endl;
    std::cout  << BLUE << std::setfill('=') << std::setw(41)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout << GREEN <<"|1|"<<YELLOW<< "View Personal Information\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|2|"<<YELLOW<< "Account Management\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|3|"<<YELLOW<<"Browse Products\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|4|" <<YELLOW<<"Purchase Orders\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN <<"|5|"<<YELLOW<< "Statistics\t\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|6|"<<YELLOW<< "View Order History\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|7|"<<YELLOW<<"View Available Discount\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|8|" <<YELLOW<<"Exit\t\t\t              "<<BLUE<<"| |"<<std::endl;
    std::cout  << BLUE << std::setfill('=') << std::setw(41)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout<< RESET;
    int choice;
    int vitri;
    std::cin >> choice;
    system("CLS");
    switch (choice)
    {
    case 1:
        cus.Display();
        break;
    case 2:
    {
        std::cout  << BLUE << std::setfill('=') << std::setw(46)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout  <<BLUE <<"| |"<< BRIGHT_MAGENTA <<"           Account Management:          "<<BLUE<<"| |"<<std::endl;
    std::cout  << BLUE << std::setfill('=') << std::setw(46)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout << BLUE <<"| |"<<YELLOW<< "Account ID:"<<cus.GetCustomerID()<<"\t   "     <<BLUE<<"| |"<<std::endl;
    std::cout << BLUE <<"| |"<<YELLOW<< "Please select the information to change:"<<BLUE<<"| |"<<std::endl;
    std::cout  << BLUE << std::setfill('=') << std::setw(46)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout << GREEN <<"|1|"<<YELLOW<< "Full Name\t\t\t           "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|2|"<<YELLOW<< "Gender\t\t\t           "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|3|"<<YELLOW<<"Age\t\t\t                   "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|4|" <<YELLOW<<"Day of Birth\t\t\t           "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN <<"|5|"<<YELLOW<< "Address\t\t\t           "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|6|"<<YELLOW<< "Phone Number\t\t\t           "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|7|"<<YELLOW<<"Email\t\t\t           "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|8|" <<YELLOW<<"Go back\t\t\t           "<<BLUE<<"| |"<<std::endl;
    std::cout  << BLUE << std::setfill('=') << std::setw(46)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout<< RESET;

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
            break;
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
       std::cout  << BLUE << std::setfill('=') << std::setw(41)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout  <<BLUE <<"| |"<< BRIGHT_MAGENTA <<"         Browse Products:          "<<BLUE<<"| |"<<std::endl;
    std::cout  << BLUE << std::setfill('=') << std::setw(41)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout << GREEN <<"|1|"<<YELLOW<< "View all products\t              "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|2|"<<YELLOW<< "Search for a product\t              "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|3|"<<YELLOW<<"Add a product to the cart\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|4|" <<YELLOW<<"Go back\t\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout  << BLUE << std::setfill('=') << std::setw(41)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout<< RESET;

        int browseChoice;
        std::cin >> browseChoice;
        system("CLS");
        switch (browseChoice)
        {
        case 1:
        {
            std::cout  << BLUE << std::setfill('=') << std::setw(41)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout  <<BLUE <<"| |"<< BRIGHT_MAGENTA <<"        Product Categories:        "<<BLUE<<"| |"<<std::endl;
     std::cout  << BLUE << std::setfill('=') << std::setw(41)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout << GREEN <<"|1|"<<YELLOW<< "View Houseware Products\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|2|"<<YELLOW<< "View Food Products\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|3|"<<YELLOW<<"View Electrical Products\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|4|" <<YELLOW<<"Go back\t\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout  << BLUE << std::setfill('=') << std::setw(41)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout<< RESET;

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
                displayCustomerMenu(cus, order);
                break;
            default:
                std::cout << "Invalid selection!" << endl;
                break;
                cout << "Enter 0 to return " << endl;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayCustomerMenu(cus, order);
            }
            break;
        }

        case 2:
        {
            std::cout << BRIGHT_MAGENTA << "Enter product name or product id " << endl;
            std::cout << RED << "1. Product name " << endl;
            std::cout << RED << "2. Product id " << endl
                      << RESET;
            int selection;
            char *name;
            int proid;
            bool productFound = false;
            cin >> selection;
            system("CLS");
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
                system("CLS");
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
            system("CLS");
            if (is == 0)
                return displayCustomerMenu(cus, order);

            break;
        }
        case 3:
        {
            std::cout << BRIGHT_MAGENTA << "Enter Product name or Product ID to get to cash" << endl;
            std::cout << RED << "1. Product name " << endl;
            std::cout << RED << "2. Product id " << endl
                      << RESET;
            int selection;
            char *name;
            int proid;
            bool productFound = false;
            cin >> selection;
            system("CLS");
            if (selection == 1)
            {
                int sl;
                std::cout << "Enter product name  : ";
                getInput(name, cin);
                for (int i = 0; i < foodManager.lists.getSize(); i++)
                {
                    if (name == foodManager.lists.at(i).getTenSanPham())
                    {
                        cout << "Product name : " << name << endl;
                        cout << "Quantity of product remaining : " << foodManager.lists.at(i).getSoLuongTonKho() << endl;
                        std::cout << "Enter quanity =  ";
                        cin >> sl;
                        std::cout << "Do you want to buy " << sl << " " << name << "(Y/N)" << endl;
                        char ch = getch();
                        if (ch == 'Y' || ch == 'y')
                        {
                            // Mua ;
                            cus.BuyProduct(order, foodManager.lists.at(i), sl);
                            cout << "Enter 0 to return " << endl;
                            int is;
                            cin >> is;
                            if (is == 0)
                                return displayCustomerMenu(cus, order);
                        }
                        productFound = true;
                        break;
                    }
                }
                for (int i = 0; i < electricalproductManager.lists.getSize(); i++)
                {
                    if (name == electricalproductManager.lists.at(i).getTenSanPham())
                    {
                        cout << "Product name : " << name << endl;
                        cout << "Quantity of product remaining : " << electricalproductManager.lists.at(i).getSoLuongTonKho() << endl;
                        std::cout << "Enter quanity =  ";
                        cin >> sl;
                        std::cout << "Do you want to buy " << sl << " " << name << "(Y/N)" << endl;
                        char ch = getch();
                        if (ch == 'Y' || ch == 'y')
                        {
                            // Mua ;
                            cus.BuyProduct(order, electricalproductManager.lists.at(i), sl);
                            cout << "Enter 0 to return " << endl;
                            int is;
                            cin >> is;
                            if (is == 0)
                                return displayCustomerMenu(cus, order);
                        }
                        productFound = true;
                        break;
                    }
                }
                for (int i = 0; i < housewareManager.lists.getSize(); i++)
                {
                    if (name == housewareManager.lists.at(i).getTenSanPham())
                    {
                        cout << "Product name : " << name << endl;
                        cout << "Quantity of product remaining : " << housewareManager.lists.at(i).getSoLuongTonKho() << endl;
                        std::cout << "Enter quanity =  ";
                        cin >> sl;
                        std::cout << "Do you want to buy " << sl << " " << name << "(Y/N)" << endl;
                        char ch = getch();
                        if (ch == 'Y' || ch == 'y')
                        {

                            cus.BuyProduct(order, housewareManager.lists.at(i), sl);
                            cout << "Enter 0 to return " << endl;
                            int is;
                            cin >> is;
                            if (is == 0)
                                return displayCustomerMenu(cus, order);
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
                        cout << "Product name : " << foodManager.lists.at(i).getMaSanPham() << endl;
                        cout << "Quantity of product remaining : " << foodManager.lists.at(i).getSoLuongTonKho() << endl;
                        std::cout << "Enter quanity =  ";
                        cin >> sl;
                        std::cout << "Do you want to buy " << sl << " " << foodManager.lists.at(i).getTenSanPham() << "(Y/N)" << endl;
                        char ch = getch();
                        if (ch == 'Y' || ch == 'y')
                        {
                            cus.BuyProduct(order, foodManager.lists.at(i), sl);
                            cout << "Enter 0 to return " << endl;
                            int is;
                            cin >> is;
                            if (is == 0)
                                return displayCustomerMenu(cus, order);
                        }
                        productFound = true;
                        break;
                    }
                }
                for (int i = 0; i < electricalproductManager.lists.getSize(); i++)
                {
                    if (proid == electricalproductManager.lists.at(i).getMaSanPham())
                    {
                        cout << "Product name : " << electricalproductManager.lists.at(i).getTenSanPham() << endl;
                        cout << "Quantity of product remaining : " << electricalproductManager.lists.at(i).getSoLuongTonKho() << endl;
                        std::cout << "Enter quanity =  ";
                        cin >> sl;
                        std::cout << "Do you want to buy " << sl << " " << electricalproductManager.lists.at(i).getTenSanPham() << "(Y/N)" << endl;
                        char ch = getch();
                        if (ch == 'Y' || ch == 'y')
                        {
                            cus.BuyProduct(order, electricalproductManager.lists.at(i), sl);
                        }
                        cout << "Enter 0 to return " << endl;
                        int is;
                        cin >> is;
                        system("CLS");
                        if (is == 0)
                            return displayCustomerMenu(cus, order);
                        productFound = true;
                        break;
                    }
                }
                for (int i = 0; i < housewareManager.lists.getSize(); i++)
                {
                    if (proid == housewareManager.lists.at(i).getMaSanPham())
                    {
                        cout << "Product name : " << housewareManager.lists.at(i).getTenSanPham() << endl;
                        cout << "Quantity of product remaining : " << housewareManager.lists.at(i).getSoLuongTonKho() << endl;
                        std::cout << "Enter quanity =  ";
                        cin >> sl;
                        std::cout << "Do you want to buy " << sl << " " << housewareManager.lists.at(i).getTenSanPham() << "(Y/N)" << endl;
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
                            return displayCustomerMenu(cus, order);
                        productFound = true;
                        break;
                    }
                }
            }
            cout << "Enter 0 to return " << endl;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayCustomerMenu(cus, order);
            if (productFound == false)
            {
                std::cout << "Can not found!";
            }
            break;
        }

        case 4:
            displayCustomerMenu(cus, order);
            break;
        default:
            std::cout << "Invalid selection!" << endl;
            break;
        }

        break;
    }
    case 4:
    {
        order.setTotalAfterDiscount(order.CalculateTotalAmount());
        order.Display(std::cout, cus.GetFullName());
        std::cout << "Do you want to apply discount (Y/N)" << std::endl;
        char ch1 = getch();
        if (ch1 == 'Y' || ch1 == 'y')
        {
            std::cout << "Available Discounts:" << std::endl;
            for (size_t j = 0; j < cus.GetDiscounts().getSize(); j++)
            {
                std::cout << j + 1 << ". "
                          << "Discount ID : " << cus.GetDiscounts().at(j).getDiscountID() << "|";
                std::cout << "Discount percentage :  " << cus.GetDiscounts().at(j).getPercentage() << std::endl;
            }
            int discountChoice;
            std::cout << "Enter the number of the discount you want to apply: ";
            std::cin >> discountChoice;

            if (discountChoice > 0 && discountChoice <= static_cast<int>(cus.GetDiscounts().getSize()))
            {
                order.ApplyDiscount(cus.GetDiscounts().at(discountChoice - 1));
                order.Display(std::cout, cus.GetFullName());
            }
            else
            {
                std::cout << "Invalid discount choice." << std::endl;
            }
        }
        cout << "Enter 0 to confirm " << endl;
        int is;
        cin >> is;
        if (is == 0)
        {
            order.HoanThanh = true;
            cout << "Do you want to export bill (Y/N)" << endl;
            char ch = getch();
            if (ch == 'Y' || ch == 'y')
            {
                int length = snprintf(nullptr, 0, "data/Order_list/Cus%d/%d_order.txt", order.getCustomerID(), order.GetOrderID());
                char *filename = new char[length + 1];
                snprintf(filename, length + 1, "data/Order_list/Cus%d/%d_order.txt", order.getCustomerID(), order.GetOrderID());
                cout << "File path " << filename << endl;
                order.Display_file(filename, cus.GetFullName());
            }
            Order::setNumberOrder();
            Order newOrder(Order::getNumberOrder(), cus.GetCustomerID());
            cus.add_to_orders(newOrder);

            return displayCustomerMenu(cus, cus.Last_Order());
            return;
        }
        break;
    }

    case 5:
    {
        cus.UpdateStatistics();
        cus.ViewStatistics();
        break;
    }

    case 6:
    {
        cus.Show_Orders_History(std::cout);
        cout << "Enter 0 to return " << endl;
        int is;
        cin >> is;
        system("CLS");
        if (is == 0)
            return displayCustomerMenu(cus, order);
        break;
    }
    case 7:
    {
        if (cus.GetDiscounts().isEmpty())
        {
            std::cout << "No discount available " << std::endl;
        }
        else
            std::cout << cus.GetDiscounts();
        std::cout << "Do you want to add new discount(Y/N)" << std::endl;
        char ch;
        cin >> ch;
        if (ch == 'Y' || ch == 'y')
        {
            while (1)
            {
                std::cout << "Enter your code : ";
                char *code;
                Menu::getInput(code, cin);
                bool found = false;
                for (size_t i = 0; i < discountManager.lists.getSize(); i++)
                {
                    if (areEqual(code, discountManager.lists.at(i).getCouponCode()))
                    {
                        found = true;
                        cus.AddDiscount(discountManager.lists.at(i));
                        break;
                    }
                }
                if (!found)
                {
                    std::cout << "Can't found" << std::endl;
                }
                std::cout << "Do you want to add more discount " << std::endl;
                char ch3;
                std::cin >> ch3;
                if (ch3 == 'Y' || ch3 == 'y')
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
        }

        cout << "Enter 0 to return " << endl;
        int is;
        cin >> is;
        if (is == 0)
            return displayCustomerMenu(cus, order);
        break;
    }
    default:
        cout << "Invalid value. Please try again" << endl;

        break;
    }
}
void Menu::displayEmployeeMenu(Employee &employee)
{
    std::cout << BLUE << "==============================\n";
    std::cout << "    " << BRIGHT_MAGENTA << "Employee Menu" << BLUE << "       \n";
    std::cout << "==============================\n";
    std::cout << "1. " << YELLOW << "View Personal Information\n";
    std::cout << "2. " << YELLOW << "Account Management\n";
    std::cout << "3. " << YELLOW << "Manage Inventory\n";
    std::cout << "4. " << BLUE << "Statistics\n";
    std::cout << "5. " << RED << "Exit\n";
    std::cout << "==============================\n"
              << RESET;
    int choice;
    std::cin >> choice;
    system("CLS");
    switch (choice)
    {
    case 1:
        employee.Display();
        break;
    case 2:
    {
        std::cout << BLUE << "==============================\n";
        std::cout << " " << BRIGHT_MAGENTA << "Account Management" << BLUE << "   \n";
        std::cout << "==============================\n";
        std::cout << "Account ID: " << employee.GetEmployeeID() << "\n";
        std::cout << "Please select the information you need to change:\n";
        std::cout << "1. " << YELLOW << "Full Name\n";
        std::cout << "2. " << YELLOW << "Gender\n";
        std::cout << "3. " << YELLOW << "Age\n";
        std::cout << "4. " << YELLOW << "Day of Birth\n";
        std::cout << "5. " << YELLOW << "Address\n";
        std::cout << "6. " << YELLOW << "Phone Number\n";
        std::cout << "7. " << YELLOW << "Email\n";
        std::cout << "8. " << BLUE << "Go back\n";
        std::cout << "==============================\n"
                  << RESET;
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
            employee.SetFullName(fullName);
            break;
        }
        case 2:
        {
            std::cout << "Enter your new gender :";
            char *gender;
            getInput(gender, std::cin);
            employee.SetGender(gender);
            break;
        }
        case 3:
        {
            int age;
            std::cout << "Enter your new age : ";
            std::cin >> age;
            employee.SetAge(age);
            break;
        }
        // ... (other cases)
        case 5:
        {
            std::cout << "Enter your new address";
            char *address;
            getInput(address, std::cin);
            employee.SetAddress(address);
            break;
        }
        case 6:
        {
            std::cout << "Enter your new phone number : ";
            char *phonenumber;
            getInput(phonenumber, std::cin);
            employee.SetPhoneNumber(phonenumber);
            break;
        }
        case 7:
        {
            std::cout << "Enter your new email : ";
            char *email;
            getInput(email, std::cin);
            employee.SetEmail(email);
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
        std::cout << BLUE << "==============================\n";
        std::cout << "  " << BRIGHT_MAGENTA << "Product Categories" << BLUE << "   \n";
        std::cout << "==============================\n";
        std::cout << "1. " << YELLOW << "View Houseware Products\n";
        std::cout << "2. " << YELLOW << "View Food Products\n";
        std::cout << "3. " << YELLOW << "View Electrical Products\n";
        std::cout << "4. " << BLUE << "Go back\n";
        std::cout << "==============================\n"
                  << RESET;

        int viewChoice;
        std::cin >> viewChoice;

        switch (viewChoice)
        {
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
                displayEmployeeMenu(employee);
                break;
            default:
                std::cout << "Invalid selection!" << endl;
                break;
                cout << "Enter 0 to return " << endl;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayEmployeeMenu(employee);
            }
            break;
        }
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
}
//!
void Menu::displayManagerMenu()
{
   std::cout  << BLUE << std::setfill('=') << std::setw(41)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout  <<BLUE <<"| |"<< BRIGHT_MAGENTA <<"            Manager Menu:          "<<BLUE<<"| |"<<std::endl;
     std::cout  << BLUE << std::setfill('=') << std::setw(41)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout << GREEN <<"|1|"<<YELLOW<< "View lists\t\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|2|"<<YELLOW<< "Edit Information\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|3|"<<YELLOW<<"Add object\t\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|4|" <<YELLOW<<"Delete object\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|5|" <<YELLOW<<"Statistics\t\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|8|" <<YELLOW<<"Exit\t\t\t              "<<BLUE<<"| |"<<std::endl;
    std::cout  << BLUE << std::setfill('=') << std::setw(41)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout<< RESET;

    int choice;
    std::cin >> choice;
    system("CLS");
    switch (choice)
    {
    case 1:
    {
        std::cout << BLUE << "==============================\n";
        std::cout << "    " << BRIGHT_MAGENTA << "MENU OPTIONS" << BLUE << "        \n";
        std::cout << "==============================\n";
        std::cout << "1. " << YELLOW << "View employee list\n";
        std::cout << "2. " << YELLOW << "View customer list\n";
        std::cout << "3. " << YELLOW << "View product list\n";
        std::cout << "4. " << RED << "View order list\n";
        std::cout << "5. " << BLUE << "Turn back\n";
        std::cout << "==============================\n"
                  << RESET;
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
            std::cout << BLUE << "==============================\n";
            std::cout << "  " << BRIGHT_MAGENTA << "Product Categories" << BLUE << "   \n";
            std::cout << "==============================\n";
            std::cout << "1. " << YELLOW << "View Houseware Products\n";
            std::cout << "2. " << YELLOW << "View Food Products\n";
            std::cout << "3. " << YELLOW << "View Electrical Products\n";
            std::cout << "4. " << BLUE << "Go back\n";
            std::cout << "==============================\n"
                      << RESET;

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
                displayManagerMenu();
                break;
            default:
                std::cout << "Invalid selection!" << endl;
                break;
                cout << "Enter 0 to return " << endl;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
            }
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
        std::cout << BRIGHT_MAGENTA << "=== Select object you want to add ===" << RESET << endl;
        std::cout << YELLOW << "1. Employee" << RESET << endl;
        std::cout << GREEN << "2. Customer" << RESET << endl;
        std::cout << BLUE << "3. Product" << RESET << endl;
        std::cout << CYAN << "4. Discount" << RESET << endl;
        std::cout << BLUE << "5. Delivery" << RESET << endl;
        std::cout << RED << "6. Turn back " << RESET << endl;
        std::cout << BRIGHT_MAGENTA << "-------------------------------------" << RESET << endl;

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
            int numCustomer;
            std::cout << "Enter the number of Customer to add: ";
            std::cin >> numCustomer;
            Customer *customers = new Customer[numCustomer];

            for (int i = 0; i < numCustomer; i++)
            {
                customers[i].GetInformation();

                customerManager.AddToLists(customers[i]);
            }

            delete[] customers;
            break;
        }
        case 3:
        {
            std::cout << BLUE << "==============================\n";
            std::cout << "  " << BRIGHT_MAGENTA << "Product Categories" << BLUE << "   \n";
            std::cout << "==============================\n";
            std::cout << "1. " << YELLOW << "Add Houseware Products\n";
            std::cout << "2. " << YELLOW << "Add Food Products\n";
            std::cout << "3. " << YELLOW << "Add Electrical Products\n";
            std::cout << "4. " << BLUE << "Go back\n";
            std::cout << "==============================\n"
                      << RESET;

            int selection;
            std::cin >> selection;
            switch (selection)
            {
            case 1:
            {
                std::cout << "Enter number houseware product you want to add  : ";
                int numHouseware;
                std::cin >> numHouseware;
                Houseware *houseware = new Houseware[numHouseware];
                for (size_t i = 0; i < numHouseware; i++)
                {
                    cin >> houseware[i];
                    housewareManager.AddToLists(houseware[i]);
                }
                delete[] houseware;
                break;
            }
            case 2:
            {
                std::cout << "Enter number food product you want to add  : ";
                int numfood;
                std::cin >> numfood;
                Food *food = new Food[numfood];
                for (size_t i = 0; i < numfood; i++)
                {
                    cin >> food[i];
                    foodManager.AddToLists(food[i]);
                }
                delete[] food;
                break;
            }
            case 3:
            {
                std::cout << "Enter number electrical product you want to add  : ";
                int numelectricalproduct;
                std::cin >> numelectricalproduct;
                ElectricalProduct *electricalproducts = new ElectricalProduct[numelectricalproduct];
                for (size_t i = 0; i < numelectricalproduct; i++)
                {
                    cin >> electricalproducts[i];
                    electricalproductManager.AddToLists(electricalproducts[i]);
                }
                delete[] electricalproducts;
                break;
            }
            case 4:
            {
                return displayManagerMenu();
                break;
            }
            default:
                std::cout << "Invalid selection ";
                break;
            }
            break;
        case 4:
        {
            // Discount
            std::cout << "Enter number of Discount you want to add ";
            int numDiscount;
            std::cin >> numDiscount;
            Discount *discount = new Discount[numDiscount];
            for (size_t i = 0; i < numDiscount; i++)
            {
                std::cin >> discount[i];
                discountManager.AddToLists(discount[i]);
            }
            delete[] discount;
            break;
        }
        default:
            std::cout << "Invalid selection";
            break;
        }
        break;
        }
    case 4:
    {
        std::cout << "Which object you want to delete " << std::endl;
        std::cout << "1. Customer " << std::endl;
        std::cout << "2. Employee " << std::endl;
        std::cout << "3. Product" << std::endl;
        std::cout << "4. Discount " << std::endl;
        int selection;
        std::cin >> selection;
        switch (selection)
        {
        case 1:
        {
            std::cout << "Enter customer ID you want to delete" << std::endl;
            int id;
            std::cin >> id;
            for (size_t i = 0; i < customerManager.lists.getSize(); i++)
            {
                if (id == customerManager.lists.at(i).GetCustomerID())
                {
                    customerManager.lists.remove(i);
                    break;
                }
            }
            break;
        }
        case 2:
        {
            std::cout << "Enter employee ID you want to delete" << std::endl;
            int id;
            std::cin >> id;
            for (size_t i = 0; i < employeeManager.lists.getSize(); i++)
            {
                if (id == employeeManager.lists.at(i).GetEmployeeID())
                {
                    employeeManager.lists.remove(i);
                    break;
                }
            }
            break;
        }
        case 3:
        {
            std::cout << BLUE << "==============================\n";
            std::cout << "  " << BRIGHT_MAGENTA << "Product Categories" << BLUE << "   \n";
            std::cout << "==============================\n";
            std::cout << "1. " << YELLOW << "Delete Houseware Products\n";
            std::cout << "2. " << YELLOW << "Delete Food Products\n";
            std::cout << "3. " << YELLOW << "Delete Electrical Products\n";
            std::cout << "4. " << BLUE << "Go back\n";
            std::cout << "==============================\n";
            int choice;
            std::cin >> choice;
            switch (choice)
            {
            case 1:
            {
                std::cout << "Enter HousewareID you want to delete" << std::endl;
                int id;
                std::cin >> id;
                for (size_t i = 0; i < housewareManager.lists.getSize(); i++)
                {
                    if (id == housewareManager.lists.at(i).getMaSanPham())
                    {
                        housewareManager.lists.remove(i);
                        break;
                    }
                }
                break;
            }
            case 2:
            {
                std::cout << "Enter Food ID you want to delete" << std::endl;
                int id;
                std::cin >> id;
                for (size_t i = 0; i < foodManager.lists.getSize(); i++)
                {
                    if (id == foodManager.lists.at(i).getMaSanPham())
                    {
                        foodManager.lists.remove(i);
                        break;
                    }
                }
                break;
            }
            case 3:
            {
                std::cout << "Enter electrical product ID you want to delete" << std::endl;
                int id;
                std::cin >> id;
                for (size_t i = 0; i < electricalproductManager.lists.getSize(); i++)
                {
                    if (id == electricalproductManager.lists.at(i).getMaSanPham())
                    {
                        electricalproductManager.lists.remove(i);
                        break;
                    }
                }
                break;
            }
            case 4:
            {
                std::cout << "Enter Discount ID you want to delete" << std::endl;
                int id;
                std::cin >> id;
                for (size_t i = 0; i < discountManager.lists.getSize(); i++)
                {
                    if (id == discountManager.lists.at(i).getDiscountID())
                    {
                        discountManager.lists.remove(i);
                        break;
                    }
                }
                break;
            }
            case 5:
            {
                return displayManagerMenu();
                break;
            }
            default:
                std::cout << "Invalid selection ";
                break;
            }
            break;
        }
        default:
            break;
        }
    }
    break;
    case 5:
        UpdateStatistics();
        statistics.DisplaySuperMarketStatistics(); 

        break;
    case 7:
    {
        return run();
        break;
    }
    case 8:
    {
        Menu::~Menu();
        break;
    }
    default:
        std::cout << "Invalid value. Please try again" << endl;
        break;
    }
    }
}

void Menu::run()
{
    bool exit = false;
    int userType;

    std::cout  << BLUE << std::setfill('=') << std::setw(41)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout  <<BLUE <<"| |"<< BRIGHT_MAGENTA <<"       Select the user type:       "<<BLUE<<"| |"<<std::endl;
    std::cout  << BLUE << setfill('=') << setw(40)<< "=" <<std::endl;
    std::cout <<std::setfill(' ');
    std::cout << GREEN <<"|1|"<<YELLOW<< "Customer\t\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|2|"<<YELLOW<< "Manager\t\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|3|"<<YELLOW<<"Employee\t\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout << GREEN << "|4|" <<YELLOW<<"Turn back\t\t\t      "<<BLUE<<"| |"<<std::endl;
    std::cout  << BLUE << std::setfill('=') << std::setw(41)<< "=" <<std::endl;
    std::cout << std::setfill(' ');
    std::cout<< RESET;

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
            system("CLS");
            for (size_t i = 0; i < customerManager.lists.getSize(); i++)
            {
                if (customerid == customerManager.lists.at(i).GetCustomerID())
                {
                    validID = true;
                    Customer &cus = customerManager.lists.at(i);
                    if (cus.getOrderHistory().isEmpty())
                    {
                        Order ord(Order::getNumberOrder(), customerid);
                        cus.getOrderHistory().pushBack(ord);
                    }

                    Order &order = cus.Last_Order();
                    if (cus.Last_Order().HoanThanh)
                    {
                        Order newOrder(Order::getNumberOrder(), customerid);
                        cus.add_to_orders(newOrder);
                        displayCustomerMenu(cus, cus.Last_Order());
                        break;
                        return;
                    }
                    displayCustomerMenu(cus, order);
                    int choice;
                    std::cout << "Choose a number to continue or 0 to exit: ";
                    std::cin >> choice;
                    system("CLS");
                    if (choice == 0)
                    {
                        break;
                    }
                    else
                    {
                        return run();
                    }
                }
            }

            if (validID)
            {
                break;
            }
            else
            {
                std::cout << "Invalid ID! Do you want to try again? (Y/N): ";
                char tryAgain;
                std::cin >> tryAgain;
                system("CLS");
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
        // int maxChar = 100;
        // char temp[maxChar];
        // char* password;
        // std::cout << "Enter Manager Password: ";
        // getInput(password, std::cin);

        // if (areEqual(password,key))
        // {
            system("CLS");
            displayManagerMenu();
            int choice;
            std::cout << "Choose a number to continue or 0 to exit: ";
            std::cin >> choice;

            if (choice == 0)
            {
                break;
            }
            else
            {
                return run();
            }
        }
        // else
        // {
        //     std::cout << "Invalid password!" << std::endl;
        // }
        break;
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
                    Employee &employee = employeeManager.lists.at(i);
                    displayEmployeeMenu(employee);
                    int choice;
                    std::cout << "Choose a number to continue or 0 to exit: ";
                    std::cin >> choice;
                    system("CLS");
                    if (choice == 0)
                    {
                        break;
                    }
                    else
                    {

                        return run();
                    }
                }
            }

            std::cout << "Invalid Employee ID! Do you want to try again? (Y/N): ";
            char tryAgain;
            std::cin >> tryAgain;
            system("CLS");
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
        std::cout << "Invalid user type!" << std::endl;
        break;
    }
}
