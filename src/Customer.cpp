#include <iomanip>
#include <limits>
#include "Menu.h"
#include "Customer.h"

#define MAX_LENGTH 256

Customer::Customer(){

};
Customer::Customer(int CustomerID, char *fullName, char *Gender, int age, Date DayOfBirth, char *address, char *phoneNumber, char *email, int point, char *type) : Person(CustomerID, fullName, Gender, age, DayOfBirth, address, phoneNumber, email), Point(Point), CustomerType(type){};
void Customer::SetPoint(int Point)
{
    this->Point = Point;
}
int Customer::GetPoint() const
{
    return this->Point;
}
int Customer::GetCustomerID() const
{
    return this->CustomerID;
}
Statistics &Customer::getStatistics()
{
    return statistics;
}
void Customer::SetCustomerID(int ID)
{
    this->CustomerID = ID;
}
char *Customer::getCustomerType() const
{
    return this->CustomerType;
}
void Customer::setCustomerType(char *type)
{
    this->CustomerType = type;
}
// void Customer::AddToPurchaseHistory(const Order& order){

// }
Vector_Class<Order> &Customer::getOrderHistory()
{
    return orderHistory;
}
void Customer::Display()
{
    std::cout << "Customer Information : " << std::endl;
    std::cout << "Customer ID : " << GetCustomerID() << std::endl;
    std::cout << "Full name : " << GetFullName() << std::endl;
    std::cout << "Age : " << GetAge() << std::endl;
    std::cout << "Gender :" << GetGender() << std::endl;
    std::cout <<  std::right << std::setw(0) << "Day of birth: " << GetDayOfBirth() << std::endl;
    std::cout << "Address : " << GetAddress() << std::endl;
    std::cout << "Phone number : " << GetPhoneNumber() << std::endl;
    std::cout << "Email: " << GetEmail() << std::endl;
    std::cout << "Point : " << GetPoint() << std::endl;
    std::cout << "Customer Type : " << getCustomerType() << endl;
}
Customer::~Customer()
{
}
ostream &operator<<(ostream &os, const Customer &obj)
{
    os << obj.GetCustomerID() << "," << obj.GetFullName() << "," << obj.GetAge() << "," << obj.GetDayOfBirth() << "," << obj.GetAddress() << "," << obj.GetPhoneNumber() << "," << obj.GetEmail() << "," << obj.GetPoint() << "," << obj.getCustomerType() << endl;
    return os;
}
void Customer::Display_01(ostream &cout)
{
    cout << std::left << std::setw(15) << GetCustomerID() << " | ";
    cout << std::left << std::setw(20) << GetFullName() << " | ";
    cout << std::left << std::setw(4) << GetAge() << " | ";
    cout << std::left << std::setw(20) <<std::right << std::setw(0)  << GetDayOfBirth() << " | ";
    cout << std::left << std::setw(25) << GetAddress() << " | ";
    cout << std::left << std::setw(15) << GetPhoneNumber() << " | ";
    cout << std::left << std::setw(30) << GetEmail() << " | ";
    cout << std::left << std::setw(20) << GetPoint() << " | ";
    cout << std::left << std::setw(10) << getCustomerType() << " | ";
    cout << "\n";
}
// void Customer::DataFile(const Customer obj , const char* filename) {
//     cout << obj.GetCustomerID() << "," << obj.GetFullName() << "," << obj.GetAge() << "," << obj.GetDayOfBirth() << "," << obj.GetAddress() << "," << obj.GetPhoneNumber() << "," << obj.GetEmail() << "," << obj.getCustomerType() << "," << obj.getCustomerType()  << endl ;
// }
void Customer::WriteDataToFile(std::ostream &file) const
{
    file << GetCustomerID() << ","
         << GetFullName() << ","
         << GetGender() << ","
         << GetAge() << ","
         << GetDayOfBirth() << ","
         << GetAddress() << ","
         << GetPhoneNumber() << ","
         << GetEmail() << ","
         << GetPoint() << ","
         << getCustomerType() << std::endl;
}
void Customer::ReadDataFromFile(std::istream &file)
{
    char comma;
    file >> CustomerID >> comma;
    Menu::readAttributeTillDelimiter(fullName, file);
    Menu::readAttributeTillDelimiter(Gender, file);
    file >> age >> comma;
    file >> DayOfBirth >> comma;
    Menu::readAttributeTillDelimiter(address, file);
    Menu::readAttributeTillDelimiter(phoneNumber, file);
    Menu::readAttributeTillDelimiter(email, file);
    file >> Point >> comma;
    Menu::readAttributeTillDelimiter(CustomerType, file);
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
void Customer::BuyProduct(Order &order, Food &obj, int sl)
{
    obj.setSoLuongTonKho(obj.getSoLuongTonKho() - sl);
    obj.setSoLuongDaBan(obj.getSoLuongDaBan() + sl);
    obj.setSoLuongTrongGio(sl);
    order.Order_Food(obj);
    cout << "Buy " << obj.getTenSanPham() << " Successfully" << endl;
    Point += 1 ;
}
void Customer::BuyProduct(Order &order, ElectricalProduct &obj, int sl)
{
    obj.setSoLuongTonKho(obj.getSoLuongTonKho() - sl);
    obj.setSoLuongDaBan(obj.getSoLuongDaBan() + sl);
    obj.setSoLuongTrongGio(sl);
    order.Order_ElectricalProduct(obj);
    cout << "Buy " << obj.getTenSanPham() << " Successfully" << endl;
    Point += 1 ;
}

void Customer::BuyProduct(Order &order, Houseware &obj, int sl)
{
    obj.setSoLuongTonKho(obj.getSoLuongTonKho() - sl);
    obj.setSoLuongDaBan(obj.getSoLuongDaBan() + sl);
    obj.setSoLuongTrongGio(sl);
    order.Order_Houseware(obj);
    cout << "Buy " << obj.getTenSanPham() << " Successfully" << endl;
    Point += 1 ;
}
void Customer::add_to_orders(const Order &ord)
{
    orderHistory.pushBack(ord);
}
void Customer::GetInformation()
{
    // Nhập dữ liệu bằng tay
    std::cout << "Customer Information : " << std::endl;
    std::cout << "Customer ID : ";
    std::cin >> CustomerID;
    std::cout << "Full name : ";
    Menu::getInput(fullName, cin);
    std::cout << "Age : ";
    std::cin >> age;
    std::cout << "Day of birth: ";
    std::cin.ignore();
    std::cin >> DayOfBirth;
    std::cout << "Gender : "  ; 
    Menu::getInput(Gender,cin) ; 
    std::cout << "Address : ";
    std::cin.ignore();
    Menu::getInput(address, cin);
    std::cout << "Phone number : ";
    Menu::getInput(phoneNumber, cin);
    std::cout << "Email: ";
    Menu::getInput(email, cin);
    std::cout << "Point : ";
    std::cin >> Point;
    std::cout << "Customer type :";
    Menu::getInput(CustomerType, cin);
}

Order &Customer::Last_Order()
{
    return orderHistory.at(orderHistory.getSize() - 1);
}
int Customer::getOrd_Size()
{
    return orderHistory.getSize();
}
void Customer::Show_Orders_History(std::ostream &o)
{
    o << "===================================================================" << std::endl;
    o << "                           ORDERS HISTORY   " << std::endl;
    o << "===================================================================" << std::endl;
    o << "Customer : " << GetFullName() << endl;
    o << "ID: " << GetCustomerID() << endl;
    o << "===========================================" << std::endl;
    o << std::setw(8) << "Order ID"
      << "|"
      << std::setw(14) << "Total Amount"
      << "|"
      << std::setw(12) << "Date"
      << "    |"
      << std::setw(12) << "Quanity"
      << "|"
      << std::setw(12) << "Is Complete"
      << "|"
      << std::endl
      << "-------------------------------------------------------------------" << endl;

    for (int i = 0; i < orderHistory.getSize(); i++)
    {
        if(orderHistory.at(i).HoanThanh)
        orderHistory.at(i).Display_List(o);
    }
}
void Customer::AddDiscount(Discount &discount)
{
    discounts.pushBack(discount);
    cout << "Add discount" << discount.getDiscountID() << " " << discount.getPercentage() << "succcessfully" << endl;
}

Vector_Class<Discount> &Customer::GetDiscounts()
{
    return discounts;
}
void Customer::ApplyDiscounts(Order &order)
{
}
void Customer::ViewStatistics(Time &start, Time &end)
{
    std::cout << "Start time : " ; 
    std::cout << start  << std::endl ;
    std::cout << "End time : "  ; 
    std::cout << end << std::endl ; 
    getStatistics().DisplayCustomerStatistics();
}
void Customer::UpdateStatistics(Time &start, Time &end)
{
    
        std::cout << "Excuted time : " << Date::getRealTime() << std::endl;
        double avgquanity = 0;
        double avgSpent = 0;
        double totalspent = 0;
        double totalwithoutdiscount = 0;
        int numUseDiscount = 0;
        int total_import_price = 0;
        int totalOrders = 0;

        for (size_t i = 0; i < getOrderHistory().getSize(); i++)
        {
            if ((getOrderHistory().at(i).GetOrderTime()) >= start && (getOrderHistory().at(i).GetOrderTime()) <= end)
            {
                totalOrders++;
                avgquanity += getOrderHistory().at(i).getQuanityProduct();
                avgSpent += getOrderHistory().at(i).getTotalAfterDiscount();
                totalspent += getOrderHistory().at(i).getTotalAfterDiscount();
                total_import_price += getOrderHistory().at(i).GetImportPrice();
                totalwithoutdiscount += getOrderHistory().at(i).GetTotalAmount();
                if (getOrderHistory().at(i).getTotalAfterDiscount() != getOrderHistory().at(i).GetTotalAmount())
                {
                    numUseDiscount++;
                }
            }
        }

        if (totalOrders == 0)
        {
            throw std::runtime_error("No orders found within the specified time range.");
        }

        getStatistics().SetCustomerID(CustomerID);
        getStatistics().SetTotalOrders(totalOrders);

        getStatistics().SetTotalAmountSpent(totalspent);
        avgquanity = avgquanity / (totalOrders);
        getStatistics().SetAvgQuantityPerOrder(avgquanity);
        avgSpent = avgSpent / (totalOrders);
        getStatistics().SetAvgAmountPerOrder(avgSpent);
        getStatistics().SetSavedMoneyDiscount(totalwithoutdiscount - totalspent);
        getStatistics().SetAvgDiscountRate(totalspent / totalwithoutdiscount);
        getStatistics().SetCustomerLifetimeValue(totalspent - total_import_price);
        getStatistics().SetAvgDiscountRate(numUseDiscount * 100 / totalOrders);
    }
   
