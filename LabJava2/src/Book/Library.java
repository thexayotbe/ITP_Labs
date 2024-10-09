package Book;

import java.util.ArrayList;

public class Library {
    // List of books
    private ArrayList<Book> books;

    // Constructor
    public Library() {
        books = new ArrayList<>();
    }

    // Add a book to the library
    public void addBook(Book book) {
        books.add(book);
    }

    // Update book quantity
    public void updateBookQty(String bookName, int newQty) {
        for (Book book : books) {
            if (book.getName().equalsIgnoreCase(bookName)) {
                book.setQty(newQty);
                break;
            }
        }
    }

    // Display information about all books in the library
    public void displayBooks() {
        for (Book book : books) {
            System.out.println(book.toString());
        }
    }

    public static void main(String[] args) {
        // Create authors
        Author author1 = new Author("John Doe", "johndoe@example.com", 'M');
        Author author2 = new Author("Jane Smith", "janesmith@example.com", 'F');

        // Create books
        Book book1 = new Book("Java Programming", author1, 29.99, 10);
        Book book2 = new Book("Data Structures", author2, 39.99, 5);

        // Create library and add books
        Library library = new Library();
        library.addBook(book1);
        library.addBook(book2);

        // Display books
        library.displayBooks();

        // Update quantity of a book
        library.updateBookQty("Java Programming", 15);

        // Display books after update
        System.out.println("\nAfter updating quantity:");
        library.displayBooks();
    }
}
