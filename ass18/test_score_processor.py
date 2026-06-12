import pytest
from score_processor import ScoreProcessor

@pytest.fixture
def processor():
    return ScoreProcessor()

def test_valid_score(tmp_path, processor):
    file_path = tmp_path / "score.txt"
    file_path.write_text("7")
    result = processor.process_score_file(str(file_path))
    assert result == 70

def test_missing_file(processor):
    with pytest.raises(FileNotFoundError):
        processor.process_score_file("non_existent.txt")

def test_invalid_data(tmp_path, processor):
    file_path = tmp_path / "score.txt"
    file_path.write_text("abc")
    with pytest.raises(ValueError):
        processor.process_score_file(str(file_path))
