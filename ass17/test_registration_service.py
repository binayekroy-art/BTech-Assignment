import pytest
from registration_service import RegistrationService, InvalidEmailError, UnderageError

@pytest.fixture
def service():
    return RegistrationService()

def test_successful_registration(service):
    assert service.register_user("valid.user@example.com", 25) is True

def test_invalid_email_empty(service):
    with pytest.raises(InvalidEmailError):
        service.register_user("", 25)

def test_invalid_email_format(service):
    with pytest.raises(InvalidEmailError):
        service.register_user("invalid-email.com", 30)

def test_underage_registration(service):
    with pytest.raises(UnderageError):
        service.register_user("teen@example.com", 16)

def test_system_invariant(service):
    service.system_ready = False
    with pytest.raises(AssertionError):
        service.register_user("user@example.com", 20)
