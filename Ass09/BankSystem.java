import java.util.*;

class Account {
    private String accountNumber;
    private String ownerName;
    private double balance;

    public Account(String accountNumber, String ownerName) {
        this(accountNumber, ownerName, 0.0);
    }

    public Account(String accountNumber, String ownerName, double balance) {
        this.accountNumber = accountNumber;
        this.ownerName = ownerName;
        this.balance = balance;
    }

    public String getAccountNumber() { return accountNumber; }
    public String getOwnerName() { return ownerName; }
    public double getBalance() { return balance; }
    public void setOwnerName(String ownerName) { this.ownerName = ownerName; }

    public void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            System.out.println("Deposited: " + amount);
        } else {
            throw new IllegalArgumentException("Deposit amount must be positive!");
        }
    }

    public void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            System.out.println("Withdrawn: " + amount);
        } else {
            throw new IllegalArgumentException("Invalid withdrawal amount!");
        }
    }

    public void display() {
        System.out.println("Account Number: " + accountNumber);
        System.out.println("Owner: " + ownerName);
        System.out.println("Balance: " + balance);
    }
}

class SavingsAccount extends Account {
    private final double interestRate;

    public SavingsAccount(String accountNumber, String ownerName, double balance, double interestRate) {
        super(accountNumber, ownerName, balance);
        this.interestRate = interestRate;
    }

    @Override
    public void display() {
        super.display();
        System.out.println("Interest Rate: " + interestRate + "%");
        double interest = getBalance() * interestRate / 100;
        System.out.println("Interest Earned: " + interest);
    }
}

class CurrentAccount extends Account {
    private final double overdraftLimit;

    public CurrentAccount(String accountNumber, String ownerName, double balance, double overdraftLimit) {
        super(accountNumber, ownerName, balance);
        this.overdraftLimit = overdraftLimit;
    }

    @Override
    public void withdraw(double amount) {
        if (amount > 0 && amount <= getBalance() + overdraftLimit) {
            if (amount <= getBalance()) {
                super.withdraw(amount);
            } else {
                double overdraftUsed = amount - getBalance();
                super.withdraw(getBalance()); // empty the balance
                System.out.println("Overdraft used: " + overdraftUsed);
            }
            System.out.println("Withdrawn: " + amount);
        } else {
            throw new IllegalArgumentException("Withdrawal exceeds overdraft limit!");
        }
    }

    @Override
    public void display() {
        super.display();
        System.out.println("Overdraft Limit: " + overdraftLimit);
    }
}

public class BankSystem {
    public static void main(String[] args) {
        List<Account> accounts = new ArrayList<>();
        accounts.add(new SavingsAccount("S001", "Alice", 5000, 5.0));
        accounts.add(new CurrentAccount("C001", "Bob", 2000, 1000));

        accounts.get(0).deposit(1000);
        accounts.get(1).withdraw(2500);

        for (Account acc : accounts) {
            System.out.println("\n--- Account Details ---");
            acc.display();
        }
    }
}
