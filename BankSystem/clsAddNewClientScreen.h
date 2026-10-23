#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsInputValidate.h"

class clsAddNewClientScreen : protected clsScreen
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
        Client.AccountBalance = clsInputValidate::ReadFloatNumber() ;
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

    static void ShowAddNewClientScreen()
    {
        if (!CheckAccessRights(clsBankUser::enPermissions::pListClients))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\t  Add New Client Screen");

        string AccountNumber = "";

        AccountNumber = clsInputValidate::ReadString("\nPlease Enter Client Account Number :");
        while (clsBankClient::IsClientExist(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadString("\nAccount Number is Already Used , Choose Another One : ");
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        cout << "\n\n Add New Client Info ";
        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Updated Successfully :-)  \n";
            _PrintClient(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFailedEmptyObject:
        {
            cout << "\n Error account was not saved because it's Empty";
            break;
        }
        case clsBankClient::enSaveResults::svFailedAccountNumberExist:
        {
            cout << "\n Error account was not saved because account number is used \n";
            break;
        }
        }
    }



};
