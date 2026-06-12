from abc import ABC, abstractmethod

class LibraryItem(ABC):
    counter = 0

    def __init__(self, title, year):
        self.title = title
        self.year = year
        LibraryItem.counter += 1

    @abstractmethod
    def displayInfo(self):
        pass


class Book(LibraryItem):
    def __init__(self, title, year, author="Unknown"):
        super().__init__(title, year)
        self.author = author

    def displayInfo(self):
        print("Book Title:", self.title)
        print("Year:", self.year)
        print("Author:", self.author)


class DVD(LibraryItem):
    def __init__(self, title, year, duration=0, genre="General"):
        super().__init__(title, year)
        self.duration = duration
        self.genre = genre

    def displayInfo(self):
        print("DVD Title:", self.title)
        print("Year:", self.year)
        print("Duration:", self.duration, "minutes")
        print("Genre:", self.genre)


items = []
items.append(Book("Python Basics", 2020, "John Doe"))
items.append(Book("Algorithms", 2021))
items.append(DVD("Inception", 2010, 148, "Sci-Fi"))
items.append(DVD("Documentary", 2015))

for item in items:
    print("\n--- Library Item ---")
    item.displayInfo()

print("\nTotal Library Items:", LibraryItem.counter)
