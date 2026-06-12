import java.util.ArrayList;
import java.util.Scanner;

public class BookTitles {
    public static void main(String[] args) {
        ArrayList<String> books = new ArrayList<>();

        books.add("The Great Gatsby");
        books.add("To Kill a Mockingbird");
        books.add("1984");
        books.add("Pride and Prejudice");
        books.add("The Catcher in the Rye");
        books.add("Harry Potter and the Sorcerer's Stone");

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a word to search for in book titles: ");
        String searchWord = scanner.nextLine().toLowerCase();

        System.out.println("\nBooks containing \"" + searchWord + "\":");
        boolean found = false;

        for (String title : books) {
            if (title.toLowerCase().contains(searchWord)) {
                System.out.println("- " + title);
                found = true;
            }
        }

        if (!found) {
            System.out.println("No books found containing that word.");
        }

        scanner.close();
    }
}