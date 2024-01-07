#include "Menu.h"
#include <iostream>
#include <conio.h>
#include <algorithm>
using namespace std;
void Menu::createDiscountPointvsTime()
{
    // Tạo discount theo thời gian 10%
    Time startTime(11, 0);
    Time endTime(20, 0);
    time.updateRealTime();
    Discount discount(10);
    discount.setAvailable(1);
    if (time >= startTime && time <= endTime)
    {
        for (size_t i = 0; i < customerManager.lists.getSize(); i++)
        {
            customerManager.lists.at(i).AddDiscount(discount);
        }
        discountManager.AddToLists(discount);
    }
    // Tạo discount theo điểm
    //  Discount trên 100 điểm
    Discount discount100(5);
    discount100.setType(POINT_BASED);
    Discount discount1000(10);
    discount1000.setType(POINT_BASED);
    discount100.setAvailable(1);
    discount1000.setAvailable(1);
    discountManager.AddToLists(discount100);
    discountManager.AddToLists(discount1000);
    for (size_t i = 0; i < customerManager.lists.getSize(); i++)
    {
        if (customerManager.lists.at(i).GetPoint() >= 100)
            customerManager.lists.at(i).AddDiscount(discount100);
        if (customerManager.lists.at(i).GetPoint() >= 1000)
        {
            customerManager.lists.at(i).AddDiscount(discount1000);
        }
    }
}
bool Menu::areEqual(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
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
void Menu::getInput(char *&str, std::istream &cin, int maxChar)
{
    char temp[maxChar];
    cin >> std::ws; // Loại bỏ khoảng trắng và ký tự newline còn tồn đọng

    char ch = ' ';
    int index = 0;
    while (ch != '\n' && index < maxChar - 1)
    {
        ch = cin.get();
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
void Menu::UpdateStatistics(Time &start, Time &end)
{
    std::cout << "Start time : " << start << std::endl;
    std::cout << "End time :" << end << std::endl;
    int tQuanitySold = 0;
    double tAmountIn = 0;
    double tAmountOut = 0;
    double tSalary = 0;
    int numOrds = 0;
    int numCustomer = 0; // Khởi tạo giá trị ban đầu
    int numEmployees = 0;
    for (size_t i = 0; i < orderManager.lists.getSize(); i++)
    {
        if (orderManager.lists.at(i).GetOrderTime() >= start && orderManager.lists.at(i).GetOrderTime() <= end)
        {
            // Số hóa đơn
            numOrds++;
            // Tiền vào, khách mua hàng
            tAmountIn += orderManager.lists.at(i).getTotalAfterDiscount();
            // Số lượng sản phẩm
            tQuanitySold += orderManager.lists.at(i).getQuanityProduct();
            // Xem id cua khach hang là orderManager.lists.at(i).getCustomerID() ;
            bool isUnique = true;
            for (size_t j = i + 1; j < orderManager.lists.getSize(); j++)
            {
                if (orderManager.lists.at(j).GetOrderTime() >= start && orderManager.lists.at(j).GetOrderTime() <= end)
                {
                    if (orderManager.lists.at(i).getCustomerID() == orderManager.lists.at(j).getCustomerID())
                    {
                        isUnique = false;
                        break; // Thoát ngay khi tìm thấy khách hàng trùng
                    }
                }
            }
            if (isUnique)
            {
                numCustomer++;
            }
        }
    }

    // Tính lương nhân viên
    for (size_t i = 0; i < employeeManager.lists.getSize(); i++)
    {
        if (employeeManager.lists.at(i).GetEndDay() >= start && employeeManager.lists.at(i).GetStartDay() <= end)
        {
            // Tính số ngày làm việc trong khoảng thời gian
            Time employeeStart = std::max(employeeManager.lists.at(i).GetStartDay(), start);
            Time employeeEnd = std::min(employeeManager.lists.at(i).GetEndDay(), end);
            int workingDays = employeeEnd - employeeStart;
            numEmployees++;
            // Tính lương dựa trên số ngày làm việc và lương theo ngày
            tSalary += workingDays * employeeManager.lists.at(i).GetSalary();
        }
    }
    // Tính tiền nhập hàng trong khoảng thời gian
    int tImport = 0;
    for (size_t i = 0; i < housewareManager.lists.getSize(); i++)
    {
        if (housewareManager.lists.at(i).getNgayNhapHang() <= end && housewareManager.lists.at(i).getNgayNhapHang() >= start)
        {
            tImport += housewareManager.lists.at(i).GetImportPrice()*housewareManager.lists.at(i).getSoLuongNhapHang();
        }
    }
    for (size_t i = 0; i < foodManager.lists.getSize(); i++)
    {
        if (foodManager.lists.at(i).getNgayNhapHang() <= end && foodManager.lists.at(i).getNgayNhapHang() >= start)
        {
            tImport += housewareManager.lists.at(i).GetImportPrice()*housewareManager.lists.at(i).getSoLuongNhapHang();
        }
    }
    for (size_t i = 0; i < electricalproductManager.lists.getSize(); i++)
    {
        if (electricalproductManager.lists.at(i).getNgayNhapHang() <= end && electricalproductManager.lists.at(i).getNgayNhapHang() >= start)
        {
            tImport += electricalproductManager.lists.at(i).GetImportPrice()*electricalproductManager.lists.at(i).getSoLuongNhapHang();
        }
    }
    statistics.SetNumberOfSalesInvoices(numOrds);
    statistics.SetTotalUnitsSold(tQuanitySold);
    statistics.SetTotalAmountOut(tImport + tSalary);
    statistics.setImportCost(tImport);
    statistics.SetTotalPaymentsToEmployees(tSalary);
    statistics.SetTotalProfit(tAmountIn - tImport - tSalary);
    statistics.SetTotalAmountIn(tAmountIn);
    statistics.SetTotalRevenue(tAmountIn);
    statistics.SetNumberOfCustomers(numCustomer);
    statistics.SetNumberOfEmployees(numEmployees);
    
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
    Time currentTime ;
    for (size_t i = 0; i < employeeManager.lists.getSize(); i++)
    {
        employeeManager.lists.at(i).calculateAge();
        if(currentTime < employeeManager.lists.at(i).GetStartDay() || currentTime > employeeManager.lists.at(i).GetEndDay())
        employeeManager.lists.at(i).SetIsWorking(false);
    }
    for (size_t i = 0; i < customerManager.lists.getSize(); i++)
    {
        customerManager.lists.at(i).calculateAge();
    }
}

Menu::~Menu()
{
    customerManager.SaveData(customerManager.lists, "data/input_output/customer.txt");
    employeeManager.SaveData(employeeManager.lists, "data/input_output/employee.txt");
    orderManager.SaveData(orderManager.lists, "data/input_output/order.txt");
    foodManager.SaveData(foodManager.lists, "data/input_output/food.txt");
    electricalproductManager.SaveData(electricalproductManager.lists, "data/input_output/electricalproduct.txt");
    housewareManager.SaveData(housewareManager.lists, "data/input_output/houseware.txt");
}
void Menu::displayCustomerMenu(Customer &cus, Order &order)
{
    std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "          Customer Menu:           " << BLUE << "| |" << std::endl;
    std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << GREEN << "|1|" << YELLOW << "View Personal Information\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|2|" << YELLOW << "Account Management\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|3|" << YELLOW << "Browse Products\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|4|" << YELLOW << "Purchase Orders\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|5|" << YELLOW << "Statistics\t\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|6|" << YELLOW << "View Order History\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|7|" << YELLOW << "View Available Discount\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|8|" << YELLOW << "Exit\t\t\t              " << BLUE << "| |" << std::endl;
    std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << RESET;
    int choice;
    int vitri;
    std::cin >> choice;
    system("CLS");
    switch (choice)
    {
    case 1:
        cus.Display();
        std::cout << YELLOW << "Enter 0 to return " << endl;
        std::cout << RESET;
        int is;
        cin >> is;
        system("CLS");
        if (is == 0)
            return displayCustomerMenu(cus, order);
        break;
    case 2:
    {
        std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "           Account Management:          " << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << BLUE << "| |" << YELLOW << "Account ID:" << std::setw(29) << left << cus.GetCustomerID() << BLUE << "| |" << std::endl;
        std::cout << BLUE << "| |" << YELLOW << "Please select the information to change:" << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << GREEN << "|1|" << YELLOW << "Full Name\t\t\t           " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|2|" << YELLOW << "Gender\t\t\t           " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|3|" << YELLOW << "Age\t\t\t                   " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|4|" << YELLOW << "Day of Birth\t\t\t           " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|5|" << YELLOW << "Address\t\t\t           " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|6|" << YELLOW << "Phone Number\t\t\t           " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|7|" << YELLOW << "Email\t\t\t           " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|8|" << YELLOW << "Go back\t\t\t           " << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << RESET;
        int selection;
        std::cin >> selection;
        system("CLS");
        switch (selection)
        {
        case 1:
        {
            std::cout << CYAN << "Enter your new full name : ";
            std::cout << RESET;
            char *fullName;
            getInput(fullName, std::cin);
            cus.SetFullName(fullName);
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayCustomerMenu(cus, order);
            break;
        }
        case 2:
        {
            std::cout << CYAN << "Enter your new gender :";
            std::cout << RESET;
            char *gender;
            getInput(gender, std::cin);
            cus.SetGender(gender);
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayCustomerMenu(cus, order);
            break;
        }
        case 3:
        {
            int age;
            std::cout << CYAN << "Enter your new age : ";
            std::cout << RESET;
            std::cin >> age;
            cus.SetAge(age);
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayCustomerMenu(cus, order);
            break;
        }
        case 4 : 
        {
            std::cout << CYAN << "Enter your new DOB";
            std::cout << RESET;
            Date dob ;
            std::cin >> dob ;
            cus.SetDayOfBirth(dob);
             std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayCustomerMenu(cus, order);
            break;
        }
        case 5:
        {
            std::cout << CYAN << "Enter your new address";
            std::cout << RESET;
            char *address;
            getInput(address, std::cin);
            cus.SetAddress(address);
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayCustomerMenu(cus, order);
            break;
        }
        case 6:
        {
            std::cout << CYAN << "Enter your new phone number : ";
            std::cout << RESET;
            char *phonenumber;
            getInput(phonenumber, std::cin);
            cus.SetPhoneNumber(phonenumber);
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayCustomerMenu(cus, order);
            break;
        }
        case 7:
        {
            std::cout << CYAN << "Enter your new email : ";
            std::cout << RESET;
            char *email;
            getInput(email, std::cin);
            cus.SetEmail(email);
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayCustomerMenu(cus, order);
            break;
        }
        case 8:
        {
            return displayCustomerMenu(cus,order);
            break;
        }

        default:
        {
            std::cout << RED << "Invalid selection!" << endl;
            std::cout << RESET;
            return displayCustomerMenu(cus, order);
            break;
        }
        }

        break;
    }
    case 3:
    {
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "         Browse Products:          " << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << GREEN << "|1|" << YELLOW << "View all products\t              " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|2|" << YELLOW << "Search for a product\t              " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|3|" << YELLOW << "Add a product to the cart\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|4|" << YELLOW << "Go back\t\t\t      " << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << RESET;
        int browseChoice;
        std::cin >> browseChoice;
        system("CLS");
        switch (browseChoice)
        {
        case 1:
        {
            std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "        Product Categories:        " << BLUE << "| |" << std::endl;
            std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << GREEN << "|1|" << YELLOW << "View Houseware Products\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|2|" << YELLOW << "View Food Products\t\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|3|" << YELLOW << "View Electrical Products\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|4|" << YELLOW << "Go back\t\t\t      " << BLUE << "| |" << std::endl;
            std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << RESET;

            int viewChoice;
            std::cin >> viewChoice;

            switch (viewChoice)
            {
            case 1:
            {
                housewareManager.Display(housewareManager.lists);
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayCustomerMenu(cus, order);
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
            }
            case 2:
            {
                foodManager.Display(foodManager.lists);
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayCustomerMenu(cus, order);
                break;
            }
            case 3:
            {
                electricalproductManager.Display(electricalproductManager.lists);
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayCustomerMenu(cus, order);
                break;
            }
            case 4:
            {
                displayCustomerMenu(cus, order);
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayCustomerMenu(cus, order);
                break;
            }
            default:
            {
                std::cout << RED << "Invalid selection!" << endl;
                std::cout << RESET;
                break;
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayCustomerMenu(cus, order);
            }
            break;
            }
        }
        case 2:
        {
            std::cout << BLUE << std::setfill('=') << std::setw(54) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "Enter Product name or Product ID:\t\t   " << BLUE << "| |" << std::endl;
            std::cout << BLUE << setfill('=') << setw(54) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << GREEN << "|1|" << YELLOW << "Product name\t\t\t\t           " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|2|" << YELLOW << "Product id\t\t\t\t           " << BLUE << "| |" << std::endl;
            std::cout << BLUE << std::setfill('=') << std::setw(54) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << RESET;
            int selection;
            char *name;
            int proid;
            bool productFound = false;
            cin >> selection;
            system("CLS");
            if (selection == 1)
            {
                std::cout << CYAN << "Enter product name  : ";
                std::cout << RESET;
                getInput(name, cin);
                for (int i = 0; i < foodManager.lists.getSize(); i++)
                {
                    if (Menu::areEqual(name,foodManager.lists.at(i).getTenSanPham()))
                    {
                        foodManager.lists.at(i).Display();
                        productFound = true;
                        break;
                    }
                }
                for (int i = 0; i < electricalproductManager.lists.getSize(); i++)
                {
                    if (Menu::areEqual(name,electricalproductManager.lists.at(i).getTenSanPham()))
                    {
                        electricalproductManager.lists.at(i).Display();
                        productFound = true;
                        break;
                    }
                }
                for (int i = 0; i < housewareManager.lists.getSize(); i++)
                {
                    if (Menu::areEqual(name,housewareManager.lists.at(i).getTenSanPham()))
                    {
                        housewareManager.lists.at(i).Display();
                        productFound = true;
                        break;
                    }
                }
            }
            else if (selection == 2)
            {
                std::cout << CYAN << "Enter product id : ";
                std::cout << RESET;
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
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayCustomerMenu(cus, order);

            break;
        }
        case 3:
        {
            std::cout << BLUE << std::setfill('=') << std::setw(55) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "Enter Product name or Product ID  to get to cash:" << BLUE << "| |" << std::endl;
            std::cout << BLUE << setfill('=') << setw(55) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << GREEN << "|1|" << YELLOW << "Product name\t\t\t\t            " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|2|" << YELLOW << "Product id\t\t\t\t            " << BLUE << "| |" << std::endl;
            std::cout << BLUE << std::setfill('=') << std::setw(55) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << RESET;
            int selection;
            char *name;
            int proid;
            bool productFound = false;
            cin >> selection;
            system("CLS");
            if (selection == 1)
            {
                int sl;
                std::cout << CYAN << "Enter product name  : ";
                std::cout << RESET;
                getInput(name, std::cin);
                for (int i = 0; i < foodManager.lists.getSize(); i++)
                {
                    if (Menu::areEqual(name,foodManager
                    .lists.at(i).getTenSanPham()))
                    {
                        std::cout << GREEN << "Product name : " << name << std::endl;
                        std::cout << RESET;
                        std::cout << GREEN << "Quantity of product remaining : " << foodManager.lists.at(i).getSoLuongTonKho() << std::endl;
                        std::cout << RESET;
                        std::cout << CYAN << "Enter quanity =  ";
                        std::cout << RESET;
                        cin >> sl;
                        system("CLS");
                        if (sl > foodManager.lists.at(i).getSoLuongTonKho())
                        {
                            std::cout << "Not enough quanity in stock " << std::endl;
                        }
                        else
                        {
                            std::cout << "Do you want to buy " << sl << " " << name << "(Y/N)" << endl;
                            char ch = getch();
                            if (ch == 'Y' || ch == 'y')
                            {
                                // Mua ;
                                cus.BuyProduct(order, foodManager.lists.at(i), sl);
                                std::cout << YELLOW << "Enter 0 to return " << endl;
                                std::cout << RESET;
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
                for (int i = 0; i < electricalproductManager.lists.getSize(); i++)
                {
                    if (Menu::areEqual(name,electricalproductManager.lists.at(i).getTenSanPham()))
                    {
                        cout << "Product name : " << name << endl;
                        cout << "Quantity of product remaining : " << electricalproductManager.lists.at(i).getSoLuongTonKho() << endl;
                        std::cout << CYAN << "Enter quanity =  ";
                        std::cout << RESET;
                        cin >> sl;
                        if (sl > electricalproductManager.lists.at(i).getSoLuongTonKho())
                        {
                            std::cout << RED << "Not enough quanity in stock " << std::endl;
                            std::cout << RESET;
                        }
                        else
                        {
                            std::cout << CYAN << "Do you want to buy " << sl << " " << name << CYAN << "(Y/N)" << std::endl;
                            char ch = getch();
                            if (ch == 'Y' || ch == 'y')
                            {
                                // Mua ;
                                cus.BuyProduct(order, electricalproductManager.lists.at(i), sl);
                                std::cout << YELLOW << "Enter 0 to return " << endl;
                                std::cout << RESET;
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
                for (int i = 0; i < housewareManager.lists.getSize(); i++)
                {
                    if (Menu::areEqual(name,housewareManager.lists.at(i).getTenSanPham()))
                    {
                        std::cout << GREEN << "Product name : " << name << std::endl;
                        std::cout << GREEN << "Quantity of product remaining : " << housewareManager.lists.at(i).getSoLuongTonKho() << std::endl;
                        std::cout << RESET;
                        std::cout << RESET;
                        cin >> sl;
                        system("CLS");
                        if (sl > housewareManager.lists.at(i).getSoLuongTonKho())
                        {
                            std::cout << RED << "Not enough quanity in stock " << std::endl;
                            std::cout << RESET;
                        }
                        else
                        {
                            std::cout << CYAN << "Product name : " << name << std::endl;
                            std::cout << CYAN << "Quantity of product remaining : " << housewareManager.lists.at(i).getSoLuongTonKho() << std::endl;
                            std::cout << RESET;
                            char ch = getch();
                            if (ch == 'Y' || ch == 'y')
                            {

                                cus.BuyProduct(order, housewareManager.lists.at(i), sl);
                                std::cout << YELLOW << "Enter 0 to return " << endl;
                                std::cout << RESET;
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
            }
            else if (selection == 2)
            {
                int sl;
                std::cout << CYAN << "Enter product id : ";
                std::cout << RESET;
                cin >> proid;
                system("CLS");
                for (int i = 0; i < foodManager.lists.getSize(); i++)
                {
                    if (proid == foodManager.lists.at(i).getMaSanPham())
                    {
                        std::cout<<GREEN << "Product name : " << foodManager.lists.at(i).getTenSanPham() << std::endl;
                        cout << "Quantity of product remaining : " << foodManager.lists.at(i).getSoLuongTonKho() << endl;
                        std::cout << CYAN << "Enter quanity =  ";
                        std::cout << RESET;
                        cin >> sl;
                        if (sl > foodManager.lists.at(i).getSoLuongTonKho())
                        {
                            std::cout << RED << "Not enough quanity in stock " << std::endl;
                        }
                        {
                            std::cout << CYAN << "Do you want to buy " << sl << " " << name << CYAN << "(Y/N)" << endl;
                            std::cout << RESET;
                            char ch = getch();
                            system("CLS");
                            if (ch == 'Y' || ch == 'y')
                            {
                                cus.BuyProduct(order, foodManager.lists.at(i), sl);
                                std::cout << YELLOW << "Enter 0 to return " << endl;
                                std::cout << RESET;
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
                for (int i = 0; i < electricalproductManager.lists.getSize(); i++)
                {
                    if (proid == electricalproductManager.lists.at(i).getMaSanPham())
                    {
                        std::cout << GREEN << "Product name : " << electricalproductManager.lists.at(i).getTenSanPham() << std::endl;
                        std::cout << GREEN << "Quantity of product remaining : " << electricalproductManager.lists.at(i).getSoLuongTonKho() << std::endl;
                        std::cout << RESET;
                        std::cout << CYAN << "Enter quanity =  ";
                        std::cout << RESET;
                        cin >> sl;
                        if (sl > electricalproductManager.lists.at(i).getSoLuongTonKho())
                        {
                            std::cout << RED << "Not enough quanity in stock " << std::endl;
                            std::cout << RESET;
                        }
                        else
                        {
                            std::cout << CYAN << "Do you want to buy " << sl << " " << electricalproductManager.lists.at(i).getTenSanPham() << CYAN << "(Y/N)" << std::endl;
                            std::cout << RESET;
                            char ch = getch();
                            if (ch == 'Y' || ch == 'y')
                            {
                                cus.BuyProduct(order, electricalproductManager.lists.at(i), sl);
                            }
                            std::cout << YELLOW << "Enter 0 to return " << endl;
                            std::cout << RESET;
                            int is;
                            cin >> is;
                            system("CLS");
                            if (is == 0)
                                return displayCustomerMenu(cus, order);
                            productFound = true;
                            break;
                        }
                    }
                }
                for (int i = 0; i < housewareManager.lists.getSize(); i++)
                {
                    if (proid == housewareManager.lists.at(i).getMaSanPham())
                    {
                        std::cout << GREEN << "Product name : " << housewareManager.lists.at(i).getTenSanPham() << std::endl;
                        std::cout << GREEN << "Quantity of product remaining : " << housewareManager.lists.at(i).getSoLuongTonKho() << std::endl;
                        std::cout << CYAN << "Enter quanity =  ";
                        std::cout << RESET;
                        cin >> sl;
                        system("CLS");
                        if (sl > housewareManager.lists.at(i).getSoLuongTonKho())
                        {
                            std::cout << RED << "Not enough quanity in stock " << std::endl;
                            std::cout << RESET;
                        }
                        else
                        {
                            std::cout << CYAN << "Do you want to buy " << sl << " " << housewareManager.lists.at(i).getTenSanPham() << CYAN << "(Y/N)" << std::endl;
                            char ch = getch();
                            if (ch == 'Y' || ch == 'y')
                            {
                                // Mua ;
                                cus.BuyProduct(order, housewareManager.lists.at(i), sl);
                            }
                            std::cout << YELLOW << "Enter 0 to return " << endl;
                            std::cout << RESET;
                            int is;
                            cin >> is;
                            system("CLS");
                            if (is == 0)
                                return displayCustomerMenu(cus, order);
                            productFound = true;
                            break;
                        }
                    }
                }
            }
            std::cout << YELLOW << "Enter 0 to return " << std::endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayCustomerMenu(cus, order);
            if (productFound == false)
            {
                std::cout << RED << "Can not found!";
                std::cout << RESET;
            }
            break;
        }

        case 4:
            displayCustomerMenu(cus, order);
            break;
        default:
            std::cout << RED << "Invalid selection!" << endl;
            std::cout << RESET;
            break;
        }

        break;
    }
    case 4:
    {
        int totalamoutout = order.CalculateTotalAmountOut();
        int totalamount = order.CalculateTotalAmount();
        order.SetImportPrice(totalamoutout);
        order.SetTotalAmount(totalamount);
        order.setTotalAfterDiscount(totalamount);
        order.Display(std::cout, cus.GetFullName());
        int totalquanity = 0;
            for (size_t i = 0; i < housewareManager.lists.getSize(); i++)
            {
                totalquanity += housewareManager.lists.at(i).getSoLuongTrongGio();
            }
            for (size_t i = 0; i < foodManager.lists.getSize(); i++)
            {
                totalquanity += foodManager.lists.at(i).getSoLuongTrongGio();
            }
            for (size_t i = 0; i < electricalproductManager.lists.getSize(); i++)
            {
                totalquanity += electricalproductManager.lists.at(i).getSoLuongTrongGio();
            }
        std::cout << CYAN << "Do you want to apply discount (Y/N)" << std::endl;
        std::cout << RESET;
        char ch1 = getch();
        if (ch1 == 'Y' || ch1 == 'y')
        {
            std::cout << GREEN << "Available Discounts:" << std::endl;
            std::cout << RESET;
            for (size_t j = 0; j < cus.GetDiscounts().getSize(); j++)
            {
                std::cout << j + 1 << ". "
                          << "Discount ID : " << cus.GetDiscounts().at(j).getDiscountID() << "|";
                std::cout << "Discount percentage :  " << cus.GetDiscounts().at(j).getPercentage() << std::endl;
            }
            int discountChoice;
            std::cout << CYAN << "Enter the number of the discount you want to apply: ";
            std::cout << RESET;
            std::cin >> discountChoice;
            system("CLS");

            if (discountChoice > 0 && discountChoice <= static_cast<int>(cus.GetDiscounts().getSize()))
            {
                order.ApplyDiscount(cus.GetDiscounts().at(discountChoice - 1));
                order.Display(std::cout, cus.GetFullName());
            }
            else
            {
                std::cout << RED << "Invalid discount choice." << std::endl;
                std::cout << RESET;
            }
        }
        std::cout << YELLOW << "Enter 0 to confirm " << std::endl;
        std::cout << RESET;
        int is;
        cin >> is;
        if (is == 0)
        {
            
            order.setQuanityProduct(totalquanity);
            Time time;
            time.updateRealTime();
            order.SetOrderTime(time);
            order.HoanThanh = true;
            orderManager.AddToLists(order);
            std::cout << CYAN << "Do you want to export bill (Y/N)" << std::endl;
            std::cout << RESET;
            char ch = getch();
            if (ch == 'Y' || ch == 'y')
            {
                int length = snprintf(nullptr, 0, "data/Order_list/Cus%d/%d_order.txt", order.getCustomerID(), order.GetOrderID());
                char *filename = new char[length + 1];
                snprintf(filename, length + 1, "data/Order_list/Cus%d/%d_order.txt", order.getCustomerID(), order.GetOrderID());
                std::cout << CYAN << "File path " << filename << std::endl;
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
        int choice;
        do
        {
            try
            {
                std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
                std::cout << std::setfill(' ');
                std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "         Enter your choice:        " << BLUE << "| |" << std::endl;
                std::cout << BLUE << setfill('=') << setw(41) << "=" << std::endl;
                std::cout << std::setfill(' ');
                std::cout << GREEN << "|1|" << YELLOW << "View statistics by day\t\      " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|2|" << YELLOW << "View statistics by month\t      " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|3|" << YELLOW << "View statistics by year\t      " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|0|" << YELLOW << "Return\t\t\t      " << BLUE << "| |" << std::endl;
                std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
                std::cout << std::setfill(' ');
                std::cout << RESET;
                std::cin >> choice;
                system("CLS");
                Time start, end;

                switch (choice)
                {
                case 1:
                    int temp;
                    std::cout << CYAN << "Enter start day " << std::endl;
                    std::cout << RESET;
                    std::cout << CYAN << "Day : ";
                    std::cout << RESET;
                    std::cin >> temp;
                    start.setDay(temp);
                    std::cout << CYAN << "Month : ";
                    std::cout << RESET;
                    std::cin >> temp;
                    start.setMonth(temp);
                    std::cout << CYAN << "Year : ";
                    std::cout << RESET;
                    std::cin >> temp;
                    start.setYear(temp);
                    std::cout << CYAN << "Enter end day " << std::endl;
                    std::cout << RESET;
                    std::cout << CYAN << "Day : ";
                    std::cout << RESET;
                    std::cin >> temp;
                    end.setDay(temp);
                    std::cout << CYAN << "Month : ";
                    std::cout << RESET;
                    std::cin >> temp;
                    end.setMonth(temp);
                    std::cout << CYAN << "Year  : ";
                    std::cout << RESET;
                    std::cin >> temp;
                    end.setYear(temp);
                    break;
                case 2:
                    int selectedMonth, selectedYear;
                    std::cout << CYAN << "Enter month (1-12): ";
                    std::cout << RESET;
                    std::cin >> selectedMonth;
                    std::cout << CYAN << "Enter year: ";
                    std::cout << RESET;
                    std::cin >> selectedYear;
                    start.setMonth(selectedMonth);
                    end.setMonth(selectedMonth);
                    start.setYear(selectedYear);
                    end.setYear(selectedYear);
                    start.setDay(1);
                    end.setDay(31);
                    break;
                case 3:
                    std::cout << CYAN << "Enter year: ";
                    std::cout << RESET;
                    std::cin >> selectedYear;
                    end.setYear(selectedYear);
                    start.setYear(selectedYear);
                    start.setDay(1);
                    start.setMonth(1);
                    end.setDay(31);
                    end.setMonth(12);
                    break;
                case 0:
                    return;
                default:
                    std::cout << RED << "Invalid choice. Please try again.\n";
                    std::cout << RESET;
                }

                cus.UpdateStatistics(start, end);
                cus.ViewStatistics(start, end);

                std::cout << YELLOW << "Enter 0 to return\n"
                          << RESET;
                std::cout << CYAN << "Enter your choice: ";
                std::cout << RESET;
                std::cin >> choice;
                system("CLS");
            }
            catch (const std::exception &ex)
            {
                std::cerr << RED << "Error: " << ex.what() << std::endl;
                std::cout << RESET;
            }
        } while (choice != 0);
        break;
    }

    case 6:
    {
        cus.Show_Orders_History(std::cout);
        std::cout << YELLOW << "Enter 0 to return " << endl;
        std::cout << RESET;
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
            std::cout << RED << "No discount available " << std::endl;
            std::cout << RESET;
        }
        else
            std::cout << cus.GetDiscounts();
        std::cout << CYAN << "Do you want to add new discount(Y/N)" << std::endl;
        char ch;
        cin >> ch;
        system("CLS");
        if (ch == 'Y' || ch == 'y')
        {
            while (1)
            {
                std::cout << CYAN << "Enter your code : ";
                std::cout << RESET;
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
                    std::cout << RED << "Can't found" << std::endl;
                }
                std::cout << CYAN << "Do you want to add more discount " << std::endl;
                std::cout << RESET;
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

        std::cout << YELLOW << "Enter 0 to return " << endl;
        std::cout << RESET;
        int is;
        cin >> is;
        if (is == 0)
            return displayCustomerMenu(cus, order);
        break;
    }
    case 8 : {
        return run() ;
        break ;
    }
    default:
        std::cout << RED << "Invalid value. Please try again" << endl;
        std::cout << RESET;
        break;
    }
}
void Menu::displayEmployeeMenu(Employee &employee)
{
    std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "           Employee Menu           " << BLUE << "| |" << std::endl;
    std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << GREEN << "|1|" << YELLOW << "View Personal Information\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|2|" << YELLOW << "Account Management\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|3|" << YELLOW << "View Inventory\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|4|" << YELLOW << "Manage Inventory\t \t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|6|" << YELLOW << "Exit\t\t\t              " << BLUE << "| |" << std::endl;
    std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << RESET;
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
        std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "           Account Management:          " << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << BLUE << "| |" << YELLOW << "Account ID:" << std::setw(29) << left << employee.GetEmployeeID() << BLUE << "| |" << std::endl;
        std::cout << BLUE << "| |" << YELLOW << "Please select the information to change:" << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << GREEN << "|1|" << YELLOW << "Full Name\t\t\t           " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|2|" << YELLOW << "Gender\t\t\t           " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|3|" << YELLOW << "Age\t\t\t                   " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|4|" << YELLOW << "Day of Birth\t\t\t           " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|5|" << YELLOW << "Address\t\t\t           " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|6|" << YELLOW << "Phone Number\t\t\t           " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|7|" << YELLOW << "Email\t\t\t           " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|8|" << YELLOW << "Go back\t\t\t           " << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << RESET;
        int selection;
        std::cin >> selection;
        system("CLS");
        switch (selection)
        {
        case 1:
        {
            std::cout << CYAN << "Enter your new full name : ";
            std::cout << RESET;
            char *fullName;
            getInput(fullName, std::cin);
            employee.SetFullName(fullName);
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayEmployeeMenu(employee);
            break;
        }
        case 2:
        {
            std::cout << CYAN << "Enter your new gender : ";
            std::cout << RESET;
            char *gender;
            getInput(gender, std::cin);
            employee.SetGender(gender);
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayEmployeeMenu(employee);
            break;
        }
        case 3:
        {
            int age;
            std::cout << CYAN << "Enter your new age : ";
            std::cout << RESET;
            std::cin >> age;
            employee.SetAge(age);
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayEmployeeMenu(employee);
            break;
        }
        case 4:
        {
            Date date;
            std::cout << CYAN << "Enter your new day of birth  : ";
            std::cout << RESET;
            std::cin >> date;
            employee.SetDayOfBirth(date);
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayEmployeeMenu(employee);
            break;
        }
        case 5:
        {
            std::cout << CYAN << "Enter your new address";
            std::cout << RESET;
            char *address;
            getInput(address, std::cin);
            employee.SetAddress(address);
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayEmployeeMenu(employee);
            break;
        }
        case 6:
        {
            std::cout << CYAN << "Enter your new phone number : ";
            std::cout << RESET;
            char *phonenumber;
            getInput(phonenumber, std::cin);
            employee.SetPhoneNumber(phonenumber);
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayEmployeeMenu(employee);
            break;
        }
        case 7:
        {
            std::cout << CYAN << "Enter your new email : ";
            std::cout << RESET;
            char *email;
            getInput(email, std::cin);
            employee.SetEmail(email);
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayEmployeeMenu(employee);
            break;
        }
        case 8:
        {
            return displayEmployeeMenu(employee);
            break;
        }

        default:
        {
            std::cout << RED << "Invalid selection!" << endl;
            std::cout << RESET;
            return displayEmployeeMenu(employee);
            break;
        }
        }

        break;
    }
    case 3:
    {
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "        Product Categories:        " << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << GREEN << "|1|" << YELLOW << "View Houseware Products\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|2|" << YELLOW << "View Food Products\t\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|3|" << YELLOW << "View Electrical Products\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|4|" << YELLOW << "Go back\t\t\t      " << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << RESET;

        int viewChoice;
        std::cin >> viewChoice;

        switch (viewChoice)
        {
            {
            case 1:
            {
                housewareManager.Display(housewareManager.lists);
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayEmployeeMenu(employee);
                break;
            }
            case 2:
            {
                foodManager.Display(foodManager.lists);
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayEmployeeMenu(employee);
                break;
            }
            case 3:
            {
                electricalproductManager.Display(electricalproductManager.lists);
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayEmployeeMenu(employee);
                break;
            }
            case 4:
            {
                displayEmployeeMenu(employee);
                break;
            }
            default:
                std::cout << RED << "Invalid selection!" << endl;
                std::cout << RESET;
                break;
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
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
    {
        // EDIT THÔNG TIN SẢN PHẨM
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "        Product Categories:        " << BLUE << "| |" << std::endl;
        std::cout << BLUE << setfill('=') << setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << GREEN << "|1|" << YELLOW << "Edit Houseware Products\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|2|" << YELLOW << "Edit Food Products\t\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|3|" << YELLOW << "Edit Electrical Products\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|4|" << YELLOW << "Go back\t\t\t      " << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << RESET;

        int selection;
        std::cin >> selection;
        switch (selection)
        {
        case 1:
        {
            std::cout << CYAN << "Enter Houseware ID to edit : ";
            std::cout << RESET;
            int id;
            std::cin >> id;
            int index;
            bool found = false;
            for (size_t i = 0; i < housewareManager.lists.getSize(); i++)
            {
                if (housewareManager.lists.at(i).getMaSanPham() == id)
                {
                    found = true;
                    index = i;
                }
            }
            Houseware &houseware = housewareManager.lists.at(index);
            houseware.EditProduct();
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayEmployeeMenu(employee);
            break;
        }
        case 2:
        {
            std::cout << CYAN << "Enter Food ID to edit : ";
            std::cout << RESET;
            int id;
            std::cin >> id;
            int index;
            bool found = false;
            for (size_t i = 0; i < foodManager.lists.getSize(); i++)
            {
                if (foodManager.lists.at(i).getMaSanPham() == id)
                {
                    found = true;
                    index = i;
                }
            }
            Food &food = foodManager.lists.at(index);
            food.EditProduct();
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayEmployeeMenu(employee);
            break;
        }
        case 3:
        {
            std::cout << CYAN << "Enter Electrical Product ID to edit : ";
            std::cout << RESET;
            int id;
            std::cin >> id;
            int index;
            bool found = false;
            for (size_t i = 0; i < electricalproductManager.lists.getSize(); i++)
            {
                if (electricalproductManager.lists.at(i).getMaSanPham() == id)
                {
                    found = true;
                    index = i;
                }
            }
            ElectricalProduct &electricalproduct = electricalproductManager.lists.at(index);
            electricalproduct.EditProduct();
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayEmployeeMenu(employee);
            break;
        }
        case 4:
        {
            return displayEmployeeMenu(employee);
            break;
        }
        default:
        {
            std::cout << RED << "Invalid selection!" << endl;
            std::cout << RESET;
            break;
        }
        }
    }
    break;

    default:
        std::cout << RED << "Invalid value. Please try again" << endl;
        std::cout << RESET;
        break;
    }
    }
}
//!
void Menu::displayManagerMenu()
{
    std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "            Manager Menu:          " << BLUE << "| |" << std::endl;
    std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << GREEN << "|1|" << YELLOW << "View lists\t\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|2|" << YELLOW << "Edit Information\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|3|" << YELLOW << "Add object\t\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|4|" << YELLOW << "Delete object\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|5|" << YELLOW << "Statistics\t\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|8|" << YELLOW << "Exit\t\t\t              " << BLUE << "| |" << std::endl;
    std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << RESET;

    int choice;
    std::cin >> choice;
    system("CLS");
    switch (choice)
    {
    case 1:
    {
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "            MENU OPTIONS:          " << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << GREEN << "|1|" << YELLOW << "View employee list\t\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|2|" << YELLOW << "View customer list\t\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|3|" << YELLOW << "View product list\t\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|4|" << YELLOW << "View discount list\t\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|5|" << YELLOW << "Turn back\t\t\t      " << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << RESET;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        {
            employeeManager.Display(employeeManager.lists);
            std::cout << CYAN << "Do you want to export file (Y/N)" << endl;
            std::cout << RESET;
            char ch;
            std::cin >> ch;
            if (ch == 'Y' || ch == 'y')
            {
                employeeManager.ShowLists_file(employeeManager.lists, "data/employee_lists.txt");
            }
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayManagerMenu();
            break;
        }
        case 2:
        {
            customerManager.Display(customerManager.lists);
            std::cout << CYAN << "Do you want to export file (Y/N)" << endl;
            std::cout << RESET;
            char ch;
            std::cin >> ch;
            if (ch == 'Y' || ch == 'y')
            {
                customerManager.ShowLists_file(customerManager.lists, "data/customer_lists.txt");
            }
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayManagerMenu();
            break;
        }
        case 3:
        {
            std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "        Product Categories:        " << BLUE << "| |" << std::endl;
            std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << GREEN << "|1|" << YELLOW << "View Houseware Products\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|2|" << YELLOW << "View Food Products\t\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|3|" << YELLOW << "View Electrical Products\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|4|" << YELLOW << "Go back\t\t\t      " << BLUE << "| |" << std::endl;
            std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << RESET;

            int viewChoice;
            std::cin >> viewChoice;

            switch (viewChoice)
            {
            case 1:
            {
                housewareManager.Display(housewareManager.lists);
                std::cout << BLUE << "Do you want to export file (Y/N)" << std::endl << RESET ;
                char selection ;
                std::cin >> selection ;
                if(selection == 'Y' || selection == 'y') {
                    housewareManager.ShowLists_file(housewareManager.lists,"data/houseware_lists.txt");
                } 
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            case 2:
            {
                foodManager.Display(foodManager.lists);
                std::cout << BLUE << "Do you want to export file (Y/N)" << std::endl << RESET ;
                char selection ;
                std::cin >> selection ;
                if(selection == 'Y' || selection == 'y') {
                    foodManager.ShowLists_file(foodManager.lists,"data/food_lists.txt");
                } 
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            case 3:
            {
                electricalproductManager.Display(electricalproductManager.lists);
                std::cout << BLUE << "Do you want to export file (Y/N)" << std::endl << RESET ;
                char selection ;
                std::cin >> selection ;
                if(selection == 'Y' || selection == 'y') {
                    electricalproductManager.ShowLists_file(electricalproductManager.lists,"data/houseware_lists.txt");
                } 
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            case 4:
            {
                displayManagerMenu();
                break;
            }
            default:
            {
                std::cout << RED << "Invalid selection!" << endl;
                std::cout << RESET;
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
            }
            }
            break;
        }
        case 4:
        {
            if (discountManager.lists.isEmpty())
            {
                std::cout << RED << "No discount available" << std::endl;
                std::cout << RESET;
                return;
            }
            else
            {
                discountManager.Display(discountManager.lists);
            }
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayManagerMenu();
        }
        case 5:
        {
            return displayManagerMenu();
            break;
        }
        }
        break;
    }
    case 2:
    {
        std::cout << "== Select object you want to edit information ===" << std::endl;
        std::cout << YELLOW << "1. Employee" << RESET << endl;
        std::cout << GREEN << "2. Customer" << RESET << endl;
        std::cout << BLUE << "3. Product" << RESET << endl;
        std::cout << CYAN << "4. Discount" << RESET << endl;
        std::cout << RED << "5. Turn back " << RESET << endl;
        int choose;
        std::cin >> choose;
        system("CLS");
        switch (choose)
        {
        case 1:
        {
            int index;
            std::cout << CYAN << "Enter employee ID you want to delete" << std::endl;
            std::cout << RESET;
            int id;
            bool found = false;
            std::cin >> id;
            for (size_t i = 0; i < employeeManager.lists.getSize(); i++)
            {
                if (employeeManager.lists.at(i).GetEmployeeID() == id)
                {
                    index = i;
                    found = true;
                }
            }
            Employee &employee = employeeManager.lists.at(index);
            if (found == false)
                std::cout << RED << "Can't found" << std::endl;
            else
            {
                std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
                std::cout << std::setfill(' ');
                std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "           Account Management:          " << BLUE << "| |" << std::endl;
                std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
                std::cout << std::setfill(' ');
                std::cout << BLUE << "| |" << YELLOW << "Account ID:" << std::setw(29) << left << employee.GetEmployeeID() << BLUE << "| |" << std::endl;
                std::cout << BLUE << "| |" << YELLOW << "Please select the information to change:" << BLUE << "| |" << std::endl;
                std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
                std::cout << std::setfill(' ');
                std::cout << GREEN << "|1|" << YELLOW << "Full Name\t\t\t           " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|2|" << YELLOW << "Gender\t\t\t           " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|3|" << YELLOW << "Age\t\t\t                   " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|4|" << YELLOW << "Day of Birth\t\t\t           " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|5|" << YELLOW << "Address\t\t\t           " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|6|" << YELLOW << "Phone Number\t\t\t           " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|7|" << YELLOW << "Email\t\t\t           " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|8|" << YELLOW << "Go back\t\t\t           " << BLUE << "| |" << std::endl;
                std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
                std::cout << std::setfill(' ');
                std::cout << RESET;
                int selection;
                std::cin >> selection;
                system("CLS");
                switch (selection)
                {
                case 1:
                {
                    std::cout << CYAN << "Enter your new full name : ";
                    std::cout << RESET;
                    char *fullName;
                    getInput(fullName, std::cin);
                    employee.SetFullName(fullName);
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                    break;
                }
                case 2:
                {
                    std::cout << CYAN << "Enter your new gender :";
                    std::cout << RESET;
                    char *gender;
                    getInput(gender, std::cin);
                    employee.SetGender(gender);
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                    break;
                }
                case 3:
                {
                    int age;
                    std::cout << CYAN << "Enter your new age : ";
                    std::cout << RESET;
                    std::cin >> age;
                    employee.SetAge(age);
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                    break;
                }
                case 4:
                {
                    Date date;
                    std::cout << CYAN << "Enter your new day of birth : ";
                    std::cout << RESET;
                    std::cin >> date;
                    employee.SetDayOfBirth(date);
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                }
                case 5:
                {
                    std::cout << CYAN << "Enter your new address";
                    std::cout << RESET;
                    char *address;
                    getInput(address, std::cin);
                    employee.SetAddress(address);
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                    break;
                }
                case 6:
                {
                    std::cout << CYAN << "Enter your new phone number : ";
                    std::cout << RESET;
                    char *phonenumber;
                    getInput(phonenumber, std::cin);
                    employee.SetPhoneNumber(phonenumber);
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                    break;
                }
                case 7:
                {
                    std::cout << CYAN << "Enter your new email : ";
                    std::cout << RESET;
                    char *email;
                    getInput(email, std::cin);
                    employee.SetEmail(email);
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                    break;
                }
                case 8:
                {
                    return run();
                    break;
                }

                default:
                {
                    std::cout << RED << "Invalid selection!" << endl;
                    std::cout << RESET;
                    break;
                }
                }

                break;
            }
        }
        case 2:
        {
            int index;
            std::cout << CYAN << "Enter customer ID you want to delete" << std::endl;
            std::cout << RESET;
            int id;
            std::cin >> id;
            bool found = false;
            for (size_t i = 0; i < customerManager.lists.getSize(); i++)
            {
                if (customerManager.lists.at(i).GetCustomerID() == id)
                {
                    index = i;
                    found = true;
                }
            }
            Customer &cus = customerManager.lists.at(index);
            if (found == false)
                std::cout << RED << "Can't found" << std::endl;
            else
            {
                std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
                std::cout << std::setfill(' ');
                std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "           Account Management:          " << BLUE << "| |" << std::endl;
                std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
                std::cout << std::setfill(' ');
                std::cout << BLUE << "| |" << YELLOW << "Account ID:" << std::setw(29) << left << cus.GetCustomerID() << BLUE << "| |" << std::endl;
                std::cout << BLUE << "| |" << YELLOW << "Please select the information to change:" << BLUE << "| |" << std::endl;
                std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
                std::cout << std::setfill(' ');
                std::cout << GREEN << "|1|" << YELLOW << "Full Name\t\t\t           " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|2|" << YELLOW << "Gender\t\t\t           " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|3|" << YELLOW << "Age\t\t\t                   " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|4|" << YELLOW << "Day of Birth\t\t\t           " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|5|" << YELLOW << "Address\t\t\t           " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|6|" << YELLOW << "Phone Number\t\t\t           " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|7|" << YELLOW << "Email\t\t\t           " << BLUE << "| |" << std::endl;
                std::cout << GREEN << "|8|" << YELLOW << "Go back\t\t\t           " << BLUE << "| |" << std::endl;
                std::cout << BLUE << std::setfill('=') << std::setw(46) << "=" << std::endl;
                std::cout << std::setfill(' ');
                std::cout << RESET;
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
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                    break;
                }
                case 2:
                {
                    std::cout << "Enter your new gender :";
                    char *gender;
                    getInput(gender, std::cin);
                    cus.SetGender(gender);
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                    break;
                }
                case 3:
                {
                    int age;
                    std::cout << "Enter your new age : ";
                    std::cin >> age;
                    cus.SetAge(age);
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                    break;
                }
                case 4:
                {
                    Date date;
                    std::cout << "Enter your new DOB : ";
                    std::cin >> date;
                    cus.SetDayOfBirth(date);
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                }
                case 5:
                {
                    std::cout << "Enter your new address";
                    char *address;
                    getInput(address, std::cin);
                    cus.SetAddress(address);
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                    break;
                }
                case 6:
                {
                    std::cout << "Enter your new phone number : ";
                    char *phonenumber;
                    getInput(phonenumber, std::cin);
                    cus.SetPhoneNumber(phonenumber);
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                    break;
                }
                case 7:
                {
                    std::cout << "Enter your new email : ";
                    char *email;
                    getInput(email, std::cin);
                    cus.SetEmail(email);
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                    break;
                }
                case 8:
                {
                    return run();
                    break;
                }

                default:
                {
                    std::cout << RED << "Invalid selection!" << endl;
                    std::cout << RESET;
                    std::cout << YELLOW << "Enter 0 to return " << endl;
                    std::cout << RESET;
                    int is;
                    cin >> is;
                    system("CLS");
                    if (is == 0)
                        return displayManagerMenu();
                    break;
                }
                }

                break;
            }
        }
        case 3:
        {
            // EDIT THÔNG TIN SẢN PHẨM
            std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "        Product Categories:        " << BLUE << "| |" << std::endl;
            std::cout << BLUE << setfill('=') << setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << GREEN << "|1|" << YELLOW << "Edit Houseware Products\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|2|" << YELLOW << "Edit Food Products\t\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|3|" << YELLOW << "Edit Electrical Products\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|4|" << YELLOW << "Go back\t\t\t      " << BLUE << "| |" << std::endl;
            std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << RESET;

            int selection;
            std::cin >> selection;
            switch (selection)
            {
            case 1:
            {
                std::cout << "Enter Houseware ID to edit : ";
                int id;
                std::cin >> id;
                int index;
                bool found = false;
                for (size_t i = 0; i < housewareManager.lists.getSize(); i++)
                {
                    if (housewareManager.lists.at(i).getMaSanPham() == id)
                    {
                        found = true;
                        index = i;
                    }
                }
                Houseware &houseware = housewareManager.lists.at(index);
                houseware.EditProduct();
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            case 2:
            {
                std::cout << "Enter Food ID to edit : ";
                int id;
                std::cin >> id;
                int index;
                bool found = false;
                for (size_t i = 0; i < foodManager.lists.getSize(); i++)
                {
                    if (foodManager.lists.at(i).getMaSanPham() == id)
                    {
                        found = true;
                        index = i;
                    }
                }
                Food &food = foodManager.lists.at(index);
                food.EditProduct();
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            case 3:
            {
                std::cout << "Enter Electrical Product ID to edit : ";
                int id;
                std::cin >> id;
                int index;
                bool found = false;
                for (size_t i = 0; i < electricalproductManager.lists.getSize(); i++)
                {
                    if (electricalproductManager.lists.at(i).getMaSanPham() == id)
                    {
                        found = true;
                        index = i;
                    }
                }
                ElectricalProduct &electricalproduct = electricalproductManager.lists.at(index);
                electricalproduct.EditProduct();
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            case 4:
            {
                return displayManagerMenu();
                break;
            }
            default:
            {
                std::cout << RED << "Invalid selection!" << endl;
                std::cout << RESET;
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            }
        }
        break;
        case 4:
        {
            std::cout << "Enter Discount ID to edit : ";
            int id;
            std::cin >> id;
            int index;
            bool found = false;
            for (size_t i = 0; i < discountManager.lists.getSize(); i++)
            {
                if (discountManager.lists.at(i).getDiscountID() == id)
                {
                    found = true;
                    index = i;
                }
            }
            if(found) {
                discountManager.lists.at(index).Display_01(std::cout) ;
                Discount &discount = discountManager.lists.at(index);
            std::cin >> discount;
            }
            
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayManagerMenu();
            break;
        }
        default:
            std::cout << RED << "Invalid selection!" << endl;
            std::cout << RESET;
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayManagerMenu();
            break;
        }
        break;
    }
    break;
    case 3:
    {
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "   Select object you want to add:  " << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << GREEN << "|1|" << YELLOW << "Employee\t\t\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|2|" << YELLOW << "Customer\t\t\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|3|" << YELLOW << "Product\t\t\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|4|" << YELLOW << "Discount\t\t\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|6|" << YELLOW << "Turn back\t\t              " << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << RESET;

        int choose;
        std::cin >> choose;
        system("CLS");
        switch (choose)
        {
        case 1:
        {
            int numEmployees;
            std::cout << CYAN << "Enter the number of employees to add: ";
            std::cout << RESET;
            std::cin >> numEmployees;
            Employee *employees = new Employee[numEmployees];

            for (int i = 0; i < numEmployees; i++)
            {
                bool found = false ; 
                employees[i].GetInformation();
                for(size_t j = 0 ; j< employeeManager.lists.getSize();j++){
                        if(employeeManager.lists.at(j).GetEmployeeID() == employees[i].GetEmployeeID()) {
                            found = true ;
                            break ;
                        }
                }
                if(!found) 
                employeeManager.AddToLists(employees[i]);
                else {
                    std::cout << "Employee ID already existed" << std::endl ;
                }
            }

            delete[] employees;
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayManagerMenu();
            break;
        }
        case 2:
        {
            int numCustomer;
            std::cout << CYAN << "Enter the number of Customer to add: ";
            std::cout << RESET;
            std::cin >> numCustomer;
            Customer *customers = new Customer[numCustomer];

            for (int i = 0; i < numCustomer; i++)
            {
                bool found = false ; 
                customers[i].GetInformation();
                for (size_t j = 0 ; j < customerManager.lists.getSize() ; j++) {
                    if(customerManager.lists.at(j).GetCustomerID() == customers[i].GetCustomerID()){
                        found = true ;
                        break;
                    }
                }

                if(!found)
                customerManager.AddToLists(customers[i]);
                else 
                    std::cout <<  RED <<  "Customer ID already existed" <<  RESET << std::endl ;
            }

            delete[] customers;
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayManagerMenu();
            break;
        }
        case 3:
        {
            std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "        Product Categories:        " << BLUE << "| |" << std::endl;
            std::cout << BLUE << setfill('=') << setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << GREEN << "|1|" << YELLOW << "Add Houseware Products\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|2|" << YELLOW << "Add Food Products\t\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|3|" << YELLOW << "Add Electrical Products\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|4|" << YELLOW << "Go back\t\t\t      " << BLUE << "| |" << std::endl;
            std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << RESET;
            int selection;
            std::cin >> selection;
            switch (selection)
            {
            case 1:
            {
                std::cout << CYAN << "Enter number houseware product you want to add : ";
                std::cout << RESET;
                int numHouseware;
                std::cin >> numHouseware;
                Houseware *houseware = new Houseware[numHouseware];
                for (size_t i = 0; i < numHouseware; i++)
                {
                    cin >> houseware[i];
                    bool found = false ;
                    for (size_t j = 0; j < housewareManager.lists.getSize(); j++)
                    {
                        if(houseware[i].getMaSanPham() == housewareManager.lists.at(j).getMaSanPham()) {
                            found = true ;
                            break; 
                        }
                    }
                    if(!found)
                    housewareManager.AddToLists(houseware[i]);
                    else 
                    std::cout << "ProductID already existed" << std::endl ;
                }
                delete[] houseware;
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            case 2:
            {
                std::cout << CYAN << "Enter number food product you want to add : ";
                std::cout << RESET;
                int numfood;
                std::cin >> numfood;
                Food *food = new Food[numfood];
                for (size_t i = 0; i < numfood; i++)
                {
                    cin >> food[i];
                    bool found = false ;
                    for (size_t j = 0; j < foodManager.lists.getSize(); j++)
                    {
                        if(food[i].getMaSanPham() == foodManager.lists.at(j).getMaSanPham()) {
                            found = true ;
                            break; 
                        }
                    }
                    if(!found)
                    foodManager.AddToLists(food[i]);
                    else 
                    std::cout << "ProductID already existed" << std::endl ;
                }
                delete[] food;
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            case 3:
            {
                std::cout << CYAN << "Enter number electrical product you want to add : ";
                std::cout << RESET;
                int numelectricalproduct;
                std::cin >> numelectricalproduct;
                ElectricalProduct *electricalproducts = new ElectricalProduct[numelectricalproduct];
                for (size_t i = 0; i < numelectricalproduct; i++)
                {
                    cin >> electricalproducts[i];
                    bool found = false ;
                    for (size_t j = 0; j < electricalproductManager.lists.getSize(); j++)
                    {
                        if(electricalproducts[i].getMaSanPham() == electricalproductManager.lists.at(j).getMaSanPham()) {
                            found = true ;
                            break; 
                        }
                    }
                    if(!found)
                    electricalproductManager.AddToLists(electricalproducts[i]);
                    else {
                    std::cout << "ProductID already existed" << std::endl ;
                    }
                    }
                delete[] electricalproducts;
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            case 4:
            {
                return displayManagerMenu();
                break;
            }
            default:
                std::cout << RED << "Invalid selection!" << endl;
                std::cout << RESET;
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            break;
        case 4:
        {
            // Discount
            std::cout << CYAN << "Enter number of Discount you want to add ";
            std::cout << RESET;
            int numDiscount;
            std::cin >> numDiscount;
            Discount *discount = new Discount[numDiscount];
            for (size_t i = 0; i < numDiscount; i++)
            {
                std::cin >> discount[i];
                discountManager.AddToLists(discount[i]);
            }
            delete[] discount;
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayManagerMenu();
            break;
        }
        default:
            std::cout << RED << "Invalid selection!" << endl;
            std::cout << RESET;
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayManagerMenu();
            break;
        }
        break;
        }
    case 4:
    {
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "  Which object you want to delete: " << BLUE << "| |" << std::endl;
        std::cout << BLUE << setfill('=') << setw(40) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << GREEN << "|1|" << YELLOW << "Customer\t\t\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|2|" << YELLOW << "Employee\t\t\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|3|" << YELLOW << "Product\t\t\t      " << BLUE << "| |" << std::endl;
        std::cout << GREEN << "|4|" << YELLOW << "Discount\t\t\t      " << BLUE << "| |" << std::endl;
        std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
        std::cout << std::setfill(' ');
        std::cout << RESET;
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
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayManagerMenu();
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
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayManagerMenu();
            break;
        }
        case 3:
        {
            std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "        Product Categories:        " << BLUE << "| |" << std::endl;
            std::cout << BLUE << setfill('=') << setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << GREEN << "|1|" << YELLOW << "Delete Houseware Products\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|2|" << YELLOW << "Delete Food Products\t\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|3|" << YELLOW << "Delete Electrical Products\t      " << BLUE << "| |" << std::endl;
            std::cout << GREEN << "|4|" << YELLOW << "Go back\t\t\t      " << BLUE << "| |" << std::endl;
            std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
            std::cout << std::setfill(' ');
            std::cout << RESET;
            int choice;
            std::cin >> choice;
            switch (choice)
            {
            case 1:
            {
                std::cout << CYAN << "Enter electrical product ID you want to delete" << std::endl;
                std::cout << RESET;
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
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            case 2:
            {
                std::cout << CYAN << "Enter Food ID you want to delete" << std::endl;
                std::cout << RESET;
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
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            case 3:
            {
                std::cout << CYAN << "Enter electrical product ID you want to delete" << std::endl;
                std::cout << RESET;
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
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            case 4:
            {
                std::cout << CYAN << "Enter Discount ID you want to delete" << std::endl;
                std::cout << RESET;
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
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            case 5:
            {
                return displayManagerMenu();
                break;
            }
            default:
                std::cout << RED << "Invalid selection!" << endl;
                std::cout << RESET;
                std::cout << YELLOW << "Enter 0 to return " << endl;
                std::cout << RESET;
                int is;
                cin >> is;
                system("CLS");
                if (is == 0)
                    return displayManagerMenu();
                break;
            }
            break;
        }
        default:
            std::cout << YELLOW << "Enter 0 to return " << endl;
            std::cout << RESET;
            int is;
            cin >> is;
            system("CLS");
            if (is == 0)
                return displayManagerMenu();
            break;
        }
    }
    break;
    case 5:
    {
        int choice;
        do
        {
            try
            {
                std::cout << "1. View statistics by day\n";
                std::cout << "2. View statistics by month\n";
                std::cout << "3. View statistics by year\n";
                std::cout << YELLOW << "Enter 0 to return\n"
                          << RESET;
                std::cout << "Enter your choice: ";
                std::cin >> choice;

                Time start, end;

                switch (choice)
                {
                case 1:
                    int temp;
                    std::cout << "Enter start day " << std::endl;
                    std::cout << "Day : ";
                    std::cin >> temp;
                    start.setDay(temp);
                    std::cout << "Month : ";
                    std::cin >> temp;
                    start.setMonth(temp);
                    std::cout << "Year  : ";
                    std::cin >> temp;
                    start.setMonth(temp);
                    std::cout << "Enter end day " << std::endl;
                    std::cout << "Day : ";
                    std::cin >> temp;
                    end.setDay(temp);
                    std::cout << "Month : ";
                    std::cin >> temp;
                    end.setMonth(temp);
                    std::cout << "Year  : ";
                    std::cin >> temp;
                    end.setMonth(temp);
                    break;
                case 2:
                    int selectedMonth, selectedYear;
                    std::cout << "Enter month (1-12): ";
                    std::cin >> selectedMonth;
                    std::cout << "Enter year: ";
                    std::cin >> selectedYear;
                    start.setMonth(selectedMonth);
                    end.setMonth(selectedMonth);
                    start.setYear(selectedYear);
                    end.setYear(selectedYear);
                    start.setDay(1);
                    end.setDay(31);
                    break;
                case 3:
                    std::cout << "Enter year: ";
                    std::cin >> selectedYear;
                    end.setYear(selectedYear);
                    start.setYear(selectedYear);
                    start.setDay(1);
                    start.setMonth(1);
                    end.setDay(31);
                    end.setMonth(12);
                    break;
                case 0:
                    return;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                }
                system("CLS");
                UpdateStatistics(start, end);
                statistics.DisplaySuperMarketStatistics();
                std::cout << YELLOW << "Enter 0 to return\n"
                          << RESET;
                std::cout << "Enter your choice: ";
                std::cin >> choice;
                system("CLS");
            }
            catch (const std::exception &ex)
            {
                std::cerr << "Error: " << ex.what() << std::endl;
            }
        } while (choice != 0);
        break;
    }

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
        std::cout << RED << "Invalid value. Please try again" << endl;
        std::cout << RESET;
        break;
    }
    }
}

void Menu::run()
{
    createDiscountPointvsTime();
    system("CLS");
    bool exit = false;
    int userType;

    std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << BLUE << "| |" << BRIGHT_MAGENTA << "       Select the user type:       " << BLUE << "| |" << std::endl;
    std::cout << BLUE << setfill('=') << setw(41) << "=" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << GREEN << "|1|" << YELLOW << "Customer\t\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|2|" << YELLOW << "Manager\t\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|3|" << YELLOW << "Employee\t\t\t      " << BLUE << "| |" << std::endl;
    std::cout << GREEN << "|4|" << YELLOW << "Turn back\t\t\t      " << BLUE << "| |" << std::endl;
    std::cout << BLUE << std::setfill('=') << std::setw(41) << "=" << std::endl;
    std::cout << std::setfill(' ');
    std::cout << RESET;

    std::cin >> userType;
    system("CLS");

    switch (userType)
    {
    case 1:
    {
        bool validID = false;
        // while (true)
        // {
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
                    std::cout << YELLOW << "Choose 0 to return Customer Menu or other to return main menu: ";
                    std::cout << RESET;
                    std::cin >> choice;
                    system("CLS");
                    if (choice == 0)
                    {
                        displayCustomerMenu(cus, order);
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
                std::cout << RED << "Invalid ID! Do you want to try again? (Y/N): ";
                std::cout << RESET;
                char tryAgain;
                std::cin >> tryAgain;
                system("CLS");
                if (tryAgain != 'Y' && tryAgain != 'y')
                {
                    return;
                }
            }
        // }
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
        std::cout << YELLOW << "Choose 0 to return Manager Menu or other to return Main menu : ";
        std::cout << RESET;
        std::cin >> choice;

        if (choice == 0)
        {
            displayManagerMenu();
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
        // while (true)
        // {
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
                    std::cout << YELLOW << "Choose 0 to return Employee Menu or other number to return main menu :  ";
                    std::cout << RESET;
                    std::cin >> choice;
                    system("CLS");
                    if (choice == 0)
                    {
                        displayEmployeeMenu(employee);
                    }
                    else
                    {

                        return run();
                    }
                }
            }

            std::cout << RED << "Invalid Employee ID! Do you want to try again? (Y/N): ";
            std::cout << RESET;
            char tryAgain;
            std::cin >> tryAgain;
            system("CLS");
            if (tryAgain != 'Y' && tryAgain != 'y')
            {
                return;
            }
        // }
        break;
    }
    case 4:
        // exit = true;
        break;
    default:
        std::cout << RED << "Invalid user type!" << std::endl;
        std::cout << RESET;
        break;
    }
}
