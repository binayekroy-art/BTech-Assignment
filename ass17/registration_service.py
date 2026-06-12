import re

class InvalidEmailError(ValueError):
    def __init__(self, email: str):
        super().__init__(f"Invalid email address provided: '{email}'")

class UnderageError(RuntimeError):
    def __init__(self, age: int):
        super().__init__(f"User is underage: {age} years old (must be at least 18)")

class RegistrationService:
    EMAIL_PATTERN = re.compile(r"^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$")

    def __init__(self):
        self.system_ready = True

    def register_user(self, email: str, age: int) -> bool:
        assert self.system_ready, "System context is invalid"
        if not email or not self.EMAIL_PATTERN.match(email):
            raise InvalidEmailError(email)
        if age < 18:
            raise UnderageError(age)
        return True
