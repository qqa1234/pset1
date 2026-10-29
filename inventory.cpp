
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct item
{
    int partNumber;
    string description;
    int quantity;

    item (int num, string dsp, int quant)
    {
        partNumber = num;
        description = dsp;
        quantity = quant;
    }
};

int search (vector<item>& inventory, int partNumber)
{
    int left = 0;
    int right = inventory.size() - 1;

    while (left <= right)
    {
        int mid = left+(right - left)/2;

        if (inventory[mid].partNumber == partNumber)
        {
            return mid;
        }

        else if (inventory[mid].partNumber < partNumber)
        {
            left = mid + 1;
        }

        else
        {
            right = mid - 1;
        }
    }

    return -1;
}


void add(vector<item>& inventory, item& newItem)
{
    int index = search(inventory, newItem.partNumber);

    if (index != -1)
    {
        inventory[index].quantity += newItem.quantity;
        return;
    }

    int pos = 0;

    while (pos < inventory.size() &&
           inventory[pos].partNumber < newItem.partNumber)
    {
        pos++;
    }

    inventory.insert(inventory.begin() + pos, newItem);
}


void show(vector<item>& inventory, int partNumber)
{
    int index = search (inventory, partNumber);

    if (index == -1)
    {
        cout << "notFound" << endl;
        return;
    }

    cout << "PartNum: " << inventory[index].partNumber << endl;
    cout << "Description: " << inventory[index].description << endl;
    cout << "Quantity: " << inventory[index].quantity << endl;
}



void remove(vector<item>& inventory, int partNumber, int quantity)
{
    int index = search(inventory, partNumber);

    if (index == -1)
    {
        cout << "notFound" << endl;
        return;
    }

    if (quantity <= 0)
    {
        cout << "Invalid quantity" << endl;
        return;
    }

    if (quantity >= inventory[index].quantity)
    {
        inventory.erase(inventory.begin() + index);
        cout << "Item removed" << endl;
    }
    else
    {
        inventory[index].quantity -= quantity;
        cout << "Quantity updated" << endl;
    }
}


void list(vector<item>& inventory)
{
    if (inventory.empty())
    {
        cout << "Inventory is empty" << endl;
        return;
    }

    for (int i = 0; i < inventory.size(); i++)
    {
        show(inventory, inventory[i].partNumber);
        cout << "-------------------" << endl;
    }
}

int main()
{
    vector<item> inventory;

    item a = item (103, "a", 5);
    item b = item (101, "b", 20);
    item c = item (102, "c", 10);

    add(inventory, a);
    add(inventory, b);
    add(inventory, c);

    cout << "Initial inventory:" << endl;
    list(inventory);

    item d = item (101, "b", 20);
    add(inventory, d);

    cout << "add 5 bolts:" << endl;
    show(inventory, 101);

    remove(inventory, 102, 3);

    cout << "remove 3 gears:" << endl;
    show(inventory, 102);

    remove(inventory, 103, 5);

    cout << "final inventory:" << endl;
    list(inventory);

    return 0;
}
