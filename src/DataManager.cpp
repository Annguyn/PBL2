#include "DataManager.h"
#include <iomanip>
template <class T>
DataManager<T>::DataManager()
{
}
template <class T>
void DataManager<T>::ShowLists_file(const Vector_Class<T> &data, const char *filename)
{
	std::ofstream file(filename);
	if (file.is_open())
	{
		if (typeid(T) == typeid(Customer) || typeid(T) == typeid(Employee))
		{
			if (typeid(T) == typeid(Employee))
			{
				file << "Employee Information" << endl;
			}
			else if (typeid(T) == typeid(Customer))
			{
				file << "Customer information" << endl;
			}
			file << "STT" << std::right << std::setw(3) << "|";
			file << "ID" << std::right << std::setw(16) << "|";
			file << "Full Name" << std::right << std::setw(14) << "|";
			file << "Age" << std::right << std::setw(4) << "|";
			file << "Day of birth" << std::right << std::setw(0) << "|";
			file << "Address" << std::right << std::setw(21) << "|";
			file << "Phone number" << std::right << std::setw(6) << "|";
			file << "Email" << std::right << std::setw(28) << "|";
			if (typeid(T) == typeid(Employee))
			{
				file << "Position" << std::right << std::setw(14) << "|";
				file << "Salary" << std::right << std::setw(7) << "|";
				file << "Start day" << std::right << std::setw(10) << "|";
				file << "End day" << std::right << std::setw(13) << "|";
				file << "Is working" << std::right << std::setw(0) << "|";
			}
			else if (typeid(T) == typeid(Customer))
			{
				file << "Point" << std::right << std::setw(19) << "|";
				file << "Customer Type" << std::right << std::setw(0) << "|";
			}
		}
		else if (typeid(T) == typeid(Food) || typeid(T) == typeid(ElectricalProduct) || typeid(T) == typeid(Houseware))
		{
			file << "STT" << std::right << std::setw(3) << "|";
			file << "Product ID" << std::right << std::setw(2) << "|";
			file << "Import ID" << std::right << std::setw(0) << "|";
			file << "Product Name" << std::right << std::setw(16) << "|";
			file << "Price" << std::right << std::setw(2) << "|";
			file << "Quanity in Stock" << std::right << std::setw(0) << "|";
			file << "Manufacturer" << std::right << std::setw(12) << "|";
			file << "Production Date" << std::right << std::setw(3) << "|";
			if (typeid(T) == typeid(Food))
			{
				file << "Food Type" << std::right << std::setw(1) << "|";
				file << "Calories" << std::right << std::setw(1) << "|";
				file << "Carbohydrates" << std::right << std::setw(1) << "|";
				file << "Fat" << std::right << std::setw(1) << "|";
				file << "Vitamins" << std::right << std::setw(1) << "|";
				file << "Net Weight" << std::right << std::setw(1) << "|";
				file << "Is Expired" << std::right << std::setw(5) << "|";
			}
			else if (typeid(T) == typeid(ElectricalProduct))
			{
				file << "Resolution X" << std::right << std::setw(1) << "|";
				file << "Resolution Y" << std::right << std::setw(1) << "|";
				file << "Capacity" << std::right << std::setw(1) << "|";
				file << "Screen Size" << std::right << std::setw(1) << "|";
				file << "Wattage" << std::right << std::setw(1) << "|";
				file << "Operating System" << std::right << std::setw(1) << "|";
			}
			else if (typeid(T) == typeid(Houseware))
			{
				file << "Matterial" << std::right << std::setw(0) << "|";
			}
		}
		if (typeid(T) == typeid(Discount))
		{
			file << "STT" << std::right << std::setw(3) << "|";
			file << "Discount ID" << std::right << std::setw(0) << "|";
			file << "Discount Type" << std::right << std::setw(10) << "|";
			file << "Coupon Code" << std::right << std::setw(2) << "|";
			file << "Percentage" << std::right << std::setw(0) << "|";
			file << "Available" << std::right << std::setw(0) << "|";
			file << "\n";
		}
		file << std::endl;
		for (int i = 0; i < 160; ++i)
		{
			file << '-';
		}
		file << endl;
		for (size_t i = 0; i < data.getSize(); i++)
		{
			file << std::left << std::setw(4) << i + 1 << " | ";
			data.at(i).Display_01(file);
		}
		file.close();
	}
}

template <class T>
void DataManager<T>::Display(const Vector_Class<T> &data)
{

	if (typeid(T) == typeid(Customer) || typeid(T) == typeid(Employee))
	{
		if (typeid(T) == typeid(Employee))
		{
			cout << "Employee Information" << endl;
		}
		else if (typeid(T) == typeid(Customer))
		{
			cout << "Customer information" << endl;
		}

		cout << "STT" << std::right << std::setw(3) << "|";
		cout << "ID" << std::right << std::setw(16) << "|";
		cout << "Full Name" << std::right << std::setw(14) << "|";
		cout << "Age" << std::right << std::setw(4) << "|";
		cout << "Day of birth" << std::right << std::setw(0) << "|";
		cout << "Address" << std::right << std::setw(21) << "|";
		cout << "Phone number" << std::right << std::setw(6) << "|";
		cout << "Email" << std::right << std::setw(28) << "|";
		if (typeid(T) == typeid(Employee))
		{
			cout << "Position" << std::right << std::setw(14) << "|";
			cout << "Salary" << std::right << std::setw(7) << "|";
			cout << "Start day" << std::right << std::setw(10) << "|";
			cout << "End day" << std::right << std::setw(13) << "|";
			cout << "Is working" << std::right << std::setw(0) << "|";
		}
		else if (typeid(T) == typeid(Customer))
		{
			cout << "Point" << std::right << std::setw(19) << "|";
			cout << "Customer Type" << std::right << std::setw(0) << "|";
		}
	}
	else if (typeid(T) == typeid(Food) || typeid(T) == typeid(ElectricalProduct) || typeid(T) == typeid(Houseware))
	{
		cout << "STT" << std::right << std::setw(3) << "|";
		cout << "Product ID" << std::right << std::setw(2) << "|";
		cout << "Import ID" << std::right << std::setw(0) << "|";
		cout << "Product Name" << std::right << std::setw(16) << "|";
		cout << "Price" << std::right << std::setw(2) << "|";
		cout << "Quanity in Stock" << std::right << std::setw(0) << "|";
		cout << "Manufacturer" << std::right << std::setw(12) << "|";
		cout << "Production Date" << std::right << std::setw(3) << "|";
		if (typeid(T) == typeid(Food))
		{
			cout << "Food Type" << std::right << std::setw(1) << "|";
			cout << "Calories" << std::right << std::setw(1) << "|";
			cout << "Carbohydrates" << std::right << std::setw(1) << "|";
			cout << "Fat" << std::right << std::setw(1) << "|";
			cout << "Vitamins" << std::right << std::setw(1) << "|";
			cout << "Net Weight" << std::right << std::setw(1) << "|";
			cout << "Is Expired" << std::right << std::setw(5) << "|";
		}
		else if (typeid(T) == typeid(ElectricalProduct))
		{
			cout << "Resolution X" << std::right << std::setw(1) << "|";
			cout << "Resolution Y" << std::right << std::setw(1) << "|";
			cout << "Capacity" << std::right << std::setw(1) << "|";
			cout << "Screen Size" << std::right << std::setw(1) << "|";
			cout << "Wattage" << std::right << std::setw(1) << "|";
			cout << "Operating System" << std::right << std::setw(1) << "|";
		}
		else if (typeid(T) == typeid(Houseware))
		{
			cout << "Material" << std::right << std::setw(0) << "|";
		}
	}
	if (typeid(T) == typeid(Discount))
	{
		cout << "STT" << std::right << std::setw(3) << "|";
		cout << "Discount ID" << std::right << std::setw(0) << "|";
		cout << "Discount Type" << std::right << std::setw(10) << "|";
		cout << "Coupon Code" << std::right << std::setw(2) << "|";
		cout << "Percentage" << std::right << std::setw(0) << "|";
		cout << "Available" << std::right << std::setw(0) << "|";
		cout << "\n";
	}
	cout << std::endl;
	for (int i = 0; i < 160; ++i)
	{
		std::cout << '-';
	}
	cout << endl;
	for (size_t i = 0; i < data.getSize(); i++)
	{
		cout << std::left << std::setw(4) << i + 1 << " | ";
		data.at(i).Display_01(std::cout);
	}
}

template <class T>
void DataManager<T>::AddToLists(const T &obj)
{
	lists.pushBack(obj);
}

template <class T>
void DataManager<T>::SaveData(const Vector_Class<T> data, const char *filename)
{
	std::ofstream file(filename);
	if (file.is_open())
	{
		for (size_t i = 0; i < data.getSize(); i++)
		{
			data[i].WriteDataToFile(file);
		}
		file.close();
	}
	else
	{
		std::cerr << "Can't open" << filename << "for writing" << std::endl;
	}
}

template <class T>
void DataManager<T>::GetData(Vector_Class<T> &data, const char *filename)
{
	std::ifstream file(filename);
	if (file.is_open())
	{
		T temp;
		while (!file.eof())
		{
			temp.ReadDataFromFile(file);
			if (file.eof())
			{
				break;
			}
			data.pushBack(temp);
		}
		file.close();
	}
	else
	{
		std::cerr << "Can't open " << filename << "for reading" << std::endl;
	}
}
