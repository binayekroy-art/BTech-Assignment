class Address:
    def __init__(self, street, city, zipCode):
        self.street = street
        self.city = city
        self.zipCode = zipCode

    def __str__(self):
        return f"{self.street}, {self.city}, {self.zipCode}"


class Student:
    def __init__(self, name, age, address):
        self.name = name
        self._age = None
        self.age = age
        self.address = address
        self.courses = []

    @property
    def age(self):
        return self._age

    @age.setter
    def age(self, value):
        if 0 < value < 120:
            self._age = value
        else:
            raise ValueError("Age must be between 1 and 119")

    def add_course(self, course):
        self.courses.append(course)

    def display(self):
        print("Name:", self.name)
        print("Age:", self.age)
        print("Address:", self.address)
        print("Courses:", ", ".join(self.courses) if self.courses else "None")


class ScholarshipStudent(Student):
    def __init__(self, name, age, address, scholarshipAmount):
        super().__init__(name, age, address)
        self.scholarshipAmount = scholarshipAmount

    def display(self):
        super().display()
        print("Scholarship Amount:", self.scholarshipAmount)


addr1 = Address("123 Main St", "Guwahati", "781001")
student1 = Student("Ravi", 20, addr1)
student1.add_course("Math")
student1.add_course("Physics")

addr2 = Address("456 College Rd", "Tezpur", "784001")
student2 = ScholarshipStudent("Anita", 22, addr2, 10000)
student2.add_course("Computer Science")

print("\n--- Student Details ---")
student1.display()

print("\n--- Scholarship Student Details ---")
student2.display()
