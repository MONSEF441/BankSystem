# Bank Management System (Console Application)

A modular, console-based Bank Management System built in C++ using Object-Oriented Programming (OOP). Developed as part of **Course 11: OOP as It Should Be in Applications** from [Programming Advices](https://programmingadvices.com/).

The application separates UI presentation from business logic and implements role-based permissions, financial transactions, currency conversion, and file-based data persistence.

---

## Features & Modules

### 1. Client Management
- **CRUD Operations:** Add, view, update, and delete client accounts.
- **Client Information:** Manage personal details, PIN codes, contact information, and account balances.
- **Find Client:** Retrieve client information using an account number.

### 2. Transactions
- **Deposit & Withdraw:** Perform transactions with balance validation and boundary checks.
- **Total Balances:** Calculate and display the combined balances of all bank accounts.
- **Fund Transfers:** Transfer money between accounts and record transactions in `TransferLog.txt`.
- **Transfer History:** View previously recorded account transfers.

### 3. User & Permission Management
- **User CRUD:** Add, view, update, and delete system users.
- **Bitwise Permissions:** Configure granular access rights, including full access, transaction management, client management, and currency exchange.
- **Login Register:** Record successful logins with timestamps in `LoginRegister.txt`.

### 4. Currency Exchange
- **List Currencies:** Display supported currencies, ISO codes, and exchange rates relative to USD.
- **Find Currency:** Search for currencies by country name or ISO currency code.
- **Update Exchange Rates:** Modify exchange rates stored in `Currencies.txt`.
- **Currency Calculator:** Convert amounts between supported currencies using their exchange rates.

---

## OOP Architecture & Design

### Inheritance & Abstraction
- `clsPerson`: Base class extended by `clsBankClient` and `clsBankUser`.
- `clsScreen`: Base class providing shared screen headers and permission-checking functionality.

### Interfaces & Contracts
- `InterfaceCommunication.h`: Defines the interface contract used for communication between relevant components.

### Separation of Concerns
- **Domain Layer:** `clsBankClient`, `clsBankUser`, and `clsCurrency` handle domain-related operations.
- **Presentation Layer:** Dedicated screen classes, including `clsMainScreen`, `clsTransactionsScreen`, and `clsLoginScreen`, manage user interaction.
- **Utilities & Validation:** Reusable helper libraries, including `clsInputValidate`, `clsString`, `clsDate`, and `clsUtil`, provide common functionality.

### File-Based Persistence
The application stores data in delimited text files, including:
- `Clients.txt`
- `Users.txt`
- `Currencies.txt`
- `TransferLog.txt`
- `LoginRegister.txt`

---

## Project Structure

```text
BankSystem/
├── BankSystem.cpp
├── BankSystem.sln
│
├── Core Models
│   ├── clsPerson.h
│   ├── clsBankClient.h
│   ├── clsBankUser.h
│   ├── clsCurrency.h
│   └── InterfaceCommunication.h
│
├── Presentation Screens
│   ├── clsScreen.h
│   ├── clsMainScreen.h
│   ├── clsLoginScreen.h
│   ├── clsLoginRegisterScreen.h
│   ├── clsManageUsersScreen.h
│   ├── clsTransactionsScreen.h
│   ├── clsTransferScreen.h
│   ├── clsTransferLogScreen.h
│   ├── clsCurrencyExchangeMainScreen.h
│   └── Other screen classes
│
├── Utilities & Shared
│   ├── clsDate.h
│   ├── clsString.h
│   ├── clsInputValidate.h
│   ├── clsUtil.h
│   └── Global.h
│
└── Data Storage
    ├── Clients.txt
    ├── Users.txt
    ├── Currencies.txt
    ├── LoginRegister.txt
    └── TransferLog.txt
```

*Note: The structure above is illustrative. Actual file locations may differ.*

---

## Getting Started

### Prerequisites
- **IDE:** Visual Studio 2019/2022 or another compatible C++ development environment.
- **Platform:** Windows.
- **Language Standard:** C++17 or the standard required by the project configuration.

### Build & Run

1. Clone the repository:

   ```bash
   git clone https://github.com/MONSEF441/BankSystem.git
   ```

2. Open `BankSystem.sln` in Visual Studio.
3. Select the `Debug` or `Release` configuration and the appropriate platform (`x64` or `x86`).
4. Build the solution using `Ctrl + Shift + B`.
5. Run the application using `Ctrl + F5`.

### Default Login Credentials

| Username | Password | Permissions |
|---|---|---|
| `Admin` | `Adminn1234` | Full Access (`-1`) |

**Security note:** These are the default credentials documented for the application. Change them before distributing the project, and avoid committing real passwords or sensitive user data to the repository.

---

## Technologies Used

- C++
- Object-Oriented Programming (OOP)
- File Handling
- Bitwise Permission Management
- Console-Based User Interface
- Visual Studio
