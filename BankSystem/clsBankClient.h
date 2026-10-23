#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>

using namespace std;

class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1 , AddNewMode = 2};
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    struct stTransferLogRecord;
    static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stTransferLogRecord TransferLogRecord;

        vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
        TransferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TransferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
        TransferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
        TransferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
        TransferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
        TransferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
        TransferLogRecord.UserName = vTrnsferLogRecordLine[6];

        return TransferLogRecord;

    }


    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector <string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], clsUtil::DecryptText(vClientData[5]), stod(vClientData[6]));

    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += clsUtil::EncryptText(Client.PinCode) + Seperator;
        stClientRecord += to_string(Client.AccountBalance);
        
        
        return stClientRecord;

    }

    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }

    static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsBankClient> vClients;
        vClients = _LoadClientsDataFromFile();

        for (clsBankClient & C : vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this; 

            }
        }
         
        _SaveClientsDataToFile(vClients);
    
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }


    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }


    string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
        string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += AccountNumber() + Seperator;
        TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }

    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
    {

        string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

        fstream MyFile;
        MyFile.open("TransfersLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }


public:

    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }
   
    struct stTransferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float Amount;
        float srcBalanceAfter;
        float destBalanceAfter;
        string UserName;

    };

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }
  
    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }
    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


    ///////////////////////////////////////////////
   



   static clsBankClient Find(string AccountNumber)
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

              clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client._AccountNumber == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }


                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return _GetEmptyClientObject();


    }
   static clsBankClient Find(string AccountNumber , string PinCode)
   {

       vector <clsBankClient> vClients;

       fstream MyFile;
       MyFile.open("Clients.txt", ios::in);//read Mode

       if (MyFile.is_open())
       {

           string Line;

           while (getline(MyFile, Line))
           {

               clsBankClient Client = _ConvertLinetoClientObject(Line);
               if (Client._AccountNumber == AccountNumber && Client.PinCode == PinCode)
               {
                   MyFile.close();
                   return Client;
               }


               vClients.push_back(Client);
           }

           MyFile.close();

       }

       return _GetEmptyClientObject();


   }
   static clsBankClient GetAddNewClientObject(string AccountNumber)
   {
       return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
   }

   enum enSaveResults {  svFailedEmptyObject = 0  , svSucceeded = 1 , svFailedAccountNumberExist=2 };

   enSaveResults Save()
   {
     switch (_Mode)
     {
       case enMode::EmptyMode :
       {
           return enSaveResults::svFailedEmptyObject;
           break;
       }
       case enMode::UpdateMode :
       {   _Update();
           return enSaveResults::svSucceeded;
           break;
       }
       case enMode::AddNewMode :
       {
           //This will add new record to file or database
           if (clsBankClient::IsClientExist(_AccountNumber))
           {
               return enSaveResults::svFailedAccountNumberExist ;
           }
           else
           {
               _AddNew();

               //We need to set the mode to update after add new
               _Mode = enMode::UpdateMode;
               return enSaveResults::svSucceeded;
           }

           break;
       }
     }
   }

   static bool IsClientExist(string AccountNumber)
   {

       clsBankClient Client = clsBankClient::Find(AccountNumber);

       return (!Client.IsEmpty());

   }
   bool Delete()
   {
       vector <clsBankClient> _vClients;
       _vClients = _LoadClientsDataFromFile();

       for (clsBankClient& C : _vClients)
       {
           if (C.AccountNumber() == _AccountNumber)
           {
               C._MarkedForDelete = true;
               break;
           }

       }

       _SaveClientsDataToFile(_vClients);

       *this = _GetEmptyClientObject();

       return true;

   }
   static vector <clsBankClient> GetClientsList()
   {
       return _LoadClientsDataFromFile();
   }
   void Deposit(double Amount)
   {
       _AccountBalance += Amount;
       Save();
   }

   bool Withdraw(double Amount)
   {
       if (Amount > _AccountBalance)
       {
           return false;
       }
       else
       {
           _AccountBalance -= Amount;
           Save();
           return true;
       }

   }

   static double GetTotalBalances()
   {
       vector <clsBankClient> vClients = clsBankClient::GetClientsList();

       double TotalBalances = 0;

       for (clsBankClient Client : vClients)
       {

           TotalBalances += Client.AccountBalance;
       }

       return TotalBalances;
   }

   bool Transfer(float Amount, clsBankClient& DestinationClient , string UserName)
   {
       if (Amount > AccountBalance)
       {
           return false;
       }

       Withdraw(Amount);
       DestinationClient.Deposit(Amount);
       _RegisterTransferLog(Amount, DestinationClient, UserName);

       return true;
   }
   
   static  vector <stTransferLogRecord> GetTransfersLogList()
   {
       vector <stTransferLogRecord> vTransferLogRecord;

       fstream MyFile;
       MyFile.open("TransfersLog.txt", ios::in);//read Mode

       if (MyFile.is_open())
       {

           string Line;

           stTransferLogRecord TransferRecord;

           while (getline(MyFile, Line))
           {

               TransferRecord = _ConvertTransferLogLineToRecord(Line);

               vTransferLogRecord.push_back(TransferRecord);

           }

           MyFile.close();

       }

       return vTransferLogRecord;

   }


};