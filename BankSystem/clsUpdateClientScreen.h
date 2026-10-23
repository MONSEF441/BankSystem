#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsUpdateClientScreen :protected clsScreen

{
private:

    static void _ReadClientInfo(clsBankClient& Client)
    {

        Client.FirstName = clsInputValidate::ReadString("\nEnter FirstName: ");

        Client.LastName = clsInputValidate::ReadString("\nEnter LastName: ");

        Client.Email = clsInputValidate::ReadString("\nEnter Email: ");

        Client.Phone = clsInputValidate::ReadString("\nEnter Phone: ");

        Client.PinCode = clsInputValidate::ReadString("\nEnter PinCode: ");

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

public:

    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsBankUser::enPermissions::pListClients))
        {
            return;// this will exit the function and it will not continue
        }
        _DrawScreenHeader("\tUpdate Client Screen");

        string AccountNumber = "";

        AccountNumber = clsInputValidate::ReadString("\nPlease Enter Client Account Number :");
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadString("\nAccount Number Is Not Found , Choose Another One : ");
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\n\nUpdate Client Info ";
        _ReadClientInfo(Client);

        clsBankClient::enSaveResults SaveResult = Client.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Updated Successfully :-)  \n";
            _PrintClient(Client);
            break;
        }
        case clsBankClient::enSaveResults::svFailedEmptyObject:
        {
            cout << "\n Error account was not saved because it's Empty";
            break;
        }
        }

    }
};
