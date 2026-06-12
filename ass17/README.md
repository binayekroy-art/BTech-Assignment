# Assignment 17 – User Onboarding Validation Module

Build a user onboarding validation module for a platform. Your objective is to create a core validation class that processes incoming application data—specifically a user's email address and age—and enforces strict business constraints before allowing a registration to complete.

The system must ensure that the email string is neither null nor empty, and that it conforms to a standard email format matching the regular expression patterns outlined in the slides (containing a valid identifier, an @ symbol, and a domain name). Additionally, the system must enforce a strict age restriction where applicants must be at least 18 years old to create an account.

**Implementation Rules**

If choosing **Java**: ... *(omitted)*

If choosing **Python**:
- Implement a custom exception named `InvalidEmailError` and another named `UnderageError`, both inheriting from the appropriate built‑in exception classes.
- Create a `RegistrationService` class containing a method `def register_user(self, email: str, age: int) -> bool`.
- Use an internal `assert` statement to verify basic state invariants.
- Write a `pytest` suite using a shared `@pytest.fixture` for configuration, validating successful workflows, and utilizing `pytest.raises` to assert that your custom errors are raised appropriately during invalid inputs.

You must have the followings:
- **Custom Exception Design**: Correctly establishing inheritance with descriptive, dynamic error messages.
- **Core Service Validation**: Implementing the regex parsing, age boundary checks, invariant assertions, and proper exception triggering.
- **Unit Testing Suite**: Writing comprehensive test cases using the correct framework assertions, proper test lifecycle setup (fixtures/before‑each), and targeted exception testing.
