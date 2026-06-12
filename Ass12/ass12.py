from abc import ABC, abstractmethod

class Order(ABC):
    def __init__(self, order_id, amount):
        self.order_id = order_id
        self.amount = amount

class RegularOrder(Order):
    pass

class DiscountedOrder(Order):
    def __init__(self, order_id, amount, discount):
        super().__init__(order_id, amount - discount)

class PriorityOrder(Order):
    def __init__(self, order_id, amount, priority_fee):
        super().__init__(order_id, amount + priority_fee)


class PaymentMethod(ABC):
    @abstractmethod
    def pay(self, amount):
        pass

class CreditCardPayment(PaymentMethod):
    def pay(self, amount):
        print(f"Paid {amount} using Credit Card")

class UPIPayment(PaymentMethod):
    def pay(self, amount):
        print(f"Paid {amount} using UPI")

class WalletPayment(PaymentMethod):
    def pay(self, amount):
        print(f"Paid {amount} using Wallet")


class NotificationChannel(ABC):
    @abstractmethod
    def notify(self, message):
        pass

class EmailNotification(NotificationChannel):
    def notify(self, message):
        print(f"Email sent: {message}")

class SMSNotification(NotificationChannel):
    def notify(self, message):
        print(f"SMS sent: {message}")

class PushNotification(NotificationChannel):
    def notify(self, message):
        print(f"Push notification: {message}")


class Storage(ABC):
    @abstractmethod
    def save(self, order):
        pass

class DatabaseStorage(Storage):
    def save(self, order):
        print(f"Order {order.order_id} saved to Database")

class FileStorage(Storage):
    def save(self, order):
        print(f"Order {order.order_id} saved to File")


class OrderService:
    def __init__(self, payment: PaymentMethod, notification: NotificationChannel, storage: Storage):
        self.payment = payment
        self.notification = notification
        self.storage = storage

    def process_order(self, order: Order):
        print(f"Processing Order {order.order_id}...")
        self.payment.pay(order.amount)
        self.notification.notify(f"Order {order.order_id} processed successfully!")
        self.storage.save(order)


if __name__ == "__main__":
    order_id = int(input("Enter Order ID: "))
    amount = float(input("Enter Order Amount: "))
    order_type = input("Enter Order Type (regular/discounted/priority): ").lower()

    if order_type == "discounted":
        discount = float(input("Enter discount amount: "))
        order = DiscountedOrder(order_id, amount, discount)
    elif order_type == "priority":
        fee = float(input("Enter priority fee: "))
        order = PriorityOrder(order_id, amount, fee)
    else:
        order = RegularOrder(order_id, amount)

    payment_choice = input("Choose Payment Method (card/upi/wallet): ").lower()
    if payment_choice == "card":
        payment = CreditCardPayment()
    elif payment_choice == "upi":
        payment = UPIPayment()
    else:
        payment = WalletPayment()

    notify_choice = input("Choose Notification (email/sms/push): ").lower()
    if notify_choice == "email":
        notification = EmailNotification()
    elif notify_choice == "sms":
        notification = SMSNotification()
    else:
        notification = PushNotification()

    storage_choice = input("Choose Storage (db/file): ").lower()
    if storage_choice == "db":
        storage = DatabaseStorage()
    else:
        storage = FileStorage()

    service = OrderService(payment, notification, storage)
    service.process_order(order)
