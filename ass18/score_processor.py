class ScoreProcessor:
    def process_score_file(self, file_path: str) -> int:
        try:
            with open(file_path, "r") as f:
                content = f.read().strip()
                score = int(content)
                result = score * 10
        except FileNotFoundError:
            print("Error: The file was not found.")
            raise
        except ValueError:
            print("Error: Invalid data format. Expected an integer.")
            raise
        else:
            print("Data processed successfully")
            return result
        finally:
            print("File cleanup completed")
